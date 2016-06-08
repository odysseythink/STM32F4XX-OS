/**
* @file      Commu_Uart.c
* @brief     
* @details   
* @author    ranwei
* @version     
* @date      2016/5/11 11:11:51:172
* @copyright Efficien
* @par         (c) COPYRIGHT 2010-2018 by Efficien Systems, Inc.    
*                        All rights reserved.
*                                                                    
*       This software is confidential and proprietary to Efficien 
*     Systems, Inc.  No part of this software may be reproduced,    
*     stored, transmitted, disclosed or used in any form or by any means
*     other than as expressly provided by the written license agreement    
*     between Efficien Systems and its licensee.
* @par History      
*         1.Date         -- 2016/5/11 11:11:51:172
*           Author       -- ranwei
*           Modification -- Created file
*
*/
    
#define  COMMU_UART_GLOBAL

/* includes-------------------------------------------------------------------*/
#include <string.h>
#include "stm32f4xx.h"
#include "Communication\Commu_Uart.h"


    
/* Private typedef&macro&definde----------------------------------------------*/
#ifdef __XBEE_COMMU_USE_UART3
/* Definition for USARTx resources */
#define COMMU_XBEE_UART                           USART3
#define COMMU_XBEE_UART_CLK                       RCC_APB1Periph_USART3
#define COMMU_XBEE_UART_CLK_INIT                  RCC_APB1PeriphClockCmd
#define COMMU_XBEE_UART_IRQn                      USART3_IRQn
#define COMMU_XBEE_UART_IRQHandler                USART3_IRQHandler
#define COMMU_XBEE_UART_TX_PIN                    GPIO_Pin_10                
#define COMMU_XBEE_UART_TX_GPIO_PORT              GPIOC                       
#define COMMU_XBEE_UART_TX_GPIO_CLK               RCC_AHB1Periph_GPIOC
#define COMMU_XBEE_UART_TX_SOURCE                 GPIO_PinSource10
#define COMMU_XBEE_UART_TX_AF                     GPIO_AF_USART3
#define COMMU_XBEE_UART_RX_PIN                    GPIO_Pin_11                
#define COMMU_XBEE_UART_RX_GPIO_PORT              GPIOC                    
#define COMMU_XBEE_UART_RX_GPIO_CLK               RCC_AHB1Periph_GPIOC
#define COMMU_XBEE_UART_RX_SOURCE                 GPIO_PinSource11
#define COMMU_XBEE_UART_RX_AF                     GPIO_AF_USART3
#define COMMU_XBEE_UART_BAUDRATE                  256000

/* Definition for DMAx resources */
#define COMMU_XBEE_UART_DR_ADDRESS                ((uint32_t)USART3 + 0x04) 
#define COMMU_XBEE_UART_DMA                       DMA1
#define COMMU_XBEE_UART_DMA_CLK                   RCC_AHB1Periph_DMA1
#define COMMU_XBEE_UART_TX_DMA_CHANNEL            DMA_Channel_4
#define COMMU_XBEE_UART_TX_DMA_STREAM             DMA1_Stream3
#define COMMU_XBEE_UART_TX_DMA_FLAG_FEIF          DMA_FLAG_FEIF3
#define COMMU_XBEE_UART_TX_DMA_FLAG_DMEIF         DMA_FLAG_DMEIF3
#define COMMU_XBEE_UART_TX_DMA_FLAG_TEIF          DMA_FLAG_TEIF3
#define COMMU_XBEE_UART_TX_DMA_FLAG_HTIF          DMA_FLAG_HTIF3
#define COMMU_XBEE_UART_TX_DMA_FLAG_TCIF          DMA_FLAG_TCIF3
#define COMMU_XBEE_UART_TX_DMA_IT_FEIF            DMA_IT_FEIF3
#define COMMU_XBEE_UART_TX_DMA_IT_DMEIF           DMA_IT_DMEIF3
#define COMMU_XBEE_UART_TX_DMA_IT_TEIF            DMA_IT_TEIF3
#define COMMU_XBEE_UART_TX_DMA_IT_HTIF            DMA_IT_HTIF3
#define COMMU_XBEE_UART_TX_DMA_IT_TCIF            DMA_IT_TCIF3

