/*
 * Contador.h
 *
 *  Created on: May 20, 2025
 *      Author: Guilherme Silva Módolo
 */
#ifndef INC_CONTADOR_H_
#define INC_CONTADOR_H_
#include <stdint.h>
#include "stm32f3xx_hal.h"
#include "math.h"

extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim1;

extern volatile uint16_t RPM[2];
extern volatile uint8_t readyFlag;

void calcularRPM();

#endif /* INC_CONTADOR_H_ */
