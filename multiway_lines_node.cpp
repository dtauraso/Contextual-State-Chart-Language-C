#include "multiway_lines_node.h"

/*
typedef struct Vector
{
	void** values;
	int size;
	int population;


}Vector;


Vector* initVector()
{
	Vector* new_container = (Vector*) malloc(sizeof(Vector));
	new_container->values = NULL;
	new_container->size = 0;
	new_container->population = 0;
	return new_container;
}
Vector* initVectorSize(int size)
{
	Vector* new_container = (Vector*) malloc(sizeof(Vector) * size);
	new_container->values = (void**) malloc(sizeof(void*) * size);
	new_container->size = size;
	new_container->population = 0;
	return new_container;
}
bool deleteVector(Vector* container)
{
	for(int i = 0; i < container->population; i++)
	{
		free(container->values[i]);
		container->values[i] = NULL;
	}
	free(container->values);
	container->values = NULL;
	return true;
}

int getLastIndex(Vector* container)
{
	return container->population - 1;
}
void* getItem(Vector* container, int i)
{
	//printf("getting item %i, %i\n", i, container->population);
	if(i < container->population && i >= 0)
	{
		//printf("item |%x|\n", container->values[i]);
		return container->values[i];
	}
	else
	{
		//printf("out of bounds\n");
		return NULL;
	}
}
void Print(Vector* container)
{
	printf("printing container pop %i, size %i\n", container->population, container->size);
	for(int i = 0; i < container->population; i++)
	{
		//printf("i %i\n", i);
		if(container->values[i] == NULL)
		{
			printf("|NULL|\n");
		}
		else
		{
			//printf("|%x|", container->values[i]);
			void* a = container->values[i];
			int* b = (int*) a;
			printf("|%i|\n", *b);
			
			//printf("|item|");
		}
	}
	printf("\n");

}
void append(Vector* container, void* element)
{
	if(container != NULL)
	{
		//printf("pop %i, size %i\n", container->population, container->size);

		if(container->size == 0)
		{
			//printf("insert 0\n");
			container->values = (void**) malloc(sizeof(void*));
			container->size = 1;
			container->values[0] = element;
			container->population = 1;

		}
		else if(container->population == container->size)
		{

			//printf("size %i\n", container->size);

			container->size *= 2;

			container->values = (void**) realloc(container->values, sizeof(void*) * container->size);


			container->values[container->population] = element;
			container->population += 1;

			
		}
		else if(container->population < container->size)
		{
			//printf("regular\n");

			container->values[container->population] = element;
			container->population += 1;

		}
		//printf("result\n");
		//Print(container);
	}

}
bool deleteItem(Vector* container, int index)
{
	//printf("delete at %i\n", index);
	// set container[index] to null
	// shift all values from [index + 1, end] to the left by 1
	if(container != NULL)
	{
		free(container->values[index]);
		container->values[index] = NULL;
		if(index < container->population)
		{
			for(int i = index + 1; i < container->population; i++)
			{
				container->values[i - 1] = container->values[i];

				container->values[i] = NULL;

			}
			container->population--;
		}
		return true;
	}
	return false;
}

void test()
{
	// make a vector
	Vector* my_vector = initVector();

	// add a list of numbers

	int* a = (int*) malloc(sizeof(int));
	*a = 0;
	append(my_vector, a);
	Print(my_vector);
	int* b = (int*) malloc(sizeof(int));
	*b = 1;
	append(my_vector, b);
	Print(my_vector);

	int* c = (int*) malloc(sizeof(int));
	*c = 2;
	append(my_vector, c);
	Print(my_vector);

	int* d = (int*) malloc(sizeof(int));
	*d = 2;
	append(my_vector, d);
	Print(my_vector);


	deleteItem(my_vector, 1);
	Print(my_vector);
	deleteItem(my_vector, 2);
	Print(my_vector);

	deleteItem(my_vector, 0);
	Print(my_vector);

	deleteItem(my_vector, 0);
	Print(my_vector);	
	
	for(int i = 0; i < 5; i++)
	{
		printf("inserting %i\n", i);
		int* j = &i;
		append(my_vector, j, 0);
		Print(my_vector);
		//printf("element added %i\n", (int) my_vector->values[i]);
	}
	printf("here\n");
	for(int i = 0; i < 5; i++)
	{
		if(my_vector->values[i] == NULL)
		{
			printf("problem\n");
		}
		void* a = my_vector->values[i];
		int* b = (int*) a;
		printf("%i\n", *b);
	}

	// erase a list of numbers
}
*/
/*
typedef struct MultiwayLinesNode
{
	char* line;
	struct MultiwayLinesNode** parents;
	int parents_size;
	struct MultiwayLinesNode** children;
	int children_size;
}MultiwayLinesNode;

*/
// utility functions from main
char* makeSpaces(int indent_level);
int countLines(char* input);
char* getNextWord(char* input, int i);
int countTabs(char* input, int i);
void swap(int* a, int* b);
char* copyString(char* b);