#define COMMU_XBEE_UART_RX_DMA_CHANNEL            DMA_Channel_4
#define COMMU_XBEE_UART_RX_DMA_STREAM             DMA1_Stream1
#define COMMU_XBEE_UART_RX_DMA_FLAG_FEIF          DMA_FLAG_FEIF1
#define COMMU_XBEE_UART_RX_DMA_FLAG_DMEIF         DMA_FLAG_DMEIF1
#define COMMU_XBEE_UART_RX_DMA_FLAG_TEIF          DMA_FLAG_TEIF1
#define COMMU_XBEE_UART_RX_DMA_FLAG_HTIF          DMA_FLAG_HTIF1
#define COMMU_XBEE_UART_RX_DMA_FLAG_TCIF          DMA_FLAG_TCIF1
#define COMMU_XBEE_UART_RX_DMA_IT_FEIF            DMA_IT_FEIF1
#define COMMU_XBEE_UART_RX_DMA_IT_DMEIF           DMA_IT_DMEIF1
#define COMMU_XBEE_UART_RX_DMA_IT_TEIF            DMA_IT_TEIF1
#define COMMU_XBEE_UART_RX_DMA_IT_HTIF            DMA_IT_HTIF1
#define COMMU_XBEE_UART_RX_DMA_IT_TCIF            DMA_IT_TCIF1

#define COMMU_XBEE_UART_DMA_TX_IRQn               DMA1_Stream3_IRQn
#define COMMU_XBEE_UART_DMA_RX_IRQn               DMA1_Stream1_IRQn
#define COMMU_XBEE_UART_DMA_TX_IRQHandler         DMA1_Stream3_IRQHandler
#define COMMU_XBEE_UART_DMA_RX_IRQHandler         DMA1_Stream1_IRQHandler

#endif

#ifdef __XBEE_COMMU_USE_UART2
/* Definition for USARTx resources */
#define COMMU_XBEE_UART                           USART2
#define COMMU_XBEE_UART_CLK                       RCC_APB1Periph_USART2
#define COMMU_XBEE_UART_CLK_INIT                  RCC_APB1PeriphClockCmd
#define COMMU_XBEE_UART_IRQn                      USART2_IRQn
#define COMMU_XBEE_UART_IRQHandler                USART2_IRQHandler
#define COMMU_XBEE_UART_TX_PIN                    GPIO_Pin_5                
#define COMMU_XBEE_UART_TX_GPIO_PORT              GPIOD                       
#define COMMU_XBEE_UART_TX_GPIO_CLK               RCC_AHB1Periph_GPIOD
#define COMMU_XBEE_UART_TX_SOURCE                 GPIO_PinSource5
#define COMMU_XBEE_UART_TX_AF                     GPIO_AF_USART2
#define COMMU_XBEE_UART_RX_PIN                    GPIO_Pin_6                
#define COMMU_XBEE_UART_RX_GPIO_PORT              GPIOD                    
#define COMMU_XBEE_UART_RX_GPIO_CLK               RCC_AHB1Periph_GPIOD
#define COMMU_XBEE_UART_RX_SOURCE                 GPIO_PinSource6
#define COMMU_XBEE_UART_RX_AF                     GPIO_AF_USART2
#define COMMU_XBEE_UART_BAUDRATE                  256000

