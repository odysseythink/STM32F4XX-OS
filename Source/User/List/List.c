/**
* @file      List.c
* @brief     
* @details   
* @author    ranwei
* @version     
* @date      2016/5/11 14:41:52:551
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
*         1.Date         -- 2016/5/11 14:41:52:551
*           Author       -- ranwei
*           Modification -- Created file
*
*/
    
#define  LIST_GLOBAL

/* includes-------------------------------------------------------------------*/
#include <stdio.h>
#include "Mem\Mem.h"
#include "List\List.h"
    
/* Private typedef&macro&definde----------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* External functions --------------------------------------------------------*/
/* External variables --------------------------------------------------------*/

/*
 * Delete a list entry by making the prev/next entries
 * point to each other.
 *
 * This is only for internal list manipulation where we know
 * the prev/next entries already!
 */
static void __List_Node_del(ST_List_Node_T* prev, ST_List_Node_T* next)
{
    next->pre = prev;
    prev->next = next;
}

/*
 * Insert a new entry between two known consecutive entries.
 *
 * This is only for internal list manipulation where we know
 * the prev/next entries already!
 */
static void __List_Node_add(ST_List_Node_T *new, ST_List_Node_T *prev, ST_List_Node_T *next)
{
    next->pre = new;
    new->next = next;
    new->pre = prev;
    prev->next = new;
}

static void _List_HeadInsert(List *this, void *pData)
{
    ST_List_Node_T *pNode = NULL; 
    if(this != NULL)
    {
        pNode = (ST_List_Node_T *)Mem_Malloc(sizeof(ST_List_Node_T));
        if(NULL == pNode)
        {
            return;
        }
        pNode->pData = pData;
        
        if(0 == this->ucLen)
        {
            pNode->next = pNode->pre = pNode;
            this->pHead = this->pTail = pNode;
        }
        else
        {
            __List_Node_add(pNode, this->pHead->pre, this->pHead);
            this->pHead = pNode;
        }
        this->ucLen++;
    }
}

static void _List_TailInsert(List *this, void *pData)
{
    ST_List_Node_T *pNode = NULL; 
    if(this != NULL)
    {
        pNode = (ST_List_Node_T *)Mem_Malloc(sizeof(ST_List_Node_T));
        if(NULL == pNode)
        {
            return;
        }
        pNode->pData = pData;
        
        if(0 == this->ucLen)
        {
            pNode->next = pNode->pre = pNode;
            this->pHead = this->pTail = pNode;
        }
        else
        {
            __List_Node_add(pNode, this->pTail, this->pTail->next);
            this->pTail= pNode;
        }
        this->ucLen++;
    }
}

static void *_List_HeadRemove(List *this)
{
    ST_List_Node_T *pNode = NULL; 
    void *pData = NULL;
    if(this != NULL)
    {
        pNode = this->pHead;
        pData = pNode->pData;

        if(1 == this->ucLen)
        {
            this->pHead = this->pTail = NULL;
        }
        else
        {
            __List_Node_del(pNode->pre, pNode->next);
            this->pHead = pNode->next;
        }
        Mem_Free(pNode);
        this->ucLen--;
        return pData;
    }
    
    return NULL;
}

static void *_List_TailRemove(List *this)
{
    ST_List_Node_T *pNode = NULL; 
    void *pData = NULL;
    if(this != NULL)
    {
        pNode = this->pTail;
        pData = pNode->pData;

        if(1 == this->ucLen)
        {
            this->pHead = this->pTail = NULL;
        }
        else
        {
            __List_Node_del(pNode->pre, pNode->next);
            this->pTail= pNode->pre;
        }
        Mem_Free(pNode);
        this->ucLen--;
        return pData;
    }
    
    return NULL;
}


static void List_Init(List *this)
{
    if(this != NULL)
    {
        this->pHead = NULL;
        this->pTail = NULL;
        this->ucLen = 0;

        this->HeadInsert = _List_HeadInsert;
        this->TailInsert = _List_TailInsert;
        this->TailRemove = _List_TailRemove;
        this->HeadRemove = _List_HeadRemove;
    }
}

static void List_Cleanup(List *this)
{
    ST_List_Node_T *pNode = NULL;
    
    if(this != NULL)
    {
        while(this->ucLen)
        {
            if(1 == this->ucLen)
            {
                pNode = this->pHead;
                if(pNode->pData != NULL)
                {
                    Mem_Free(pNode->pData);
                }
                Mem_Free(pNode);                
            }
            else
            {
                pNode = this->pHead;
                __List_Node_del(pNode->pre, pNode->next);
                this->pHead = pNode->next;
                if(pNode->pData != NULL)
                {
                    Mem_Free(pNode->pData);
                }
                Mem_Free(pNode);
            }
            this->ucLen--;
        }
    }    
}


List *List_Create()
{
    List *pList = (List *)Mem_Malloc(sizeof(List));
    if(pList != NULL)    
    {
        List_Init(pList);
    }
    return pList;
}

void List_Destroy(List *this)
{
    if(this != NULL)
    {
        List_Cleanup(this);
        Mem_Free(this);
    }
}


    
/**************** (C) COPYRIGHT 2010-2018 Efficient *****END OF FILE***********/
