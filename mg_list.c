/*================================================================
*  
*  文件名称：mg_list.c
*  创 建 者: mongia
*  创建日期：2022年03月16日
*  邮    箱：mongiaK@outlook.com
*  
================================================================*/

#include "mg_list.h"

void init_list(struct mg_list* l) {
    l->_next = l;
    l->_prev = l;
}

void insert_list_front(struct mg_list* e, struct mg_list* l) {
    e->_next = l;
    e->_prev = l->_prev;
    l->_prev->_next = e;
    l->_prev = e;
}

void insert_list_end(struct mg_list* e, struct mg_list* l) {
    e->_next = l->_next;
    e->_prev = l;
    l->_next->_prev = e;
    l->_next = e;
}

void remove_list_node(struct mg_list* e, mg_bool_t cleanup) {
    e->_prev->_next = e->_next;
    e->_next->_prev = e->_prev;

    if (cleanup) {
        init_list(e);
    }
}

struct mg_list* list_head(struct mg_list* l) { return l->_next; }

struct mg_list* list_tail(struct mg_list* l) { return l->_prev; }
