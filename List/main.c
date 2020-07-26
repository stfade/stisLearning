#include <stdlib.h>
#include <stdio.h>
#include "list.h"
#include "user.h"

void menu(generic_list_t *,user_informations_t *);
void wait();
int main(int argc, char const *argv[])
{	
	user_informations_t *user = malloc(sizeof(user_informations_t));
	generic_list_t *list = malloc(sizeof(generic_list_t));
	
	while (1) 
	{
        	menu(list,user);
    	}
	

	return 0;
}
void menu(generic_list_t *list,user_informations_t *user) 
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
    		char ad[128],*name=NULL,soyad[128],*surname=NULL;
    		printf("Isim Giriniz: ");
    		scanf("%s",ad);
    		name = ad;
    		generic_list_add_node(list, (void*)user);
    		user_information_set_name((void*)user,(char*)name);
    		printf("soyisim giriniz: ");
    		scanf("%s",soyad);
    		surname = soyad;
    		user_information_set_surname((void*)user,(char*)surname);
    		
    		break;
    	
    	case 2:
    		system("clear");
    		generic_list_display(list);
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
    system("clear");
 
}
	
