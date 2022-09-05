/*================================================================
*  
*  文件名称：mg_pool.c
*  创 建 者: mongia
*  创建日期：2022年09月05日
*  邮    箱：mongiaK@outlook.com
*  
================================================================*/

#include "mg_pool.h"

mg_pool_t* mg_create_pool(mg_uint32_t size) {
    mg_pool_t* p;
    p = (mg_pool_t*)mg_malloc(sizeof(mg_pool_t));
    if (p == nullptr) {
        return nullptr;
    }

    p->_max = (size < MG_MAX_ALLOC_FROM_POOL) ? size : MG_MAX_ALLOC_FROM_POOL;
    p->_current = &p->_small;
    MG_LIST_INIT(&p->_large);
    MG_LIST_INIT(&p->_small);

    return p;
}

void mg_destory_pool(mg_pool_t* pool) {
    mg_list_t *h, *n;
    mg_large_block_t* l;
    mg_small_block_t* s;

    for (h = &pool->_large, n = h->_next; n != h; n = n->_next) {
        l = MG_STRUCT_POINT(mg_large_block_t, n, _l);
        mg_free(l->_head);
    }

    for (h = &pool->_small, n = h->_next; n != h; n = n->_next) {
        s = MG_STRUCT_POINT(mg_small_block_t, n, _l);
        mg_free(s->_head);
    }

    mg_free(pool);
}

void* mg_palloc_large(mg_pool_t* pool, mg_uint32_t size) {
    void* p;
    mg_large_block_t* large;
    p = mg_malloc(size + sizeof(mg_large_block_t));
    if (p == nullptr) {
        return nullptr;
    }

    large = (mg_large_block_t*)p;
    large->_head = p;
    large->_buf = large + 1;
    MG_LIST_PUSH_BACK(&large->_l, &pool->_large);

    return large->_buf;
}

void* mg_palloc_small(mg_pool_t* pool, mg_uint32_t size) {
    mg_list_t* p = pool->_current;
    mg_char_t* m;

    mg_small_block_t *s, *bl;

    while (p && p != &pool->_small) {
        s = MG_STRUCT_POINT(mg_small_block_t, p, _l);
        m = s->_last;
        if ((mg_uint32_t)(s->_end - m) >= size) {
            s->_last = m + size;
            return m;
        }
        p = p->_next;
    }

    m = (mg_char_t*)mg_malloc(MG_PAGESIZE);
    if (m == nullptr) {
        return nullptr;
    }

    bl = (mg_small_block_t*)m;
    bl->_head = m;
    bl->_end = m + MG_PAGESIZE - 1;
    bl->_failed = 0;

    m = (mg_char_t*)(bl + 1);
    bl->_last = m + size;

    for (p = pool->_current; p->_next != &pool->_small; p = p->_next) {
        s = MG_STRUCT_POINT(mg_small_block_t, p, _l);
        if (s->_failed++ > 4) {
            pool->_current = p->_next;
        }
    }

    MG_LIST_PUSH_BACK(&bl->_l, &pool->_small);
    return m;
}

void* mg_palloc(mg_pool_t* pool, mg_uint32_t size) {
    if (size <= pool->_max) {
        return mg_palloc_small(pool, size);
    }
    return mg_palloc_large(pool, size);
}

#
