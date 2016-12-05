#include "RS485.h"


u8 buff_485[9] = {0,0,0,0,0,0,0,0,0};  //����485�źŻ�����
u8 uart_1 = 0;                         //����1���ձ�־
u8 di_zhi = 1;		                   //�豸��ַ





/****** ����1��ʼ�� *************************************************/
void USART1_Config(void)		//��ʼ�� ����USART1
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	/* ��1������GPIO��USART������ʱ�� */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);	//�򿪴��ڸ���ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);   //��PC�˿�ʱ��
	USART_DeInit(USART1);  //��λ����1

	/*����485оƬ��DE��RE����*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 ;	  //ѡ���ĸ�IO�� ��ѡ��PC4�ں�PC5��
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;		  //�趨IO�ڵ�����ٶ�Ϊ10MHz
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		  //�趨IO�ڵ�ģʽΪ�������
    GPIO_Init(GPIOC, &GPIO_InitStructure);					  //��ʼ��GPIOC

	/* ��2������USART1 Tx��GPIO����Ϊ���츴��ģʽ */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;			   //����1���ͽ�
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		   //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	   //����ٶ�50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);				   //��ʼ��GPIOA
														  
	/* ��3������USART Rx��GPIO����Ϊ��������ģʽ   */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;			   //����1���ս�
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  //��������
	//GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);				   //��ʼ��GPIOA

	/* ��4��������USART1����  */
	USART_InitStructure.USART_BaudRate             = 2400;							 //���������ã�2400
	USART_InitStructure.USART_WordLength           = USART_WordLength_8b;			 //����λ�����ã�8λ
	USART_InitStructure.USART_StopBits             = USART_StopBits_1;				 //ֹͣλ���ã�1λ
	USART_InitStructure.USART_Parity               = USART_Parity_No;				 //�Ƿ���żУ�飺��
	USART_InitStructure.USART_HardwareFlowControl  = USART_HardwareFlowControl_None; //Ӳ��������ģʽ���ã�û��ʹ��
	USART_InitStructure.USART_Mode                 = USART_Mode_Rx | USART_Mode_Tx;	 //�����뷢�Ͷ�ʹ��
	USART_Init(USART1, &USART_InitStructure);										 //��ʼ��USART1

    /* ���������ݼĴ�������������ж� */
	//USART_ITConfig(USART1, USART_IT_TXE, ENABLE);  // ʹ��ָ����USART1�����ж� ��
  	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); // ʹ��ָ����USART1�����ж� ��

	/* ��5����ʹ�� USART1�� ������� */
	USART_Cmd(USART1, ENABLE);							   //ʹ�� USART1

    /* �����������1���ֽ��޷���ȷ���ͳ�ȥ������ */
    USART_ClearFlag(USART1, USART_FLAG_TC);                //�崮��1���ͱ�־
	
}

/****** ����2��ʼ�� *************************************************/
void USART2_Config(void)   //��ʼ�� ����USART2
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	/* ʹ�� USART2 ʱ��*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);	//�򿪴��ڸ���ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);   //��PA�˿�ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);   //��PC�˿�ʱ��	 
	/*����485оƬ��DE��RE����*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 ;	  //ѡ���ĸ�IO�� ��ѡ��PC4�ں�PC5��
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;		  //�趨IO�ڵ�����ٶ�Ϊ10MHz
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		  //�趨IO�ڵ�ģʽΪ�������
    GPIO_Init(GPIOC, &GPIO_InitStructure);					  //��ʼ��GPIOC

	/* USART2 ʹ��IO�˿�TX�������� */    
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;				  //ѡ���ĸ�IO�� ��ѡ��PA2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;           //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		  //�趨IO�ڵ�����ٶ�Ϊ50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);    				  //��ʼ��GPIOA
	/* USART2 ʹ��IO�˿�RX�������� */														  
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;				  //ѡ���ĸ�IO�� ��ѡ��PA3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	  //��������
	GPIO_Init(GPIOA, &GPIO_InitStructure);                    //��ʼ��GPIOA
	  
	/* USART2 ����ģʽ���� */
	USART_InitStructure.USART_BaudRate = 2400;	                    //���������ã�2400
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;	    //����λ�����ã�8λ
	USART_InitStructure.USART_StopBits = USART_StopBits_1; 	        //ֹͣλ���ã�1λ
	USART_InitStructure.USART_Parity = USART_Parity_No ;            //�Ƿ���żУ�飺��
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//Ӳ��������ģʽ���ã�û��ʹ��
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //�����뷢�Ͷ�ʹ��
	USART_Init(USART2, &USART_InitStructure);                       //��ʼ��USART2
	
    /*ʹ�ܴ���2�ķ��ͺͽ����ж�*/
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);         // ʹ��ָ����USART2�����ж� ��
	USART_Cmd(USART2, ENABLE);                             // USART2ʹ��

	/* �����������1���ֽ��޷���ȷ���ͳ�ȥ������ */
    USART_ClearFlag(USART2, USART_FLAG_TC);                //�崮��2���ͱ�־

	Clr_DE;		 //DE����׼������
	Clr_RE; 	 //RE����׼������  
}

