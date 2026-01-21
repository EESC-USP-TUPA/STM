/*
 * APPS.c
 *
 *  Created on: Mar 26, 2025
 *      Author: pedro
 */

#include "APPS.h"


/* Objetivos dessa lógica:
 * Verificar erros no APPS
 * fazer a média móvel para os valores de apps1 e apps2 raws
 * será enviado por can apenas os valores de: apps1Raw, apps2Raw, APPS_Error
 * */

int APPS1, APPS2;
uint16_t appsReal;

/*======== ajustar ;-; ====*/
uint16_t apps1Min = 400;
uint16_t apps1Max = 1500;

uint16_t apps2Min = 150;
uint16_t apps2Max = 660;
/*========================*/

/* erro: */
uint8_t appsErrorFlag, appsError, appsErrorTime;

/* média móvel */
#define M 10 //numero de amostras

uint16_t mediaApps1[M], mediaApps2[M], apps1Raw, apps2Raw;
uint8_t firstRead = 0;


void APPS(){

	mediaAPPS();

	//converte o adc de 0-4095 para 0-1000 para verificação de erro
	APPS1 = (int)(((float)(apps1Raw - apps1Min)/(float)(apps1Max - apps1Min))*1000.0f);
	APPS2 = (int)(((float)(apps2Raw - apps2Min)/(float)(apps2Max - apps2Min))*1000.0f);

	//erro curta com vcc ou gnd
	if(apps1Raw <= 0 || apps1Raw >= 4095 || apps2Raw <= 0 || apps2Raw >= 4095){

		appsError = 1;
		appsErrorFlag = 0;
		appsReal = 0;
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_SET);

	}

	// erro de 10%:
	else if(fabs(APPS1 - APPS2) > 100){
		apps_Error_Counter();
	}

	//sem erros
	else{
		if(APPS1>1000){
			APPS1 = 1000;
		}
		if(APPS1<25){
			APPS1 = 0;
		}
		appsErrorFlag = 0;
		appsError = 0;
		appsReal = APPS1;
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_RESET);
	}

}

void apps_Error_Counter(){

	if (!appsErrorFlag) //se a flag for 0: (ou seja, primeira vez em 100ms que o erro foi detectado
		{
			appsErrorTime = HAL_GetTick();
			appsErrorFlag = 1;
		}
		else //flag ja é 1, ou seja o erro esta acontecendo continuamente
		{
			if (HAL_GetTick() - appsErrorTime > 100) //verifica se o erro permaneceu por mais de 100ms
			{
				appsError = 1;
				appsErrorFlag = 0;
				appsReal = 0;
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_SET);
			}
		}
}

void mediaAPPS(){

	uint16_t mediaSum1 = 0;
	uint16_t mediaSum2 = 0;

	if(!firstRead)
	{
		for(uint8_t i=0; i<M; i++)
		{
			mediaApps1[i] = adcRaw[0];
			mediaApps2[i] = adcRaw[1];

			mediaSum1 += mediaApps1[i];
			mediaSum2 += mediaApps2[i];
		}
        apps1Raw = (uint16_t)((float)mediaSum1 / 10.0f);
        apps2Raw = (uint16_t)((float)mediaSum2 / 10.0f);
		firstRead = 1;
	}

	else
	{
		for(uint8_t i=0; i< (M-1); i++) //move cada valor uma posição para trás no vetor
		{
			mediaApps1[i] = mediaApps1[i+1];
			mediaApps2[i] = mediaApps2[i+1];
		}
		mediaApps1[M-1] = adcRaw[0]; //atualiza o ultimo espaço do vetor
		mediaApps2[M-1] = adcRaw[1];

		for(uint8_t i=0; i<M; i++)
		{
			mediaSum1 = mediaSum1 + mediaApps1[i];
			mediaSum2 = mediaSum2 + mediaApps2[i];
		}
        apps1Raw = (uint16_t)((float)mediaSum1 / 10.0f);
        apps2Raw = (uint16_t)((float)mediaSum2 / 10.0f);
	}
}
