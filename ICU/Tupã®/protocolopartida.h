/*
 * protocolopartida.h
 *
 *  Created on: Apr 4, 2025
 *      Author: rafael
 */

#ifndef INC_PROTOCOLOPARTIDA_H_
#define INC_PROTOCOLOPARTIDA_H_

#include <stdint.h>
#include "stm32f1xx_hal.h"
#include "gpio.h"

#include "cant.h"
#include "shutdown.h"

extern TIM_HandleTypeDef htim1;

extern uint8_t partidaFlag;

void blight();
void partida();

#endif /* INC_PROTOCOLOPARTIDA_H_ */
