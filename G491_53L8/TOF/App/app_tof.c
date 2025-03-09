/**
  ******************************************************************************
  * @file          : app_tof.c
  * @author        : IMG SW Application Team
  * @brief         : This file provides code for the configuration
  *                  of the STMicroelectronics.X-CUBE-TOF1.3.4.2 instances.
  ******************************************************************************
  *
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "app_tof.h"
#include "main.h"
#include <stdio.h>

#include "53l8a1_ranging_sensor.h"
#include "app_tof_pin_conf.h"
#include "stm32g4xx_nucleo.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
#define TIMING_BUDGET (20U) /* 5 ms < TimingBudget < 100 ms */
#define RANGING_FREQUENCY (50U) /* Ranging frequency Hz (shall be consistent with TimingBudget value) */
#define POLLING_PERIOD (1)


typedef struct {
    int32_t distance_mm;
    int32_t status;
    float ambient;
    float signal;
} UsefulData_t;

UsefulData_t useful_data[RANGING_SENSOR_MAX_NB_ZONES][RANGING_SENSOR_NB_TARGET_PER_ZONE];





/* Private variables ---------------------------------------------------------*/
static RANGING_SENSOR_Capabilities_t Cap;
static RANGING_SENSOR_ProfileConfig_t Profile;
static RANGING_SENSOR_Result_t Result;
static int32_t status = 0;
static volatile uint8_t PushButtonDetected = 0;
volatile uint8_t ToF_EventDetected = 0;

/* Private function prototypes -----------------------------------------------*/
static void MX_53L8A1_SimpleRanging_Init(void);
static void MX_53L8A1_SimpleRanging_Process(void);
static void print_result(RANGING_SENSOR_Result_t *Result);
static void toggle_resolution(void);
static void toggle_signal_and_ambient(void);
static void clear_screen(void);
static void display_commands_banner(void);
static void handle_cmd(uint8_t cmd);
static uint8_t get_key(void);
static uint32_t com_has_data(void);

uint32_t prev_time = 0;  // Stores last frame time
uint32_t current_time = 0;  // Stores current time
uint32_t frame_time = 0;  // Stores time taken for one frame
float measured_fps = 0;   // Measured frame rate (Hz)

void MX_TOF_Init(void)
{
  /* USER CODE BEGIN SV */

  /* USER CODE END SV */

  /* USER CODE BEGIN TOF_Init_PreTreatment */

  /* USER CODE END TOF_Init_PreTreatment */

  /* Initialize the peripherals and the TOF components */

  MX_53L8A1_SimpleRanging_Init();

  /* USER CODE BEGIN TOF_Init_PostTreatment */

  /* USER CODE END TOF_Init_PostTreatment */
}

/*
 * LM background task
 */
void MX_TOF_Process(void)
{
  /* USER CODE BEGIN TOF_Process_PreTreatment */
	  //current_time = HAL_GetTick();

	      /* polling mode */

	  MX_53L8A1_SimpleRanging_Process();


	    //  prev_time = HAL_GetTick();; // Update previous time
	      /* Calculate the time taken for one frame */


	   //   frame_time = current_time - prev_time;  // Time in milliseconds


	      /* Compute actual FPS (frames per second) */


	   //       measured_fps = 1000.0f / frame_time;  // Convert ms to Hz
  /* USER CODE END TOF_Process_PreTreatment */



  /* USER CODE BEGIN TOF_Process_PostTreatment */

  /* USER CODE END TOF_Process_PostTreatment */
}

static void MX_53L8A1_SimpleRanging_Init(void)
{
  /* Initialize Virtual COM Port */
	COM_InitTypeDef COM_Init;
	COM_Init.BaudRate = 115200;    // Example baud rate
	COM_Init.WordLength = UART_WORDLENGTH_8B;
	COM_Init.StopBits = UART_STOPBITS_1;
	COM_Init.Parity = UART_PARITY_NONE;
	//COM_Init.Mode = UART_MODE_TX_RX;
	COM_Init.HwFlowCtl = UART_HWCONTROL_NONE;

	BSP_COM_Init(COM1, &COM_Init);


  /* Initialize button */
  BSP_PB_Init(BUTTON_USER, BUTTON_MODE_EXTI);

  /* Sensor reset */
  HAL_GPIO_WritePin(VL53L8A1_PWR_EN_C_PORT, VL53L8A1_PWR_EN_C_PIN, GPIO_PIN_RESET);
  HAL_Delay(2);
  HAL_GPIO_WritePin(VL53L8A1_PWR_EN_C_PORT, VL53L8A1_PWR_EN_C_PIN, GPIO_PIN_SET);
  HAL_Delay(2);
  HAL_GPIO_WritePin(VL53L8A1_LPn_C_PORT, VL53L8A1_LPn_C_PIN, GPIO_PIN_RESET);
  HAL_Delay(2);
  HAL_GPIO_WritePin(VL53L8A1_LPn_C_PORT, VL53L8A1_LPn_C_PIN, GPIO_PIN_SET);
  HAL_Delay(2);

  printf("\033[2H\033[2J");
  printf("53L8A1 Simple Ranging demo application\n");
  printf("Sensor initialization...\n");

  status = VL53L8A1_RANGING_SENSOR_Init(VL53L8A1_DEV_CENTER);

  if (status != BSP_ERROR_NONE)
  {
    printf("VL53L8A1_RANGING_SENSOR_Init failed\n");
    while (1);
  }
}

