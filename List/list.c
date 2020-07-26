#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "list.h"
#include "user.h"

generic_list_t *generic_list_create()
{
	generic_list_t *this = malloc(sizeof(generic_list_t));
	this->next=NULL;
	this->data=NULL;
	if (!this)
	{
		return NULL;
	}

	return this;
}

void generic_list_display(generic_list_t *this)
{
	generic_list_t *temp=this;
	if(temp == NULL)
    	{
        	printf(" List is empty.");
    	}
    	else
	{
        	while(temp != NULL)
        	{
            		printf(" id = %d\n", temp->generic_variables.id); 
            		printf(" isim = %s\n", user_information_get_name((void*)temp->data));
            		printf(" soyad = %s\n", user_information_get_surname((void*)temp->data));
            		
            		temp = temp->next;                     
        	}
    }
}

void generic_list_add_node(generic_list_t *this, void *node)
{
	generic_list_t *temp=NULL ;
	temp=this;
	temp->generic_variables.id = 1; 

	
	while(temp->next != NULL)
	{	
		
		temp=temp->next;
		printf("temp kontrol\n");
	}
	
	if(temp->data == NULL)
	{	
		printf("data kontrol\n");
		temp->data = node;
			
	}
		
	generic_list_t *temp2 = malloc(sizeof(generic_list_t));
	temp2->next=NULL;
	temp2->data=NULL;
	temp->next = temp2;

}
