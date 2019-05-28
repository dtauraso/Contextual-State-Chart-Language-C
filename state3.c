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
char* lispNodeType(int type_value)
{
	if(type_value == is_list)
	{
		return "is_list";
	}
	else if(type_value == is_string)
	{
		return "is_string";
	}
	else if(type_value == is_empty_case)
	{
		return "is_empty_case";
	}
	else
	{
		return NULL;
	}
}
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
				// returns NamesSize*
				printLispNodes(root->next, indent_level);

			}	
		}
		else if(root->value_type == is_list)
		{
			// visiting a list of lists
			//printf("list\n");
			LispNode* list_of_lists_tracker = root;
			LispNode* list_of_strings = (LispNode*) root->value;
			int count = 0;
			while(list_of_lists_tracker != NULL && list_of_strings != NULL)
			{
				//printf("%i\n", count);
				printf("count %i\n", list_of_lists_tracker->count);
				// doesn't return anything to use
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
// list of lists -> lisp chain -> char pointers
void printNodes2(LispNode* root)
{
	/*
	typedef struct ListOfNames
	{
		char*** list_of_names;
		int* names_sizes;
		int list_of_names_size;

	}ListOfNames;

	*/
	printf("PRINTING\n");
	// assume root has 2 levels of strings and 1 level of root
	if(root != NULL)
	{
		// char** words, int* start_indexes(traversal: current index of the words, index of i+1th start_indexes )
		// test with 
		/*
		[["child", "nexts"],
           ["sibling"],
           ["new_parent"]]
           	total strings
			["indent_number", "0", "76543"]
			# of lists
			[0]

           ["child", "nexts", "sibling", "new_parent"]
           [0, 2, 3]
           i = 0, 1, 2, 3
           j = 2, 3


			["root", "0"]
			[0, 1]

	
           collect data
           i++
           if i == j at end of current "list" of strings
				j++
				if j is out of bounds
					done
			if i > j
				done

		*/
		printf("total = %i\n", root->call_count);
		ListOfNames* list_of_words = malloc(sizeof(ListNames));
		list_of_words->list_of_names = malloc(sizeof(char**) * root->count);
		memset(list_of_words->list_of_names, 0, sizeof(char**) * root->count);
		list_of_words->names_sizes = malloc(sizeof(int));
		memset(list_of_words->names_sizes, 0, sizeof(int) * root->count);
		//LispNode* n = NULL;
		LispNode* list_of_lists_tracker = root->value;
		int count = list_of_lists_tracker->count;
		if(root->count == 1)
		{
			// list of strings
			printf("list of strings %i\n", root->count);

			// wrong
			// 1 list of words
			list_of_words->names_sizes[0] = 1;
			// 1 list holding 1 list of words
			list_of_words->list_of_names_size = 1;
		}
		else
		{
			printf("list of lists of strings %i\n", root->count);

			list_of_words->list_of_names_size = list_of_lists_tracker->count;
			printf("count %i\n", list_of_words->list_of_names_size);
			//list_of_words->list_of_names_size = list_of_lists_tracker->count;
		}
		//printf("list_of_words->list_of_names_size 2 %i\n", list_of_words->list_of_names_size);


		printf("# of items %i\n", count);
		//printf("type %s\n", lispNodeType(list_of_lists_tracker->value_type));

		list_of_lists_tracker = (LispNode*) list_of_lists_tracker->value;
		int i = 0;
		while(list_of_lists_tracker != NULL && i < root->count)
		{
			printf("# of sub items LIST %i: %i, %i\n", list_of_lists_tracker->count, i, root->count);
			//printf("type %s\n", lispNodeType(list_of_lists_tracker->value_type));
			//list_of_words->names_sizes[i] = 0;

			list_of_words->list_of_names[i] = malloc(sizeof(char*) * list_of_lists_tracker->count/*what goes here*/);
			//memset(list_of_words->list_of_names[i], 0,  list_of_lists_tracker->count);


			// [0][3] = [2][0]
			// (i, j) => (0, k)
			// i*j
			// root->count * ith list_of_lists_tracker->count
			//printf("here\n");
			LispNode* list_of_strings_tracker = list_of_lists_tracker->value;
			int j = 0;
			// char* list_of_string_collected = f(list_of_strings_tracker, list_of_words->list_of_names[i])
			while(list_of_strings_tracker != NULL && j < list_of_lists_tracker->count)
			{
				//printf("# of sub sub items %i\n", list_of_strings_tracker->count);
				//printf("type %s\n", lispNodeType(list_of_strings_tracker->value_type));

				//list_of_words->names_sizes[i] = 
				// still on the char**
				// not actually at the char* or the char
				list_of_words->list_of_names[i][j] = malloc(sizeof(char) * strlen(list_of_strings_tracker->value));
				//memset(list_of_words->list_of_names[i][j], 0, sizeof(char));
				//list_of_words->list_of_names[i][j] = list_of_strings_tracker->value; //malloc(sizeof(char) * strlen(list_of_strings_tracker->value));
				// setting it after above line to prevent the mess up
				printf("		%s: %i\n", list_of_strings_tracker->value, j);
				printf("		%i, %i\n", i, j);
				printf("		%x\n", list_of_words->list_of_names[i][j]);
				//printf()
				memcpy(list_of_words->list_of_names[i][j],
					list_of_strings_tracker->value,
					sizeof(char) * strlen(list_of_strings_tracker->value));
				printf(" name found %x\n", list_of_words->list_of_names[i][j]);

				//printf("		%s\n", list_of_words->list_of_names[i][j]);

				list_of_strings_tracker = list_of_strings_tracker->next;

				j++;
				printf("j incremented %i\n", j);
				printf(" name found 2 %x\n", list_of_words->list_of_names[0][0]);

			}
			printf(" name found 3 %x\n", list_of_words->list_of_names[0][0]);

			//printf("list_of_words->list_of_names_size 4 %i\n", list_of_words->list_of_names_size);

			list_of_words->names_sizes[i] = list_of_lists_tracker->count;
			//printf("size %i\n", list_of_words->names_sizes[i]);

			list_of_lists_tracker = list_of_lists_tracker->next;
			// don't want the size to increase if there is nothing there
			// not quite it yet
			if(list_of_lists_tracker != NULL)
			{
				//list_of_words->list_of_names_size += 1;
				//break;
				i++;
				printf("i incremented %i\n", i);
				printf("		%i, %i\n", i-1, j-1);

				printf(" name found 4 %x\n", list_of_words->list_of_names[0][0]);

			}
			else
			{
				printf("i incremented %i\n", i);
				printf("		%i, %i\n", i, j-1);

				printf(" name found 4 %x\n", list_of_words->list_of_names[0][0]);

				break;
			}



		}
		/*
		char*** list_of_names;
		int* names_sizes;
		int list_of_names_size;
		*/
		printf("list_of_words->list_of_names_size ::: %i\n", list_of_words->list_of_names_size);
		// erased after setting it?
		//printf(" name found again %s\n", list_of_words->list_of_names[0][0]);

		for(int k = 0; k < list_of_words->list_of_names_size; k++)
		{
			//printf("%i\n", list_of_words->names_sizes[k]);
			
			for(int l = 0; l < list_of_words->names_sizes[k]; l++)
			{
				printf("%i, %i\n", k, l);
				//printf("|%s|\n", list_of_words->list_of_names[k][l]);
			}
		}
		
		
	}
	printf("DONE PRINTING\n");
}
void collectNodes2(LispNode* root)
{
	
	//printf("PRINTING\n");
	// assume root has 2 levels of strings and 1 level of root
	if(root != NULL)
	{
		ListOfNames* list_of_words = malloc(sizeof(ListNames));
		//LispNode* n = NULL;
		if(root->count == 1)
		{
			// list of strings
			printf("list of strings %i\n", root->count);
			list_of_words->list_of_names = malloc(sizeof(char**) * root->count);
			memset(list_of_words->list_of_names, 0, sizeof(char**) * root->count);
			//n = root->value;
		}
		else
		{
			printf("list of lists of strings %i\n", root->count);
			//n = root->value;
		}
		LispNode* list_of_lists_tracker = root->value;
		int count = list_of_lists_tracker->count;
		printf("# of items %i\n", count);
		//printf("type %s\n", lispNodeType(list_of_lists_tracker->value_type));

		list_of_lists_tracker = (LispNode*) list_of_lists_tracker->value;

		while(list_of_lists_tracker != NULL)
		{
			printf("# of sub items LIST %i\n", list_of_lists_tracker->count);
			//printf("type %s\n", lispNodeType(list_of_lists_tracker->value_type));
			LispNode* list_of_strings_tracker = list_of_lists_tracker->value;
			if(list_of_strings_tracker != NULL)
			{
				while(list_of_strings_tracker != NULL)
				{
					//printf("# of sub sub items %i\n", list_of_strings_tracker->count);
					//printf("type %s\n", lispNodeType(list_of_strings_tracker->value_type));
					printf("		%s\n", list_of_strings_tracker->value);
					list_of_strings_tracker = list_of_strings_tracker->next;

				}
			}

			list_of_lists_tracker = list_of_lists_tracker->next;
		}
		
		
	}
	//printf("DONE PRINTING\n");
}

/*
void* createContextStateAttribute(LispNode* root, int indent_level)
{
	// indent_level = 1, 2, 3

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
				//printf("%s%s\n", makeSpaces(indent_level), string);
			
				NamesSize* words = (NamesSize*) createContextStateAttribute(root->next, indent_level);
				words->names[indent_level] = malloc(sizeof(char) * strlen(string));
				memcpy(words->names + indent_level, string, sizeof(char) * strlen(string));
				return words;

			}	
			else
			{
				// indent_level is the count
				// set up names to have 
				NamesSize* words = malloc(sizeof(NamesSize));

				words->names = malloc(sizeof(char*) * indent_level);

				words->size = indent_level;
				return words;
			}
		}
		else if(root->value_type == is_list)
		{
			// visiting a list of lists
			//printf("list\n");
			LispNode* list_of_lists_tracker = root;
			LispNode* list_of_strings = (LispNode*) root->value;
			int count = 0;
			ListNames* list_of_names = malloc(sizeof(ListNames));

			while(list_of_lists_tracker != NULL && list_of_strings != NULL)
			{
				//printf("%i\n", count);

				NamesSize* filled_words = (NamesSize*) createContextStateAttribute(list_of_strings, indent_level + 1);

				list_of_lists_tracker = list_of_lists_tracker->next;
				if(list_of_lists_tracker == NULL)
						break;
				list_of_strings = (LispNode*) list_of_lists_tracker->value;
				count++;
			}
		}
		
	}

	
}
*/

LispNode* cons(void* data, void* link, int data_type, int count, int call_count)
{
	LispNode* new_ob = malloc(sizeof(LispNode));
	new_ob->value = data;
	new_ob->next = link;
	new_ob->count = count;
	new_ob->call_count = call_count;
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
	node->count = 0;

	node->value_type = 2;


	// not valid anymore
	// char* = 0
	// LispNode* = 1

	// unset = 2
	return node;
}




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
/*
ContextState* makeFullContextState(
	LispNode* nexts,
	LispNode* start_children,
	LispNode* children,
	char* function_name,
	Data* variable_from_json_dict,
	LispNode* parents)
{

	ContextState* node = malloc(sizeof(ContextState));
	

}
*/
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