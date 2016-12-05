#include "MY_time_Conf.h"


void Timer2_Init(u16 arr,u16 psc)  //��ʱ��2��ʼ������
{
	TIM_TimeBaseInitTypeDef   TIM_TimeBaseStructure;  //�������ö�ʱ���Ľṹ�����
	
	//��ʱ��2�⺯����ʼ�����֣�
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //ʹ��TIM2ʱ��
	TIM_DeInit(TIM2);	            //������TIMx�Ĵ�������Ϊȱʡֵ 
	TIM_InternalClockConfig(TIM2);  //��ʱ��ʱ��Դ��ѡ���ڲ�ʱ��
	/*��������*/
	TIM_TimeBaseStructure.TIM_Period = arr - 1;                     //�趨�������Զ���װֵ  
	TIM_TimeBaseStructure.TIM_Prescaler = psc - 1;    	            //Ԥ��Ƶ,��ֵ+1Ϊ��Ƶ�ĳ���
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;  	                //����ʱ�ӷָ�  ������Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 	//���ϼ���
	TIM2->CR1  &= ~(1<<7);   //�Զ���װARR���ֵû�л���,��ʱ����������ʱ��Ч��
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);					//��ʼ��

	TIM_Cmd(TIM2, ENABLE);						 //ʹ�ܶ�ʱ��2����ʼ��ʱ
	//TIM_Cmd(TIM2, DISABLE);						 //��ʱ������ʹ�ܶ�ʱ��2
	TIM_PrescalerConfig(TIM2, psc - 1, TIM_PSCReloadMode_Immediate);//�ö�ʱ��Ԥ��Ƶֵ����װ��
	TIM_ClearFlag(TIM2,TIM_FLAG_Update);     //����жϱ�־
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE); //ʹ�ܶ�ʱ���ж�
}

void Timer3_Init(u16 arr,u16 psc)  //��ʱ��3��ʼ������
{
	TIM_TimeBaseInitTypeDef   TIM_TimeBaseStructure;  //�������ö�ʱ���Ľṹ�����
	
	//��ʱ��3�⺯����ʼ�����֣�
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //ʹ��TIM3ʱ��
	TIM_DeInit(TIM3);	            //������TIMx�Ĵ�������Ϊȱʡֵ 
	TIM_InternalClockConfig(TIM3);  //��ʱ��ʱ��Դ��ѡ���ڲ�ʱ��
	/*��������*/
	TIM_TimeBaseStructure.TIM_Period = arr - 1;                     //�趨�������Զ���װֵ  
	TIM_TimeBaseStructure.TIM_Prescaler = psc - 1;    	            //Ԥ��Ƶ,��ֵ+1Ϊ��Ƶ�ĳ���
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;  	                //����ʱ�ӷָ�  ������Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 	//���ϼ���
	TIM3->CR1  &= ~(1<<7);   //�Զ���װARR���ֵû�л���,��ʱ����������ʱ��Ч��
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);					//��ʼ��

	TIM_Cmd(TIM3, ENABLE);						 //ʹ�ܶ�ʱ��3����ʼ��ʱ
	//TIM_Cmd(TIM3, DISABLE);						 //��ʱ������ʹ�ܶ�ʱ��3
	TIM_PrescalerConfig(TIM3, psc - 1, TIM_PSCReloadMode_Immediate);//�ö�ʱ��Ԥ��Ƶֵ����װ��
	TIM_ClearFlag(TIM3,TIM_FLAG_Update);     //����жϱ�־
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); //ʹ�ܶ�ʱ���ж�
}

void Timer7_Init(u16 arr,u16 psc)  //��ʱ��7��ʼ������
{
	TIM_TimeBaseInitTypeDef   TIM_TimeBaseStructure;  //�������ö�ʱ���Ľṹ�����
	
	//��ʱ��7�⺯����ʼ�����֣�
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE); //ʹ��TIM7ʱ��
	TIM_DeInit(TIM7);	            //������TIMx�Ĵ�������Ϊȱʡֵ 
	TIM_InternalClockConfig(TIM7);  //��ʱ��ʱ��Դ��ѡ���ڲ�ʱ��
	/*��������*/
	TIM_TimeBaseStructure.TIM_Period = arr - 1;                     //�趨�������Զ���װֵ  
	TIM_TimeBaseStructure.TIM_Prescaler = psc - 1;    	            //Ԥ��Ƶ,��ֵ+1Ϊ��Ƶ�ĳ���
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;  	                //����ʱ�ӷָ�  ������Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 	//���ϼ���
	TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure);					//��ʼ��

	TIM_Cmd(TIM7, ENABLE);						 //ʹ�ܶ�ʱ��7����ʼ��ʱ
	TIM_PrescalerConfig(TIM7, psc - 1, TIM_PSCReloadMode_Immediate);//�ö�ʱ��Ԥ��Ƶֵ����װ��
	TIM_ClearFlag(TIM7,TIM_FLAG_Update);     //����жϱ�־
	TIM_ITConfig(TIM7,TIM_IT_Update,ENABLE); //ʹ�ܶ�ʱ���ж�
}



