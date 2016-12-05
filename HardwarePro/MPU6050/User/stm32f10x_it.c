/**
  ******************************************************************************
  * @file    GPIO/JTAG_Remap/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and peripherals
  *          interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "sys.h"
#include "string.h"
//#include "uart_1.h"
//#include "dma.h"
//#include "RS485.h"
//#include "74hc595.h"

//u8 t = 0;	 //������ʱ���� ������
//u8 he = 0;	//У���
//
//extern u8 f;    //������,����1׼�����ͱ�־
//
//#define led_PB13   PBout(13)	   //λ�󶨣�λ����PB13����ΪLED����������ٶ����
//#define feng      PBout(14)	   //λ�󶨣�λ����PB14����ΪLED���(������)�������ٶ����
//
//#define CLK1   PDout(0)
//#define CWW1   PDout(1)
//#define CLK2   PDout(2)
//#define CWW2   PDout(3)
//
//u8 buff[5] = {0,0,0,0,0}; //����
//u8 p = 0;  //����
//u8 LR_uart_buf = 0;
//u8 UD_uart_buf = 0;
//u8 fang_xiang = 0;
//u8 Led_T = 0; //LED����ʱ�����
////u8 Time2_OK = 0;  //��ʱ���ж���ɱ�־

unsigned char Re_buf[11],temp_buf[11],counter=0;
unsigned char sign,t,he;

static unsigned char Temp[11];





/** @addtogroup STM32F10x_StdPeriph_Examples
  * @{
  */

/** @addtogroup GPIO_JTAG_Remap
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSV_Handler exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}

void WWDG_IRQHandler(void)		 //���ڶ�ʱ���жϷ�����
{
}

void PVD_IRQHandler(void)		 //����EXTI�ĵ�Դ��ѹ��⣨PVD���жϷ�����
{
}

void TAMPER_IRQHandler(void)	 //�������жϷ�����
{
}

void RTC_IRQHandler(void)		 //ʵʱʱ�ӣ�RTC��ȫ���жϷ�����
{

}

void FLASH_IRQHandler(void)		 //����ȫ���жϷ�����
{
}

void RCC_IRQHandler(void)		 //��λ��ʱ�ӿ��ƣ�RCC���жϷ�����
{
}

void EXTI0_IRQHandler(void)		 //EXTI��0�жϷ�����
{

}

void EXTI1_IRQHandler(void)		 //EXTI��1�жϷ�����
{

}

void EXTI2_IRQHandler(void)		 //EXTI��2�жϷ�����
{
}

void EXTI3_IRQHandler(void)		 //EXTI��3�жϷ�����
{
}

void EXTI4_IRQHandler(void)		 //EXTI��4�жϷ�����
{
 
}

void DMA1_Channel1_IRQHandler(void)	   //DMA1ͨ��1ȫ���жϷ�����
{
}

void DMA1_Channel2_IRQHandler(void)	   //DMA1ͨ��2ȫ���жϷ�����
{
}

void DMA1_Channel3_IRQHandler(void)	   //DMA1ͨ��3ȫ���жϷ�����
{
}

void DMA1_Channel4_IRQHandler(void)	   //DMA1ͨ��4ȫ���жϷ�����
{
//	//�ж��Ƿ�ΪDMA��������ж�
//	if(DMA_GetFlagStatus(DMA1_FLAG_TC4)==SET) 
//	{  	
//		DMA_ClearFlag(DMA2_FLAG_TC4);//���ͨ��4������ɱ�־ 
//	}	
}

void DMA1_Channel5_IRQHandler(void)	   //DMA1ͨ��5ȫ���жϷ�����
{
//	if(DMA_GetITStatus(DMA1_IT_TC5))
// 	{
//	    //DataCounter = DMA_GetCurrDataCounter(DMA1_Channel5);//��ȡʣ�೤��,һ�㶼Ϊ0,������
//	    DMA_ClearITPendingBit(DMA1_IT_GL5);	//���ȫ���жϱ�־										     
//		//ת���ɲ���BUF
//		if(Free_Buf_No==BUF_NO1) //���BUF1���У���DMA�������ݸ�ֵ��BUF1
//		{	
//			DMA_InitStructure.DMA_MemoryBaseAddr = (u32)USART1_DMA_Buf1;
//			DMA_Init(DMA1_Channel5, &DMA_InitStructure);
//			Free_Buf_No=BUF_NO2;
//		}
//		else  //���BUF2���У���DMA�������ݸ�ֵ��BUF2
//		{
//			DMA_InitStructure.DMA_MemoryBaseAddr = (u32)USART1_DMA_Buf2;
//			DMA_Init(DMA1_Channel5, &DMA_InitStructure);
//			Free_Buf_No=BUF_NO1;
//		}
//		Buf_Ok=TRUE;	   //��׼���õ�������
// 	}
}

void DMA1_Channel6_IRQHandler(void)	   //DMA1ͨ��6ȫ���жϷ�����
{
}

void DMA1_Channel7_IRQHandler(void)	   //DMA1ͨ��7ȫ���жϷ�����
{
}

void ADC1_2_IRQHandler(void)		   //ADCȫ���жϷ�����
{
    //Get injected channel1 converted value  // ADC_GetConversionValue(ADC1);
 //     ADC_ConvertedValue = ADC_GetInjectedConversionValue(ADC1, ADC_InjectedChannel_1);
 //     ADC_ClearITPendingBit(ADC1, ADC_IT_JEOC); // ���ADCx���жϴ�����λ ��

/*  GPIO_WriteBit(GPIOB,GPIO_Pin_8,(BitAction)(1-GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_8)));
    ADC_ClearITPendingBit(ADC1, ADC_IT_AWD); // ���ADC1��AWDOG�ж����δ���λ ��    */

    /* Clear ADC1 JEOC pending interrupt bit */
  //    ADC_ClearITPendingBit(ADC1, ADC_IT_JEOC);
  //    ADC_ConvertedValue = ADC_GetInjectedConversionValue(ADC1, ADC_InjectedChannel_1);
}

