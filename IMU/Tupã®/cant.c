/*
 * cant.c
 *
 *  Created on: Mar 27, 2025
 *      Author: pedro
 */

#include "cant.h"

uint8_t txDataG[7], txDataA[7], canFlag[2];

void can_enviar(){

	FDCAN_TxHeaderTypeDef txHeader;

	/*Mensagem 1
	 * CONTEÚDO:
	 * bit 0, 1: accel x
	 * bit 2, 3: accel y
	 * bit 4, 5: accel z
	 * bit 6: contagem
	 */

	txHeader.Identifier = 0x440;
	txHeader.IdType = FDCAN_STANDARD_ID;
	txHeader.TxFrameType = FDCAN_DATA_FRAME;
	txHeader.DataLength = FDCAN_DLC_BYTES_7;
	txHeader.ErrorStateIndicator = FDCAN_ESI_ACTIVE;
	txHeader.BitRateSwitch = FDCAN_BRS_OFF;
	txHeader.FDFormat = FDCAN_CLASSIC_CAN;
	txHeader.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
	txHeader.MessageMarker = 0;

	for(uint8_t i = 6; i<12; i++){
		txDataA[i - 6] = lsm6Buffer[i];
	}

	if (HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &txHeader, txDataA) != HAL_OK){
		canFlag[0] = 1;
		HAL_GPIO_WritePin(GPIOA, bat_led_Pin, 1);
	}
	else{
		canFlag[0] = 0;
		HAL_GPIO_TogglePin(GPIOA, bat_led_Pin);
	}
	txDataA[6]++;

	/*Mensagem 1
	 * CONTEÚDO:
	 * bit 0, 1: gyro x
	 * bit 2, 3: gyro y
	 * bit 4, 5: gyro z
	 * bit 6: contagem
	 */

	txHeader.Identifier = 0x450;
	txHeader.IdType = FDCAN_STANDARD_ID;
	txHeader.TxFrameType = FDCAN_DATA_FRAME;
	txHeader.DataLength = FDCAN_DLC_BYTES_7;
	txHeader.ErrorStateIndicator = FDCAN_ESI_ACTIVE;
	txHeader.BitRateSwitch = FDCAN_BRS_OFF;
	txHeader.FDFormat = FDCAN_CLASSIC_CAN;
	txHeader.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
	txHeader.MessageMarker = 0;

	for(uint8_t i = 0; i<6; i++){
		txDataG[i] = lsm6Buffer[i];
	}

	if (HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &txHeader, txDataA) != HAL_OK){
		canFlag[1] = 1;
	}
	else{
		canFlag[1] = 0;
	}
	txDataG[6]++;



}
