/*
 * protocolopartida.c
 *
 *  Created on: Apr 4, 2025
 *      Author: rafael
 */

#include "protocolopartida.h"



uint8_t partidaFlag;

void blight()
{
	if(bse > 50)
	{
		HAL_GPIO_WritePin(GPIOA,  BRAKELIGHT_MCU_Pin, 1);
	}
	else
	{
		HAL_GPIO_WritePin(GPIOA, BRAKELIGHT_MCU_Pin, 0);
	}
}

void partida()
{
	if(!partidaFlag && bse > 50 && !stateError)
	{

		HAL_GPIO_WritePin(GPIOA, BUZZER_MCU_Pin, 1); //ativa o buzzer

		__HAL_TIM_CLEAR_IT(&htim1, TIM_IT_UPDATE); //reseta A FLAG, pra ele n triggar a IT quando acordar
		HAL_TIM_Base_Start_IT(&htim1); //inicia o timer/cronometro de 3s

	}
}
