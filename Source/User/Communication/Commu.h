/**
* @file      Commu.h
* @brief     
* @details   
* @author    ranwei
* @version     
* @date      2016/5/11 16:10:26:163
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
*         1.Date         -- 2016/5/11 16:10:26:163
*           Author       -- ranwei
*           Modification -- Created file
*
*/
#ifndef __COMMU_H__
#define __COMMU_H__

#ifdef __cplusplus
extern "C"{
#endif /** __cplusplus */

#ifdef  COMMU_GLOBAL
#define COMMU_EXT
#else
#define COMMU_EXT extern
#endif /** COMMU_GLOBAL */

/*============================================================================*/
/*                                  @INCLUDES                                 */
/*============================================================================*/
#include <stdint.h>


/*============================================================================*/
/*                              @MACROS & @TYPEDEFS                           */
/*============================================================================*/

/*============================================================================*/
/*                               @GLOBAL VIRIABLES                            */
/*============================================================================*/

/*============================================================================*/
/*                                    @FUNCS                                  */
/*============================================================================*/
int32_t Commu_SendData(uint8_t *pData, uint8_t len);
void Commu_LoopProc(void *arg);
void Commu_PerioProc(void *arg);
void Commu_Init(void);



#ifdef __cplusplus
}
#endif /** __cplusplus */

#endif /** __COMMU_H__ */
/**************** (C) COPYRIGHT 2010-2018 Efficien ******END OF FILE***********/
