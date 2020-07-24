#ifndef USER_H
#define USER_H

typedef struct
{
	char name[124];
	char surname[124];
} user_informations_t;

user_informations_t *user_informations_create();
void destroy(user_informations_t *this);
void user_information_set_name(user_informations_t *this,char *name);
void user_information_set_surname(user_informations_t *this,char *surname);
char user_information_get_name(user_informations_t *this);
char user_information_get_surname(user_informations_t *this);
#endif 
