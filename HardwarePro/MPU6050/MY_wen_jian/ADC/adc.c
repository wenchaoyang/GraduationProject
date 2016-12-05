/******************** (C) COPYRIGHT 2013 CEPARK�๦�ܿ���ѧϰ��********************
 * �ļ���  ��adc.c
 * ����    ��ADCֵӦ�ú�����         
 * ʵ��ƽ̨��CEPARK�๦�ܿ���ѧϰ��
 * Ӳ�����ӣ�----------------------------------------------------
 *          |                                                    |
 *          | PA0 - JP25 �����ⲿ��ѹ(ͨ��һ��������������ѹ����)|
 *          | J1��̽�																					 |
 *          |                                                    |
 *           ----------------------------------------------------
 * ��汾  ��ST3.5.0
**********************************************************************************/
#include "adc.h"

#define ADC1_DR_Address    ((u32)0x4001244C)

__IO u16 ADC_ConvertedValue;

/*
 * ��������ADC1_GPIO_Config
 * ����  ��ʹ��ADC1��ʱ�ӣ���ʼ��PA.01
 * ����  : ��
 * ���  ����
 * ����  ���ڲ�����
 */
static void ADC1_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/* Enable ADC1 and GPIOC clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_GPIOA, ENABLE);
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //72M/6=12,ADC���ʱ�䲻�ܳ���14M����δ�ҵ���������Ͷ���Ƶ

  /* Configure PA.01  as analog input */
  //GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_Init(GPIOA, &GPIO_InitStructure);				// PB0,����ʱ������������
}


/* ��������ADC1_Mode_Config
 * ����  ������ADC1�Ĺ���ģʽ
 * ����  : ��
 * ���  ����
 * ����  ���ڲ�����
 */
static void ADC1_Mode_Config(void)
{
	ADC_InitTypeDef ADC_InitStructure;

	/* Resets ADC1 */ 
	ADC_DeInit(ADC1);  //������ ADC1 ��ȫ���Ĵ�������Ϊȱʡֵ
	
	/* ADC1 configuration ------------------------------------------------------*/
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC����ģʽ:ADC1��ADC2�����ڶ���ģʽ
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;	//ģ��ת�������ڵ�ͨ��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	//ģ��ת�������ڵ���ת��ģʽ
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//ת��������������ⲿ��������
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC�����Ҷ���
	ADC_InitStructure.ADC_NbrOfChannel = 1;	//˳����й���ת����ADCͨ������Ŀ
	ADC_Init(ADC1, &ADC_InitStructure);	//����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���
	
	/* Enable ADC1 */
	ADC_Cmd(ADC1, ENABLE);	//ʹ��ָ����ADC1
	
	
	/* Enable ADC1 reset calibaration register */   
	ADC_ResetCalibration(ADC1);	//����ָ����ADC1��У׼�Ĵ���
	/* Check the end of ADC1 reset calibration register */
	while(ADC_GetResetCalibrationStatus(ADC1));	//��ȡADC1����У׼�Ĵ�����״̬,����״̬��ȴ�
	
	/* Start ADC1 calibaration */
	ADC_StartCalibration(ADC1);		//��ʼָ��ADC1��У׼״̬
	/* Check the end of ADC1 calibration */
	while(ADC_GetCalibrationStatus(ADC1));		//��ȡָ��ADC1��У׼����,����״̬��ȴ�
	
	/* Start ADC1 Software Conversion */ 
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//ʹ��ָ����ADC1�����ת����������
}

/*
 * ��������ADC1_Init
 * ����  ����
 * ����  ����
 * ���  ����
 * ����  ���ⲿ����
 */
void ADC1_Init(void)
{
	ADC1_GPIO_Config();
	ADC1_Mode_Config();
}



/******************* (C) COPYRIGHT 2013 CEPARK�๦�ܿ���ѧϰ��*****END OF FILE****/

