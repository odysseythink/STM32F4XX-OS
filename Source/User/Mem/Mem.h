/**
* @file      Mem.h
* @brief     
* @details   
* @author    ranwei
* @version     
* @date      2016/5/9 15:50:32:354
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
*         1.Date         -- 2016/5/9 15:50:32:354
*           Author       -- ranwei
*           Modification -- Created file
*
*/
#ifndef __MEM_H__
#define __MEM_H__

#ifdef __cplusplus
extern "C"{
#endif /** __cplusplus */

#ifdef  MEM_GLOBAL
#define MEM_EXT
#else
#define MEM_EXT extern
#endif /** MEM_GLOBAL */

/*============================================================================*/
/*                                  @INCLUDES                                 */
/*============================================================================*/
#include <stdint.h>


/*============================================================================*/
/*                              @MACROS & @TYPEDEFS                           */
/*============================================================================*/
/**
 * MEM_SIZE: the size of the heap memory. If the application will send
 * a lot of data that needs to be copied, this should be set high.
 */
#ifndef MEM_SIZE
#define MEM_SIZE                        1600
#endif

/**
 * MEM_ALIGNMENT: should be set to the alignment of the CPU
 *    4 byte alignment -> #define MEM_ALIGNMENT 4
 *    2 byte alignment -> #define MEM_ALIGNMENT 2
 */
#ifndef MEM_ALIGNMENT
#define MEM_ALIGNMENT                   1
#endif


/* MEM_SIZE would have to be aligned, but using 64000 here instead of
 * 65535 leaves some room for alignment...
 */
#if MEM_SIZE > 64000l
typedef uint32_t Mem_Size_T;
#else
typedef uint16_t Mem_Size_T;
#endif /* MEM_SIZE > 64000 */

#ifndef LWIP_MEM_ALIGN_SIZE
#define LWIP_MEM_ALIGN_SIZE(size) (((size) + MEM_ALIGNMENT - 1) & ~(MEM_ALIGNMENT-1))
#endif

#ifndef LWIP_MEM_ALIGN
#define LWIP_MEM_ALIGN(addr) ((void *)(((uint32_t)(addr) + MEM_ALIGNMENT - 1) & ~(uint32_t)(MEM_ALIGNMENT - 1)))
#endif



/*============================================================================*/
/*                               @GLOBAL VIRIABLES                            */
/*============================================================================*/

/*============================================================================*/
/*                                    @FUNCS                                  */
/*============================================================================*/
void  Mem_Init(void);
void *Mem_Realloc(void *mem, Mem_Size_T size);
void *Mem_Malloc(Mem_Size_T size);
void  Mem_Free(void *mem);



#ifdef __cplusplus
}
#endif /** __cplusplus */

#endif /** __MEM_H__ */
/**************** (C) COPYRIGHT 2010-2018 Efficien ******END OF FILE***********/
