################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Tupã®/Contador.c \
../Tupã®/cant.c \
../Tupã®/terms.c 

OBJS += \
./Tupã®/Contador.o \
./Tupã®/cant.o \
./Tupã®/terms.o 

C_DEPS += \
./Tupã®/Contador.d \
./Tupã®/cant.d \
./Tupã®/terms.d 


# Each subdirectory must supply rules for building sources it contributes
Tupã®/%.o Tupã®/%.su Tupã®/%.cyclo: ../Tupã®/%.c Tupã®/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F303xC -c -I../Core/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/pedro/OneDrive/Ambiente de Trabalho/T09/sensor/Tupã®" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Tup-e3--ae-

clean-Tup-e3--ae-:
	-$(RM) ./Tupã®/Contador.cyclo ./Tupã®/Contador.d ./Tupã®/Contador.o ./Tupã®/Contador.su ./Tupã®/cant.cyclo ./Tupã®/cant.d ./Tupã®/cant.o ./Tupã®/cant.su ./Tupã®/terms.cyclo ./Tupã®/terms.d ./Tupã®/terms.o ./Tupã®/terms.su

.PHONY: clean-Tup-e3--ae-

