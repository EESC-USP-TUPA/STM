/*
 * Volante.h
 *
 *  Created on: Mar 27, 2025
 *      Author: pedro
 */

#ifndef VOLANTE_H_
#define VOLANTE_H_

#include <stdint.h>

void mediavolante();

extern uint16_t adcRaw[5];
extern int volRaw;
extern uint16_t volReal;

#endif /* VOLANTE_H_ */
