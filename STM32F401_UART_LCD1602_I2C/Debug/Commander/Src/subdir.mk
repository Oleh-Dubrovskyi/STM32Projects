################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Commander/Src/commander.c 

OBJS += \
./Commander/Src/commander.o 

C_DEPS += \
./Commander/Src/commander.d 


# Each subdirectory must supply rules for building sources it contributes
Commander/Src/%.o Commander/Src/%.su Commander/Src/%.cyclo: ../Commander/Src/%.c Commander/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Commander/Inc -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Uart/Inc -I../Lcd1602_i2c/Inc -I../Lcd1602_i2c_tests/Inc -I../DelayMicro/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Commander-2f-Src

clean-Commander-2f-Src:
	-$(RM) ./Commander/Src/commander.cyclo ./Commander/Src/commander.d ./Commander/Src/commander.o ./Commander/Src/commander.su

.PHONY: clean-Commander-2f-Src

