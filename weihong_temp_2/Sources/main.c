/* ###################################################################
**     Filename    : main.c
**     Project     : weihong_temp
**     Processor   : SKEAZ128MLK4
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2016-08-07, 15:04, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.01
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "uLED.h"
#include "BitIoLdd1.h"
#include "Flow_en.h"
#include "BitIoLdd2.h"
#include "Press_en.h"
#include "BitIoLdd3.h"
#include "Cold_en.h"
#include "BitIoLdd4.h"
#include "Hot_en.h"
#include "BitIoLdd5.h"
#include "Comp_Start.h"
#include "BitIoLdd6.h"
#include "Cold_RLY1.h"
#include "BitIoLdd7.h"
#include "Hot_RLY2.h"
#include "BitIoLdd8.h"
#include "Air_Comp_RLY3.h"
#include "BitIoLdd9.h"
#include "FAN_RLY4.h"
#include "BitIoLdd10.h"
#include "Pump1_RLY5.h"
#include "BitIoLdd11.h"
#include "Pump2_RLY6.h"
#include "BitIoLdd12.h"
#include "CAN1.h"
#include "PWM1.h"
#include "PwmLdd1.h"
#include "TU1.h"
#include "Timer_10ms.h"
#include "TU2.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "PDD_Includes.h"
#include "Init_Config.h"

#include "driver\can.h"
#include "driver\adc.h"

#include "user\globalvars.h"
#include "user\commprotocol.h"
#include "user\error.h"
#include "user\getSysInfo.h"
#include "user\mode.h"
/* User includes (#include below this line is not maintained by Processor Expert) */
uint8 err_Mode = ERR_NULL; 
/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */
 // uint8 err_Mode = ERR_NULL; 
  unsigned int switchco = 1;
  unsigned int switchho = 1;
  unsigned int  gMsgTxTcnt_BMS2 = 0;

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  CAN_Init();
  adc_init();
  SysInfo_Init();
  /*** End of Processor Expert internal initialization.                    ***/
  PWM1_SetRatio16(65535);      //PWM占空比初始化为0
  gSysStartTcnt = TIME_SEC;
  //user_Info.tempCtrHot = 60.0;
  //user_Info.Comp_PWM = 17874; //压缩机PWM设定5000转
  while(gSysStartTcnt != 0)       //检测模式判断，如需检测上电之前拨动开关至相应位置
  {
	  switchco = Cold_en_GetVal();
	  switchho = Hot_en_GetVal();
  }
  /* Write your code here */
  /* For example: for(;;) { } */
  
  if((switchco ==1 ) && (switchho == 1))     //正常工作模式，受BMS系统控制
  {
	  sys_Info.sendBuf.bits.WorkMode = 0;
	  for(;;)
	  {
	  	  Get_SysInfo();
	  	  err_Mode = ErrorCheck();
	  	  if(err_Mode != ERR_NULL)
	  	  {
	  		  ErrorHandle(err_Mode);
	  	  }else{
	  		  sys_Info.sendBuf.bits.StartorStop = 1;
	  		  sys_Info.sendBuf.bits.WorkState = 0;
	  	  }
	  	  if((Cold_en_GetVal() == 0) || (Hot_en_GetVal() == 0))
	  	  {
	  		  sys_Info.sendBuf.bits.StartorStop = 0;                   //关闭启停位不允许启动   
	  	  }
	  	if(gMsgTxTcnt == 0)                     //每20ms发送一次数据
	  	{
	  		gMsgTxTcnt_BMS2++;
	  		if(gMsgTxTcnt_BMS2 == 3)
	  		{
	  			CAN_Tx();  
	  		}else if(gMsgTxTcnt_BMS2 == 5)
	  		{
	  			CAN_Tx_BMS2(); 
	  			gMsgTxTcnt_BMS2 = 0;
	  		}
	  		gMsgTxTcnt = 1;
	  	}
	  	CAN_Rx();
	 }
  }
  else                                   //检测模式，受系统内部传感器控制
  {
	  for(;;)
	  {
		  if(gMsgTxTcnt == 0)                     //每20ms发送一次数据
		  {
			  gMsgTxTcnt_BMS2++;
			  if(gMsgTxTcnt_BMS2 == 3)
			  {
				  CAN_Tx();  
			  }else if(gMsgTxTcnt_BMS2 == 5)
			  {
				  CAN_Tx_BMS2(); 
				  gMsgTxTcnt_BMS2 = 0;
			  }
			  gMsgTxTcnt = 1;
		  }
		  Get_SysInfo();
		  err_Mode = ErrorCheck();
		  if(err_Mode != ERR_NULL)
		  {
			  ErrorHandle(err_Mode);
		  }else{
	  		  sys_Info.sendBuf.bits.StartorStop = 1;
	  		  sys_Info.sendBuf.bits.WorkState = 0;
	  	  }
		 
		  if((Cold_en_GetVal() == 0) && (Hot_en_GetVal() == 1))  //制冷
		  {
			  if(Press_en_GetVal() == 1){       //压力传感器保护
				 Cold_RLY1_ClrVal();
				 Air_Comp_RLY3_ClrVal();
			  }
			  Cold_PowerOn();	  
			  sys_Info.sendBuf.bits.WorkMode = 1;
		  }else if(Hot_en_GetVal() == 0 && (Cold_en_GetVal() == 1))  //制热
		  {
			  if(sys_Info.TEMP > 60)
			  {
				  Hot_Close();
			  }
			  Hot_PowerOn();
			  sys_Info.sendBuf.bits.WorkMode = 2;
		  }
		  else if((Hot_en_GetVal() == 1) && (Cold_en_GetVal() == 1))   //关闭
		  {
			  Hot_Close();
			  Cold_Close();
			  sys_Info.sendBuf.bits.WorkMode = 0;
		  }
	  }  
  }
  
  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.3 [05.09]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
