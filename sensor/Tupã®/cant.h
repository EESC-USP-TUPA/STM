/*
 * cant.h
 *
 *  Created on: Mar 29, 2025
 *      Author: pedro
 */

#ifndef CANT_H_
#define CANT_H_

#include <stdint.h>
#include "stm32f3xx_hal.h"
#include "terms.h"
#include "Contador.h"

extern CAN_HandleTypeDef hcan;

void canRPM();
void canTemp();
void binCode();

#endif /* CANT_H_ */
