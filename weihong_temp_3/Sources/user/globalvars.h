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
 * 变量需修改
 ***********************/
#define TIME_SEC			100
#define TIME_MIN			(1*TIME_SEC)     //由于压缩机自身有延时，所以软件延时变短为10s
#define TIME_SYS_START		(2*TIME_SEC)		//系统启动5s计时
#define TIME_MSG_SEND		20				//系统运行100ms计时
#define CMP_STOP_TIME		TIME_MIN
#define GET_SYSINFO_TIME    20				//采集系统信息时间间隔200ms
#define TREND_CHANGE_TIME	(5*TIME_SEC)		//温度趋势变化时间间隔5s
#define OFF_MODE_TIME		(8*TIME_SEC)		//关机模式时间计时88s
#define CAN_RECV_TIME		(3*TIME_SEC)		//3秒没收到CAN信息，通信故障
#define COLD_TEMPER          35                  //预设35℃以上开启制冷模式
#define BASE_TEMPER          25                  //预设35℃以上开启制冷模式
//通信相关
extern unsigned char CANRx_Buf[8];		//CAN接收缓存
extern unsigned char CANTx_Buf[8];		//CAN发送缓存
extern unsigned long CAN_ID;
//接收温度定义
extern	float Indoortemp;
//定义开机标志位

//时间管理
extern unsigned int  gSysStartTcnt; 	//系统上电启动5s定时计数
extern unsigned int  gMsgTxTcnt; 		//CAN发送时间间隔20ms定时计数
extern unsigned int  gSysRunTcnt; 		//系统运行间隔100ms定时计数
extern unsigned int  gGetSysInfoTcnt;	//采集温度时间间隔
extern unsigned int  PumpTestDelay;       //水泵检测延时
extern unsigned int  handCtrDelay;       //强制冷强制热模式下500ms 检测一次

typedef struct{
	float TEMP;				//油箱硅油温度
	float oil_level;        //油箱硅油液位
	unsigned char LevelErrTimes;
	unsigned char TEMPErrTimes;
	unsigned char CANRecvErrTimes;		//CAN通信计时，超时后表示通信失败
	union
	{
		unsigned char Byte;
		struct{
			unsigned char COMPFault     :1;	    //压缩机过压  确认不定义8位是否可行
			unsigned char PUMPLOWSPEED  :1;	    //水泵故障
			unsigned char LEVELLOW      :1;     //硅油液位过低故障
			unsigned char CANFault      :1;	    //CAN通信故障
			unsigned char TEMPHIGH      :1;	    //0：硅油温度传感器正常；1表示温度传感器故障或者温度过高
			unsigned char TEMPLOW       :1;	    //1表示温度传感器温度过低
		}bits;
	}ErrDevices;
	union{                                      //系统工作定义
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
//	float tempCtrHot;        //强制制热控制温度
//	unsigned int Comp_PWM;   //用户设置PWM调速
//}UserMessage;

extern SysMessage sys_Info;
//extern UserMessage user_Info;

#endif /* GLOBALVARS_H_ */
