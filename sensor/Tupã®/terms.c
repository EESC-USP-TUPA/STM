/*
 * terms.c
 *
 *  Created on: Apr 6, 2025
 *      Author: pedro
 */


#include "terms.h"

uint16_t adcRaw[3];

/* SALVAR DADOS APENAS CRU E CONVERTER DPS */

/* Parametros para o calculo */

//uint16_t R0 = 10000; //Resistor série - 10k
//float T0 = 298.15; //25° em kelvin (R_NTC deve estar em 10k nessa temperatura)
//uint16_t B = 3380; //Coeficiente Beta dos termistors
//uint8_t V = 5; //Tensão de alimentação
///*=============================*/
//
//float tempC[3]; //temperatura final em celsius
//
//void tempConverter(){
//
//	/* Equação de Steinhart-Hart */
//
//	float pin_v, R_NTC, tempK;
//
//	for(uint8_t i=0; i<3; i++){
//
//		pin_v = adcRaw[i]*(3.3/4095);
//		R_NTC = ((V - pin_v)*R0);
//		tempK = (T0*B)/(B + log(R_NTC/R0)*T0);
//		tempC[i] = tempK - 275.15;
//	}
//}
