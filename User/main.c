/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   adc1 �ɼ�ʵ��
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ�� ISO-MINI STM32 ������ 
  * ��̳    :http://www.chuxue123.com
  * �Ա�    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */

//time : pc1-1 0      1us
//       pc1-2 0 0.5us    1.5us
//			 pc1-3 0 0.5us 0.8us

#include "stm32f10x.h"
#include "bsp_usart1.h"
#include "bsp_spi_nrf.h"
#include "bsp_adc.h"
#include "bsp_dac.h"

u8 status;
u8 txbuf[4] = {1,2,3,4};	 //���ͻ���
u8 rxbuf[4];			 //���ջ���
u8 TX_FLAG = 0;
int uartComm;//ָ���ж�
// ADC1ת���ĵ�ѹֵͨ��MDA��ʽ����SRAM
extern __IO uint16_t ADC_ConvertedValue;
// �ֲ����������ڱ���ת�������ĵ�ѹֵ 	 
float ADC_ConvertedValueLocal;  
      

// �����ʱ
void Delay(__IO uint32_t nCount)
{
  for(; nCount != 0; nCount--);
} 



void key_init()
{
	
		GPIO_InitTypeDef GPIO_InitStructure;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_Init(GPIOB, &GPIO_InitStructure);
		
		GPIO_SetBits(GPIOB, GPIO_Pin_0);
}


/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{	
    uartComm = -1;
	/* INIT */
	
    USART1_Config();
    USART1_NVIC_Configuration();	
    SPI_NRF_Init();
	printf(" test\r\n");
    Dac1_Init();
	ADC1_Init();
    if(NRF_Check() == SUCCESS){
		printf(" nrf success\r\n");
	}else{
		printf(" nrf fail\r\n");
	}
	NRF_RX_Mode();
    TX_FLAG = 0;
	Dac1_Set_Vol(2500);
    
	while (1)
	{
        /*
        *-1����ָ��
        *1��openָ��
        *2��set_carnoָ��
        *3��selectָ��
        *4��say_carnoָ��
        *5��closeָ��
        *6��say_closeָ��
        */
		switch(uartComm){
			case -1:break;
			case 1:
                printf("success\r\n");
                uartComm = -1;
				break;
            case 2:
                printf("success\r\n");
                uartComm = -1;
                break;
            case 3:
                printf("EAT777\r\n");
                uartComm = -1;
                break;
            case 4:
                printf("success\r\n");
                SPI_NRF_Init();
                NRF_TX_Mode();
                TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
                TIM_CtrlPWMOutputs(TIM2, ENABLE);
                DAC_Cmd(DAC_Channel_1, DISABLE);
                TX_FLAG = 1;
                uartComm = -1;
                break;
            case 5:
                printf("success\r\n");
                uartComm = -1;
                break;
            case 6:
                printf("success\r\n");
                SPI_NRF_Init();
                NRF_RX_Mode();
                TIM_ITConfig(TIM2, TIM_IT_Update, DISABLE);
                TIM_CtrlPWMOutputs(TIM2, DISABLE);
                DAC_Cmd(DAC_Channel_1, ENABLE);
                TX_FLAG = 0;
                uartComm = -1;
                break;   
		}
       
        if(TX_FLAG == 0)//rx
        {
            status = NRF_Rx_Dat(rxbuf);
            switch(status)
            {
                case RX_DR:
                {		
//                    printf("rx\r\n");
                    ADC_ConvertedValue = rxbuf[0] << 4;
//                    Dac1_Set_Vol(ADC_ConvertedValue);
                    DAC_SetChannel1Data(DAC_Align_12b_R,ADC_ConvertedValue);
                    ADC_ConvertedValue = rxbuf[1] << 4;
//                    Dac1_Set_Vol(ADC_ConvertedValue);
                    DAC_SetChannel1Data(DAC_Align_12b_R,ADC_ConvertedValue);
                    ADC_ConvertedValue = rxbuf[2] << 4;
//                    Dac1_Set_Vol(ADC_ConvertedValue);
                    DAC_SetChannel1Data(DAC_Align_12b_R,ADC_ConvertedValue);
                    ADC_ConvertedValue = rxbuf[3] << 4;
//                    Dac1_Set_Vol(ADC_ConvertedValue);
                    DAC_SetChannel1Data(DAC_Align_12b_R,ADC_ConvertedValue);
                    break;
                }
                case ERROR:
                {
//                    printf("error\r\n");
                    break;  
                }                    
            }
        }  
    }
}

