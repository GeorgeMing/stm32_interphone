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
#include "bsp_spi_nrf.h"
#include "bsp_dac.h"
#include "bsp_usart1.h"
#define uchar unsigned char
#define uint unsigned int
extern char TXFLAG;
char uartBuf[100];//��ָ��
uchar bufNum = 0;//ָ���ַ�λ��
extern int uartComm;//ָ���־λ
extern __IO uint16_t ADC_ConvertedValue;
extern u8 txbuf[4];
int timeIRQNum = 0;
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

/*
*-1����ָ��
*1��openָ��
*2��set_carnoָ��
*3��selectָ��
*4��say_carnoָ��
*5��closeָ��
*6��say_closeָ��
*/
void USART1_IRQHandler(void)
{
	uint8_t ch;
	char uartBufTemp[100];
    if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{ 	
		//ch = USART1->DR;
        ch = USART_ReceiveData(USART1);
		if(ch == '#')//ָ���ж�
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
				if(strcmp((const char*)uartBufTemp, "set_carno=")==0)uartComm = 2;
				if(strcmp((const char*)uartBufTemp, "say_carno=")==0)uartComm = 4;
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
