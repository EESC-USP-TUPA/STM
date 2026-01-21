/*
 * PWM.c
 *
 *  Created on: Apr 10, 2025
 *      Author: pedro
 */

#include "PWM.h"

float pwmL, pwmR, pwmLfinal, pwmRfinal; //Variáveis que indicam o valor do pulso do PWM. Devem ir de 0 a 100, sendo 0 a saída de 0V e 100 5V.
uint16_t pwmMax = 523;  //output do controle em neutro e pedal 100%

void inversores_init() //Inicializa e reinicia os PWMs
{
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);
	TIM3->CCR1 = 0;
	TIM3->CCR2 = 0;
	TIM3->CCR3 = 0;
	TIM3->CCR4 = 0;
}
/* função oficial */

//void diferencial(){
//
//	if(stateError || !partidaFlag){
//		/* desligar inversores */
//		HAL_GPIO_WritePin(GPIOA, INVR_TRT_Pin, GPIO_PIN_RESET);
//		HAL_GPIO_WritePin(GPIOA, INVL_TRT_Pin, GPIO_PIN_RESET);
//		/*==================================================*/
//
//		TIM3->CCR1 = 0;
//		TIM3->CCR2 = 0;
//		return;
//	}
//	/* TRT SW: */
//	HAL_GPIO_WritePin(GPIOA, INVR_TRT_Pin, GPIO_PIN_SET);
//	HAL_GPIO_WritePin(GPIOA, INVL_TRT_Pin, GPIO_PIN_SET);
//	/*==================================================*/
//
//	float w, volanteCentral, ester_medio;
//
//	volanteCentral = ((float)volante/10.0f) - 90; //rxdata[2] vai de 0 a 1800, agr o "volante" vai de -90 a 90
//	w = (5000*2*PI/60)* ((float)apps/1000); //(rad/s)
//	ester_medio = volanteCentral * 39 *PI/(180*162);
//	float D = 1.25; // Comprimento entre as rodas traseiras (m)
//	float L = 1.55; // Comprimento entre eixos (m)
//
//	if (ester_medio > 0) {
//	   // Curva para direita
//		pwmL = w * (1 + D * tan(ester_medio) / (2 * L));
//		pwmR = w * (1 - D * tan(ester_medio) / (2 * L));
//	}
//	else if (ester_medio < 0) {
//	    // Curva para esquerda
//	    pwmL = w * (1 + D * tan(ester_medio) / (2 * L));
//	    pwmR = w * (1 - D * tan(ester_medio) / (2 * L));
//	}
//	else {
//	    // Caso de equilibrio zero
//	    pwmL = w;
//	    pwmR = w;
//	}
//
//	if(pwmR>pwmMax || pwmL>pwmMax){
//	    if(pwmR>pwmL){
//	      pwmR=pwmMax;
//	      pwmL=pwmR -2 * D * tan(ester_medio) / (2 * L) * w;
//	    }
//	    else
//	    {
//	      pwmL=pwmMax;
//	      pwmR=pwmL -2 * D * tan(ester_medio) / (2 * L) * w;
//	    }
//	  }
//
//	pwmLfinal = (pwmL*100*0.6/(float)pwmMax) +20;
//	pwmRfinal = (pwmR*100*0.6/(float)pwmMax) +20;
//
//	//PWM update:
//	TIM3->CCR1=(uint32_t)pwmLfinal;
//	TIM3->CCR2=(uint32_t)pwmRfinal;
//}

/* COM FREIO REGEN PRA TESTE: */

