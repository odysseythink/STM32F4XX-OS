/**
* @file      List.h
* @brief     
* @details   
* @author    ranwei
* @version     
* @date      2016/5/11 14:42:12:758
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
*         1.Date         -- 2016/5/11 14:42:12:758
*           Author       -- ranwei
*           Modification -- Created file
*
*/
#ifndef __LIST_H__
#define __LIST_H__

#ifdef __cplusplus
extern "C"{
#endif /** __cplusplus */

#ifdef  LIST_GLOBAL
#define LIST_EXT
#else
#define LIST_EXT extern
#endif /** LIST_GLOBAL */

/*============================================================================*/
/*                                  @INCLUDES                                 */
/*============================================================================*/
#include <stdint.h>


/*============================================================================*/
/*                              @MACROS & @TYPEDEFS                           */
/*============================================================================*/
#pragma pack(push, 1)

typedef struct ST_List_Node{
    void *pData;
    struct ST_List_Node *pre, *next;
}ST_List_Node_T;

typedef struct ST_List{
    ST_List_Node_T *pHead, *pTail;
    uint8_t ucLen;

    void (*HeadInsert)(struct ST_List *this, void *pData);
    void (*TailInsert)(struct ST_List *this, void *pData);
    void *(*HeadRemove)(struct ST_List *this);
    void *(*TailRemove)(struct ST_List *this);    
}ST_List_T;

#pragma pack(pop)

typedef ST_List_T List;





/*============================================================================*/
/*                               @GLOBAL VIRIABLES                            */
/*============================================================================*/

/*============================================================================*/
/*                                    @FUNCS                                  */
/*============================================================================*/
List *List_Create(void);
void List_Destroy(List *this);


#ifdef __cplusplus
}
#endif /** __cplusplus */

#endif /** __LIST_H__ */
/**************** (C) COPYRIGHT 2010-2018 Efficien ******END OF FILE***********/
