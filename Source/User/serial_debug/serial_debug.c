/*******************************************************************************
        (c) COPYRIGHT 2010-2018 by Efficient Systems, Inc.    
                          All rights reserved.
    
       This software is confidential and proprietary to Efficient 
     Systems, Inc.  No part of this software may be reproduced,    
     stored, transmitted, disclosed or used in any form or by any means
     other than as expressly provided by the written license agreement    
     between Efficient Systems and its licensee.
 FileName    : serial_debug.c
 Author      : ranwei
 Version     : 
 Date        : 2016/3/1 10:51:2:558
 Description : 
 Others      : 

 History      :
  1.Date         -- 2016/3/1 10:51:2:558
    Author       -- ranwei
    Modification -- Created file

*******************************************************************************/
    
#define  SERIAL_DEBUG_GLOBAL

/* includes-------------------------------------------------------------------*/
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include "main_conf.h"
#include "serial_debug.h"
#include "stm32f4xx.h"

    
/* Private macro&definde------------------------------------------------------*/
#ifdef SERIAL_DEBUG
    #define SERIAL_DEBUG_COM                        USART2
    #define SERIAL_DEBUG_COM_CLK                    RCC_APB1Periph_USART2
    #define SERIAL_DEBUG_COM_TX_PIN                 GPIO_Pin_5
    #define SERIAL_DEBUG_COM_TX_GPIO_PORT           GPIOD
    #define SERIAL_DEBUG_COM_TX_GPIO_CLK            RCC_AHB1Periph_GPIOD
    #define SERIAL_DEBUG_COM_TX_SOURCE              GPIO_PinSource5
    #define SERIAL_DEBUG_COM_TX_AF                  GPIO_AF_USART2
    #define SERIAL_DEBUG_COM_RX_PIN                 GPIO_Pin_6
    #define SERIAL_DEBUG_COM_RX_GPIO_PORT           GPIOD
    #define SERIAL_DEBUG_COM_RX_GPIO_CLK            RCC_AHB1Periph_GPIOD
    #define SERIAL_DEBUG_COM_RX_SOURCE              GPIO_PinSource6
    #define SERIAL_DEBUG_COM_RX_AF                  GPIO_AF_USART2
    #define SERIAL_DEBUG_COM_IRQn                   USART2_IRQn    
#endif



/* Private typedef -----------------------------------------------------------*/
/* 
**  With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
**  set to 'Yes') calls __io_putchar() 
*/
#ifdef __GNUC__
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */



/* Private variables ---------------------------------------------------------*/
#ifdef SERIAL_DEBUG
#define SZ_LogBuFF_MAXSIZE  128
uint8_t aucLogBuff[SZ_LogBuFF_MAXSIZE+1] = {0};
#endif


/* Private functions ---------------------------------------------------------*/
/* External functions --------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
    

void __Prompt__(const char *file, int line, const char *func, const char *format, va_list argp)
#ifdef SERIAL_DEBUG
{
    if(NULL == format|| 0 == format[0]) 
    {
        return;
    }
    memset(aucLogBuff, 0, sizeof(aucLogBuff));
    vsnprintf((char *)aucLogBuff, SZ_LogBuFF_MAXSIZE, format, argp);
    printf("\n  Prompt : [%s %d]%s():", file, line, func);
    printf("%s\n", aucLogBuff);
}
#else
{
}
#endif

void __Assert__(const char *file, int line, const char *func, const char *format, va_list argp)
#ifdef SERIAL_DEBUG
{
    if (NULL == format|| 0 == format[0]) 
    {
        return;
    }
    memset(aucLogBuff, 0, sizeof(aucLogBuff));
    vsnprintf((char *)aucLogBuff, SZ_LogBuFF_MAXSIZE, format, argp);
    printf("\n  Prompt : [%s %d]%s():", file, line, func);
    printf("%s\n", aucLogBuff);

}
#else
{
}
#endif


#ifdef SERIAL_DEBUG
void DebugComPort_Init(void)
{
    //NVIC_InitTypeDef NVIC_InitStructure;

    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure; 
    
    RCC_AHB1PeriphClockCmd(SERIAL_DEBUG_COM_TX_GPIO_CLK | SERIAL_DEBUG_COM_RX_GPIO_CLK, ENABLE);
    RCC_APB1PeriphClockCmd(SERIAL_DEBUG_COM_CLK,ENABLE);
    switch(SERIAL_DEBUG_COM_CLK)
    {
    case RCC_APB1Periph_USART2:
    case RCC_APB1Periph_USART3:
    case RCC_APB1Periph_UART4:
    case RCC_APB1Periph_UART5:
        RCC_APB1PeriphClockCmd(SERIAL_DEBUG_COM_CLK,ENABLE);
        break;
    case RCC_APB2Periph_USART1:
    case RCC_APB2Periph_USART6:
        RCC_APB2PeriphClockCmd(SERIAL_DEBUG_COM_CLK,ENABLE);
        break;
    }

    /* Enable the USARTx Interrupt */
    //NVIC_InitStructure.NVIC_IRQChannel = IAP_COM1_IRQn;
    //NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    //NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    //NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    //NVIC_Init(&NVIC_InitStructure);      
    
    GPIO_PinAFConfig(SERIAL_DEBUG_COM_TX_GPIO_PORT, SERIAL_DEBUG_COM_TX_SOURCE, SERIAL_DEBUG_COM_TX_AF);
    GPIO_PinAFConfig(SERIAL_DEBUG_COM_RX_GPIO_PORT, SERIAL_DEBUG_COM_RX_SOURCE, SERIAL_DEBUG_COM_RX_AF);

    GPIO_InitStructure.GPIO_Pin = SERIAL_DEBUG_COM_TX_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;

    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(SERIAL_DEBUG_COM_TX_GPIO_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = SERIAL_DEBUG_COM_RX_PIN;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(SERIAL_DEBUG_COM_RX_GPIO_PORT, &GPIO_InitStructure);

    /*
             USARTx configured as follow:
             - BaudRate = 115200 baud  
             - Word Length = 8 Bits
             - One Stop Bit
             - No parity
             - Hardware flow control disabled (RTS and CTS signals)
             - Receive and transmit    
     */
    
    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(SERIAL_DEBUG_COM, &USART_InitStructure);
    /* Enable the Open_USART Transmit interrupt: this interrupt is generated when the 
     Open_USART transmit data register is empty */
    //USART_ITConfig(IAP_COM1, USART_IT_RXNE,ENABLE);

    USART_Cmd(SERIAL_DEBUG_COM, ENABLE); 
}


/* Use no semihosting */
#pragma import(__use_no_semihosting)
struct __FILE
{  	
    int handle;
};
FILE __stdout;

_sys_exit(int x)
{
	x = x;
}

PUTCHAR_PROTOTYPE
{
    /* Place your implementation of fputc here */
    /* e.g. write a character to the USART */
    while(!(SERIAL_DEBUG_COM->SR & USART_SR_TXE));
    USART_SendData(SERIAL_DEBUG_COM, (uint8_t) ch);
    while(!(SERIAL_DEBUG_COM->SR & USART_SR_TC)); 	
    
    return ch;
}
#endif

    
/**************** (C) COPYRIGHT 2010-2018 Efficient *****END OF FILE***********/
