#include "stm32f10x.h"
#include "usart.h"
#include "bsp_adc.h"
#include "bsp_dac.h"
#include "bsp_spi_nrf.h"
#include "List.h"
#include "delay.h"
#include <stdlib.h>

u8 status;
int uartComm;//指令判断
char carno[10];//本车车牌
u8 nrfaddr[] = {0x34,0x43,0x10,0x10,0x02};//本车nrf地址
u8 TX_ADDRESS[TX_ADR_WIDTH];  //发送地址
u8 RX_ADDRESS[RX_ADR_WIDTH];//本车地址
u8 txbuf[4];	 
u8 rxbuf[4];			
u8 TX_FLAG = 0;
int uartComm;
List carinfo;
extern __IO uint16_t ADC_ConvertedValue;
extern char selectCarFlag;
float ADC_ConvertedValueLocal; 

void showmovies(Item item);

// 软件延时
void Delay(__IO uint32_t nCount)
{
  for(; nCount != 0; nCount--);
} 




int main(void)
{	
    int addnum;
	InitializeList(&carinfo);//初始化队列
    
    for(addnum = 0; addnum < RX_ADR_WIDTH; addnum++){//设置自己的地址
        RX_ADDRESS[addnum] = nrfaddr[addnum];
    }
    
    uartComm = -1;
	/* INIT */
    delay_init();
    USART1_Config();
    USART2_Config();
    USART1_NVIC_Configuration();	
    USART2_NVIC_Configuration();
	USART_printf(USART1, (uint8_t*)" USART1 test %d %s\r\n", uartComm, "abc");
    USART_printf(USART2, (uint8_t*)"USART2 test2 %d %s\r\n", uartComm, "abc");
    SPI_NRF_Init();
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
    
    //init carinfo
   
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
			case -1:break;//无指令
			case 1://open
                printf("success\r\n");
                uartComm = -1;
				break;
            case 2://set_carno
                printf("success\r\n");
//                printf("carno=%s\r\n", carno);
                uartComm = -1;
                break;
            case 3://select
                USART_printf(USART2, (uint8_t*)"select_car#");
                EmptyTheList(&carinfo);
                delay_ms(1000);
                delay_ms(1000);
                selectCarFlag = 0;
                printf("success\r\n");
                if(!ListIsEmpty((const List *)carinfo))
                    Traverse(&carinfo, showmovies);
                uartComm = -1;
                break;
            case 4://say_carno
                printf("success\r\n");
                SPI_NRF_Init();
                NRF_TX_Mode();
                TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
                TIM_CtrlPWMOutputs(TIM2, ENABLE);
                DAC_Cmd(DAC_Channel_1, DISABLE);
                TX_FLAG = 1;
                uartComm = -1;
                break;
            case 5://close
                printf("success\r\n");
                uartComm = -1;
                break;
            case 6://say_close
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
                    //printf("rx\r\n");
                    ADC_ConvertedValue = rxbuf[0] << 4;                 
                    DAC_SetChannel1Data(DAC_Align_12b_R,ADC_ConvertedValue);
                    ADC_ConvertedValue = rxbuf[1] << 4;
                    DAC_SetChannel1Data(DAC_Align_12b_R,ADC_ConvertedValue);
                    ADC_ConvertedValue = rxbuf[2] << 4;
                    DAC_SetChannel1Data(DAC_Align_12b_R,ADC_ConvertedValue);
                    ADC_ConvertedValue = rxbuf[3] << 4;
                    DAC_SetChannel1Data(DAC_Align_12b_R,ADC_ConvertedValue);
                    break;
                }
                case ERROR:
                {
                    break;  
                }                    
            }
        }  
    }
}

void showmovies(Item item)
{
	USART_printf(USART1, (uint8_t*)"%s#", item.carno);
}

