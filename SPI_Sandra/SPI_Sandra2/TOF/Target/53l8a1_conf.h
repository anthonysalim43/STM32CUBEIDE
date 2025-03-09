/**
  ******************************************************************************
  * @file    53l8a1_conf.h
  * @author  IMG SW Application Team
  * @brief   This file contains definitions for the ToF components bus interfaces
  *          when using the X-NUCLEO-53L8A1 expansion board
  ******************************************************************************
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

#include "stm32g4xx_hal.h"
#include "stm32g4xx_nucleo_bus.h"
#include "platform.h"
#include "stm32g4xx_nucleo_errno.h"

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef VL53L8A1_CONF_H
#define VL53L8A1_CONF_H

#ifdef __cplusplus
extern "C" {
#endif

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/*
 * the 53L8A1 BSP driver uses this symbol to allocate a structure for each device
 * if you are only using the on-board sensor without break-out boards
 * change its to (1U) in order to save space in RAM memory
 */
#define RANGING_SENSOR_INSTANCES_NBR    (3U)



#define VL53L8A1_SPI_INIT               BSP_SPI2_Init
#define VL53L8A1_SPI_DEINIT             BSP_SPI2_DeInit
#define VL53L8A1_SPI_WRITEREG           VL53L8CX_WrByte
#define VL53L8A1_SPI_READREG            VL53L8CX_RdByte
#define VL53L8A1_GETTICK                BSP_GetTick


#ifdef __cplusplus
}
#endif

#endif /* VL53L8A1_CONF_H*/


