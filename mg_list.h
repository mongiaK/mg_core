/*================================================================
*
*  文件名称：mg_list.h
*  创 建 者: mongia
*  创建日期：2022年01月27日
*  邮    箱：mr_pengmj@outlook.com
*
================================================================*/

#ifndef __MG_LIST_INCLUDE_H__
#define __MG_LIST_INCLUDE_H__

#include "mg_config.h"

struct mg_list {
    struct mg_list* _prev;
    struct mg_list* _next;
};

void init_list(struct mg_list* l);
void insert_list_front(struct mg_list* e, struct mg_list* l);
void insert_list_end(struct mg_list* e, struct mg_list* l);
void remove_list_node(struct mg_list* e, mg_bool_t cleanup);
struct mg_list* list_head(struct mg_list* l);
struct mg_list* list_tail(struct mg_list* l);

#define MG_LIST_INIT(l) init_list(l)
#define MG_LIST_EMPTY(l) ((l) == (l)->_prev)
#define MG_LIST_PUSH_BACK(e, l) insert_list_end(e, l)
#define MG_LIST_PUSH_FRONT(e, l) insert_list_front(e, l)
#define MG_LIST_DELETE(e, cleanup) remove_list_node(e, cleanup)
#define MG_LIST_HEAD(l) list_head(l)
#define MG_LIST_TAIL list_tail(l)
#define MG_LIST_STATIC_INIT(l) \
    { (l), (l) }

#endif
