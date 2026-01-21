/*
 * BPPC.c
 *
 *  Created on: Mar 27, 2025
 *      Author: pedro
 */

#include "BPPC.h"

uint8_t bppcError = 0, stateError = 0;

int BPPC(){

	if(appsReal > 250 && bseReal > 50){

		stateError = 1;
		bppcError = 1;
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, 1);
		return 1;
	}
	/* pós print o piloto deve soltar o pedal de aceleração para que saia do estado de erro*/
	else if (stateError && appsReal >


	50){

		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, 1);
		bppcError = 1;
		return 1;
	}

	/* sem erro, ou apps em repouso*/

	stateError = 0;
	bppcError = 0;
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, 0);
	return 0;

}

