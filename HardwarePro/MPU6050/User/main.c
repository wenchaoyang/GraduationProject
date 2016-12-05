#include "stm32f10x.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "MY_time_Conf.h"
//#include "uart_1.h"
//#include "dma.h"
//#include "RS485.h"
//#include "74hc595.h"
#include "string.h"
//#include "adc.h"

/**************************
ģ��������Ϣ��
ѡ��оƬ�� stm32f103vc
������Ϣ��stm32f10x_hd.s
�̼��⣺stm32�̼���v3.5
***************************/

#define led_PB12   PBout(12)	   //λ�󶨣�λ����PB12����ΪLED����������ٶ����
//#define led_PB1   PBout(1)	   //λ�󶨣�λ����PB1����ΪLED����������ٶ����
//#define PA9   PAout(10)
//#define CLK1   PDout(0)
//#define CWW1   PDout(1)
//#define CLK2   PDout(2)
//#define CWW2   PDout(3)


//uint8_t i = 0;    //������

float a[3],w[3],angle[3],T;
extern unsigned char Re_buf[11],temp_buf[11],counter;
extern unsigned char sign;

/*************************************************
����: int main(void)
����: main������
����: ��
����: ��
**************************************************/

int main(void)
{
   unsigned char Temp[11];
   u16 ADC_Value1;
   u16 ADC_Value2;

   //u8 i;

   RCC_Configuration();      //��ʼ��ʱ��

//   delay_ms(50);
//   ADC1_Init();
//   delay_ms(50);

   GPIO_Configuration();      //��ʼ��IO�˿�
   delay_init(72);            //��ʼ����ʱ����
   NVIC_Configuration();      //�ж����ȼ���ʼ��

   USART1_Config();   //��ʼ�� ����USART1
   USART2_Config();   //��ʼ�� ����USART2 �����ڽ���MPU6050���ݣ�
   		   
   delay_ms(200);
   printf("hello stm32");
      
   while (1)
   {
      if(sign)
      {  
         memcpy(Temp,Re_buf,11);
         sign=0;
         if(Re_buf[0]==0x55)       //���֡ͷ
         {  
            switch(Re_buf[1])
            {
               case 0x51: //��ʶ������Ǽ��ٶȰ�
                  a[0] = ((short)(Temp[3]<<8 | Temp[2]))/32768.0*16;      //X����ٶ�
                  a[1] = ((short)(Temp[5]<<8 | Temp[4]))/32768.0*16;      //Y����ٶ�
                  a[2] = ((short)(Temp[7]<<8 | Temp[6]))/32768.0*16;      //Z����ٶ�
                  T    = ((short)(Temp[9]<<8 | Temp[8]))/340.0+36.25;      //�¶�
                  break;
               case 0x52: //��ʶ������ǽ��ٶȰ�
                  w[0] = ((short)(Temp[3]<<8| Temp[2]))/32768.0*2000;      //X����ٶ�
                  w[1] = ((short)(Temp[5]<<8| Temp[4]))/32768.0*2000;      //Y����ٶ�
                  w[2] = ((short)(Temp[7]<<8| Temp[6]))/32768.0*2000;      //Z����ٶ�
                  T    = ((short)(Temp[9]<<8| Temp[8]))/340.0+36.25;      //�¶�
                  break;
               case 0x53: //��ʶ������ǽǶȰ�
                  angle[0] = ((short)(Temp[3]<<8| Temp[2]))/32768.0*180;   //X���ת�ǣ�x �ᣩ
                  angle[1] = ((short)(Temp[5]<<8| Temp[4]))/32768.0*180;   //Y�ḩ���ǣ�y �ᣩ
                  angle[2] = ((short)(Temp[7]<<8| Temp[6]))/32768.0*180;   //Z��ƫ���ǣ�z �ᣩ
                  T        = ((short)(Temp[9]<<8| Temp[8]))/340.0+36.25;   //�¶�

//				  ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 1, ADC_SampleTime_239Cycles5 );	//ADC1,ADCͨ��0,�������˳��ֵΪ1,����ʱ��Ϊ239.5����	  			    				
//			      /* Start ADC1 Software Conversion */ 
//				  ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//ʹ��ָ����ADC1�����ת����������
//				  //while(!(ADC1->SR&1<<1));//�ȴ�ת������	 
//				  while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//�ȴ�ת������
//				  ADC_Value1=ADC_GetConversionValue(ADC1);	//�������һ��ADC1�������ת�����
//
//				  ADC_RegularChannelConfig(ADC1, ADC_Channel_7, 1, ADC_SampleTime_239Cycles5 );	//ADC1,ADCͨ��0,�������˳��ֵΪ1,����ʱ��Ϊ239.5����	  			    				
//			      /* Start ADC1 Software Conversion */ 
//				  ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//ʹ��ָ����ADC1�����ת����������
//				  //while(!(ADC1->SR&1<<1));//�ȴ�ת������	 
//				  while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//�ȴ�ת������
//				  ADC_Value2=ADC_GetConversionValue(ADC1);	//�������һ��ADC1�������ת�����

				  printf("D#%d:%d:%d#%d:%d\n\0",(int)(10 * angle[0]),(int)(10 * angle[1]),(int)(10 * angle[2]), ADC_Value1, ADC_Value2);
                  //printf("X��Ƕȣ�%.2f   Y��Ƕȣ�%.2f   Z��Ƕȣ�%.2f\r\n",angle[0],angle[1],angle[2]);
                  break;
               default:  break;
            }
			//printf("X�ǣ�%.2f  Y�ǣ�%.2f  Z�ǣ�%.2f  X�ٶȣ�%.2f  Y�ٶȣ�%.2f  Z�ٶȣ�%.2f\r\n",angle[0],angle[1],angle[2],w[0],w[1],w[2]);
         }
         
      }
      delay_ms(50);
//	   ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 1, ADC_SampleTime_239Cycles5 );	//ADC1,ADCͨ��0,�������˳��ֵΪ1,����ʱ��Ϊ239.5����	  			    				
//      /* Start ADC1 Software Conversion */ 
//	  ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//ʹ��ָ����ADC1�����ת����������
//	  //while(!(ADC1->SR&1<<1));//�ȴ�ת������	 
//	  while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//�ȴ�ת������
//	  ADC_Value=ADC_GetConversionValue(ADC1);	//�������һ��ADC1�������ת�����
//
//	  printf("D#%d:%d:%d#%d:2000\n\0",(int)(10 * angle[0]),(int)(10 * angle[1]),(int)(10 * angle[2]), ADC_Value);
   }
}


