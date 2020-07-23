#ifndef LIST_H
#define LIST_H

typedef struct 
{
	int id;
} variables_t;

typedef struct generic_list
{
	variables_t generic_variables;
	void *data;
	struct generic_list *next;
} generic_list_t;

generic_list_t *generic_list_create();
void generic_list_destroy();
void generic_list_init(generic_list_t *this);
void generic_list_display(generic_list_t *this);
generic_list_t *generic_list_search(generic_list_t *this, int id);
void generic_list_add_node(generic_list_t *this, void *node);
void generic_list_delete_node(generic_list_t *this, int id);

#endif
