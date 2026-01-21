################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Tupã®/PWM.c \
../Tupã®/cant.c \
../Tupã®/protocolopartida.c \
../Tupã®/shutdown.c 

OBJS += \
./Tupã®/PWM.o \
./Tupã®/cant.o \
./Tupã®/protocolopartida.o \
./Tupã®/shutdown.o 

C_DEPS += \
./Tupã®/PWM.d \
./Tupã®/cant.d \
./Tupã®/protocolopartida.d \
./Tupã®/shutdown.d 


# Each subdirectory must supply rules for building sources it contributes
Tupã®/%.o Tupã®/%.su Tupã®/%.cyclo: ../Tupã®/%.c Tupã®/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/pedro/OneDrive/Ambiente de Trabalho/T09/ICU/Tupã®" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Tup-e3--ae-

clean-Tup-e3--ae-:
	-$(RM) ./Tupã®/PWM.cyclo ./Tupã®/PWM.d ./Tupã®/PWM.o ./Tupã®/PWM.su ./Tupã®/cant.cyclo ./Tupã®/cant.d ./Tupã®/cant.o ./Tupã®/cant.su ./Tupã®/protocolopartida.cyclo ./Tupã®/protocolopartida.d ./Tupã®/protocolopartida.o ./Tupã®/protocolopartida.su ./Tupã®/shutdown.cyclo ./Tupã®/shutdown.d ./Tupã®/shutdown.o ./Tupã®/shutdown.su

.PHONY: clean-Tup-e3--ae-

