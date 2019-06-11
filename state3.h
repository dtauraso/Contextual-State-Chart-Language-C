#ifndef STATE3
#define STATE3
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lisp_node.h"
#include "trie_node.h"


//enum stack_types{char_p_p, struct_context_state_p_p};




struct TrieNode;

// can't group it like this
// need to think by letter than by word
// typedef only seems to let me use "ContextState" outside the struct definition
typedef struct Data
{
	int type_id; // enum
	/*
	0 => int
	1 => string
	2 => float

	*/
	int _int;

	char* _string;
	int string_size;

	float _float;

}Data;
typedef struct ContextState
{
		char* name;
		struct TrieNode* state_name;

		int** neighbors;
		int* neighbors_count;

		struct TrieNode* start_children;


		struct ContextState** parents;
		int* parents_hash;

		char** parents_names;
		int parents_size;

		struct TrieNode* parents_;


		// no recursion, have an indent on/off var in the stack
		// when the child state is at a higher level than the current state
			// deactivate the indent
		// use last indent on/off value to find out if indents should be on or off
		// (current state, prev item on stack, is_indent_on)

		struct ContextState** children;
		int* children_hash;

		char** children_names;
		int children_size;

		struct TrieNode* children_;


		struct ContextState** nexts;
		int* nexts_hash;

		char** nexts_names;
		int nexts_size;


		struct TrieNode* nexts_;

		// tri tree for partial state name matches(can match only 1 name at a time)
		//struct TrieNode* tri_children;

		// the next level from name's perspective

		// when parts of a full name are linked to a context state object
		// the context state object may be a dummy node
		//bool dummy_node;

		// can only be a function state or a data state
		bool (*function_pointer)(char* name, void** tree);
		char* function_pointer_name;

		Data* var_data;
		int context_id;  // each context is enumerated
		
		// used by visitor function
		// set in parser
		bool start_children_are_parallel;
		bool nexts_are_parallel;
		bool is_start_child;
		bool is_child;
		bool is_parent;
		bool is_start_state;
		bool is_end_state;
		bool is_data_state;

		// set in visitor
		bool is_visited;
		int total_start_children_who_failed;

		// set by an api the state function uses
		char* debugging_log;

}ContextState;

ContextState* initContextState();
ContextState* setName(ContextState* node, char* name);
ContextState* appendParent(ContextState* node, ContextState* parent);
ContextState* appendChild(ContextState* node, ContextState* parent);
void printContextState2(ContextState* node);
int isMatch(char* ith_word, struct TrieNode* node);

struct TrieNode* appendNode(struct TrieNode* node, char* ith_name);
void addToTrie(struct TrieNode* root, ContextState* state);
char* lispNodeType(int type_value);
void printLispNodes(LispNode* root, int indent_level);
void deleteLispNodes(LispNode* root);

void printData(Data* var_data);
void printTrieNodeTree(struct TrieNode* root, int indent);
void printContextState(ContextState* node);
void printTrieNodes(struct TrieNode* trie_node_sequence);
void printTrieNodeTreeFlat(struct TrieNode* root);
ContextState* duplicate(ContextState* item);
ContextState* initContextState();
ContextState* makeContextState(int* i, jsmntok_t tokens[], const char* input, int token_count);

int countTabs(char* input, int i);
char* makeSpaces(int indent_level);
void swap(int* a, int* b);
void doubleLink(ContextState* parent, ContextState* child);
int countLines(char* input);


//////
char* getNextWord(char* input, int i);
char* collectChars(jsmntok_t token, const char* input);



#endif
