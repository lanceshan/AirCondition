/*
 * globalvars.h
 *
 *  Created on: Jul 30, 2015
 *      Author: Hill
 */

#ifndef GLOBALVARS_H_
#define GLOBALVARS_H_

//#define Debug
/************************
 * �������޸�
 ***********************/
#define TIME_SEC			100
#define TIME_MIN			(1*TIME_SEC)     //����ѹ������������ʱ�����������ʱ���Ϊ10s
#define TIME_SYS_START		(2*TIME_SEC)		//ϵͳ����5s��ʱ
#define TIME_MSG_SEND		20				//ϵͳ����100ms��ʱ
#define CMP_STOP_TIME		TIME_MIN
#define GET_SYSINFO_TIME    20				//�ɼ�ϵͳ��Ϣʱ����200ms
#define TREND_CHANGE_TIME	(5*TIME_SEC)		//�¶����Ʊ仯ʱ����5s
#define OFF_MODE_TIME		(8*TIME_SEC)		//�ػ�ģʽʱ���ʱ88s
#define CAN_RECV_TIME		(3*TIME_SEC)		//3��û�յ�CAN��Ϣ��ͨ�Ź���
#define COLD_TEMPER          35                  //Ԥ��35�����Ͽ�������ģʽ
#define BASE_TEMPER          25                  //Ԥ��35�����Ͽ�������ģʽ
//ͨ�����
extern unsigned char CANRx_Buf[8];		//CAN���ջ���
extern unsigned char CANTx_Buf[8];		//CAN���ͻ���
extern unsigned long CAN_ID;
//�����¶ȶ���
extern	float Indoortemp;
//���忪����־λ

//ʱ�����
extern unsigned int  gSysStartTcnt; 	//ϵͳ�ϵ�����5s��ʱ����
extern unsigned int  gMsgTxTcnt; 		//CAN����ʱ����20ms��ʱ����
extern unsigned int  gSysRunTcnt; 		//ϵͳ���м��100ms��ʱ����
extern unsigned int  gGetSysInfoTcnt;	//�ɼ��¶�ʱ����
extern unsigned int  PumpTestDelay;       //ˮ�ü����ʱ
extern unsigned int  handCtrDelay;       //ǿ����ǿ����ģʽ��500ms ���һ��

typedef struct{
	float TEMP;				//��������¶�
	float oil_level;        //�������Һλ
	unsigned char LevelErrTimes;
	unsigned char TEMPErrTimes;
	unsigned char CANRecvErrTimes;		//CANͨ�ż�ʱ����ʱ���ʾͨ��ʧ��
	union
	{
		unsigned char Byte;
		struct{
			unsigned char COMPFault     :1;	    //ѹ������ѹ  ȷ�ϲ�����8λ�Ƿ����
			unsigned char PUMPLOWSPEED  :1;	    //ˮ�ù���
			unsigned char LEVELLOW      :1;     //����Һλ���͹���
			unsigned char CANFault      :1;	    //CANͨ�Ź���
			unsigned char TEMPHIGH      :1;	    //0�������¶ȴ�����������1��ʾ�¶ȴ��������ϻ����¶ȹ���
			unsigned char TEMPLOW       :1;	    //1��ʾ�¶ȴ������¶ȹ���
		}bits;
	}ErrDevices;
	union{                                      //ϵͳ��������
		unsigned char Byte;
		struct{
			unsigned char WorkMode    :3;
			unsigned char WorkState   :1;
			unsigned char PumpState   :1;
			unsigned char StartorStop :1;
		}bits;
	}sendBuf;
}SysMessage;
//typedef struct{
//	float tempCtrHot;        //ǿ�����ȿ����¶�
//	unsigned int Comp_PWM;   //�û�����PWM����
//}UserMessage;

extern SysMessage sys_Info;
//extern UserMessage user_Info;

#endif /* GLOBALVARS_H_ */
