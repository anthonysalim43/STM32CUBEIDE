/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : stm32g4xx_nucleo_bus.h
  * @brief          : Header file for the BSP BUS IO driver
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32G4XX_NUCLEO_BUS_H
#define STM32G4XX_NUCLEO_BUS_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g4xx_hal.h"  // For HAL SPI definitions and HAL_GetTick

/* Exported function prototypes ----------------------------------------------*/
int32_t BSP_GetTick(void);
void BSP_SPI2_Init(SPI_HandleTypeDef* hspi2);
void BSP_SPI2_DeInit(void);
/* External variables --------------------------------------------------------*/
extern SPI_HandleTypeDef hspi2;

#ifdef __cplusplus
}
#endif

#endif /* STM32G4XX_NUCLEO_BUS_H */
