#include "state.h"
#include "jsmn/jsmn.h"

char* makeSpaces(int indent_level);

const char* getInput(Tokens* my_tokens);
int getI(Tokens* my_tokens);

enum data_types{is_list, is_string, is_empty_case};
enum token_types {_primitive, _object, _array, _string};

/*
typedef struct LispNode
{
	void* value;
	struct LispNode* next;

	int count_of_value_items;
	bool value_type;
}*/




void printData(Data* var_data)
{
	if(var_data != NULL)
	{
		switch(var_data->type_id)
		{
			case 0:
			{

				printf("%i\n", var_data->_int);
				break;
			}
			case 1:
			{
				printf("%s\n", var_data->_string);

				break;
			}
			case 2:
			{

				printf("%f\n", var_data->_float);

				break;
			}

		}
		printf("\n");
	}
	else
	{
		printf("no data\n");
	}
	
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
		//printf("%x\n", root_tracker->neighbors);
		//printf("%x\n", root_tracker->object);

		if(root_tracker->neighbors != NULL)
		{
			if(root_tracker->object != NULL)
			{
				printf("%s", makeSpaces(indent + 2));
				printContextState2(root_tracker->object);
				printf("\n");

			}
			//printf("# of neighbors %i\n", root_tracker->neighbors_count);
			//printf("size %i\n", root_tracker->size);
			for(int i = 0; i < root_tracker->size; i++)
			{
				if(root_tracker->neighbors[i] != NULL)
				{
					printTrieNodeTree(root_tracker->neighbors[i], indent + 2);

				}
			}
		}
		else
		{
			if(root_tracker->object != NULL)
			{
				printf("%s", makeSpaces(indent + 2));
				printContextState2(root_tracker->object);
				printf("\n");

			}
		}
	}
	else
	{
		printf("[]\n");
	}
}

void printContextState(ContextState* node)
{
	/*
		nexts,
		start_children,
		children,
		function_name,
		variable_from_json_dict,
		parents
	*/
	printf("state name\n");
	printTrieNodeTree(node->state_name, 0);
	printf("\n");

	printf("nexts\n");

	printTrieNodeTree(node->nexts_, 0);
	printf("\n");

	printf("start children\n");
	printTrieNodeTree(node->start_children, 0);
	printf("\n");

	printf("children\n");
	printTrieNodeTree(node->children_, 0);
	printf("\n");

	printf("function name\n");
	printf("%s\n\n", node->function_pointer_name);
	printf("\n");

	printf("data\n");
	printData(node->var_data);
	printf("\n");


	printf("parents\n");
	printTrieNodeTree(node->parents_, 0);
	printf("\n");

	printf("start_children_are_parallel\n");
	printf("%i\n", node->start_children_are_parallel);
	printf("\n");

	printf("nexts_are_parallel\n");
	printf("%i\n", node->nexts_are_parallel);
	printf("\n");
	
	printf("is_start_child\n");
	printf("%i\n", node->is_start_child);
	printf("\n");
	
	printf("is_child\n");
	printf("%i\n", node->is_child);
	printf("\n");
	
	printf("is_parent\n");
	printf("%i\n", node->is_parent);
	printf("\n");

	printf("is_start_state\n");
	printf("%i\n", node->is_start_state);
	printf("\n");

	printf("is_end_state\n");
	printf("%i\n", node->is_end_state);
	printf("\n");
	
	printf("is_data_state\n");
	printf("%i\n", node->is_data_state);
	printf("\n");



}
void printTrieNodes(TrieNode* trie_node_sequence)
{
	TrieNode* trie_node_sequence_tracker = trie_node_sequence;
	while(trie_node_sequence_tracker != NULL)
	{
		if(trie_node_sequence_tracker->word != NULL)
		{
			printf("%s\n", trie_node_sequence_tracker->word);
			

		}
		if(trie_node_sequence_tracker->neighbors != NULL)
		{
			trie_node_sequence_tracker = trie_node_sequence_tracker->neighbors[0];

		}
		else
		{
			//printf("at last node\n");
			if(trie_node_sequence_tracker->object != NULL)
			{
				printContextState(trie_node_sequence_tracker->object);
			}
			
			break;
		}

	}
	printf("\n");
}

