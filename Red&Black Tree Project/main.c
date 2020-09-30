#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rb_tree.h"
#include "user.h"

typedef enum
{
    ADD,
    DISPLAY,
    SEARCH,
    DELETE,
    EXIT,
    MENU_LAST_ITEM
}menu_items;

//void array[];

void menu(rb_tree_t *);
void wait();
int main()
{
    rb_tree_t *test = rb_tree_create();
    rb_tree_init(test, &user_display, &user_delete);
    for(;;)
    {
        menu(test);
    }
    // user_destroy(user);
    // rb_tree_display(test);
    // rb_tree_destroy(test);
    // rb_tree_test(test);
    return 0;
}
void menu(rb_tree_t *test)
{
    int id;
    int secim;
    char name_array[128] = "Samet";
    char surname_array[128] = "Taslioglu";
    printf("1-Add\n");
    printf("2-Display\n");
    printf("3-Search\n");
    printf("4-Delete\n");
    printf("5-Exit\n");
    printf("Please make a selection --> ");
    scanf("%d", &secim);
    secim--;

    switch(secim)
    {
    	case ADD:
            system("clear");
            user_informations_t *user = user_informations_create();
            user_init(user);
            /*
            memset(name_array, '\0', sizeof(name_array));
            memset(surname_array, '\0', sizeof(surname_array));
            printf("\n name?: \n");
            scanf("%s",name_array);
            */
            user_informations_set_name(user, name_array);
            /*
            printf("\n surname?: \n");
            scanf("%s",surname_array);
            */
            user_informations_set_surname(user, surname_array);
            /*
            printf("\n id: \n");
            scanf("%d",&id);
            */
            rb_tree_add(test,user);
            wait();
            break;
        case DISPLAY:
            inorder(test, test->root);
            wait();
            break;
        case SEARCH:
            printf("bulmak istediginiz verinin id'si? :\n");
            scanf("%d",&id);
            rb_tree_search(test,id);
            wait();
            break;
        case DELETE:
            printf("silmek istediginiz verinin id'si? :\n");
            scanf("%d",&id);
            rb_tree_delete(test,id);
            wait();
            break;
        case EXIT:
    		printf("Program Bitti!\n");
        	exit(0);
        	break;
    }
}
void wait()
{
    char temp;
    printf("Devam etmek icin Enter'a basiniz!\n");
    temp = getchar();
    temp = getchar();
    // system("clear");
}
