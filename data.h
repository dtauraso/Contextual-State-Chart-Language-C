#ifndef DATA
#define DATA
#include "standard_headers.h"
struct Data {

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
	bool is_levels;
};
#endif
