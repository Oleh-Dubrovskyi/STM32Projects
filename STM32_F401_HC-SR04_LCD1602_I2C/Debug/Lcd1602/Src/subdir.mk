################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Lcd1602/Src/lcd1602.c 

OBJS += \
./Lcd1602/Src/lcd1602.o 

C_DEPS += \
./Lcd1602/Src/lcd1602.d 


# Each subdirectory must supply rules for building sources it contributes
Lcd1602/Src/%.o Lcd1602/Src/%.su Lcd1602/Src/%.cyclo: ../Lcd1602/Src/%.c Lcd1602/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Lcd1602/Inc -I../DelayMicro/Inc -I../Dh11/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Lcd1602-2f-Src

clean-Lcd1602-2f-Src:
	-$(RM) ./Lcd1602/Src/lcd1602.cyclo ./Lcd1602/Src/lcd1602.d ./Lcd1602/Src/lcd1602.o ./Lcd1602/Src/lcd1602.su

.PHONY: clean-Lcd1602-2f-Src