/* Definition for DMAx resources */
#define COMMU_XBEE_UART_DR_ADDRESS                ((uint32_t)USART3 + 0x04) 
#define COMMU_XBEE_UART_DMA                       DMA1
#define COMMU_XBEE_UART_DMA_CLK                   RCC_AHB1Periph_DMA1
#define COMMU_XBEE_UART_TX_DMA_CHANNEL            DMA_Channel_4
#define COMMU_XBEE_UART_TX_DMA_STREAM             DMA1_Stream6
#define COMMU_XBEE_UART_TX_DMA_FLAG_FEIF          DMA_FLAG_FEIF6
#define COMMU_XBEE_UART_TX_DMA_FLAG_DMEIF         DMA_FLAG_DMEIF6
#define COMMU_XBEE_UART_TX_DMA_FLAG_TEIF          DMA_FLAG_TEIF6
#define COMMU_XBEE_UART_TX_DMA_FLAG_HTIF          DMA_FLAG_HTIF6
#define COMMU_XBEE_UART_TX_DMA_FLAG_TCIF          DMA_FLAG_TCIF6
#define COMMU_XBEE_UART_TX_DMA_IT_FEIF            DMA_IT_FEIF6
#define COMMU_XBEE_UART_TX_DMA_IT_DMEIF           DMA_IT_DMEIF6
#define COMMU_XBEE_UART_TX_DMA_IT_TEIF            DMA_IT_TEIF6
#define COMMU_XBEE_UART_TX_DMA_IT_HTIF            DMA_IT_HTIF6
#define COMMU_XBEE_UART_TX_DMA_IT_TCIF            DMA_IT_TCIF6

#define COMMU_XBEE_UART_RX_DMA_CHANNEL            DMA_Channel_4
#define COMMU_XBEE_UART_RX_DMA_STREAM             DMA1_Stream5
#define COMMU_XBEE_UART_RX_DMA_FLAG_FEIF          DMA_FLAG_FEIF5
#define COMMU_XBEE_UART_RX_DMA_FLAG_DMEIF         DMA_FLAG_DMEIF5
#define COMMU_XBEE_UART_RX_DMA_FLAG_TEIF          DMA_FLAG_TEIF5
#define COMMU_XBEE_UART_RX_DMA_FLAG_HTIF          DMA_FLAG_HTIF5
#define COMMU_XBEE_UART_RX_DMA_FLAG_TCIF          DMA_FLAG_TCIF5
#define COMMU_XBEE_UART_RX_DMA_IT_FEIF            DMA_IT_FEIF5
#define COMMU_XBEE_UART_RX_DMA_IT_DMEIF           DMA_IT_DMEIF5
#define COMMU_XBEE_UART_RX_DMA_IT_TEIF            DMA_IT_TEIF5
#define COMMU_XBEE_UART_RX_DMA_IT_HTIF            DMA_IT_HTIF5
#define COMMU_XBEE_UART_RX_DMA_IT_TCIF            DMA_IT_TCIF5

#define COMMU_XBEE_UART_DMA_TX_IRQn               DMA1_Stream6_IRQn
#define COMMU_XBEE_UART_DMA_RX_IRQn               DMA1_Stream5_IRQn
#define COMMU_XBEE_UART_DMA_TX_IRQHandler         DMA1_Stream6_IRQHandler
#define COMMU_XBEE_UART_DMA_RX_IRQHandler         DMA1_Stream5_IRQHandler
#endif

#ifdef __XBEE_COMMU_USE_UART4
/* Definition for USARTx resources */
#define COMMU_XBEE_UART                           UART4
#define COMMU_XBEE_UART_CLK                       RCC_APB1Periph_UART4
#define COMMU_XBEE_UART_CLK_INIT                  RCC_APB1PeriphClockCmd
#define COMMU_XBEE_UART_IRQn                      UART4_IRQn
#define COMMU_XBEE_UART_IRQHandler                UART4_IRQHandler
#define COMMU_XBEE_UART_TX_PIN                    GPIO_Pin_0                
#define COMMU_XBEE_UART_TX_GPIO_PORT              GPIOA                       
#define COMMU_XBEE_UART_TX_GPIO_CLK               RCC_AHB1Periph_GPIOA
#define COMMU_XBEE_UART_TX_SOURCE                 GPIO_PinSource0
#define COMMU_XBEE_UART_TX_AF                     GPIO_AF_UART4
#define COMMU_XBEE_UART_RX_PIN                    GPIO_Pin_1                
#define COMMU_XBEE_UART_RX_GPIO_PORT              GPIOA                    
#define COMMU_XBEE_UART_RX_GPIO_CLK               RCC_AHB1Periph_GPIOA
#define COMMU_XBEE_UART_RX_SOURCE                 GPIO_PinSource1
#define COMMU_XBEE_UART_RX_AF                     GPIO_AF_UART4
#define COMMU_XBEE_UART_BAUDRATE                  115200