static void MX_53L8A1_SimpleRanging_Process(void)
{
  uint32_t Id;
  uint32_t measurement_index = 0;
  VL53L8A1_RANGING_SENSOR_ReadID(VL53L8A1_DEV_CENTER, &Id);
  printf("Sensor ID: 0x%X\n", Id);

  VL53L8A1_RANGING_SENSOR_GetCapabilities(VL53L8A1_DEV_CENTER, &Cap);
  printf("Capabilities:\n");
  printf("  Number of Zones: %u\n", Cap.NumberOfZones);
  printf("  Max Targets per Zone: %u\n", Cap.MaxNumberOfTargetsPerZone);
  printf("  Custom ROI: %u\n", Cap.CustomROI);
  printf("  Threshold Detection: %u\n", Cap.ThresholdDetection);


  printf("Sensor ID: 0x%X\n", Id);
  Profile.RangingProfile = RS_PROFILE_8x8_CONTINUOUS;
  Profile.TimingBudget = TIMING_BUDGET;
  Profile.Frequency = RANGING_FREQUENCY; /* Ranging frequency Hz (shall be consistent with TimingBudget value) */
  Profile.EnableAmbient = 0; /* Enable: 1, Disable: 0 */
  Profile.EnableSignal = 0; /* Enable: 1, Disable: 0 */

  /* set the profile if different from default one */
  VL53L8A1_RANGING_SENSOR_ConfigProfile(VL53L8A1_DEV_CENTER, &Profile);

  status = VL53L8A1_RANGING_SENSOR_Start(VL53L8A1_DEV_CENTER, RS_MODE_BLOCKING_CONTINUOUS);

  if (status != BSP_ERROR_NONE)
  {
    printf("VL53L8A1_RANGING_SENSOR_Start failed\n");
    while (1);
  }
  printf("It work\n");
  printf("It work\n");
  printf("It work\n");
  printf("It work\n");
  printf("It work\n");
  printf("It work\n");
  printf("It work\n");
  printf("It work\n");
  printf("It work\n");
  printf("It work\n");

  while (1)
  {

	  //HAL_Delay(2000);
  //   uint32_t start_time = HAL_GetTick();

      // Get sensor data
    //  uint32_t start_time1 = HAL_GetTick();
      status = VL53L8A1_RANGING_SENSOR_GetDistance(VL53L8A1_DEV_CENTER, &Result);
    //  uint32_t end_time1 = HAL_GetTick();


      //uint32_t frame_time1 = end_time1 - start_time1;  // in milliseconds
      //float measured_fps = (frame_time1 > 0) ? 1000.0f / frame_time1 : 0;

      if (status == BSP_ERROR_NONE)
      {
          save_useful_data(&Result);
          print_useful_data_txt(measurement_index);
          measurement_index++;
      }

      // Check for commands, etc.
      if (com_has_data())
      {
          handle_cmd(get_key());
      }

      // Calculate elapsed time for this frame

      // Optionally, print the measured FPS
     // printf("start time1: %d \n", start_time1);
    //   printf("end time1: %d\n", end_time1);
    //   printf("frame rate: %.2f\n", measured_fps);
      HAL_Delay(POLLING_PERIOD);
  }

}

