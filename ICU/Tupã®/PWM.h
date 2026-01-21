/*
 * PWM.h
 *
 *  Created on: Apr 10, 2025
 *      Author: pedro
 */

#ifndef PWM_H_
#define PWM_H_

#include "stm32f1xx_hal.h"
#include <stdint.h>
#include "cant.h"
#include "protocolopartida.h"
#include <math.h>

extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim2; //regen

void inversores_init();
void diferencial();

void testeRegenInit();
extern volatile uint8_t regenOK;


//thayson
void ackerman(float* eL, float* eR);
void thayson();
void diferencialMalhaFechada();
extern float u[2], wL, wR;

extern volatile uint32_t buzzerTimer;
void buzzerRegen();

#define PI M_PI

#endif /* PWM_H_ */
