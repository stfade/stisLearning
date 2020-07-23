#include <stdlib.h>
#include <stdio.h>
#include "list.h"

typedef struct
{
	char name[124];
	char surname[124];
} user_informations_t;

int main(int argc, char const *argv[])
{
	user_informations_t *user = malloc(sizeof(user_informations_t));

	generic_list_t *list = malloc(sizeof(generic_list_t));
	generic_list_add_node(list, (void*)user);

	return 0;
}