void USB_HP_CAN_TX_IRQHandler(void)	   //USB�����ȼ���CAN�����жϷ�����
{
}

void USB_LP_CAN_RX0_IRQHandler(void)   //USB�����ȼ���CAN����0�жϷ�����
{
}

void CAN_RX1_IRQHandler(void)		   //CAN����1�жϷ�����
{
}

void CAN_SCE_IRQHandler(void)		   //CAN SCE�жϷ�����
{
}

void EXTI9_5_IRQHandler(void)		   //�ⲿ�ж�9�ߡ�9:5���жϷ�����
{
//	if(EXTI_GetITStatus(EXTI_Line9) != RESET) 
//	{
//     //����жϴ������
////		t = !t;	   //ȡ����־λ
////		if(t == 1)
////			
////			GPIO_ResetBits(GPIOB , GPIO_Pin_1);		  //һ��λ����PB1������͵�ƽ����LED��
////		else
////	 		GPIO_SetBits(GPIOB, GPIO_Pin_1);	      // һ��λ���� PB1������ߵ�ƽ�ر�LED��
//
//		led_PB13 = ~led_PB13;	   //ȡ��
//	
//		EXTI_ClearFlag(EXTI_Line9);			          //����жϱ�־�����룩
//		EXTI_ClearITPendingBit(EXTI_Line9);			  //����жϹ���
//	 }
}

void TIM1_BRK_IRQHandler(void)		   //��ʱ��1�Ͽ��жϷ�����
{
}

void TIM1_UP_IRQHandler(void)		   //��ʱ��1�����жϷ�����
{
}

void TIM1_TRG_COM_IRQHandler(void)	   //��ʱ��1������ͨ���жϷ�����
{
}

void TIM1_CC_IRQHandler(void)		   //��ʱ��1����Ƚ��жϷ�����
{
}

void TIM2_IRQHandler(void)			   //��ʱ��2ȫ���жϷ�����
{
//	if(TIM2->SR & 0X0001)//����ж�
//	{	
//	    //����жϴ������
////		t = !t;	   //ȡ����־λ
////		if(t == 1)
////			
////			GPIO_ResetBits(GPIOB , GPIO_Pin_1);		  //һ��λ����PB1������͵�ƽ����LED��
////		else
////	 		GPIO_SetBits(GPIOB, GPIO_Pin_1);	      // һ��λ���� PB1������ߵ�ƽ�ر�LED��
//		
//		CLK1 = ~CLK1;
//	}				   
//	TIM2->SR &= ~(1<<0);//����жϱ�־λ
//	TIM_Cmd(TIM2, DISABLE);						 //�ض�ʱ��2����main�����ڴ�
//	
//	//Time2_OK = 1;
}

