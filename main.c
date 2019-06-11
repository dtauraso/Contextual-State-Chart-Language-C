#include "state3.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
//https://zserge.com/jsmn.html
#include "jsmn/jsmn.h"
#include "hash_table1.h"



char* getNextWord(char* input, int i)
{
 	// this function gets the next word
	int j = 0;
	int count = 0;
	if(i >= strlen(input))
	{
		return NULL;
	}
	while(input[i + j] != '\n')
	{
		//printf("%c ", input[i + j]);

		j++;
		count++;
	}
	//printf("character count %i\n", count);
	char* word = malloc(sizeof(char) * j );
	//printf("%i\n", j);
	memcpy(word, input + i, j);
	word[j] = '\0';
	//printf("%s\n", word);
	//printf("chars in word %lu\n", strlen(word));
	/*
	collect the word
	return word
	*/
	return word;
}
char* surroundByQuotes(char* word_from_input)
{
	int size = strlen(word_from_input);
	int new_size = size + 2;
	char* word_surrounded_by_quotes = malloc(sizeof(char) * new_size);

	word_surrounded_by_quotes[0] = '\"';
	memcpy(word_surrounded_by_quotes + 1, word_from_input, sizeof(char) * size);
	word_surrounded_by_quotes[new_size - 1] = '\"';
	word_surrounded_by_quotes[new_size] = '\0';
	return word_surrounded_by_quotes;
}
int countTabs(char* input, int i)
{
	int k = 0;
	//printf("|%x|\n", input[i+k]);
	// this 't' is actually invisable from Atom when used as a tab character
	while(input[i + k] == '\t')
		k++;
	return k;
}
char* makeSpaces(int indent_level)
{
	if(indent_level == 0)
	{
		return NULL;
	}
	char* indents;
	indents = malloc(indent_level + 1);
	memset(indents, ' ', sizeof(char) * indent_level);
	indents[indent_level] = '\0';
	//printf("|%s|\n", indents);


	
	return indents;


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
void swap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = *a;
}
void printHash(ht_hash_table* ht);

void appendLink(ht_hash_table* states,
			    const char* node,
				const char* other_node, // child node or parent node
				int attribute);

// pointer to string saved as a name
void doubleLink(ContextState* parent, ContextState* child)
{
	child = appendParent(child, parent);
	//printf("child saved 1.2 %s\n", child->name);

	parent = appendChild(parent, child);
	//printf("child saved 1.3 %s\n", child->name);


}
/*
void doubleLinkHash(ht_hash_table* input_states, const char* parent, const char* child)
{
	//printf("%s <=> %s\n", parent, child);
	//printHash(input_states);

	//input_states = appendParentLink(input_states, child, parent);
	appendLink(input_states, child, parent, 1); // 1 == parents

	//printf("here\n");

	appendLink(input_states, parent, child, 0); // 0 == children
	//printf("here 2\n");

}*/
int countLines(char* input)
{
	int num_lines = 0;
	unsigned input_size = strlen(input);
	for(int i = 0; i < input_size; i++)
	{
		if(input[i] == '\n')
			num_lines++;
	}
	return num_lines;
}



void printState(ContextState* node);

// 2 hash tables
// each input name + object name -> object holding the name
// parse tree each name part -> waypoint object or object holding data

// 1 tri tree for the name part chain to the object holding data, so auto-enumerating
// new states is simple


