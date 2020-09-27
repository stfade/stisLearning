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
    fix(this,temp);
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

    if(temp->id != id)
    {
        printf("matcing not found\n");
        return NULL;
    }

    printf("\nMatching id = %d , ", temp->id);
    // this->user_info_display(temp->data);
    return temp;
}

void rb_tree_delete(rb_tree_t *this,int id)
{
    rb_tree_node_t *result = rb_tree_search(this,id);
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

    while(temp->left != NULL)
    {
        temp = temp->left;
    }

    result->data = temp->data;
    result->id = temp->id;
    temp->data = helper;
    temp->id = temp_id;

    this->user_info_delete(temp->data);

    if(temp == temp->parent->right)
    {
        temp->parent->right = NULL;
    }

    else
    {
        temp->parent->left = NULL;
    }

    free(temp);
    // fix(this,temp2);
}

rb_tree_node_t *rb_tree_swap(rb_tree_t *this, rb_tree_node_t *x, rb_tree_node_t *y)
{
    if(x->parent == NULL)
    {
        this->root = y;
    }

    else if(x == x->parent->left)
    {
        x->parent->left = y;
    }

    else
    {
        x->parent->right = y;
    }

    y->parent = x->parent;
    return x;
}

void right_rotate(rb_tree_t *this, rb_tree_node_t *node)
{
    rb_tree_node_t *sibling = node->left;

    node->left = sibling->right;
    // node'un solu, node'un solunun sagi oldu,

    if(sibling->right != NULL)
    {
        sibling->right->parent = node;
        // node'un left'ini(node'un solunu), parent'ina(node'a) bagladik.
    }
    sibling->parent = node->parent;
    // temp ve node'un parent'i ayni oldu.

    if(node->parent == NULL)
    {
        this->root = sibling;
        // node'un parent'i yoksa root, temp oldu.
    }
    else
    {
        if(node == node->parent->right)
        {
            node->parent->right = sibling;
            // node, parent'inin sagindaysa parent'in sagi temp oldu.
        }
        else
        {
            node->parent->left = sibling;
            // node, parent'inin solundaysa parent'inin solu temp oldu.
        }
    }
    sibling->right = node;
    // node'un solunun sagi node oldu.
    node->parent = sibling;
    // node'un parent'i node'un solu oldu.
}

void left_rotate(rb_tree_t *this, rb_tree_node_t *node)
{
    rb_tree_node_t *sibling = node->right;
    node->right = sibling->left;

    if(sibling->left != NULL)
    {
        sibling->left->parent = node;
    }
    sibling->parent = node->parent;

    if(node->parent == NULL)
    {
        this->root = sibling;
    }
    else
    {
        if(node == node->parent->left)
        {
            node->parent->left = sibling;
        }
        else
        {
            node->parent->right = sibling;
        }
    }

    sibling->left = node;
    node->parent = sibling;
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
