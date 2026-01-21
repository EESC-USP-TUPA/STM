/*
 * botão.c
 *
 *  Created on: Apr 10, 2025
 *      Author: pedro
 */

#include "stm32f1xx_hal.h"
#include "cant.h"
#include "BSE.h"

extern TIM_HandleTypeDef htim3;
uint8_t exti8Flag;


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {


	if (GPIO_Pin == GPIO_PIN_8 && bseReal > 50) {

		can_botão();

		/*desliga a interrupção no pino PA8 pra evitar multiplas interrupções dentro de 0.5s:
		 * isso salva do efeito de bouncing, lógica bem foda, so genial*/

		EXTI->IMR &= ~EXTI_IMR_IM8; //desliga as interrupções da linha EXTI8

		__HAL_TIM_CLEAR_IT(&htim3, TIM_IT_UPDATE);
		HAL_TIM_Base_Start_IT(&htim3); //0.5s

		exti8Flag++; //so pra ver em debug

	}

}

/*literal esse arquivo so serve pra enviar uma can quando apertarem o botão*/
