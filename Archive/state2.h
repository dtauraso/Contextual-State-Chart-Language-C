#ifdef STATE
#define STATE

#include "standard_headers.h"

// each ContextState is a state
typedef struct ContextState {
	char* name;

	char** start_children;
	int start_children_size;

	char** parents;
	int parents_size;


	// no recursion, have an indent on/off var in the stack
	// when the child state is at a higher level than the current state
		// deactivate the indent
	// use last indent on/off value to find out if indents should be on or off
	// (current state, prev item on stack, is_indent_on)

	char** children;
	int children_size;

	char** nexts;
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
} ContextState;

struct ContextState* newState();


#endif
