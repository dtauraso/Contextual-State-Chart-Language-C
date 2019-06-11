#include "state3.h"
#include "lisp_node.h"
#include "trie_node.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
//https://zserge.com/jsmn.html
#include "jsmn/jsmn.h"

void deleteLispNodes(LispNode* root);

void printState(ContextState* node);
enum token_types {_primitive, _object, _array, _string};
LispNode* makeLispNode();
LispNode* setValueToList(LispNode* list_a, LispNode* list_b);
LispNode* setValueToString(LispNode* list, char* word);
LispNode* appendList(LispNode* root, LispNode* list_a, LispNode* list_b);
enum data_types{is_list, is_string, is_empty_case};
LispNode* cons(void* data, void* link, int data_type, int count, int call_count);
void printLispNodes(LispNode* root, int indent_level);
TrieNode* convertLispChainToTrieNodeChain(LispNode* root);
void deleteLispNodes(LispNode* root);

ContextState* makeFullContextState(
	TrieNode* name,
	TrieNode* nexts,
	TrieNode* start_children,
	TrieNode* children,
	char* function_name,
	Data* variable_from_json_dict,
	TrieNode* parents);
ContextState* makeTree(char* input);


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

void swap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = *a;
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




// 2 hash tables
// each input name + object name -> object holding the name
// parse tree each name part -> waypoint object or object holding data

// 1 tri tree for the name part chain to the object holding data, so auto-enumerating
// new states is simple



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
// enum token_types {_primitive, _object, _array, _string};

// user can't use "\n" in the state name
// make a string of entire name[name1\nname2/\n...] -> contextState map
// then partal name -> contextState (each internal node in the trie is a dummy node, unless a state name is a partial path)
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

// enum data_types{is_list, is_string, is_empty_case};

// for reading the token sequence the json parsing api provides

//////////////


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

	//printf("%i\n", _primitive);
	//printf("%i\n", parsing_results);
	//exit(1);
	for(int i = 0; i < parsing_results;)
	{
		int json_type = tokens[i].type;
		if(json_type == 0)
		{
			//printf("primitive\n");
			 i++;
		}
		else if(json_type == 1)
		{
			//printf("object to run %i\n", i);
			//printf("|%s|\n", collectChars(tokens[i], parsing_graph));

			ContextState* state = makeContextState(&i, tokens, parsing_graph, parsing_results);

			//printf("printing state\n\n");
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
			//printf("array\n");
			 i++;
		}
		else if(json_type == 3)
		{
			//printf("string\n");
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
