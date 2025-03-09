/**

  ******************************************************************************
  * @file    53l8a1_ranging_sensor.c
  * @author  IMG SW Application Team
  * @brief   This file includes the driver for Ranging Sensor modules mounted on
  *          X-NUCLEO 53L8A1 expansion board.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* File Info: ------------------------------------------------------------------
*                                   User NOTES

* Includes ------------------------------------------------------------------ */

#include "main.h"
#include "53l8a1_ranging_sensor.h"
#include "vl53l8cx.h"

/** @addtogroup BSP
  * @{
  */

/** @addtogroup XNUCLEO_53L8A1
  * @{
  */

/** @addtogroup XNUCLEO_53L8A1_RANGING_SENSOR
  * @{
  */

/** @defgroup XNUCLEO_53L8A1_RANGING_SENSOR_Exported_Variables Exported Variables
  * @{
  */
void *VL53L8A1_RANGING_SENSOR_CompObj[RANGING_SENSOR_INSTANCES_NBR] = {0};
/**
  * @}
  */

/** @defgroup XNUCLEO_53L8A1_RANGING_SENSOR_Private_Variables Private Variables
  * @{
  */
static RANGING_SENSOR_Drv_t *VL53L8A1_RANGING_SENSOR_Drv = NULL;
static RANGING_SENSOR_Capabilities_t VL53L8A1_RANGING_SENSOR_Cap;
/**
  * @}
  */

static int32_t VL53L8CX_Probe(uint32_t Instance);




int32_t VL53L8A1_RANGING_SENSOR_GetCapabilities(uint32_t Instance, RANGING_SENSOR_Capabilities_t *pCapabilities)
{
  int32_t ret;

  if (Instance >= RANGING_SENSOR_INSTANCES_NBR)
  {
    ret = BSP_ERROR_WRONG_PARAM;
  }
  else if (VL53L8A1_RANGING_SENSOR_Drv->GetCapabilities(VL53L8A1_RANGING_SENSOR_CompObj[Instance], pCapabilities) < 0)
  {

	  printf("Get Capability failed\n");
    ret = BSP_ERROR_COMPONENT_FAILURE;
  }
  else
  {

	  printf("Get Capability success\n");
    ret = BSP_ERROR_NONE;
  }

  return ret;
}


int32_t VL53L8A1_RANGING_SENSOR_Start(uint32_t Instance, uint32_t Mode)
{
  int32_t ret;

  if (Instance >= RANGING_SENSOR_INSTANCES_NBR)
  {
    ret = BSP_ERROR_WRONG_PARAM;
  }
  else if (VL53L8A1_RANGING_SENSOR_Drv->Start(VL53L8A1_RANGING_SENSOR_CompObj[Instance], Mode) < 0)
  {
	  printf("Start failed \n");
    ret = BSP_ERROR_COMPONENT_FAILURE;
  }
  else
  {

	  printf("Start success\n");
    ret = BSP_ERROR_NONE;
  }

  return ret;
}



int32_t VL53L8A1_RANGING_SENSOR_ConfigProfile(uint32_t Instance, RANGING_SENSOR_ProfileConfig_t *pConfig)
{
  int32_t ret;

  if (Instance >= RANGING_SENSOR_INSTANCES_NBR)
  {
    ret = BSP_ERROR_WRONG_PARAM;
  }
  else if (VL53L8A1_RANGING_SENSOR_Drv->ConfigProfile(VL53L8A1_RANGING_SENSOR_CompObj[Instance], pConfig) < 0)
  {

	  printf("ConfigProfile failed\n");
    ret = BSP_ERROR_COMPONENT_FAILURE;
  }
  else
  {

	  printf("Config Profile success\n");
    ret = BSP_ERROR_NONE;
  }
printf("ret = %d",ret);
  return ret;
}



int32_t VL53L8A1_RANGING_SENSOR_ReadID(uint32_t Instance, uint32_t *pId)
{
  int32_t ret;



  //void *VL53L8A1_RANGING_SENSOR_CompObj[RANGING_SENSOR_INSTANCES_NBR] = {0};

      // Debug print the pointer value for the sensor object
         printf("Inside the Process let see VL53L8A1_RANGING_SENSOR_CompObj[%u] = %p\n", VL53L8A1_DEV_CENTER, VL53L8A1_RANGING_SENSOR_CompObj[Instance]);



  if (Instance >= RANGING_SENSOR_INSTANCES_NBR)
  {
	  printf("To many instance\n");
    ret = BSP_ERROR_WRONG_PARAM;
  }
  else if (VL53L8A1_RANGING_SENSOR_Drv->ReadID(VL53L8A1_RANGING_SENSOR_CompObj[VL53L8A1_DEV_CENTER], pId) < 0)
  {
	  printf("ReadID fail\n");
    ret = BSP_ERROR_COMPONENT_FAILURE;
  }
  else
  {
	  printf("ReadID success\n");
    ret = BSP_ERROR_NONE;
  }

  return ret;
}



int32_t VL53L8A1_RANGING_SENSOR_Init(uint32_t Instance)
{
  int32_t ret;

  printf("are you stuck in  VL53L8A1_RANGING_SENSOR_Init\n");

  if (Instance >= RANGING_SENSOR_INSTANCES_NBR)
  {

	  printf("Prob failed\n");
    ret = BSP_ERROR_WRONG_PARAM;
  }
  else
  {
	  printf("Prob sucess\n");
    ret = VL53L8CX_Probe(Instance);
  }

  return ret;
}




