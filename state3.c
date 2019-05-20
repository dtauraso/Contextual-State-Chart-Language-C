#include "state3.h"
#include "hash_table1.h"
void* ht_search(ht_hash_table* ht, const char* key);
void* getValueAt(ht_hash_table* ht, int i);


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
//enum doubly_linked_attribues {children, parents};
/*
void appendLink(ht_hash_table* states,
			    const char* node,
				const char* other_node, // child node or parent node
				int attribute)
{
	// node -> other_node
	//printf("append other_node\n");
 	//printf("appending 2 %s <=> %s\n", node, other_node);
	//printHash(states);
	ContextState* other_node_state = (ContextState*) ht_search(states, other_node);
	ContextState* node_state = (ContextState*) ht_search(states, node);
	//printf("%i\n", node_state);
	//printf("%i\n", node_state->children_size);
	//printf("%s\n", node_state->name);
	//printf("node is valid\n");

	// attribute == children
	if(attribute == 0)
	{
		//printf("setting children\n");
		// setLink(&node_state->children_size, node_state->children_names, other_node);
		node_state->children_names = setLink(&node_state->children_size, node_state->children_names, other_node);
		//printf("saved\n");
		//printf("name saved: %s\n", node_state->children_names[0]);

		//printState(node_state);

	}
	else
	{
		//printf("setting parents\n");
		// setLink(&node_state->parents_size, node_state->parents_names, other_node);
		node_state->parents_names = setLink(&node_state->parents_size, node_state->parents_names, other_node);
		//printf("saved\n");
		//printf("name saved: %s\n", node_state->parents_names[0]);
		//printState(node_state);


	}

	// if it returns the table the table gets corrupted
	//return states;
}*/