void TIM3_IRQHandler(void)			   //��ʱ��3ȫ���жϷ�����
{
//	if(TIM3->SR & 0X0001)//����ж�
//	{	
//	    //����жϴ������
////		t = !t;	   //ȡ����־λ
////		if(t == 1)
////			
////			GPIO_ResetBits(GPIOB , GPIO_Pin_1);		  //һ��λ����PB1������͵�ƽ����LED��
////		else
////	 		GPIO_SetBits(GPIOB, GPIO_Pin_1);	      // һ��λ���� PB1������ߵ�ƽ�ر�LED��
//		
//		CLK2 = ~CLK2;
//	}				   
//	TIM3->SR &= ~(1<<0);//����жϱ�־λ
//	TIM_Cmd(TIM3, DISABLE);						 //�ض�ʱ��3����main�����ڴ�
}

void TIM4_IRQHandler(void)			   //��ʱ��4ȫ���жϷ�����
{
//	if(TIM4->SR & 0X0001)//����ж�
//	{	
//	    //����жϴ������
//		t = !t;	   //ȡ����־λ
//		if(t == 1)
//			
//			GPIO_ResetBits(GPIOB , GPIO_Pin_1);		  //һ��λ����PB1������͵�ƽ����LED��
//		else
//	 		GPIO_SetBits(GPIOB, GPIO_Pin_1);	      // һ��λ���� PB1������ߵ�ƽ�ر�LED��			    				   				     	    	
//	}				   
//	TIM4->SR &= ~(1<<0);//����жϱ�־λ
}

void I2C1_EV_IRQHandler(void)		   //I2C1�¼��жϷ�����
{
}

void I2C1_ER_IRQHandler(void)		   //I2C1�����жϷ�����
{
}

void I2C2_EV_IRQHandler(void)		   //I2C2�¼��жϷ�����
{
}

void I2C2_ER_IRQHandler(void)		   //I2C2�����жϷ�����
{
}

void SPI1_IRQHandler(void)			   //SPI1ȫ���жϷ�����
{
}

void SPI2_IRQHandler(void)			   //SPI2ȫ���жϷ�����
{
}

void USART1_IRQHandler(void)		   //����1ȫ���жϷ�����
{
//	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //�����ж���Ч,���������ݼĴ�����
//  	{
//    	//buff_485[0] = USART_ReceiveData(USART1);	//��������
//		switch(uart_1)
//        {
//            case 0:
//				buff_485[0] = USART_ReceiveData(USART1);	//��������
//                if((buff_485[0] == 0xff) || (buff_485[0] == 0xef) || (buff_485[0] == 0x68))
//				{
//                	uart_1 = 1;
//				} 
//                else
//                    uart_1 = 0;
//                break;
//            case 1:
//                buff_485[1] = USART_ReceiveData(USART1);	//��������
//                uart_1 ++;
//                break;
//            case 2:
//                buff_485[2] = USART_ReceiveData(USART1);	//��������
//                uart_1 ++;
//                break;
//            case 3:
//                buff_485[3] = USART_ReceiveData(USART1);	//��������
//                uart_1 ++;
//                break;
//            case 4:
//                buff_485[4] = USART_ReceiveData(USART1);	//��������
//                uart_1 ++;
//                break;
//            case 5:
//                buff_485[5] = USART_ReceiveData(USART1);	//��������
//                uart_1 ++;
//                break;
//            case 6:
//                buff_485[6] = USART_ReceiveData(USART1);	//��������
//                if((buff_485[0] == 0xff) || (buff_485[0] == 0x68))
//                {
//                    uart_1 = 0;         //������������ݣ�����״̬����
//                    he = 0;
//                    for(t=1; t<6; t++)
//                        he += buff_485[t];             //����У��
//             
//                    if(buff_485[6] == he && buff_485[1] == di_zhi)     //���У����ȷ �ҵ�ַҲ��ȷ
//					{
//						//ming_ling_jie_shi();         //��������
//						if(buff_485[3] == 0x08 )	feng = 0;  //�� ����������
//						//else aa = 0;
//						if(buff_485[2] == 0 && buff_485[3] == 0 && buff_485[4] == 0 && buff_485[5] == 0)  //����ֹͣ�ź�
//						{
//						 	feng = 1;	//�ط�����
//						}
//					}
//					else  //������ȷ
//					{
//					 	for(t = 0;t<9;t++)           //����
//							buff_485[t] = 0;	
//					}
//                } 
//				else if( buff_485[0] == 0xef )
//                    uart_1 ++;
//                break;
//            case 7:
//                buff_485[7] = USART_ReceiveData(USART1);	//��������
//                uart_1 ++;
//                break;
//            case 8:
//                buff_485[8] = USART_ReceiveData(USART1);	//��������
//                uart_1 = 0;
//                he = 0;
//                for(t=1; t<8; t++)
//                    he += buff_485[t];             //����У��

//                if(buff_485[8] == he && buff_485[1] == di_zhi)     //���У����ȷ �ҵ�ַҲ��ȷ
//				{
//					//ming_ling_jie_shi();         //��������
//				}
//				else  //������ȷ
//				{
//				 	for(t = 0;t<9;t++)           //����
//						buff_485[t] = 0;	
//				}
//                break;
//            default:  break;
//        }	 
//  	}



//	if(USART_GetITStatus(USART1, USART_IT_TXE) == SET)      // �����ж���Ч �� 
//  	{   
//		//USART_ClearFlag(USART1, USART_FLAG_TC);                //�崮��1���ͱ�־
//
//		f ++;
//		if(f >= 2)	{f = 0; } // ���USART1�ķ����ж� �� 
//		else  
//		{
//			USART_ClearITPendingBit(USART1, USART_IT_TXE);     // ���USART1�ķ����ж� 
//			USART_SendData(USART1, 0x97);
//		}
//  	}   
}  	 

