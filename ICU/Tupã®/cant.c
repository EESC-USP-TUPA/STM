/*
 * cant.c
 *
 *  Created on: Mar 27, 2025
 *      Author: pedro
 */

#include "cant.h"

uint8_t canFlag0;
uint16_t apps, bse, volante, erros, contagem, rpmR, rpmL;
uint8_t bFlag = 0;

uint8_t diferentialReady; //pra chamar o cntrole so quando chegar as 3 cans

uint8_t rxData[8];


void can_init(){

	HAL_CAN_Start(&hcan);

	/*  FIFO0 mensagens da DCU */
	HAL_CAN_ActivateNotification(&hcan, CAN_IT_RX_FIFO0_MSG_PENDING);
    CAN_FilterTypeDef can_filter;
    can_filter.FilterBank = 0;
    can_filter.FilterMode = CAN_FILTERMODE_IDLIST;
    can_filter.FilterScale = CAN_FILTERSCALE_32BIT;
    can_filter.FilterIdHigh = (0x080 << 5);
    can_filter.FilterIdLow = 0x0000;
    can_filter.FilterMaskIdHigh = 0x0000;
    can_filter.FilterMaskIdLow = 0x0000;
    can_filter.FilterFIFOAssignment = CAN_FILTER_FIFO0;
    can_filter.FilterActivation = ENABLE;
    HAL_CAN_ConfigFilter(&hcan, &can_filter);

    CAN_FilterTypeDef can_filter1;
    can_filter1.FilterBank = 1;
    can_filter1.FilterMode = CAN_FILTERMODE_IDLIST;
    can_filter1.FilterScale = CAN_FILTERSCALE_32BIT;
    can_filter1.FilterIdHigh = (0x0B0 << 5); //id do botao
    can_filter1.FilterIdLow = 0x0000;
    can_filter1.FilterMaskIdHigh = 0x0000; //mascara 0x080 a 0x08F, compara os 7 bits mais alto
    can_filter1.FilterMaskIdLow = 0x0000;
    can_filter1.FilterFIFOAssignment = CAN_FILTER_FIFO0;
    can_filter1.FilterActivation = ENABLE;
    HAL_CAN_ConfigFilter(&hcan, &can_filter1);


//    //FIFO1 - Mensagens da toradex
//	HAL_CAN_ActivateNotification(&hcan, CAN_IT_RX_FIFO1_MSG_PENDING);
//    CAN_FilterTypeDef can_filter;
//    can_filter.FilterBank = 0;
//    can_filter.FilterMode = CAN_FILTERMODE_IDLIST;
//    can_filter.FilterScale = CAN_FILTERSCALE_32BIT;
//    can_filter.FilterIdHigh = (0x100 << 5);
//    can_filter.FilterIdLow = 0x0000;
//    can_filter.FilterMaskIdHigh = 0x0000;
//    can_filter.FilterMaskIdLow = 0x0000;
//    can_filter.FilterFIFOAssignment = CAN_FILTER_FIFO0;
//    can_filter.FilterActivation = ENABLE;
//    HAL_CAN_ConfigFilter(&hcan, &can_filter);

}

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan){

	CAN_RxHeaderTypeDef rx_header;

	 if(HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &rx_header, rxData) == HAL_OK){

		 __HAL_TIM_SET_COUNTER(&htim4, 0); //reseta o timer de erro da can

		 switch (rx_header.StdId){

		 	 case 0x080:

		 		 apps = ((uint16_t)rxData[0] << 8) | rxData[1];
		 		 bse = ((uint16_t)rxData[2] << 8) | rxData[3];
		 		 volante = ((uint16_t)rxData[4] << 8) | rxData[5];
		 		 erros = rxData[6];
		 		 contagem = rxData[7];
		 		 diferentialReady |= 1 << 0;
		 		 if (!apps){
		 			diferentialReady = 0;
		 		 }

		 		 break;


		 	 case 0x0B0:

		 		 partida();
		 		 bFlag = 1;

		 		 testeRegenInit();

		 	 	 break;

		 	 case 0x585:

		 		 rpmR = ((uint16_t)rxData[0] << 8) | rxData[1];
		 		 diferentialReady |= 1 << 1;

		 		 break;

		 	 case 0x584:

		 		rpmL = ((uint16_t)rxData[0] << 8) | rxData[1];
		 		diferentialReady |= 1 << 2;

		 		break;

	    }
		 canFlag0 = 0;
		 HAL_GPIO_WritePin(GPIOA, TESTE_LED_Pin, 0);
	 }
	else{
		canFlag0 = 1;
	}
}

uint8_t canFlag1;
void can_enviar(){

	CAN_TxHeaderTypeDef txHeader;

	txHeader.StdId = 0x700;
	txHeader.IDE = CAN_ID_STD;
	txHeader.RTR = CAN_RTR_DATA;
	txHeader.DLC = 1;
	uint8_t txData[1];
	uint32_t txMailbox0;
	/*
	 * CAN IDEAL DE SE MANDAR SE A MALHA ESTIVER FUNFANDO
	 */
//
//
//	uint16_t wL_inteiro = (uint16_t)wL;
//	uint16_t wR_inteiro = (uint16_t)wR;
//	uint16_t u0_inteiro = (uint16_t)u[0];
//	uint16_t u1_inteiro = (uint16_t)u[1]; //isso parece meio redundante, mas dava erro e to com
//	//preguiça de pensar em outra solução menos feia
//
//
//	// Envia wL (RPM IDEAL Esquerdo)
//	txData[0] = (wL_inteiro >> 8) & 0xFF;
//	txData[1] = wL_inteiro & 0xFF;
//
//	// Envia wR (RPM IDEAL Direito)
//	txData[2] = (wR_inteiro >> 8) & 0xFF;
//	txData[3] = wR_inteiro & 0xFF;
//
//	// Envia u[0] (Tensão Esquerda)
//	txData[4] = (u0_inteiro >> 8) & 0xFF;
//	txData[5] = u0_inteiro & 0xFF;
//
//	// Envia u[1] (Tensão Direita)
//	txData[6] = (u1_inteiro >> 8) & 0xFF;
//	txData[7] = u1_inteiro & 0xFF;

	/*
	 * CAN que vou enviar so pra ver se pelo menos a malha entra em ação ;-;
	 */
	txData[0] = diferentialReady;

	if (HAL_CAN_AddTxMessage(&hcan, &txHeader, txData, &txMailbox0) != HAL_OK){
		canFlag1 = 1;
	}
	else{
		canFlag1 = 0;
	}
}
