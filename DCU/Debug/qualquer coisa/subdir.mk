################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../qualquer\ coisa/qualquer.c 

OBJS += \
./qualquer\ coisa/qualquer.o 

C_DEPS += \
./qualquer\ coisa/qualquer.d 


# Each subdirectory must supply rules for building sources it contributes
qualquer\ coisa/qualquer.o: ../qualquer\ coisa/qualquer.c qualquer\ coisa/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/pedro/OneDrive/Ambiente de Trabalho/T09/DCU/Tupã®" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"qualquer coisa/qualquer.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-qualquer-20-coisa

clean-qualquer-20-coisa:
	-$(RM) ./qualquer\ coisa/qualquer.cyclo ./qualquer\ coisa/qualquer.d ./qualquer\ coisa/qualquer.o ./qualquer\ coisa/qualquer.su

.PHONY: clean-qualquer-20-coisa