/* Definition for DMAx resources */
#define COMMU_XBEE_UART_DR_ADDRESS                ((uint32_t)UART4 + 0x04) 
#define COMMU_XBEE_UART_DMA                       DMA1
#define COMMU_XBEE_UART_DMA_CLK                   RCC_AHB1Periph_DMA1
#define COMMU_XBEE_UART_TX_DMA_CHANNEL            DMA_Channel_4
#define COMMU_XBEE_UART_TX_DMA_STREAM             DMA1_Stream4
#define COMMU_XBEE_UART_TX_DMA_FLAG_FEIF          DMA_FLAG_FEIF4
#define COMMU_XBEE_UART_TX_DMA_FLAG_DMEIF         DMA_FLAG_DMEIF4
#define COMMU_XBEE_UART_TX_DMA_FLAG_TEIF          DMA_FLAG_TEIF4
#define COMMU_XBEE_UART_TX_DMA_FLAG_HTIF          DMA_FLAG_HTIF4
#define COMMU_XBEE_UART_TX_DMA_FLAG_TCIF          DMA_FLAG_TCIF4
#define COMMU_XBEE_UART_TX_DMA_IT_FEIF            DMA_IT_FEIF4
#define COMMU_XBEE_UART_TX_DMA_IT_DMEIF           DMA_IT_DMEIF4
#define COMMU_XBEE_UART_TX_DMA_IT_TEIF            DMA_IT_TEIF4
#define COMMU_XBEE_UART_TX_DMA_IT_HTIF            DMA_IT_HTIF4
#define COMMU_XBEE_UART_TX_DMA_IT_TCIF            DMA_IT_TCIF4

#define COMMU_XBEE_UART_RX_DMA_CHANNEL            DMA_Channel_4
#define COMMU_XBEE_UART_RX_DMA_STREAM             DMA1_Stream2
#define COMMU_XBEE_UART_RX_DMA_FLAG_FEIF          DMA_FLAG_FEIF2
#define COMMU_XBEE_UART_RX_DMA_FLAG_DMEIF         DMA_FLAG_DMEIF2
#define COMMU_XBEE_UART_RX_DMA_FLAG_TEIF          DMA_FLAG_TEIF2
#define COMMU_XBEE_UART_RX_DMA_FLAG_HTIF          DMA_FLAG_HTIF2
#define COMMU_XBEE_UART_RX_DMA_FLAG_TCIF          DMA_FLAG_TCIF2
#define COMMU_XBEE_UART_RX_DMA_IT_FEIF            DMA_IT_FEIF2
#define COMMU_XBEE_UART_RX_DMA_IT_DMEIF           DMA_IT_DMEIF2
#define COMMU_XBEE_UART_RX_DMA_IT_TEIF            DMA_IT_TEIF2
#define COMMU_XBEE_UART_RX_DMA_IT_HTIF            DMA_IT_HTIF2
#define COMMU_XBEE_UART_RX_DMA_IT_TCIF            DMA_IT_TCIF2

#define COMMU_XBEE_UART_DMA_TX_IRQn               DMA1_Stream4_IRQn
#define COMMU_XBEE_UART_DMA_RX_IRQn               DMA1_Stream2_IRQn
#define COMMU_XBEE_UART_DMA_TX_IRQHandler         DMA1_Stream4_IRQHandler
#define COMMU_XBEE_UART_DMA_RX_IRQHandler         DMA1_Stream2_IRQHandler
#endif


