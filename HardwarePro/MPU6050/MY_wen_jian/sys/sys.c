#include "sys.h"

//����ϵͳʱ��
void RCC_Configuration(void)
{
	ErrorStatus HSEStartUpStatus;                    //�����ⲿ���پ�������״̬ö�ٱ���

	RCC_DeInit();                                    //��λRCC�ⲿ�豸�Ĵ�����Ĭ��ֵ
	RCC_HSEConfig(RCC_HSE_ON);                       //���ⲿ���پ���
	HSEStartUpStatus = RCC_WaitForHSEStartUp();      //�ȴ��ⲿ����ʱ��׼����
	if(HSEStartUpStatus == SUCCESS)                  //�ⲿ����ʱ���Ѿ�׼���
	{
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable); //����FLASHԤ�����幦�ܣ�����FLASH�Ķ�ȡ�����г����б�����÷�.λ�ã�RCC��ʼ���Ӻ������棬ʱ������֮��
		FLASH_SetLatency(FLASH_Latency_2);                    //flash��������ʱ
			
		RCC_HCLKConfig(RCC_SYSCLK_Div1);               //����AHB(HCLK)ʱ�ӵ���==SYSCLK
		RCC_PCLK2Config(RCC_HCLK_Div1);                //����APB2(PCLK2)��==AHBʱ��
		RCC_PCLK1Config(RCC_HCLK_Div2);                //����APB1(PCLK1)��==AHB1/2ʱ��
			 
		RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);  //����PLLʱ�� == �ⲿ���پ���ʱ�� * 9 = 72MHz
		RCC_PLLCmd(ENABLE);                                   //ʹ��PLLʱ��
   
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)    //�ȴ�PLLʱ�Ӿ���
		{
		}
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);            //����ϵͳʱ�� = PLLʱ��
		while(RCC_GetSYSCLKSource() != 0x08)                  //���PLLʱ���Ƿ���Ϊϵͳʱ��
		{
		}
	}
}

//IO������
//�÷������ĸ����Ǹ�
void GPIO_Configuration(void)
{
	GPIO_InitTypeDef   GPIO_InitStructure;   //������ΪGPIO_InitStructure�Ľṹ�����ͱ���

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //��GPIOB��ʱ�ӣ���ʹ�ܡ�
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);  //��GPIOC��ʱ�ӣ���ʹ�ܡ�
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);  //��GPIOD��ʱ�ӣ���ʹ�ܡ�
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //��GPIOA��ʱ�ӣ���ʹ�ܡ�
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOD, ENABLE);  //��GPIOB��GPIOD��ʱ�ӣ���ʹ�ܡ�
	//����PD10�ڣ�
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_9;              //ѡ���ĸ�IO�� ��ѡ��PD9�ں�PD10��
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU ;                       //�趨IO�ڵ�ģʽΪ�������몽
//	//GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	                 //���IO�ڵ�ģʽ�����룬GPIO_Speed���Բ���ֵ
//	GPIO_Init(GPIOD, &GPIO_InitStructure);	/* PC6 */                    //��ʼ��GPIOD

	//����PA�ڣ�
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;              //ѡ���ĸ�IO�� ��ѡ��PA0�ں�PA1��
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		             //�趨IO�ڵ�ģʽΪ���������
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;	                 //�趨IO�ڵ�����ٶ�Ϊ2MHz
//	GPIO_Init(GPIOA, &GPIO_InitStructure);	/* PC6 */                    //��ʼ��GPIOD
	
	//����PD�ڣ�
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;              //ѡ���ĸ�IO�� ��ѡ��PD0123��
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		             //�趨IO�ڵ�ģʽΪ���������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	                 //�趨IO�ڵ�����ٶ�Ϊ50MHz
	GPIO_Init(GPIOD, &GPIO_InitStructure);	                             //��ʼ��GPIOD

	//����PD�ڣ�
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;              //ѡ���ĸ�IO�� ��ѡ��PD2��
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		             //�趨IO�ڵ�ģʽΪ���������
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;	                 //�趨IO�ڵ�����ٶ�Ϊ2MHz
//	GPIO_Init(GPIOD, &GPIO_InitStructure);	/* PC6 */                    //��ʼ��GPIOD

	//����3��LED�ƣ�PB12��PB13��PB14��
	GPIO_SetBits(GPIOB,  GPIO_Pin_0 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14);	         //�ر�3��LED�ƣ�PB12��PB13��PB14������ߵ�ƽ
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14;	             //ѡ��PB12��PB13��PB14
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		             //�趨IO�ڵ�ģʽΪ�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;		             //�趨IO�ڵ�����ٶ�Ϊ2MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);					             //��ʼ��GPIOB
}

//�ж�IO������
//�÷������ĸ����Ǹ�
void EXTI_Configuration(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;						   //����һ���ṹ�����

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE); 		   //��APB2���߸���ʱ��
	
	//�ⲿ�ж���10���ã�
	EXTI_ClearITPendingBit(EXTI_Line10);						   //����жϹ���λ �ⲿ�ж���10
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;		       //ѡ�����жϴ��������¼�����������ѡ������жϴ���
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;	       //������ʽ������ѡ������½��ش���
	EXTI_InitStructure.EXTI_Line = EXTI_Line10;				       //ѡ���ĸ�IO����Ϊ�ж����룬����ѡ�����PD10��
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;					   //ʹ���ж�
	EXTI_Init(&EXTI_InitStructure);							       //����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOD, GPIO_PinSource10);   //ѡ��GPIO�ܽ���Ϊ�ⲿ�ж���·
	//�ⲿ�ж���9���ã�
	EXTI_ClearITPendingBit(EXTI_Line9);						       //����жϹ���λ �ⲿ�ж���9
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;		       //ѡ�����жϴ��������¼�����������ѡ������жϴ���
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;	       //������ʽ������ѡ������½��ش���
	EXTI_InitStructure.EXTI_Line = EXTI_Line9;				       //ѡ���ĸ�IO����Ϊ�ж����룬����ѡ�����PD9��
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;					   //ʹ���ж�
	EXTI_Init(&EXTI_InitStructure);							       //����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOD, GPIO_PinSource9);    //ѡ��GPIO�ܽ���Ϊ�ⲿ�ж���·
}

