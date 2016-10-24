/*
 * mode.h
 *
 *  Created on: Jul 30, 2015
 *      Author: Hill
 */

#ifndef MODE_H_
#define MODE_H_

typedef void (*tModeProcess)(void);

typedef enum{
	MODE_HALT=0,	//空模式0
	MODE_COLD,		//制冷模式
	MODE_HOT,		//制热模式
}DRV_MODE;

void Cold_PowerOn(void);
void Cold_Close(void);

void Hot_PowerOn(void);
void Hot_Close(void);

 /************************************                           
void ColdProcess(void);
void Cold_Open(void);

unsigned char Power_OFFProcess(unsigned char offstep);
*************************************/
#endif /* MODE_H_ */
