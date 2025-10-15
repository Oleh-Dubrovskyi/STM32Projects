################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Leds_control/Src/leds_control.c 

OBJS += \
./Leds_control/Src/leds_control.o 

C_DEPS += \
./Leds_control/Src/leds_control.d 


# Each subdirectory must supply rules for building sources it contributes
Leds_control/Src/%.o Leds_control/Src/%.su Leds_control/Src/%.cyclo: ../Leds_control/Src/%.c Leds_control/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../DelayMicro/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Hc_Sr04/Inc -I../Lcd1602_i2c/Inc -I../Leds_control/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Leds_control-2f-Src

clean-Leds_control-2f-Src:
	-$(RM) ./Leds_control/Src/leds_control.cyclo ./Leds_control/Src/leds_control.d ./Leds_control/Src/leds_control.o ./Leds_control/Src/leds_control.su

.PHONY: clean-Leds_control-2f-Src

