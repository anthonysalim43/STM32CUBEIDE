################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/STM32G4xx_Nucleo/stm32g4xx_nucleo.c 

OBJS += \
./Drivers/BSP/STM32G4xx_Nucleo/stm32g4xx_nucleo.o 

C_DEPS += \
./Drivers/BSP/STM32G4xx_Nucleo/stm32g4xx_nucleo.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/STM32G4xx_Nucleo/%.o Drivers/BSP/STM32G4xx_Nucleo/%.su Drivers/BSP/STM32G4xx_Nucleo/%.cyclo: ../Drivers/BSP/STM32G4xx_Nucleo/%.c Drivers/BSP/STM32G4xx_Nucleo/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_NUCLEO_64 -DUSE_HAL_DRIVER -DSTM32G491xx -c -I../Core/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/BSP/STM32G4xx_Nucleo -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/AS000053/Desktop/Workspace_STM32/F401_53L8/SPI_Sandra/SPI_Sandra2/Core" -I"C:/Users/AS000053/Desktop/Workspace_STM32/F401_53L8/SPI_Sandra/SPI_Sandra2/Core/Inc" -I"C:/Users/AS000053/Desktop/Workspace_STM32/F401_53L8/SPI_Sandra/SPI_Sandra2/Core/Src" -I"C:/Users/AS000053/Desktop/Workspace_STM32/F401_53L8/SPI_Sandra/SPI_Sandra2/Core/Startup" -I"C:/Users/AS000053/Desktop/Workspace_STM32/F401_53L8/SPI_Sandra/SPI_Sandra2/Drivers/BSP/Components/VL53L8CX_ULD_API/inc" -I"C:/Users/AS000053/Desktop/Workspace_STM32/F401_53L8/SPI_Sandra/SPI_Sandra2/Drivers/BSP/Components/VL53L8CX_ULD_API/src" -I"C:/Users/AS000053/Desktop/Workspace_STM32/F401_53L8/SPI_Sandra/SPI_Sandra2/Drivers/BSP/Components/Common" -I"C:/Users/AS000053/Desktop/Workspace_STM32/F401_53L8/SPI_Sandra/SPI_Sandra2/TOF/Target" -I"C:/Users/AS000053/Desktop/Workspace_STM32/F401_53L8/SPI_Sandra/SPI_Sandra2/Drivers/BSP/Components/VL53L8CX_ULD_API" -I"C:/Users/AS000053/Desktop/Workspace_STM32/F401_53L8/SPI_Sandra/SPI_Sandra2/TOF/App" -I"C:/Users/AS000053/Desktop/Workspace_STM32/F401_53L8/SPI_Sandra/SPI_Sandra2/Drivers/BSP/53L8A1" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-STM32G4xx_Nucleo

clean-Drivers-2f-BSP-2f-STM32G4xx_Nucleo:
	-$(RM) ./Drivers/BSP/STM32G4xx_Nucleo/stm32g4xx_nucleo.cyclo ./Drivers/BSP/STM32G4xx_Nucleo/stm32g4xx_nucleo.d ./Drivers/BSP/STM32G4xx_Nucleo/stm32g4xx_nucleo.o ./Drivers/BSP/STM32G4xx_Nucleo/stm32g4xx_nucleo.su

.PHONY: clean-Drivers-2f-BSP-2f-STM32G4xx_Nucleo

