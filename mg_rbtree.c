/*================================================================
*  
*  文件名称：mg_rbtree.c
*  创 建 者: mongia
*  创建日期：2022年09月05日
*  邮    箱：mongiaK@outlook.com
*  
================================================================*/

#include "mg_rbtree.h"

mg_bool_t rb_node_is_red(struct mg_rb_node* node) {
    return node->_type == RBREDNODE;
}

mg_bool_t rb_node_is_black(struct mg_rb_node* node) {
    return node->_type == RBBLACKNODE;
}

void init_rb_node(struct mg_rb_node* rbnode) {
    rbnode->_type = RBREDNODE;
    rbnode->_parent = rbnode->_lchild = rbnode->_rchild = nullptr;
}

void init_rb_tree(struct mg_rbtree* rbtree,
                                mg_rb_node_compare compare) {
    rbtree->_count = 0;
    rbtree->_compare = compare;
    rbtree->_root = nullptr;
}

struct mg_rb_node* search_rb_node(struct mg_rb_node* node, struct mg_rbtree* tree,
                                         mg_bool_t insert_position) {
    struct mg_rb_node* p = tree->_root;
    while (p != nullptr) {
        mg_int_t ret = tree->_compare(node, p);
        if (ret > 0) {
            p = p->_lchild;
        } else if (ret < 0) {
            p = p->_rchild;
        } else {
            return p;
        }
    }
    return insert_position ? p : nullptr;
}

//                  P                         p
//                /x                          /
//              node                       rchild
//              /  \x                        /  \
//         lchild  rchild         =>     node   rrchild
//                  /x  \                /  \
//            rlchild   rrchild      lchild  rlchild
//
void left_rotate(struct mg_rb_node* node, struct mg_rbtree* tree) {
    struct mg_rb_node* p = node->_parent;
    struct mg_rb_node* rchild = node->_rchild;

    if (rchild->_lchild != nullptr) rchild->_lchild->_parent = node;

    node->_rchild = rchild->_lchild;
    rchild->_parent = p;

    if (p == nullptr) {
        tree->_root = rchild;
    } else if (p->_lchild == node) {
        p->_lchild = rchild;
    } else if (p->_rchild == node) {
        p->_rchild = rchild;
    }
    rchild->_lchild = node;
    node->_parent = rchild;
}

//                  P                         p
//                /x                         /
//              node                        lchild
//              /x  \                        /  \
//         lchild  rchild         =>   llchild node
//         /   \x                               /  \
//   llchild   lrchild                   lrchild  rchild
//
void right_rotate(struct mg_rb_node* node, struct mg_rbtree* tree) {
    struct mg_rb_node* p = node->_parent;
    struct mg_rb_node* lchild = node->_lchild;

    if (lchild->_rchild != nullptr) lchild->_rchild->_parent = node;

    node->_lchild = lchild->_rchild;
    lchild->_parent = p;

    if (p == nullptr) {
        tree->_root = lchild;
    } else if (p->_lchild == node) {
        p->_lchild = lchild;
    } else {
        p->_rchild = lchild;
    }

    lchild->_rchild = node;
    node->_parent = lchild;
}

void delete_leaf_node(struct mg_rb_node* leaf, struct mg_rbtree* tree) {
    if (leaf == tree->_root) {
        tree->_root = nullptr;
        return;
    }

    struct mg_rb_node* p = leaf->_parent;
    if (p->_lchild == leaf) {
        p->_lchild = nullptr;
    } else {
        p->_rchild = nullptr;
    }
}

// n1 is higher than n2
void change_rb_node(struct mg_rb_node* n1, struct mg_rb_node* n2,
                                  struct mg_rbtree* tree, mg_bool_t change_type) {
    if (n1 == n2) return;
    struct mg_rb_node* n1p = n1->_parent;
    struct mg_rb_node* n2p = n2->_parent;

    struct mg_rb_node* tmp;

    tmp = n1->_lchild;
    n1->_lchild = n2->_lchild;
    n2->_lchild = tmp;

    tmp = n1->_rchild;
    n1->_rchild = n2->_rchild;
    n2->_rchild = tmp;

    n1->_parent = n2p;
    n2->_parent = n1p;

    if (n1p == nullptr) {
        tree->_root = n2;
    } else {
        if (n1p->_lchild == n1) {
            n1p->_lchild = n2;
        } else {
            n1p->_rchild = n2;
        }
    }

    if (n2p->_lchild == n2) {
        n2p->_lchild = n1;
    } else {
        n2p->_rchild = n1;
    }

    if (change_type) {
        mg_uint8_t typ = n1->_type;
        n1->_type = n2->_type;
        n2->_type = typ;
    }
}

struct mg_rb_node* find_right_replace_node(struct mg_rb_node* n) {
    struct mg_rb_node* r = n->_rchild;
    while (r->_lchild != nullptr) {
        r = r->_lchild;
    }
    return r;
}

