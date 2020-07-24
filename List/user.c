#include <stdlib.h>
#include <stdio.h>
#include "user.h"

user_informations_t *user_informations_create()
{
	user_informations_t *this = malloc(sizeof(user_informations_t));
	
	if (this == NULL)
	{
		return NULL;
	}
	
	return this;
}

void destroy(user_informations_t *this)
{
	
}

void user_information_set_name(user_informations_t *this,char *name)
{
	this->name = name;
}
void user_information_set_surname(user_informations_t *this,char *surname)
{

}

char user_information_get_name(user_informations_t *this)
{

	return this->name;
}
char user_information_get_surname(user_informations_t *this)
{

	return this->surname;
}
