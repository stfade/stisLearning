#include <stdlib.h>
#include <stdio.h>
#include "list.h"
#include "user.h"

int main(int argc, char const *argv[])
{	
	
	user_informations_t *user = malloc(sizeof(user_informations_t));

	generic_list_t *list = malloc(sizeof(generic_list_t));
	generic_list_add_node(list, (void*)user);
	
	char isim[128],*name=NULL;
	printf("sayiyi giriniz: ");
	scanf("%s",isim);
	name=isim;
	
	user_information_set_name((void*)user,char *name);
	user_information_get_name((void*)user);

	return 0;
}
