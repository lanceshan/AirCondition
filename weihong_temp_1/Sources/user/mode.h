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
	MODE_HALT=0,	//��ģʽ0
	MODE_COLD,		//����ģʽ
	MODE_HOT,		//����ģʽ
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