//ͨ�ö�ʱ���жϳ�ʼ��
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//����ʹ�õ��Ƕ�ʱ��3!
/*
void Timerx_Init(u16 arr,u16 psc)
{
	//TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	
	//��ʱ��2��ʼ�����֣�
//	RCC->APB1ENR |= 1<<0;  //��ͨ�ö�ʱ��TIM2ʱ��
//	
//	TIM2->ARR = arr;       //�趨�������Զ���װֵ//arr=10�պ�1ms    
//	TIM2->PSC = psc;       //Ԥ��Ƶ��7200,�õ�10Khz�ļ���ʱ�� 72MHz/7200=10KHz=0.1ms=100us
//	TIM2->DIER |= 1<<0;    //��������ж�				
//	TIM2->DIER |= 1<<6;    //�������ж�	   
//	TIM2->CR1  |= 0x01;    //ʹ�ܶ�ʱ��2 

	//��ʱ��3��ʼ�����֣�
//	RCC->APB1ENR |= 1<<1;  //��ͨ�ö�ʱ��TIM3ʱ�� 
//	   
// 	TIM3->ARR = arr;       //�趨�������Զ���װֵ//arr=10�պ�1ms    
//	TIM3->PSC = psc;       //Ԥ��Ƶ��7200,�õ�10Khz�ļ���ʱ�� 72MHz/7200=10KHz=0.1ms=100us
//	TIM3->DIER |= 1<<0;    //��������ж�				
//	TIM3->DIER |= 1<<6;    //�������ж�	   
//	TIM3->CR1  |= 0x01;    //ʹ�ܶ�ʱ��3

	//��ʱ��4��ʼ�����֣�
//	RCC->APB1ENR |= 1<<2;  //��ͨ�ö�ʱ��TIM4ʱ��
//	
//	TIM4->ARR = arr;       //�趨�������Զ���װֵ//arr=10�պ�1ms    
//	TIM4->PSC = psc;       //Ԥ��Ƶ��7200,�õ�10Khz�ļ���ʱ�� 72MHz/7200=10KHz=0.1ms=100us
//	TIM4->DIER |= 1<<0;    //��������ж�				
//	TIM4->DIER |= 1<<6;    //�������ж�	   
//	TIM4->CR1  |= 0x01;    //ʹ�ܶ�ʱ��4 

	//��ʱ��5��ʼ�����֣�
//	RCC->APB1ENR |= 1<<3;  //��ͨ�ö�ʱ��TIM5ʱ��
//	
//	TIM5->ARR = arr;       //�趨�������Զ���װֵ//arr=10�պ�1ms    
//	TIM5->PSC = psc;       //Ԥ��Ƶ��7200,�õ�10Khz�ļ���ʱ�� 72MHz/7200=10KHz=0.1ms=100us
//	TIM5->DIER |= 1<<0;    //��������ж�				
//	TIM5->DIER |= 1<<6;    //�������ж�	   
//	TIM5->CR1  |= 0x01;    //ʹ�ܶ�ʱ��5 

	//��ʱ��6��ʼ�����֣�
//	RCC->APB1ENR |= 1<<4;  //��ͨ�ö�ʱ��TIM6ʱ��
//	
//	TIM6->ARR = arr;       //�趨�������Զ���װֵ//arr=10�պ�1ms    
//	TIM6->PSC = psc;       //Ԥ��Ƶ��7200,�õ�10Khz�ļ���ʱ�� 72MHz/7200=10KHz=0.1ms=100us
//	TIM6->DIER |= 1<<0;    //��������ж�				
//	TIM6->DIER |= 1<<6;    //�������ж�	   
//	TIM6->CR1  |= 0x01;    //ʹ�ܶ�ʱ��6 

	//��ʱ��7��ʼ�����֣�
//	RCC->APB1ENR |= 1<<5;  //��ͨ�ö�ʱ��TIM7ʱ��
//	
//	TIM7->ARR = arr;       //�趨�������Զ���װֵ//arr=10�պ�1ms    
//	TIM7->PSC = psc;       //Ԥ��Ƶ��7200,�õ�10Khz�ļ���ʱ�� 72MHz/7200=10KHz=0.1ms=100us
//	TIM7->DIER |= 1<<0;    //��������ж�				
//	TIM7->DIER |= 1<<6;    //�������ж�	   
//	TIM7->CR1  |= 0x01;    //ʹ�ܶ�ʱ��7 
	
	
	
  	//MY_NVIC_Init(1,3,TIM3_IRQChannel,2);//��ռ1�������ȼ�3����2									 
}	 */

