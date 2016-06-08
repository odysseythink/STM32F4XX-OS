/**
* @file      Mem.c
* @brief     
* @details   
* @author    ranwei
* @version     
* @date      2016/5/9 15:50:9:264
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
*         1.Date         -- 2016/5/9 15:50:9:264
*           Author       -- ranwei
*           Modification -- Created file
*
*/
    
#define  MEM_GLOBAL

/* includes-------------------------------------------------------------------*/
#include "serial_debug\serial_debug.h"
#include "Mem\Mem.h"
#include "main.h"
    
/* Private typedef&macro&definde----------------------------------------------*/
#ifdef SERIAL_DEBUG
    #define __Mem_PROMPT__
    #define __Mem_ASSERT__
#endif



/**
 * The heap is made up as a list of structs of this type.
 * This does not have to be aligned since for getting its size,
 * we only use the macro SIZEOF_STRUCT_MEM, which automatically alignes.
 */ 
typedef struct mem {
    /** index (-> ram[next]) of the next struct */
    Mem_Size_T next;
    /** index (-> ram[next]) of the next struct */
    Mem_Size_T prev;
    /** 1: this area is used; 0: this area is unused */
    uint8_t used;
}ST_Mem_T;

/** All allocated blocks will be MIN_SIZE bytes big, at least!
 * MIN_SIZE can be overridden to suit your needs. Smaller values save space,
 * larger values could prevent too small blocks to fragment the RAM too much. */
#ifndef MIN_SIZE
#define MIN_SIZE             12
#endif /* MIN_SIZE */
/* some alignment macros: we define them here for better source code layout */
#define MIN_SIZE_ALIGNED     LWIP_MEM_ALIGN_SIZE(MIN_SIZE)
#define SIZEOF_STRUCT_MEM    LWIP_MEM_ALIGN_SIZE(sizeof(struct mem))
#define MEM_SIZE_ALIGNED     LWIP_MEM_ALIGN_SIZE(MEM_SIZE)

/** the heap. we need one struct mem at the end and some room for alignment */
static uint8_t ram_heap[MEM_SIZE_ALIGNED + (2*SIZEOF_STRUCT_MEM) + MEM_ALIGNMENT];
/** pointer to the heap (ram_heap): for alignment, ram is now a pointer instead of an array */
static uint8_t *ram;
/** the last entry, always unused! */
static ST_Mem_T *ram_end;
/** pointer to the lowest free block, this is used for faster search */
static ST_Mem_T *lfree;




/* Private variables ---------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* External functions --------------------------------------------------------*/
/* External variables --------------------------------------------------------*/

static void _Mem_Prompt(int line, const char *func, const char *format, ...)
#ifdef __Mem_PROMPT__
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


static void _Mem_Assert(int line, const char *func, uint8_t assertion, const char *format, ...)
#ifdef __Mem_ASSERT__
{
    va_list args;

    if(!assertion)
    {
        va_start(args, format);
        __Assert__(__FILE__, line, func, format, args);
        va_end(args);    
    }
}
#else
{
}
#endif



/**
 * "Plug holes" by combining adjacent empty struct mems.
 * After this function is through, there should not exist
 * one empty struct mem pointing to another empty struct mem.
 *
 * @param mem this points to a struct mem which just has been freed
 * @internal this function is only called by mem_free() and mem_realloc()
 *
 * This assumes access to the heap is protected by the calling function
 * already.
 */
static void plug_holes(ST_Mem_T *mem)
{
    ST_Mem_T *nmem;
    ST_Mem_T *pmem;

    _Mem_Assert(__LINE__, __FUNCTION__, (uint8_t *)mem >= ram, "mem >= ram");
    _Mem_Assert(__LINE__, __FUNCTION__, (uint8_t *)mem < (uint8_t *)ram_end, "mem < ram_end");
    _Mem_Assert(__LINE__, __FUNCTION__, mem->used == 0, "mem->used == 0");

    /* plug hole forward */
    _Mem_Assert(__LINE__, __FUNCTION__, mem->next <= MEM_SIZE_ALIGNED, "mem->next <= MEM_SIZE_ALIGNED");

    nmem = (ST_Mem_T *)&ram[mem->next];
    if(mem != nmem && nmem->used == 0 && (uint8_t *)nmem != (uint8_t *)ram_end) 
    {
        /* if mem->next is unused and not end of ram, combine mem and mem->next */
        if(lfree == nmem) 
        {
            lfree = mem;
        }
        mem->next = nmem->next;
        ((ST_Mem_T *)&ram[nmem->next])->prev = (uint8_t *)mem - ram;
    }

    /* plug hole backward */
    pmem = (ST_Mem_T *)&ram[mem->prev];
    if(pmem != mem && pmem->used == 0)
    {
        /* if mem->prev is unused, combine mem and mem->prev */
        if(lfree == mem) 
        {
            lfree = pmem;
        }
        pmem->next = mem->next;
        ((ST_Mem_T *)&ram[mem->next])->prev = (uint8_t *)pmem - ram;
    }
}

