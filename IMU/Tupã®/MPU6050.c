/*
 * MPU6050.c
 *
 *  Created on: Apr 16, 2025
 *      Author: pedro
 */


#include "MPU6050.h"

extern I2C_HandleTypeDef hi2c2;

#define MPU6050_ADDR 0x68 << 1
#define SMPLRT_DIV_REG 0x19
#define GYRO_CONFIG_REG 0x1B
#define ACCEL_CONFIG_REG 0x1C
#define ACCEL_XOUT_H_REG 0x3B
#define TEMP_OUT_H_REG 0x41
#define GYRO_XOUT_H_REG 0x43
#define PWR_MGMT_1_REG 0x6B
#define WHO_AM_I_REG 0x75

/* acelerometro */
int16_t Accel_X_RAW, Accel_Y_RAW, Accel_Z_RAW;
float Ax, Ay, Az;

/* giroscopio*/
int16_t Gyro_X_RAW, Gyro_Y_RAW, Gyro_Z_RAW;
float Gx, Gy, Gz;
uint8_t check1;
void MPU6050_Init()
{

	uint8_t data;

	//ver se o mpu6050 está conectado com o who i am, o sensor deve responde-lo com 0x68 (104)

	HAL_I2C_Mem_Read (&hi2c2, MPU6050_ADDR,WHO_AM_I_REG,1, &check1, 1, 1000);
	if (check1 == 104){
		data = 0;
		//setar o pwr_mgmt_1 (power management) pro valor 0x00, assim vai "acordar" o sensor, esses valores são encontrados no register map and descriptions do mpu6050
		HAL_I2C_Mem_Write(&hi2c2, MPU6050_ADDR, PWR_MGMT_1_REG, 1, &data, 1, 1000);

		//setar a taxa de output data, pra uma sample rate de 1KHz o valor precisa ser 7, palavra chave pro mapa: sample rate divider
		data = 0x07;
		HAL_I2C_Mem_Write(&hi2c2, MPU6050_ADDR, SMPLRT_DIV_REG, 1, &data, 1, 1000);

		//definir a escala máxima tanto de acelerometro quanto do giroscopo, com o valor de 0x00
		data = 0x00;
		HAL_I2C_Mem_Write(&hi2c2, MPU6050_ADDR, ACCEL_CONFIG_REG, 1, &data, 1, 1000);
		//accel ±2g
		data = 0x00;
		HAL_I2C_Mem_Write(&hi2c2, MPU6050_ADDR, GYRO_CONFIG_REG, 1, &data, 1, 1000);
		//gyro ± 250 °/s
	}
}

//pra ler os dados do acelerometro precisamos ler 6 byts das accel out (0x3B), cada eixo vai possuir um valor de 16 bits
void MPU6050_Ler_Acel()
{
	uint8_t Rec_Data[6];
	//então é necessario combinar esses 6 byts em 3 eixos, cada um cm 16 bits

	//ACCEL_XOUT_H armazena os dados da aceleração no eixo X, e o ACCEL_XOUT_L armazena o "lower byte", essas duas variaveis compoe o eixo completo de 16 bits, então 16/2 = 8 (isso vale para todos os eixos)
		HAL_I2C_Mem_Read (&hi2c2, MPU6050_ADDR, ACCEL_XOUT_H_REG, 1, Rec_Data, 6, 1000);

	// as linhas abaixo possuem esse formato: "ACCEL_X = (ACCEL_XOUT_H << 8 | ACCEL_XOUT_L)"
		Accel_X_RAW = (int16_t)(Rec_Data[0] << 8 | Rec_Data [1]);
		Accel_Y_RAW = (int16_t)(Rec_Data[2] << 8 | Rec_Data [3]);
		Accel_Z_RAW = (int16_t)(Rec_Data[4] << 8 | Rec_Data [5]);

		Ax = (Accel_X_RAW/16384.0)*9.81;
		Ay = (Accel_Y_RAW/16384.0)*9.81;
		Az = (Accel_Z_RAW/16384.0)*9.81;
		/*agora é necessario converter os valores de raw em aceleração "g", pra fazer a conversão dessas valores vai depender do range definido anteriormente, no  caso 2g
		no mapa o 2g está associado a uma LBS sensitivity de 16384, então devemos dividir o valor por esse número: */
}

//giroscopo usa a exata mesma lógica
void MPU6050_Ler_Gyro()
{
	uint8_t Rec_Data[6];
	HAL_I2C_Mem_Read (&hi2c2, MPU6050_ADDR, GYRO_XOUT_H_REG, 1, Rec_Data, 6, 1000);
	Gyro_X_RAW = (int16_t)(Rec_Data[0] << 8 | Rec_Data [1]);
	Gyro_Y_RAW = (int16_t)(Rec_Data[2] << 8 | Rec_Data [3]);
	Gyro_Z_RAW = (int16_t)(Rec_Data[4] << 8 | Rec_Data [5]);

	Gx = Gyro_X_RAW/131.0;
	Gy = Gyro_Y_RAW/131.0;
	Gz = Gyro_Z_RAW/131.0;
}
