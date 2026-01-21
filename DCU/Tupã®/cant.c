/*
 * cant.c
 *
 *  Created on: Mar 27, 2025
 *      Author: pedro
 */

/*
 * 0x080 = Mensagens com valores de apps, bse e volante já calculados
 * 0x090 = mensagem com apps1, e apps2, e erros cru
 * 0x091 = bse1, bse2 e volante cru
 */


#include "cant.h"

uint8_t txData0[8], txData1[6], txData2[7], txBotao[1], canFlag[3];
uint8_t count[3] = {0, 0, 0};



void can_enviar(){

	CAN_TxHeaderTypeDef txHeader;

	/*Mensagem 1
	 * CONTEÚDO:
	 * bit 0, 1: appsReal
	 * bit 2, 3: bseReal
	 * bit 4, 5: volReal
	 * bit 6: erros
	 * bit 7: contagem
	 */

	txHeader.StdId = 0x080;
	txHeader.IDE = CAN_ID_STD;
	txHeader.RTR = CAN_RTR_DATA;
	txHeader.DLC = 8;
	uint32_t txMailbox0;

	uint16_t data0[3] = {appsReal, bseReal, volReal};
	for(uint8_t i = 0; i < 3; i++){
		txData0[i*2] = (data0[i] >> 8) & 0xFF;
		txData0[i*2 + 1] = data0[i] & 0xFF;
	}

	uint8_t erros = 0;
	erros |= (appsError & 0x01) << 2;
	erros |= (bseError & 0x01) << 1;
	erros |= (bppcError & 0x01);

	txData0[6] = erros;

	txData0[7] = count[0];
	if (HAL_CAN_AddTxMessage(&hcan, &txHeader, txData0, &txMailbox0) != HAL_OK){
		canFlag[0] = 1;
	}
	else{
		canFlag[0] = 0;
	}
	count[0]++;

	/*Mensagem 2
	 * CONTEÚDO:
	 * bit 0, 1: apps1Raw
	 * bit 2, 3: apps2Raw
	 * bit 4: flags de erro
	 * bit 5: contagem de mensagem
	 */

	txHeader.StdId = 0x090;
	txHeader.IDE = CAN_ID_STD;
	txHeader.RTR = CAN_RTR_DATA;
	txHeader.DLC = 6;
	uint32_t txMailbox1;

	uint16_t data1[2] = {apps1Raw, apps2Raw};
	for (uint8_t i =0; i < 2; i++){
		txData1[i*2] = (data1[i] >> 8) & 0xFF;
		txData1[i*2 + 1] = data1[i] & 0xFF;
	}
	/*
	 * Junta os valores binários das 3 flags de erro em uma unica mensagem
	 * (ela será traduzida para decimal na can, depois é so desconverter)
	 */

	txData1[4]= erros;

	txData1[5] = count[1];

	if (HAL_CAN_AddTxMessage(&hcan, &txHeader, txData1, &txMailbox1) != HAL_OK){
		canFlag[1] = 1;
	}
	else{
		canFlag[1] = 0;
	}
	count[1]++;


	/*Mensagem 3
	 * CONTEÙDO:
	 * bit 0, 1: bse1Raw
	 * bit 2, 3: bse2Raw
	 * bit 4, 5: volRaw
	 * bit 6: contagem de mensagem
	 */
	txHeader.StdId = 0x091;
	txHeader.IDE = CAN_ID_STD;
	txHeader.RTR = CAN_RTR_DATA;
	txHeader.DLC = 7;
	uint32_t txMailbox2;

	uint16_t data2[3] = {bse1Raw, bse2Raw, volRaw};
	for(uint8_t i = 0; i < 3; i++){
		txData2[i*2] = (data2[i] >> 8) & 0xFF;
		txData2[i*2 + 1] = data2[i] & 0xFF;
	}
	txData2[6] = count[2];
	if (HAL_CAN_AddTxMessage(&hcan, &txHeader, txData2, &txMailbox2) != HAL_OK){
		canFlag[2] = 1;
	}
	else{
		canFlag[2] = 0;
	}
	count[2]++;

}



void can_botão(){
	CAN_TxHeaderTypeDef txHeader;

	txHeader.StdId = 0x0B0;
	txHeader.IDE = CAN_ID_STD;
	txHeader.RTR = CAN_RTR_DATA;
	txHeader.DLC = 1;
	uint32_t txMailbox;
	uint8_t botao[1] = {0};
	HAL_CAN_AddTxMessage(&hcan, &txHeader, botao, &txMailbox);
}
