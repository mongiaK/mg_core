/*================================================================
*
*  文件名称：mg_rbtree.h
*  创 建 者: mongia
*  创建日期：2021年09月27日
*
================================================================*/
#ifndef __MG_RBTREE_INCLUDE__
#define __MG_RBTREE_INCLUDE__

#include "mg_config.h"
#include "mg_core.h"

#define RBREDNODE 0
#define RBBLACKNODE 1

typedef struct mg_rb_node {
    mg_uint8_t _type;

    struct mg_rb_node* _parent;
    struct mg_rb_node* _lchild;
    struct mg_rb_node* _rchild;
} mg_rb_node_t;

// return
// = 0: l = r
// > 0: l < r
// < 0: l > r
typedef mg_int32_t (*mg_rb_node_compare)(mg_rb_node_t* l, mg_rb_node_t* r);

typedef struct mg_rbtree {
    mg_int32_t _count;
    mg_rb_node_compare _compare;

    mg_rb_node_t* _root;
} mg_rbtree_t;

mg_bool_t rb_node_is_red(mg_rb_node_t* node);
mg_bool_t rb_node_is_black(mg_rb_node_t* node);

void init_rb_node(mg_rb_node_t* rbnode);
void init_rb_tree(mg_rbtree_t* rbtree, mg_rb_node_compare compare);

mg_rb_node_t* search_rb_node(mg_rb_node_t* node, mg_rbtree_t* tree, mg_bool_t insert_position);
void change_rb_node(mg_rb_node_t* n1, mg_rb_node_t* n2, mg_rbtree_t* tree, mg_bool_t change_type);
void insert_rb_node(mg_rb_node_t* node, mg_rbtree_t* tree);
void delete_rb_node(mg_rb_node_t* dnode, mg_rbtree_t* tree);

void left_rotate(mg_rb_node_t* node, mg_rbtree_t* tree);
void right_rotate(mg_rb_node_t* node, mg_rbtree_t* tree);

void delete_leaf_node(mg_rb_node_t* leaf, mg_rbtree_t* tree);
mg_rb_node_t* find_right_replace_node(mg_rb_node_t* n);

#define MG_RBTREE_INIT_TREE(t, cmp) init_rb_tree(t, cmp)
#define MG_RBTREE_INIT_NODE(n) init_rb_node(n)
#define MG_RBTREE_INSERT_NODE(n, t) insert_rb_node(n, t)
#define MG_RBTREE_DELETE_NODE(n, t) delete_rb_node(n, t)
#define MG_RBTREE_GET_NODE(n, t) search_rb_node(n, t, false)

#endif
