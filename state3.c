#include "state3.h"
char* makeSpaces(int indent_level);

/*
typedef struct StringNode
{
	char* word;
	struct StringNode* next;
}StringNode;

typedef struct List
{
	void* first;
	void* last;
	bool void_is_string_node;

	int count
}List;

*/
/*
typedef struct LispNode
{
	void* value;
	struct LispNode* next;

	int count_of_value_items;
	bool value_type;
}*/
enum data_types{is_list, is_string, is_empty_case};

void printLispNodes(LispNode* root, int indent_level)
{
	//LispNode* root_list = (LispNode*) root->value;
	//printf("%x\n", root);
	// can't seem to get the last list
	if(root != NULL)
	{

		// root could have a list in value or a string
		// each node containing a string points to the next one
		if(root->value_type == is_string)
		{
			//printf("indent level %i\n", indent_level);
			//printf("|%s|\n", makeSpaces(indent_level));
			if(root->value != NULL)
			{
				char* string = (char*) root->value;
				printf("%s%s\n", makeSpaces(indent_level), string);
			
				printLispNodes(root->next, indent_level);

			}	
		}
		else if(root->value_type == is_list)
		{
			// visiting a list of lists
			printf("list\n");
			LispNode* list_of_lists_tracker = root;
			LispNode* list_of_strings = (LispNode*) root->value;
			int count = 0;
			while(list_of_lists_tracker != NULL && list_of_strings != NULL)
			{
				printf("%i\n", count);

				printLispNodes(list_of_strings, indent_level + 1);
				list_of_lists_tracker = list_of_lists_tracker->next;
				if(list_of_lists_tracker == NULL)
						break;
				list_of_strings = (LispNode*) list_of_lists_tracker->value;
				count++;
			}
		}
		
	}

	
}
LispNode* cons(void* data, void* link, int data_type)
{
	LispNode* new_ob = malloc(sizeof(LispNode));
	new_ob->value = data;
	new_ob->next = link;
	//printf("void link %i\n", link);
	//printf("void data %i\n", data);
	
	/*if(data_type == is_string)
	{
		char* x = (char*) new_ob->value;
		printf("saved string %s\n", x);
	}*/
	if(data_type == is_list)
		new_ob->value_type = is_list;
	else if(data_type == is_string)
		new_ob->value_type = is_string;
	else if(data_type == is_empty_case)
		new_ob->value_type = is_empty_case;
	return new_ob;

}
LispNode* makeLispNode()
{
	LispNode* node = malloc(sizeof(LispNode));
	node->value = NULL;
	node->next = NULL;
	node->count_of_value_items = 0;

	node->value_type = 2;


	// not valid anymore
	// char* = 0
	// LispNode* = 1

	// unset = 2
	return node;
}

LispNode* setValueToList(LispNode* list_a, LispNode* list_b)
{
	if(list_b->value_type == 2)
	{
		list_a->value = list_b;
		list_a->count_of_value_items = 1;
		list_a->value_type = 1;
		list_a->next = makeLispNode();

	}

	return list_a;
}
LispNode* setValueToString(LispNode* list, char* word)
{
	if(list->value_type == 2)
	{
		list->value = strdup(word);
		printf("SAVED VALUE %s\n", list->value);
		list->count_of_value_items = 1;
		list->value_type = 0;
		list->next = makeLispNode();


	}
	return list;
}
/*
LispNode* appendList(LispNode* root, LispNode* list_a, LispNode* list_b)
{
	// assume root -> list_a
	// grow the list, don't nest it
	list_a->value = list_b;
	root->count_of_value_items++;
	list_a->next = makeLispNode();
	return root;
}
*/


ContextState* duplicate(ContextState* item)
{

	ContextState* the_duplicate = malloc(sizeof(ContextState));
	//printf("allocating\n");
	//printf("item = %s\n", item->name);
	the_duplicate->name = strdup(item->name);

	/*malloc(sizeof(char) * strlen(item->name));
	memcpy(the_duplicate->name, item->name, sizeof(char) * strlen(item->name));
	the_duplicate->name[strlen(item->name)] = '\n';*/
	//printf("done allocating\n");
	return the_duplicate;

}

