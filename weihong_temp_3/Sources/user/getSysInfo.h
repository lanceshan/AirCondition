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
void Get_SysInfo(void);					//��ȡ�����¶�����
float Temper_CALC(unsigned int Rr, unsigned int B, unsigned char T, unsigned int val);//�¶ȼ���
float Get_oilTemper(void);				//��ȡ�����¶�
float level_Calc(unsigned int levelVal);//Һλ����
float Get_oilLevel(void);			//��ȡҺλֵ


#endif /* GETSYSINFO_H_ */
