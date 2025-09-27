################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Lcd1602_i2c/Src/lcd1602_custom.c \
../Lcd1602_i2c/Src/lcd1602_i2c.c 

OBJS += \
./Lcd1602_i2c/Src/lcd1602_custom.o \
./Lcd1602_i2c/Src/lcd1602_i2c.o 

C_DEPS += \
./Lcd1602_i2c/Src/lcd1602_custom.d \
./Lcd1602_i2c/Src/lcd1602_i2c.d 


# Each subdirectory must supply rules for building sources it contributes
Lcd1602_i2c/Src/%.o Lcd1602_i2c/Src/%.su Lcd1602_i2c/Src/%.cyclo: ../Lcd1602_i2c/Src/%.c Lcd1602_i2c/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Commander/Inc -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Uart/Inc -I../Lcd1602_i2c/Inc -I../Lcd1602_i2c_tests/Inc -I../DelayMicro/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Lcd1602_i2c-2f-Src

clean-Lcd1602_i2c-2f-Src:
	-$(RM) ./Lcd1602_i2c/Src/lcd1602_custom.cyclo ./Lcd1602_i2c/Src/lcd1602_custom.d ./Lcd1602_i2c/Src/lcd1602_custom.o ./Lcd1602_i2c/Src/lcd1602_custom.su ./Lcd1602_i2c/Src/lcd1602_i2c.cyclo ./Lcd1602_i2c/Src/lcd1602_i2c.d ./Lcd1602_i2c/Src/lcd1602_i2c.o ./Lcd1602_i2c/Src/lcd1602_i2c.su

.PHONY: clean-Lcd1602_i2c-2f-Src