volatile uint8_t regenOK = 0;
void diferencial(){

	if(stateError || !partidaFlag){
		/* desligar inversores */
		HAL_GPIO_WritePin(GPIOA, INVR_TRT_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, INVL_TRT_Pin, GPIO_PIN_RESET);
		/*==================================================*/

		TIM3->CCR1 = 0;
		TIM3->CCR2 = 0;

		//TIM3->CCR3 = 0;
		//TIM3->CCR4 = 0;
		return;
	}
	/* TRT SW: */
	if (apps>0){
		HAL_GPIO_WritePin(GPIOA, INVR_TRT_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, INVL_TRT_Pin, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOA, INVR_BRK_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, INVL_BRK_Pin, GPIO_PIN_RESET);
		TIM3->CCR3 = 0;
		TIM3->CCR4 = 0;

		float w, volanteCentral, ester_medio;

		volanteCentral = ((float)volante/10.0f) - 90; //rxdata[2] vai de 0 a 1800, agr o "volante" vai de -90 a 90
		w = (5000*2*PI/60)* ((float)apps/1000); //(rad/s)
		ester_medio = volanteCentral * 39 *PI/(180*162);
		float D = 1.25; // Comprimento entre as rodas traseiras (m)
		float L = 1.55; // Comprimento entre eixos (m)

		if (ester_medio > 0) {
		   // Curva para direita
			pwmL = w * (1 + D * tan(ester_medio) / (2 * L));
			pwmR = w * (1 - D * tan(ester_medio) / (2 * L));
		}
		else if (ester_medio < 0) {
		    // Curva para esquerda
		    pwmL = w * (1 + D * tan(ester_medio) / (2 * L));
		    pwmR = w * (1 - D * tan(ester_medio) / (2 * L));
		}
		else {
		    // Caso de equilibrio zero
		    pwmL = w;
		    pwmR = w;
		}

		if(pwmR>pwmMax || pwmL>pwmMax){
		    if(pwmR>pwmL){
		      pwmR=pwmMax;
		      pwmL=pwmR -2 * D * tan(ester_medio) / (2 * L) * w;
		    }
		    else
		    {
		      pwmL=pwmMax;
		      pwmR=pwmL -2 * D * tan(ester_medio) / (2 * L) * w;
		    }
		  }

		pwmLfinal = (pwmL*100*0.6/(float)pwmMax) +20;
		pwmRfinal = (pwmR*100*0.6/(float)pwmMax) +20;

		//PWM update:
		TIM3->CCR1=(uint32_t)pwmLfinal;
		TIM3->CCR2=(uint32_t)pwmRfinal;
	}
	else{ //pedal < 0
		TIM3->CCR1 = 0;
		TIM3->CCR2 = 0;
		HAL_GPIO_WritePin(GPIOA, INVR_TRT_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, INVL_TRT_Pin, GPIO_PIN_RESET);

		//regen:
		if(regenOK){
			HAL_GPIO_WritePin(GPIOA, INVR_BRK_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOA, INVL_BRK_Pin, GPIO_PIN_SET);
			if(bse > 150){
				TIM3->CCR3 = 99;
				TIM3->CCR4 = 99;
			}

		}

	}

}
volatile uint32_t buzzerTimer;
void testeRegenInit(){
//	if(partidaFlag){
//		HAL_GPIO_WritePin(GPIOA, BUZZER_MCU_Pin, 1); //ativa o buzzer
//		__HAL_TIM_CLEAR_IT(&htim2, TIM_IT_UPDATE);
//		HAL_TIM_Base_Start_IT(&htim2);
//	}
	if(partidaFlag){
		regenOK++;
		if(HAL_GetTick()){
			buzzerTimer = HAL_GetTick();
			HAL_GPIO_WritePin(GPIOA, BUZZER_MCU_Pin, 1); //ativa o buzzer, user hall get tick pq tamo sem timer sobrando
		}

	}
}

void buzzerRegen(){
	if(buzzerTimer){
		if(HAL_GetTick() - buzzerTimer > 500){
			buzzerTimer = 0;
			HAL_GPIO_WritePin(GPIOA, BUZZER_MCU_Pin, 0);
		}
	}
}



/* CONTROLE THAYSON */

#define kp 0.179062253414369f
#define ki 1.52929144753969f
#define ts 0.01
#define rpmMAX 5000
#define maxVoltage 102 //tensao maxima do motor
#define L 1.25 // Comprimento entre as rodas traseiras (m)
#define D 1.55 // Comprimento entre eixos (m)

float u[2], wL, wR;

void diferencialMalhaFechada(){
	if (apps>0){
		HAL_GPIO_WritePin(GPIOA, INVR_TRT_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, INVL_TRT_Pin, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOA, INVR_BRK_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, INVL_BRK_Pin, GPIO_PIN_RESET);
		TIM3->CCR3 = 0;
		TIM3->CCR4 = 0;
	}
	else{ //pedal < 0
			TIM3->CCR1 = 0;
			TIM3->CCR2 = 0;
			HAL_GPIO_WritePin(GPIOA, INVR_TRT_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA, INVL_TRT_Pin, GPIO_PIN_RESET);

			//regen:
			if(regenOK){
				HAL_GPIO_WritePin(GPIOA, INVR_BRK_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOA, INVL_BRK_Pin, GPIO_PIN_SET);
				if(bse > 150){
					TIM3->CCR3 = 99;
					TIM3->CCR4 = 99;
				}

			}

		}

}

void ackerman(float* eL, float* eR){
	/* ERRO - DIFERENÇA ENTRE RPM REAL X RPM BARÇA */

	float w = rpmMAX * ((float)apps/1000); //RPM proporcional ao RPM max motor e APPS
	float angle = (((float)volante/10.0f) - 90) * 39 *PI/(180*162);

	wL = w * (1 + D * tan(angle) / (2 * L)); //rpm ideal motor esquerdo
	wR = w * (1 - D * tan(angle) / (2 * L)); //rpm ideal motor direito

	*eL = wL - rpmL;
	*eR = wR - rpmR;
}

void thayson(){
	//CONTROLE

	//indice 0 esquerda, 1 direita
	static float prev_u[2], prev_e[2]; //u[k-1] e e[k-1]
	float erro[2];
	ackerman(&erro[0], &erro[1]);

	for(uint8_t i = 0; i<2; i++){
		u[i] = prev_u[i] + ((kp + (ki * ts / 2.0f)) * erro[i]) + ((-kp + (ki * ts / 2.0f)) * prev_e[i]); //VOLT
		prev_u[i] = u[i];
		prev_e[i] = erro[i];
		if(u[i] > maxVoltage){ //pra saida em pwm capar em 99
			u[i] = maxVoltage;
		}
		else if (u[i] < 0){
			u[i] = 0;
		}
	}
	TIM3->CCR1 = (uint32_t)((u[0] / maxVoltage) * 99); //converte linearmente 0-102 pra 0-100
	TIM3->CCR2 = (uint32_t)((u[1] / maxVoltage) * 99);
}
