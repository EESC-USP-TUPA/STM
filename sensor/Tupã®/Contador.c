/*
 * Contador.c
 *
 *  Created on: May 20, 2025
 *      Author: Guilherme Silva Módolo
 */
#include "contador.h"

// Variáveis globais
//volatile uint16_t currentCount1, currentCount2;
volatile uint16_t RPM[2];
volatile uint32_t icValue10, icValue20, difference0, icValue11, icValue21, difference1;;
volatile float pulseFreq0, pulseFreq1;
volatile uint8_t readyFlag, firstRead;

#define timerClockFreq  100000


// Handler de interrupção EXTI.
//void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
//    if(GPIO_Pin == GPIO_PIN_13) {
//        currentCount1++;
//    }
//    if(GPIO_Pin == GPIO_PIN_11){
//    	currentCount2++;
//    }
//
//}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim) {
	if(htim == &htim1){
		if(!firstRead){
			icValue10 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_2);
			icValue11 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_3);
			firstRead = 1;
		}
		else{
			icValue20 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_2);
			icValue21 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_3);
			if(icValue20 > icValue10){
				difference0 = icValue20 - icValue10;
			}
			else{
				difference0 = (htim->Instance->ARR - icValue10) + icValue20;
			}
			if(icValue21 > icValue11){
				difference1 = icValue21 - icValue11;
			}
			else{
				difference1 = (htim->Instance->ARR - icValue11) + icValue21;
			}
			icValue10 = icValue20;
			icValue11 = icValue21;
			readyFlag = 1;
			__HAL_TIM_SET_COUNTER(&htim4, 0); //reseta o timer de erro da can pra zerar rpm
		}

	}

}

void calcularRPM(){

	if(difference0 > 0){
		pulseFreq0 = timerClockFreq / difference0;
	}
	if(difference1 > 0){
		pulseFreq1 = timerClockFreq / difference1;
	}
	RPM[0] = (uint16_t)((pulseFreq0 / 4.0) * 60); //mtr
	RPM[1] = (uint16_t)((pulseFreq1 / 8.0) * 60); //roda
	readyFlag = 0;
}


//    RPM[0] = round((currentCount1 / 8.0) * 60);
//    currentCount1 = 0;
//
//    RPM[1] = round((currentCount2 / 4.0)*60);
//    currentCount2 = 0;
