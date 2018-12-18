#ifndef HASH_TABLE
#define HASH_TABLE
#include "standard_headers.h"
#include "state.h"
/*
hash table
https://github.com/jamesroutley/write-a-hash-table/tree/master/01-introduction
*/
// state_name ->  level_id_state_id
struct Names {

	char** strings;
	int strings_size;
};
struct SparseMatrix {
	struct ContextState** state_list;//[max_states];
	int state_population;   // needed so when visiting the level for the nth time, not resetting the state_id back to 0(as there are now states in this level)
};
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
