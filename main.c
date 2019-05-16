#include "state3.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
//https://zserge.com/jsmn.html
#include "jsmn/jsmn.h"
#include "hash_table1.h"


 ht_hash_table* ht_new();


char* getNextWord(char* input, int i)
{
 	// this function gets the next word
	int j = 0;
	int count = 0;
	if(i >= strlen(input))
	{
		return NULL;
	}
	while(input[i+j] != '\n')
	{
		//printf("%c ", input[i+j]);

		j++;
		count ++;
	}
	//printf("character count %i\n", count);
	char* word = malloc(sizeof(char) * j);
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
int countTabs(char* input, int i)
{
	int k = 0;
	//printf("|%x|\n", input[i+k]);
	// this 't' is actually invisable from Atom when used as a tab character
	while(input[i+k] == '\t')
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
void doubleLink(ContextState* parent, ContextState* child)
{
	child = appendParent(child, parent);
	//printf("child saved 1.2 %s\n", child->name);

	parent = appendChild(parent, child);
	//printf("child saved 1.3 %s\n", child->name);


}
void doubleLinkHash(ht_hash_table* input_states, int parent, int child)
{

	input_states = appendParentHash(input_states, child, parent);
		printf("here\n");

	input_states = appendChildHash(input_states, parent, child);
	printf("here 2\n");

}
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
ht_hash_table* appendParentHash(ht_hash_table* states,
								int node, // use char* instead because table[f(node)] will always get to the right thing, table[node] may not due to table being updated quite often
							    int parent);
void ht_insert(ht_hash_table* ht, const char* key, const void* value);
int getIndexOfKey(ht_hash_table* ht, const char* key);
void* ht_search(ht_hash_table* ht, const char* key);
void printHash(ht_hash_table* ht);

ContextState* makeTree(char* input)
{
	// needs the input to end on a newline after the last collectable text
	// there can't be any lines with only indents
	int current_indent = 0;
	int next_indent = 0;
	int i = 0;
	int num_lines = countLines(input);
	ht_hash_table* input_states = ht_new();
	//printf("%s\n %i\n", input, i);
	// this is so the we can traverse above nodes in the tree that have data
	// from input
	// something is wrong with adding and searching the hash table
	ContextState* dummy_dummy_root = initContextState();
	// when setting strings for ContextState I seem to have to save them as "\"" + name + "\"" or the string may resizes itself and puts in garbage chars
	// the hash table(ht_hash_table) seems to be immune to this
	// object is fine, but the entry in the table didn't save the name right
	dummy_dummy_root = setName(dummy_dummy_root, "\"dummy_dummy_root\"");
	printf("from original object %s\n", dummy_dummy_root->name);



	// insert to table under "dummy_dummy_root"
	ht_insert(input_states, "\"dummy_dummy_root\"", dummy_dummy_root);
	/*printf("testing\n");
	printHash(input_states);
	printf("done testing\n");
	*/
	ContextState* test1 = (ContextState*) ht_search(input_states, "\"dummy_dummy_root\"");
	printf("test1 %s\n", test1->name);
	

	int dummy_dummy_root_hash = getIndexOfKey(input_states, "\"dummy_dummy_root\"");

	ContextState* dummy_root = initContextState();
	// insert to table under "dummy_root"
	dummy_root = setName(dummy_dummy_root, "\"dummy_root\"");


	ht_insert(input_states, "\"dummy_root\"", dummy_root);
	// maybe inserting another item causes the original index to be invalid because the table gets updated
	int dummy_root_hash = getIndexOfKey(input_states, "\"dummy_root\"");



	ContextState* root = initContextState();
	root = setName(root, "\"root\"");

	ht_insert(input_states, "\"root\"", root);
	ContextState* test2 = (ContextState*) ht_search(input_states, "\"root\"");
	printf("test2 %s\n", test2->name);

	ContextState* parent = root;
	//int parent_hash = getIndexOfKey(input_states, "root");

	int child_hash;
	ContextState* child;
	// now have to 

	exit(0);
	//ContextState* test2 = (ContextState*) ht_search(input_states, "dummy_root");

	//printf("%s\n", test1->name);
	//printf("%s\n", test2->name);


	doubleLink(dummy_dummy_root, dummy_root);

	doubleLink(dummy_root, parent);

	// error here
	//doubleLinkHash(input_states, dummy_dummy_root_hash, dummy_root_hash);
	//doubleLinkHash(input_states, dummy_root_hash, parent_hash);

	// need a parent pointer and a child pointer
	// have the parent and child already set up before the loop starts
	char* word = getNextWord(input, i);
	parent = setName(parent, word);

	i += strlen(word) + 1;
	next_indent = countTabs(input, i);
	i += next_indent;
	free(word);
	//printf("indents current %i, next %i\n", current_indent, next_indent);

	// swap(&current_indent, &next_indent);

	// assuming there will be 1 state and 1 child
	if(next_indent > current_indent)
	{
		word = getNextWord(input, i);
		child = initContextState();
		child = setName(child, word);

		//ht_insert(input_states, word, child);
		//child_hash = getIndexOfKey(input_states, word);
		doubleLink(parent, child);
		//doubleLinkHash(input_states, parent_hash, child_hash);
		//next_indent = countTabs(input, i);
		//printf("child%s\n", child->name[0]);
		//next_indent = countTabs(input, i);
		//printf("indents current %i, next %i\n", current_indent, next_indent);

		//printf("|%c|\n", input[i]);
		i += strlen(word) + 1;
		//printf("|%c|\n", input[i]);
		next_indent = countTabs(input, i);

		i += next_indent;

		//next_indent = countTabs(input, i);

		swap(&current_indent, &next_indent);

		free(word);

	}
	//printTree(parent, 0);
	//i++;
	//next_indent = countTabs(input, i);
	//printf("indents current %i, next %i\n", current_indent, next_indent);

	//printf("%lu\n", sizeof(struct ContextState));
	//printf("|%c|\n", input[i]);

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
void makeContextState(jsmntok_t token, ht_hash_table* parsing_graph)
{
	// token is array
	if(token.type == 2)
	{
		// check array start and end for "[", "]"
		// if not null
		// check next item for being an array type
		// while there are arrays
	}
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
	/*
	for(int i = 0; i < parsing_results; i++)
	{
		int json_type = tokens[i].type;
		if(json_type == 0)
		{
			printf("primitive\n");
		}
		else if(json_type == 1)
		{
			printf("object\n");
		}
		else if(json_type == 2)
		{
			printf("array\n");
		}
		else if(json_type == 3)
		{
			printf("string\n");
		}

		printf("|%s|\n", collectChars(tokens[i], parsing_graph));
	}
	*/
	// loop untill hit object
	// call makeContextState on object
	/*
	jsmnerr_t jsmn_parse(jsmn_parser *parser,
						 const char *js,
						 size_t len,
						 jsmntok_t *tokens,
						 unsigned int num_tokens) {
	*/

	ht_hash_table* parsing_states = ht_new();


	return 0;
}