void USART2_IRQHandler(void)		   //����2ȫ���жϷ�����
{
//	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //�����ж���Ч,���������ݼĴ�����
//  	{
//		Re_buf[counter] = USART_ReceiveData(USART2);	//��������
//		//�������ĳ���
//		if(counter == 0 && Re_buf[0] != 0x55) return;      //�� 0 �����ݲ���֡ͷ������
//		counter++; 
//		if(counter==11) //���յ� 11 ������
//		{ 
//			counter=0; //���¸�ֵ��׼����һ֡���ݵĽ���
//			sign=1;
//			for(t=0; t<11; t++)	temp_buf[t]	= Re_buf[t];
//		}



//	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //�����ж���Ч,���������ݼĴ�����
//	{
//		Re_buf[counter] = USART_ReceiveData(USART2);   //��������
//		if(counter == 0 && Re_buf[0] != 0x55) return;      //�� 0 �����ݲ���֡ͷ������
//		counter++; 
//		if(counter==11) //���յ� 11 ������
//		{ 
//			counter=0; //���¸�ֵ��׼����һ֡���ݵĽ���
//			he = 0;
//            for(t=0; t<10; t++)
//                he += Re_buf[t];             //����У��
//			he = he%256;
//
//            if(Re_buf[10] == he && Re_buf[0] == 0x55)     //���У����ȷ��λsign=1;
//			{
//				for(t=0; t<11; t++)	temp_buf[t]	= Re_buf[t];
//				sign = 1;        //��������
//			}
//
////			sign=1;
////			for(t=0; t<11; t++)	temp_buf[t]	= Re_buf[t];
//		}    
//	}

 
   
   if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //�����ж���Ч,���������ݼĴ�����
     {
      Temp[counter] = USART_ReceiveData(USART2);   //��������
      //�������ĳ���
      //if(counter == 0 && Re_buf[0] != 0x55) return;      //�� 0 �����ݲ���֡ͷ������
	  if(counter == 0 && Temp[0] != 0x55) return;      //�� 0 �����ݲ���֡ͷ������
      counter++; 
      if(counter==11) //���յ� 11 ������
      { 
         memcpy(Re_buf,Temp,11);
         counter=0; //���¸�ֵ��׼����һ֡���ݵĽ���
         sign=1;
      }    
   }




		
//		switch(counter)
//        {
//            case 0:
//				Re_buf[0] = USART_ReceiveData(USART2);	//��������
//                if(Re_buf[0] == 0x55)  counter = 1; 
//                else   counter = 0;   
//                break;
//            case 1:
//                Re_buf[1] = USART_ReceiveData(USART2);	//��������
//                counter = 2;
//                break;
//            case 2:
//                Re_buf[2] = USART_ReceiveData(USART2);	//��������
//                counter = 3;
//                break;
//            case 3:
//                Re_buf[3] = USART_ReceiveData(USART2);	//��������
//                counter = 4;
//                break;
//            case 4:
//                Re_buf[4] = USART_ReceiveData(USART2);	//��������
//                counter = 5;
//                break;
//            case 5:
//                Re_buf[5] = USART_ReceiveData(USART2);	//��������
//                counter = 6;
//                break;
//            case 6:
//                Re_buf[6] = USART_ReceiveData(USART2);	//��������
//                counter = 7;
//                break;
//            case 7:
//                Re_buf[7] = USART_ReceiveData(USART2);	//��������
//                counter = 8;
//                break;
//			case 8:
//                Re_buf[8] = USART_ReceiveData(USART2);	//��������
//                counter = 9;
//                break;
//			case 9:
//                Re_buf[9] = USART_ReceiveData(USART2);	//��������
//                counter = 10;
//                break;
//            case 10:
//                Re_buf[10] = USART_ReceiveData(USART2);	//��������
//                counter = 0;
//                he = 0;
//                for(t=0; t<10; t++)
//                    he += Re_buf[t];             //����У��
//				//he = he%256;
//
//                if(Re_buf[10] == he && Re_buf[0] == 0x55)     //���У����ȷ��λsign=1;
//				{
//					for(t=0; t<11; t++)	temp_buf[t]	= Re_buf[t];
//					sign = 1;        //��������
//				}
//
//                break;
//            default:  break;
//        }	 	
}



