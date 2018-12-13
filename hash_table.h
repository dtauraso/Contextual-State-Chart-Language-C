#ifndef HASH_TABLE
#define HASH_TABLE
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
/*
hash table
https://github.com/jamesroutley/write-a-hash-table/tree/master/01-introduction
*/

typedef struct
{
	char* key;
	char* value;
} ht_item;

typedef struct
{
	int size;
	int count;
	int base_size;
	ht_item** items;
} ht_hash_table;

// state_name ->  level_id_state_id
struct Names {

	char** strings;
	int strings_size;
};

typedef struct
{
	int level_id;
	int state_id;
} level_id_state_id;



typedef struct
{
	struct Names* key;
	level_id_state_id* value;
} state_name_look_up_entry;

typedef struct
{
	int size;
	int count;
	int base_size;
	state_name_look_up_entry** items;
} state_x_y_hash_table;
#endif
