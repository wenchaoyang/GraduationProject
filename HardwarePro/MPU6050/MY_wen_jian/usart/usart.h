#ifndef __USART_H
#define __USART_H
#include "stm32f10x.h" 
#include "stdio.h"	 
 	  
 
	  	
void USART1_Config(void);   //��ʼ�� ����USART1
void USART2_Config(void);   //��ʼ�� ����USART2
void USART3_Config(void);   //��ʼ�� ����USART3
void UART4_Config(void);    //��ʼ�� ����UART4
void UART5_Config(void);    //��ʼ�� ����UART5
void usart3_SendByte(unsigned char SendData);	  //�ô���3����һ���ֽ�����



#endif	   
















