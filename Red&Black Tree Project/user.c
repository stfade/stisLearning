#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "user.h"

user_informations_t *user_informations_create()
{
	user_informations_t *this = malloc(sizeof(user_informations_t));

	if(this == NULL)
	{
		return NULL;
	}
	return this;
}
void user_informations_set_name(user_informations_t *this, char *name)
{
	strncpy(this->name ,name ,strlen(name));
}
char *user_informations_get_name(user_informations_t *this)
{
	return this->name;
}
void user_informations_set_surname(user_informations_t *this, char *surname)
{
	strncpy(this->surname ,surname ,strlen(surname));
}
char *user_informations_get_surname(user_informations_t *this)
{
	return this->surname;
}
void user_destroy(user_informations_t *this)
{
	user_informations_t *temp = this;
	if(temp != NULL)
	{
		free(temp);
	}
}
void *user_display(user_informations_t *this)
{
	printf("name : %s ,",user_informations_get_name(this));
	printf("surname : %s\n",user_informations_get_surname(this));
}
