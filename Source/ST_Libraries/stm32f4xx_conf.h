/*******************************************************************************
                     (C) COPYRIGHT 2011 STMicroelectronics    
                          All rights reserved.
    

    
 FileName    : stm32f4xx_conf.h
 Author      : ranwei    
 Version     : 
 Date        : 2015/5/15 9:19:45
 Description : 
 Others      : 
 attention   : THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING
               CUSTOMERS WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN 
               ORDER FOR THEM TO SAVE TIME. AS A RESULT, STMICROELECTRONICS 
               SHALL NOT BE HELD LIABLE FOR ANY DIRECT, INDIRECT OR 
               CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
               CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
               CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR 
               PRODUCTS.
*******************************************************************************/

#ifndef __STM32F4xx_CONF_H__
#define __STM32F4xx_CONF_H__


/*============================================================================*/
/*                                  @INCLUDES                                 */
/*============================================================================*/
/* Uncomment the line below to enable peripheral header file inclusion */
//#include "STM32F4XX_StdPeriph_Driver\stm32f4xx_adc.h"
//#include "STM32F4XX_StdPeriph_Driver\stm32f4xx_can.h"
//#include "STM32F4XX_StdPeriph_Driver\stm32f4xx_crc.h"
//#include "STM32F4XX_StdPeriph_Driver\stm32f4xx_cryp.h"
//#include "STM32F4XX_StdPeriph_Driver\stm32f4xx_dac.h"
//#include "STM32F4XX_StdPeriph_Driver\stm32f4xx_dbgmcu.h"
//#include "STM32F4XX_StdPeriph_Driver\stm32f4xx_dcmi.h"
#include "STM32F4XX_StdPeriph_Driver\stm32f4xx_dma.h"
#include "STM32F4XX_StdPeriph_Driver\stm32f4xx_exti.h"
#include "STM32F4XX_StdPeriph_Driver\stm32f4xx_flash.h"
//#include "STM32F4XX_StdPeriph_Driver\stm32f4xx_fsmc.h"
//#include "STM32F4XX_StdPeriph_Driver\stm32f4xx_hash.h"
#include "STM32F4XX_StdPeriph_Driver\stm32f4xx_gpio.h"
#include "STM32F4XX_StdPeriph_Driver\stm32f4xx_i2c.h"
#include "STM32F4XX_StdPeriph_Driver\stm32f4xx_iwdg.h"
#include "STM32F4XX_StdPeriph_Driver\stm32f4xx_pwr.h"
#include "STM32F4XX_StdPeriph_Driver\stm32f4xx_rcc.h"
#include "STM32F4XX_StdPeriph_Driver\stm32f4xx_rng.h"
#include "STM32F4XX_StdPeriph_Driver\stm32f4xx_rtc.h"
#include "STM32F4XX_StdPeriph_Driver\stm32f4xx_sdio.h"
//#include "STM32F4XX_StdPeriph_Driver\stm32f4xx_spi.h"
#include "STM32F4XX_StdPeriph_Driver\stm32f4xx_syscfg.h"
//#include "STM32F4XX_StdPeriph_Driver\stm32f4xx_tim.h"
#include "STM32F4XX_StdPeriph_Driver\stm32f4xx_usart.h"
//#include "STM32F4XX_StdPeriph_Driver\stm32f4xx_wwdg.h"
#include "STM32F4XX_StdPeriph_Driver\misc.h" /* High level functions for NVIC and SysTick (add-on to CMSIS functions) */



/*============================================================================*/
/*                              @MACROS & @TYPEDEFS                           */
/*============================================================================*/
/* 
** If an external clock source is used, then the value of the following define 
** should be set to the value of the external clock source, else, if no external 
** clock is used, keep this define commented 
*/
/*#define I2S_EXTERNAL_CLOCK_VAL   12288000 */ /* Value of the external clock in Hz */


/*
** Uncomment the line below to expanse the "assert_param" macro in the 
** Standard Peripheral Library drivers code 
*/
/* #define USE_FULL_ASSERT    1 */


#ifdef  USE_FULL_ASSERT
/*******************************************************************************
** @Fn     :
**
** @Brief  : The assert_param macro is used for function's parameters check.
**
** @Param  :
**    <input>
**            expr -- If expr is false, it calls assert_failed function  which 
**                    reports the name of the source file and the source line 
**                    number of the call that failed. If expr is true, it 
**                    returns no value.
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
#define assert_param(expr) ((expr) ? (void)0 : assert_failed((uint8_t *)__FILE__, __LINE__))

void assert_failed(uint8_t* file, uint32_t line);
#else
#define assert_param(expr) ((void)0)
#endif /* USE_FULL_ASSERT */

#endif /* __STM32F4xx_CONF_H__ */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
