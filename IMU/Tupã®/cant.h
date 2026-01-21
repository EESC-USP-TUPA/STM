/*
 * cant.h
 *
 *  Created on: Mar 27, 2025
 *      Author: pedro
 */

#ifndef CANT_H_
#define CANT_H_

#include <stdint.h>
#include "stm32g4xx_hal.h"
#include "gpio.h"
#include "LSM6.h"

extern FDCAN_HandleTypeDef hfdcan1;

void can_enviar();

#endif /* CANT_H_ */