void printTrieNodeTreeFlat(TrieNode* root)
{
	// printContextState2 calls this
	//printf("printing flat name\n");

	TrieNode* root_tracker = root;
	if(root_tracker != NULL)
	{
		//printf("\nabout to print word root_tracker->word %x, root_tracker->neighbors %x\n", root_tracker->word, root_tracker->neighbors);

		if(root_tracker->word != NULL)
		{

			printf("%s ", root_tracker->word);
		}
		//printf("neighbors count %i\n", root_tracker->neighbors_count);
		//printf("tracker size %i\n", root_tracker->size);
		//printf("neighbors %x\n", root_tracker->neighbors);

		if(root_tracker->neighbors != 0)
		{
			//printf("neighbors 2 %x\n", root_tracker->neighbors);

			// can't check it, doesn't happen all the time, the nodes are set correctly
			//if(root_tracker->neighbors_count != NULL)
			//	printf("# of neighbors %i\n", root_tracker->neighbors_count);
			//else
			//	printf("no neighbor count\n");
			//printf("size %i\n", root_tracker->size);
			//printf("# of neighbors %i, size %i\n", root_tracker->neighbors_count, root_tracker->size);
			//printf("will the loop happen\n");
			for(int i = 0; i < root_tracker->neighbors_count; i++)
			{
				//printf("%i problem? %i\n", i, root_tracker->size);
				if(root_tracker->neighbors[i] != NULL)
				{
					printTrieNodeTreeFlat(root_tracker->neighbors[i]);

				}
			}
		}
	}
	else
	{
		printf("[]\n");
	}
}

