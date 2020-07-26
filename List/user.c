#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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
	user_informations_t *temp=this;
	
	while(temp == NULL)
	{
		free(temp);
	}
}

void user_information_set_name(user_informations_t *this,char *name)
{

	
	strncpy(this->name, name, strlen(name));
}
void user_information_set_surname(user_informations_t *this,char *surname)
{
	
	strncpy(this->surname, surname, strlen(surname));
}

char *user_information_get_name(user_informations_t *this)
{
	return this->name;
}
char *user_information_get_surname(user_informations_t *this)
{
	
	return this->surname;
}
