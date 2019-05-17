#include "hash_table1.h"
#include "state3.h"

static ht_item HT_DELETED_ITEM = {NULL, NULL};
// primes > 128
const int HT_PRIME_1 = 131;
const int HT_PRIME_2 = 137;
const int HT_INITIAL_BASE_SIZE = 50;

void ht_insert(ht_hash_table* ht, const char* key, ContextState* value);
void* ht_search(ht_hash_table* ht, const char* key);
void ht_delete(ht_hash_table* h, const char* key);
ContextState* duplicate(ContextState* item);

static ht_item* ht_new_item(const char* k, ContextState* v)
{
	// v->name gets's messed up when it comes in unless v->name ends in "\\" (for when it ends in t)
	// works
	//printf("v1 %s %lu\n", v->name, strlen(v->name));

	ht_item* i = malloc(sizeof(ht_item));

	i->key = strdup(k);//malloc(strlen (k) + 1);  // Space for length plus nul
    //if (i->key == NULL) return NULL;          // No memory
    //strcpy(i->key, k);
	//memcpy(i->key, k, sizeof(char) * (strlen (k) + 1));
	//i->key = strdup(k);
	// gets messed up
	//printf("v2 %s %lu\n", v->name, strlen(v->name));
	//printf("making a state object\n");
	ContextState* x = duplicate(v);
	//memcpy(x, v, sizeof(ContextState));
	i->value = x; //strdup(v);
	//printf("made object\n");
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
void printHash(ht_hash_table* ht)
{
	printf("size = %i, count = %i, base = %i\n", ht->size, ht->count, ht->base_size);
	//printf("%i\n", &HT_DELETED_ITEM);
	for(int i = 0; i < ht->size; i++)
	{
		printf("item %i\n", i);
		//printf("%x\n", ht->items[i]);
		if(ht->items[i] != 0)
		{
			printf("%i %s\n\n", i,  ht->items[i]->key);

		}
		else
		{
			printf("blank\n\n");
		}
	}
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

void ht_insert(ht_hash_table* ht, const char* key, ContextState* value)
{
	//printf("insert\n");
	const int load = ht->count * 100 / ht->size;
	//printf("load = %i\n", load);

	if(load > 70)
	{
		ht_resize_up(ht);
	}

	printf("inserting value %s\n", value->name);

	ht_item* item = ht_new_item(key, value);

	int index = ht_get_hash(item->key, ht->size, 0);
	//printf("location = %i\n", index);
	ht_item* cur_item = ht->items[index];

	//printf("%i %i\n\n", index, ht->items[index]);

	int i = 1;
	while (cur_item != NULL)
	{
		if(cur_item != &HT_DELETED_ITEM)
		{
			if(strcmp(cur_item->key, key) == 0)
			{
				// if value and cur_item->value are the same object
				// then add to table
				if(value == cur_item->value)
				{
					ht_del_item(cur_item);
					ht->items[index] = item;
					// prove item has been stored successfully

				return;
				}
				
			}
		}
		index = ht_get_hash(item->key, ht->size, i);
		cur_item = ht->items[index];
		i++;
	}

	ht->items[index] = item;
	//printf("%i %s\n\n", index, result->name);
	//printf("done inserting\n");
	//printf("%i %s\n\n", index, ht->items[index]->key);

	ht->count++;
}

void* getValueAt(ht_hash_table* ht, int i)
{
	return ht->items[i]->value;
}
int getIndexOfKey(ht_hash_table* ht, const char* key)
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
				return index;
			}
		}
		index = ht_get_hash(key, ht->size, i);
		item = ht->items[index];
		i++;
	}
	// can't find anything
	return -1;
}
void* ht_search(ht_hash_table* ht, const char* key)
{
	//printf("searching for %s\n", key);
	int index = ht_get_hash(key, ht->size, 0);


	ht_item* item = ht->items[index];

	int i = 1;
	while(item != NULL)
	{
		if(item != &HT_DELETED_ITEM)
		{
			//printf("%i\n", index);
			//printf("element %s, key %s\n", item->key, key);
	//		printf("item %x, deleted tag %x\n", item, &HT_DELETED_ITEM);

			if (strcmp(item->key, key) == 0)
			{
				//printf("done\n");
				//printf("%s\n", item->key);
				//ContextState* result = (ContextState*) item->value;
				// sometimes the name has garbage characters added
				// prints out 'd' or segfaults
				//printf("name: %s\n", result->name );
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