/**
 * Zero the heap and initialize start, end and lowest-free
 */
void Mem_Init(void)
{
    ST_Mem_T *mem;

    _Mem_Assert(__LINE__, __FUNCTION__, (SIZEOF_STRUCT_MEM & (MEM_ALIGNMENT-1)) == 0, "Sanity check alignment");

    /* align the heap */
    ram = LWIP_MEM_ALIGN(ram_heap);
    /* initialize the start of the heap */
    mem = (ST_Mem_T *)ram;
    mem->next = MEM_SIZE_ALIGNED;
    mem->prev = 0;
    mem->used = 0;
    /* initialize the end of the heap */
    ram_end = (ST_Mem_T *)&ram[MEM_SIZE_ALIGNED];
    ram_end->used = 1;
    ram_end->next = MEM_SIZE_ALIGNED;
    ram_end->prev = MEM_SIZE_ALIGNED;

    /* initialize the lowest-free pointer to the start of the heap */
    lfree = (ST_Mem_T *)ram;
}


/**
 * Put a struct mem back on the heap
 *
 * @param rmem is the data portion of a struct mem as returned by a previous
 *             call to mem_malloc()
 */
void Mem_Free(void *rmem)
{
    struct mem *mem;

    if (rmem == NULL) 
    {
        _Mem_Prompt(__LINE__, __FUNCTION__, "mem_free(p == NULL) was called.");
        return;
    }
    _Mem_Assert(__LINE__, __FUNCTION__, (((uint32_t)rmem) & (MEM_ALIGNMENT-1)) == 0, "sanity check alignment");
    _Mem_Assert(__LINE__, __FUNCTION__, (uint8_t *)rmem >= (uint8_t *)ram && (uint8_t *)rmem < (uint8_t *)ram_end, "legal memory");

    if ((uint8_t *)rmem < (uint8_t *)ram || (uint8_t *)rmem >= (uint8_t *)ram_end) 
    {
        _Mem_Prompt(__LINE__, __FUNCTION__, "illegal memory");
        return;
    }
    
    /* Get the corresponding struct mem ... */
    mem = (struct mem *)((uint8_t *)rmem - SIZEOF_STRUCT_MEM);
    /* ... which has to be in a used state ... */
    _Mem_Assert(__LINE__, __FUNCTION__, mem->used, "mem->used");

    /* ... and is now unused. */
    mem->used = 0;

    if (mem < lfree) 
    {
        /* the newly freed struct is now the lowest */
        lfree = mem;
    }

    /* finally, see if prev or next are free also */
    plug_holes(mem);
}

/**
 * In contrast to its name, mem_realloc can only shrink memory, not expand it.
 * Since the only use (for now) is in pbuf_realloc (which also can only shrink),
 * this shouldn't be a problem!
 *
 * @param rmem pointer to memory allocated by mem_malloc the is to be shrinked
 * @param newsize required size after shrinking (needs to be smaller than or
 *                equal to the previous size)
 * @return for compatibility reasons: is always == rmem, at the moment
 *         or NULL if newsize is > old size, in which case rmem is NOT touched
 *         or freed!
 */
