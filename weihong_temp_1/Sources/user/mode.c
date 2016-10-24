/*
 * mode.c
 *
 *  Created on: Jul 30, 2015
 *      Author: Hill
 */
#include "mode.h"
#include "globalvars.h"
#include "Comp_start.h"
#include "Cold_RLY1.h"
#include "Hot_RLY2.h"
#include "FAN_RLY4.h"
#include "Pump1_RLY5.h"
#include "Pump2_RLY6.h"
#include "Air_Comp_RLY3.h"
#include "PWM1.h"

void Hot_PowerOn(void)
{
	if((Pump1_RLY5_GetVal() == 0) || (Pump2_RLY6_GetVal() == 0))
	{
		Pump1_RLY5_SetVal();
		Pump2_RLY6_SetVal();
	}	

	if(Hot_RLY2_GetVal() == 0)
	{
		Hot_RLY2_SetVal();
	}
}

void Hot_Close(void)
{
	if(Hot_RLY2_GetVal() == 1)
	{
		Hot_RLY2_ClrVal();
	}
	
	if((Pump1_RLY5_GetVal() == 1) || (Pump2_RLY6_GetVal() == 1))
	{
		Pump1_RLY5_ClrVal();
		Pump2_RLY6_ClrVal();
	}
	
}

void Cold_PowerOn(void)
{
	if((Pump1_RLY5_GetVal() == 0) || (Pump2_RLY6_GetVal() == 0))
	{
		Pump1_RLY5_SetVal();
		Pump2_RLY6_SetVal();
	}
	if(FAN_RLY4_GetVal() == 0)
	{
		FAN_RLY4_SetVal();
	}
	if(Cold_RLY1_GetVal() == 0)
	{
		Cold_RLY1_SetVal();
	}
	if(Air_Comp_RLY3_GetVal() == 0)
	{
		Air_Comp_RLY3_SetVal();
	}
	if(Comp_Start_GetVal() == 1)
	{
		Comp_Start_ClrVal();
	}
	
	PWM1_SetRatio16(17874);      //设置占空比5000转
}

void Cold_Close(void)
{
	if(Comp_Start_GetVal() == 0)
	{
		Comp_Start_SetVal();
	}
	if(Air_Comp_RLY3_GetVal() == 1)
	{
		Air_Comp_RLY3_ClrVal();
	}
	if(Cold_RLY1_GetVal() == 1)
	{
		Cold_RLY1_ClrVal();
	}
	
	PWM1_SetRatio16(65535);    //设置占空比为0
	
	if((Pump1_RLY5_GetVal() == 1) || (Pump2_RLY6_GetVal() == 1))
	{
		Pump1_RLY5_ClrVal();
		Pump2_RLY6_ClrVal();
	}
	if(FAN_RLY4_GetVal() == 1)
	{
		FAN_RLY4_ClrVal();
	}
}
