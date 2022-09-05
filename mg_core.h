/*================================================================
*
*  文件名称：mg_core.h
*  创 建 者: mongia
*  创建日期：2022年01月25日
*  邮    箱：mr_pengmj@outlook.com
*
================================================================*/
#ifndef __MG_CORE_INCLUDE_H__
#define __MG_CORE_INCLUDE_H__

// no other reference
#include "mg_time.h"
#include "mg_list.h"
#include "mg_rbtree.h"
#include "mg_log.h"

// no other reference
typedef struct mg_list mg_list_t;
typedef struct mg_rb_node mg_rb_node_t;
typedef struct mg_rbtree mg_rbtree_t;

// have front reference
#include "mg_pool.h"
#include "mg_skiplist.h"

typedef struct mg_pool mg_pool_t;
typedef struct mg_skiplist_node mg_skiplist_node_t;
typedef struct mg_skiplist mg_skiplist_t;

#endif
