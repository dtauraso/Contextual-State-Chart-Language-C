#include "data.h"
#include "states.h"
struct Data* addInt(int var)
{
	struct Data* variable = malloc(sizeof(struct Data));
	variable->_int = var;
	variable->_is_int = true;
	variable->_is_string = false;
	variable->_is_float = false;
	variable->_is_int_p = false;
	variable->_is_string_p = false;
	variable->_is_float_p = false;
	variable->is_levels = false;

	return variable;
}
struct Data* addString(char* var)
{
	struct Data* variable = malloc(sizeof(struct Data));
	variable->_string = var;
	variable->_is_int = false;
	variable->_is_string = true;
	variable->_is_float = false;
	variable->_is_int_p = false;
	variable->_is_string_p = false;
	variable->_is_float_p = false;
	variable->is_levels = false;

	return variable;
}
struct Data* addFloat(float var)
{
	struct Data* variable = malloc(sizeof(struct Data));
	variable->_float = var;
	variable->_is_int = false;
	variable->_is_string = false;
	variable->_is_float = true;
	variable->_is_int_p = false;
	variable->_is_string_p = false;
	variable->_is_float_p = false;
	variable->is_levels = false;
	return variable;
}

struct Data* addIntPointer(int* var)
{
	struct Data* variable = malloc(sizeof(struct Data));
	variable->_int_p = var;
	variable->_is_int = false;
	variable->_is_string = false;
	variable->_is_float = false;
	variable->_is_int_p = true;
	variable->_is_string_p = false;
	variable->_is_float_p = false;
	variable->is_levels = false;
	return variable;
}

struct Data* addStringPointer(char** var)
{
	struct Data* variable = malloc(sizeof(struct Data));
	variable->_string_p = var;
	variable->_is_int = false;
	variable->_is_string = false;
	variable->_is_float = false;
	variable->_is_int_p = false;
	variable->_is_string_p = true;
	variable->_is_float_p = false;
	variable->is_levels = false;
	return variable;
}

struct Data* addFloatPointer(float* var)
{
	struct Data* variable = malloc(sizeof(struct Data));
	variable->_float_p = var;
	variable->_is_int = false;
	variable->_is_string = false;
	variable->_is_float = false;
	variable->_is_int_p = false;
	variable->_is_string_p = false;
	variable->_is_float_p = true;
	variable->is_levels = false;
	return variable;
}

struct Data* addSparseMatrixLevels(struct SparseMatrix* var)
{
	struct Data* variable = malloc(sizeof(struct Data));
	variable->levels = var;
	variable->_is_int = false;
	variable->_is_string = false;
	variable->_is_float = false;
	variable->_is_int_p = false;
	variable->_is_string_p = false;
	variable->_is_float_p = false;
	variable->is_levels = true;
	return variable;
}
