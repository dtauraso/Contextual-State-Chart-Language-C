#ifndef STATE3
#define STATE3
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hash_table1.h"


enum stack_types{char_p_p, struct_context_state_p_p};
typedef struct Stack
{
	void** container;
	int size;
	int last_pos;
	bool is_char_p_p;
	bool is_struct_context_state_p_p;
}Stack;
Stack* setup(int type_value);
Stack* insert(Stack* stack, void* item);

// typedef only seems to let me use "ContextState" outside the struct definition
typedef struct ContextState
{
		// int** is for finding neighbors stored inside a hash table
		char* name;

		struct ContextState** start_children;
		int* start_children_hash;

		char** start_children_names;
		int start_children_size;

		struct ContextState** parents;
		int* parents_hash;

		char** parents_names;
		int parents_size;


		// no recursion, have an indent on/off var in the stack
		// when the child state is at a higher level than the current state
			// deactivate the indent
		// use last indent on/off value to find out if indents should be on or off
		// (current state, prev item on stack, is_indent_on)

		struct ContextState** children;
		int* children_hash;

		char** children_names;
		int children_size;

		struct ContextState** nexts;
		int* nexts_hash;

		char** nexts_names;
		int nexts_size;

		// tri tree for partial state name matches(can match only 1 name at a time)
		ht_hash_table* tri_children;

		// the next level from name's perspective

		// when parts of a full name are linked to a context state object
		// the context state object may be a dummy node
		bool dummy_node;

		bool (*function_pointer)(char* name, void** tree);
		char* function_pointer_name;

		int type_id; // enum

		int** _int_p;
		int _int_p_size;

		char** _string_p;
		int string_p_size;

		float** _float_p;
		int _float_p_size;		
		
		
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
typedef struct Data
{
	int type_id; // enum

	int** _int_p;
	int _int_p_size;

	char** _string_p;
	int string_p_size;

	float** _float_p;
	int _float_p_size;
};*/
ContextState* initContextState();
ContextState* setName(ContextState* node, char* name);
ContextState* appendParent(ContextState* node, ContextState* parent);
ContextState* appendChild(ContextState* node, ContextState* parent);
ht_hash_table* appendParentHash(ht_hash_table* states,
								const char* node,
							    const char* parent);
ht_hash_table* appendChildHash(ht_hash_table* states,
							   const char* node,
							   const char* child);


#endif
