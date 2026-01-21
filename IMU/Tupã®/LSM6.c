/*
 * LSM6.c
 *
 *  Created on: Jul 28, 2025
 *      Author: Pedro
 */

//olá você do futuro, códigos i2c realmente não sao simples, muito endereço de registrador e configuração estranha

#include "LSM6.h"

volatile uint8_t lsmReady;

/* lsm6Data:
 * 0-2 = dados do gyro em dps
 * 3-5 = dados do acelerometro em m/s
 */
uint8_t lsm6Buffer[12];

// Sensibilidade para os modos padrão (FS = ±2g e FS = ±250 dps)
#define LSM6DSOX_ACC_SENSITIVITY_FS2G   0.061f  // mg/LSB
#define LSM6DSOX_GYRO_SENSITIVITY_FS250DPS 8.75f   // mdps/LSB
uint8_t ctrl_reg = 0x40; // 0100 0000b  p/ configuração do acelemerometro e gyro
uint8_t ctrl3_reg = 0x44; //0100 0100b 	p/ configurações gerais
//=====================================================================================//

uint8_t check;
uint8_t lsm6_Init(){
	if(HAL_I2C_Mem_Read(&hi2c2, lsm6_Adress, lsm6_who_i_am, I2C_MEMADD_SIZE_8BIT, &check, 1, 1000) == HAL_OK){
		if(check == 0x6c){ //valor esperado do lsm6

			/* 1. Configura o Acelerômetro (CTRL1_XL)
		    ODR = 104 Hz, FS = ±2g */
		    if (HAL_I2C_Mem_Write(&hi2c2, lsm6_Adress, LSM6DSOX_CTRL1_XL, I2C_MEMADD_SIZE_8BIT, &ctrl_reg, 1, 1000) != HAL_OK) {
		    	HAL_GPIO_WritePin(GPIOB, teste_led_Pin, 0);
		        return 0;
		    }
		    /* 2. Configura o Giroscópio (CTRL2_G)
		    ODR = 104 Hz, FS = ±250 dps */
		    if (HAL_I2C_Mem_Write(&hi2c2, lsm6_Adress, LSM6DSOX_CTRL2_G, I2C_MEMADD_SIZE_8BIT, &ctrl_reg, 1, 1000) != HAL_OK) {
		    	HAL_GPIO_WritePin(GPIOB, teste_led_Pin, 0);
		    	return 0;
		    }
		    /* 3. Configurações gerais (CTRL3_C)
		    Habilita BDU (Block Data Update) e IF_INC (auto-incremento de endereço)
		    BDU garante que os bytes de saída (L e H) pertençam à mesma amostra de dados.
		    F_INC é essencial para ler múltiplos registradores em uma única transação. */
		    if (HAL_I2C_Mem_Write(&hi2c2, lsm6_Adress, LSM6DSOX_CTRL3_C, I2C_MEMADD_SIZE_8BIT, &ctrl3_reg, 1, 1000) != HAL_OK) {
		    	HAL_GPIO_WritePin(GPIOB, teste_led_Pin, 0);
		    	return 0;
		    }

		    /* Se todas as configurações foram feitas com sucesso: */
			HAL_GPIO_WritePin(GPIOB, teste_led_Pin, 1);
			return 1;
		}
		HAL_GPIO_WritePin(GPIOB, teste_led_Pin, 0);
		return 0;
	}
	HAL_GPIO_WritePin(GPIOB, teste_led_Pin, 0);
	return 0;
}

void lsm6_Read(){
	/* 1. Buffer para receber os dados brutos via DMA.
	6 bytes para o giroscópio + 6 bytes para o acelerômetro = 12 bytes */

    /* 2. A leitura começa no registrador OUTX_L_G (0x22) e, graças ao auto-incremento,
     lê 12 bytes consecutivos, cobrindo todos os eixos do giroscópio e do acelerômetro. */

	//HAL_I2C_Mem_Read_DMA(&hi2c2, lsm6_Adress, LSM6DSOX_OUTX_L_G, I2C_MEMADD_SIZE_8BIT, lsm6Buffer, 12);
	//nao consegui por DMA
	HAL_I2C_Mem_Read(&hi2c2, lsm6_Adress, LSM6DSOX_OUTX_L_G, I2C_MEMADD_SIZE_8BIT, lsm6Buffer, 12, 100);

}

/* FUNÇÂO DE CONVERTER OS VALORES RAWs PRA ALGO FISICO DESABILITADA:
 * o micro nao precisa fazer essas contas no carro, é aconselhavel que apenas fazermos as leituras
 * cruas e a conversão no PC, a conta de conversão dos valores é essa da função
 * Você pode e deve habilitar ess função (descomentando) pra debugar a placa e atestar se o sensor
 * esta funcionando corretamente. Os resultados fisicos que você esta vendo no debug fazem sentido?
 * Se sim, seu sensor funciona parabens
 */

//volatile float lsm6Data[6];
//
//void lsm6_DataParsing(){
//	/* 3. DATA PARSING
//	 *Giroscópio: de LSB para dps (*sensibilidade e dividindo por 1000 pois a sensibilidade está em mdps/LSB)
//
//	 *Aceleração: de LSB para g (*sensibilidade e dividindo por 1000 pois a sensibilidade está em mg/LSB)
//      depois converte g para m/s multiplicando por 981 (o certo seria 9.81, mas 981 deixa
//      o valor inteiro pra CAN)
//	 */
//
//	volatile int16_t rawData;
//
//	for(uint8_t i = 0; i<3; i++){
//		rawData = (int16_t)((lsm6Buffer[2*i + 1] << 8) | lsm6Buffer[2*i]);
//		lsm6Data[i] = rawData*LSM6DSOX_GYRO_SENSITIVITY_FS250DPS/1000.0f;
//	}
//	for(uint8_t i = 3; i<6; i++){
//		rawData = ((lsm6Buffer[2*i + 1] << 8) | lsm6Buffer[2*i]);
//		lsm6Data[i] = rawData*LSM6DSOX_ACC_SENSITIVITY_FS2G*9.81/1000.0f;
//	}
//}
