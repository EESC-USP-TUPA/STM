/*
 * cant.h
 *
 *  Created on: Mar 27, 2025
 *      Author: pedro
 */

#ifndef CANT_H_
#define CANT_H_

#include <stdint.h>
#include "stm32f1xx_hal.h"
#include "gpio.h"

#include "protocolopartida.h"
#include "PWM.h"

extern CAN_HandleTypeDef hcan;
extern TIM_HandleTypeDef htim4;

extern uint16_t apps, bse, volante, erros, rpmR, rpmL;
extern uint8_t canFlag0;

extern uint8_t diferentialReady;

void can_enviar();

void can_init();

#endif /* CANT_H_ */
