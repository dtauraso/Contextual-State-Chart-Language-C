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
char* getIthWord(NeighborNames* name, int i);
int isMatch(char* ith_word, TrieNode* node);
TrieNodePackage* findInTrie(TrieNode* root, NeighborNames* name); // have to update this too
TrieNodePackage* findInTrie2(TrieNode* root, TrieNode* name);

TrieNode* appendNode(TrieNode* node, char* ith_name);
void addToTrie(TrieNode* root, ContextState* state);

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
void deleteLispNodes(LispNode* root)
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
				//printf("%s%s\n", makeSpaces(indent_level), string);
				// returns NamesSize*
				deleteLispNodes(root->next);
				if(root->value != NULL)
				{
					free(root->value);
				}
				if(root->next != NULL)
				{
					free(root->next);
					//free(root);  // temp's value from call in while loop
				}
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
				//printf("count %i\n", list_of_lists_tracker->count);
				// doesn't return anything to use
				deleteLispNodes(list_of_strings);
				LispNode* temp = list_of_lists_tracker;
				list_of_lists_tracker = list_of_lists_tracker->next;

				if(list_of_lists_tracker == NULL)
						break;
				list_of_strings = (LispNode*) list_of_lists_tracker->value;
				
				if(temp->value != NULL)
				{
					free(temp->value);

				}
				if(temp != NULL)
				{
					free(temp);
				}
				count++;
			}
		}
		
	}

	
}
TrieNode* initTrieNode()
{
	TrieNode* node = malloc(sizeof(TrieNode));

	node->word = NULL;
	node->object = NULL;
	node->neighbors = NULL;
	node->neighbors_count = 0;
	node->size = 0;

	return node;

}
TrieNode* initTrieNodeWithNeighborCount(int number_of_neighbors)
{
	TrieNode* node = malloc(sizeof(TrieNode));

	node->word = NULL;
	node->object = NULL;
	if(number_of_neighbors == 0)
	{
		node->neighbors = NULL;
		node->size = 0;
	}
	else
	{
		node->neighbors = malloc(sizeof(TrieNode*) * number_of_neighbors);
		node->size = number_of_neighbors;

	}
	node->neighbors_count = 0;

	return node;

}
void printTrieNodes(TrieNode* trie_node_sequence)
{
	TrieNode* trie_node_sequence_tracker = trie_node_sequence;
	while(trie_node_sequence_tracker != NULL)
	{
		if(trie_node_sequence_tracker->word != NULL)
		{
			printf("%s ", trie_node_sequence_tracker->word);
		}
		if(trie_node_sequence_tracker->neighbors != NULL)
		{
			trie_node_sequence_tracker = trie_node_sequence_tracker->neighbors[0];

		}
		else
		{
			break;
		}

	}
	printf("\n");
}
void printTrieNodeTree(TrieNode* root, int indent)
{
	//printf("printing\n");
	TrieNode* root_tracker = root;
	if(root_tracker != NULL)
	{
		if(root_tracker->word != NULL)
		{
			printf("%s%s\n", makeSpaces(indent), root_tracker->word);
		}
		if(root_tracker->neighbors != NULL)
		{
			//printf("# of neighbors %i\n", root_tracker->neighbors_count);
			for(int i = 0; i < root_tracker->size; i++)
			{
				if(root_tracker->neighbors[i] != NULL)
				{
					printTrieNodeTree(root_tracker->neighbors[i], indent + 2);

				}
			}
		}
	}
	else
	{
		printf("[]\n");
	}
}
// list of lists -> lisp chain -> char pointers
TrieNode* convertLispChainToTrieNodeChain(LispNode* root)
{

	// assume root has 2 levels of strings and 1 level of root
	if(root != NULL)
	{
		// test with 
		/*
		["indent_number", "0", "76543"]
     	
     	[]

		[["child", "nexts"],
	       ["sibling"],
	       ["new_parent"]]

	    [["root"], ["0"]]
		*/
		//printf("total = %i\n", root->call_count);
		

		// storing the list of list of strings

		TrieNode* root2 = initTrieNodeWithNeighborCount(root->call_count);

		LispNode* list_of_lists_tracker = root->value;
		int count = list_of_lists_tracker->count;

		list_of_lists_tracker = (LispNode*) list_of_lists_tracker->value;
		int i = 0;
		while(list_of_lists_tracker != NULL && i < root->count)
		{
			//printf("# of sub items LIST %i: %i, %i\n", list_of_lists_tracker->count, i, root->count);
			TrieNode* trie_node_sequence = initTrieNodeWithNeighborCount(1);
			TrieNode* trie_node_squence_tracker = trie_node_sequence;
			LispNode* list_of_strings_tracker = list_of_lists_tracker->value;
			int j = 0;
			while(list_of_strings_tracker != NULL && j < list_of_lists_tracker->count)
			{

				// add word to trie_node_squence_tracker
				trie_node_squence_tracker->word = malloc(sizeof(char) * strlen(list_of_strings_tracker->value));

				memcpy(trie_node_squence_tracker->word,
					   list_of_strings_tracker->value,
					   sizeof(char) * strlen(list_of_strings_tracker->value));

				// untill have last element assume each new node has at least
				// make new node
				TrieNode* new_node = initTrieNodeWithNeighborCount(1);

				trie_node_squence_tracker->neighbors[0] = new_node;
				trie_node_squence_tracker->neighbors_count = 1;
				//printf("size %i\n", trie_node_squence_tracker->size);
				// set tracker to new node
				trie_node_squence_tracker = trie_node_squence_tracker->neighbors[0];
				list_of_strings_tracker = list_of_strings_tracker->next;
				j++;
				if(j == list_of_lists_tracker->count)
				{
					free(new_node->neighbors);
					new_node->neighbors = NULL;

				}


			}


			list_of_lists_tracker = list_of_lists_tracker->next;

			root2->neighbors[i] = trie_node_sequence;
			root2->neighbors_count++;

			if(list_of_lists_tracker != NULL)
			{
				i++;

			}
			else
			{

				break;
			}



		}
		return root2;	
	}
	return NULL;
}



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

