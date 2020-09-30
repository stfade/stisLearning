#include <stdio.h>
#include <stdlib.h>
#include "rb_tree.h"

rb_tree_t *rb_tree_create()
{
    rb_tree_t *this = malloc(sizeof(rb_tree_t));

    if(this == NULL)
    {
        printf("allocation error!");
    }

    return this;
}

void rb_tree_init(rb_tree_t *this,void (*display)(void*),void (*delete)(void*))
{
    this->root = NULL;
    this->id_counter = 1;
    this->user_info_display = display;
    this->user_info_delete = delete;
}

void rb_tree_deinit(rb_tree_t *this)
{
    if(this->root != NULL)
    {
        this->user_info_delete(this->root->data);
        free(this->root);
        // TODO: eger root doluysa tum dugumlerdeki veriler silinmesi gerekiyor.
    }
}
void rb_tree_destroy(rb_tree_t *this)
{
    rb_tree_deinit(this);
    free(this);
    printf("Everything is destroyed\n");
}
void rb_tree_test(rb_tree_t *this)
{
    printf("\nTEST\n");
    rb_tree_deinit(this);
    rb_tree_destroy(this);
    printf("\nTEST\n");
}
void rb_tree_add(rb_tree_t *this, void *data)
{
    rb_tree_node_t *temp = this->root;
    rb_tree_node_t *parent = NULL;

    while(temp != NULL)
    {
        parent = temp;
        if(this->id_counter > temp->id)
        {
            temp = temp->right;
        }
        else if(this->id_counter < temp->id)
        {
            temp = temp->left;
        }
    }

    temp = malloc(sizeof(rb_tree_node_t));
    temp->id = this->id_counter;
    temp->color = RED;
    temp->data = data;
    temp->right = NULL;
    temp->left = NULL;
    temp->parent = parent;
    if(temp->parent != NULL)
    {
        if(parent->id < temp->id)
        {
            parent->right = temp;
            printf("parent in sagina temp eklendi \n");
        }
        else if(parent->id > temp->id)
        {
            parent->left = temp;
            printf("parent in soluna temp eklendi \n");
        }
    }

    if(this->root == NULL)
    {
        temp->color = BLACK;
        this->root = temp;
    }

    this->id_counter++;
    add_fix(this,temp);
}

void add_fix(rb_tree_t *this, rb_tree_node_t *node)
{
    if(node == NULL)
    {
        return;
    }

    while((node != this->root) && (node->parent->color == RED))
    {
        if(node->parent == node->parent->parent->left)
        {
            rb_tree_node_t *uncle = node->parent->parent->right;

            // Case 1:
            if(uncle != NULL && uncle->color == RED)
            {
                node->parent->color = BLACK;
                uncle->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            }
            else
            {

                // Case 2:
                if(node == node->parent->right)
                {
                    node = node->parent;
                    left_rotate(this,node);
                }
                // Case 3:
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                right_rotate(this,node->parent->parent);
            }
        }

        else
        {
            rb_tree_node_t *uncle = node->parent->parent->left;

            if(uncle != NULL && uncle->color == RED)
            {
                node->parent->color = BLACK;
                uncle->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            }

            else
            {
                if(node == node->parent->left)
                {
                    node = node->parent;
                    right_rotate(this,node);
                }
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                left_rotate(this,node->parent->parent);
            }
        }
    }
    this->root->color = BLACK;
}

void right_rotate(rb_tree_t *this, rb_tree_node_t *root)
{
    rb_tree_node_t *pivot = root->left;

    root->left = pivot->right;

    if(pivot->right != NULL)
    {
        pivot->right->parent = root;
    }

    pivot->parent = root->parent;

    if(root->parent == NULL)
    {
        this->root = pivot;
    }

    else
    {
        if(root == root->parent->right)
        {
            root->parent->right = pivot;
        }

        else
        {
            root->parent->left = pivot;
        }
    }

    pivot->right = root;
    root->parent = pivot;
}

void left_rotate(rb_tree_t *this, rb_tree_node_t *root)
{
    rb_tree_node_t *pivot = root->right;
    root->right = pivot->left;

    if(pivot->left != NULL)
    {
        pivot->left->parent = root;
    }
    pivot->parent = root->parent;

    if(root->parent == NULL)
    {
        this->root = pivot;
    }
    else
    {
        if(root == root->parent->left)
        {
            root->parent->left = pivot;
        }
        else
        {
            root->parent->right = pivot;
        }
    }

    pivot->left = root;
    root->parent = pivot;
}

void inorder(rb_tree_t *this, rb_tree_node_t *node)
{
    if(this->root == NULL)
    {
        printf("TREE IS EMPTY\n");
    }

    if(node == NULL)
    {
        return;
    }

    inorder(this,node->left);
    printf("\nid = %d , ", node->id);
    printf("\ncolor = %d , ", node->color);
    this->user_info_display(node->data);
    inorder(this,node->right);

}

