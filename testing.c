#include "state3.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


/*
typedef struct ListOfNames
{

	int list_of_names_size;  // put here cause altering list_of_names messes it up
	char*** list_of_names;
	int* names_sizes;



}ListOfNames;
*/

int main()
{
	char* a = "child";
	char* b = "nexts";
	char* c = "sibling";
	char* d = "new_parent";
	int number_of_lists_of_strings = 2;
	int size_of_string_list = 2;
	ListOfNames* x = malloc(sizeof(ListOfNames));
	x->list_of_names = malloc(sizeof(char**) * number_of_lists_of_strings);
	x->names_sizes = malloc(sizeof(int) * size_of_string_list);

	printf("here\n");
	x->list_of_names[0] = malloc(sizeof(char*) * number_of_lists_of_strings);
	x->names_sizes[0] = size_of_string_list;
	x->list_of_names[0][0] = malloc(sizeof(char) * strlen(a));
	memcpy(x->list_of_names[0][0], a, sizeof(char) * strlen(a));
	x->list_of_names[0][1] = malloc(sizeof(char) * strlen(b));
	memcpy(x->list_of_names[0][1], b, sizeof(char) * strlen(b));

	x->list_of_names[1] = malloc(sizeof(char*) * number_of_lists_of_strings);
	x->names_sizes[1] = size_of_string_list;

	x->list_of_names[1][0] = malloc(sizeof(char) * strlen(c));
	memcpy(x->list_of_names[1][0], c, sizeof(char) * strlen(c));
	x->list_of_names[1][1] = malloc(sizeof(char) * strlen(d));
	memcpy(x->list_of_names[1][1], d, sizeof(char) * strlen(d));
	printf("%i, %i\n", x->names_sizes[0], x->names_sizes[1]);
	return 0;
}