################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Dht/Src/Dht.c 

OBJS += \
./Dht/Src/Dht.o 

C_DEPS += \
./Dht/Src/Dht.d 


# Each subdirectory must supply rules for building sources it contributes
Dht/Src/%.o Dht/Src/%.su Dht/Src/%.cyclo: ../Dht/Src/%.c Dht/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../DelayMicro/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Lcd1602_i2c/Inc -I../Dht/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Dht-2f-Src

clean-Dht-2f-Src:
	-$(RM) ./Dht/Src/Dht.cyclo ./Dht/Src/Dht.d ./Dht/Src/Dht.o ./Dht/Src/Dht.su

.PHONY: clean-Dht-2f-Src

