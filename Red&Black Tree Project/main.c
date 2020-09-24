#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rb_tree.h"
#include "user.h"
void menu(rb_tree_t *);
void wait();
int main()
{
    rb_tree_t *test = rb_tree_create();
    rb_tree_init(test,&user_display);
    while(1)
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
    int secim;
    printf("1-Ekleme\n");
    printf("2-Listeleme\n");
    printf("3-Arama\n");
    printf("4-Silme\n");
    printf("5-Cikis\n");
    printf("Lutfen Secim Yapiniz --> ");
    scanf("%d", &secim);

    switch(secim)
    {
    	case 1:
            system("clear");
            user_informations_t *user = user_informations_create();
            char name_array[128];
            printf("\n name?: \n");
            scanf("%s",name_array);
            user_informations_set_name(user, name_array);
            char surname_array[128];
            printf("\n surname?: \n");
            scanf("%s",surname_array);
            user_informations_set_surname(user, surname_array);
            rb_tree_add(test, user);
            wait();
            break;
        case 2:
            rb_tree_display(test);
            wait();
            break;
        case 3:

        case 4:

        case 5:
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