#ifndef COMMU_XBEE_UART
#error "must select one uart as COMMU_XBEE_UART"
#endif


/** ����ע��Ĵ�������accept�ص������ĸ��� */
#define SZ_COMMU_Uart_ACCEPT_HDL_NUM           1


#define COMMU_UART_RX_BUFF_LEN  SZ_COMMU_DMA_BUFF_MAX
#define COMMU_UART_TX_BUFF_LEN  SZ_COMMU_DMA_BUFF_MAX

#define SZ_COMMU_RCVFRAME_MIN_LEN 4

#pragma pack(push, 1)


typedef struct{
    uint8_t aucRxBuff[COMMU_UART_RX_BUFF_LEN];       
    uint8_t aucTxBuff[COMMU_UART_TX_BUFF_LEN];       
    uint8_t bIsSendIdleFlag : 1; /** �����Ƿ���б�ʶ��1:����|0:������ */
    uint8_t reserved1 : 7;
    Accept_Func_Type afAcceptHdlArray[SZ_COMMU_Uart_ACCEPT_HDL_NUM];
    uint8_t aucHalfFrameBuff[COMMU_UART_RX_BUFF_LEN];
    uint8_t ucHalfFrameLen;
}ST_Commu_Uart_CB_T;

#pragma pack(pop)


/* Private variables ---------------------------------------------------------*/
ST_Commu_Uart_CB_T g_stCommuUartCB;




/* Private functions ---------------------------------------------------------*/
/* External functions --------------------------------------------------------*/
/* External variables --------------------------------------------------------*/


static void _Commu_Uart_CB_Init(void)
{
    uint32_t iLoop;
    
    memset(g_stCommuUartCB.aucRxBuff, 0, COMMU_UART_RX_BUFF_LEN);
    memset(g_stCommuUartCB.aucTxBuff, 0, COMMU_UART_TX_BUFF_LEN);
    g_stCommuUartCB.bIsSendIdleFlag = 1; /** �����Ƿ���б�ʶ��1:����|0:������ */

    for(iLoop = 0; iLoop < SZ_COMMU_Uart_ACCEPT_HDL_NUM; iLoop++)
    {
        g_stCommuUartCB.afAcceptHdlArray[iLoop] = NULL;
    }
    memset(g_stCommuUartCB.aucHalfFrameBuff, 0, COMMU_UART_RX_BUFF_LEN);
    g_stCommuUartCB.ucHalfFrameLen = 0;
}