/** @defgroup XNUCLEO_53L8A1_RANGING_SENSOR_Private_Functions Private Functions
  * @{
  */

/**
  * @brief Register Bus IOs if component ID is OK.
  * @param Instance    Ranging sensor instance.
  * @retval BSP status
  */
static int32_t VL53L8CX_Probe(uint32_t Instance)
{
  int32_t ret;
  VL53L8CX_IO_t              IOCtx;
  uint32_t                   id;
  static VL53L8CX_Object_t   VL53L8CXObj[RANGING_SENSOR_INSTANCES_NBR];

  /* Configure the ranging sensor driver */
  IOCtx.Address     = RANGING_SENSOR_VL53L8CX_ADDRESS;
  IOCtx.Init        = VL53L8A1_SPI_INIT;
  IOCtx.DeInit      = VL53L8A1_SPI_DEINIT;
  IOCtx.WriteReg    = VL53L8A1_SPI_WRITEREG;
  IOCtx.ReadReg     = VL53L8A1_SPI_READREG;
  IOCtx.GetTick     = VL53L8A1_GETTICK;


  printf("Hayaaaa\n");
  if (VL53L8CX_RegisterBusIO(&(VL53L8CXObj[Instance]), &IOCtx) != VL53L8CX_OK)
  {
    ret = BSP_ERROR_COMPONENT_FAILURE;
  }
  else
  {
    VL53L8A1_RANGING_SENSOR_Drv = (RANGING_SENSOR_Drv_t *) &VL53L8CX_RANGING_SENSOR_Driver;//This means that VL53L8A1_RANGING_SENSOR_Drv now points to the VL53L8CX_RANGING_SENSOR_Driver structure.
    VL53L8A1_RANGING_SENSOR_CompObj[Instance] = &(VL53L8CXObj[Instance]);

    // Debug print the pointer value for the sensor object
       printf("Probe: VL53L8A1_RANGING_SENSOR_CompObj[%u] = %p\n", Instance, VL53L8A1_RANGING_SENSOR_CompObj[Instance]);


    if (VL53L8CX_ReadID(&(VL53L8CXObj[Instance]), &id) != VL53L8CX_OK)
    {
    	printf("Not ssuccesfull communication\n");
      ret = BSP_ERROR_COMPONENT_FAILURE;
    }

  //  else {
    	//printf("Read Id succefull we have a communication congrats");
    //}
    else if (id != VL53L8CX_ID)
    {
    	printf("failed in id \n");
      ret = BSP_ERROR_UNKNOWN_COMPONENT;
    }
    else if (VL53L8A1_RANGING_SENSOR_Drv->Init(VL53L8A1_RANGING_SENSOR_CompObj[Instance]) != VL53L8CX_OK)
    {

    	printf("failed in init \n");
      ret = BSP_ERROR_COMPONENT_FAILURE;
    }
    else if (VL53L8A1_RANGING_SENSOR_Drv->GetCapabilities(VL53L8A1_RANGING_SENSOR_CompObj[Instance],
                                                          &VL53L8A1_RANGING_SENSOR_Cap) != VL53L8CX_OK)
    {

    	printf("failed in capabiluty \n");
      ret = BSP_ERROR_COMPONENT_FAILURE;
    }
    else
    {
printf("Id from the  intializing is ID: 0x%X\n", id);
    	  printf("return value after initialized is = %d\n",ret);
    	  printf("Read Id succefull we have a communication congrats\n");
    	  VL53L8CX_ReadID(&(VL53L8CXObj[Instance]), &id);
    	  printf("SEcond ID read in initializing dod it change? ID : 0x%X\n", id);
      ret = BSP_ERROR_NONE;
    }
  }

 // while(1);
  return ret;
  //}


}

int32_t VL53L8A1_RANGING_SENSOR_GetDistance(uint32_t Instance, RANGING_SENSOR_Result_t *pResult)
{
  int32_t ret=0;
printf("I am here\n");
  if (Instance >= RANGING_SENSOR_INSTANCES_NBR)
  {
	  printf("Wrong parameter for distance\n");
    ret = BSP_ERROR_WRONG_PARAM;
  }
  else if (VL53L8A1_RANGING_SENSOR_Drv->GetDistance(VL53L8A1_RANGING_SENSOR_CompObj[Instance], pResult) < 0)
  {

	  printf("Could not get distance \n");
    ret = BSP_ERROR_COMPONENT_FAILURE;
  }
  else
  {
	  printf("distnace is succefull bravo\n");
    ret = BSP_ERROR_NONE;
  }

  return ret;
}


int32_t VL53L8A1_RANGING_SENSOR_Stop(uint32_t Instance)
{
  int32_t ret;

  if (Instance >= RANGING_SENSOR_INSTANCES_NBR)
  {
    ret = BSP_ERROR_WRONG_PARAM;
  }
  else if (VL53L8A1_RANGING_SENSOR_Drv->Stop(VL53L8A1_RANGING_SENSOR_CompObj[Instance]) < 0)
  {
    ret = BSP_ERROR_COMPONENT_FAILURE;
  }
  else
  {
    ret = BSP_ERROR_NONE;
  }

  return ret;
}