//�ж����ȼ�����
//�÷������ĸ����Ǹ�
void NVIC_Configuration(void)
{
	NVIC_InitTypeDef    NVIC_InitStructure; 					   //�������������жϵĽṹ�����

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);                //�ж����ȼ�����  ��ռʽ���ȼ�������Ϊ2λ����Ӧ���ȼ�ռ2λ
	
	//�ⲿ�ж���10���ȼ�����
//	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;           //ָ���ж�Դ
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	   //��ռ���ȼ�1
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;             //ָ����Ӧ���ȼ���1
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	               //ʹ���ⲿ�ж�ͨ��
//	NVIC_Init(&NVIC_InitStructure);							       //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
	//�ⲿ�ж���9���ȼ�����
//	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;             //ָ���ж�Դ  
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	   //��ռ���ȼ� ��ʱû��
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;             //ָ����Ӧ���ȼ���2
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	               //ʹ���ⲿ�ж�ͨ��
//	NVIC_Init(&NVIC_InitStructure);							       //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
	//����1�ж����ȼ�����
//	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;              //ͨ������Ϊ����1�ж�  
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	   //��ռ���ȼ�1
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;             //ָ����Ӧ���ȼ���1
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	               //���ж�
//	NVIC_Init(&NVIC_InitStructure);							       //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
	//����1��DMA�����ж����ȼ�����
//	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel4_IRQn;       //ͨ������Ϊ����DMAͨ��4�ж�  
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	   //��ռ���ȼ�1
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;             //ָ����Ӧ���ȼ���1
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	               //���ж�
//	NVIC_Init(&NVIC_InitStructure);							       //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
	//����2�ж����ȼ�����(RS485)
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;			   //ָ���ж�Դ
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	   //��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;             //ָ����Ӧ���ȼ���1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	               //���ж�
	NVIC_Init(&NVIC_InitStructure);							       //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

	//����3�ж����ȼ�����(RS485)
//	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;			   //ָ���ж�Դ
//  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	   //��ռ���ȼ�1
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;             //ָ����Ӧ���ȼ���1
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	               //���ж�
//	NVIC_Init(&NVIC_InitStructure);							       //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

//	//����1��DMA�������ȼ�����
//	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel5_IRQn;       //DMA1ͨ��5�ж� 
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	   //��ռ���ȼ�1
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;             //ָ����Ӧ���ȼ���1
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	               //���ж�
//	NVIC_Init(&NVIC_InitStructure);							       //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

//	//����4�ж����ȼ�����(RS485)
//	NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;			   //ָ���ж�Դ
//  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	   //��ռ���ȼ�1
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;             //ָ����Ӧ���ȼ���1
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	               //���ж�
//	NVIC_Init(&NVIC_InitStructure);							       //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

//	//����5�ж����ȼ�����(RS485)
//	NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;			   //ָ���ж�Դ
//  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	   //��ռ���ȼ�1
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;             //ָ����Ӧ���ȼ���1
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	               //���ж�
//	NVIC_Init(&NVIC_InitStructure);							       //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

	
	//ͨ�ö�ʱ��2�ж����ȼ�����
//	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //TIM2�ж�
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�1��
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //�����ȼ�3��
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
//	NVIC_Init(&NVIC_InitStructure);  //��ʼ��NVIC�Ĵ���	
	
	//ͨ�ö�ʱ��3�ж����ȼ�����
//	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3�ж�
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //��ռ���ȼ�1��
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  //�����ȼ�3��
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
//	NVIC_Init(&NVIC_InitStructure);  //��ʼ��NVIC�Ĵ���
	
	//ͨ�ö�ʱ��4�ж����ȼ�����
//	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  //TIM4�ж�
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //��ռ���ȼ�1��
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //�����ȼ�3��
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
//	NVIC_Init(&NVIC_InitStructure);  //��ʼ��NVIC�Ĵ���	
	
	//ͨ�ö�ʱ��5�ж����ȼ�����
//	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;  //TIM5�ж�
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //��ռ���ȼ�1��
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //�����ȼ�3��
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
//	NVIC_Init(&NVIC_InitStructure);  //��ʼ��NVIC�Ĵ���	
	
	//ͨ�ö�ʱ��6�ж����ȼ�����
//	NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;  //TIM6�ж�
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //��ռ���ȼ�1��
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //�����ȼ�3��
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
//	NVIC_Init(&NVIC_InitStructure);  //��ʼ��NVIC�Ĵ���	
	
	//ͨ�ö�ʱ��7�ж����ȼ�����
//	NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;  //TIM7�ж�
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //��ռ���ȼ�1��
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //�����ȼ�3��
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
//	NVIC_Init(&NVIC_InitStructure);  //��ʼ��NVIC�Ĵ���					 
}