void* Mem_Realloc(void *rmem, Mem_Size_T newsize)
{
    Mem_Size_T size;
    Mem_Size_T ptr, ptr2;
    struct mem *mem, *mem2;

    /* Expand the size of the allocated memory region so that we can
       adjust for alignment. */
    newsize = LWIP_MEM_ALIGN_SIZE(newsize);

    if(newsize < MIN_SIZE_ALIGNED) 
    {
        /* every data block must be at least MIN_SIZE_ALIGNED long */
        newsize = MIN_SIZE_ALIGNED;
    }

    if (newsize > MEM_SIZE_ALIGNED) 
    {
        return NULL;
    }

    _Mem_Assert(__LINE__, __FUNCTION__, (uint8_t *)rmem >= (uint8_t *)ram && (uint8_t *)rmem < (uint8_t *)ram_end, "legal memory");

    if ((uint8_t *)rmem < (uint8_t *)ram || (uint8_t *)rmem >= (uint8_t *)ram_end) 
    {
        _Mem_Prompt(__LINE__, __FUNCTION__, "illegal memory");
        return rmem;
    }
    /* Get the corresponding struct mem ... */
    mem = (struct mem *)((uint8_t *)rmem - SIZEOF_STRUCT_MEM);
    /* ... and its offset pointer */
    ptr = (uint8_t *)mem - ram;

    size = mem->next - ptr - SIZEOF_STRUCT_MEM;
    _Mem_Assert(__LINE__, __FUNCTION__, newsize <= size, "mem_realloc can only shrink memory");

    if (newsize > size) 
    {
        /* not supported */
        return NULL;
    }
    if (newsize == size) 
    {
        /* No change in size, simply return */
        return rmem;
    }

    mem2 = (struct mem *)&ram[mem->next];
    if(mem2->used == 0) 
    {
        /* The next struct is unused, we can simply move it at little */
        Mem_Size_T next;
        /* remember the old next pointer */
        next = mem2->next;
        /* create new struct mem which is moved directly after the shrinked mem */
        ptr2 = ptr + SIZEOF_STRUCT_MEM + newsize;
        if (lfree == mem2) 
        {
            lfree = (struct mem *)&ram[ptr2];
        }
        mem2 = (struct mem *)&ram[ptr2];
        mem2->used = 0;
        /* restore the next pointer */
        mem2->next = next;
        /* link it back to mem */
        mem2->prev = ptr;
        /* link mem to it */
        mem->next = ptr2;
        /* last thing to restore linked list: as we have moved mem2,
         * let 'mem2->next->prev' point to mem2 again. but only if mem2->next is not
         * the end of the heap */
        if (mem2->next != MEM_SIZE_ALIGNED) 
        {
            ((struct mem *)&ram[mem2->next])->prev = ptr2;
        }
        /* no need to plug holes, we've already done that */
    } 
    else if (newsize + SIZEOF_STRUCT_MEM + MIN_SIZE_ALIGNED <= size) 
    {
        /* Next struct is used but there's room for another struct mem with
         * at least MIN_SIZE_ALIGNED of data.
         * Old size ('size') must be big enough to contain at least 'newsize' plus a struct mem
         * ('SIZEOF_STRUCT_MEM') with some data ('MIN_SIZE_ALIGNED').
         * @todo we could leave out MIN_SIZE_ALIGNED. We would create an empty
         *       region that couldn't hold data, but when mem->next gets freed,
         *       the 2 regions would be combined, resulting in more free memory */
        ptr2 = ptr + SIZEOF_STRUCT_MEM + newsize;
        mem2 = (struct mem *)&ram[ptr2];
        if (mem2 < lfree) 
        {
            lfree = mem2;
        }
        mem2->used = 0;
        mem2->next = mem->next;
        mem2->prev = ptr;
        mem->next = ptr2;
        if (mem2->next != MEM_SIZE_ALIGNED) 
        {
            ((struct mem *)&ram[mem2->next])->prev = ptr2;
        }
        /* the original mem->next is used, so no need to plug holes! */
    }

    return rmem;
}

/**
 * Adam's mem_malloc() plus solution for bug #17922
 * Allocate a block of memory with a minimum of 'size' bytes.
 *
 * @param size is the minimum size of the requested block in bytes.
 * @return pointer to allocated memory or NULL if no free memory was found.
 *
 * Note that the returned value will always be aligned (as defined by MEM_ALIGNMENT).
 */