static void _Commu_Uart_Lowlevel_Init(void)
{
    NVIC_InitTypeDef NVIC_InitStructure ;  
    GPIO_InitTypeDef GPIO_InitStructure;  
    USART_InitTypeDef USART_InitStructure;  
    DMA_InitTypeDef DMA_InitStructure;  
  
    /*!< �򿪴��ڶ�Ӧ������ʱ�� */
    COMMU_XBEE_UART_CLK_INIT(COMMU_XBEE_UART_CLK, ENABLE);  
       
    /*!< ------���ڷ�DMA����------ */   
    RCC_AHB1PeriphClockCmd(COMMU_XBEE_UART_DMA_CLK, ENABLE);  /** ����DMAʱ�� */ 
    /*! DMA�����ж����� */
    NVIC_InitStructure.NVIC_IRQChannel = COMMU_XBEE_UART_DMA_TX_IRQn;  
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
    NVIC_Init(&NVIC_InitStructure);  
    /*!< ---DMAͨ������--- */ 
    DMA_DeInit(COMMU_XBEE_UART_TX_DMA_STREAM);  
    DMA_InitStructure.DMA_Channel = COMMU_XBEE_UART_TX_DMA_CHANNEL;   
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&COMMU_XBEE_UART->DR); /** �����ַ  */    
    DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)g_stCommuUartCB.aucTxBuff; /** �ڴ��ַ  */    
    DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;                      /** dma���䷽��  */    
    DMA_InitStructure.DMA_BufferSize = COMMU_UART_TX_BUFF_LEN;                   /** ����DMA�ڴ���ʱ�������ĳ���  */    
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;             /** ����DMA���������ģʽ��һ������  */    
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;                      /** ����DMA���ڴ����ģʽ  */    
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;      /** ���������ֳ�  */    
    DMA_InitStructure.DMA_MemoryDataSize = DMA_PeripheralDataSize_Byte;          /** �ڴ������ֳ�  */    
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;                                /** ����DMA�Ĵ���ģʽ  */    
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;                          /** ����DMA�����ȼ���  */
    DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;                       /** ָ�����FIFOģʽ��ֱ��ģʽ������ָ������ �� ��ʹ��FIFOģʽ  */           
    DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;            /** ָ����FIFO��ֵˮƽ  */            
    DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;                  /** ָ����Burstת�������ڴ洫��   */               
    DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;          /** ָ����Burstת��������Χת�� */
    DMA_Init(COMMU_XBEE_UART_TX_DMA_STREAM, &DMA_InitStructure);                 /** ����DMA1��ͨ�� */   
    DMA_ITConfig(COMMU_XBEE_UART_TX_DMA_STREAM, DMA_IT_TC, ENABLE);              /** ʹ���ж�  */  


    /*!< ------������DMA����------ */  
    
    RCC_AHB1PeriphClockCmd(COMMU_XBEE_UART_DMA_CLK, ENABLE);  /** ����DMAʱ��  */
    /*!< ---DMAͨ������--- */ 
    DMA_DeInit(COMMU_XBEE_UART_RX_DMA_STREAM);  
    DMA_InitStructure.DMA_Channel = COMMU_XBEE_UART_RX_DMA_CHANNEL;       
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&COMMU_XBEE_UART->DR); /** �����ַ */   
    DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)g_stCommuUartCB.aucRxBuff; /** �ڴ��ַ  */     
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;                      /** dma���䷽�� */    
    DMA_InitStructure.DMA_BufferSize = COMMU_UART_RX_BUFF_LEN;                   /** ����DMA�ڴ���ʱ�������ĳ���  */    
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;             /** ����DMA���������ģʽ��һ������  */    
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;                      /** ����DMA���ڴ����ģʽ  */    
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;      /** ���������ֳ�  */    
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;              /** �ڴ������ֳ�  */   
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;                                /** ����DMA�Ĵ���ģʽ  */    
    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;                      /** ����DMA�����ȼ���  */     
    DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;                       /** ָ�����FIFOģʽ��ֱ��ģʽ������ָ������ �� ��ʹ��FIFOģʽ  */          
    DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;            /** ָ����FIFO��ֵˮƽ  */          
    DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;                  /** ָ����Burstת�������ڴ洫�� */     
    DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;          /** ָ����Burstת��������Χת�� */           
    DMA_Init(COMMU_XBEE_UART_RX_DMA_STREAM, &DMA_InitStructure);                 /** ����DMA1��ͨ�� */                
    DMA_Cmd(COMMU_XBEE_UART_RX_DMA_STREAM, ENABLE);                              /** ʹ��ͨ�� */ 


    /*!< ------��ʼ�����ڲ���------ */
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;    
    USART_InitStructure.USART_StopBits = USART_StopBits_1;    
    USART_InitStructure.USART_Parity = USART_Parity_No;    
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;    
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;      
    USART_InitStructure.USART_BaudRate = COMMU_XBEE_UART_BAUDRATE;   
    /*!< ��ʼ������ */  
    USART_Init(COMMU_XBEE_UART,&USART_InitStructure);    
      
    /*!< �ж����� */ 
    USART_ITConfig(COMMU_XBEE_UART, USART_IT_TC, DISABLE);  
    USART_ITConfig(COMMU_XBEE_UART, USART_IT_RXNE, DISABLE);  
    USART_ITConfig(COMMU_XBEE_UART, USART_IT_IDLE, ENABLE);  
    
    /*!< --�����ж�-- */
    NVIC_InitStructure.NVIC_IRQChannel = COMMU_XBEE_UART_IRQn; /** ͨ������Ϊ�����ж� */ 
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  /** �ж�ռ�ȵȼ� */ 
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;         /** �ж���Ӧ���ȼ� */  
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;            /** ���ж� */   
    NVIC_Init(&NVIC_InitStructure);     
     
    /*!< ����DMA��ʽ����  */
    USART_DMACmd(COMMU_XBEE_UART, USART_DMAReq_Tx, ENABLE);  
    /*!< ����DMA��ʽ����  */
    USART_DMACmd(COMMU_XBEE_UART, USART_DMAReq_Rx, ENABLE);  
  
    /*!< �ж�����  */
    USART_ITConfig(COMMU_XBEE_UART, USART_IT_TC, DISABLE);  
    USART_ITConfig(COMMU_XBEE_UART, USART_IT_RXNE, DISABLE);  
    USART_ITConfig(COMMU_XBEE_UART, USART_IT_TXE, DISABLE);  
    USART_ITConfig(COMMU_XBEE_UART, USART_IT_IDLE, ENABLE);    
    /*!< �������� */   
    USART_Cmd(COMMU_XBEE_UART, ENABLE);      


    /*!< ------GPIO����------ */
    /*!< ����IO��ʱ��  */      
    RCC_AHB1PeriphClockCmd(COMMU_XBEE_UART_TX_GPIO_CLK | COMMU_XBEE_UART_RX_GPIO_CLK, ENABLE);   
    GPIO_PinAFConfig(COMMU_XBEE_UART_TX_GPIO_PORT, COMMU_XBEE_UART_TX_SOURCE, COMMU_XBEE_UART_TX_AF);    
    GPIO_PinAFConfig(COMMU_XBEE_UART_RX_GPIO_PORT, COMMU_XBEE_UART_RX_SOURCE, COMMU_XBEE_UART_RX_AF);  
  
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;          
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;                /** ����:����ģʽ  */       
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;                  /** ���� */       
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;            /** IO���ٶ�  */    
    GPIO_InitStructure.GPIO_Pin = COMMU_XBEE_UART_TX_PIN;         /** �ܽ�ָ��  */    
    GPIO_Init(COMMU_XBEE_UART_TX_GPIO_PORT, &GPIO_InitStructure); /** ��ʼ��  */
         
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;      
    GPIO_InitStructure.GPIO_Pin = COMMU_XBEE_UART_RX_PIN;  
    GPIO_Init(COMMU_XBEE_UART_RX_GPIO_PORT, &GPIO_InitStructure);       
}

