#ifndef STATE3
#define STATE3
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


enum stack_types{char_p_p, struct_context_state_p_p};


/*
char*** lists_of_list_of_char_p
int count


char** list_of_char_p
int count
*/
typedef struct LispNode
{
	void* value;
	struct LispNode* next;

	int value_type;
	int count;
	int call_count;

}LispNode;

// for collecting a list of lists of strings for ContextState
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
	int count;
}List;


// for storing the name -> ContextState map
typedef struct TrieNode
{

	char* word;
	struct TrieNode** neighbors;
	int neighbors_count;

	int size; // power of 2
	struct ContextState* object;
}TrieNode;

/*
dummy node
		root2->word = NULL;
		root2->object = NULL;
		root2->neighbors = malloc(sizeof(TrieNode*) * root->call_count);
		root2->neighbors_count = 0;
		root2->size = 0;

*/
typedef struct TrieNodePackage
{
	TrieNode* address;
	int ith_name_checked_in_search;

}TrieNodePackage;

typedef struct TrieNodePackage2
{
	TrieNode* address;
	bool address_is_match;

}TrieNodePackage2;

typedef struct TrieTree
{
	struct TrieNode* root;

}TrieTree;

typedef struct NamesSize
{
	char** names;
	int size;

}NamesDelimiterLocations;

typedef struct ListNames
{
	struct NamesSize* full_name;
	int size;
}ListNames;
typedef struct ListOfNames
{

	int list_of_names_size;  // put here cause altering list_of_names messes it up
	char*** list_of_names;
	int* names_sizes;



}ListOfNames;

typedef struct NeighborNames
{
	char** list_of_names;
	int number_of_names;
	int* start_names;
	int number_of_start_names;
}NeighborNames;
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
		TrieNode* state_name;

		int** neighbors;
		int* neighbors_count;

		TrieNode* start_children;


		struct ContextState** parents;
		int* parents_hash;

		char** parents_names;
		int parents_size;

		TrieNode* parents_;


		// no recursion, have an indent on/off var in the stack
		// when the child state is at a higher level than the current state
			// deactivate the indent
		// use last indent on/off value to find out if indents should be on or off
		// (current state, prev item on stack, is_indent_on)

		struct ContextState** children;
		int* children_hash;

		char** children_names;
		int children_size;

		TrieNode* children_;


		struct ContextState** nexts;
		int* nexts_hash;

		char** nexts_names;
		int nexts_size;


		TrieNode* nexts_;

		// tri tree for partial state name matches(can match only 1 name at a time)
		//struct TrieNode* tri_children;

		// the next level from name's perspective

		// when parts of a full name are linked to a context state object
		// the context state object may be a dummy node
		bool dummy_node;

		bool (*function_pointer)(char* name, void** tree);
		char* function_pointer_name;

		Data* var_data;

		
		
}ContextState;


/*
typedef struct Names
{
	char** strings;
	int size;
};

typedef struct neighbors
{
		struct Names* start_children_names;
		struct Names* parents_names;
		struct Names* children_names;
		struct Names* nexts_names;

};
typedef struct ContextState1
{
		// int** is for finding neighbors stored inside a hash table
		char* name;

		struct neighbors* neighbors_;
		//struct Names* start_children_names;
		ht_hash_table* tri_children;


		//struct Names* parents_names;


		// no recursion, have an indent on/off var in the stack
		// when the child state is at a higher level than the current state
			// deactivate the indent
		// use last indent on/off value to find out if indents should be on or off
		// (current state, prev item on stack, is_indent_on)


		//struct Names* children_names;

		//struct Names* nexts_names;

		// tri tree for partial state name matches(can match only 1 name at a time)
		//ht_hash_table* tri_children;

		// the next level from name's perspective

		// when parts of a full name are linked to a context state object
		// the context state object may be a dummy node
		bool dummy_node;

		bool (*function_pointer)(char* name, void** tree);
		char* function_pointer_name;

		struct Data* var;
		
		
		
}ContextState1;
*/

ContextState* initContextState();
ContextState* setName(ContextState* node, char* name);
ContextState* appendParent(ContextState* node, ContextState* parent);
ContextState* appendChild(ContextState* node, ContextState* parent);
LispNode* cons(void* data, void* link, int data_type, int count, int call_count);

//char** setLink(int* size, char** names, const char* other_node);




#endif
