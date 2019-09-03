#ifndef DATA
#define DATA
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
#endif