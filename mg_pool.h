/*================================================================
*
*  文件名称：mg_pool.h
*  创 建 者: mongia
*  创建日期：2022年01月27日
*  邮    箱：mr_pengmj@outlook.com
*
================================================================*/
#ifndef __MG_POOL_INCLUDE_H__
#define __MG_POOL_INCLUDE_H__

#include "mg_config.h"
#include "mg_core.h"

#ifndef MG_PAGESIZE
#define MG_PAGESIZE (4 * 1024)
#endif

#ifndef MG_ALIGNEMNT
#define MG_ALIGNMENT (32)
#endif

#ifdef MG_DEBUG
#define MG_REDZONE MG_PAGESIZE
#else
#define MG_REDZONE (0)
#endif

#ifndef MG_MAX_ALLOC_FROM_POOL
#define MG_MAX_ALLOC_FROM_POOL (MG_PAGESIZE - 1 - sizeof(mg_small_block_t))
#endif

#define MG_ALIGN(n, alignment) (((n) + (alignment - 1)) & ~(alignment - 1))

typedef struct mg_large_block {
    mg_list_t _l;
    void* _head;
    void* _buf;
} mg_large_block_t;

typedef struct mg_small_block {
    mg_list_t _l;
    void* _head;
    mg_char_t* _last;
    mg_char_t* _end;
    mg_int_t _failed;
} mg_small_block_t;

typedef struct mg_pool {
    mg_uint32_t _max;
    mg_list_t* _current;
    mg_list_t _large;
    mg_list_t _small;
} mg_pool_t;

mg_pool_t* mg_create_pool(mg_uint32_t size);
void mg_destory_pool(mg_pool_t* pool);
void* mg_palloc_large(mg_pool_t* pool, mg_uint32_t size);
void* mg_palloc_small(mg_pool_t* pool, mg_uint32_t size);
void* mg_palloc(mg_pool_t* pool, mg_uint32_t size);

#endif
