#include "hash_table.h"

static ht_item HT_DELETED_ITEM = {NULL, NULL};
// primes > 128
const int HT_PRIME_1 = 131;
const int HT_PRIME_2 = 137;
const int HT_INITIAL_BASE_SIZE = 50;

void ht_insert(ht_hash_table* ht, const char* key, const char* value);
char* ht_search(ht_hash_table* ht, const char* key);
void ht_delete(ht_hash_table* h, const char* key);
static ht_item* ht_new_item(const char* k, const char* v)
{
	ht_item* i = malloc(sizeof(ht_item));
	i->key = strdup(k);
	i->value = strdup(v);
	return i;
}

static void ht_del_item(ht_item* i)
{
	free(i->key);
	free(i->value);
	free(i);
}

void ht_del_hash_table(ht_hash_table* ht)
{
	for(int i = 0; i < ht->size; i++)
	{
		ht_item* item = ht->items[i];
		if (item != NULL)
		{
			ht_del_item(item);
		}
	}
	free(ht->items);
	free(ht);
}
/*
 * Return whether x is prime or not
 *
 * Returns:
 *   1  - prime
 *   0  - not prime
 *   -1 - undefined (i.e. x < 2)
 */
int is_prime(const int x)
{
	if(x < 2) {return -1;}
	if(x < 4) {return 1;}
	if((x % 2) == 0) {return 0;}
	for(int i = 3; i <= floor(sqrt((double) x)); i += 2)
	{
		if((x % i) == 0)
		{
			return 0;
		}
	}
	return 1;
}
/*
 * Return the next prime after x, or x if x is prime
 */
 int next_prime(int x)
 {
	 while(is_prime(x) != 1)
	 {
		 x++;
	 }
	 return x;
 }

static ht_hash_table* ht_new_sized(const int base_size)
{
	ht_hash_table* ht = malloc(sizeof(ht_hash_table));
	ht->base_size = base_size;

	ht->size = next_prime(ht->base_size);

	ht->count = 0;
	ht->items = calloc((size_t) ht->size, sizeof(ht_item*));
	return ht;
}

static int ht_hash(const char* s, const int a, const int m)
{
	long hash = 0;
	const int len_s = strlen(s);
	for(int i = 0; i < len_s; i++)
	{
		hash += (long) pow(a, len_s - (i+1)) * s[i];
		hash = hash % m;
	}
	return (int) hash;
}
static int ht_get_hash(const char* s, const int num_buckets, const int attempt)
{
	const int hash_a = ht_hash(s, HT_PRIME_1, num_buckets);
	const int hash_b = ht_hash(s, HT_PRIME_2, num_buckets);
	return (hash_a + (attempt * (hash_b + 1)) % num_buckets);
}
static void ht_resize(ht_hash_table* ht, const int base_size)
{
	if(base_size < HT_INITIAL_BASE_SIZE)
	{
		return;
	}
	ht_hash_table* new_ht = ht_new_sized(base_size);
	for(int i = 0; i < ht->size; i++)
	{
		ht_item* item = ht->items[i];
		if(item != NULL && item != &HT_DELETED_ITEM)
		{
			ht_insert(new_ht, item->key, item->value);
		}
	}
	ht->base_size = new_ht->base_size;
	ht->count = new_ht->count;

	// To delete new_ht, we give it ht's size and items
	const int tmp_size = ht->size;
	ht->size = new_ht->size;
	new_ht->size = tmp_size;

	ht_item** tmp_items = ht->items;
	ht->items = new_ht->items;
	new_ht->items = tmp_items;

	ht_del_hash_table(new_ht);
}
static void ht_resize_up(ht_hash_table* ht)
{
	const int new_size = ht->base_size * 2;
	ht_resize(ht, new_size);
}
static void ht_resize_down(ht_hash_table* ht)
{
	const int new_size = ht->base_size / 2;
	ht_resize(ht, new_size);
}

void ht_insert(ht_hash_table* ht, const char* key, const char* value)
{
	const int load = ht->count * 100 / ht->size;
	if(load > 70)
	{
		ht_resize_up(ht);
	}
	ht_item* item = ht_new_item(key, value);
	int index = ht_get_hash(item->key, ht->size, 0);
	ht_item* cur_item = ht->items[index];
	int i = 1;
	while (cur_item != NULL)
	{
		if(cur_item != &HT_DELETED_ITEM)
		{
			if(strcmp(cur_item->key, key) == 0)
			{
				ht_del_item(cur_item);
				ht->items[index] = item;
				return;
			}
		}
		index = ht_get_hash(item->key, ht->size, i);
		cur_item = ht->items[index];
		i++;
	}
	ht->items[index] = item;
	ht->count++;
}