void printContextState2(ContextState* node)
{

	if(node != NULL)
	{
		if(node->state_name != NULL)
		{

			printf("-> ");
			printTrieNodeTreeFlat(node->state_name->neighbors[0]);

		}

	}
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
ContextState* makeFullContextState2(
	TrieNode* name,
	TrieNode* nexts,
	TrieNode* start_children,
	TrieNode* children,
	char* function_name,
	Data* variable_from_json_dict,
	TrieNode* parents,
	bool (*function_pointer)(struct ContextState* state),
	bool start_children_are_parallel,
	bool nexts_are_parallel,
	bool is_start_child,
	bool is_child,
	bool is_parent,
	bool is_start_state,
	bool is_end_state,
	bool is_data_state)
{
	// printf("got here\n");

	ContextState* state = makeFullContextState(
	name,
	nexts,
	start_children,
	children,
	function_name,
	variable_from_json_dict,
	parents,
	start_children_are_parallel,
	nexts_are_parallel,
	is_start_child,
	is_child,
	is_parent,
	is_start_state,
	is_end_state,
	is_data_state);
	state->function_pointer = function_pointer;
	return state;

}
ContextState* makeFullContextState(
	TrieNode* name,
	TrieNode* nexts,
	TrieNode* start_children,
	TrieNode* children,
	char* function_name,
	Data* variable_from_json_dict,
	TrieNode* parents,
	bool start_children_are_parallel,
	bool nexts_are_parallel,
	bool is_start_child,
	bool is_child,
	bool is_parent,
	bool is_start_state,
	bool is_end_state,
	bool is_data_state)
{
	// name, nexts, start_children, children, parents are all dummy nodes
	//printf("got here\n");

	int sizeof_trie_node = sizeof(TrieNode);

	int sizeof_context_state = sizeof(ContextState);

	int sizeof_data = sizeof(Data);
	//printf("got here\n");

	int sizeof_function_name = 0;
	if(function_name != NULL)
	{
		sizeof_function_name = sizeof(char) * (strlen(function_name) + 1);

	}
	ContextState* node 			= malloc(sizeof_context_state);
	//printf("got here\n");

	if(name == NULL &&
		nexts == NULL &&
		start_children == NULL &&
		children == NULL &&
		function_name == NULL &&
		variable_from_json_dict == NULL &&
		parents == NULL)
	{
		//printf("all null\n");
		return node;
	}
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

	
	node->start_children_are_parallel = start_children_are_parallel;
	node->nexts_are_parallel = nexts_are_parallel;
	node->is_start_child = is_start_child;
	node->is_child = is_child;
	node->is_parent = is_parent;
	node->is_start_state = is_start_state;
	node->is_end_state = is_end_state;
	node->is_data_state = is_data_state;
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
void printTree(ContextState* root, int indent_level)
{
	//printf("here %x\n", root);
	// is not root equal to NULL?
	//printf("%i\n", indent_level);

	// if root is non existent, then we compare it's opposite to NULL
	if(root == NULL)
	{
		//printf("null node\n");
		return;
	}
	else
	{
		if(root->name != NULL)
		{

			if(indent_level > 0)
			{
				char* indents = makeSpaces(indent_level);
				if(indents != NULL)
				{
					printf("%s%i %s\n\n", indents, indent_level, root->name);

				}

				free(indents);

			}
			else
			{
						//printf("here\n");

				printf("%s\n\n", root->name);

			}
		}
		else
		{
			printf("no name\n\n");
		}
		//printf("screwed\n");
		for(int i = 0; i < root->children_size; i++)
		{
			//printf("%i\n", i);
			//printf("%x\n", root->children[i]);
			//if()
			printTree(root->children[i], indent_level + 1);
		}

	}
	return;
}



// pointer to string saved as a name
void doubleLink(ContextState* parent, ContextState* child)
{
	child = appendParent(child, parent);
	//printf("child saved 1.2 %s\n", child->name);

	parent = appendChild(parent, child);
	//printf("child saved 1.3 %s\n", child->name);


}
// segfaulted after this was moved
ContextState* makeTree(char* input)
{
	// needs the input to end on a newline after the last collectable text
	// there can't be any lines with only indents
	//printf("makeTree\n");

	int current_indent = 0;
	int next_indent = 0;
	int i = 0;
	int num_lines = countLines(input);
	//printf("here\n");
	ContextState* dummy_dummy_root = initContextState();
	dummy_dummy_root = setName(dummy_dummy_root, "\"dummy_dummy_root\"");


	ContextState* dummy_root = initContextState();

	dummy_root = setName(dummy_dummy_root, "\"dummy_root\"");



	ContextState* root = initContextState();

	root = setName(root, "\"root\"");


	ContextState* parent = root;

	ContextState* child;

	doubleLink(dummy_dummy_root, dummy_root);

	doubleLink(dummy_root, parent);

	char* word = getNextWord(input, i);

	parent = setName(parent, word);

	i += strlen(word) + 1;

	next_indent = countTabs(input, i);
	i += next_indent;
	free(word);

	// assuming there will be 1 state and 1 child
	if(next_indent > current_indent)
	{
		word = getNextWord(input, i);
		child = initContextState();
		child = setName(child, word);

		doubleLink(parent, child);

		i += strlen(word) + 1;

		next_indent = countTabs(input, i);

		i += next_indent;


		swap(&current_indent, &next_indent);

		free(word);

	}
	//printf("got here\n");

	// input[i] should be first char of 3rd word
	int count = 0;
	while(count < num_lines)
	{
		//printf("count %i, num_lines %i, i %i, input len %lu\n", count+1, num_lines, i, strlen(input));

		char* word = getNextWord(input, i);

		ContextState* new_node = initContextState();
		if(new_node == NULL) exit(1);

		new_node = setName(new_node, word);


		free(word);

		i += strlen(new_node->name) + 1;

		next_indent = countTabs(input, i);
		

		if(next_indent > current_indent)
		{
			// GOING DOWN

			doubleLink(child, new_node);


			parent = child;

			child = new_node;

		}
		else if(next_indent < current_indent)
		{
			// CLIMB UP
			doubleLink(child, new_node);
			if(next_indent <= 0)
			{
				return root;
			}
			int target_indent = current_indent;
			while(target_indent > next_indent)
			{

				// have parent go up 1 parent
				parent = parent->parents[parent->parents_size - 1]; // last path visited
				child = child->parents[child->parents_size - 1];

				// target_indent--
				target_indent--;
			}

		}
		else // next_indent == current_indent
		{
			//  GOING ACROSS
			doubleLink(child, new_node);
			



		}
		i += next_indent;
		swap(&current_indent, &next_indent);

		//printf("tree -------------------------\n");
		//printTree(root, 0);
		//printf("-------------------------\n");



		count++;
	}
	//printf("done with file tree -------------------------\n");
	//printTree(root, 0);
	//printf("-------------------------\n");

	return 0;
}
Data* variable(Tokens* my_tokens)
{
	if(getToken(my_tokens).type != _object) exit(1);
	//printf("%s\n", tokenType(token));
	//printf("%s\n", collectChars(token, input));
	char* token_string = collectChars(getToken(my_tokens), getInput(my_tokens));
	/*
	typedef struct Data
	{
	int type_id; // enum

	int _int;

	char* _string;
	int string_size;

	float _float;
	}Data;
	*/
	Data* variable = malloc(sizeof(Data));

	if(strcmp(token_string, "\"{}\"") == 0)
	{

		//*i += 1;
		advanceToken(my_tokens);
		variable = NULL;
	}
	else
	{

		//*i += 1;
		advanceToken(my_tokens);
		//token = tokens[*i];
		char* type_name = collectChars(getToken(my_tokens), getInput(my_tokens));


		//*i += 1;
		//token = tokens[*i];
		advanceToken(my_tokens);
		char* data = collectChars(getToken(my_tokens), getInput(my_tokens));

		//*i += 1;
		advanceToken(my_tokens);
		if(strcmp(data, "\"NULL\"") == 0)
		{
			variable = NULL;
		}
		else
		{
			if(strcmp(type_name, "\"int\"") == 0)
			{
				int integer;
				// skip over the '\"'
				sscanf(data + 1, "%i", &integer);
				variable->_int = integer;

				variable->type_id = 0;
			}
			else if(strcmp(type_name, "\"char*\"") == 0)
			{
				if(strcmp(data, "\"\"") == 0)
				{
					variable = NULL;
				}
				else
				{
					int sizeof_string = sizeof(char) * (strlen(data) + 1);
					variable->_string = malloc(sizeof_string);
					memcpy(variable->_string, data, sizeof_string);
					variable->string_size = strlen(data);
					variable->type_id = 1;

				}
			}
			else if(strcmp(type_name, "\"float\"") == 0)
			{
				float float_value;

				// skip over the '\"'
				sscanf(data + 1, "%f", &float_value);
				variable->_float = float_value;
				variable->type_id = 2;

			}
		}
		
	}
	return variable;

}
bool getBinaryValue(char* json_value)
{
	if(strcmp(json_value, "0"))
	{
		return 0;
	}
	else if(strcmp(json_value, "1"))
	{
		return 1;
	}
	else
	{
		printf("not a valid binary value\n");
		exit(1);
	}
}
ContextState* makeContextState(/*int* i, jsmntok_t tokens[], const char* input*/Tokens* my_tokens, int token_count)
{
	//printf("object to run |%s|\n", collectChars(tokens[*i], input));
	//TrieTree* name_context_state = makeDict();
	//jsmntok_t token = tokens[*i];
	//printf("%s\n", tokenType(getToken(my_tokens).type));
	//printf("object to run\n");
	//printf("%s\n", collectChars(getToken(my_tokens), getInput(my_tokens)));

	if(getToken(my_tokens).type != _object) exit(1);
	//printf("%s\n", collectChars(getToken(my_tokens), getInput(my_tokens)));

	//*i += 1;
	//token = tokens[*i];
	advanceToken(my_tokens);
	//printf("%s\n", tokenType(token));
	if(getToken(my_tokens).type != _string) exit(1);
	//*i += 1;
	//token = tokens[*i];
	advanceToken(my_tokens);
	//printf("%s\n", tokenType(getToken(my_tokens)));
	//printf("name\n");
	//printf("%s\n", collectChars(getToken(my_tokens), getInput(my_tokens)));

	//TrieNode* makeTrieTree(int i, jsmntok_t tokens[], const char* input)
	//printf("%i\n", getI(my_tokens));
	TrieNode* name = makeTrieTree(my_tokens);//arrayOfArrays(i, tokens, input, token_count);
	//printTrieNodeTreeFlat(name);
	//	printf("%i\n", getI(my_tokens));
	//printf("%s\n", collectChars(getToken(my_tokens), getInput(my_tokens)));

	/*
	printf("printing trie tree\n");
	printTrieNodeTree(name, 0);
	printf("\n\n");
	*/
	/*
	typedef struct NeighborNames
		{
			char** list_of_names;
			int number_of_names;
			int* start_names;
			int number_of_start_names;
		}NeighborNames;
	*/
	//printListOfListsOfStrings(name);
	
	
	
	//printf("got here\n");

	// tokens[i] == "nexts"
	//token = tokens[*i];

	//printf("%s\n", collectChars(token, input));
	//printf("%s\n", tokenType(token));

	//printf("%s\n", collectChars(token, input));

	// at keyword now
	//*i += 1;
	advanceToken(my_tokens);
	//token = tokens[*i];
	//printf("%s\n", collectChars(token, input));

	//printf("%s\n", tokenType(token));
	//printf("nexts\n");
	TrieNode* nexts = makeTrieTree(my_tokens);//arrayOfArrays(i, tokens, input, token_count);
	/*
	printf("printing trie tree\n");
	printTrieNodeTree(nexts, 0);
	printf("\n\n");
	*/
	//printListOfListsOfStrings(nexts);
	//token = tokens[*i];

	//printf("%s\n", collectChars(token, input));
	//printf("%s\n", collectChars(token, input));
	//printf("%s\n", collectChars(getToken(my_tokens), getInput(my_tokens)));

	// at keyword now
	advanceToken(my_tokens);
	//*i += 1;
	//token = tokens[*i];
	//printf("%s\n", tokenType(token));
	//printf("start children\n");
	TrieNode* start_children = makeTrieTree(my_tokens);//arrayOfArrays(i, tokens, input, token_count);
	/*
	printf("printing trie tree\n");
	printTrieNodeTree(start_children, 0);
	printf("\n\n");
	*/
	//printListOfListsOfStrings(start_children);

	//token = tokens[*i];

	//printf("%s\n", collectChars(token, input));
	//printf("%s\n", collectChars(token, input));
	//printf("%s\n", collectChars(getToken(my_tokens), getInput(my_tokens)));

	// at keyword now
	advanceToken(my_tokens);
	//*i += 1;
	//token = tokens[*i];
	//printf("%s\n", tokenType(token));
	//printf("children\n");
	TrieNode* children = makeTrieTree(my_tokens);//arrayOfArrays(i, tokens, input, token_count);
	/*
	printf("printing trie tree\n");
	printTrieNodeTree(children, 0);
	printf("\n\n");
	*/
	//printListOfListsOfStrings(children);
	//token = tokens[*i];
	//printf("%s\n", tokenType(token));
	//printf("%s\n", collectChars(token, input));

	//printf("%s\n", collectChars(getToken(my_tokens), getInput(my_tokens)));
	advanceToken(my_tokens);
	//*i += 1;
	//token = tokens[*i];
	//printf("%s\n", tokenType(token));
	char* function_name = collectChars(getToken(my_tokens), getInput(my_tokens));
	// n time for this
	// add to a trienode
	// insert into a functions trie	
	//printf("function name %s\n", function_name);
	advanceToken(my_tokens);

	//printf("%s\n", collectChars(getToken(my_tokens), getInput(my_tokens)));
	advanceToken(my_tokens);

	//*i += 1;
	//token = tokens[*i];
	//printf("%s\n", tokenType(token));
	//printf("%s\n", collectChars(token, input));

	//*i += 1;
	//token = tokens[*i];
	Data* variable_from_json_dict = variable(my_tokens);
	//printf("variable\n");
	//printData(variable_from_json_dict);
	//token = tokens[*i];
	//printf("%s\n", collectChars(token, input));

	//printf("%s\n", collectChars(getToken(my_tokens), getInput(my_tokens)));
	advanceToken(my_tokens);

	//*i += 1;
	//token = tokens[*i];
	//printf("before arrayOfArrays %s\n", tokenType(token));

	TrieNode* parents = makeTrieTree(my_tokens);//arrayOfArrays(i, tokens, input, token_count);
	//printListOfListsOfStrings(parents);
	//*i += 1;

	//printf("%s\n", collectChars(getToken(my_tokens), getInput(my_tokens)));
	advanceToken(my_tokens);
	//printf("%s\n", collectChars(tokens[*i], input));
	bool start_children_are_parallel = getBinaryValue(collectChars(getToken(my_tokens), getInput(my_tokens)));
	//printf("%i\n", start_children_are_parallel);
	advanceToken(my_tokens);



	//*i += 1;

	//printf("%s\n", collectChars(getToken(my_tokens), getInput(my_tokens)));
	advanceToken(my_tokens);

	//printf("%s\n", collectChars(getToken(my_tokens), getInput(my_tokens)));

	bool nexts_are_parallel = getBinaryValue(collectChars(getToken(my_tokens), getInput(my_tokens)));
	advanceToken(my_tokens);
	//printf("%i\n", nexts_are_parallel);



	//	*i += 1;


	//printf("%s\n", collectChars(getToken(my_tokens), getInput(my_tokens)));
	advanceToken(my_tokens);

	bool is_start_child = getBinaryValue(collectChars(getToken(my_tokens), getInput(my_tokens)));
	//printf("%i\n", is_start_child);
	advanceToken(my_tokens);

	//	*i += 1;

	//printf("%s\n", collectChars(getToken(my_tokens), getInput(my_tokens)));
	advanceToken(my_tokens);
	bool is_child = getBinaryValue(collectChars(getToken(my_tokens), getInput(my_tokens)));
	//printf("%i\n", is_child);
	advanceToken(my_tokens);

	//	*i += 1;



	//printf("%s\n", collectChars(getToken(my_tokens), getInput(my_tokens)));
	advanceToken(my_tokens);
	bool is_parent = getBinaryValue(collectChars(getToken(my_tokens), getInput(my_tokens)));
	//printf("%i\n", is_parent);
	advanceToken(my_tokens);


	//	*i += 1;
	//printf("%s\n", collectChars(getToken(my_tokens), getInput(my_tokens)));
	advanceToken(my_tokens);

	bool is_start_state = getBinaryValue(collectChars(getToken(my_tokens), getInput(my_tokens)));
	//printf("%i\n", is_start_state);
	advanceToken(my_tokens);
	//	*i += 1;



	//printf("%s\n", collectChars(getToken(my_tokens), getInput(my_tokens)));
	advanceToken(my_tokens);

	bool is_end_state = getBinaryValue(collectChars(getToken(my_tokens), getInput(my_tokens)));
	//printf("%i\n", is_end_state);
	advanceToken(my_tokens);
	//	*i += 1;


	//printf("%s\n", collectChars(getToken(my_tokens), getInput(my_tokens)));
	advanceToken(my_tokens);


	bool is_data_state = getBinaryValue(collectChars(getToken(my_tokens), getInput(my_tokens)));

	//printf("%i\n", is_data_state);
	advanceToken(my_tokens);
	//printf("\n\n\n\n");
	//exit(1);
	/*
	printf("printing trie tree\n");
	printTrieNodeTree(parents, 0);
	printf("\n\n");
	*/
		/*
	{
	    "name":           ["start"],
	    "nexts":          [],
	    "start_children": [["("]],
	    "children":       [["test_data"],
	                       ["letters_and_digits"],
	                       [")"]],
	    "function_name":  "returnTrue",
	    "data":           {"nothing": "null"},
	    "parents":        [["NONE"]],
	    "start_children_are_parallel" : 0,
	    "nexts_are_parallel" : 0,
	    "is_start_child" : 0,
	    "is_child" : 0,
	    "is_parent" : 1,
	    "is_start_state" : 0,
	    "is_end_state" : 0,
	    "is_data_state" : 0
	  }
  */
	  // also should add the actual functions to the state
	  // f(state, parent)
	
	ContextState* current_state = makeFullContextState(
		name,
		nexts,
		start_children,
		children,
		function_name,
		variable_from_json_dict,
		parents,
		start_children_are_parallel,
		nexts_are_parallel,
		is_start_child,
		is_child,
		is_parent,
		is_start_state,
		is_end_state,
		is_data_state);
	
	//printf("printing state\n\n");
	//printContextState(current_state);
	// now we are at the next object
	//printf("next\n");
	//exit(1);

	// may be out of tokens
	/*
	if(*i < token_count)
	{
		token = tokens[*i];
		//printf("done\n");
		return current_state;
	}*/
	return current_state;
	
}
