/*
 * getSysInfo.h
 *
 *  Created on: Jul 30, 2015
 *      Author: Hill
 */
#ifndef GETSYSINFO_H_
#define GETSYSINFO_H_

typedef  enum{
	oil_level=0,	//ch8	PTC0
	Temper,	        //ch9	PTC1
	
}ADC_CHANNEL;

void SysInfo_Init(void);
float Average_CALC(float *buf);
void Get_SysInfo(void);					//获取所有温度数据
float Temper_CALC(unsigned int Rr, unsigned int B, unsigned char T, unsigned int val);//温度计算
float Get_oilTemper(void);				//获取硅油温度
float level_Calc(unsigned int levelVal);//液位计算
float Get_oilLevel(void);			//获取液位值


#endif /* GETSYSINFO_H_ */
