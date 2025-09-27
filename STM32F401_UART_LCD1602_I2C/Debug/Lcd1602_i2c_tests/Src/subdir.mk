################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Lcd1602_i2c_tests/Src/lcd1602_i2c_tests.c 

OBJS += \
./Lcd1602_i2c_tests/Src/lcd1602_i2c_tests.o 

C_DEPS += \
./Lcd1602_i2c_tests/Src/lcd1602_i2c_tests.d 


# Each subdirectory must supply rules for building sources it contributes
Lcd1602_i2c_tests/Src/%.o Lcd1602_i2c_tests/Src/%.su Lcd1602_i2c_tests/Src/%.cyclo: ../Lcd1602_i2c_tests/Src/%.c Lcd1602_i2c_tests/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Commander/Inc -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Uart/Inc -I../Lcd1602_i2c/Inc -I../Lcd1602_i2c_tests/Inc -I../DelayMicro/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Lcd1602_i2c_tests-2f-Src

clean-Lcd1602_i2c_tests-2f-Src:
	-$(RM) ./Lcd1602_i2c_tests/Src/lcd1602_i2c_tests.cyclo ./Lcd1602_i2c_tests/Src/lcd1602_i2c_tests.d ./Lcd1602_i2c_tests/Src/lcd1602_i2c_tests.o ./Lcd1602_i2c_tests/Src/lcd1602_i2c_tests.su

.PHONY: clean-Lcd1602_i2c_tests-2f-Src