void printMultiwayLinesNodesInContainer(Vector* container)
{
	for(int i = 0; i < container->population; i++)
	{
		//printf("i %i\n", i);
		if(container->values[i] == NULL)
		{
			printf("|NULL|\n");
		}
		else
		{
			printf("i %i\n", i);
			//printf("|%x|", container->values[i]);
			//void* a = container->values[i];
			MultiwayLinesNode* node = getMultiwayLinesNode(getItem(container, i));
			printf("%s\n", node->line.c_str());

			printf("parent %i\n", node->parent_id);

			printf("children\n");
			for(int j = 0; j < node->children_ids->population; j++)
			{
				printf("%i\n", *getInt(getItem(node->children_ids, j)));
			}
			printf("\n\n");
			//int* b = (int*) a;
			//printf("|%i|\n", *b);
			
			//printf("|item|");
		}
	}
}

// create
MultiwayLinesNode* initMultiwayLinesNode()
{
	MultiwayLinesNode* new_parse_node = (MultiwayLinesNode*) malloc(sizeof(MultiwayLinesNode));
	new_parse_node->line = "";
	new_parse_node->parents = NULL;
	new_parse_node->parents_size = 0;
	new_parse_node->parent_id = 0;
	new_parse_node->children = NULL;
	new_parse_node->children_size = 0;
	new_parse_node->children_ids = initVector();
	return new_parse_node;
}
// destroy
bool deleteMultiwayLinesNode(MultiwayLinesNode* node)
{
	if(node != NULL)
	{
		//MultiwayLinesNode* new_parse_node = malloc(sizeof(MultiwayLinesNode));
		//new_parse_node->line = NULL;
		//new_parse_node->parents = NULL;
		//new_parse_node->parents_size = 0;
		//new_parse_node->children = NULL;
		//new_parse_node->children_size = 0;

		//delete(node->line);
		//node->line = NULL;
		// erase children first so the children on branches not visited are still connected

		for(int i = 0; i < node->children_size; i++)
		{
			deleteMultiwayLinesNode(node->children[i]);
		}
		free(node->children);
		node->children = NULL;

		for(int i = 0; i < node->parents_size; i++)
		{
			deleteMultiwayLinesNode(node->parents[i]);
		}
		free(node->parents);
		node->parents = NULL;
		free(node);
		node = NULL;
		return 1;
	}
	
	return 1;
}

