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
void rb_tree_init(rb_tree_t *this,void *user_d)
{
    this->root = NULL;
    this->id_counter = 0;
    this->user_f = user_d;
}
void rb_tree_deinit(rb_tree_t *this)
{
    if(this->root != NULL)
    {
        this->root->data = NULL;
        free(this->root);
        // TODO: eger root doluysa tum dugumlerdeki veriler silinmesi gerekiyor.
    }
}
void rb_tree_destroy(rb_tree_t *this)
{
    rb_tree_deinit(this);
    free(this);
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
    temp->data = NULL;
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
    if(temp->data == NULL)
    {
        temp->data = data;
    }
    this->id_counter ++;
}
void rb_tree_display(rb_tree_t *this)
{
    rb_tree_node_t *temp = this->root;
    if(temp == NULL)
    {
        printf("\nTree is empty\n");
    }
    while(temp != NULL)
    {
        printf("\nid = %d , ", temp->id);
        this->user_f(temp->data);
        // tum agacta gezinmem lazim.
    }
}
void right_rotate(rb_tree_t *this, rb_tree_node_t *node)
{
    rb_tree_node_t *temp = node->left;

    node->left = temp->right;
    // node'un solu, node'un solunun sagi oldu,

    if(node->left != NULL)
    {
        node->left->parent = node;
        // node'un left'ini(node'un solunun sagini), parent'ina(node'a) bagladik.
    }
    temp->parent = node->parent;
    // temp ve node'un parent'i ayni oldu.

    if(node->parent == NULL)
    {
        this->root = temp;
        // node'un parent'i yoksa root, temp oldu.
    }
    else if(node == node->parent->right)
    {
        node->parent->right = temp;
        // node, parent'inin sagindaysa parent'in sagi temp oldu.
    }
    else
    {
        node->parent->left = temp;
        // node, parent'inin solundaysa parent'inin solu temp oldu.
    }

    temp->right = node;
    // node'un solunun sagi node oldu.
    node->parent = temp;
    // node'un parent'i node'un solu oldu.
}
void left_rotate(rb_tree_t *this, rb_tree_node_t *node)
{
    rb_tree_node_t *temp = node->right;
    node->right = temp->left;

    if(node->right != NULL)
    {
        node->right->parent = node;
    }
    temp->parent = node->parent;

    if(node->parent == NULL)
    {
        this->root = temp;
    }
    else if(node == node->parent->left)
    {
        node->parent->left = temp;
    }
    else
    {
        node->parent->right = temp;
    }

    temp->left = node;
    node->parent = temp;

}
void fix(rb_tree_t *this, rb_tree_node_t *node)
{
    while((node != this->root) && (node->parent->color == RED))
    {
        if(node->parent == node->parent->parent->left)
        {
            rb_tree_node_t *uncle = node->parent->parent->right;

            // Case 1:
            // node'un amcasi kirmizi ise yeniden renklendirme yapacagiz.
            if(uncle != NULL && uncle->color == RED)
            {
                node->parent->color = BLACK;
                uncle->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
                // node, kendisinin dedesi oldu. Bunu yapma sebebi bir sonraki dongude dede icin fixleri tamamlamak.
            }
            else
            {
                // Case 2:
                // node, node'un babasinin sagi ise "left_rotate" yapacagiz.
                if(node == node->parent->right)
                {
                    node = node->parent;
                    left_rotate(this,node);
                }
                // Case 3:
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                right_rotate(this,node->parent->parent);
                // rotate'lerden sonra tekrar kontrol etmemiz gerekiyor.
                // cunku bir yer degistirme islemi yapiyoruz.
                // bu islemlerden sonra Red&Black Tree algoritma kurallarini cignemis olabiliriz.
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
                if(node == node->parent->right)
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
rb_tree_node_t *sibling(rb_tree_node_t *node)
{
    if(node != NULL)
    {
        if(node->parent != NULL)
        {
            if(node == node->parent->left)
            {
                return node->parent->right;
            }
            else
                return node->parent->left;
        }
    }
}
