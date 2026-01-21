/*
 * MPU6050.h
 *
 *  Created on: Apr 16, 2025
 *      Author: pedro
 */

#ifndef MPU6050_H_
#define MPU6050_H_

#include "stm32g4xx_hal.h"
#include <stdint.h>

extern float Ax, Ay, Az;
extern float Gx, Gy, Gz;

void MPU6050_Init();
void MPU6050_Ler_Acel();
void MPU6050_Ler_Gyro();

#endif /* MPU6050_H_ */
