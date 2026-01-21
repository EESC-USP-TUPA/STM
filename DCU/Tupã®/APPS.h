/*
 * APPS.h
 *
 *  Created on: Mar 26, 2025
 *      Author: pedro
 */

#ifndef APPS_H_
#define APPS_H_

#include "stm32f1xx_hal.h" //hal get tick
#include <stdint.h> //unsigned int
#include <math.h>

void APPS();
void apps_Error_Counter();
void mediaAPPS();

extern uint16_t adcRaw[5];
extern uint16_t apps1Raw;
extern uint16_t apps2Raw;
extern uint8_t appsError;
extern uint16_t appsReal;

#endif /* APPS_H_ */