/****** ����3��ʼ�� *************************************************/
void USART3_Config(void)   //��ʼ�� ����USART3
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	/* ʹ�� USART3 ʱ��*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);	//�򿪴��ڸ���ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);   //��PB�˿�ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);   //��PC�˿�ʱ��	 
	/*����485оƬ��DE��RE����*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 ;	  //ѡ���ĸ�IO�� ��ѡ��PC4�ں�PC5��
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;		  //�趨IO�ڵ�����ٶ�Ϊ10MHz
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		  //�趨IO�ڵ�ģʽΪ�������
    GPIO_Init(GPIOC, &GPIO_InitStructure);					  //��ʼ��GPIOC

	/* USART3 ʹ��IO�˿����� */    
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;				  //ѡ���ĸ�IO�� ��ѡ��PB10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;           //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		  //�趨IO�ڵ�����ٶ�Ϊ50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);    				  //��ʼ��GPIOB
															  
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;				  //ѡ���ĸ�IO�� ��ѡ��PB11
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	  //��������
	GPIO_Init(GPIOB, &GPIO_InitStructure);                    //��ʼ��GPIOA
	  
	/* USART3 ����ģʽ���� */
	USART_InitStructure.USART_BaudRate = 2400;	                    //���������ã�2400
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;	    //����λ�����ã�8λ
	USART_InitStructure.USART_StopBits = USART_StopBits_1; 	        //ֹͣλ���ã�1λ
	USART_InitStructure.USART_Parity = USART_Parity_No ;            //�Ƿ���żУ�飺��
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//Ӳ��������ģʽ���ã�û��ʹ��
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //�����뷢�Ͷ�ʹ��
	USART_Init(USART3, &USART_InitStructure);                       //��ʼ��USART3
	
    /*ʹ�ܴ���3�ķ��ͺͽ����ж�*/
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);         // ʹ��ָ����USART1�����ж� ��
	USART_Cmd(USART3, ENABLE);                             // USART3ʹ��

	/* �����������1���ֽ��޷���ȷ���ͳ�ȥ������ */
    USART_ClearFlag(USART3, USART_FLAG_TC);                //�崮��3���ͱ�־

	Clr_DE;		 //DE����׼������
	Clr_RE; 	 //RE����׼������  
}

