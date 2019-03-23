#ifndef STATE3
#define STATE3
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
		bool _is_string_p;

		int string_p_size;

		float* _float_p;
		bool _is_float_p;
		void** additional_types;
		bool** is_additional_types;
}ContextState;
ContextState* ContextState1();
ContextState* setName(ContextState* node, char* name);
ContextState* appendParent(ContextState* node, ContextState* parent);
ContextState* appendChild(ContextState* node, ContextState* parent);

#endif
