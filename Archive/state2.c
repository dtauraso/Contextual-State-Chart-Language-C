
//#include "state.h"
//#include "point.h"
//#include "name.h"
#include "state2.h"


// state2.h is not being read before this is
struct ContextState* newState()
{
	struct ContextState* test =  malloc(sizeof(struct ContextState));
	test->name = malloc(sizeof(char) * 50);
	//memcpy(test->name, input, sizeof(char) * strlen(input));
	return test;
}
//#include "states.h"
// forward declaration of a struct
//struct Names;
//struct ContextState;
//struct SparseMatrix;
//enum attributes {_StartChildren, _Parents, _Children, _Nexts, _int, _string, string_size, _float, _int_p, _string_p, string_p_size, _float_p, sparse_matrix_levels};
/*
bool runFunction(struct ContextState* state, struct SparseMatrix* levels, struct level_id_state_id* point, struct Names* current_state_name)
{

	return levels[point->level_id].state_list[point->state_id]->function_pointer(current_state_name, levels);
}
*/
/*
struct ContextState* makeNewState()
{
	struct ContextState* new_state = malloc(sizeof(struct ContextState));
	return new_state;
}
void setFunctionPointer(struct ContextState* node, bool (*function_pointer)(struct Names* a, struct SparseMatrix* b), char* function_pointer_name)
{
	node->function_pointer = function_pointer;
	node->function_pointer_name = function_pointer_name

	//return node->function_pointer;
}
void setNames(struct ContextState* state, struct Names* names)
{
	state->name = malloc(sizeof(struct Names));
	memcpy(state->name, names, sizeof(struct Names));

}
void initializeSizes(struct ContextState* state)
{
	state->start_children_size = 0;
	state->parents_size = 0;
	state->children_size = 0;
	state->nexts_size = 0;
}
void initializeVars(struct ContextState* state)
{
	state->var = malloc(sizeof(struct Data));
	state->var->_int = 0;
	state->var->_string = NULL;
	state->var->_float = 0.0;
	state->var->_int_p = NULL;
	state->var->_string_p = NULL;
	state->var->_float_p = NULL;
	state->var->levels = NULL;
}
void setIsInt(struct ContextState* state, bool on_off)
{
	state->var->_is_int = on_off;

}

void setIsString(struct ContextState* state, bool on_off)
{
		state->var->_is_string = on_off;

}

void setIsFloat(struct ContextState* state, bool on_off)
{
		state->var->_is_float = on_off;

}
void setIsIntPtr(struct ContextState* state, bool on_off)
{
		state->var->_is_int_p = on_off;

}
void setIsStringPtr(struct ContextState* state, bool on_off)
{
		state->var->_is_string_p = on_off;

}
void setIsFloatPtr(struct ContextState* state, bool on_off)
{
		state->var->_is_float_p = on_off;

}
void setIsLevels(struct ContextState* state, bool on_off)
{
		state->var->is_levels = on_off;

}
struct Names* getName(struct ContextState* state)
{
	return state->name;
}
struct Names** getStartChildren(struct ContextState* state)
{
	return state->start_children;
}
struct Names** getParents(struct ContextState* state)
{
	return state->parents;
}
struct Names** getChildren(struct ContextState* state)
{
	return state->children;
}
struct Names** getNexts(struct ContextState* state)
{
	return state->nexts;
}
char* getFunctionPointerName(struct ContextState* state)
{
	return state->function_pointer_name;
}
struct Data* getVar(struct ContextState* state)
{
	return state->var;
}
bool getVarIsInt(struct ContextState* state)
{
	return state->var->_is_int;
}
bool getVarIsString(struct ContextState* state)
{
	return state->var->_is_string;
}
bool getVarIsFloat(struct ContextState* state)
{
	return state->var->_is_float;
}
bool getVarIsIntPtr(struct ContextState* state)
{
	return state->var->_is_int_p;
}
bool getVarIsStringPtr(struct ContextState* state)
{
	return state->var->_is_string_p;
}
bool getVarIsFloatPtr(struct ContextState* state)
{
	return state->var->_is_float_p;
}
bool getVarIsLevels(struct ContextState* state)
{
	return state->var->is_levels;
}


int getVarInt(struct ContextState* state)
{
	return state->var->_int;
}
char* getVarString(struct ContextState* state)
{
	return state->var->_string;
}
float getVarFloat(struct ContextState* state)
{
	return state->var->_float;
}
int* getVarIntPtr(struct ContextState* state)
{
	return state->var->_int_p;
}
char** getVarStringPtr(struct ContextState* state)
{
	return state->var->_string_p;
}
float* getVarFloatPtr(struct ContextState* state)
{
	return state->var->_float_p;
}
struct SparseMatrix* getVarLevels(struct ContextState* state)
{
	return state->var->levels;
}


int getStartChildrenSize(struct ContextState* state)
{
	return state->start_children_size;
}
int getParentsSize(struct ContextState* state)
{
	return state->parents_size;
}
int getChildrenSize(struct ContextState* state)
{
	return state->children_size;
}
int getNextsSize(struct ContextState* state)
{
	return state->nexts_size;
}

void setName(struct ContextState* state, struct Names* name)
{
	state->name = name;

}
void setStartChildren(struct ContextState* state, struct Names** start_children)
{
	state->start_children = makeNew(state->start_children, &state->start_children_size, start_children);
	// = start_children;

}
void setParents(struct ContextState* state, struct Names** parents)
{
	state->parents = makeNew(state->parents, &state->parents_size, parents);
}
void setChildren(struct ContextState* state, struct Names** children)
{
	state->children = makeNew(state->children, &state->children_size, children);

}
void setNexts(struct ContextState* state, struct Names** nexts)
{
	state->nexts = makeNew(state->nexts, &state->nexts_size, nexts);

}
void setVar(struct ContextState* state, struct Data* var)
{
	state->var = var;

}


	//struct Names** start_children;
	//int start_children_size;

	//struct Names** parents;
	//int parents_size;


	// no recursion, have an indent on/off var in the stack
	// when the child state is at a higher level than the current state
		// deactivate the indent
	// use last indent on/off value to find out if indents should be on or off
	// (current state, prev item on stack, is_indent_on)

	//struct Names** children;
	//int children_size;

	//struct Names** nexts;
	//int nexts_size;

	//bool (*function_pointer)(struct Names* a, struct SparseMatrix* b);
	//char* function_pointer_name;

	//struct Data* var;

struct ContextState* addFunction(struct ContextState* node,
								bool (*function_pointer)(struct Names* , struct SparseMatrix* ),
							 	 char* function_pointer_name)
{
	setFunctionPointer(node, function_pointer, function_pointer_name);
 	//bool (*x)(struct Names* , struct SparseMatrix* ) = getFunctionPointer(node);
	//node->function_pointer = function_pointer;
	//node->function_pointer_name = function_pointer_name;
	return node;
}




struct ContextState* makeState(struct Names* names)
{

	struct ContextState* state = makeNewState();

	setNames(state, names);
	//printf("%s, %s\n", state->name->strings[0], state->name->strings[1]);


	initializeSizes(state);


	initializeVars(state);

	setIsInt(state, false);
	setIsString(state, false);
	setIsFloat(state, false);
	setIsIntPtr(state, false);
	setIsStringPtr(state, false);
	setIsFloatPtr(state, false);
	setIsLevels(state, false);
	return state;

}
void deleteState(struct ContextState* node)
{
	free(getName(node));
	for(int i = 0; i < getStartChildrenSize(node); i++)
		free(getStartChildren(node)[i]);
	for(int i = 0; i < getParentsSize(node); i++)
		free(getParents(node)[i]);
	for(int i = 0; i < getChildrenSize(node); i++)
		free(getChildren(node)[i]);
	for(int i = 0; i < getNextsSize(node); i++)
		free(getNexts(node)[i]);

}
// add name
struct Names** makeNew(struct Names** handle, int* handle_size, struct Names* add_node)
{
	//printf("here\n");
	// fix
	int size = *handle_size;
	//printf("handkle size: %i\n", size);
	if(size == 0)
	{
		handle = malloc(sizeof(struct Names*));
	}
	else
	{
		struct Names** x = realloc(handle, size * sizeof(struct Names*));
		if(x != NULL)
		{
			handle = x;
		}
		else
		{
			//failure
		}
	}
	//printf("before\n");
	handle[size] = add_node;
	//memcpy(handle + size, add_node, sizeof(struct Names));
	//printf("after \n%s %s\n", handle[0]->strings[0], handle[0]->strings[1]);
	//printf("after\n");

	*handle_size += 1;
	//printf("%i\n", *handle_size);
	return handle;
}
struct ContextState* addNode(struct ContextState* node,
							 int attribute_name,
							 struct Names* add_node)
{
	switch(attribute_name)
	{
		case _StartChildren:
		{
			//printf("here2\n");
			//printf("%s %s\n", add_node->strings[0], add_node->strings[1]);

			//node->start_children = malloc(sizeof(struct Names*));
			setStartChildren(node, &add_node);
			//node->start_children = makeNew(node->start_children, &node->start_children_size, add_node);
			//printf("%s ", node->start_children[0]->strings[0]);
			//printf("%s\n", node->start_children[0]->strings[1]);
			//exit(1);
			break;
		}
		case _Parents:
		{
			//node->parents = malloc(sizeof(struct Names*));
			setParents(node, &add_node);
			//node->parents = makeNew(node->parents, &node->parents_size, add_node);

			break;
		}

		case _Children:
		{
			//node->children = malloc(sizeof(struct Names*));
			setChildren(node, &add_node);
			//node->children = makeNew(node->children, &node->children_size, add_node);

			break;

		}
		case _Nexts:
		{
			//node->nexts = malloc(sizeof(struct Names*));
			setNexts(node, &add_node);
			//node->nexts = makeNew(node->nexts, &node->nexts_size, add_node);
		}
		default:
		{
			// failure
		}

	}

	return node;
}*/
