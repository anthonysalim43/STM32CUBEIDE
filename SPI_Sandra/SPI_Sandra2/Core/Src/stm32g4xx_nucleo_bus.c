/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : stm32g4xx_nucleo_bus.c
  * @brief          : source file for the BSP BUS IO driver
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

/* Includes ------------------------------------------------------------------*/
#include "stm32g4xx_nucleo_bus.h"
//SPI_HandleTypeDef hspi2;



int32_t BSP_GetTick(void) {
  return HAL_GetTick();
}


 void BSP_SPI2_Init(SPI_HandleTypeDef* hspi2)
{

	  /* USER CODE BEGIN SPI2_Init 0 */

	  /* USER CODE END SPI2_Init 0 */

	  /* USER CODE BEGIN SPI2_Init 1 */

	  /* USER CODE END SPI2_Init 1 */
	  /* SPI2 parameter configuration*/
	  hspi2->Instance = SPI2;
	  hspi2->Init.Mode = SPI_MODE_MASTER;
	  hspi2->Init.Direction = SPI_DIRECTION_2LINES;
	  hspi2->Init.DataSize = SPI_DATASIZE_8BIT;
	  hspi2->Init.CLKPolarity = SPI_POLARITY_HIGH;
	  hspi2->Init.CLKPhase = SPI_PHASE_2EDGE;
	  hspi2->Init.NSS = SPI_NSS_SOFT;
	  hspi2->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_64;
	  hspi2->Init.FirstBit = SPI_FIRSTBIT_MSB;
	  hspi2->Init.TIMode = SPI_TIMODE_DISABLE;
	  hspi2->Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	  hspi2->Init.CRCPolynomial = 7;
	  hspi2->Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
	  hspi2->Init.NSSPMode = SPI_NSS_PULSE_DISABLE;
	  if (HAL_SPI_Init(&hspi2) != HAL_OK)
	  {
		  printf("erro while initilizing the spi2\n");
	    Error_Handler();
	  }
	  /* USER CODE BEGIN SPI2_Init 2 */

	  /* USER CODE END SPI2_Init 2 */

}
 void BSP_SPI2_DeInit(void)
 {
   /* USER CODE BEGIN BSP_SPI2_DeInit 0 */

   /* USER CODE END BSP_SPI2_DeInit 0 */
printf("Hey deinit\n");
printf("Hey deinit\n");
printf("Hey deinit\n");
printf("Hey deinit\n");
printf("Hey deinit\n");
printf("Hey deinit\n");
printf("Hey deinit\n");
printf("Hey deinit\n");
printf("Hey deinit\n");
printf("Hey deinit\n");
printf("Hey deinit\n");
printf("Hey deinit\n");

/* De-initialize the SPI peripheral */
   if (HAL_SPI_DeInit(&hspi2) != HAL_OK)
   {
     Error_Handler();
   }

   /* USER CODE BEGIN BSP_SPI2_DeInit 1 */
   // Optionally de-initialize GPIO pins or disable clocks here if needed
   /* USER CODE END BSP_SPI2_DeInit 1 */
 }

