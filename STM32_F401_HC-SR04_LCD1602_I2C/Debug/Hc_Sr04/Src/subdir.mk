################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Hc_Sr04/Src/hc_sr04.c 

OBJS += \
./Hc_Sr04/Src/hc_sr04.o 

C_DEPS += \
./Hc_Sr04/Src/hc_sr04.d 


# Each subdirectory must supply rules for building sources it contributes
Hc_Sr04/Src/%.o Hc_Sr04/Src/%.su Hc_Sr04/Src/%.cyclo: ../Hc_Sr04/Src/%.c Hc_Sr04/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../DelayMicro/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Hc_Sr04/Inc -I../Lcd1602_i2c/Inc -I../Leds_control/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Hc_Sr04-2f-Src

clean-Hc_Sr04-2f-Src:
	-$(RM) ./Hc_Sr04/Src/hc_sr04.cyclo ./Hc_Sr04/Src/hc_sr04.d ./Hc_Sr04/Src/hc_sr04.o ./Hc_Sr04/Src/hc_sr04.su

.PHONY: clean-Hc_Sr04-2f-Src