void USART3_IRQHandler(void)		   //����3ȫ���жϷ�����
{
//	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)  //�����ж���Ч,���������ݼĴ�����
//  	{
//    	//buff_485[0] = USART_ReceiveData(USART3);	//��������
//		switch(uart_1)
//        {
//            case 0:
//				buff_485[0] = USART_ReceiveData(USART3);	//��������
//                if((buff_485[0] == 0xff) || (buff_485[0] == 0xef) || (buff_485[0] == 0x68))
//				{
//                	uart_1 = 1;
//				} 
//                else
//                    uart_1 = 0;
//                break;
//            case 1:
//                buff_485[1] = USART_ReceiveData(USART3);	//��������
//                uart_1 ++;
//                break;
//            case 2:
//                buff_485[2] = USART_ReceiveData(USART3);	//��������
//                uart_1 ++;
//                break;
//            case 3:
//                buff_485[3] = USART_ReceiveData(USART3);	//��������
//                uart_1 ++;
//                break;
//            case 4:
//                buff_485[4] = USART_ReceiveData(USART3);	//��������
//                uart_1 ++;
//                break;
//            case 5:
//                buff_485[5] = USART_ReceiveData(USART3);	//��������
//                uart_1 ++;
//                break;
//            case 6:
//                buff_485[6] = USART_ReceiveData(USART3);	//��������
//                if((buff_485[0] == 0xff) || (buff_485[0] == 0x68))
//                {
//                    uart_1 = 0;         //������������ݣ�����״̬����
//                    he = 0;
//                    for(t=1; t<6; t++)
//                        he += buff_485[t];             //����У��
//             
//                    if(buff_485[6] == he && buff_485[1] == di_zhi)     //���У����ȷ �ҵ�ַҲ��ȷ
//					{
//						//ming_ling_jie_shi();         //��������
//						if(buff_485[3] == 0x04 )	{feng = 0; LR_uart_buf = buff_485[4];CWW1 = 1;} //�� ������������buff_485[4]��ָ���ٶ�
//						if(buff_485[3] == 0x02 )	{feng = 0; LR_uart_buf = buff_485[4];CWW1 = 0;} //�� ������������buff_485[4]��ָ���ٶ�
//						if(buff_485[3] == 0x08 )	{feng = 0; UD_uart_buf = buff_485[5];CWW2 = 1;} //�� ������������buff_485[5]��ָ���ٶ�
//						if(buff_485[3] == 0x10 )	{feng = 0; UD_uart_buf = buff_485[5];CWW2 = 0;} //�� ������������buff_485[5]��ָ���ٶ�
//						if(buff_485[3] == 0x0C )    //����
//						{
//							fang_xiang = 1;
//							CWW1 = 1;
//							CWW2 = 1;
//							feng = 0;
//							LR_uart_buf = buff_485[4];
//							UD_uart_buf = buff_485[5];
//						}
//						if(buff_485[3] == 0x14 )    //����
//						{
//							fang_xiang = 2;
//							CWW1 = 1;
//							CWW2 = 0;
//							feng = 0;
//							LR_uart_buf = buff_485[4];
//							UD_uart_buf = buff_485[5];
//						}
//						if(buff_485[3] == 0x0A )    //����
//						{
//							fang_xiang = 3;
//							CWW1 = 0;
//							CWW2 = 1;
//							feng = 0;
//							LR_uart_buf = buff_485[4];
//							UD_uart_buf = buff_485[5];
//						}
//						if(buff_485[3] == 0x12 )    //����
//						{
//							fang_xiang = 4;
//							CWW1 = 0;
//							CWW2 = 0;
//							feng = 0;
//							LR_uart_buf = buff_485[4];
//							UD_uart_buf = buff_485[5];
//						}
//						//else aa = 0;
//						if(buff_485[2] == 0 && buff_485[3] == 0 && buff_485[4] == 0 && buff_485[5] == 0)  //����ֹͣ�ź�
//						{
//						 	feng = 1;	//�ط�����
//							LR_uart_buf = 0; //�ٶ�ָ������
//							UD_uart_buf = 0;
//							fang_xiang = 0;
//						}
//					}
//					else  //������ȷ
//					{
//					 	for(t = 0;t<9;t++)           //����
//							buff_485[t] = 0;	
//					}
//                } 
//				else if( buff_485[0] == 0xef )
//                    uart_1 ++;
//                break;
//            case 7:
//                buff_485[7] = USART_ReceiveData(USART3);	//��������
//                uart_1 ++;
//                break;
//            case 8:
//                buff_485[8] = USART_ReceiveData(USART3);	//��������
//                uart_1 = 0;
//                he = 0;
//                for(t=1; t<8; t++)
//                    he += buff_485[t];             //����У��
//
//                if(buff_485[8] == he && buff_485[1] == di_zhi)     //���У����ȷ �ҵ�ַҲ��ȷ
//				{
//					//ming_ling_jie_shi();         //��������
//				}
//				else  //������ȷ
//				{
//				 	for(t = 0;t<9;t++)           //����
//						buff_485[t] = 0;	
//				}
//                break;
//            default:  break;
//        }	 
//  	}
}

