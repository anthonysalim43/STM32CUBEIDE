################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/Components/vl53l8cx/modules/vl53l8cx_api.c \
../Drivers/BSP/Components/vl53l8cx/modules/vl53l8cx_plugin_detection_thresholds.c \
../Drivers/BSP/Components/vl53l8cx/modules/vl53l8cx_plugin_motion_indicator.c \
../Drivers/BSP/Components/vl53l8cx/modules/vl53l8cx_plugin_xtalk.c 

OBJS += \
./Drivers/BSP/Components/vl53l8cx/modules/vl53l8cx_api.o \
./Drivers/BSP/Components/vl53l8cx/modules/vl53l8cx_plugin_detection_thresholds.o \
./Drivers/BSP/Components/vl53l8cx/modules/vl53l8cx_plugin_motion_indicator.o \
./Drivers/BSP/Components/vl53l8cx/modules/vl53l8cx_plugin_xtalk.o 

C_DEPS += \
./Drivers/BSP/Components/vl53l8cx/modules/vl53l8cx_api.d \
./Drivers/BSP/Components/vl53l8cx/modules/vl53l8cx_plugin_detection_thresholds.d \
./Drivers/BSP/Components/vl53l8cx/modules/vl53l8cx_plugin_motion_indicator.d \
./Drivers/BSP/Components/vl53l8cx/modules/vl53l8cx_plugin_xtalk.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/Components/vl53l8cx/modules/%.o Drivers/BSP/Components/vl53l8cx/modules/%.su Drivers/BSP/Components/vl53l8cx/modules/%.cyclo: ../Drivers/BSP/Components/vl53l8cx/modules/%.c Drivers/BSP/Components/vl53l8cx/modules/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_NUCLEO_64 -DUSE_HAL_DRIVER -DSTM32G491xx -c -I../Core/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/BSP/STM32G4xx_Nucleo -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -I../TOF/App -I../TOF/Target -I../Drivers/BSP/Components/Common -I../Drivers/BSP/53L8A1 -I../Drivers/BSP/Components/vl53l8cx/modules -I../Drivers/BSP/Components/vl53l8cx/porting -I../Drivers/BSP/Components/vl53l8cx -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-Components-2f-vl53l8cx-2f-modules

clean-Drivers-2f-BSP-2f-Components-2f-vl53l8cx-2f-modules:
	-$(RM) ./Drivers/BSP/Components/vl53l8cx/modules/vl53l8cx_api.cyclo ./Drivers/BSP/Components/vl53l8cx/modules/vl53l8cx_api.d ./Drivers/BSP/Components/vl53l8cx/modules/vl53l8cx_api.o ./Drivers/BSP/Components/vl53l8cx/modules/vl53l8cx_api.su ./Drivers/BSP/Components/vl53l8cx/modules/vl53l8cx_plugin_detection_thresholds.cyclo ./Drivers/BSP/Components/vl53l8cx/modules/vl53l8cx_plugin_detection_thresholds.d ./Drivers/BSP/Components/vl53l8cx/modules/vl53l8cx_plugin_detection_thresholds.o ./Drivers/BSP/Components/vl53l8cx/modules/vl53l8cx_plugin_detection_thresholds.su ./Drivers/BSP/Components/vl53l8cx/modules/vl53l8cx_plugin_motion_indicator.cyclo ./Drivers/BSP/Components/vl53l8cx/modules/vl53l8cx_plugin_motion_indicator.d ./Drivers/BSP/Components/vl53l8cx/modules/vl53l8cx_plugin_motion_indicator.o ./Drivers/BSP/Components/vl53l8cx/modules/vl53l8cx_plugin_motion_indicator.su ./Drivers/BSP/Components/vl53l8cx/modules/vl53l8cx_plugin_xtalk.cyclo ./Drivers/BSP/Components/vl53l8cx/modules/vl53l8cx_plugin_xtalk.d ./Drivers/BSP/Components/vl53l8cx/modules/vl53l8cx_plugin_xtalk.o ./Drivers/BSP/Components/vl53l8cx/modules/vl53l8cx_plugin_xtalk.su

.PHONY: clean-Drivers-2f-BSP-2f-Components-2f-vl53l8cx-2f-modules

