/**
* @file      Commu_Uart.h
* @brief     
* @details   
* @author    ranwei
* @version     
* @date      2016/5/11 11:12:33:80
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
*         1.Date         -- 2016/5/11 11:12:33:80
*           Author       -- ranwei
*           Modification -- Created file
*
*/
#ifndef __COMMU_UART_H__
#define __COMMU_UART_H__

#ifdef __cplusplus
extern "C"{
#endif /** __cplusplus */

#ifdef  COMMU_UART_GLOBAL
#define COMMU_UART_EXT
#else
#define COMMU_UART_EXT extern
#endif /** COMMU_UART_GLOBAL */

/*============================================================================*/
/*                                  @INCLUDES                                 */
/*============================================================================*/
#include <stdint.h>


/*============================================================================*/
/*                              @MACROS & @TYPEDEFS                           */
/*============================================================================*/
#define __COMMU_USE_UART4

/** 经测试，发送和接收DMA缓冲区的最大值为255 */
#define SZ_COMMU_DMA_BUFF_MAX 255 

typedef void (*Accept_Func_Type)(uint8_t *pucData, uint16_t uslen);



/*============================================================================*/
/*                               @GLOBAL VIRIABLES                            */
/*============================================================================*/

/*============================================================================*/
/*                                    @FUNCS                                  */
/*============================================================================*/
void Commu_Uart_Init(void);
int32_t Commu_Uart_SendData(uint8_t *pData, uint8_t len);
void Commu_Uart_Subscribe(Accept_Func_Type Accept);
void Commu_Uart_UnSubscribe(Accept_Func_Type Accept);
uint32_t Commu_Uart_IsTxLineValid(void);



#ifdef __cplusplus
}
#endif /** __cplusplus */

#endif /** __COMMU_UART_H__ */
/**************** (C) COPYRIGHT 2010-2018 Efficien ******END OF FILE***********/
