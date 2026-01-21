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

#include "APPS.h"
#include "BSE.h"
#include "BPPC.h"
#include "Volante.h"

extern CAN_HandleTypeDef hcan;
extern TIM_HandleTypeDef htim1;

void can_enviar();
void can_botão();

#endif /* CANT_H_ */
