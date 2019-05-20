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
	
	return json_part;

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
void arrayOfArrays(int* i, jsmntok_t tokens[], const char* input)
{
	// the array token is also [] or [stuff]
	// current token is at an array
	// automaticall sets i to the next token
	jsmntok_t token = tokens[*i];
	if(token.type != _array) exit(1);
	//*i += 1;
	//token = tokens[*i];

	char* token_string = collectChars(token, input);
	if(strcmp(token_string, "[]") == 0)
	{
		printf("empty array\n");
		*i += 1;

	}
	else
	{
		// current token is at first array in the sequence:
		// array array strings array strings
		// array strings not_array
		if(tokens[ *i ].type 		 == _array &&
		   tokens[ ( *i ) + 1 ].type == _array)
		{
			*i += 1;
		}
		while(!tokenIsKeyWord(token_string))
		{

			if(token.type == _object)
			{
				printf("here\n");
				return;
			}
			else if(token.type == _array)
			{
				// no data to collect the first time this is run
				printf("end of last block and start of next block\n");

			}
			else
			{
				printf("%s\n", tokenType(token));
				printf("	%s\n", token_string);
				printf("increment insert to trie\n\n");

			}

			
			

			*i += 1;
			token = tokens[*i];

			token_string = collectChars(token, input);
			if(tokenIsKeyWord(token_string))
			{
				printf("end of final block\n");
				printf("rest trie tracker to trie root\n");
			}
		}
	}
}
void variable(int* i, jsmntok_t tokens[], const char* input)
{
	jsmntok_t token = tokens[*i];
	if(token.type != _object) exit(1);
	printf("%s\n", tokenType(token));
	printf("%s\n", collectChars(token, input));
	char* token_string = collectChars(token, input);
	if(strcmp(token_string, "{}") == 0)
	{
		printf("empty variable\n");
		*i += 1;
	}
	else
	{
		printf("%s\n", token_string);
		*i += 1;
		token = tokens[*i];
		printf("	%s\n", collectChars(token, input));
		*i += 1;
		token = tokens[*i];
		printf("	%s\n", collectChars(token, input));
		*i += 1;
	}

}
void makeContextState(int* i, jsmntok_t tokens[], const char* input, int token_count)
{
	printf("object to run |%s|\n", collectChars(tokens[*i], input));

	jsmntok_t token = tokens[*i];
	printf("%s\n", tokenType(token));
	if(token.type != _object) exit(1);
	*i += 1;
	token = tokens[*i];
	//printf("%s\n", tokenType(token));
	if(token.type != _string) exit(1);
	*i += 1;
	token = tokens[*i];
	//printf("%s\n", tokenType(token));
	arrayOfArrays(i, tokens, input);
	// tokens[i] == "nexts"
	token = tokens[*i];

	//printf("%s\n", collectChars(token, input));
	printf("%s\n", collectChars(token, input));

	// at keyword now
	*i += 1;
	token = tokens[*i];
	printf("%s\n", tokenType(token));
	arrayOfArrays(i, tokens, input);


	token = tokens[*i];

	//printf("%s\n", collectChars(token, input));
	printf("%s\n", collectChars(token, input));
	// at keyword now
	*i += 1;
	token = tokens[*i];
	printf("%s\n", tokenType(token));
	arrayOfArrays(i, tokens, input);


	token = tokens[*i];

	//printf("%s\n", collectChars(token, input));
	printf("%s\n", collectChars(token, input));
	// at keyword now
	*i += 1;
	token = tokens[*i];
	printf("%s\n", tokenType(token));
	arrayOfArrays(i, tokens, input);
	token = tokens[*i];
	printf("%s\n", tokenType(token));
	printf("%s\n", collectChars(token, input));


	*i += 1;
	token = tokens[*i];
	printf("%s\n", tokenType(token));
	printf("%s\n", collectChars(token, input));

	*i += 1;
	token = tokens[*i];
	printf("%s\n", tokenType(token));
	printf("%s\n", collectChars(token, input));

	*i += 1;
	token = tokens[*i];
	variable(i, tokens, input);
	printf("done with variable\n");
	token = tokens[*i];
	printf("%s\n", collectChars(token, input));

	*i += 1;
	token = tokens[*i];
	printf("%s\n", tokenType(token));
	arrayOfArrays(i, tokens, input);
	// now we are at the next object
	printf("next\n");
	//*i += 1;
	// may be out of tokens
	if(*i < token_count)
	{
		token = tokens[*i];
		printf("done %i\n", *i);
	}
	
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
	for(int i = 0; i < parsing_results;)
	{
		int json_type = tokens[i].type;
		if(json_type == 0)
		{
			printf("primitive\n");
			 i++;
		}
		else if(json_type == 1)
		{
			//printf("object to run %i\n", i);
			//printf("|%s|\n", collectChars(tokens[i], parsing_graph));

			makeContextState(&i, tokens, parsing_graph, parsing_results);
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

		//printf("|%s|\n", collectChars(tokens[i], parsing_graph));
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
