#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "list.h"
#include "user.h"

generic_list_t *generic_list_create()
{
	generic_list_t *this = malloc(sizeof(generic_list_t));

	if (!this)
	{
		return NULL;
	}

	return this;
}

void generic_list_display(generic_list_t *this)
{
	struct generic_list *temp=this;
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
	struct generic_list *temp=NULL ,*temp2=NULL;
	
	this->generic_variables.id = 1; 
	temp=this;
	
	while(temp != NULL)
	{
		if(temp->data == NULL)
		{	
		printf("\ndata 1 KONTROL:%p\n",temp->data);
			temp->data = node;
			printf("\n data 2 KONTROL:%p\n",temp->data);
		}
		printf("\ntemp 1 KONTROL:%p\n",temp);
		temp=temp->next;
		printf("\ntemp 2 KONTROL:%p\n",temp);
	}
	
	if(temp == NULL)
	{
		struct generic_list *temp2 = malloc(sizeof(generic_list_t));
		printf("\n temp2  KONTROL:%p\n",temp2);
		temp2->next=NULL;
		temp2->data=NULL;
		temp = temp2;
		printf("\ntemp 3 KONTROL:%p\n",temp);
	}
}
