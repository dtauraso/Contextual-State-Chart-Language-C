#ifndef LISPNODE
#define LISPNODE
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "jsmn/jsmn.h"

// for collecting a list of lists of strings for ContextState

typedef struct LispNode
{
	void* value;
	struct LispNode* next;

	int value_type;
	int count;
	int call_count;

}LispNode;

LispNode* cons(void* data, void* link, int data_type, int count, int call_count);
char* lispNodeType(int type_value);
void printLispNodes(LispNode* root, int indent_level);
void deleteLispNodes(LispNode* root);
LispNode* strings(int* i, jsmntok_t tokens[], const char* input, int number_of_strings_left, int call_count);
LispNode* array(int* i, jsmntok_t tokens[], const char* input, int call_count, int token_count);
LispNode* cons(void* data, void* link, int data_type, int count, int call_count);
LispNode* makeLispNode();

//////
char* makeSpaces(int indent_level);
char* collectChars(jsmntok_t token, const char* input);
char* tokenType(jsmntok_t token);
bool tokenIsKeyWord(char* token_string);




#endif