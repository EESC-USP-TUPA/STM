################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Tupã®/APPS.c \
../Tupã®/BPPC.c \
../Tupã®/BSE.c \
../Tupã®/Volante.c \
../Tupã®/botão.c \
../Tupã®/cant.c 

OBJS += \
./Tupã®/APPS.o \
./Tupã®/BPPC.o \
./Tupã®/BSE.o \
./Tupã®/Volante.o \
./Tupã®/botão.o \
./Tupã®/cant.o 

C_DEPS += \
./Tupã®/APPS.d \
./Tupã®/BPPC.d \
./Tupã®/BSE.d \
./Tupã®/Volante.d \
./Tupã®/botão.d \
./Tupã®/cant.d 


# Each subdirectory must supply rules for building sources it contributes
Tupã®/%.o Tupã®/%.su Tupã®/%.cyclo: ../Tupã®/%.c Tupã®/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/pedro/OneDrive/Ambiente de Trabalho/T09/DCU/Tupã®" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Tup-e3--ae-

clean-Tup-e3--ae-:
	-$(RM) ./Tupã®/APPS.cyclo ./Tupã®/APPS.d ./Tupã®/APPS.o ./Tupã®/APPS.su ./Tupã®/BPPC.cyclo ./Tupã®/BPPC.d ./Tupã®/BPPC.o ./Tupã®/BPPC.su ./Tupã®/BSE.cyclo ./Tupã®/BSE.d ./Tupã®/BSE.o ./Tupã®/BSE.su ./Tupã®/Volante.cyclo ./Tupã®/Volante.d ./Tupã®/Volante.o ./Tupã®/Volante.su ./Tupã®/botão.cyclo ./Tupã®/botão.d ./Tupã®/botão.o ./Tupã®/botão.su ./Tupã®/cant.cyclo ./Tupã®/cant.d ./Tupã®/cant.o ./Tupã®/cant.su

.PHONY: clean-Tup-e3--ae-

