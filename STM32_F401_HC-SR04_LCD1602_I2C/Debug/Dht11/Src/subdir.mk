################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Dht11/Src/Dth11.c 

OBJS += \
./Dht11/Src/Dth11.o 

C_DEPS += \
./Dht11/Src/Dth11.d 


# Each subdirectory must supply rules for building sources it contributes
Dht11/Src/%.o Dht11/Src/%.su Dht11/Src/%.cyclo: ../Dht11/Src/%.c Dht11/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../DelayMicro/Inc -I../Dh11/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Lcd1602_i2c/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Dht11-2f-Src

clean-Dht11-2f-Src:
	-$(RM) ./Dht11/Src/Dth11.cyclo ./Dht11/Src/Dth11.d ./Dht11/Src/Dth11.o ./Dht11/Src/Dth11.su

.PHONY: clean-Dht11-2f-Src

