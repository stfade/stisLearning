#include <stddef.h>
#ifndef RB_TREE_H_
#define RB_TREE_H_

enum Colors{RED,BLACK};
typedef struct rb_tree_node
{
    int id;
    int color;
    void *data;
    struct rb_tree_node *parent, *left, *right;
} rb_tree_node_t;

typedef struct
{
    rb_tree_node_t *root;
    int id_counter;
    void (*user_f)();
} rb_tree_t;

rb_tree_t *rb_tree_create();
void rb_tree_init(rb_tree_t *this, void *);
void rb_tree_deinit(rb_tree_t *this);
void rb_tree_destroy(rb_tree_t *this);
void rb_tree_add(rb_tree_t *this, void *data);
void rb_tree_display(rb_tree_t *this);
void right_rotate(rb_tree_t *this, rb_tree_node_t *node);
void left_rotate(rb_tree_t *this, rb_tree_node_t *node);
void fix(rb_tree_t *this, rb_tree_node_t *node);
rb_tree_node_t *sibling(rb_tree_node_t *node);
void rb_tree_test(rb_tree_t *this);

#endif