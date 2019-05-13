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
	char* value;
} ht_item;

typedef struct
{
	int size;
	int count;
	int base_size;
	ht_item** items;
} ht_hash_table;


#endif