void Commu_Uart_Init(void)
{       
    _Commu_Uart_CB_Init();
    _Commu_Uart_Lowlevel_Init();
}
  

uint32_t Commu_uart_IsTxLineValid(void)
{
    return (g_stCommuUartCB.bIsSendIdleFlag == 1);
}

int32_t Commu_Uart_SendData(uint8_t *pData, uint8_t len)
{
    /*!< ��鴮���Ƿ���Է���  */
    while(!g_stCommuUartCB.bIsSendIdleFlag)
    g_stCommuUartCB.bIsSendIdleFlag = 0;      

    /*!< �������� */
    memcpy(g_stCommuUartCB.aucTxBuff, pData, len);   

    /*!< ���ô������ݳ���  */
    DMA_SetCurrDataCounter(COMMU_XBEE_UART_TX_DMA_STREAM, len);  
    /*!< ��DMA */  
    DMA_Cmd(COMMU_XBEE_UART_TX_DMA_STREAM, ENABLE);      

    return 0;    
}

void Commu_Uart_Subscribe(Accept_Func_Type Accept)
{
    uint32_t iLoop;

    for(iLoop = 0; iLoop < SZ_COMMU_Uart_ACCEPT_HDL_NUM; iLoop++)
    {
        if(NULL == g_stCommuUartCB.afAcceptHdlArray[iLoop])
        {
            g_stCommuUartCB.afAcceptHdlArray[iLoop] = Accept;
            break;
        }
    }     
}

