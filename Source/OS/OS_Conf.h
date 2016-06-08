/*******************************************************************************
        (c) COPYRIGHT 2010-2018 by Efficient Systems, Inc.    
                          All rights reserved.
    
       This software is confidential and proprietary to Efficient 
     Systems, Inc.  No part of this software may be reproduced,    
     stored, transmitted, disclosed or used in any form or by any means
     other than as expressly provided by the written license agreement    
     between Efficient Systems and its licensee.
 FileName    : OS_Conf.h
 Author      : ranwei
 Version     : 
 Date        : 2016/1/21 16:25:42:809
 Description : 
 Others      : 
*******************************************************************************/
#ifndef __OS_CONF_H__
#define __OS_CONF_H__

/* Uncomment the next line to choose avalable period */
//#define OS_PERIOD  1000 /* 1ms */
//#define OS_PERIOD  1000000 /* 1us */
//#define OS_PERIOD 2000 /* 500us */
//#define OS_PERIOD 5000 /* 200us */
#define OS_PERIOD 10000 /* 100us */


#define OS_PERIOD_UNIT_1MS *OS_PERIOD/1000

#endif /* __OS_CONF_H__ */



OS_TASK(TEST1, test1_PerioProc, test1_LoopProc, test1_Init, EN_TASK_Periodic, 500 OS_PERIOD_UNIT_1MS, 500 OS_PERIOD_UNIT_1MS, "hello test1")   
OS_TASK(TEST2, test2_PerioProc, test2_LoopProc, test2_Init, EN_TASK_Periodic, 500 OS_PERIOD_UNIT_1MS, 500 OS_PERIOD_UNIT_1MS, "ranwei")  
OS_TASK(Commu, Task_Commu_PerioProc, Task_Commu_LoopProc, Task_Commu_Init, EN_TASK_Periodic, 1000 OS_PERIOD_UNIT_1MS, 1000 OS_PERIOD_UNIT_1MS, NULL)  


#undef  OS_TASK

/**************** (C) COPYRIGHT 2010-2018 Efficient *****END OF FILE***********/