static void print_result(RANGING_SENSOR_Result_t *Result)
{
  int8_t i;
  int8_t j;
  int8_t k;
  int8_t l;
  uint8_t zones_per_line;

  zones_per_line = ((Profile.RangingProfile == RS_PROFILE_8x8_AUTONOMOUS) ||
                    (Profile.RangingProfile == RS_PROFILE_8x8_CONTINUOUS)) ? 8 : 4;

  display_commands_banner();

  printf("Cell Format :\n\n");
  for (l = 0; l < RANGING_SENSOR_NB_TARGET_PER_ZONE; l++)
  {
    printf(" \033[38;5;10m%20s\033[0m : %20s\n", "Distance [mm]", "Status");
    if ((Profile.EnableAmbient != 0) || (Profile.EnableSignal != 0))
    {
      printf(" %20s : %20s\n", "Signal [kcps/spad]", "Ambient [kcps/spad]");
    }
  }

  printf("\n\n");

  for (j = 0; j < Result->NumberOfZones; j += zones_per_line)
  {
    for (i = 0; i < zones_per_line; i++) /* number of zones per line */
    {
      printf(" -----------------");
    }
    printf("\n");

    for (i = 0; i < zones_per_line; i++)
    {
      printf("|                 ");
    }
    printf("|\n");

    for (l = 0; l < RANGING_SENSOR_NB_TARGET_PER_ZONE; l++)
    {
      /* Print distance and status */
      for (k = (zones_per_line - 1); k >= 0; k--)
      {
        if (Result->ZoneResult[j + k].NumberOfTargets > 0)
          printf("| \033[38;5;10m%5ld\033[0m  :  %5ld ",
                 (long)Result->ZoneResult[j + k].Distance[l],
                 (long)Result->ZoneResult[j + k].Status[l]);
        else
          printf("| %5s  :  %5s ", "X", "X");
      }
      printf("|\n");

      if ((Profile.EnableAmbient != 0) || (Profile.EnableSignal != 0))
      {
        /* Print Signal and Ambient */
        for (k = (zones_per_line - 1); k >= 0; k--)
        {
          if (Result->ZoneResult[j + k].NumberOfTargets > 0)
          {
            if (Profile.EnableSignal != 0)
            {
              printf("| %5ld  :  ", (long)Result->ZoneResult[j + k].Signal[l]);
            }
            else
              printf("| %5s  :  ", "X");

            if (Profile.EnableAmbient != 0)
            {
              printf("%5ld ", (long)Result->ZoneResult[j + k].Ambient[l]);
            }
            else
              printf("%5s ", "X");
          }
          else
            printf("| %5s  :  %5s ", "X", "X");
        }
        printf("|\n");
      }
    }
  }

  for (i = 0; i < zones_per_line; i++)
  {
    printf(" -----------------");
  }
  printf("\n");
}





void save_useful_data(RANGING_SENSOR_Result_t *Result) {
    for (int zone = 0; zone < Result->NumberOfZones; zone++) {
        for (int target = 0; target < RANGING_SENSOR_NB_TARGET_PER_ZONE; target++) {
            if (target < Result->ZoneResult[zone].NumberOfTargets) {
                useful_data[zone][target].distance_mm = Result->ZoneResult[zone].Distance[target];
                useful_data[zone][target].status = Result->ZoneResult[zone].Status[target];
                useful_data[zone][target].signal = Result->ZoneResult[zone].Signal[target];
                useful_data[zone][target].ambient = Result->ZoneResult[zone].Ambient[target];
            } else {
                useful_data[zone][target].distance_mm = -1;
                useful_data[zone][target].status = -1;
                useful_data[zone][target].signal = -1;
                useful_data[zone][target].ambient = -1;
            }
        }
    }
}
void print_useful_data_txt(uint32_t measurement_index) {
    uint8_t zones_per_line = ((Profile.RangingProfile == RS_PROFILE_8x8_AUTONOMOUS) ||
                              (Profile.RangingProfile == RS_PROFILE_8x8_CONTINUOUS)) ? 8 : 4;

    // Print measurement number
    printf("\nMeasurement %lu:\n", (long)measurement_index);

    // Print measured FPS (frame rate)
  //  printf("Frame Rate: %.2f Hz\n", measured_fps);




   //   printf(" current_time: %.2f \n", current_time);



     //printf("prev_time: %.2f \n", prev_time);



    // Print distance table
    for (int row = 0; row < zones_per_line; row++) {
        for (int col = 0; col < zones_per_line; col++) {
            int index = row * zones_per_line + col;
            if (useful_data[index][0].distance_mm != -1) {
                printf("%5ld ", (long)useful_data[index][0].distance_mm);
            } else {
                printf("%5s ", "X"); // Print "X" if no data
            }
        }
        printf("\n");  // New line after each row
    }
}