void insert_rb_node(struct mg_rb_node* node, struct mg_rbtree* tree) {
    struct mg_rb_node* p = search_rb_node(node, tree, true);
    if (p == nullptr) {
        tree->_root = node;
        tree->_root->_type = RBBLACKNODE;
        tree->_count++;
        return;
    }

    mg_int_t ret = tree->_compare(node, p);
    if (ret == 0) {
        return;
    } else if (ret > 0) {
        p->_lchild = node;
    } else {
        p->_rchild = node;
    }

    tree->_count++;
    struct mg_rb_node* u = nullptr;
    struct mg_rb_node* pp = nullptr;
    while ((p = node->_parent) && rb_node_is_red(p)) {
        pp = p->_parent;
        u = node == p->_rchild ? pp->_lchild : pp->_rchild;
        // 父亲是红色的，如果叔叔存在，那必然是红色，否则父亲与叔叔不平衡
        if (u && rb_node_is_red(u)) {
            pp->_type = RBREDNODE;
            u->_type = RBBLACKNODE;
            p->_type = RBBLACKNODE;

            node = pp;
            continue;
        }
        if (p == pp->_lchild) {  // 父亲是左孩子
            //            pp(Black)          P(Black)
            //             /                  /    \
            //          p(Red)       =>     I(Red) PP(Red)
            //           /
            //         I(Red)
            if (node == p->_lchild) {  // 插入的是做孩子
                p->_type = RBBLACKNODE;
                pp->_type = RBREDNODE;
                right_rotate(pp, tree);
            } else {  // 插入右孩子
                //      pp(Black)        pp(Black)         I(Black)
                //       /                 /                /   \
                //     p(Red)     =>     I(Red)    =>    P(Red) PP(Red)
                //        \              /
                //        I(Red)       p(Red)
                left_rotate(p, tree);
                node->_type = RBBLACKNODE;
                pp->_type = RBREDNODE;
                right_rotate(pp, tree);
            }
        } else {  // 父亲是右孩子
            //            pp(Black)            P(Black)
            //               \                  /    \
            //             p(Red)       =>   PP(Red) I(Red)
            //                \
            //              I(Red)
            if (node == p->_rchild) {
                p->_type = RBBLACKNODE;
                pp->_type = RBREDNODE;
                left_rotate(pp, tree);
            } else {
                //    pp(Black)       pp(Black)         I(Black)
                //      \                \                /   \
                //     p(Red)     =>     I(Red)    => PP(Red) p(Red)
                //      /                  \
                //    I(Red)              p(Red)
                right_rotate(p, tree);
                node->_type = RBBLACKNODE;
                pp->_type = RBREDNODE;
                left_rotate(pp, tree);
            }
        }
    }

    tree->_root->_type = RBBLACKNODE;
}

void delete_rb_node(struct mg_rb_node* dnode, struct mg_rbtree* tree) {
    struct mg_rb_node* d = search_rb_node(dnode, tree, false);
    if (d == nullptr) return;

    if (d->_lchild != nullptr && d->_rchild != nullptr) {
        struct mg_rb_node* r = find_right_replace_node(d);
        change_rb_node(d, r, tree, true);
    }

    // 节点是红色，那么肯定是叶子节点
    if (rb_node_is_red(d)) {
        delete_leaf_node(d, tree);
        return;
    }

    // 删除节点有一个单叶子节点，那么节点肯定是黑色，单叶子肯定是红色
    if (d->_lchild != nullptr) {
        change_rb_node(d, d->_lchild, tree, true);
        delete_leaf_node(d, tree);
        return;
    } else if (d->_rchild != nullptr) {
        change_rb_node(d, d->_rchild, tree, true);
        delete_leaf_node(d, tree);
        return;
    }

    // 思想：
    // 第一步：把兄弟节点边黑
    // 第二步：兄弟节点的子节点都是黑，那么直接将兄弟节点设置为红色，递归处理
    // 第三步：兄弟节点的子节点存在红色节点，那么把这个红色节点借过来，保证黑色节点删除之后黑高不变。

    // delete node is black, dont have leaf
    struct mg_rb_node* p = d->_parent;
    struct mg_rb_node* b = nullptr;
    struct mg_rb_node* node = d;
    while ((node && rb_node_is_black(node)) && node != tree->_root) {
        if (p->_lchild == node) {
            b = p->_rchild;
            // 把兄弟节点变黑
            // 兄弟是红色，那么兄弟的孩子必须都是黑色才能平衡
            if (rb_node_is_red(b)) {
                b->_type = RBBLACKNODE;
                p->_type = RBREDNODE;
                left_rotate(p, tree);
                b = p->_rchild;
            }

            // 兄弟的左右孩子都是黑色，那么将兄弟变黑，网上递归，黑高-1，直到根节点
            if ((b->_lchild == nullptr || rb_node_is_black(b->_lchild)) &&
                (b->_rchild == nullptr || rb_node_is_black(b->_rchild))) {
                b->_type = RBREDNODE;
                node = p;
                p = node->_parent;
            } else {
                // 将兄弟的右孩子变成红，方便选择平衡
                if (rb_node_is_black(b->_rchild)) {
                    b->_lchild->_type = RBBLACKNODE;
                    b->_type = RBREDNODE;
                    right_rotate(b, tree);
                    b = p->_rchild;
                }
                b->_type = p->_type;
                p->_type = RBBLACKNODE;
                b->_rchild->_type = RBBLACKNODE;
                left_rotate(p, tree);
                break;
            }
        } else {
            b = p->_lchild;
            if (rb_node_is_red(b)) {
                b->_type = RBBLACKNODE;
                p->_type = RBREDNODE;
                right_rotate(p, tree);
                b = p->_lchild;
            }

            if ((b->_lchild == nullptr || rb_node_is_black(b->_lchild)) &&
                (b->_rchild == nullptr || rb_node_is_black(b->_lchild))) {
                b->_type = RBREDNODE;
                node = p;
                p = node->_parent;
            } else {
                if (rb_node_is_black(b->_lchild)) {
                    b->_rchild->_type = RBBLACKNODE;
                    b->_type = RBREDNODE;
                    left_rotate(b, tree);
                    b = p->_lchild;
                }
                b->_type = p->_type;
                p->_type = RBBLACKNODE;
                b->_lchild->_type = RBBLACKNODE;
                right_rotate(p, tree);
                break;
            }
        }
    }
    node->_type = RBBLACKNODE;

    delete_leaf_node(d, tree);
}