ContextState* initContextState()
{
	ContextState* test =  malloc(sizeof(ContextState));
	test->parents_size = 0;
	test->children_size = 0;

	//test->name = malloc(sizeof(char) * 50);
	//memcpy(test->name, input, sizeof(char) * strlen(input));

	return test;
}
void printState(ContextState* node)
{
	if(node != NULL)
	{
		printf("\nname: %s\n", node->name);
		printf("parents: size = %i\n", node->parents_size);
		for(int i = 0; i < node->parents_size; i++)
		{
			printf("%s, ", node->parents_names[i]);
		}
		printf("\n");
		printf("children: size = %i\n", node->children_size);
		for(int i = 0; i < node->children_size; i++)
		{
			printf("%s, ", node->children_names[i]);
		}
		printf("\n");

	}
}
// unit test all of these functions
ContextState* setName(ContextState* node, char* name)
{
	// if I don't put name_length here the size of the new string has changed possibly due to setting node->name
	int name_length = strlen(name);

	node->name = malloc(sizeof(char) * name_length);
	// strlen(name) appears to change when 		node->name[0] = malloc(sizeof(char) * name_length); is run

	//printf("name size %i\n", name_length);

	//node->name[0] = malloc(sizeof(char) * name_length);
	//printf("name size %lu\n", x);

	memcpy(node->name, name, sizeof(char) * (name_length + 1));

	//node->name[name_length] = '\0';

	return node;

}
ContextState* appendParent(ContextState* node, ContextState* parent)
{

	//printf("append parent\n");

	if(node->parents_size == 0)
	{
		node->parents_size = 1;

		node->parents = malloc(sizeof(ContextState**));
		if(!node->parents) exit(1);
		node->parents[0] = parent;

	}
	else if(node->parents_size > 0)
	{
		node->parents_size += 1;
		// only use malloc and free
		ContextState** new_parents = malloc(sizeof(ContextState*) * node->parents_size);
		if(!new_parents) exit(1);

		memcpy(new_parents,
			   node->parents,
			   sizeof(ContextState*) * node->parents_size-1);
		free(node->parents);
		node->parents = new_parents;
		node->parents[node->parents_size - 1] = parent;

	}


	//printf("%s\n", node->parents[0]->name);
	//printf("passes parent\n");
	//memcpy(node->parents, parent, 1);
	return node;
}

ContextState* appendChild(ContextState* node, ContextState* child)
{
	//printf("append child\n");

	if(node->children_size == 0)
	{
		node->children_size = 1;

		node->children = malloc(sizeof(ContextState**));

		if(!node->children) exit(1);
		//printf("child saved 1.2.0 %s\n", child->name);

		//memcpy(node->children[0], child, sizeof(ContextState*));

		node->children[0] = child;
		//printf("child saved 1.2.9 %s\n", child->name);


	}
	else if(node->children_size > 0)
	{
		//printf("here\n");
		node->children_size += 1;
		ContextState** new_children = malloc(sizeof(ContextState*) * node->children_size);

		if(!new_children) exit(1);
		memcpy(new_children,
			   node->children,
			   sizeof(ContextState*) * node->children_size - 1);

		new_children[node->children_size - 1] = child;

		free(node->children);
		//printf("got here\n");
		//exit(0);
		node->children = new_children;
		//printf("afer adding in\n");
		//printTree(node, 0);

	}


	//printf("%s\n", node->parents[0]->name);
	//printf("passes child\n");
	//memcpy(node->parents, parent, 1);
	return node;
}
/*
char** setLink(int* size, char** names, const char* other_node)
{
	// case 0 works
	if(*size == 0)
	{
		*size = 1;
		names = malloc(sizeof(char*));
		if(!names) exit(1);
		names[0] = strdup(other_node);

	}
	// case 1, n not tested
	else if(*size > 0)
	{
		*size += 1;
		char** new_children = malloc(sizeof(char*) * (*size));

		if(!new_children) exit(1);

		// using old size
		for(int i = 0; i < (*size) - 1; i++)
		{
			new_children[i] = strdup(names[i]);
			free(names[i]);
		}
		new_children[(*size)] = strdup(other_node);


		free(names);
		names = new_children;
	}
	// not sure why we need to return names or segfault
	return names;
}
*/