ContextState* makeFullContextState(
	TrieNode* name,
	TrieNode* nexts,
	TrieNode* start_children,
	TrieNode* children,
	char* function_name,
	Data* variable_from_json_dict,
	TrieNode* parents)
{
	// name, nexts, start_children, children, parents are all dummy nodes

	int sizeof_trie_node = sizeof(TrieNode);

	int sizeof_context_state = sizeof(ContextState);

	int sizeof_data = sizeof(Data);

	int sizeof_function_name = sizeof(char) * (strlen(function_name) + 1);
	ContextState* node 			= malloc(sizeof_context_state);
	node->state_name 			= malloc(sizeof_trie_node);
	node->nexts_ 				= NULL;
	node->start_children 		= NULL;
	node->children_ 			= NULL;
	node->parents_ 				= NULL;
	
	node->function_pointer_name = NULL;
	
	node->var_data 				= NULL;


	// only need to copy over the pointers inside NeighborNames

	if(name != NULL)
	{

		memcpy(node->state_name,
			   name,
			   sizeof_trie_node);
	}

	if(nexts != NULL)
	{
		node->nexts_ = malloc(sizeof_trie_node);
		memcpy(node->nexts_,
			   nexts,
			   sizeof_trie_node);
	}

	if(start_children != NULL)
	{
		//printf("added start children\n");
		node->start_children = malloc(sizeof_trie_node);

		memcpy(node->start_children,
			   start_children,
			   sizeof_trie_node);
	}
	

	if(children != NULL)
	{
		//printf("added children\n");
		node->children_ = malloc(sizeof_trie_node);

		memcpy(node->children_,
			   children,
			   sizeof_trie_node);
	}
	if(parents != NULL)
	{
		//printf("added parents\n");
		node->parents_ = malloc(sizeof_trie_node);

		memcpy(node->parents_,
			   parents,
			   sizeof_trie_node);
	}
	if(function_name != NULL)
	{
		node->function_pointer_name = malloc(sizeof_function_name);

		memcpy(node->function_pointer_name,
			   function_name,
			   sizeof(char) * (strlen(function_name) + 1));
		
	}
	if(variable_from_json_dict != NULL)
	{
		node->var_data = malloc(sizeof_data);
		memcpy(node->var_data,
			   variable_from_json_dict,
			   sizeof_data);
	}
	return node;

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