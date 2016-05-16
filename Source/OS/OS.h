/*******************************************************************************
        (c) COPYRIGHT 2010-2018 by Efficient Systems, Inc.    
                          All rights reserved.
    
       This software is confidential and proprietary to Efficient 
     Systems, Inc.  No part of this software may be reproduced,    
     stored, transmitted, disclosed or used in any form or by any means
     other than as expressly provided by the written license agreement    
     between Efficient Systems and its licensee.
 FileName    : OS.h
 Author      : ranwei
 Version     : 
 Date        : 2016/1/21 16:5:1:93
 Description : 
 Others      : 
*******************************************************************************/
#ifndef __OS_H__
#define __OS_H__

#ifdef __cplusplus
extern "C"{
#endif

#ifdef  OS_GLOBAL
#define OS_EXT
#else
#define OS_EXT extern
#endif /* __cplusplus */

/*============================================================================*/
/*                                  @INCLUDES                                 */
/*============================================================================*/
#include <stdint.h>


/*============================================================================*/
/*                              @MACROS & @TYPEDEFS                           */
/*============================================================================*/
typedef enum{
    EN_TASK_Periodic,
    EN_TASK_OneShot,
}EN_TASK_Mode_Type;

typedef void (* Task_Periodic_Func_Type)(void *arg);
typedef void (* Task_Loop_Func_Type)(void *arg);
typedef void (* Task_Init_Func_Type)(void);

typedef struct _Task{
    Task_Periodic_Func_Type periodicFunc;
    Task_Loop_Func_Type loopFunc;
    Task_Init_Func_Type initFunc;
    EN_TASK_Mode_Type mode;
    uint16_t period;
    uint16_t periodBackup;
    void *arg;
}Task;




/*============================================================================*/
/*                               @GLOBAL VIRIABLES                            */
/*============================================================================*/



/*============================================================================*/
/*                                    @FUNCS                                  */
/*============================================================================*/
void OS_Init(void);
void OS_Loop(void);
void OS_Time_Update(void);



#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __OS_H__ */
/**************** (C) COPYRIGHT 2010-2018 Efficient *****END OF FILE***********/
