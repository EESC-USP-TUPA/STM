/*
 * BSE.h
 *
 *  Created on: Mar 27, 2025
 *      Author: pedro
 */

#ifndef BSE_H_
#define BSE_H_

#include "stm32f1xx_hal.h" //hal get tick
#include <stdint.h> //unsigned int
#include <math.h>
#include "APPS.h"


//void BSE_ErrorVerify();
void BSE();
void mediabse();

extern uint16_t adcRaw[5];
extern uint16_t bse1Raw;
extern uint16_t bse2Raw;
extern uint8_t bseError;
extern uint16_t bseReal;


#endif /* BSE_H_ */
