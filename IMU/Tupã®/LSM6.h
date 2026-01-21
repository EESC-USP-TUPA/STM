/*
 * LSM6.h
 *
 *  Created on: Jul 28, 2025
 *      Author: pedro
 */

#ifndef LSM6_H_
#define LSM6_H_

#include "stm32g4xx_hal.h"
#include <stdint.h>
#include "gpio.h"

extern I2C_HandleTypeDef hi2c2;

//registradores:
#define lsm6_Adress  (0x6A << 1) //endereço i2c
#define lsm6_who_i_am 0x0F
#define LSM6DSOX_CTRL1_XL 0x10 // Controle do Acelerômetro
#define LSM6DSOX_CTRL2_G 0x11 //controle giroscopio
#define LSM6DSOX_CTRL3_C 0x12 // Controle geral (BDU, IF_INC, etc)

#define LSM6DSOX_OUTX_L_G 0x22 // Saída do Giroscópio
#define LSM6DSOX_OUTX_L_A 0x28 // Saída do Acelerômetro

uint8_t lsm6_Init();
void lsm6_Read();

volatile extern uint8_t lsmReady;
extern uint8_t lsm6Buffer[12];

//void lsm6_DataParsing();
//extern volatile float lsm6Data[6];

#endif /* LSM6_H_ */
