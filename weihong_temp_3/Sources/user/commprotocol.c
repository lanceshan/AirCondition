/*
 * commprotocol.c
 *
 *  Created on: Jul 30, 2015
 *      Author: Hill
 */

#include "commprotocol.h"
#include "mode.h"
#include "CAN1.h"
#include "driver\can.h"
#include "globalvars.h"
#include <cstdlib>
#include "Cold_RLY1.h"
#include "Hot_RLY2.h"
#include "FAN_RLY4.h"
#include "Pump1_RLY5.h"
#include "Pump2_RLY6.h"
#include "Air_Comp_RLY3.h"
#include "Press_en.h"

extern uint8 err_Mode;
void CAN_Rx(void)
{
	if(CAN_Read(&CANRx_Buf[0], &CAN_ID) != 8)return;	//��������
	sys_Info.CANRecvErrTimes = 0;
	if(CAN_ID == 0x14b)
	{
		switch(CANRx_Buf[0])
		{
			/*********
			case 0x33:			//�����û�������Ϣ,���������¶Ȳ�����TEMPAΪ�¶��������֣�TEMPBΪ�¶�С������
				user_Info.TempA	   = CANRx_Buf[1];
				user_Info.TempB    = CANRx_Buf[2];
				Indoortemp=0.1*((signed int)(user_Info.TempA*10+user_Info.TempB));
				break;
			 
			case 0x44:		//��������
				user_Info.tempA   = CANRx_Buf[1];
				user_Info.tempB   = CANRx_Buf[2];
				user_Info.Comp_PWM_H   = CANRx_Buf[3];
				user_Info.Comp_PWM_L   = CANRx_Buf[4];
				user_Info.tempCtrHot = 0.1*((signed int)(user_Info.tempA * 10 +user_Info.tempB));
				user_Info.Comp_PWM = (unsigned int)(user_Info.Comp_PWM_H*256 + user_Info.Comp_PWM_L);
				break;
			*********/
			case 0x55:							          //����ϵͳ�ڼ̵�������
				if(CANRx_Buf[1] == 0) Cold_RLY1_ClrVal();		//����ѹ������ѹ�̵�����
				if(CANRx_Buf[1] == 1) Cold_RLY1_SetVal();		//����ѹ������ѹ�̵�����
				if(CANRx_Buf[2] == 0) Hot_RLY2_ClrVal();	   	//PTC�̵�����
				if(CANRx_Buf[2] == 1) Hot_RLY2_SetVal();		//PTC�̵�����		
				if(CANRx_Buf[3] == 0) Air_Comp_RLY3_ClrVal();	//����ѹ�������Ƽ̵�����
				if(CANRx_Buf[3] == 1) Air_Comp_RLY3_SetVal();	//����ѹ�������Ƽ̵�����
				if(CANRx_Buf[4] == 0) FAN_RLY4_ClrVal();		//����̵�����
				if(CANRx_Buf[4] == 1) FAN_RLY4_SetVal();		//����̵�����
				if(CANRx_Buf[5] == 0) Pump1_RLY5_ClrVal();		//ˮ��1�̵�����
				if(CANRx_Buf[5] == 1) Pump1_RLY5_SetVal();		//ˮ��1�̵�����
				if(CANRx_Buf[6] == 0) Pump2_RLY6_ClrVal();		//ˮ��2�̵�����
				if(CANRx_Buf[6] == 1) Pump2_RLY6_SetVal();		//ˮ��2�̵�����
				break;
			default:
				break;
		}
	}
	if((CAN_ID & 0x1fffffff) == 0x18011114)
	{
		if((CANRx_Buf[0] & 0x03) == 0x01)        //����
		{  
			if(Hot_RLY2_GetVal() == 1){
				Hot_RLY2_ClrVal();
			}
			if(Press_en_GetVal() == 1){       //ѹ������������
				Cold_RLY1_ClrVal();
				Air_Comp_RLY3_ClrVal();
			}
			Cold_PowerOn();
			sys_Info.sendBuf.bits.WorkMode = 1;
		} 
		else if((CANRx_Buf[0] & 0x03) == 0x02)  //����
		{
			if((Cold_RLY1_GetVal() == 1) || (Air_Comp_RLY3_GetVal() == 1) || (FAN_RLY4_GetVal() == 1)){
				Cold_RLY1_ClrVal();
				Air_Comp_RLY3_ClrVal();
				FAN_RLY4_ClrVal();
			}
			if(sys_Info.TEMP > 60)
			{
				Hot_Close();
			}
			Hot_PowerOn();
			sys_Info.sendBuf.bits.WorkMode = 2;
		}
		else if((CANRx_Buf[0] & 0x03) == 0x00)   //�ر����� ����
		{
			Hot_Close();
			Cold_Close();
			sys_Info.sendBuf.bits.WorkMode = 0;
		}
	}
	
	
		
}

void CAN_Tx(void)
{
	if(gMsgTxTcnt != 0)return;
	gMsgTxTcnt = 2;
	
	CANTx_Buf[0] = sys_Info.sendBuf.Byte;
	CANTx_Buf[1] = (uint8)((uint16)(abs(sys_Info.TEMP*10))/10);
	CANTx_Buf[2] = (uint8)((uint16)(abs(sys_Info.TEMP*10))%10);
	CANTx_Buf[3] = (uint8)((uint16)(abs(sys_Info.oil_level*10))/10);
	CANTx_Buf[4] = (uint8)((uint16)(abs(sys_Info.oil_level*10))%10);
	CANTx_Buf[5] = 0;									//����ʹ��
	CANTx_Buf[6] = err_Mode;
	CANTx_Buf[7] = sys_Info.ErrDevices.Byte;     
//	CANTx_Buf[5] = user_Info.tempA;									
//	CANTx_Buf[6] = (uint8)((uint16)(user_Info.Comp_PWM/256));
//	CANTx_Buf[7] = (uint8)((uint16)(user_Info.Comp_PWM%256));
	CAN_ID = 0x18021411;
	CAN_Send(CANTx_Buf,8,CAN_ID);	
}
