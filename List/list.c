#include <stdlib.h>
#include <stdio.h>
#include "list.h"

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
            		temp = temp->next;                     
        	}
    }
}



void generic_list_add_node(generic_list_t *this, void *node)
{
	struct generic_list *temp=NULL;
	this->generic_variables.id = 1; 
	this->data = node;
	this->next = NULL; 
	temp = this;
}