char* ht_search(ht_hash_table* ht, const char* key)
{
	int index = ht_get_hash(key, ht->size, 0);
	ht_item* item = ht->items[index];
	int i = 1;
	while(item != NULL)
	{
		if(item != &HT_DELETED_ITEM)
		{
			if (strcmp(item->key, key) == 0)
			{
				return item->value;
			}
		}
		index = ht_get_hash(key, ht->size, i);
		item = ht->items[index];
		i++;
	}
	return NULL;
}

void ht_delete(ht_hash_table* ht, const char* key)
{
	const int load = ht->count * 100 / ht->size;
	if(load < 10)
	{
		ht_resize_down(ht);
	}
	int index = ht_get_hash(key, ht->size, 0);
	ht_item* item = ht->items[index];
	int i = 1;
	while(item != NULL)
	{
		if(item != &HT_DELETED_ITEM)
		{
			if(strcmp(item->key, key) == 0)
			{
				ht_del_item(item);
				ht->items[index] = &HT_DELETED_ITEM;
			}
		}
		index = ht_get_hash(key, ht->size, i);
		item = ht->items[index];
		i++;
	}
	ht->count--;
}


 ht_hash_table* ht_new()
 {

 	return ht_new_sized(HT_INITIAL_BASE_SIZE);
 }
 struct Names* makeName2(char* name_1, char* name_2)
 {

 	char** name = malloc(sizeof(char*) * 2);
 	name[0] = name_1;
 	name[1] = name_2;

 	struct Names* names = malloc(sizeof(struct Names));
 	names->strings = malloc(sizeof(char*) * 2);

 	memcpy(names->strings, name, sizeof(char*) * 2);
 	names->strings_size = 2;

 	return names;
 }
struct Names* makeName(char* name)
{
	struct Names* names = malloc(sizeof(struct Names));
	names->strings = malloc(sizeof(char*));
	memcpy(names->strings, name, sizeof(char*));
	names->strings_size = 1;

	return names;

}
struct Names* addName(struct Names* names, char* next_name)
{
	names = realloc(names, sizeof(struct Names) * (names->strings_size + 1));
	memcpy(names->strings[names->strings_size], next_name, sizeof(char*));
	names->strings_size++;
	return names;
}
level_id_state_id* newPoint(int level_id, int state_id)
{
	level_id_state_id* point = malloc(sizeof(level_id_state_id));
	point->level_id = level_id;
	point->state_id = state_id;
	return point;
}
/*
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

*/
static state_name_look_up_entry HT_DELETED_ITEM2 = {NULL, NULL};

state_x_y_hash_table* ht_new_sized2(const int base_size);

state_x_y_hash_table* ht_new2()
{

	return ht_new_sized2(HT_INITIAL_BASE_SIZE);
}
 void ht_insert2(state_x_y_hash_table* ht,
	 struct Names* key,
	 level_id_state_id* value);

state_x_y_hash_table* ht_new_sized2(const int base_size)
 {
 	state_x_y_hash_table* ht = malloc(sizeof(state_x_y_hash_table));
 	ht->base_size = base_size;

 	ht->size = next_prime(ht->base_size);

 	ht->count = 0;
 	ht->items = calloc((size_t) ht->size, sizeof(state_name_look_up_entry*));
 	return ht;
 }


 state_name_look_up_entry* ht_new_item2(
 /*const char* k, const char* v*/
 struct Names* k,
 level_id_state_id* v
)
 {
	 // state_name_look_up_entry
 	state_name_look_up_entry* i = malloc(sizeof(state_name_look_up_entry));
	// need to copy k into i->key
	i->key = k;
	// malloc i->key
	// memcpy(i->key, k, sizeof(state_name))
 	//i->key = strdup(k);
	// need to copy v into i->value
 	//i->value = strdup(v);
	i->value = v;
 	return i;
 }