ContextState* makeTree(char* input)
{
	// needs the input to end on a newline after the last collectable text
	// there can't be any lines with only indents

	int current_indent = 0;
	int next_indent = 0;
	int i = 0;
	int num_lines = countLines(input);

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
char* readFile(char* file_name)
{
	FILE* file = fopen(file_name, "r");
	char* string;
	size_t n = 0;
	int c;

	if(file == NULL)
	   return NULL; // file can't be opened
   fseek(file, 0, SEEK_END);
   long f_size = ftell(file);
   fseek(file, 0, SEEK_SET);
   string = malloc(f_size);

   while((c = fgetc(file)) != EOF)
   {
	   string[n++] = (char) c;
   }
   string[n] = '\0';
   return string;
}
char* collectChars(jsmntok_t token, const char* input)
{
	int size = token.end - token.start;
	char* json_part = malloc(sizeof(char) * size);

	memcpy(json_part, input + token.start, sizeof(char) * size);
	json_part[size] = '\0';

	return surroundByQuotes(json_part);
;

}
/*
typedef struct TrieNode
{
	// letters of the entire state name
	char letter;
	struct TrieNode* neighbors;
	struct ContextState* object;
}TrieNodee;

name:
string
|name|
array
|["states", "state"]|
string
|states|
string
|state|
array string string


next:
string
|nexts|
array
|[]|
array([])

start children:
string
|start_children|
array
|[["names", "0"]]|
array
|["names", "0"]|
string
|names|
string
|0|

array array string string

array array string string ... array string ...

first array
	[]
	done
1, nth array
	strings
	if string == children
		done
if first array
	if next token == []
		done
while(true)
	if next token == string
		has string
		if token.strings != keyword
			collect
		else
			done

children:
string
|children|
array
|[]|

function name:
string
|function_name|
string
|returnTrue|

data:
string
|data|
object
|{"nothing": "null"}|
string
|nothing|
string
|null|

parents:
string
|parents|
array
|[["root", "0"]]|
array
|["root", "0"]|
string
|root|
string
|0|

insert the link names into the trie
the leaf nodes will link to the ContextState object

object is the ContextState
first array token will be ignored
array -> []
array -> array (not [])
array -> string string ... untill string == key_name

sub object is inside a ContextState
sub object -> {}
sub object -> string string pairs ... untill string == key_name

makeContextState
	read the tokens in the object and make the context state from them
	add each object to a hash table

*/
// user can't use "\n" in the state name
// make a string of entire name[name1\nname2/\n...] -> contextState map
// then partal name -> contextState (each internal node in the trie is a dummy node, unless a state name is a partial path)
enum token_types {_primitive, _object, _array, _string};
char* tokenType(jsmntok_t token)
{
	switch(token.type)
	{
		case _primitive:
			return "primitive";
		case _object:
			return "object";
		case _array:
			return "array";
		case _string:
			return "string";
	}
}
bool tokenIsKeyWord(char* token_string)
{
	return ((strcmp(token_string, "function_name") == 0)  	||
		    (strcmp(token_string, "start_children") == 0) 	||
		    (strcmp(token_string, "children") == 0)		  	||
		    (strcmp(token_string, "nexts") == 0)			||
  		    (strcmp(token_string, "name") == 0)			 	||
    	    (strcmp(token_string, "parents") == 0)		 	||
      	    (strcmp(token_string, "data") == 0));
}
LispNode* makeLispNode();
LispNode* setValueToList(LispNode* list_a, LispNode* list_b);
LispNode* setValueToString(LispNode* list, char* word);
LispNode* appendList(LispNode* root, LispNode* list_a, LispNode* list_b);
enum data_types{is_list, is_string, is_empty_case};
LispNode* cons(void* data, void* link, int data_type, int count, int call_count);
void printLispNodes(LispNode* root, int indent_level);

// for reading the token sequence the json parsing api provides

//////////////
LispNode* strings(int* i, jsmntok_t tokens[], const char* input, int number_of_strings_left, int call_count)
{
	jsmntok_t current_token = tokens[*i];
	char* current_string = collectChars(current_token, input);
	printf("current string %s\n", current_string);
	printf("items remaining %i\n", number_of_strings_left);
	if(number_of_strings_left == 1)
	{
		printf("type %s\n", tokenType(current_token));
		//printf("last case keword\n");
		*i += 1;
		return cons(current_string, NULL, is_string, 0, call_count);
	}
	
	else //if(current_token.type == _string)
	{
		//printf("got here 2\n %s\n", current_string);

		*i += 1;
		LispNode* n = strings(i, tokens, input, number_of_strings_left - 1, call_count + 1);
		//printf("total count %i\n", n->call_count);
		LispNode* x = cons(current_string,
						   n,
						   is_string,
						   0,
						   n->call_count);
		// how many more items from this one?
		//printLispNodes(x, 1);
		return x;
	}
	
}
// record # of total calls
LispNode* array(int* i, jsmntok_t tokens[], const char* input, int call_count, int token_count)
{


	// count # of calls to obtain a total # of strings in adition to counting how many strings in each list
	// return a lisp style linked list holding the strings collected

	jsmntok_t current_token = tokens[*i];
	if(current_token.type != _array)  	// error
	{
		//printf("we have a problem\n");
		return cons(NULL, NULL, is_empty_case, 0, call_count);
	}
	printf("number of nested items %i\n", current_token.size);
	// null array
	if(strcmp(collectChars(current_token, input), "\"[]\"") == 0)
	{
		// done with all inner arrays and outer arrays
		printf("null array\n");
		return cons(NULL, NULL, is_empty_case, 0, call_count);
	}
	
	*i += 1;
	int items_in_array = current_token.size;
	current_token = tokens[*i];
	printf("second time\n");
	if(current_token.type != _string)
	{
		//printf("we have a problem\n");
		return cons(NULL, NULL, is_empty_case, 0, call_count);
	}
	LispNode* string_coll = strings(i, tokens, input, items_in_array, call_count + 1);
	printf("collected the strings\n");
	if(*i == token_count)
	{
		return cons(string_coll, NULL, is_list, items_in_array, string_coll->call_count);
	}
	//string_coll->count = items_in_array;
	// token is o keyword or array
	printf("i %i\n", *i);
	//printf("%i, %i\n", *i, max_tokens);
	//if(*i >= max_tokens)
	//	return cons(string_coll, NULL, is_list);
	current_token = tokens[*i];
	printf("array or keyword %s\n", tokenType(current_token));

	if(tokenIsKeyWord(collectChars(current_token, input)))  // end of outer array, still in object
	{

		printf("at keyword\n");
		//printf("%s %s\n", tokenType(current_token), collectChars(current_token, input));
		// setting the number of items in string_coll would not be meaningfull
		return cons(string_coll, NULL, is_list, items_in_array, string_coll->call_count);
	}
	else if(current_token.type == _array)  // end of inner array, still in object
	{
		printf("items in array %i\n", items_in_array);
		LispNode* x = array(i, tokens, input, string_coll->call_count, token_count);
		return cons(string_coll, x, is_list, items_in_array, x->call_count);
	}
	else  // end of object
	{
		printf("items in array 2 %i\n", items_in_array);
		// setting the number of items in string_coll would not be meaningfull
		return cons(string_coll, NULL, is_list, items_in_array, string_coll->call_count);
	}

	//printf("got here object\n");

}
TrieNode* convertLispChainToTrieNodeChain(LispNode* root);
void deleteLispNodes(LispNode* root);

// each function consuming tokens advance the index
// to the token for the next function
TrieNode* arrayOfArrays(int* i,
				   jsmntok_t tokens[],
				   const char* input,
				   int token_count)
{
	// returns a TrieNode* type
	// the word and object attributes will be set to null
	/*
		typedef struct StringNode
		{
			char* word;
			struct StringNode* next;
		}StringNode;

		typedef struct TrieNode
		{

			char* word;
			struct TrieNode** neighbors;
			int neighbors_count;

			struct ContextState* object;
		}TrieNode;

	*/



	// the array token is also [] or [stuff]
	// current token is at an array
	// automaticall sets i to the next token
	jsmntok_t token = tokens[*i];
	if(token.type != _array) exit(1);
	//*i += 1;
	//token = tokens[*i];
	LispNode* root = makeLispNode();
	char* token_string = collectChars(token, input);
	printf("%s\n", token_string);
	if(strcmp(token_string, "\"[]\"") == 0)
	{
		//printf("empty array\n");
		*i += 1;
		// return list;

		return NULL;

	}
	else
	{
		// current token is at first array in the sequence:
		// array array strings array strings
		// array strings not_array
		//printf("%s\n", tokenType(tokens[ ( *i ) ]));
		//printf("number of nested items %i\n", tokens[ ( *i ) ].size);
		int items_in_array = tokens[ ( *i ) ].size;
		// for the top level, we want to record a size of 1 for the container of n lists
		int items_in_high_level = 1;
		if(tokens[ *i ].type 		 == _array &&
		   tokens[ ( *i ) + 1 ].type == _array)
		{
			*i += 1;
			items_in_high_level = items_in_array;
		}
		//printf("items in outer array %i\n", items_in_array);
		//printf("%s\n", tokenType(tokens[ ( *i ) ]));
		// inner cons for the array of lists count
		// outer cons to tell the difference from a list of lists of strings and a list of strings
		printf("about to convert to a lisp node chain\n");
		LispNode* x = array(i, tokens, input, 0, token_count);
		root = cons(cons(x, NULL, is_list, items_in_array, x->call_count), NULL, is_list, items_in_high_level, x->call_count);
		//root->count = items_in_array;
		printf("items at top level %i\n", root->count);

		 TrieNode* trie_tree_of_names = convertLispChainToTrieNodeChain(root);
		printTrieNodeTreeFlat(trie_tree_of_names);

		 deleteLispNodes(root);

		//printLispNodes(root->value, 1);

		printf("\nreturning trie_tree_of_names\n");
		return trie_tree_of_names;

		

	}
}
// count backwards from current sequence
// 0th items, 0
// n-(n - 1)1th item, 0
// n-(n-2)th item, 1
// n-(n-3)th item, 2
// ...
// nth item, |delimiter_indicies|
// call stack evaluation order
// f(name3, (NULL, [0, 0])) => (name3, [0, 0])
// f(name2, (name3, [0, 0])) => (name2_name3, [5, 0])
// f(name1, (name2_name3, [5, 0])) => (name1_name2_name3, [5, 11])
/*
ith_call counts down
ith_call_revers counts up
f(nth_name, f_name_delimiter_loc, ith_call, ith_call_reverse)
	if(f_name_delimiter_loc.f_name == NULL)
		return (nth_name, delimiter_loc.set(zeros, size = ith_call_reverse - 1))
	else
		new_name = concat(nth_name, "_", f_name_delimiter_loc.f_name)
		if(ith_call <= 1)  second to last and last calls
			index = 0
		else
			index = ith_call - 1
		f_name_delimiter_loc[index] = |nth_name| + 1
		return(new_name, f_name_delimiter_loc))
*/
Data* variable(int* i, jsmntok_t tokens[], const char* input)
{
	jsmntok_t token = tokens[*i];
	if(token.type != _object) exit(1);
	//printf("%s\n", tokenType(token));
	//printf("%s\n", collectChars(token, input));
	char* token_string = collectChars(token, input);
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

		*i += 1;
		variable = NULL;
	}
	else
	{

		*i += 1;
		token = tokens[*i];
		char* type_name = collectChars(token, input);


		*i += 1;
		token = tokens[*i];
		char* data = collectChars(token, input);

		*i += 1;
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
//////////
/*
void printListOfListsOfStrings(NeighborNames* names)
{
	if(names != NULL)
	{
		if(names->number_of_names > 0)
		{
			printf("printing lists\n");
			for(int i = 0, j = 0; i < names->number_of_names; i++)
			{
				if(i == 0 && j == 0)
				{
					printf("start of list\n");
				}

				//printf("%i, %i\n", i, j);
				if(i != 0)
				{
					if(i == names->start_names[j + 1])
					{
						j++;
						printf("\nstart of list\n");

					}
				}
				printf("%s\n", names->list_of_names[i]);

			}
			printf("\n\n");
		}
		else
		{
			printf("empty list\n\n");
		}
	}
	else
	{
		printf("empty list\n");
		printf("\n\n");

	}
}
*/
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
ContextState* makeFullContextState(
	NeighborNames* name,
	NeighborNames* nexts,
	NeighborNames* start_children,
	NeighborNames* children,
	char* function_name,
	Data* variable_from_json_dict,
	NeighborNames* parents);
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

	




}

void printContextState2(ContextState* node)
{
	printTrieNodeTreeFlat(node->state_name);
}
ContextState* makeContextState(int* i, jsmntok_t tokens[], const char* input, int token_count)
{
	printf("object to run |%s|\n", collectChars(tokens[*i], input));
	//TrieTree* name_context_state = makeDict();
	jsmntok_t token = tokens[*i];
	//printf("%s\n", tokenType(token));
	if(token.type != _object) exit(1);
	*i += 1;
	token = tokens[*i];
	//printf("%s\n", tokenType(token));
	if(token.type != _string) exit(1);
	*i += 1;
	token = tokens[*i];
	//printf("%s\n", tokenType(token));
	//printf("name\n");
	TrieNode* name = arrayOfArrays(i, tokens, input, token_count);
	//printTrieNodeTreeFlat(name);
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
	token = tokens[*i];

	//printf("%s\n", collectChars(token, input));
	//printf("%s\n", tokenType(token));

	//printf("%s\n", collectChars(token, input));

	// at keyword now
	*i += 1;
	token = tokens[*i];
	//printf("%s\n", tokenType(token));
	//printf("nexts\n");
	TrieNode* nexts = arrayOfArrays(i, tokens, input, token_count);
	/*
	printf("printing trie tree\n");
	printTrieNodeTree(nexts, 0);
	printf("\n\n");
	*/
	//printListOfListsOfStrings(nexts);
	token = tokens[*i];

	//printf("%s\n", collectChars(token, input));
	//printf("%s\n", collectChars(token, input));
	// at keyword now
	*i += 1;
	token = tokens[*i];
	//printf("%s\n", tokenType(token));
	//printf("start children\n");
	TrieNode* start_children = arrayOfArrays(i, tokens, input, token_count);
	/*
	printf("printing trie tree\n");
	printTrieNodeTree(start_children, 0);
	printf("\n\n");
	*/
	//printListOfListsOfStrings(start_children);

	token = tokens[*i];

	//printf("%s\n", collectChars(token, input));
	//printf("%s\n", collectChars(token, input));
	// at keyword now
	*i += 1;
	token = tokens[*i];
	//printf("%s\n", tokenType(token));
	//printf("children\n");
	TrieNode* children = arrayOfArrays(i, tokens, input, token_count);
	/*
	printf("printing trie tree\n");
	printTrieNodeTree(children, 0);
	printf("\n\n");
	*/
	//printListOfListsOfStrings(children);
	token = tokens[*i];
	//printf("%s\n", tokenType(token));
	//printf("%s\n", collectChars(token, input));


	*i += 1;
	token = tokens[*i];
	//printf("%s\n", tokenType(token));
	char* function_name = collectChars(token, input);
	//printf("function name %s\n", collectChars(token, input));

	*i += 1;
	token = tokens[*i];
	//printf("%s\n", tokenType(token));
	//printf("%s\n", collectChars(token, input));

	*i += 1;
	token = tokens[*i];
	Data* variable_from_json_dict = variable(i, tokens, input);
	//printf("variable\n");
	//printData(variable_from_json_dict);
	token = tokens[*i];
	//printf("%s\n", collectChars(token, input));

	*i += 1;
	token = tokens[*i];
	//printf("before arrayOfArrays %s\n", tokenType(token));

	TrieNode* parents = arrayOfArrays(i, tokens, input, token_count);
	//printListOfListsOfStrings(parents);
	/*
	printf("printing trie tree\n");
	printTrieNodeTree(parents, 0);
	printf("\n\n");
	*/

	ContextState* current_state = makeFullContextState(
		name,
		nexts,
		start_children,
		children,
		function_name,
		variable_from_json_dict,
		parents);

	//printf("printing state\n\n");
	//printContextState(current_state);
	// now we are at the next object
	//printf("next\n");
	//exit(1);

	// may be out of tokens
	if(*i < token_count)
	{
		token = tokens[*i];
		//printf("done\n");
		return current_state;
	}
	return current_state;
	
	//if(token.type != _array) exit(1);
	//printf("%s\n", collectChars(token, input));
	/*
	if first array
	if next token == []
		done
	while(true)
	if next token == string
		has string
		if token.strings != keyword
			collect
		else
			done
	*/
}

/*

findInTrie(NeighborNames* name, TrieNode* node)
{
	current = next one after root
	prev = root
	if current is empty
		return prev
	else

		for i in enumerate(name)
			while current is not null

				check all children of node
					if a single string == name[i]
						advance pointers
			return prev
			

}
*/

////
// trie tree functions
char* getIthWord(NeighborNames* name, int i)
{
	// if i is in range
	if(i >= 0 && i < name->number_of_names)

		// get the ith name
		return name->list_of_names[i];
	return NULL;
}
int isMatch(char* ith_word, TrieNode* node)
{
	// finds out if ith_word is a neighbor of node
	if(ith_word != NULL && node != NULL)
	{
		//printf("isMatch\n");
		//printf("# of neighbors %i\n", node->neighbors_count);
		// returns the index on the first match
		for(int j = 0; node != NULL && j < node->neighbors_count; j++)
		{
			if(node->neighbors[j] != NULL)
			{
				if(node->neighbors[j]->word != NULL)
				{
					printf("%s == %s\n", ith_word, node->neighbors[j]->word);
					if(strcmp(ith_word, node->neighbors[j]->word) == 0)
					{
						//printf("passes\n");
						return j;
					}
				}
				else
				{
					return -1;
				}
			}
			else
			{
				return -1;
			}
		}
	}	
	return -1;
}
// TrieNodePackage
	// TrieNode* address
	// int ith_name_checked_in_search
TrieNodePackage* findInTrie(TrieNode* root, NeighborNames* name)
{
	// we are returning the node where we will start appending the words remaining
	// and the index of the first word remaining

	// if all match return -1 for 
	TrieNode* current = root;

	TrieNodePackage* package = malloc(sizeof(TrieNodePackage));
	package->address = NULL;
	package->ith_name_checked_in_search = -1;
	if(current != NULL)
	{
		//prev = root;
		//printf("root->neighbors %x\n", root->neighbors);
		if(current->neighbors == NULL)
		{
			package->address = current;
			package->ith_name_checked_in_search = -1;
			return package;

		}
		else
		{
			// at this point there has to be at least 1 node root connects to
			//TrieNode** neighbors = current->neighbors;

			//current = neighbors[0];
			// assume the name is the state name
			// the list_of_names has only 1 list of strings

			// as some point we will run out of trie nodes before we run out of names to check with

			// for each word in name
				// check the word with all edges for a match
					// if a match
						// move to the next node and restart outer loop

			// can't tell the difference between all matching and none matching
			// count # of matches
			for(int i = 0; i < name->number_of_names; i++)
			{

				// return true if item is a match
				// return false if pointer hits null (pointer should hit null if there are no matches)
				// isMatch(char* ith_word, TrieNode* current)
				// assume the ith word exists
				int ith_branch = isMatch(getIthWord(name, i), current);
				if(ith_branch != -1)
				{
					current = current->neighbors[ith_branch];
				}
				else
				{
					package->address = current;
					package->ith_name_checked_in_search = i;

					return package;
				}
				
			}
			// if count == name->number_of_names
				// return index of last item matched
			// else
				// return -1
			package->address = current;
			package->ith_name_checked_in_search = -1;

			return package;
		}
	}
	return NULL;
}
TrieNodePackage2* findInTrie2(TrieNode* root, TrieNode* sequence_of_strings)
{
	// sequence_of_strings is the address of the first word in the state name
	// sequence_of_strings attribute set
	// word has a word stored
	// neighbors has 1 neighbor
	// neighbors_count == 1
	// size == 2
	// object = null
	// we are returning the node where we will start appending the words remaining
	// and the index of the first word remaining
	/*
	how does this work?
	*/
	/*
	typedef struct TrieNodePackage2
	{
		TrieNode* address;
		bool address_is_match;

	}TrieNodePackage;
	*/
	printf("findInTrie2\n");

	/*
	typedef struct TrieNodePackage3
	{
		TrieNode* dict_trie_node;
		TrieNode* context_state_attribute_trie_node;
		bool context_state_is_found;
		bool is_first_mismatch;
		bool need_to_append_more_name;
	}TrieNodePackage3;
	*/
	TrieNodePackage3* package3 = malloc(sizeof(TrieNodePackage3));

	package3->dict_trie_node = root;
	package3->context_state_attribute_trie_node = sequence_of_strings;

	package3->context_state_is_found = NULL;
	package3->is_first_mismatch = NULL;
	package3->need_to_append_more_name = NULL;

	//TrieNode* dict_trie_node_prev = root;  // can't be null cause isMatch may return -1


	//prev = root;
	//printf("root->neighbors %x\n", root->neighbors);
	// replace this with something cleaner
	/*

	null, null case 1(assume both tree and input are null)
	loop
		

		a, b (no match stop)

		a, a(keep matching)
			null, null case 2(perfect match) enumerate this (match)
				context state doesn't exist
				else
					reutrn a found flag
			*, null(input was completely found but tree still has more nodes)(match)
				context state doesn't exist
				else
					return a found flag
			

			null, *(tree ran out of input first)


	tree, input
	a, b (no match stop)
	a, null(input was completely found)
	null, b(tree ran out of input first)
	null, null case 1(assume both tree and input are null)

	null, null case 2(perfect match)
	a, a

	any matching doesn't prove there is a context node or not
	matching and checking for a context node are separate
	*/
	/*
	found
	current
	string_tracker
	is_partial_match
	need_to_append_more_name
	*/
	if(package3->dict_trie_node == NULL || package3->context_state_attribute_trie_node == NULL)
	{
		// return null package
		return NULL;
	}

	/*
	these entries are also in the code where they are set
	need_to_append_more_name, context_state_is_found
	0, 0
	0, 1
	1, 0
	1, 0
	*/
	int i = 0;
	while(package3->dict_trie_node != NULL &&
		  package3->context_state_attribute_trie_node != NULL)
	{
		if(package3->dict_trie_node->word != NULL &&
		  package3->context_state_attribute_trie_node->word != NULL)
		{
			printf("%s, %s\n", package3->dict_trie_node->word, package3->context_state_attribute_trie_node->word);

		}
		// first time the root's neighbors are checked with the first name
		int ith_branch = isMatch(package3->context_state_attribute_trie_node->word,
								 package3->dict_trie_node);
		if(ith_branch >= 0) // match
		{
			printf("perfect match\n");
			package3->is_first_mismatch = false;
			// stop conditiions
			// perfect match(full match) or
			// input was completely found but tree still has more nodes (full match)

			//null, null case 2(perfect match)
			// *, null(input was completely found but tree still has more nodes)(match)

			if(
				(package3->context_state_attribute_trie_node->neighbors == NULL) 		||  // safety check only(not a case)

				(package3->dict_trie_node->neighbors[ith_branch] 			== NULL &&
			   package3->context_state_attribute_trie_node->neighbors[0] 	== NULL) 	||

				(package3->dict_trie_node->neighbors[ith_branch] 			 != NULL &&
			   	   package3->context_state_attribute_trie_node->neighbors[0] == NULL)
				)
			{
				if(
					(package3->context_state_attribute_trie_node->neighbors == NULL) 		||

					(package3->dict_trie_node->neighbors[ith_branch] 		!= NULL))
				{
					printf("perfect match 2\n");

				}
				package3->need_to_append_more_name = false;
				printf("%x\n", package3->dict_trie_node->neighbors[ith_branch]->object);

				if(package3->dict_trie_node->neighbors[ith_branch]->object != NULL)
				{
					// return a found flag
					package3->context_state_is_found = true;	// 	0, 1
					return package3;
				}
				else
				{
					// already existing objects are being put in here as an objectless internal node
					printf("can add as an internal node\n");
					// need to add it
					package3->context_state_is_found = false;  // 	0, 0
					if((package3->context_state_attribute_trie_node->neighbors == NULL) 		||
						(package3->dict_trie_node->neighbors[ith_branch] 		!= NULL))
					{
						package3->dict_trie_node = package3->dict_trie_node->neighbors[ith_branch];
						package3->context_state_attribute_trie_node = NULL;
						//package3->dict_trie_node = package3->dict_trie_node->neighbors;

						/*if(package3->dict_trie_node->word != NULL &&
								  package3->context_state_attribute_trie_node->word != NULL)
						{
							printf("%s, %s\n", package3->dict_trie_node->word, package3->context_state_attribute_trie_node->word);

						}*/

					}
					//package3->dict_trie_node = package3->dict_trie_node->neighbors[ith_branch];
					return package3;
				}
			}
			// relationship with ith_branch < 0
			/*
			ran out of input = not present
			mismatch == the character present is wrong 
			*/
			// null, *(tree ran out of input first)
			// tree ran out of input first(partial match)
			else if(package3->dict_trie_node->neighbors[ith_branch] 	     == NULL &&
			   	   package3->context_state_attribute_trie_node->neighbors[0] != NULL)
			{
				printf("partial match\n");

				// 	1, 0

				// sequence of strings doesn't exists
				package3->context_state_is_found = false;

				// need to append more names to trie tree dict
				package3->need_to_append_more_name = true;
				return package3;

				// return current and string tracker
			}
			// a, a(keep matching)
			// all good, so advance
			else
			{
				printf("advance\n");
				//dict_trie_node_prev = package3->dict_trie_node;
				package3->dict_trie_node = package3->dict_trie_node->neighbors[ith_branch];
				package3->context_state_attribute_trie_node = package3->context_state_attribute_trie_node->neighbors[0];
			}
		
		}
		// a, b case 
		// can't use the current versions of the trackers cause appending would have this for a future check
		// a, b
		// b
		// current->neighbors == NULL should be in here
		// 1, 0
		else // ith_branch < 0
		{
			printf("mismatch\n");
			printf("%s, %s\n", package3->dict_trie_node->word, package3->context_state_attribute_trie_node->word);
			// need to know if it was the first mismatch
			if(i == 0)
			{
				package3->is_first_mismatch = true;
			}
			else
			{
				package3->is_first_mismatch = false;
			}
			printf("here neighbors\n");
			// 	NULL, 1, 0
			// return dict_trie_node and context_state_attribute_trie_node
			package3->context_state_is_found = false;
			package3->need_to_append_more_name = true;
			// package3->is_partial_match is not set cause we don't know if the first one was a mismatch or the nth one
			// was a mismatch
			// need to return the node in the dict path right before the mismatch occurred so the future checks looks like this
			// [a, b] are neighbors
			// b
			// which will be a match next time
			// actually did go in right place entire time(not sure why)
			//package3->dict_trie_node = dict_trie_node_prev;
			return package3;
		}
		i++;
	}


	return NULL;
}
/*
	typedef struct TrieNode
	{

		char* word;
		struct TrieNode** neighbors;
		int neighbors_count;

		struct ContextState* object;
	}TrieNodee;

	
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
TrieNode* appendWord(TrieNode* node, char* ith_name)
{
	if(ith_name != NULL)
	{
		// node->neighbors_count > node->size is wrong
		printf("neighbors_count %i  node size %i\n", node->neighbors_count, node->size);

		TrieNode** neighbors = node->neighbors;
		// 
		// new item was stored at node->neighbors_count + 1 and node->neighbors_count == 0
		//int neighbors_count = node->neighbors_count + 1;
		//printf("neighbors_count %i\n", neighbors_count);
		int sizeof_new_neighbors;
		TrieNode** new_neighbors = NULL;
		if(node->neighbors_count == node->size)
		{
			if(node->size == 0)
			{
				sizeof_new_neighbors = sizeof(TrieNode*);
				new_neighbors = malloc(sizeof_new_neighbors);
			}
			else
			{
				sizeof_new_neighbors = sizeof(TrieNode*) * (node->size * 2);
				new_neighbors = malloc(sizeof_new_neighbors);

			}
			memcpy(new_neighbors,
			   neighbors,
			   sizeof(TrieNode*) * node->neighbors_count);

		}
		else if(node->neighbors_count < node->size)
		{
			new_neighbors = neighbors;
		}
		// might be a problem when node->neighbors_count < node->size

		//printf("here\n");

		


		// add (k+1)th word
		//printf("got here\n");
		// make a tracker pointing to the 
		// maybe this pattern doesn't work when there was nothing originally in the array
		new_neighbors[node->neighbors_count] = malloc(sizeof(TrieNode));
		//printf("here now %s\n", ith_name);
		int sizeof_ith_name = strlen(ith_name) + 1;

		new_neighbors[node->neighbors_count]->word = malloc(sizeof(char) * sizeof_ith_name);
		//printf("reached here\n");

		

		new_neighbors[node->neighbors_count]->neighbors = NULL;
		new_neighbors[node->neighbors_count]->object = NULL;



		memcpy(new_neighbors[node->neighbors_count]->word,
			   ith_name,
			   sizeof(char) * sizeof_ith_name);

		// only for copying over entire array
		// delete node_to_put_context_state_at->neighbors
		if(node->neighbors_count == node->size)
		{
			// might need to change this later
			free(node->neighbors);

			node->neighbors = new_neighbors;

		}
		// will not work
		// doesn't work if size == 0
		if(node->neighbors_count == node->size)
		{
			if(node->size == 0)
			{
				node->size = 1;
			}
			else
			{
				node->size = node->size * 2;

			}

		}
		node->neighbors_count += 1;
		// the node appended to end of array
		//printf("saved string %s\n", node->neighbors[node->neighbors_count - 1]->word);
		return node;
	}
	else
	{
		return NULL;
	}
	
}
TrieNode* appendTrieChain(TrieNode* root, ContextState* state, TrieNode* name)
{
	TrieNode* root_tracker = root;
	TrieNode* name_tracker = name;
	int count = 0;
	printf("appendTrieChain\n");
	if(root->word != NULL)
		printf("%s\n\n", root->word);

	while(name_tracker != NULL && root_tracker != NULL)
	{

		printf("%i\n", count);
		printf("%s   %s\n", root_tracker->word, name_tracker->word);
		printf("root_tracker %i, %i\n", root_tracker->size, root_tracker->neighbors_count);

		//printf("name_tracker %x\n", name_tracker);
		//printf("about to append\n");
		// not updating root_tracker correctly

		root_tracker = appendWord(root_tracker, name_tracker->word);
		//printf("root_tracker %i, %i\n", root_tracker->size, root_tracker->neighbors_count);
		//printTrieNodeTree(root, 1);
		printf("appended\n");
		if(name_tracker->neighbors != NULL)
		{
			name_tracker = name_tracker->neighbors[0];
			// go to the last one found
			root_tracker = root_tracker->neighbors[root_tracker->neighbors_count - 1];
		}
		else
		{
			// no more words left to add so go to the last word added
			root_tracker = root_tracker->neighbors[root_tracker->neighbors_count - 1];
			//printf("last word %s\n", root_tracker->word);

			break;
		}
		count++;
	}
	// setting the state to the last word
	root_tracker->object = state;
	printf("object added %x\n", root_tracker->object);
	// need to add indents and a thumbnail attribute so not all of the state is printed out

	return root;
}

// adding a ContextState to a 
void insert(TrieNode* root, ContextState* state)
{
	// tracker is always pointing to root
	TrieNode* root_tracker = root;
	printf("neighbors_count %i\n", root_tracker->neighbors_count);

	// take the name
	// search for name in the trienode
	TrieNodePackage3* last_word_index_correctly_matched_package = findInTrie2(root_tracker, state->state_name->neighbors[0]);
	/*
	typedef struct TrieNodePackage3
	{
		TrieNode* dict_trie_node;
		TrieNode* context_state_attribute_trie_node;
		bool context_state_is_found;
		bool is_partial_match;
		bool need_to_append_more_name;
	}TrieNodePackage3;
	*/

	if(last_word_index_correctly_matched_package == NULL)
	{
		// root is empty
		printf("root is empty\n");
		// root_tracker = f(state, )
		root_tracker = appendTrieChain(root_tracker, state, state->state_name->neighbors[0]);

		//printf("last word associated with state %s\n\n", root_tracker->word);

		//printTrieNodes(root_tracker);
		//printf("\n");
		//printContextState(root_tracker->object);
		//exit(1);
		//root_tracker = appendNode(root_tracker,
		//							  getIthWord(state->state_name, 0));
	}

	else
	{

		// the trackers have already be adjusted acording to their situation
		TrieNode* dict_trie_node = last_word_index_correctly_matched_package->dict_trie_node;
		TrieNode* context_state_attribute_trie_node = last_word_index_correctly_matched_package->context_state_attribute_trie_node;
		//printf("%x, %x\n", dict_trie_node, context_state_attribute_trie_node);
		bool context_state_is_found = last_word_index_correctly_matched_package->context_state_is_found;
		bool need_to_append_more_name = last_word_index_correctly_matched_package->need_to_append_more_name;
		bool is_first_mismatch = last_word_index_correctly_matched_package->is_first_mismatch;

		if(!context_state_is_found)
		{
			if(need_to_append_more_name)
			{
				if(is_first_mismatch)
				{
					printf("first mismatch\n");
					root_tracker = appendTrieChain(dict_trie_node, state, state->state_name->neighbors[0]);

					//printf("\n\nprint out tree\n");
					//printTrieNodeTree(root_tracker, 1);
				}
				else
				{
					printf("2 to nth mismatch\n");

					// need to add stuff
					root_tracker = appendTrieChain(dict_trie_node, state, context_state_attribute_trie_node);
				}
				

			}
			else
			{
				printf("add as an internal node\n");
				root_tracker = appendTrieChain(dict_trie_node, state, context_state_attribute_trie_node);
			}
			// x x something
			// x x isn't being added right
			// problem
			// add context state
			//root_tracker->object = state;
			// it might have connected this with the root
			// 
			//printContextState(root_tracker->object);

		}
		
	}
	
}
/////
int main(int argc, char** argv)
{
	char* input = readFile(argv[2]);
	//printf("%s\n", input);
	// todo
	// get rid of all blank lines
	ContextState* tree = makeTree(input);
	//printTree(tree, 0);
	const char* parsing_graph = readFile(argv[1]);
	//printf("%s\n", parsing_graph);
	// the parser code appears to compile
	const int number_of_tokens = 1000;
	jsmn_parser parser;
	jsmntok_t tokens[number_of_tokens];

	jsmn_init(&parser);
	jsmnerr_t parsing_results;
	parsing_results = jsmn_parse(&parser,
								 parsing_graph,
								 (size_t) strlen(parsing_graph),
								 tokens,
								 number_of_tokens
								 );
	/*
		typedef struct TrieNode
		{

			char* word;
			struct TrieNode** neighbors;
			int neighbors_count;

			struct ContextState* object;
		}TrieNodee;

	
	*/
	TrieNode* root = malloc(sizeof(TrieNode));
	char* root_word = "root";

	root->word = malloc(sizeof(char) * 5);
	memcpy(root->word, root_word, sizeof(char) * 5);
	root->neighbors = NULL;
	root->neighbors_count = 0;
	root->object = 0;
	root->size = 0;

	// 

	//printf("%i\n", parsing_results);
	/*
		typedef struct {
			jsmntype_t type;
			int start;
			int end;
			int size;
		#ifdef JSMN_PARENT_LINKS
			int parent;
		#endif
		} jsmntok_t;

		typedef enum {
			JSMN_PRIMITIVE = 0,
			JSMN_OBJECT = 1,
			JSMN_ARRAY = 2,
			JSMN_STRING = 3
		} jsmntype_t;

	*/

	printf("%i\n", _primitive);
	printf("%i\n", parsing_results);
	//exit(1);
	for(int i = 0; i < parsing_results;)
	{
		int json_type = tokens[i].type;
		if(json_type == 0)
		{
			printf("primitive\n");
			 i++;
		}
		// i == 73896
		else if(json_type == 1)
		{
			//printf("object to run %i\n", i);
			//printf("|%s|\n", collectChars(tokens[i], parsing_graph));

			ContextState* state = makeContextState(&i, tokens, parsing_graph, parsing_results);

			printf("printing state\n\n");
			//printContextState(state);
			if(root != NULL)
			{
				insert(root, state);

			}
			

			//void addToTrie(TrieNode* root, ContextState* state)

			if(i >= parsing_results)
			{
				break;
			}

			//exit(2);

		}
		else if(json_type == 2)
		{
			printf("array\n");
			 i++;
		}
		else if(json_type == 3)
		{
			printf("string\n");
			 i++;
		}
		// to ensure machines can't alter each other's data only allow the current machine to be passed to each function
		// how can a machine indirectly alter another machine?
		// https://stackoverflow.com/questions/2672015/hiding-members-in-a-c-struct
		// https://mattferderer.com/what-is-the-actor-model-and-when-should-you-use-it
		//printf("|%s|\n", collectChars(tokens[i], parsing_graph));
	}
	if(root->neighbors != NULL)
	{
		printf("printing tree\n");
		printTrieNodeTree(root, 1);
		printf("\n");
	}
	// loop untill hit object
	// call makeContextState on object
	/*
	jsmnerr_t jsmn_parse(jsmn_parser *parser,
						 const char *js,
						 size_t len,
						 jsmntok_t *tokens,
						 unsigned int num_tokens) {
	*/

	//ht_hash_table* parsing_states = ht_new();


	return 0;
}
