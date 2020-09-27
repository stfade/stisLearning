#include <stddef.h>
#ifndef RB_TREE_H_
#define RB_TREE_H_

enum Colors {BLACK,RED};
typedef struct rb_tree_node
{
    int id;
    enum Colors color;
    void *data;
    struct rb_tree_node *parent, *left, *right;
} rb_tree_node_t;

typedef struct
{
    rb_tree_node_t *root;
    int id_counter;
    void (*user_info_display)(void *);
    void (*user_info_delete)(void *);
} rb_tree_t;

rb_tree_t *rb_tree_create();
void rb_tree_init(rb_tree_t *this,void (*display)(void*),void (*delete)(void*));
void rb_tree_deinit(rb_tree_t *this);
void rb_tree_destroy(rb_tree_t *this);
void rb_tree_add(rb_tree_t *this, void *data);
void inorder(rb_tree_t *this, rb_tree_node_t *node);
rb_tree_node_t *rb_tree_search(rb_tree_t *this,int id);
void rb_tree_delete(rb_tree_t *this,int id);
rb_tree_node_t *rb_tree_swap(rb_tree_t *this, rb_tree_node_t *, rb_tree_node_t *);
void right_rotate(rb_tree_t *this, rb_tree_node_t *node);
void left_rotate(rb_tree_t *this, rb_tree_node_t *node);
void fix(rb_tree_t *this, rb_tree_node_t *node);
void rb_tree_test(rb_tree_t *this);

#endif
