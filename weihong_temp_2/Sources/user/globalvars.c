/*
 * globalvars.c
 *
 *  Created on: Jul 30, 2015
 *      Author: Hill
 */

#include "globalvars.h"
#include "PE_Types.h"
//ͨ�����
unsigned char CANRx_Buf[8]={0};		//CAN���ջ���
unsigned char CANTx_Buf[8]={0};		//CAN���ͻ���
unsigned long CAN_ID = 0;

//��ʱ�����
unsigned int  gSysStartTcnt = TIME_SEC;	//ϵͳ�ϵ�����5s��ʱ����
unsigned int  gMsgTxTcnt = 0; 		//CAN��Ϣ����ʱ����20ms
unsigned int  gSysRunTcnt = 0; 		//ϵͳ���м��1s��ʱ����  led��˸
unsigned int  gGetSysInfoTcnt = 0;	//�ɼ��¶�ʱ����
unsigned int  PumpTestDelay = 0;    //ˮ�ü����ʱ
unsigned int  handCtrDelay = 0;     //ǿ����ǿ����ģʽ��500ms ���һ��


SysMessage  sys_Info;       //ϵͳ��Ϣ
//UserMessage user_Info;		//�û�������Ϣ
