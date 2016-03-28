/*******************************************************************************
        (c) COPYRIGHT 2010-2018 by Efficient Systems, Inc.    
                          All rights reserved.
    
       This software is confidential and proprietary to Efficient 
     Systems, Inc.  No part of this software may be reproduced,    
     stored, transmitted, disclosed or used in any form or by any means
     other than as expressly provided by the written license agreement    
     between Efficient Systems and its licensee.
 FileName    : main.c
 Author      : ranwei
 Version     : 
 Date        : 2016/1/25 19:12:14:221
 Description : 
 Others      : 
*******************************************************************************/
    
#define  MAIN_GLOBAL

/* includes-------------------------------------------------------------------*/
#include <stddef.h>
#include <string.h>
#include <stdarg.h>
#include "main_conf.h"
#include <stdio.h>
#include "serial_debug\serial_debug.h"
#include "OS.h"

    
/* Private macro&definde------------------------------------------------------*/
#define __MAIN_PROMPT__
#define __MAIN_ASSERT__



/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* External functions --------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
    
/*******************************************************************************
 Prototype    : Main_Prompt
 Description  : main prompt function
 Input        : 
                
                
                
 Output       : 
 Return Value : static
 Calls        : 
 Called By    : 
 
 History      :
  1.Date         -- 2016/1/25 19:12:55:792
    Author       -- ranwei
    Modification -- Created function

*******************************************************************************/
static void Main_Prompt(int line, const char *func, const char *format, ...)
#ifdef __MAIN_PROMPT__
{
    va_list args;

    va_start(args, format);
    __Prompt__(__FILE__, line, func, format, args);
    va_end(args);    
}
#else
{
}
#endif

/*******************************************************************************
 Prototype    : Main_Assert
 Description  : main assert function
 Input        : 
                
                
                
 Output       : 
 Return Value : static
 Calls        : 
 Called By    : 
 
 History      :
  1.Date         -- 2016/1/25 19:13:10:862
    Author       -- ranwei
    Modification -- Created function

*******************************************************************************/
static void Main_Assert(int line, const char *func, const char *format, ...)
#ifdef __MAIN_ASSERT__
{
    va_list args;

    va_start(args, format);
    __Assert__(__FILE__, line, func, format, args);
    va_end(args);    
}
#else
{
}
#endif


void test1_Init(void)
{
    printf("task test1 init\n");
}

void test2_Init(void)
{
    printf("task test2 init\n");
}


void test1_task(void *arg)
{
    printf("Hello world, task %s\n", (char *)arg);
}

void test2_task(void *arg)
{
    printf("Hello world, task %s\n", (char *)arg);
}




/*******************************************************************************
** @Fn     :
**
** @Brief  : At this stage the microcontroller clock setting is already 
**           configured to 168 MHz, this is done through SystemInit() function 
**           which is called from startup file (startup_stm32f4xx.s) before to 
**           branch to application main. To reconfigure the default setting of 
**           SystemInit() function, refer to system_stm32f4xx.c file
**
** @Param  :
**    <input>
**            none.
**    </input>
**
**    <output>
**            none.
**    </output>
**
** @Return :
**
** @Note   :
*******************************************************************************/  
int main(void)
{        
    NVIC_SetVectorTable(0x8000000, 0x40000);	
#ifdef SERIAL_DEBUG
    DebugComPort_Init();
    printf("------------------------------------------------------------------------------------------------");printf("\n");
    printf("                                                                                                ");printf("\n");
    printf("  ***    *****   *   *    ***     ***    *****      *    *   *   *   *            ***     ***   ");printf("\n");
    printf(" *   *     *     ** **   *   *   *   *   *         **    *   *   *   *           *   *   *   *  ");printf("\n");
    printf(" *         *     * * *       *       *   *        * *     * *     * *            *   *   *      ");printf("\n");
    printf("  ***      *     * * *     **      **    ****    *  *      *       *     *****   *   *    ***   ");printf("\n");
    printf("     *     *     *   *       *    *      *       *****    * *     * *            *   *       *  ");printf("\n");
    printf(" *   *     *     *   *   *   *   *       *          *    *   *   *   *           *   *   *   *  ");printf("\n");
    printf("  ***      *     *   *    ***    *****   *          *    *   *   *   *            ***     ***   ");printf("\n");
    printf("                                                                                                ");printf("\n");
    printf("                                                     %s", __SYSTEM_VERSION);printf("\n");
    printf("------------------------------------------------------------------------------------------------");printf("\n");

#endif
    Main_Prompt(__LINE__, __FUNCTION__, "System start");

    OS_Init();     

    for(;;)
    {
        OS_Loop();			
    }
    
}




#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {}
}
#endif


    
/**************** (C) COPYRIGHT 2010-2018 Efficient *****END OF FILE***********/
