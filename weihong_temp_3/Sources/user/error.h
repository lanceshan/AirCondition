/*
 * error.h
 *
 *  Created on: Jul 30, 2015
 *      Author: Hill
 */

#ifndef ERROR_H_
#define ERROR_H_

#define ERR_NULL 			0x00 	 		//�޴�
#define ERR_Lv1 			0x01 			//�¶ȹ��ϣ��¶ȴ��������ϻ�����¶ȹ���     �¶��趨50�ȣ����Ե���
#define ERR_Lv2 			0x02 			//Һλ���ϣ�Һλ����
#define ERR_Lv3				0x04 			//ˮ�ù���
#define ERR_Lv4				0x08			//ѹ��������
#define ERR_Lv5				0x10			//CANͨ�Ź���
//#define ERR_Lv6				0x20			//���й�����ǿ�������
//#define ERR_Lv7				0x40			//���й�����ǿ���ȹ���

 
unsigned char ErrorCheck(void);
void ErrorHandle(unsigned char err);
#endif /* ERROR_H_ */
