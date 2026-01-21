/*
 * Volante.c
 *
 *  Created on: Mar 27, 2025
 *      Author: pedro
 */



#include "Volante.h"

/*Objetivo:
 * Só fazer uma média móvel simples pro dado do volante
 */

/* média móvel */
#define M 10 //numero de amostras

uint16_t mediavol[M];
int volRaw;
uint8_t firstReadVol = 0;

uint16_t volMin = 1940;
uint16_t volMax = 3500;

uint16_t volReal;




void mediavolante(){

	volatile uint16_t mediaSum1 = 0;
	volatile uint16_t volBuffer;

	if(!firstReadVol)
	{
		for(uint8_t i=0; i<M; i++)
		{
			mediavol[i] = adcRaw[4];

			mediaSum1 += mediavol[i];

		}
        volRaw = (uint16_t)((float)mediaSum1 / 10.0f);
		firstReadVol = 1;
	}

	else
	{
		for(uint8_t i=0; i< (M-1); i++) //move cada valor uma posição para trás no vetor
		{
			mediavol[i] = mediavol[i+1];

		}
		mediavol[M-1] = adcRaw[4]; //atualiza o ultimo espaço do vetor

		for(uint8_t i=0; i<M; i++)
		{
			mediaSum1 = mediaSum1 + mediavol[i];

		}
        volRaw = (int)((float)mediaSum1 / 10.0f);
	}

	volBuffer = (int)(((float)(volRaw - volMin)/(float)(volMax - volMin))*1800.0f);
	if(volBuffer>1800){
		volBuffer = 1800;
	}
	if(volBuffer<0){
		volBuffer = 0;
	}
	volReal = volBuffer;
}
