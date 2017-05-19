/**
  ******************************************************************************
  * @file    bsp_xxx.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   adc1 应用bsp / DMA 模式
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火 ISO-MINI STM32 开发板 
  * 论坛    :http://www.chuxue123.com
  * 淘宝    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */ 
  
#include "bsp_adc.h"

#define ADC1_DR_Address    ((u32)0x40012400+0x4c)

__IO uint16_t ADC_ConvertedValue;
//__IO u16 ADC_ConvertedValueLocal;

/**
  * @brief  使能ADC1和DMA1的时钟，初始化PC.0
  * @param  无
  * @retval 无
  */
//static void ADC1_GPIO_Config(void)
//{
//	GPIO_InitTypeDef GPIO_InitStructure;
//	
//	/* Enable DMA clock */
//	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
//	
//	/* Enable ADC1 and GPIOC clock */
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_GPIOC, ENABLE);
//	
//	/* Configure PC.0  as analog input */
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
//	GPIO_Init(GPIOC, &GPIO_InitStructure);				// PC0,输入时不用设置速率
//}

///**
//  * @brief  配置ADC1的工作模式为MDA模式
//  * @param  无
//  * @retval 无
//  */
//static void ADC1_Mode_Config(void)
//{
//	DMA_InitTypeDef DMA_InitStructure;
//	ADC_InitTypeDef ADC_InitStructure;
//	
//	/* DMA channel1 configuration */
//	DMA_DeInit(DMA1_Channel1);
//	
//	DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address;	 			//ADC地址
//	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)&ADC_ConvertedValue;	//内存地址
//	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
//	DMA_InitStructure.DMA_BufferSize = 2;
//	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;	//外设地址固定
//	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;  				//内存地址固定
//	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;	//半字
//	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
//	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;										//循环传输
//	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
//	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
//	DMA_Init(DMA1_Channel1, &DMA_InitStructure);
////	
//	/* Enable DMA channel1 */
//	DMA_Cmd(DMA1_Channel1, ENABLE);
//	
//	/* ADC1 configuration */	
//	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;			//独立ADC模式
//	ADC_InitStructure.ADC_ScanConvMode = DISABLE ; 	 				//禁止扫描模式，扫描模式用于多通道采集
//	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;			//开启连续转换模式，即不停地进行ADC转换
//	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//不使用外部触发转换
//	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right; 	//采集数据右对齐
//	ADC_InitStructure.ADC_NbrOfChannel = 1;	 								//要转换的通道数目1
//	ADC_Init(ADC1, &ADC_InitStructure);
//	
//	/*配置ADC时钟，为PCLK2的8分频，即9MHz*/
//	RCC_ADCCLKConfig(RCC_PCLK2_Div8); 
//	/*配置ADC1的通道11为55.	5个采样周期，序列为1 */ 
//	ADC_RegularChannelConfig(ADC1, ADC_Channel_10, 1, ADC_SampleTime_1Cycles5);
//	
//	/* Enable ADC1 DMA */
//	ADC_DMACmd(ADC1, ENABLE);
//	
//	/* Enable ADC1 */
//	ADC_Cmd(ADC1, ENABLE);
//	
//	/*复位校准寄存器 */   
//	ADC_ResetCalibration(ADC1);
//	/*等待校准寄存器复位完成 */
//	while(ADC_GetResetCalibrationStatus(ADC1));
//	
//	/* ADC校准 */
//	ADC_StartCalibration(ADC1);
//	/* 等待校准完成*/
//	while(ADC_GetCalibrationStatus(ADC1));
//	
//	/* 由于没有采用外部触发，所以使用软件触发ADC转换 */ 
//	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
//    
//}

///**
//  * @brief  ADC1初始化
//  * @param  无
//  * @retval 无
//  */
//void ADC1_Init(void)
//{
//	ADC1_GPIO_Config();
//	ADC1_Mode_Config();
//}
///*********************************************END OF FILE**********************/