/****** ����4��ʼ�� *************************************************/
void UART4_Config(void)   //��ʼ�� ����USART4
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	/* ʹ�� UART4 ʱ��*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);	//�򿪴��ڸ���ʱ��
    //RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);   //��PB�˿�ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);   //��PC�˿�ʱ��	 
	/*����485оƬ��DE��RE����*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 ;	  //ѡ���ĸ�IO�� ��ѡ��PC4�ں�PC5��
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;		  //�趨IO�ڵ�����ٶ�Ϊ10MHz
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		  //�趨IO�ڵ�ģʽΪ�������
    GPIO_Init(GPIOC, &GPIO_InitStructure);					  //��ʼ��GPIOC

	/* UART4 ʹ��IO�˿�TX�������� */    
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;				  //ѡ���ĸ�IO�� ��ѡ��PC10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;           //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		  //�趨IO�ڵ�����ٶ�Ϊ50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);    				  //��ʼ��GPIOC
	/* UART4 ʹ��IO�˿�RX�������� */														  
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;				  //ѡ���ĸ�IO�� ��ѡ��PC11
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	  //��������
	GPIO_Init(GPIOC, &GPIO_InitStructure);                    //��ʼ��GPIOC
	  
	/* UART4 ����ģʽ���� */
	USART_InitStructure.USART_BaudRate = 2400;	                    //���������ã�2400
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;	    //����λ�����ã�8λ
	USART_InitStructure.USART_StopBits = USART_StopBits_1; 	        //ֹͣλ���ã�1λ
	USART_InitStructure.USART_Parity = USART_Parity_No ;            //�Ƿ���żУ�飺��
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//Ӳ��������ģʽ���ã�û��ʹ��
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //�����뷢�Ͷ�ʹ��
	USART_Init(UART4, &USART_InitStructure);                       //��ʼ��UART4
	
    /*ʹ�ܴ���4�ķ��ͺͽ����ж�*/
	USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);         // ʹ��ָ����UART4�����ж� ��
	USART_Cmd(UART4, ENABLE);                             // UART4ʹ��

	/* �����������1���ֽ��޷���ȷ���ͳ�ȥ������ */
    USART_ClearFlag(UART4, USART_FLAG_TC);                //�崮��4���ͱ�־

	Clr_DE;		 //DE����׼������
	Clr_RE; 	 //RE����׼������  
}

/****** ����5��ʼ�� *************************************************/
void UART5_Config(void)   //��ʼ�� ����UART5
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	/* ʹ�� UART5 ʱ��*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);	//�򿪴��ڸ���ʱ��
    //RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);   //��PB�˿�ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);   //��PC�˿�ʱ��	 
	/*����485оƬ��DE��RE����*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 ;	  //ѡ���ĸ�IO�� ��ѡ��PC4�ں�PC5��
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;		  //�趨IO�ڵ�����ٶ�Ϊ10MHz
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		  //�趨IO�ڵ�ģʽΪ�������
    GPIO_Init(GPIOC, &GPIO_InitStructure);					  //��ʼ��GPIOC

	/* UART5 ʹ��IO�˿�TX�������� */    
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;				  //ѡ���ĸ�IO�� ��ѡ��PC12
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;           //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		  //�趨IO�ڵ�����ٶ�Ϊ50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);    				  //��ʼ��GPIOC
	/* UART5 ʹ��IO�˿�RX�������� */														  
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;				  //ѡ���ĸ�IO�� ��ѡ��PD2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	  //��������
	GPIO_Init(GPIOD, &GPIO_InitStructure);                    //��ʼ��GPIOC
	  
	/* UART5 ����ģʽ���� */
	USART_InitStructure.USART_BaudRate = 2400;	                    //���������ã�2400
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;	    //����λ�����ã�8λ
	USART_InitStructure.USART_StopBits = USART_StopBits_1; 	        //ֹͣλ���ã�1λ
	USART_InitStructure.USART_Parity = USART_Parity_No ;            //�Ƿ���żУ�飺��
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//Ӳ��������ģʽ���ã�û��ʹ��
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //�����뷢�Ͷ�ʹ��
	USART_Init(UART5, &USART_InitStructure);                       //��ʼ��UART5
	
    /*ʹ�ܴ���5�ķ��ͺͽ����ж�*/
	USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);         // ʹ��ָ����UART5�����ж� ��
	USART_Cmd(UART5, ENABLE);                             // UART5ʹ��

	/* �����������1���ֽ��޷���ȷ���ͳ�ȥ������ */
    USART_ClearFlag(UART5, USART_FLAG_TC);                //�崮��5���ͱ�־

	Clr_DE;		 //DE����׼������
	Clr_RE; 	 //RE����׼������  
}

void RS485_SendByte(unsigned char SendData)	  //����һ���ֽ�����
{	   
        Set_DE;		 //DE��λ׼������
	    Set_RE;		 //RE��λ׼������
		//DelayNuS(5000);
        USART_SendData(USART3,SendData);
        while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
		//DelayNuS(5000);
	    Clr_DE;		 //DE����׼������
	    Clr_RE; 	 //RE����׼������   
}  