// unit test all of these functions
MultiwayLinesNode* setName(MultiwayLinesNode* node, string line)
{
	// if I don't put name_length here the size of the new string has changed possibly due to setting node->name
	//int line_length = strlen(line);

	//node->line = (char*) malloc(sizeof(char) * line_length);
	// strlen(name) appears to change when 		node->name[0] = malloc(sizeof(char) * name_length); is run

	//printf("name size %i\n", name_length);

	//node->name[0] = malloc(sizeof(char) * name_length);
	//printf("name size %lu\n", x);
	node->line = line;
	//memcpy(node->line, line, sizeof(char) * (line_length + 1));

	//node->name[name_length] = '\0';

	return node;

}
MultiwayLinesNode* appendParent(MultiwayLinesNode* node, MultiwayLinesNode* parent)
{

	//printf("append parent\n");

	if(node->parents_size == 0)
	{
		node->parents_size = 1;

		node->parents = (MultiwayLinesNode**) malloc(sizeof(MultiwayLinesNode*));
		if(!node->parents) exit(1);
		node->parents[0] = parent;

	}
	else if(node->parents_size > 0)
	{
		//printf("%s\n", node->line);
		node->parents_size += 1;
		// only use malloc and free
		MultiwayLinesNode** new_parents = (MultiwayLinesNode**) malloc(sizeof(MultiwayLinesNode*) * node->parents_size);
		if(!new_parents) exit(1);

		//make new nodes
		//	copy string from old node to new node
		/*
		for(int i = 0; i < node->parents_size - 1; i++)
		{
			new_parents[i] = initMultiwayLinesNode();
			new_parents[i]->line = copyString(node->parents[i]->line);
		}*/
		for(int i = 0; i < node->parents_size - 1; i++)
		{
			new_parents[i] = node->parents[i];//initMultiwayLinesNode();
			//new_parents[i]->line = copyString(node->parents[i]->line);
		}
		/*
		memcpy(new_parents,
			   node->parents,
			   sizeof(MultiwayLinesNode*) * node->parents_size-1);
		*/
	    new_parents[node->parents_size - 1] = parent;

		for(int i = 0; i < node->parents_size - 1; i++)
		{
			node->parents[i] = NULL;
		}
		free(node->parents);
		node->parents = new_parents;
		//printf("%s\n", node->line);

		//node->parents[node->parents_size - 1] = parent;

	}


	//printf("%s\n", node->parents[0]->name);
	//printf("passes parent\n");
	//memcpy(node->parents, parent, 1);
	return node;
}

