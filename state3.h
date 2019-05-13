#ifndef STATE3
#define STATE3
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


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

		char* name;

		struct ContextState** start_children;
		int start_children_size;

		struct ContextState** parents;
		int parents_size;


		// no recursion, have an indent on/off var in the stack
		// when the child state is at a higher level than the current state
			// deactivate the indent
		// use last indent on/off value to find out if indents should be on or off
		// (current state, prev item on stack, is_indent_on)

		struct ContextState** children;
		int children_size;

		struct ContextState** nexts;
		int nexts_size;

		// tri tree for partial state name matches(can match only 1 name at a time)
		struct ContextState** tri_children;
		int tri_children_size;

		bool (*function_pointer)(char* name, void** tree);
		char* function_pointer_name;

		//struct Data* var;
		
		int _int;
		bool _is_int;

		char* _string;
		bool _is_string;

		int string_size;

		float _float;
		bool _is_float;

		int* _int_p;
		bool _is_int_p;

		char** _string_p;
		int _string_p_size;
		bool _is_string_p;

		int string_p_size;

		float* _float_p;
		bool _is_float_p;
		void** additional_types;
		int additional_types_size;
		bool** is_additional_types;

		struct ContextState** context_state_p;
		int context_state_p_size;
		
}ContextState;
ContextState* initContextState();
ContextState* setName(ContextState* node, char* name);
ContextState* appendParent(ContextState* node, ContextState* parent);
ContextState* appendChild(ContextState* node, ContextState* parent);

#endif
