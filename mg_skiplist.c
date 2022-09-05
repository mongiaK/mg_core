/*================================================================
*  
*  文件名称：mg_skiplist.c
*  创 建 者: mongia
*  创建日期：2022年09月05日
*  邮    箱：mongiaK@outlook.com
*  
================================================================*/

#include "mg_skiplist.h"

void init_skiplist(struct mg_skiplist* skl,
                                         mg_skiplist_node_compare compare) {
    for (mg_int32_t i = 0; i < MAX_SKIPLIST_LEVEL; i++) {
        MG_LIST_INIT(skl->_head[i]);
    }
    skl->_cur_level = 0;
    skl->_compare = compare;
}
