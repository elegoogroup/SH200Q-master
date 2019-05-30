#include "i2c.h"
#include "sh200q.h"

#define SH200Q_ADDRESS 0x6C //7bit i2c address 
#define SH200Q_WHOAMI 0x30
#define SH200Q_ACC_CONFIG 0x0E
#define SH200Q_GYRO_CONFIG 0x0F
#define SH200Q_GYRO_DLPF 0x11
#define SH200Q_FIFO_CONFIG 0x12
#define SH200Q_ACC_RANGE 0x16
#define SH200Q_GYRO_RANGE 0x2B
#define SH200Q_OUTPUT_ACC_X 0x00
#define SH200Q_OUTPUT_GYRO_X 0x06
#define SH200Q_OUTPUT_TEMP 0x0C
#define SH200Q_RESET 0x75

//i2c读写函数说明：
//读函数
//I2C_Read_NBytes(uint8_t driver_Addr, uint8_t start_Addr, uint8_t number_Bytes, uint8_t *read_Buffer)
///**
//  * @brief  I2C读函数，可以读取单个或者多个连续的字节。
//  * @param  driver_Addr(I2c器件的Slave地址，注意实际I2C驱动中7位地址和8位地址的区分)
//  * @param  start_Addr(需要读取的寄存器的起始地址)
//  * @param  number_Bytes(需要读取的数据的字节数)
//  * @param  read_Buffer(所读取寄存器的值) 
//  */

//写函数
//I2C_Write_NBytes(uint8_t driver_Addr, uint8_t start_Addr, uint8_t number_Bytes, uint8_t *write_Buffer)
///**
//  * @brief  I2C写函数，可以写单个或者多个连续的字节。
//  * @param  driver_Addr(I2c器件的Slave地址，注意实际I2C驱动中7位地址和8位地址的区分)
//  * @param  start_Addr(需要写的寄存器的起始地址)
//  * @param  number_Bytes(需要写的数据的字节数)
//  * @param  write_Buffer(所写的数据存放的地址) 
//  */

void sh200q_Reset(void)
{
	unsigned char tempdata[1];
	
	I2C_Read_NBytes(SH200Q_ADDRESS, SH200Q_RESET, 1, tempdata);
	
	//SH200Q_RESET
	tempdata[0] = tempdata[0] | 0x80;
	I2C_Write_NBytes(SH200Q_ADDRESS, SH200Q_RESET, 1, tempdata);
	
	DelayMs(1);
			
	tempdata[0] = tempdata[0] & 0x7F;
	I2C_Write_NBytes(SH200Q_ADDRESS, SH200Q_RESET, 1, tempdata);
}


//初始化
void sh200q_init(void) 
{
	unsigned char tempdata[1];
	unsigned char regdata1,regdata2;	
	
	while(tempdata[0] != 0x18)
	{
		I2C_Read_NBytes(SH200Q_ADDRESS, SH200Q_WHOAMI, 1, tempdata);
	}
	
	DelayMs(1);
	
	I2C_Read_NBytes(SH200Q_ADDRESS, 0xC2, 1, &regdata1);
	
	DelayMs(1);
	
	I2C_Read_NBytes(SH200Q_ADDRESS, 0xD8, 1, &regdata2);
	
	DelayMs(1);
	
	regdata1 = regdata1 | 0x04;
	I2C_Write_NBytes(SH200Q_ADDRESS, 0xC2, 1, &regdata1);
	
	DelayMs(1);
	
	regdata2 = regdata2 | 0x80;
	I2C_Write_NBytes(SH200Q_ADDRESS, 0xD8, 1, &regdata2);
	
	DelayMs(1);
	
	tempdata[0] = 0x61;
	I2C_Write_NBytes(SH200Q_ADDRESS, 0x78, 1, tempdata);
	
	DelayMs(1);
	
	regdata1 = regdata1 & 0xFB;
	I2C_Write_NBytes(SH200Q_ADDRESS, 0xC2, 1, &regdata1);
	
	DelayMs(1);
	
	regdata2 = regdata2 & 0x7F;
	I2C_Write_NBytes(SH200Q_ADDRESS, 0xD8, 1, &regdata2);

	DelayMs(1);
	
	tempdata[0] = 0x00;
	I2C_Write_NBytes(SH200Q_ADDRESS, 0x78, 1, tempdata);
	
	DelayMs(1);
	
	//set acc odr 256hz
	tempdata[0] = 0x91; //0x81 1024hz   //0x89 512hz    //0x91  256hz 
	I2C_Write_NBytes(SH200Q_ADDRESS, SH200Q_ACC_CONFIG, 1, tempdata);
	
	//set gyro odr 500hz
	tempdata[0] = 0x13; //0x11 1000hz    //0x13  500hz   //0x15  256hz
	I2C_Write_NBytes(SH200Q_ADDRESS, SH200Q_GYRO_CONFIG, 1, tempdata);
	
	//set gyro dlpf 50hz
	tempdata[0] = 0x03; //0x00 250hz   //0x01 200hz   0x02 100hz  0x03 50hz  0x04 25hz
	I2C_Write_NBytes(SH200Q_ADDRESS, SH200Q_GYRO_DLPF, 1, tempdata);
	
	//set no buffer mode
	tempdata[0] = 0x00;
	I2C_Write_NBytes(SH200Q_ADDRESS, SH200Q_FIFO_CONFIG, 1, tempdata);
	
	//set acc range +-8G
	tempdata[0] = 0x01;
	I2C_Write_NBytes(SH200Q_ADDRESS, SH200Q_ACC_RANGE, 1, tempdata);
	
	//set gyro range +-2000¶È/s
	tempdata[0] = 0x00; //0x00 2000 //0x01 1000 //0x02  500  //0x03 250  //0x04  125
	I2C_Write_NBytes(SH200Q_ADDRESS, SH200Q_GYRO_RANGE, 1, tempdata);
	
	//D5,D6 No contrl
	DelayMs(1);
	
	I2C_Read_NBytes(SH200Q_ADDRESS, 0xCA, 1, tempdata);
	
	DelayMs(1);
	
	tempdata[0] = tempdata[0] | 0x10;
	I2C_Write_NBytes(SH200Q_ADDRESS, 0xCA, 1, tempdata);
	
	DelayMs(1);
        
	tempdata[0] = tempdata[0] & 0xEF;
	I2C_Write_NBytes(SH200Q_ADDRESS, 0xCA, 1, tempdata);
	
	DelayMs(1);
	
	tempdata[0] = 0xC0;
	I2C_Write_NBytes(SH200Q_ADDRESS, 0xBA, 1, tempdata);

	DelayMs(10);
}


//获取ADC数据
void sh200q_getADC(void)
{
	short gyro[3] = {0};
	short acc[3] = {0};
	
	I2C_Read_NBytes(SH200Q_ADDRESS, SH200Q_OUTPUT_ACC_X, 12, rawADC);
	gyro[0] = (rawADC[7]<<8) | rawADC[6];
	gyro[1] = (rawADC[9]<<8) | rawADC[8];
	gyro[2] = (rawADC[11]<<8) | rawADC[10];
	
	
	acc[0] = (rawADC[1]<<8) | rawADC[0];
    acc[1] = (rawADC[3]<<8) | rawADC[2];
    acc[2] = (rawADC[5]<<8) | rawADC[4];
}
