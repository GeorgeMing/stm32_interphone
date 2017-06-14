/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTI
  
  AL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include<string.h>
#include "stm32f10x_it.h"
#include "usart.h"
#include "bsp_spi_nrf.h"
#include "List.h"
#define uchar unsigned char
#define uint unsigned int
char uartBuf[100];//存指令
uchar bufNum = 0;//指令字符位置
extern int uartComm;//指令标志位
extern __IO uint16_t ADC_ConvertedValue;
extern u8 txbuf[4];
extern char carno[10];
extern u8 TX_ADDRESS[TX_ADR_WIDTH];  //发送地址
extern u8 RX_ADDRESS[RX_ADR_WIDTH];//本车地址
extern List carinfo;
char saycarno[10];
int timeIRQNum = 0;
char selectCarFlag;

/** @addtogroup STM32F10x_StdPeriph_Template
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
  * @brief  This function handles PendSVC exception.
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

void sounrfaddr(Item item)
{
    int i;
    if(strcmp(item.carno, saycarno) == 0){
        TX_ADDRESS[0] = item.nrfaddr[0];
        TX_ADDRESS[1] = item.nrfaddr[1];
        TX_ADDRESS[2] = item.nrfaddr[2];
        TX_ADDRESS[3] = item.nrfaddr[3];
        TX_ADDRESS[4] = item.nrfaddr[4];
    }
    for(i = 0; i < 10; i++)saycarno[i] = ' ';
}

/*
*-1：无指令
*1：open指令
*2：set_carno指令
*3：select指令
*4：say_carno指令
*5：close指令
*6：say_close指令
*/
void USART1_IRQHandler(void)
{
	uint8_t ch;
    int num;
	char uartBufTemp[50];
    char uartBufTemp2[50];
    if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{ 	
		//ch = USART1->DR;
        ch = USART_ReceiveData(USART1);
		if(ch == '#')//指令判断
		{
			uartBuf[bufNum] = '\0';
			bufNum = 0;
			if(strcmp((const char*)uartBuf, "open")==0)uartComm = 1;
			else if(strcmp((const char*)uartBuf, "close")==0)uartComm = 5;
			else if(strcmp((const char*)uartBuf, "select")==0)uartComm = 3;
			else if(strcmp((const char*)uartBuf, "say_close")==0)uartComm = 6;
			else
			{
				strcpy(uartBufTemp, uartBuf);
				uartBufTemp[10] = '\0';
				if(strcmp((const char*)uartBufTemp, "set_carno=")==0){
                    uartComm = 2;
                    num = 10;
                    while(uartBuf[num]!='\0')
                    {
                        uartBufTemp2[num-10] = uartBuf[num];
                        num++;
                    }
                    uartBufTemp2[num-10] = '\0';
                    strcpy(carno, uartBufTemp2);
                }
				if(strcmp((const char*)uartBufTemp, "say_carno=")==0){
                    uartComm = 4;
                    num = 10;
                    while(uartBuf[num]!='\0')
                    {
                        uartBufTemp2[num-10] = uartBuf[num];
                        num++;
                    }
                    uartBufTemp2[num-10] = '\0';
                    strcpy(saycarno, uartBufTemp2);
                    Traverse(&carinfo, sounrfaddr);
                }
			}
			bufNum = 0;
		}
		else if(bufNum < 100)
		{
			uartBuf[bufNum] = ch;
			bufNum++;
		}
		else
		{
			bufNum = 0;
		}
	}  
}

void USART2_IRQHandler(void)
{
	uint8_t ch;
    Item tempCarInfo;
    int num = 6;
    int temp3num = 0;
	char uartBufTemp[50];
    char uartBufTemp2[50];
    Node *pnode = carinfo;
    char flag = 0;
    selectCarFlag = 0;
    if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
	{ 	
		//ch = USART1->DR;
        ch = USART_ReceiveData(USART2);
		if(ch == '#')//指令判断
		{
//            printf("uart2shoudao\r\n");
			uartBuf[bufNum] = '\0';
			bufNum = 0;
			if(strcmp((const char*)uartBuf, "select_car")==0)
            {
                selectCarFlag = 1;
                USART_printf(USART2, (uint8_t*)"carno=%s!", carno);
                for(num = 0; num < 5; num++)
                {
                    USART_SendData( USART2, RX_ADDRESS[num] );
					while ( USART_GetFlagStatus( USART2, USART_FLAG_TC ) == RESET );
                }
                USART_SendData( USART2, '!' );
					while ( USART_GetFlagStatus( USART2, USART_FLAG_TC ) == RESET );
                USART_SendData( USART2, '#' );
					while ( USART_GetFlagStatus( USART2, USART_FLAG_TC ) == RESET );
            }
            else
            {
                strcpy(uartBufTemp, uartBuf);
				uartBufTemp[6] = '\0';
				if(strcmp((const char*)uartBufTemp, "carno=")==0 && selectCarFlag==1){
                    while(uartBuf[num]!='!'){uartBufTemp2[num-6] = uartBuf[num];num++;}
                    uartBufTemp2[num-6] = '#';
                    uartBufTemp2[num-6+1] = '\0';
//                    USART_printf(USART1, (uint8_t*)uartBufTemp2);
                    uartBufTemp2[num-6] = '\0';//carno
                    strcpy(tempCarInfo.carno, uartBufTemp2);
                    num++;
                    while(uartBuf[num]!='!' && temp3num<5)
                    {
                        tempCarInfo.nrfaddr[temp3num] = uartBuf[num];
                        num++;temp3num++;
                    }
                    
                    while (pnode != NULL)
                    {
                        if(strcmp(pnode->item.carno, uartBufTemp2) == 0){ flag = 1;break;}
                        pnode = pnode->next;
                    }
                    if(flag == 0)
                        AddItem(tempCarInfo, &carinfo);
                }
            }
		}
		else if(bufNum < 100)
		{
			uartBuf[bufNum] = ch;
			bufNum++;
		}
		else
		{
			bufNum = 0;
		}
	}  
}

void TIM2_IRQHandler(void)   
{                      
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)  
    {  
        txbuf[timeIRQNum] = ADC_ConvertedValue >> 4;
//        printf("%d\r\n", ADC_ConvertedValue);
        if(timeIRQNum == 3){timeIRQNum = 0; NRF_Tx_Dat(txbuf);}
        else timeIRQNum++;
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    }          
} 

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
