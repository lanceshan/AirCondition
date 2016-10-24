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

unsigned char ErrorCheck(void)	//���ϼ�⣬�����������Զ��ָ�
{
	uint8 error = ERR_NULL;

	
	if((sys_Info.TEMP >= 70) || (sys_Info.TEMPErrTimes >= 30))
	{										//���Ʋָ��»��ߴ�����ʧЧ
		sys_Info.ErrDevices.bits.TEMPHIGH = 1;  //�����¶ȹ���   
		error |= ERR_Lv1;					
	}
	else if(sys_Info.TEMP <= -25)
	{
		sys_Info.ErrDevices.bits.TEMPLOW = 1;   //�����¶ȹ���  
		error |= ERR_Lv1;					
    }
	else                                      //���Ͻ���Զ��ָ�
	{                               
		sys_Info.ErrDevices.bits.TEMPHIGH = 0;    
		sys_Info.ErrDevices.bits.TEMPLOW = 0;
		error &= 0xfe;						
	}
	
	
	
	if((sys_Info.oil_level < 170) || (sys_Info.LevelErrTimes >= 300))   //Һλ���������ϻ���Һλ����
	{	
		sys_Info.ErrDevices.bits.LEVELLOW = 1;			//����Һλ���ͻ���Һλ����������
		error |= ERR_Lv2;					
	}
	else
	{
		sys_Info.ErrDevices.bits.LEVELLOW = 0;
		error &= 0xfd;						            //���Һλ����
	}

	
	if(Press_en_GetVal() == 1)               //ѹ��������
	{
		sys_Info.ErrDevices.bits.COMPFault = 1;
		error |= ERR_Lv4;					
	}
	else
	{
		sys_Info.ErrDevices.bits.COMPFault = 0;
		error &= 0xf7;						//���ѹ��������
	}
	
	if(sys_Info.CANRecvErrTimes >= 500)		//CANͨ��ʧ��
	{
		sys_Info.ErrDevices.bits.CANFault = 1;
		//error |= ERR_Lv5;					//����ʱ����CAN����
	}
	else
	{
		sys_Info.ErrDevices.bits.CANFault = 0;
		error &= 0xef;	
	}	
	
	if((Pump1_RLY5_GetVal() == 1) || (Pump2_RLY6_GetVal() == 1))    //ˮ����������ˮ��
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
		sys_Info.sendBuf.bits.PumpState = 0;     //δ����ˮ��
	}
	return error;
}

void ErrorHandle(unsigned char err)
{

	if((err & ERR_Lv1) || (err & ERR_Lv2) || (err & ERR_Lv3) || (err & ERR_Lv4) || (err & ERR_Lv5))   //����״̬����������ͣ��
	{
		//CANTx_Buf[0] |= (0x01<<0x03); 
		sys_Info.sendBuf.bits.WorkState = 1;
		
	}
	else
	{
		//CANTx_Buf[0] &= 0xf7;                                          //����״̬λ�ָ�
		sys_Info.sendBuf.bits.WorkState = 0;
	}		
	 
	if((err & ERR_Lv2) || (err & ERR_Lv3) || (err & ERR_Lv4) || (err & ERR_Lv5)) 
	{
		//CANTx_Buf[0] &= 0xdf;                    //�ر���ͣλ����������   
		sys_Info.sendBuf.bits.StartorStop = 0;
	}
	else
	{
		//CANTx_Buf[0] |= (0x01<<0x05);            //��������	
		sys_Info.sendBuf.bits.StartorStop = 1;
	}
}