void EXTI15_10_IRQHandler(void)		   //�ⲿ�ж�10��15:10���жϷ�����
{
//	if(EXTI_GetITStatus(EXTI_Line10) != RESET) 
//	{
//     //����жϴ������
////		t = !t;	   //ȡ����־λ
////		if(t == 1)
////			
////			GPIO_ResetBits(GPIOB , GPIO_Pin_1);		  //PB1������͵�ƽ����LED1
////		else
////	 		GPIO_SetBits(GPIOB, GPIO_Pin_1);	      // һ��λ���� �ر�LED1
//
//		led_PB13 = ~led_PB13;	   //ȡ��
//	
//		 EXTI_ClearFlag(EXTI_Line10);			          //����жϱ�־�����룩
//	     EXTI_ClearITPendingBit(EXTI_Line10);			  //����жϹ���λ
//	 }
}

void RTCAlarm_IRQHandler(void)		   //����EXTI��RTC�����жϷ�����
{
}

void USBWakeUp_IRQHandler(void)		   //����EXTI�Ĵ�USB���������жϷ�����
{
}

void TIM8_BRK_IRQHandler(void)		   //��ʱ��8�Ͽ��жϷ�����
{
}

void TIM8_UP_IRQHandler(void)		   //��ʱ��8�����жϷ�����
{
}

void TIM8_TRG_COM_IRQHandler(void)	   //��ʱ��8������ͨ���жϷ�����
{
}

void TIM8_CC_IRQHandler(void)		   //��ʱ��8����Ƚ��жϷ�����
{
}

void ADC3_IRQHandler(void)			   //ADC3ȫ���жϷ�����
{
}

void FSMC_IRQHandler(void)			   //FSMCȫ���жϷ�����
{
}

void SDIO_IRQHandler(void)			   //SDIOȫ���жϷ�����
{
}

void TIM5_IRQHandler(void)			   //��ʱ��5ȫ���жϷ�����
{
//	if(TIM5->SR & 0X0001)//����ж�
//	{	
//	    //����жϴ������
//		t = !t;	   //ȡ����־λ
//		if(t == 1)
//			
//			GPIO_ResetBits(GPIOB , GPIO_Pin_1);		  //һ��λ����PB1������͵�ƽ����LED��
//		else
//	 		GPIO_SetBits(GPIOB, GPIO_Pin_1);	      // һ��λ���� PB1������ߵ�ƽ�ر�LED��			    				   				     	    	
//	}				   
//	TIM5->SR &= ~(1<<0);//����жϱ�־λ
}

void SPI3_IRQHandler(void)			   //SPI3ȫ���жϷ�����
{
}

