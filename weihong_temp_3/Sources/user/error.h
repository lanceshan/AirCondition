/*
 * error.h
 *
 *  Created on: Jul 30, 2015
 *      Author: Hill
 */

#ifndef ERROR_H_
#define ERROR_H_

#define ERR_NULL 			0x00 	 		//无错
#define ERR_Lv1 			0x01 			//温度故障，温度传感器故障或硅油温度过高     温度设定50度，可以调整
#define ERR_Lv2 			0x02 			//液位故障，液位过低
#define ERR_Lv3				0x04 			//水泵故障
#define ERR_Lv4				0x08			//压缩机故障
#define ERR_Lv5				0x10			//CAN通信故障
//#define ERR_Lv6				0x20			//运行过程中强制冷故障
//#define ERR_Lv7				0x40			//运行过程中强制热故障

 
unsigned char ErrorCheck(void);
void ErrorHandle(unsigned char err);
#endif /* ERROR_H_ */
