/*
 * getSysInfo.c
 *
 *  Created on: Jul 30, 2015
 *      Author: Hill
 */
#include "user\getSysInfo.h"
#include "driver\adc.h"
#include "user\globalvars.h"
#include <math.h>
#include <cstdlib>

#define E				2.718281828459	//自然数e
#define IN_AIR_R 		10000+10
#define IN_AIR_B		3435
#define IN_AIR_T		25

static float oilTemper_Buf[10] = {0};
static float oilLevel_Buf[10] = {0};

static unsigned char sTimes = 0;


float Average_CALC(float *buf)
{
	unsigned char i = 0;
	float temp = 0;
	for(i=0; i<10; i++)
		temp += buf[i];
	temp = temp/sTimes;
	return temp;
}

void Get_SysInfo(void)
{
	float new_temper = 0.0;
	float new_level = 0.0;
	if(gGetSysInfoTcnt != 0)return; //每隔200ms采集一次
	gGetSysInfoTcnt = GET_SYSINFO_TIME;//重新定义采集时间200ms
	
	new_temper = Get_oilTemper();	//硅油温度度采集
	if((new_temper < 100) && (new_temper > -50))
	{
		oilTemper_Buf[sTimes] = new_temper;
		sys_Info.TEMPErrTimes = 0;
	}
	else
	{
		oilTemper_Buf[sTimes] = sys_Info.TEMP; 
		if(sys_Info.TEMPErrTimes < 50)sys_Info.TEMPErrTimes++;
	}
	
	new_level = Get_oilLevel();	//硅油液位度采集
	if((new_level < 250) && (new_level >= 40))
	{
		oilLevel_Buf[sTimes] = new_level;
		sys_Info.LevelErrTimes = 0;
	}
	else
	{
		oilLevel_Buf[sTimes] = sys_Info.oil_level;
		if(sys_Info.LevelErrTimes < 50)sys_Info.LevelErrTimes++;
	}
	
	sTimes++;
	if(sTimes >= 10)
	{
		sys_Info.TEMP    = Average_CALC(oilTemper_Buf);
		sys_Info.oil_level = Average_CALC(oilLevel_Buf);
		sTimes = 0;
	}
}

float Temper_CALC(unsigned int Rr, unsigned int B, unsigned char T, unsigned int val)//热敏电阻温度计算
{
	float temp=0.0;
	float x=0.0;
	x = 1.0*4700*val/((4096-val)*Rr);		//分压电阻为4.7kΩ，AD精度12位，Rt = R *EXP(B*(1/T1-1/T2)) ,R=5000,B=3470,T2=273.15+25,Rt为T1（绝对温度）温度时的电阻
	temp = 1.0*B/( (1.0*B/(T+273.15)) + (log(x)/log(E)) )-273.15;
	temp = 0.1*(((signed int)(temp*100 + 5))/10);	//四舍五入，保留一位小数
	return temp;
}

float Get_oilTemper(void)		//环境温度采集
{
	unsigned int airtmp=0;
	airtmp = adc_rd(Temper);
	return Temper_CALC(IN_AIR_R, IN_AIR_B, IN_AIR_T, airtmp);
}

float level_Calc(unsigned int levelVal)
{
	float temp=0.0;
	temp = 1.0*600*levelVal/((4096-levelVal)*7) + 40;   //计算Rt= 7/6 * h - 140/3  ;  Rt = 100*levelVal/(4096-levelVal);  100位分压电阻
	return temp;
}
float Get_oilLevel(void)
{
	unsigned int oilLevel=0;
	oilLevel = adc_rd(oil_level);
	return level_Calc(oilLevel);
}

void SysInfo_Init(void)
{
	sys_Info.TEMP    = Get_oilTemper();   //获取油箱硅油温度
	sys_Info.oil_level = Get_oilLevel();  //获取油箱液位信息
}
