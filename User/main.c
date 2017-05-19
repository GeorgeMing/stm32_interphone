/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   adc1 采集实验
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火 ISO-MINI STM32 开发板 
  * 论坛    :http://www.chuxue123.com
  * 淘宝    :http://firestm32.taobao.com
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
u8 txbuf[4] = {1,2,3,4};	 //发送缓冲
u8 rxbuf[4];			 //接收缓冲
u8 TX_FLAG = 0;
int uartComm;//指令判断
// ADC1转换的电压值通过MDA方式传到SRAM
extern __IO uint16_t ADC_ConvertedValue;
// 局部变量，用于保存转换计算后的电压值 	 
float ADC_ConvertedValueLocal;  
      

// 软件延时
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
  * @brief  主函数
  * @param  无
  * @retval 无
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
        *-1：无指令
        *1：open指令
        *2：set_carno指令
        *3：select指令
        *4：say_carno指令
        *5：close指令
        *6：say_close指令
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

