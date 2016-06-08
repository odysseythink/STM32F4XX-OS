/**
* @file      main.h
* @brief     
* @details   
* @author    ranwei
* @version     
* @date      2016/6/8 18:9:42:726
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
*         1.Date         -- 2016/6/8 18:9:42:726
*           Author       -- ranwei
*           Modification -- Created file
*
*/
#ifndef __MAIN_H__
#define __MAIN_H__

#ifdef __cplusplus
extern "C"{
#endif /** __cplusplus */

#ifdef  MAIN_GLOBAL
#define MAIN_EXT
#else
#define MAIN_EXT extern
#endif /** MAIN_GLOBAL */

/*============================================================================*/
/*                                  @INCLUDES                                 */
/*============================================================================*/

/*============================================================================*/
/*                              @MACROS & @TYPEDEFS                           */
/*============================================================================*/
typedef void (*Init_Func_Type)(void); /** ��ʼ������ */

#define SECTION(x)                    __attribute__((section(x)))  /** ����һ���� */
#define UNUSED                        __attribute__((unused))  /** ���߱����������εı�����ʹ�ã��ñ�������Ҫ��δʹ�õĴ��� */
#define USED                          __attribute__((used))    /** ���߱��������������εľ�̬�������������Ƿ񱻵��� */
#define ALIGN(n)                      __attribute__((aligned(n)))  
#define UserSys_InitFunc_Register(x)  static const Init_Func_Type __init_func_##x  SECTION("sys_init_func") USED = (x);  


#pragma pack(push, 1)

typedef struct{
    uint8_t  Reserve1;
}ST_MainSystem_CB_Type;
#pragma pack(pop)


/*============================================================================*/
/*                               @GLOBAL VIRIABLES                            */
/*============================================================================*/
MAIN_EXT ST_MainSystem_CB_Type g_stMainSystemCB;


/*============================================================================*/
/*                                    @FUNCS                                  */
/*============================================================================*/

#ifdef __cplusplus
}
#endif /** __cplusplus */

#endif /** __MAIN_H__ */
/**************** (C) COPYRIGHT 2010-2018 Efficien ******END OF FILE***********/