void preorder(rb_tree_t *this, rb_tree_node_t *node)
{
    if(this->root == NULL)
    {
        printf("TREE IS EMPTY\n");
    }

    if(node == NULL)
    {
        return;
    }

    printf("\nid = %d , ", node->id);
    printf("\ncolor = %d , ", node->color);
    this->user_info_display(node->data);
    preorder(this,node->left);
    preorder(this,node->right);

}
rb_tree_node_t *rb_tree_search(rb_tree_t *this,int id)
{
    rb_tree_node_t *temp = this->root;

    while(temp != NULL && temp->id != id)
    {
        if(id < temp->id)
        {
            temp = temp->left;
        }

        else
        {
            temp = temp->right;
        }
    }

    if(temp == NULL)
    {
        printf("matcing not found\n");
        return NULL;
    }

    else
    {
        printf("\nMatching id = %d , ", temp->id);
        return temp;
    }
}

void rb_tree_delete(rb_tree_t *this,int id)
{
    rb_tree_node_t *result = rb_tree_search(this,id);

    if(result == NULL)
    {
        return;
    }

    if(result->left != NULL && result->right != NULL)
    {
        rb_tree_node_t *temp = result;
    }

    rb_tree_node_t *temp = result;
    void *helper = result->data;
    int temp_id = result->id;

    if(result->left !=NULL)
    {
        temp = temp->left;
    }

    while(temp->right != NULL)
    {
        temp = temp->right;
    }
    if(temp->left != NULL)
    {
        temp->left->parent = temp->parent;
        temp->parent->left = temp->left;
    }

    result->data = temp->data;
    result->id = temp->id;
    temp->data = helper;
    temp->id = temp_id;

    if(temp->color == BLACK)
    {
        delete_fix(this,temp);
    }

    this->user_info_delete(temp->data);

    if(temp->parent != NULL)
    {
        if(temp == temp->parent->right)
        {
            temp->parent->right = NULL;
        }

        else
        {
            temp->parent->left = NULL;
        }
    }

    if(this->root == temp)
    {
        free(this->root);
        this->root = NULL;
    }

    else
    {

        free(temp);
    }
}

void delete_fix(rb_tree_t *this, rb_tree_node_t *node)
{
    if(node == NULL)
    {
        return;
    }

    while(node != this->root && node->color == BLACK)
    {
        if(node == node->parent->left)
        {
            rb_tree_node_t *sibling = node->parent->right;

            if(node->parent != this->root && node->parent->color == BLACK && sibling->color == BLACK)
            {
                sibling->color = RED;
                node = node->parent;
                sibling = node->parent->right;
            }

            if(sibling != NULL && sibling->color == RED)
            {
                sibling->color = BLACK;
                node->parent->color = RED;
                left_rotate(this,node->parent);
                sibling = node->parent->right;
            }

            if(sibling != NULL && sibling->left != NULL && sibling->right != NULL && sibling->left->color == BLACK && sibling->right->color == BLACK)
            {
                sibling->color = RED;
                node = node->parent;
            }

            else
            {
                if(sibling != NULL && sibling->right != NULL && sibling->right->color == BLACK)
                {
                    sibling->left->color = BLACK;
                    sibling->color = RED;
                    right_rotate(this,sibling);
                    sibling = node->parent->right;
                }

                sibling->color = node->parent->color;
                node->parent->color = BLACK;

                if(sibling->right != NULL)
                {
                    sibling->right->color = BLACK;
                }

                left_rotate(this,node->parent);
                node = this->root;
            }
        }

        else
        {
            rb_tree_node_t *sibling = node->parent->left;

            if(node->parent != this->root && node->parent->color == BLACK && sibling->color == BLACK)
            {
                sibling->color = RED;
                node = node->parent;
                sibling = node->parent->left;
            }

            if(sibling != NULL && sibling->color == RED)
            {
                sibling->color = BLACK;
                node->parent->color = RED;
                right_rotate(this,node->parent);
                sibling = node->parent->left;
            }

            if(sibling != NULL && sibling->left->color == BLACK && sibling->right->color == BLACK)
            {
                sibling->color = RED;
                node = node->parent;
            }

            else
            {
                if(sibling != NULL && sibling->left->color == BLACK)
                {
                    sibling->right->color = BLACK;
                    sibling->color = RED;
                    left_rotate(this,sibling);
                    sibling = node->parent->left;
                }

                sibling->color = node->parent->color;
                node->parent->color = BLACK;
                sibling->left->color = BLACK;
                right_rotate(this,node->parent);
                node = this->root;
            }
        }
    }

    node->color = BLACK;
}
