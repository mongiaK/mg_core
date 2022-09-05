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

#define RBREDNODE 0
#define RBBLACKNODE 1

struct mg_rb_node {
    mg_uint8_t _type;

    struct mg_rb_node* _parent;
    struct mg_rb_node* _lchild;
    struct mg_rb_node* _rchild;
};

// return
// = 0: l = r
// > 0: l < r
// < 0: l > r
typedef mg_int32_t (*mg_rb_node_compare)(struct mg_rb_node* l, struct mg_rb_node* r);

struct mg_rbtree {
    mg_int32_t _count;
    mg_rb_node_compare _compare;

    struct mg_rb_node* _root;
};

mg_bool_t rb_node_is_red(struct mg_rb_node* node);
mg_bool_t rb_node_is_black(struct mg_rb_node* node);

void init_rb_node(struct mg_rb_node* rbnode);
void init_rb_tree(struct mg_rbtree* rbtree, mg_rb_node_compare compare);

struct mg_rb_node* search_rb_node(struct mg_rb_node* node, struct mg_rbtree* tree, mg_bool_t insert_position);
void change_rb_node(struct mg_rb_node* n1, struct mg_rb_node* n2, struct mg_rbtree* tree, mg_bool_t change_type);
void insert_rb_node(struct mg_rb_node* node, struct mg_rbtree* tree);
void delete_rb_node(struct mg_rb_node* dnode, struct mg_rbtree* tree);

void left_rotate(struct mg_rb_node* node, struct mg_rbtree* tree);
void right_rotate(struct mg_rb_node* node, struct mg_rbtree* tree);

void delete_leaf_node(struct mg_rb_node* leaf, struct mg_rbtree* tree);
struct mg_rb_node* find_right_replace_node(struct mg_rb_node* n);

#define MG_RBTREE_INIT_TREE(t, cmp) init_rb_tree(t, cmp)
#define MG_RBTREE_INIT_NODE(n) init_rb_node(n)
#define MG_RBTREE_INSERT_NODE(n, t) insert_rb_node(n, t)
#define MG_RBTREE_DELETE_NODE(n, t) delete_rb_node(n, t)
#define MG_RBTREE_GET_NODE(n, t) search_rb_node(n, t, false)

#endif
