#ifndef HASH_TABLE
#define HASH_TABLE
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <math.h>
/*
hash table
https://github.com/jamesroutley/write-a-hash-table/tree/master/01-introduction
*/
typedef struct
{
	char* key;
	void* value;
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
	ht_item* item;
	int location_in_table;
}item_found;


typedef struct Node
{
	char letter;
	struct Node** next;
}node;

typedef struct
{
	ht_hash_table* dict;

	// array of element references to store the order of entries
	// this allows entries to e accessed by index as well as by hash function

	ht_item** elements;
} ordered_dict;
// array dict
// hash table
// array holding the items in the order they are entered in for quick access(know what option we want) and efficient searching(know that the option is there for easy accessing)
#endif