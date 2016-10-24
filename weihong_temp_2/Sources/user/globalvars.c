/*
 * globalvars.c
 *
 *  Created on: Jul 30, 2015
 *      Author: Hill
 */

#include "globalvars.h"
#include "PE_Types.h"
//通信相关
unsigned char CANRx_Buf[8]={0};		//CAN接收缓存
unsigned char CANTx_Buf[8]={0};		//CAN发送缓存
unsigned long CAN_ID = 0;

//定时器相关
unsigned int  gSysStartTcnt = TIME_SEC;	//系统上电启动5s定时计数
unsigned int  gMsgTxTcnt = 0; 		//CAN信息发送时间间隔20ms
unsigned int  gSysRunTcnt = 0; 		//系统运行间隔1s定时计数  led闪烁
unsigned int  gGetSysInfoTcnt = 0;	//采集温度时间间隔
unsigned int  PumpTestDelay = 0;    //水泵检测延时
unsigned int  handCtrDelay = 0;     //强制冷强制热模式下500ms 检测一次


SysMessage  sys_Info;       //系统信息
//UserMessage user_Info;		//用户设置信息