void print_useful_data() {
    uint8_t zones_per_line = ((Profile.RangingProfile == RS_PROFILE_8x8_AUTONOMOUS) ||
                              (Profile.RangingProfile == RS_PROFILE_8x8_CONTINUOUS)) ? 8 : 4;

    printf("\033[2H\033[2J"); // Clear screen
    printf("53L8A1 Simple Ranging demo application\n");
    printf("Cell Format:\n\n");

    for (int target = 0; target < RANGING_SENSOR_NB_TARGET_PER_ZONE; target++) {
        printf(" \033[38;5;10m%20s\033[0m : %20s\n", "Distance [mm]", "Status");
        if (Profile.EnableAmbient || Profile.EnableSignal) {
            printf(" %20s : %20s\n", "Signal [kcps/spad]", "Ambient [kcps/spad]");
        }
    }

    printf("\n\n");

    for (int row = 0; row < zones_per_line; row++) {
        for (int i = 0; i < zones_per_line; i++) printf(" -----------------");
        printf("\n");

        for (int col = 0; col < zones_per_line; col++) printf("|                 ");
        printf("|\n");

        for (int target = 0; target < RANGING_SENSOR_NB_TARGET_PER_ZONE; target++) {
            for (int col = 0; col < zones_per_line; col++) {
                int index = row * zones_per_line + col;
                if (useful_data[index][target].distance_mm != -1) {
                    printf("| \033[38;5;10m%5ld\033[0m  :  %5ld ",
                           (long)useful_data[index][target].distance_mm,
                           (long)useful_data[index][target].status);
                } else {
                    printf("| %5s  :  %5s ", "X", "X");
                }
            }
            printf("|\n");

            if (Profile.EnableAmbient || Profile.EnableSignal) {
                for (int col = 0; col < zones_per_line; col++) {
                    int index = row * zones_per_line + col;
                    if (useful_data[index][target].distance_mm != -1) {
                        printf("| %5ld  :  %5ld ",
                               (long)useful_data[index][target].signal,
                               (long)useful_data[index][target].ambient);
                    } else {
                        printf("| %5s  :  %5s ", "X", "X");
                    }
                }
                printf("|\n");
            }
        }
    }

    for (int i = 0; i < zones_per_line; i++) printf(" -----------------");
    printf("\n");
}








static void toggle_resolution(void)
{
  VL53L8A1_RANGING_SENSOR_Stop(VL53L8A1_DEV_CENTER);

  switch (Profile.RangingProfile)
  {
    case RS_PROFILE_4x4_AUTONOMOUS:
      Profile.RangingProfile = RS_PROFILE_8x8_AUTONOMOUS;
      break;

    case RS_PROFILE_4x4_CONTINUOUS:
      Profile.RangingProfile = RS_PROFILE_8x8_CONTINUOUS;
      break;

    case RS_PROFILE_8x8_AUTONOMOUS:
      Profile.RangingProfile = RS_PROFILE_4x4_AUTONOMOUS;
      break;

    case RS_PROFILE_8x8_CONTINUOUS:
      Profile.RangingProfile = RS_PROFILE_4x4_CONTINUOUS;
      break;

    default:
      break;
  }

  VL53L8A1_RANGING_SENSOR_ConfigProfile(VL53L8A1_DEV_CENTER, &Profile);
  VL53L8A1_RANGING_SENSOR_Start(VL53L8A1_DEV_CENTER, RS_MODE_BLOCKING_CONTINUOUS);
}

static void toggle_signal_and_ambient(void)
{
  VL53L8A1_RANGING_SENSOR_Stop(VL53L8A1_DEV_CENTER);

  Profile.EnableAmbient = (Profile.EnableAmbient) ? 0U : 1U;
  Profile.EnableSignal = (Profile.EnableSignal) ? 0U : 1U;

  VL53L8A1_RANGING_SENSOR_ConfigProfile(VL53L8A1_DEV_CENTER, &Profile);
  VL53L8A1_RANGING_SENSOR_Start(VL53L8A1_DEV_CENTER, RS_MODE_BLOCKING_CONTINUOUS);
}

static void clear_screen(void)
{
  printf("%c[2J", 27); /* 27 is ESC command */
}

static void display_commands_banner(void)
{
  /* clear screen */
  printf("%c[2H", 27);

  printf("53L8A1 Simple Ranging demo application\n");
  printf("--------------------------------------\n\n");

  printf("Use the following keys to control application\n");
  printf(" 'r' : change resolution\n");
  printf(" 's' : enable signal and ambient\n");
  printf(" 'c' : clear screen\n");
  printf("\n");
}

static void handle_cmd(uint8_t cmd)
{
  switch (cmd)
  {
    case 'r':
      toggle_resolution();
      clear_screen();
      break;

    case 's':
      toggle_signal_and_ambient();
      clear_screen();
      break;

    case 'c':
      clear_screen();
      break;

    default:
      break;
  }
}

static uint8_t get_key(void)
{
  uint8_t cmd = 0;

  HAL_UART_Receive(&hcom_uart[COM1], &cmd, 1, HAL_MAX_DELAY);

  return cmd;
}

static uint32_t com_has_data(void)
{
  return __HAL_UART_GET_FLAG(&hcom_uart[COM1], UART_FLAG_RXNE);;
}

void BSP_PB_Callback(Button_TypeDef Button)
{
  PushButtonDetected = 1;
}

#ifdef __cplusplus
}
#endif
