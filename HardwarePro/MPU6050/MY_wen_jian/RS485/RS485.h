#ifndef __RS485_H
#define __RS485_H
#include "stm32f10x.h" 

/*RE��GPIOC5�ܽ�����*/   
#define Set_RE       GPIO_SetBits(GPIOC,GPIO_Pin_5);		// һ��λ����,ĳ��λ��1��	 
#define Clr_RE       GPIO_ResetBits(GPIOC,GPIO_Pin_5);	    // һ��λ����,ĳ��λ���㡣
/*DE��GPIOC4�ܽ�����*/
#define Set_DE       GPIO_SetBits(GPIOC,GPIO_Pin_4);		// һ��λ����,ĳ��λ��1��
#define Clr_DE       GPIO_ResetBits(GPIOC,GPIO_Pin_4);	    // һ��λ����,ĳ��λ���㡣

extern u8 buff_485[9];         //����485�źŻ�����
extern u8 uart_1;              //����1���ձ�־
extern u8 di_zhi;		       //�豸��ַ


void USART1_Config(void);   //��ʼ�� ����USART1
void USART2_Config(void);   //��ʼ�� ����USART2
void USART3_Config(void);   //��ʼ�� ����USART3
void UART4_Config(void);    //��ʼ�� ����UART4
void UART5_Config(void);    //��ʼ�� ����UART5
void RS485_SendByte(unsigned char SendData);	  //����һ���ֽ�����

#endif