void ht_del_item2(state_name_look_up_entry* item)
 {
	 /*
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


	 */
	for(int i = 0; i < item->key->strings_size; i++)
	{
		free(item->key->strings[i]);
	}
 	free(item->value);
 	free(item);
 }

 void ht_del_hash_table2(state_x_y_hash_table* ht)
 {
 	for(int i = 0; i < ht->size; i++)
 	{
 		state_name_look_up_entry* item = ht->items[i];
 		if (item != NULL)
 		{
 			ht_del_item2(item);
 		}
 	}
 	free(ht->items);
 	free(ht);
 }

 void ht_resize2(state_x_y_hash_table* ht, const int base_size)
 {
 	if(base_size < HT_INITIAL_BASE_SIZE)
 	{
 		return;
 	}
 	state_x_y_hash_table* new_ht = ht_new_sized2(base_size);
 	for(int i = 0; i < ht->size; i++)
 	{
 		state_name_look_up_entry* item = ht->items[i];
 		if(item != NULL && item != &HT_DELETED_ITEM2)
 		{
 			ht_insert2(new_ht, item->key, item->value);
 		}
 	}
 	ht->base_size = new_ht->base_size;
 	ht->count = new_ht->count;

 	// To delete new_ht, we give it ht's size and items
 	const int tmp_size = ht->size;
 	ht->size = new_ht->size;
 	new_ht->size = tmp_size;

 	state_name_look_up_entry** tmp_items = ht->items;
 	ht->items = new_ht->items;
 	new_ht->items = tmp_items;

 	ht_del_hash_table2(new_ht);
 }

 void ht_resize_up2(state_x_y_hash_table* ht)
 {
 	const int new_size = ht->base_size * 2;
 	ht_resize2(ht, new_size);
 }

 void ht_resize_down2(state_x_y_hash_table* ht)
 {
 	const int new_size = ht->base_size / 2;
 	ht_resize2(ht, new_size);
 }
 static int ht_hash2(struct Names* s, const int a, const int m)
 {
 	long hash = 0;
	for(int j = 0; j < s->strings_size; j++)
	{
		const int len_s = strlen(s->strings[j]);
	 	for(int i = 0; i < len_s; i++)
	 	{
	 		hash += (long) pow(a, len_s - (i+1)) * s->strings[j][i];
	 		hash = hash % m;
	 	}
	}

 	return (int) hash;
 }
 static int ht_get_hash2(struct Names* s, const int num_buckets, const int attempt)
 {
 	const int hash_a = ht_hash2(s, HT_PRIME_1, num_buckets);
 	const int hash_b = ht_hash2(s, HT_PRIME_2, num_buckets);
 	return (hash_a + (attempt * (hash_b + 1)) % num_buckets);
 }
bool compareKeys(struct Names* key_in_table, struct Names* new_key)
{
	// returns true if keys are the same
	if(key_in_table->strings_size != new_key->strings_size)
	{
		return false;
	}
	for(int i = 0 ; i < key_in_table->strings_size; i++)
	{
		if(strcmp(key_in_table->strings[i], new_key->strings[i]) != 0)
		{
			return false;
		}
	}
	return true;
}
void ht_insert2(state_x_y_hash_table* ht, struct Names* key, level_id_state_id* value)
{
	const int load = ht->count * 100 / ht->size;
	if(load > 70)
	{
		ht_resize_up2(ht);
	}
 	state_name_look_up_entry* item = ht_new_item2(key, value);
 	int index = ht_get_hash2(item->key, ht->size, 0);
 	state_name_look_up_entry* cur_item = ht->items[index];
 	int i = 1;
 	while (cur_item != NULL)
 	{
 		if(cur_item != &HT_DELETED_ITEM2)
 		{

 			if(compareKeys(cur_item->key, key))
 			{
 				ht_del_item2(cur_item);
 				ht->items[index] = item;
 				return;
 			}
 		}
		// todo: fix for Name*
 		index = ht_get_hash2(item->key, ht->size, i);
 		cur_item = ht->items[index];
 		i++;
 	}
 	ht->items[index] = item;
 	ht->count++;
 }

 level_id_state_id* ht_search2(state_x_y_hash_table* ht, struct Names* key)
 {
 	int index = ht_get_hash2(key, ht->size, 0);
 	state_name_look_up_entry* item = ht->items[index];
 	int i = 1;
 	while(item != NULL)
 	{
 		if(item != &HT_DELETED_ITEM2)
 		{
 			if (compareKeys(item->key, key))
 			{
 				return item->value;
 			}
 		}
 		index = ht_get_hash2(key, ht->size, i);
 		item = ht->items[index];
 		i++;
 	}
 	return NULL;
 }
 void ht_delete2(state_x_y_hash_table* ht, struct Names* key)
 {
 	const int load = ht->count * 100 / ht->size;
 	if(load < 10)
 	{
 		ht_resize_down2(ht);
 	}
 	int index = ht_get_hash2(key, ht->size, 0);
 	state_name_look_up_entry* item = ht->items[index];
 	int i = 1;
 	while(item != NULL)
 	{
 		if(item != &HT_DELETED_ITEM2)
 		{
 			if(compareKeys(item->key, key))
 			{
 				ht_del_item2(item);
 				ht->items[index] = &HT_DELETED_ITEM2;
 			}
 		}
 		index = ht_get_hash2(key, ht->size, i);
 		item = ht->items[index];
 		i++;
 	}
 	ht->count--;
 }