/*
int main(void)
{
	
	//u8 i;

	RCC_Configuration();	   //��ʼ��ʱ��
	GPIO_Configuration();	   //��ʼ��IO�˿�
	delay_init(72);			   //��ʼ����ʱ����
	NVIC_Configuration();	   //�ж����ȼ���ʼ��

	USART1_Config();   //��ʼ�� ����USART1
	USART2_Config();   //��ʼ�� ����USART2 �����ڽ���MPU6050���ݣ�
	
	delay_ms(200);

		
	while (1)
	{
		if(sign)
		{  
			sign=0;
//			if(Re_buf[0]==0x55)       //���֡ͷ
//			{  
//				switch(Re_buf[1])
//				{
//					case 0x51: //��ʶ������Ǽ��ٶȰ�
//						a[0] = ((short)(Re_buf[3]<<8 | Re_buf[2]))/32768.0*16;		//X����ٶ�
//						a[1] = ((short)(Re_buf[5]<<8 | Re_buf[4]))/32768.0*16;		//Y����ٶ�
//						a[2] = ((short)(Re_buf[7]<<8 | Re_buf[6]))/32768.0*16;		//Z����ٶ�
//						T    = ((short)(Re_buf[9]<<8 | Re_buf[8]))/340.0+36.25;		//�¶�
//						break;
//					case 0x52: //��ʶ������ǽ��ٶȰ�
//						w[0] = ((short)(Re_buf[3]<<8| Re_buf[2]))/32768.0*2000;		//X����ٶ�
//						w[1] = ((short)(Re_buf[5]<<8| Re_buf[4]))/32768.0*2000;		//Y����ٶ�
//						w[2] = ((short)(Re_buf[7]<<8| Re_buf[6]))/32768.0*2000;		//Z����ٶ�
//						T    = ((short)(Re_buf[9]<<8| Re_buf[8]))/340.0+36.25;		//�¶�
//						break;
//					case 0x53: //��ʶ������ǽǶȰ�
//						angle[0] = ((short)(Re_buf[3]<<8| Re_buf[2]))/32768.0*180;	//X���ת�ǣ�x �ᣩ
//						angle[1] = ((short)(Re_buf[5]<<8| Re_buf[4]))/32768.0*180;	//Y�ḩ���ǣ�y �ᣩ
//						angle[2] = ((short)(Re_buf[7]<<8| Re_buf[6]))/32768.0*180;	//Z��ƫ���ǣ�z �ᣩ
//						T        = ((short)(Re_buf[9]<<8| Re_buf[8]))/340.0+36.25;	//�¶�
//
//						//printf("X��Ƕȣ�%.2f   Y��Ƕȣ�%.2f   Z��Ƕȣ�%.2f\r\n",angle[0],angle[1],angle[2]);
//						printf("%.2f   %.2f   %.2f\r\n",angle[0],angle[1],angle[2]);
//						break;
//					default:  break;
//				}
//			}
			//printf("X�Ƕȣ�%.2f  Y�Ƕȣ�%.2f  Z�Ƕȣ�%.2f  X�ٶȣ�%.2f  Y�ٶȣ�%.2f  Z�ٶȣ�%.2f\r\n",angle[0],angle[1],angle[2],w[0],w[1],w[2]);

//			if(temp_buf[0]==0x55)       //���֡ͷ
//			{  
//				temp_buf[0] = 0;
//				switch(temp_buf[1])
//				{
//					case 0x51: //��ʶ������Ǽ��ٶȰ�
//						a[0] = ((short)(temp_buf[3]<<8 | temp_buf[2]))/32768.0*16;		//X����ٶ�
//						a[1] = ((short)(temp_buf[5]<<8 | temp_buf[4]))/32768.0*16;		//Y����ٶ�
//						a[2] = ((short)(temp_buf[7]<<8 | temp_buf[6]))/32768.0*16;		//Z����ٶ�
//						T    = ((short)(temp_buf[9]<<8 | temp_buf[8]))/340.0+36.25;		//�¶�
//						break;
//					case 0x52: //��ʶ������ǽ��ٶȰ�
//						w[0] = ((short)(temp_buf[3]<<8| temp_buf[2]))/32768.0*2000;		//X����ٶ�
//						w[1] = ((short)(temp_buf[5]<<8| temp_buf[4]))/32768.0*2000;		//Y����ٶ�
//						w[2] = ((short)(temp_buf[7]<<8| temp_buf[6]))/32768.0*2000;		//Z����ٶ�
//						T    = ((short)(temp_buf[9]<<8| temp_buf[8]))/340.0+36.25;		//�¶�
//						break;
//					case 0x53: //��ʶ������ǽǶȰ�
//						angle[0] = ((short)(temp_buf[3]<<8| temp_buf[2]))/32768.0*180;	//X���ת�ǣ�x �ᣩ
//						angle[1] = ((short)(temp_buf[5]<<8| temp_buf[4]))/32768.0*180;	//Y�ḩ���ǣ�y �ᣩ
//						angle[2] = ((short)(temp_buf[7]<<8| temp_buf[6]))/32768.0*180;	//Z��ƫ���ǣ�z �ᣩ
//						T        = ((short)(temp_buf[9]<<8| temp_buf[8]))/340.0+36.25;	//�¶�
//
//						printf("X��Ƕȣ�%.2f   Y��Ƕȣ�%.2f   Z��Ƕȣ�%.2f\r\n",angle[0],angle[1],angle[2]);
//						break;
//					default:  break;
//				}
//			}
		}

		//printf("X��Ƕȣ�%.2f   Y��Ƕȣ�%.2f   Z��Ƕȣ�%.2f\r\n",angle[0],angle[1],angle[2]);
		delay_ms(50);
	}
}	 */

