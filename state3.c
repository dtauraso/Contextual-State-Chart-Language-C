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

// for appendParentHash, appendChildHash
// we are storing the index to the hash table to the state being linked to

ht_hash_table* appendParentHash(ht_hash_table* states,
								int node,
							    int parent)
{
	// we have already looked up the node's name and gotten an index for its location in 
	// the table
	//printf("append parent\n");
	ContextState* parent_state = (ContextState*) getValueAt(states, parent);
	ContextState* node_state = (ContextState*) getValueAt(states, node);
	if( parent_state->parents_size == 0)
	{
		parent_state->parents_size = 1;

		parent_state->parents_hash = malloc(sizeof(int));
		if(!parent_state->parents_hash) exit(1);
		parent_state->parents_hash[0] = parent;

	}
	else if(node_state->parents_size > 0)
	{
		node_state->parents_size += 1;

		int* new_parents = malloc(sizeof(int) * node_state->parents_size);
		if(!new_parents) exit(1);

		memcpy(new_parents,
			   node_state->parents_hash,
			   sizeof(int) * node_state->parents_size - 1);

		free(node_state->parents_hash);
		
		node_state->parents_hash = new_parents;
		node_state->parents_hash[node_state->parents_size - 1] = parent;

	}


	//printf("%s\n", node->parents[0]->name);
	//printf("passes parent\n");
	//memcpy(node->parents, parent, 1);
	return states;
}

// error code
ht_hash_table* appendChildHash(ht_hash_table* states,
							   int node,
							   int child)
{
	printf("append child\n");

	ContextState* child_state = (ContextState*) getValueAt(states, child);
	ContextState* node_state = (ContextState*) getValueAt(states, node);
	printf("%i\n", node_state->children_size);
	printf("%s\n", node_state->name);
	printf("node is valid\n");

	if(node_state->children_size == 0)
	{
		node_state->children_size = 1;

		node_state->children_hash = malloc(sizeof(int));

		if(!node_state->children_hash) exit(1);
		//printf("child saved 1.2.0 %s\n", child->name);

		//memcpy(node->children[0], child, sizeof(ContextState*));
		printf("base case\n");
		node_state->children_hash[0] = child;
		//printf("child saved 1.2.9 %s\n", child->name);


	}
	else if(node_state->children_size > 0)
	{
		//printf("here\n");
		printf("inductive case\n");
		// very large value
		printf("%i\n", node_state->children_size);

		node_state->children_size += 1;
		int* new_children = malloc(sizeof(int) * node_state->children_size);

		if(!new_children) exit(1);
		// problem line
		memcpy(new_children,
			   node_state->children_hash,
			   sizeof(int) * (node_state->children_size - 2) );

		//new_children[node_state->children_size - 1] = child;

		free(node_state->children_hash);
		//printf("got here\n");
		//exit(0);
		node_state->children_hash = new_children;
		//printf("afer adding in\n");
		//printTree(node, 0);

	}


	//printf("%s\n", node->parents[0]->name);
	printf("passes child\n");
	//memcpy(node->parents, parent, 1);
	return states;
}
