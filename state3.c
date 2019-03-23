#include "state3.h"


ContextState* ContextState1()
{
	ContextState* test =  malloc(sizeof(ContextState));
	test->parents_size = 0;
	test->children_size = 0;

	//test->name = malloc(sizeof(char) * 50);
	//memcpy(test->name, input, sizeof(char) * strlen(input));

	return test;
}

ContextState* setName(ContextState* node, char* name)
{
	//printf("preparing name|%s|%lu\n", name, strlen(name));
	node->name = malloc(sizeof(char) * strlen(name));

	memcpy(node->name, name, strlen(name));
	node->name[strlen(name)] = '\0';
	//printf("finished name|%s|%lu\n", node->name, strlen(node->name));

	return node;

}
ContextState* appendParent(ContextState* node, ContextState* parent)
{


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

		node->parents = realloc(node->parents, sizeof(ContextState**) * node->parents_size);
		if(!node->parents) exit(1);
		node->parents[node->parents_size-1] = parent;

	}


	//printf("%s\n", node->parents[0]->name);
	//printf("passes\n");
	//memcpy(node->parents, parent, 1);
	return node;
}

ContextState* appendChild(ContextState* node, ContextState* child)
{

	if(node->children_size == 0)
	{
		node->children_size = 1;
		node->children = malloc(sizeof(ContextState**));
		if(!node->children) exit(1);
		node->children[0] = child;

	}
	else if(node->children_size > 0)
	{
		node->children_size += 1;

		node->children = realloc(node->children, sizeof(ContextState**) * node->children_size);
		if(!node->children) exit(1);

		node->children[node->children_size-1] = child;

	}


	//printf("%s\n", node->parents[0]->name);
	//printf("passes\n");
	//memcpy(node->parents, parent, 1);
	return node;
}
