/*
 * BSE.c
 *
 *  Created on: Mar 27, 2025
 *      Author: pedro
 */


#include "BSE.h"


/* Objetivos dessa lógica:
 * Verificar erros no BSE
 * fazer a média móvel para os valores de bse1 e bse2 raws
 * será enviado por can apenas os valores de: bse1Raw, bse2Raw, bseError
 * */

int bse1, bse2;
uint16_t bseReal;

/*======== ajustar ;-; ====*/
uint16_t bse1Min = 0;
uint16_t bse1Max = 4095;

uint16_t bse2Min = 350;
uint16_t bse2Max = 3000;
/*========================*/

/* erro: */
uint8_t bseError;

/* média móvel */
#define M 10 //numero de amostras

uint16_t mediabse1[M], mediabse2[M], bse1Raw, bse2Raw;
uint8_t firstReadBSE = 0;


/*
 * EDIT: erro de 10% nao é necessario.
 */

void BSE(){

	mediabse();

	//converte o adc de 0-4095 para 0-1000 para verificação de erro
	bse1 = (int)(((float)(bse1Raw - bse1Min)/(float)(bse1Max - bse1Min))*1000.0f);
	bse2 = (int)(((float)(bse2Raw - bse2Min)/(float)(bse2Max - bse2Min))*1000.0f);

	//erro curta com vcc ou gnd
	if(/*bse1Raw <= 0 || bse1Raw >= 4095  ||*/ bse2Raw <= 0 || bse2Raw >= 4095){

		bseError = 1;
		//bseErrorFlag = 0;
		bseReal = 0;
		appsReal = 0;
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);

	}

	// erro de 10%:
	//else if(fabs(bse1 - bse2) > 100){
	//	bse_Error_Counter();
	//}

	//sem erros
	else{
		if(bse2>1000){
			bse2 = 1000;
		}
		if(bse2<50){
			bse2 = 0;
		}
		//bseErrorFlag = 0;
		bseError = 0;
		bseReal = bse2;
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
	}

}

//void bse_Error_Counter(){
//
//	if (!bseErrorFlag) //se a flag for 0: (ou seja, primeira vez em 100ms que o erro foi detectado
//		{
//			bseErrorTime = HAL_GetTick();
//			bseErrorFlag = 1;
//		}
//		else //flag ja é 1, ou seja o erro esta acontecendo continuamente
//		{
//			if (HAL_GetTick() - bseErrorTime > 100) //verifica se o erro permaneceu por mais de 100ms
//			{
//				bseError = 1;
//				bseErrorFlag = 0;
//				bseReal = 0;
//				appsReal = 0;
//				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);
//			}
//		}
//}

void mediabse(){

	uint16_t mediaSum1 = 0;
	uint16_t mediaSum2 = 0;

	if(!firstReadBSE)
	{
		for(uint8_t i=0; i<M; i++)
		{
			mediabse1[i] = adcRaw[2];
			mediabse2[i] = adcRaw[3];

			mediaSum1 += mediabse1[i];
			mediaSum2 += mediabse2[i];
		}
        bse1Raw = (uint16_t)((float)mediaSum1 / 10.0f);
        bse2Raw = (uint16_t)((float)mediaSum2 / 10.0f);
		firstReadBSE = 1;
	}

	else
	{
		for(uint8_t i=0; i< (M-1); i++) //move cada valor uma posição para trás no vetor
		{
			mediabse1[i] = mediabse1[i+1];
			mediabse2[i] = mediabse2[i+1];
		}
		mediabse1[M-1] = adcRaw[2]; //atualiza o ultimo espaço do vetor
		mediabse2[M-1] = adcRaw[3];

		for(uint8_t i=0; i<M; i++)
		{
			mediaSum1 = mediaSum1 + mediabse1[i];
			mediaSum2 = mediaSum2 + mediabse2[i];
		}
        bse1Raw = (uint16_t)((float)mediaSum1 / 10.0f);
        bse2Raw = (uint16_t)((float)mediaSum2 / 10.0f);
	}
}
