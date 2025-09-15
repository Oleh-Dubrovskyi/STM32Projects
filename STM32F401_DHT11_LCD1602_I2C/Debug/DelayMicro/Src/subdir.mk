################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../DelayMicro/Src/delay_micro.c 

OBJS += \
./DelayMicro/Src/delay_micro.o 

C_DEPS += \
./DelayMicro/Src/delay_micro.d 


# Each subdirectory must supply rules for building sources it contributes
DelayMicro/Src/%.o DelayMicro/Src/%.su DelayMicro/Src/%.cyclo: ../DelayMicro/Src/%.c DelayMicro/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../DelayMicro/Inc -I../Dh11/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Lcd1602_i2c/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-DelayMicro-2f-Src

clean-DelayMicro-2f-Src:
	-$(RM) ./DelayMicro/Src/delay_micro.cyclo ./DelayMicro/Src/delay_micro.d ./DelayMicro/Src/delay_micro.o ./DelayMicro/Src/delay_micro.su

.PHONY: clean-DelayMicro-2f-Src