void UART4_IRQHandler(void)			   //����4ȫ���жϷ�����
{
//	if(USART_GetITStatus(UART4, USART_IT_RXNE) != RESET)  //�����ж���Ч,���������ݼĴ�����
//  	{
//    	//buff_485[0] = USART_ReceiveData(UART4);	//��������
//		switch(uart_1)
//        {
//            case 0:
//				buff_485[0] = USART_ReceiveData(UART4);	//��������
//                if((buff_485[0] == 0xff) || (buff_485[0] == 0xef) || (buff_485[0] == 0x68))
//				{
//                	uart_1 = 1;
//				} 
//                else
//                    uart_1 = 0;
//                break;
//            case 1:
//                buff_485[1] = USART_ReceiveData(UART4);	//��������
//                uart_1 ++;
//                break;
//            case 2:
//                buff_485[2] = USART_ReceiveData(UART4);	//��������
//                uart_1 ++;
//                break;
//            case 3:
//                buff_485[3] = USART_ReceiveData(UART4);	//��������
//                uart_1 ++;
//                break;
//            case 4:
//                buff_485[4] = USART_ReceiveData(UART4);	//��������
//                uart_1 ++;
//                break;
//            case 5:
//                buff_485[5] = USART_ReceiveData(UART4);	//��������
//                uart_1 ++;
//                break;
//            case 6:
//                buff_485[6] = USART_ReceiveData(UART4);	//��������
//                if((buff_485[0] == 0xff) || (buff_485[0] == 0x68))
//                {
//                    uart_1 = 0;         //������������ݣ�����״̬����
//                    he = 0;
//                    for(t=1; t<6; t++)
//                        he += buff_485[t];             //����У��
//             
//                    if(buff_485[6] == he && buff_485[1] == di_zhi)     //���У����ȷ �ҵ�ַҲ��ȷ
//					{
//						//ming_ling_jie_shi();         //��������
//						if(buff_485[3] == 0x08 )	feng = 0;  //�� ����������
//						//else aa = 0;
//						if(buff_485[2] == 0 && buff_485[3] == 0 && buff_485[4] == 0 && buff_485[5] == 0)  //����ֹͣ�ź�
//						{
//						 	feng = 1;	//�ط�����
//						}
//					}
//					else  //������ȷ
//					{
//					 	for(t = 0;t<9;t++)           //����
//							buff_485[t] = 0;	
//					}
//                } 
//				else if( buff_485[0] == 0xef )
//                    uart_1 ++;
//                break;
//            case 7:
//                buff_485[7] = USART_ReceiveData(UART4);	//��������
//                uart_1 ++;
//                break;
//            case 8:
//                buff_485[8] = USART_ReceiveData(UART4);	//��������
//                uart_1 = 0;
//                he = 0;
//                for(t=1; t<8; t++)
//                    he += buff_485[t];             //����У��
//
//                if(buff_485[8] == he && buff_485[1] == di_zhi)     //���У����ȷ �ҵ�ַҲ��ȷ
//				{
//					//ming_ling_jie_shi();         //��������
//				}
//				else  //������ȷ
//				{
//				 	for(t = 0;t<9;t++)           //����
//						buff_485[t] = 0;	
//				}
//                break;
//            default:  break;
//        }	 
//  	}
}