void Commu_Uart_UnSubscribe(Accept_Func_Type Accept)
{
    uint32_t iLoop;
    
    for(iLoop = 0; iLoop < SZ_COMMU_Uart_ACCEPT_HDL_NUM; iLoop++)
    {
        if(Accept == g_stCommuUartCB.afAcceptHdlArray[iLoop])
        {
            g_stCommuUartCB.afAcceptHdlArray[iLoop] = NULL;
            break;
        }
    }       
}


void COMMU_XBEE_UART_DMA_TX_IRQHandler(void)  
{  
    if (DMA_GetITStatus(COMMU_XBEE_UART_TX_DMA_STREAM, COMMU_XBEE_UART_TX_DMA_IT_TCIF) != RESET)   
    {  
        /*!< �����־λ  */
        DMA_ClearFlag(COMMU_XBEE_UART_TX_DMA_STREAM, COMMU_XBEE_UART_TX_DMA_FLAG_TCIF);  
        /*!< �ر�DMA  */
        DMA_Cmd(COMMU_XBEE_UART_TX_DMA_STREAM, DISABLE);  

        g_stCommuUartCB.bIsSendIdleFlag = 1;
    }  
}  


void COMMU_XBEE_UART_IRQHandler(void)                                
{     
    uint32_t iLoop;
    uint32_t len = 0; 

    /*!< ��������жϴ���  */
    if(USART_GetITStatus(COMMU_XBEE_UART, USART_IT_IDLE) != RESET)  
    {  
        COMMU_XBEE_UART->SR;  
        COMMU_XBEE_UART->DR; /** ��USART_IT_IDLE��־, ����ʹ��USART_ClearITPendingBit(COMMU_XBEE_UART, USART_IT_IDLE)��
                                 ʹ��USART_ClearITPendingBit��IDLE��־��һ�ν��պ��ж�һֱ���� */
        DMA_Cmd(COMMU_XBEE_UART_RX_DMA_STREAM, DISABLE);  /** �ر�DMA */
        DMA_ClearFlag(COMMU_XBEE_UART_RX_DMA_STREAM, COMMU_XBEE_UART_RX_DMA_FLAG_TCIF); /** �����־λ */
          
        /*!< ��ý���֡֡�� */
        len = COMMU_UART_RX_BUFF_LEN - DMA_GetCurrDataCounter(COMMU_XBEE_UART_RX_DMA_STREAM);  
        if(len != 0)
        {
            //Commu_Uart_SendData(g_stCommuUartCB.aucRxBuff, len);
            
            len += g_stCommuUartCB.ucHalfFrameLen;
            memcpy(&g_stCommuUartCB.aucHalfFrameBuff[g_stCommuUartCB.ucHalfFrameLen], g_stCommuUartCB.aucRxBuff, len - g_stCommuUartCB.ucHalfFrameLen);
            if(len < SZ_COMMU_RCVFRAME_MIN_LEN)
            {
                g_stCommuUartCB.ucHalfFrameLen = len;
            }
            else
            {
                for(iLoop = 0; iLoop < SZ_COMMU_Uart_ACCEPT_HDL_NUM; iLoop++)
                {
                    if(g_stCommuUartCB.afAcceptHdlArray[iLoop] != NULL)
                    {
                        g_stCommuUartCB.afAcceptHdlArray[iLoop](g_stCommuUartCB.aucHalfFrameBuff, len);
                    }                
                }  
                g_stCommuUartCB.ucHalfFrameLen = 0;
            }
        }
          
        /*!< ���ô������ݳ��� */
        DMA_SetCurrDataCounter(COMMU_XBEE_UART_RX_DMA_STREAM, COMMU_UART_RX_BUFF_LEN);  
        /*!< ��DMA  */
        DMA_Cmd(COMMU_XBEE_UART_RX_DMA_STREAM, ENABLE);  
    }         
} 

    
/**************** (C) COPYRIGHT 2010-2018 Efficient *****END OF FILE***********/
