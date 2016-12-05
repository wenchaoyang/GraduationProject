#ifndef __74HC595_H
#define __74HC595_H

#include "stm32f10x.h"
#include "sys.h"

#define srclk   PBout(5)
#define rclk    PBout(6)
#define ser     PBout(7)

extern u8 num;
extern u8 dig_buff1, dig_buff2, dig_buff3, dig_buff4,         //ÿһλ��ʾ�Ļ��壬���жϷ���
          dig_buff5, dig_buff6, dig_buff7, dig_buff8;

void GPIO_Configuration_74HC595(void);      //74HC595�˿�����
void disp_num3(u32 num);                    //����ʾ�������4λ�������
void disp_num4(u32 num);                    //����ʾ�������4λС�����
void sao_miao_xian_shi(void);               //ɨ�������

#endif

