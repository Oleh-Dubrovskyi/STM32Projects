################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Uart/Src/uart.c 

OBJS += \
./Uart/Src/uart.o 

C_DEPS += \
./Uart/Src/uart.d 


# Each subdirectory must supply rules for building sources it contributes
Uart/Src/%.o Uart/Src/%.su Uart/Src/%.cyclo: ../Uart/Src/%.c Uart/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Commander/Inc -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Uart/Inc -I../Lcd1602_i2c/Inc -I../Lcd1602_i2c_tests/Inc -I../DelayMicro/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Uart-2f-Src

clean-Uart-2f-Src:
	-$(RM) ./Uart/Src/uart.cyclo ./Uart/Src/uart.d ./Uart/Src/uart.o ./Uart/Src/uart.su

.PHONY: clean-Uart-2f-Src