void UART5_IRQHandler(void)			   //����5ȫ���жϷ�����
{
//	if(USART_GetITStatus(UART5, USART_IT_RXNE) != RESET)  //�����ж���Ч,���������ݼĴ�����
//  	{
//    	//buff_485[0] = USART_ReceiveData(UART5);	//��������
//		switch(uart_1)
//        {
//            case 0:
//				buff_485[0] = USART_ReceiveData(UART5);	//��������
//                if((buff_485[0] == 0xff) || (buff_485[0] == 0xef) || (buff_485[0] == 0x68))
//				{
//                	uart_1 = 1;
//				} 
//                else
//                    uart_1 = 0;
//                break;
//            case 1:
//                buff_485[1] = USART_ReceiveData(UART5);	//��������
//                uart_1 ++;
//                break;
//            case 2:
//                buff_485[2] = USART_ReceiveData(UART5);	//��������
//                uart_1 ++;
//                break;
//            case 3:
//                buff_485[3] = USART_ReceiveData(UART5);	//��������
//                uart_1 ++;
//                break;
//            case 4:
//                buff_485[4] = USART_ReceiveData(UART5);	//��������
//                uart_1 ++;
//                break;
//            case 5:
//                buff_485[5] = USART_ReceiveData(UART5);	//��������
//                uart_1 ++;
//                break;
//            case 6:
//                buff_485[6] = USART_ReceiveData(UART5);	//��������
//                if((buff_485[0] == 0xff) || (buff_485[0] == 0x68))
//                {
//                    uart_1 = 0;         //������������ݣ�����״̬����
//                    he = 0;
//                    for(t=1; t<6; t++)
//                        he += buff_485[t];             //����У��
//             
//                    if(buff_485[6] == he && buff_485[1] == di_zhi)     //���У����ȷ �ҵ�ַҲ��ȷ
//					{
//						//ming_ling_jie_shi();         //��������
//						if(buff_485[3] == 0x08 )	feng = 0;  //�� ����������
//						//else aa = 0;
//						if(buff_485[2] == 0 && buff_485[3] == 0 && buff_485[4] == 0 && buff_485[5] == 0)  //����ֹͣ�ź�
//						{
//						 	feng = 1;	//�ط�����
//						}
//					}
//					else  //������ȷ
//					{
//					 	for(t = 0;t<9;t++)           //����
//							buff_485[t] = 0;	
//					}
//                } 
//				else if( buff_485[0] == 0xef )
//                    uart_1 ++;
//                break;
//            case 7:
//                buff_485[7] = USART_ReceiveData(UART5);	//��������
//                uart_1 ++;
//                break;
//            case 8:
//                buff_485[8] = USART_ReceiveData(UART5);	//��������
//                uart_1 = 0;
//                he = 0;
//                for(t=1; t<8; t++)
//                    he += buff_485[t];             //����У��
//
//                if(buff_485[8] == he && buff_485[1] == di_zhi)     //���У����ȷ �ҵ�ַҲ��ȷ
//				{
//					//ming_ling_jie_shi();         //��������
//				}
//				else  //������ȷ
//				{
//				 	for(t = 0;t<9;t++)           //����
//						buff_485[t] = 0;	
//				}
//                break;
//            default:  break;
//        }	 
//  	}
}

void TIM6_IRQHandler(void)			   //��ʱ��6ȫ���жϷ�����
{
//	if(TIM6->SR & 0X0001)//����ж�
//	{	
//	    //����жϴ������
//		t = !t;	   //ȡ����־λ
//		if(t == 1)
//			
//			GPIO_ResetBits(GPIOB , GPIO_Pin_1);		  //һ��λ����PB1������͵�ƽ����LED��
//		else
//	 		GPIO_SetBits(GPIOB, GPIO_Pin_1);	      // һ��λ���� PB1������ߵ�ƽ�ر�LED��			    				   				     	    	
//	}				   
//	TIM6->SR &= ~(1<<0);//����жϱ�־λ
}

void TIM7_IRQHandler(void)			   //��ʱ��7ȫ���жϷ�����
{
//	if(TIM7->SR & 0X0001)//����ж�
//	{	
//	    //����жϴ������
////		t = !t;	   //ȡ����־λ
////		if(t == 1)
////			
////			GPIO_ResetBits(GPIOB , GPIO_Pin_1);		  //һ��λ����PB1������͵�ƽ����LED��
////		else
////	 		GPIO_SetBits(GPIOB, GPIO_Pin_1);	      // һ��λ���� PB1������ߵ�ƽ�ر�LED��
//
//		//GPIO_WriteBit(GPIOB, GPIO_Pin_1, (BitAction)((1-GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_1)))); /* LED1 ȡ�� */	
//		
//		//led_PB13 = ~led_PB13;	   //ȡ��
//		
//		//CLK1 = ~CLK1;
//		//CLK2 = ~CLK2;
//		sao_miao_xian_shi();               //2msɨ��һ�������
//		
//		Led_T ++; //200msLED����
//		
//	}				   
//	TIM7->SR &= ~(1<<0);//����жϱ�־λ
}

void DMA2_Channel1_IRQHandler(void)	   //DMA2ͨ��1ȫ���жϷ�����
{
}

void DMA2_Channel2_IRQHandler(void)	   //DMA2ͨ��2ȫ���жϷ�����
{
}

void DMA2_Channel3_IRQHandler(void)	   //DMA2ͨ��3ȫ���жϷ�����
{
}

void DMA2_Channel4_5_IRQHandler(void)  //DMA2ͨ��4��DMA2ͨ��5ȫ���жϷ�����
{
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
