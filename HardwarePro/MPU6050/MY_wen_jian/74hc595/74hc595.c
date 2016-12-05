#include "74HC595.h"

//code unsigned char seg[16] = {
//                   0x28,0xeb,0x32,0xa2,//0,1,2,3,
//                   0xe1,0xa4,0x24,0xea,//4,5,6,7,
//                   0x20,0xa0,0xff,0x70,//8,9,��,P,             10��  11P  12-  13E
//                   0xf7,0x34,0x34,0x71 //-,E, , ,
//                             };

const u8 seg[13] = {
                   0x28,0xeb,0x32,0xa2, //0,1,2,3,
                   0xe1,0xa4,0x24,0xea, //4,5,6,7,
                   0x20,0xa0,0xf7,0xdf, //8,9,-,.,
                   0xff                 //��
                             };

u8 disp_buff[2];        //���建��
u8 dig_buff1=1, dig_buff2=2, dig_buff3=3, dig_buff4=4,         //ÿһλ��ʾ�Ļ��壬���жϷ���
   dig_buff5=5, dig_buff6=6, dig_buff7=7, dig_buff8=8;

u8 num = 1;


void GPIO_Configuration_74HC595(void) //74HC595�˿�����
{
	GPIO_InitTypeDef   GPIO_InitStructure;   //������ΪGPIO_InitStructure�Ľṹ�����ͱ���
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //��GPIOB��ʱ�ӣ���ʹ�ܡ�
	
	//����PB�ڣ�
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;              //ѡ���ĸ�IO�� ��ѡ��PB567��
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		             //�趨IO�ڵ�ģʽΪ���������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	                 //�趨IO�ڵ�����ٶ�Ϊ50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);	                             //��ʼ��GPIOB
}

void buff_to_595(void)     //������
{
   u8 char_seg;     //����ʾ����ܵ���ֵ
   char i;
   rclk=0;

      char_seg=disp_buff[1];   //595��8λ�����ڿ���λ
      for(i=0;i<8;i++)         //�ѵ�Ƭ���ڵ���ֵת��Ϊ�������ݴ��͸�595����595�Զ��ٽ�����ת����
      {
         srclk=0;
         ser=char_seg&0x01;        //�ȷ������λ
         srclk=1;
         char_seg=char_seg>>1;
      }

      char_seg=disp_buff[0];   //595��8λ���ڿ��ƶ�
      for(i=0;i<8;i++)         //�ѵ�Ƭ���ڵ���ֵת��Ϊ�������ݴ��͸�595����595�Զ��ٽ�����ת����
      {
         srclk=0;
         ser=char_seg&0x01;       //�ȷ������λ
         srclk=1;
         char_seg=char_seg>>1;
      }

   rclk=1;      //����595�������ֵ���������ʾ
}

void disp_bit(unsigned char num, unsigned char dig)   //λ��ʾ��Ҫ��ʾ���ַ�num�ڵ�digλ
{
   switch(dig)
   {
       case 1:   disp_buff[1]=0xfb;    break;
       case 2:   disp_buff[1]=0xfd;    break;
       case 3:   disp_buff[1]=0xfe;    break;
       case 4:   disp_buff[1]=0xf7;    break;
       case 5:   disp_buff[1]=0xef;    break;
       case 6:   disp_buff[1]=0xdf;    break;
       case 7:   disp_buff[1]=0xbf;    break;
       case 8:   disp_buff[1]=0x7f;    break;
       default: break;
   }

   disp_buff[0]=seg[num];
   buff_to_595();
}


void disp_num3(u32 num)  //����ʾ�������4λ�������
{
    dig_buff1=num/1000%10; dig_buff2=num/100%10; dig_buff3=num/10%10; dig_buff4=num%10;
    //dig_buff2=num/100%10;dig_buff3=num/10%10; dig_buff4=num%10;
}

void disp_num4(u32 num)  //����ʾ�������4λС�����
{
    dig_buff5=num/1000%10; dig_buff6=num/100%10; dig_buff7=num/10%10; dig_buff8=num%10;
}


void sao_miao_xian_shi(void)
{
    switch(num)         //��λɨ�������
    {
        case 1:  disp_bit(dig_buff1, 1);        break;
        case 2:  disp_bit(dig_buff2, 2);        break;
        case 3:  disp_bit(dig_buff3, 3);        break;
        case 4:  disp_bit(dig_buff4, 4);        break;
        case 5:  disp_bit(dig_buff5, 5);        break;
        case 6:  disp_bit(dig_buff6, 6);        break;
        case 7:  disp_bit(dig_buff7, 7);        break;
        case 8:  disp_bit(dig_buff8, 8);        break;
        default:  break;
    }

    num ++;
    if(num > 8)
    {
        num = 1;
    }
}

