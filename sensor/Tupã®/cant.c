/*
 * cant.c
 *
 *  Created on: Mar 29, 2025
 *      Author: pedro
 */


#include "cant.h"

uint8_t canFlagR, canFlagT, binarie, countRPM, countTemp, txData[3];


void canRPM(){
	CAN_TxHeaderTypeDef txHeader;
	//RPM e mlx pq n cabe na de temp

	//uint8_t txData[3];
	txHeader.StdId = 0x580+binarie;
	txHeader.IDE = CAN_ID_STD;
	txHeader.RTR = CAN_RTR_DATA;
	txHeader.DLC = 3;
	uint32_t txMailbox;

	//backs
	if(binarie == 0b100 || binarie == 0b101){
	txData[0] = (RPM[0] >> 8) & 0xFF;
	txData[1] = RPM[0] & 0xFF;
	}
	//fronts
	else if(binarie == 0b111 || binarie == 0b110){
	txData[0] = (RPM[1] >> 8) & 0xFF;
	txData[1] = RPM[1] & 0xFF;
	}

	if (HAL_CAN_AddTxMessage(&hcan, &txHeader, txData, &txMailbox) != HAL_OK){
		canFlagR = 1;
	}
	else{
		canFlagR = 0;
	}
	txData[2] = countRPM++;
}

void canTemp(){
	CAN_TxHeaderTypeDef txHeader;

	static uint8_t txData1[7];
	txHeader.StdId = 0x580+binarie+10;
	txHeader.IDE = CAN_ID_STD;
	txHeader.RTR = CAN_RTR_DATA;
	txHeader.DLC = 7;
	uint32_t txMailbox;

	for(uint8_t i = 0; i < 3; i++){
		txData1[i*2] = (adcRaw[i] >> 8) & 0xFF;
		txData1[i*2 + 1] = adcRaw[i] & 0xFF;
	}
	if (HAL_CAN_AddTxMessage(&hcan, &txHeader, txData1, &txMailbox) != HAL_OK){
		canFlagT = 1;
		}
	else{
		canFlagT = 0;
		}
	txData[6] = countTemp++;
}

void binCode(){
	binarie |= (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_7) & 0x01);
	binarie |= (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_8) & 0x01) << 1;
	binarie |= (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_9) & 0x01) << 2;
}
