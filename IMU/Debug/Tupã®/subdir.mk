################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Tupã®/LSM6.c \
../Tupã®/MPU6050.c \
../Tupã®/cant.c 

OBJS += \
./Tupã®/LSM6.o \
./Tupã®/MPU6050.o \
./Tupã®/cant.o 

C_DEPS += \
./Tupã®/LSM6.d \
./Tupã®/MPU6050.d \
./Tupã®/cant.d 


# Each subdirectory must supply rules for building sources it contributes
Tupã®/%.o Tupã®/%.su Tupã®/%.cyclo: ../Tupã®/%.c Tupã®/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G4A1xx -c -I../Core/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/pedro/OneDrive/Ambiente de Trabalho/T09/IMU/Tupã®" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Tup-e3--ae-

clean-Tup-e3--ae-:
	-$(RM) ./Tupã®/LSM6.cyclo ./Tupã®/LSM6.d ./Tupã®/LSM6.o ./Tupã®/LSM6.su ./Tupã®/MPU6050.cyclo ./Tupã®/MPU6050.d ./Tupã®/MPU6050.o ./Tupã®/MPU6050.su ./Tupã®/cant.cyclo ./Tupã®/cant.d ./Tupã®/cant.o ./Tupã®/cant.su

.PHONY: clean-Tup-e3--ae-