void* Mem_Malloc(Mem_Size_T size)
{
    Mem_Size_T ptr, ptr2;
    ST_Mem_T *mem, *mem2;

    if(size == 0) 
    {
        return NULL;
    }

    /* Expand the size of the allocated memory region so that we can
       adjust for alignment. */
    size = LWIP_MEM_ALIGN_SIZE(size);

    if(size < MIN_SIZE_ALIGNED) 
    {
        /* every data block must be at least MIN_SIZE_ALIGNED long */
        size = MIN_SIZE_ALIGNED;
    }

    if (size > MEM_SIZE_ALIGNED) 
    {
        return NULL;
    }

    /* Scan through the heap searching for a free block that is big enough,
     * beginning with the lowest free block.
     */
    for (ptr = (uint8_t *)lfree - ram; ptr < MEM_SIZE_ALIGNED - size; ptr = ((ST_Mem_T *)&ram[ptr])->next) 
    {
        mem = (ST_Mem_T *)&ram[ptr];

        if ((!mem->used) &&
            (mem->next - (ptr + SIZEOF_STRUCT_MEM)) >= size) 
        {
            /* mem is not used and at least perfect fit is possible:
             * mem->next - (ptr + SIZEOF_STRUCT_MEM) gives us the 'user data size' of mem */

            if (mem->next - (ptr + SIZEOF_STRUCT_MEM) >= (size + SIZEOF_STRUCT_MEM + MIN_SIZE_ALIGNED)) 
            {
                /* (in addition to the above, we test if another struct mem (SIZEOF_STRUCT_MEM) containing
                 * at least MIN_SIZE_ALIGNED of data also fits in the 'user data space' of 'mem')
                 * -> split large block, create empty remainder,
                 * remainder must be large enough to contain MIN_SIZE_ALIGNED data: if
                 * mem->next - (ptr + (2*SIZEOF_STRUCT_MEM)) == size,
                 * struct mem would fit in but no data between mem2 and mem2->next
                 * @todo we could leave out MIN_SIZE_ALIGNED. We would create an empty
                 *       region that couldn't hold data, but when mem->next gets freed,
                 *       the 2 regions would be combined, resulting in more free memory
                 */
                ptr2 = ptr + SIZEOF_STRUCT_MEM + size;
                /* create mem2 struct */
                mem2 = (ST_Mem_T *)&ram[ptr2];
                mem2->used = 0;
                mem2->next = mem->next;
                mem2->prev = ptr;
                /* and insert it between mem and mem->next */
                mem->next = ptr2;
                mem->used = 1;

                if (mem2->next != MEM_SIZE_ALIGNED) 
                {
                    ((ST_Mem_T *)&ram[mem2->next])->prev = ptr2;
                }
            }
            else 
            {
                /* (a mem2 struct does no fit into the user data space of mem and mem->next will always
                 * be used at this point: if not we have 2 unused structs in a row, plug_holes should have
                 * take care of this).
                 * -> near fit or excact fit: do not split, no mem2 creation
                 * also can't move mem->next directly behind mem, since mem->next
                 * will always be used at this point!
                 */
                mem->used = 1;
            }

            if (mem == lfree) 
            {
                /* Find next free block after mem and update lowest free pointer */
                while (lfree->used && lfree != ram_end) 
                {
                    /* prevent high interrupt latency... */
                    lfree = (ST_Mem_T *)&ram[lfree->next];
                }
                _Mem_Assert(__LINE__, __FUNCTION__, ((lfree == ram_end) || (!lfree->used)), "!lfree->used");
            }
            _Mem_Assert(__LINE__, __FUNCTION__, (uint32_t)mem + SIZEOF_STRUCT_MEM + size <= (uint32_t)ram_end, "allocated memory not above ram_end.");
            _Mem_Assert(__LINE__, __FUNCTION__, ((uint32_t)mem + SIZEOF_STRUCT_MEM) % MEM_ALIGNMENT == 0, "allocated memory properly aligned.");
            _Mem_Assert(__LINE__, __FUNCTION__, (((uint32_t)mem) & (MEM_ALIGNMENT-1)) == 0, "sanity check alignment");

            return (uint8_t *)mem + SIZEOF_STRUCT_MEM;
        }
    }

    _Mem_Prompt(__LINE__, __FUNCTION__, "could not allocate %d bytes", (int16_t)size);

    return NULL;
}

UserSys_InitFunc_Register(Mem_Init);

    
/**************** (C) COPYRIGHT 2010-2018 Efficient *****END OF FILE***********/
