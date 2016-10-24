/*
 * error.c
 *
 *  Created on: Jul 30, 2015
 *      Author: Hill
 */
#include "error.h"
#include "globalvars.h"
#include "mode.h"
#include "PE_Types.h"
#include "Cold_en.h"
#include "Hot_en.h"
#include "Flow_en.h"
#include "Press_en.h"

#include "Comp_start.h"
#include "Cold_RLY1.h"
#include "Hot_RLY2.h"
#include "Fan_RLY4.h"
#include "Pump1_RLY5.h"
#include "Pump2_RLY6.h"
#include "Air_Comp_RLY3.h"

#include "CAN1.h"
#include "commprotocol.h"

static uint8 pumpFirstTest = 1;

unsigned char ErrorCheck(void)	//故障检测，故障消除后自动恢复
{
	uint8 error = ERR_NULL;

	
	if((sys_Info.TEMP >= 70) || (sys_Info.TEMPErrTimes >= 30))
	{										//控制仓高温或者传感器失效
		sys_Info.ErrDevices.bits.TEMPHIGH = 1;  //硅油温度过高   
		error |= ERR_Lv1;					
	}
	else if(sys_Info.TEMP <= -25)
	{
		sys_Info.ErrDevices.bits.TEMPLOW = 1;   //硅油温度过低  
		error |= ERR_Lv1;					
    }
	else                                      //故障解除自动恢复
	{                               
		sys_Info.ErrDevices.bits.TEMPHIGH = 0;    
		sys_Info.ErrDevices.bits.TEMPLOW = 0;
		error &= 0xfe;						
	}
	
	
	
	if((sys_Info.oil_level < 170) || (sys_Info.LevelErrTimes >= 300))   //液位传感器故障或者液位过低
	{	
		sys_Info.ErrDevices.bits.LEVELLOW = 1;			//硅油液位过低或者液位传感器故障
		error |= ERR_Lv2;					
	}
	else
	{
		sys_Info.ErrDevices.bits.LEVELLOW = 0;
		error &= 0xfd;						            //清除液位故障
	}

	
	if(Press_en_GetVal() == 1)               //压缩机故障
	{
		sys_Info.ErrDevices.bits.COMPFault = 1;
		error |= ERR_Lv4;					
	}
	else
	{
		sys_Info.ErrDevices.bits.COMPFault = 0;
		error &= 0xf7;						//清除压缩机故障
	}
	
	if(sys_Info.CANRecvErrTimes >= 500)		//CAN通信失败
	{
		sys_Info.ErrDevices.bits.CANFault = 1;
		//error |= ERR_Lv5;					//调试时屏蔽CAN故障
	}
	else
	{
		sys_Info.ErrDevices.bits.CANFault = 0;
		error &= 0xef;	
	}	
	
	if((Pump1_RLY5_GetVal() == 1) || (Pump2_RLY6_GetVal() == 1))    //水泵启动后检测水泵
	{
		if(pumpFirstTest == 1){
			PumpTestDelay = 2000;
			pumpFirstTest = 2;
		}
		if(PumpTestDelay == 0)
		{
			PumpTestDelay = 200;	
			if(Flow_en_GetVal() == 1){
				sys_Info.sendBuf.bits.PumpState = 0;
				error |= ERR_Lv3;
				sys_Info.ErrDevices.bits.PUMPLOWSPEED =1;
			}
			else
			{
				sys_Info.sendBuf.bits.PumpState = 1;
				error &= 0xfb;	
				sys_Info.ErrDevices.bits.PUMPLOWSPEED =0;
			}
		}
	}
	else{
		sys_Info.sendBuf.bits.PumpState = 0;     //未启动水泵
	}
	return error;
}

void ErrorHandle(unsigned char err)
{

	if((err & ERR_Lv1) || (err & ERR_Lv2) || (err & ERR_Lv3) || (err & ERR_Lv4) || (err & ERR_Lv5))   //工作状态报错，但并不停机
	{
		//CANTx_Buf[0] |= (0x01<<0x03); 
		sys_Info.sendBuf.bits.WorkState = 1;
		
	}
	else
	{
		//CANTx_Buf[0] &= 0xf7;                                          //工作状态位恢复
		sys_Info.sendBuf.bits.WorkState = 0;
	}		
	 
	if((err & ERR_Lv2) || (err & ERR_Lv3) || (err & ERR_Lv4) || (err & ERR_Lv5)) 
	{
		//CANTx_Buf[0] &= 0xdf;                    //关闭启停位不允许启动   
		sys_Info.sendBuf.bits.StartorStop = 0;
	}
	else
	{
		//CANTx_Buf[0] |= (0x01<<0x05);            //允许启动	
		sys_Info.sendBuf.bits.StartorStop = 1;
	}
}