MultiwayLinesNode* appendChild(MultiwayLinesNode* node, MultiwayLinesNode* child)
{
	//printf("append child\n");

	if(node->children_size == 0)
	{
		node->children_size = 1;

		node->children = (MultiwayLinesNode**) malloc(sizeof(MultiwayLinesNode*));

		if(!node->children) exit(1);
		//printf("child saved 1.2.0 %s\n", child->name);

		//memcpy(node->children[0], child, sizeof(MultiwayLinesNode*));

		node->children[0] = child;
		//printf("child saved 1.2.9 %s\n", child->name);


	}
	else if(node->children_size > 0)
	{
		//printf("%s\n", node->line);

		//printf("here\n");
		node->children_size += 1;
		MultiwayLinesNode** new_children = (MultiwayLinesNode**) malloc(sizeof(MultiwayLinesNode*) * node->children_size);

		if(!new_children) exit(1);

		

		//make new nodes
		//	copy string from old node to new node
		/*
		for(int i = 0; i < node->children_size - 1; i++)
		{
			new_children[i] = initMultiwayLinesNode();
			new_children[i]->line = copyString(node->children[i]->line);
		}
		*/
		for(int i = 0; i < node->children_size - 1; i++)
		{
			new_children[i] = node->children[i];//initMultiwayLinesNode();
			//new_children[i]->line = copyString(node->children[i]->line);
		}
		/*
		memcpy(new_children,
			   node->children,
			   sizeof(MultiwayLinesNode*) * node->children_size - 1);
		*/
		new_children[node->children_size - 1] = child;

		for(int i = 0; i < node->children_size - 1; i++)
		{
			node->children[i] = NULL;
		}
		free(node->children);
		//printf("got here\n");
		//exit(0);
		node->children = new_children;
		//printf("%s\n", node->line);

		//printf("afer adding in\n");
		//printTree(node, 0);

	}


	//printf("%s\n", node->parents[0]->name);
	//printf("passes child\n");
	//memcpy(node->parents, parent, 1);
	return node;
}
void printTree(MultiwayLinesNode* root, int indent_level)
{
	//printf("here %x\n", root);
	// is not root equal to NULL?
	//printf("%i\n", indent_level);
	/*
	root_equals_null
		next
			done_root_equals_null
	root_is_real
		next
			(root_line_is_not_equal_to_null | root_line_is_equal_to_null), visit_children

	visit_children
		child
			children
				next
					(root_equals_null | root_is_real)

	root_line_is_not_equal_to_null
		next
			(indent_level_greater_than_0 | indent_level_not_greater_than_0)

	indent_level_greater_than_0
		next
			make_indents, indents_is_real, free_indents, visit_children


	indent_level_not_greater_than_0
		next
			print_line, visit_children


	root_line_is_equal_to_null
		next
			visit_children
	another_case

	*/
	// if root is non existent, then we compare it's opposite to NULL
	if(root == NULL)
	{
		//printf("null node\n");
		return;
	}
	else
	{
		if(root->line.size() > 0)
		{

			if(indent_level > 0)
			{
				string indents = makeSpaces(indent_level);
				if(indents.size() > 0)
				{
					printf("%s%i %s\n\n", indents.c_str(), indent_level, root->line.c_str());

				}

				//free(indents);
				//indents = NULL;

			}
			else
			{
						//printf("here\n");

				printf("%s\n\n", root->line.c_str());

			}
		}
		else
		{
			printf("no line\n\n");
		}
		//printf("screwed\n");
		for(int i = 0; i < root->children_size; i++)
		{
			//printf("%i\n", i);
			//printf("%x\n", root->children[i]);
			//if()
			printTree(root->children[i], indent_level + 3);
		}

	}
	return;
}
string makeSpaces2(int indent_level)
{
	/*if(indent_level == 0)
	{
		return ' ';
	}*/
	//printf("making indents\n");
	indent_level++;
	//printf("here\n");

	//string indents2;
	string x = "";
	//printf("here 2\n");

	for(int i = 0; i < indent_level; i++)
	{
		//printf("%i|%s|\n", i, x.c_str());

		x += ' ';
	}
	/*
	char* indents;
	indents = malloc(indent_level + 1);
	memset(indents, ' ', sizeof(char) * indent_level);
	indents[indent_level] = '\0';
	*/
	//printf("|%s|\n", indents2.c_str());


	
	return x;


}
void printTree2(Vector* container, int root, int indent_level)
{
	//printf("start of call %i\n", root);
	// in order traversal
	if(root < 0)
	{
		return;
	}
	else
	{
		MultiwayLinesNode* root_node = getMultiwayLinesNode(getItem(container, root));
		if(root_node != NULL)
		{
			//printf("node is not null %s, %i\n", root_node->line.c_str(), indent_level);
			if(root_node->line.size() > 0)
			{
				if(indent_level > 0)
				{
					//printf("about to make indents\n");
					string indents = makeSpaces2(indent_level);
					//printf("got indents\n");
					if(indents.size() > 0)
					{
						printf("%s%i %s\n\n", indents.c_str(), indent_level, root_node->line.c_str());

					}

					//free(indents);
					//indents = NULL;
				}
				else
				{
					printf("%s\n\n", root_node->line.c_str());
				}
			}
			else
			{
				printf("no line\n");
			}
			for(int i = 0; i < root_node->children_ids->population; i++)
			{
				int* x = getInt(root_node->children_ids->values[i]);
				//printf("%i, %i\n", i, *x);
				printTree2(container, *x, indent_level + 3);
			}
		}
		
	}
	return;
}
void printParentPath(Vector* container, int start)
{
	if(start < 0)
	{
		return;
	}
	else
	{
		for(int i = start; i >= 0;)
		{
			MultiwayLinesNode* node = getMultiwayLinesNode(getItem(container, i));
			if(node->line.size())
			{
				printf("|%s|\n", node->line.c_str());
			}
			if(i > 0)
			{
				i = node->parent_id;
			}
			else
			{
				i = -1;
			}
		}


	}
}

MultiwayLinesNode* getMultiwayLinesNode(void* raw_node)
{
	//printf("got node |%x|\n", raw_node);
	return (MultiwayLinesNode*) raw_node;
}
int* getInt(void* raw_node)
{
	return (int*) raw_node;
}
// pointer to string saved as a name
void doubleLink(MultiwayLinesNode* parent, MultiwayLinesNode* child)
{
	child = appendParent(child, parent);
	//printf("child saved 1.2 %s\n", child->name);

	parent = appendChild(parent, child);
	//printf("child saved 1.3 %s\n", child->name);


}
void doubleLink2(Vector* container, int parent, int child)
{
	//printf("%i, %i\n", parent, child);
	MultiwayLinesNode* _parent = (MultiwayLinesNode*) container->values[parent];

	MultiwayLinesNode* _child = (MultiwayLinesNode*) container->values[child];

	int* x = (int*) malloc(sizeof(int));
	*x = child;
	//printf("inserting ")
	append(_parent->children_ids, x);
	//Print(_parent->children_ids);
	_child->parent_id = parent;
}