void TIM2_Configuration(void) 
{ 
    
//    TIM_TimeBaseInitTypeDef   TIM_TimeBaseStructure;
//    TIM_OCInitTypeDef         TIM_OCInitStructure;
//    NVIC_InitTypeDef NVIC_InitStructure;
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);
//      /* TIM1 configuration ------------------------------------------------------*/ 
//      /* Time Base configuration */
//    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);        //??????????  
//    TIM_TimeBaseStructure.TIM_Period = 4500;                     //1us*2000=2ms
//    TIM_TimeBaseStructure.TIM_Prescaler = 2;                  //72M/(71+1)=1M
//    TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;         //TIM_CKD_DIV1  
//    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;         //??????         
//    TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);
//    /* TIM1 channel1 configuration in PWM mode */
//    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;                 //???????PWM1??
//    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;    //??????            
//    TIM_OCInitStructure.TIM_Pulse = 0x7F;                                                          //???
//    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;         //???????
//    TIM_OC1Init(TIM8, &TIM_OCInitStructure);

//    TIM_ClearFlag(TIM8, TIM_FLAG_Update);//??????  
//  
//    TIM_ITConfig(      //?????????TIM??  
//    TIM1,            //TIM1  
//    TIM_IT_Update  | //TIM ?????  
//    TIM_IT_Trigger,  //TIM ?????   
//    ENABLE           //??  
//    );  
//      
  //?????  
//      NVIC_InitStructure.NVIC_IRQChannel = TIM8_UP_IRQn;    
//      NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//?????0?  
//      NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;       //????0?  
//      NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
//      NVIC_Init(&NVIC_InitStructure);
//    /* TIM1 counter enable */
//    TIM_Cmd(TIM8, ENABLE);
//    /* TIM1 main Output Enable */
//    TIM_CtrlPWMOutputs(TIM8, ENABLE);
    TIM_TimeBaseInitTypeDef   TIM_TimeBaseStructure;
    TIM_OCInitTypeDef         TIM_OCInitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;    
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;//?????0?  
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;       //????0?  
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
    NVIC_Init(&NVIC_InitStructure);
     
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_Prescaler = 71;
    TIM_TimeBaseStructure.TIM_Period = 135;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
     
     
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0X7F;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;        
     
    TIM_OC2Init(TIM2, &TIM_OCInitStructure);
    
    TIM_ClearFlag(TIM2, TIM_FLAG_Update);
    TIM_ITConfig(TIM2, TIM_IT_Update, DISABLE);  
    TIM_Cmd(TIM2, ENABLE);
    TIM_CtrlPWMOutputs(TIM2, ENABLE);
} 

void DMA_Configuration(void)
{
    DMA_InitTypeDef DMA_InitStructure; 
    /* Enable DMA clock */ 
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
    /* DMA channel1 configuration */
	DMA_DeInit(DMA1_Channel1);
	
	DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address;	 			//ADC地址
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)&ADC_ConvertedValue;	//内存地址
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_InitStructure.DMA_BufferSize = 1;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;	//外设地址固定
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;  				//内存地址固定
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;	//半字
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;										//循环传输
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);
    DMA_Cmd(DMA1_Channel1, ENABLE); 
}


void ADC_Configuration(void) 
{ 

    ADC_InitTypeDef ADC_InitStructure; 
    GPIO_InitTypeDef GPIO_InitStructure; 
    
    /* Enable ADC1 and GPIOC clock */ 
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_GPIOC, ENABLE);
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; 
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; 
  	GPIO_Init(GPIOC, &GPIO_InitStructure); 
    DMA_Configuration();
    TIM2_Configuration(); 
    
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;	
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T2_CC2;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfChannel = 1;               
    ADC_Init(ADC1, &ADC_InitStructure); 
    RCC_ADCCLKConfig(RCC_PCLK2_Div8);
    ADC_RegularChannelConfig(ADC1, ADC_Channel_10, 1, ADC_SampleTime_239Cycles5);	  
    ADC_DMACmd(ADC1, ENABLE); 
    ADC_Cmd(ADC1, ENABLE);	
    ADC_ResetCalibration(ADC1); 
    while(ADC_GetResetCalibrationStatus(ADC1)); 
    ADC_StartCalibration(ADC1); 
    while(ADC_GetCalibrationStatus(ADC1));
    ADC_ExternalTrigConvCmd(ADC1, ENABLE);
    

}

void ADC1_Init(void)
{
	ADC_Configuration();
}
