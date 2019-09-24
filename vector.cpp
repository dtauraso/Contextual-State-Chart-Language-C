#include "vector.h"
/*
typedef struct Vector
{
	void** values;
	int size;
	int population;


}Vector;
*/enum types{integer, _string, trie_node_2};

struct TrieNode2;
void* getValue(TrieNode2* node);

Vector* initVector()
{
	Vector* new_container = (Vector*) malloc(sizeof(Vector));
	new_container->values = NULL;
	new_container->size = 0;
	new_container->population = 0;
	return new_container;
}
Vector* initVectorSize(int size)
{
	Vector* new_container = (Vector*) malloc(sizeof(Vector) * size);
	new_container->values = (void**) malloc(sizeof(void*) * size);
	new_container->size = size;
	new_container->population = 0;
	return new_container;
}
bool deleteVector(Vector* container)
{
	for(int i = 0; i < container->population; i++)
	{
		free(container->values[i]);
		container->values[i] = NULL;
	}
	free(container->values);
	container->values = NULL;
	return true;
}

int getLastIndex(Vector* container)
{
	return container->population - 1;
}
// for unsorted only
void* getItem(Vector* container, int i)
{
	//printf("getting item %i, %i\n", i, container->population);
	if(i < container->population && i >= 0)
	{
		//printf("item |%x|\n", container->values[i]);
		return container->values[i];
	}
	else
	{
		//printf("out of bounds\n");
		return NULL;
	}
}
void setItemToNull(Vector* container, int i)
{
	if(i < container->population && i >= 0)
	{
		//printf("item |%x|\n", container->values[i]);
		container->values[i] = NULL;
	}
	else
	{
		//printf("out of bounds\n");
		return;
	}
}
int getPopulation(Vector* container)
{
	return container->population;
}
void append(Vector* container, void* element)
{
	if(container != NULL)
	{
		//printf("push %i, size %i\n", container->population, container->size);

		if(container->size == 0)
		{
			//printf("insert 0\n");
			container->values = (void**) malloc(sizeof(void*));
			container->size = 1;
			container->values[0] = element;
			container->population = 1;

		}
		else if(container->population == container->size)
		{

			//printf("size %i\n", container->size);

			container->size *= 2;

			container->values = (void**) realloc(container->values, sizeof(void*) * container->size);


			container->values[container->population] = element;
			container->population += 1;

			
		}
		else if(container->population < container->size)
		{
			//printf("regular\n");

			container->values[container->population] = element;
			container->population += 1;

		}
		//printf("result\n");
		//Print(container);
	}

}
bool popItem(Vector* container)
{
	if(container != NULL)
	{
		//printf("here %i\n", container->population - 1);
		//		Print(container);

		int index = container->population - 1;
		free(container->values[index]);
		container->values[index] = NULL;

		container->population -= 1;
		//Print(container);
		return true;
	}
	return false;
}
void incrementTopInt(Vector* container)
{
	if(container != NULL)
	{
		//printf("here %i\n", container->population);
		//		Print(container);
		if(container->population > 0)
		{
			int index = container->population - 1;
			//free(container->values[index]);
			//container->values[index] = NULL;
			*((int*) container->values[index]) += 1;
			//container->population -= 1;
			//Print(container);

		}
	}
}
bool deleteItem(Vector* container, int index)
{
	// needs a special delete function for the object type
	//printf("delete at %i\n", index);
	// set container[index] to null
	// shift all values from [index + 1, end] to the left by 1
	if(container != NULL)
	{
		//printf("%i\n", container->population);
		//printf("%i\n", index);
		//int* x = (int*) container->values[index];
		//printf("%i\n", *x);
		free(container->values[index]);
		container->values[index] = NULL;
		if(index < container->population)
		{
			for(int i = index + 1; i < container->population; i++)
			{
				container->values[i - 1] = container->values[i];

				container->values[i] = NULL;

			}
			container->population--;
		}
		return true;
	}
	return false;
}
bool deleteAllItems(Vector* container)
{
	// assuems all elements are primitives
	if(container != NULL)
	{
		for(int i = 0; i < container->population; i++)
		{
			free(container->values[i]);
			container->values[i] = NULL;
		}
	}
	free(container->values);
	container->values = NULL;
	free(container);
	container = NULL;
	return true;
}
void shiftItems(Vector* container, int index)
{
	if(container != NULL)
	{
		if(index < container->population)
		{
			for(int i = index + 1; i < container->population; i++)
			{
				container->values[i - 1] = container->values[i];

				container->values[i] = NULL;

			}
			container->population--;
		}
	}
	
}

void shiftLeft(Vector* container, int start, int end)
{
	//printf("insert location bounds %i %i\n", start, end);
	// assume start >= end
	// assume container size > start+1
	for(int i = start + 1; i >= end; i--)
	{
		container->values[i] = container->values[i - 1];

	}
	//container->values[start] = NULL;
}

bool insertItem(Vector* container, void* element, int insert_location, int type)
{
	// assume element to insert was not already in container
	// does container->values[index] exist?
	if(container != NULL)
	{
		// size 0
		if(container->size == 0)
		{
			// make new position and set
			container->values = (void**) malloc(sizeof(void*));
			container->size = 1;
			container->values[0] = element;
			container->population = 1;
			return true;
		}
		// only do this if item isn't already in the container
		//Match* match_status = searchItem(container, element, type);
		//if(match_status != NULL)
		//{
			//if(match_status->exists)
			//{
			//	return true;		
			//}
			//else
			//{

				int j = insert_location;
				//if(searchItem(container, element, type))
				if(container->population == container->size)
				{
					// reallocate and shift away from position
					container->size *= 2;

					container->values = (void**) realloc(container->values,
														 sizeof(void*) * container->size);

					
				}
				//printf("insert location bounds %i %i\n", container->population - 1, j);
				shiftLeft(container, container->population - 1, j);
				container->values[j] = element;
				container->population++;
				return true;
			//}
		//}
		
	}
	return false;
}

/*
typedef struct Match
{
	bool exists;
	int index;
}Match;

*/
Match* initMatch(int index, bool exists)
{
	Match* my_match = (Match*) malloc(sizeof(Match));

	my_match->exists = exists;
	my_match->index = index;

	return my_match;
}
bool isEqualInt(void* a, void* b)
{
	if(a != NULL && b != NULL)
	{
		return *((int*) a) == *((int*) b);
	}
	return false;
}
bool isEqualString(void* a, void* b)
{
	if(a != NULL && b != NULL)
	{
		return *((string*) a) == *((string*) b);
	}
	return false;

}
bool isGreaterThanOrEqualInt(void* a, void* b)
{
	if(a != NULL && b != NULL)
	{
		return *((int*) a) >= *((int*) b);
	}
	return false;

}
bool isGreaterThanOrEqualString(void* a, void* b)
{
	if(a != NULL && b != NULL)
	{
		return *((string*) a) >= *((string*) b);
	}
	return false;

}
bool isGreaterThanInt(void* a, void* b)
{
	if(a != NULL && b != NULL)
	{
		return *((int*) a) > *((int*) b);
	}
	return false;

}
bool isGreaterThanString(void* a, void* b)
{
	if(a != NULL && b != NULL)
	{
		return *((string*) a) > *((string*) b);
	}
	return false;

}
bool isLessThanInt(void* a, void* b)
{
	if(a != NULL && b != NULL)
	{
		return *((int*) a) < *((int*) b);
	}
	return false;

}
bool isLessThanString(void* a, void* b)
{
	if(a != NULL && b != NULL)
	{
		return *((string*) a) < *((string*) b);
	}
	return false;

}
int searchItem(Vector* container, void* element, int type)
{
	// needs to return wether item was found
	if(container != NULL)
	{
		int low = 0;
		int high = container->population;
		int mid = (low + high) / 2;
		//printf("%i, %i\n", integer, _string);
		while((low <= high) && (mid < container->population))
		{
			//printf("%i, %i, %i\n", low, high, mid);
			bool is_less_than = false;
			switch(type)
			{
				case integer:
				{
					// isEqualString( element,
									// ((objec*) dict_container->values[edges->values[mid]])->value)
					if(isEqualInt(element, container->values[mid]))
					{
						return mid;
					}
					is_less_than = isLessThanInt(element, container->values[mid]);
					//printf("here %i\n", is_less_than);

					break;
				}
				case _string:
				{
					if(isEqualString(element, container->values[mid]))
					{
						return mid;
					}
					is_less_than = isLessThanString(element, container->values[mid]);
					break;
				}
				default:
				{

				}
			}
			if(is_less_than)
			{
				high = mid - 1;
			}
			else
			{
				low = mid + 1;
			}
			mid = (low + high) / 2;


		}

		//printf("item not found %i\n", low);
		// item didn't get found
		/*
		if(low == container->population )
            return -1 * container->population;
        if(nums[low] < target) return -(low + 1);
        return -(low);
		*/
		if(low == container->population)
		{
			return -1 * container->population;
		}
		else if(low < container->population)
		{
			switch(type)
			{
				case integer:
				{
					if(isGreaterThanInt(element, container->values[low]))
					{
						return -1 * (low + 1);
					}
				}
				case _string:
				{
					if(isGreaterThanString(element, container->values[low]))
					{
						return -1 * (low + 1);
					}
				}
				default:
				{

				}
			}
		}

		return -1 * low;
	}
	return -200;
	
}
/*
void* findItem(Vector* container, void* element, int type)
{
	if(container != NULL)
	{
		Match* my_match = searchItem(container, element, type);
		if(my_match != NULL)
		{
			if(my_match->exists)
			{
				return container->values[my_match->index];
			}
		}
	}
	return NULL;
}*/
	/*
bool removeItem(Vector* container, void* element, int type)
{
	if(container != NULL)
	{
		Match* my_match = searchItem(container, element, type);
		if(my_match != NULL)
		{
			if(my_match->exists)
			{
				//return container->values[my_match->index];
				return deleteItem(container, my_match->index);

			}
		}
	}
	return false;
}*/
Match* searchItemTrieDict(Vector* trie_tree_dict, Vector* edges, void* element, int type, int dict_type)
{
	//printf("we are searching the trie %i, %i, %x\n", type, dict_type, edges);

	// needs to return wether item was found
	if(edges != NULL)
	{
		int low = 0;
		int high = edges->population;
		//printf("high %i\n", high);
		if(high == 0)
		{
			return NULL;
		}
		// if no items return a no match and items doesn't exists
		int mid = (low + high) / 2;
		//printf("%i, %i\n", integer, _string);
		while((low <= high) && (mid < edges->population))
		{
			//printf("%i, %i, %i\n", low, high, mid);
			bool is_less_than = false;
			// type of edge
			switch(type)
			{
				case integer:
				{

					switch(dict_type)
					{
						case trie_node_2:
						{
							//printf("got here\n");
							//printf("%s, %s\n", ((string*) element)->c_str(),

							//( (string*) ((TrieNode2*) trie_tree_dict->values[   *((int*) edges->values[mid]) ])->value)->c_str()  );
							if(isEqualString(element,

					getValue((TrieNode2*) trie_tree_dict->values[   *((int*) edges->values[mid])  ])
								))
							{
								printf("found it\n");
								return initMatch(*((int*) edges->values[mid]), 1);
							}
							is_less_than = isLessThanInt(element,
					getValue((TrieNode2*) trie_tree_dict->values[ 	*((int*) edges->values[mid]) 	])




								);

							break;
						}
						default:
						{

						}
					}
					// isEqualString( element,
									// ((objec*) dict_container->values[edges->values[mid]])->value)
					//if(isEqualInt(element, container->values[mid]))
					//{
					//	return initMatch(mid, 1);
					//}
					//is_less_than = isLessThanInt(element, container->values[mid]);
					//printf("here %i\n", is_less_than);

					break;
				}
				//case _string:
				//{
				//	if(isEqualString(element, container->values[mid]))
				//	{
				//		return initMatch(mid, 1);
				//	}
				//	is_less_than = isLessThanString(element, container->values[mid]);
				//	break;
				//}
				default:
				{

				}
			}
			if(is_less_than)
			{
				high = mid - 1;
			}
			else
			{
				low = mid + 1;
			}
			mid = (low + high) / 2;


		}
		//printf("item not found %i\n", low);
		// item didn't get found
		/*
		if(low == container->population)
		{
			return initMatch(container->population, 0);
		}
		else if(low < container->population)
		{
			switch(type)
			{
				case integer:
				{
					if(isGreaterThanOrEqualInt(element, container->values[low]))
					{
						return initMatch(low, 0);
					}
				}
				case _string:
				{
					if(isGreaterThanOrEqualString(element, container->values[low]))
					{
						return initMatch(low, 0);
					}
				}
				default:
				{

				}
			}
		}*/
		return initMatch(low, 0);
	}
	return NULL;
	
}

int searchItemTrieDict2(Vector* trie_tree_dict, Vector* edges, void* element, int type, int dict_type)
{
	//printf("we are searching the trie %i, %i, %x\n", type, dict_type, edges);

	// needs to return wether item was found
	if(edges != NULL)
	{
		int low = 0;
		int high = edges->population;
		//printf("high %i\n", high);
		if(high == 0)
		{
			return 0;
		}
		// if no items return a no match and items doesn't exists
		int mid = (low + high) / 2;
		//printf("%i, %i\n", integer, _string);
		while((low <= high) && (mid < edges->population))
		{
			// printf("%i, %i, %i\n", low, high, mid);
			bool is_less_than = false;
			// type of edge
			switch(type)
			{
				case integer:
				{

					switch(dict_type)
					{
						case trie_node_2:
						{
							// printf("got here\n");
							int word_id = *((int*) edges->values[mid]);
							void* value_from_trie_node_2 = getValue((TrieNode2*) trie_tree_dict->values[    word_id  ]);
							string string_from_trie_node_2 = *(string*) value_from_trie_node_2;
							// printf("%s, %s\n", ((string*) element)->c_str(), string_from_trie_node_2.c_str()  );

							if(isEqualString(element, value_from_trie_node_2))
							{
								// printf("found it\n");
								return *((int*) edges->values[mid]);
							}
							is_less_than = isLessThanInt(element, value_from_trie_node_2);

							break;
						}
						default:
						{

						}
					}
					// isEqualString( element,
									// ((objec*) dict_container->values[edges->values[mid]])->value)
					//if(isEqualInt(element, container->values[mid]))
					//{
					//	return initMatch(mid, 1);
					//}
					//is_less_than = isLessThanInt(element, container->values[mid]);
					//printf("here %i\n", is_less_than);

					break;
				}
				//case _string:
				//{
				//	if(isEqualString(element, container->values[mid]))
				//	{
				//		return initMatch(mid, 1);
				//	}
				//	is_less_than = isLessThanString(element, container->values[mid]);
				//	break;
				//}
				default:
				{

				}
			}
			if(is_less_than)
			{
				high = mid - 1;
			}
			else
			{
				low = mid + 1;
			}
			mid = (low + high) / 2;


		}
		// the entries are sorted, but not the items they point to
		// the entries should be in the order that the items they point to are in sorted order
		// printf("item not found %i\n", low);
		// item didn't get found
		
		/*
		if(low == container->population )
            return -1 * container->population;
        if(nums[low] < target) return -(low + 1);
        return -(low);
		*/
		// the trie tree or the edges?
		if(low == edges->population)
		{
			return -1 * edges->population;
		}
		else if(low < edges->population)
		{
			int word_id = *((int*) edges->values[low]);
			void* value_from_trie_node_2 = getValue((TrieNode2*) trie_tree_dict->values[    word_id  ]);

			switch(type)
			{
				case integer:
				{
					if(isGreaterThanInt(element, value_from_trie_node_2))
					{
						return -1 * (low + 1);
					}
				}
				case _string:
				{
					if(isGreaterThanString(element, value_from_trie_node_2))
					{
						return -1 * (low + 1);
					}
				}
				default:
				{

				}
			}
		}

		return -1 * low;
	}
	return -200;
	
}
void Print(Vector* container)
{
	//printf("printing container pop %i, size %i\n", container->population, container->size);
	for(int i = 0; i < container->population; i++)
	{
		//printf("i %i\n", i);
		if(container->values[i] == NULL)
		{
			printf("|NULL|\n");
		}
		else
		{
			//printf("|%x|", container->values[i]);
			void* a = container->values[i];
			int* b = (int*) a;
			printf("|%i|", *b);
			
			//printf("|item|");
		}
	}
	if(container->population == 0)
	{
		printf("none");
	}
	printf("\n\n");

}
void printStrings(Vector* container)
{
	//printf("printing container pop %i, size %i\n", container->population, container->size);
	for(int i = 0; i < container->population; i++)
	{
		//printf("i %i\n", i);
		if(container->values[i] == NULL)
		{
			printf("|NULL|\n");
		}
		else
		{
			//printf("|%x|", container->values[i]);
			void* a = container->values[i];
			string* b = (string*) a;
			printf("|%s|", (*b).c_str() );
			
			//printf("|item|");
		}
	}
	printf("\n");

}

void test()
{
	// make a vector
	Vector* my_vector = initVector();

	// add a list of numbers

	int* a = (int*) malloc(sizeof(int));
	*a = 0;
	append(my_vector, a);
	Print(my_vector);
	int* b = (int*) malloc(sizeof(int));
	*b = 1;
	append(my_vector, b);
	Print(my_vector);

	int* c = (int*) malloc(sizeof(int));
	*c = 2;
	append(my_vector, c);
	Print(my_vector);

	int* d = (int*) malloc(sizeof(int));
	*d = 2;
	append(my_vector, d);
	Print(my_vector);


	deleteItem(my_vector, 1);
	Print(my_vector);
	deleteItem(my_vector, 2);
	Print(my_vector);

	deleteItem(my_vector, 0);
	Print(my_vector);

	deleteItem(my_vector, 0);
	Print(my_vector);	
	/*
	for(int i = 0; i < 5; i++)
	{
		printf("inserting %i\n", i);
		int* j = &i;
		append(my_vector, j, 0);
		Print(my_vector);
		//printf("element added %i\n", (int) my_vector->values[i]);
	}
	printf("here\n");
	for(int i = 0; i < 5; i++)
	{
		if(my_vector->values[i] == NULL)
		{
			printf("problem\n");
		}
		void* a = my_vector->values[i];
		int* b = (int*) a;
		printf("%i\n", *b);
	}*/

	// erase a list of numbers
}

/*
void testSorted()
{
	// make a vector
	Vector* my_vector = initVector();

	// add a list of numbers

	int* a = (int*) malloc(sizeof(int));
	*a = 0;
	printf("inserting %i\n", *a);


	insertItem(my_vector, a, 0);

	//append(my_vector, a);
	Print(my_vector);
	//exit(1);
	int* b = (int*) malloc(sizeof(int));
	*b = 1;

	printf("inserting %i\n", *b);

	insertItem(my_vector, b, 0);

	//append(my_vector, b);
	Print(my_vector);
	//exit(1);
	int* c = (int*) malloc(sizeof(int));
	*c = 2;
	printf("inserting %i\n", *c);
	insertItem(my_vector, c, 0);

	//append(my_vector, c);
	Print(my_vector);

	int* d = (int*) malloc(sizeof(int));
	*d = 2;
	printf("inserting %i\n", *d);
	insertItem(my_vector, d, 0);

	//append(my_vector, d);
	Print(my_vector);

	int* e = (int*) malloc(sizeof(int));
	*e = 3;
	printf("inserting %i\n", *e);
	insertItem(my_vector, e, 0);

	Print(my_vector);

	int* f = (int*) malloc(sizeof(int));
	*f = -1;
	printf("inserting %i\n", *f);
	insertItem(my_vector, f, 0);

	Print(my_vector);

	int* g = (int*) malloc(sizeof(int));
	*g = 10;
	printf("inserting %i\n", *g);
	insertItem(my_vector, g, 0);

	Print(my_vector);

	int* h = (int*) malloc(sizeof(int));
	*h = 6;
	printf("inserting %i\n", *h);
	insertItem(my_vector, h, 0);

	Print(my_vector);




	// search for item
	int* i = (int*) malloc(sizeof(int));
	*i = 2;
	printf("searching for 2 and found %i\n", *((int*) findItem(my_vector, i, 0)));


	int* j = (int*) malloc(sizeof(int));
	*j = -1;
	printf("searching for -1 and found %i\n", *((int*) findItem(my_vector, j, 0)));

	int* k = (int*) malloc(sizeof(int));
	*k = 10;
	printf("searching for 10 and found %i\n", *((int*) findItem(my_vector, k, 0)));


	// delete all items in different positions

	int* l = (int*) malloc(sizeof(int));
	*l = 6;
	printf("removing %i\n", *l);
	removeItem(my_vector, l, 0);

	Print(my_vector);

	int* m = (int*) malloc(sizeof(int));
	*m = -1;
	printf("removing %i\n", *m);
	removeItem(my_vector, m, 0);

	Print(my_vector);


	int* n = (int*) malloc(sizeof(int));
	*n = 10;
	printf("removing %i\n", *n);
	removeItem(my_vector, n, 0);

	Print(my_vector);

	int* o = (int*) malloc(sizeof(int));
	*o = 0;
	printf("removing %i\n", *o);
	removeItem(my_vector, o, 0);

	Print(my_vector);

	int* p = (int*) malloc(sizeof(int));
	*p = 2;
	printf("removing %i\n", *p);
	removeItem(my_vector, p, 0);

	Print(my_vector);

	int* q = (int*) malloc(sizeof(int));
	*q = 1;
	printf("removing %i\n", *q);
	removeItem(my_vector, q, 0);

	Print(my_vector);

	int* r = (int*) malloc(sizeof(int));
	*r = 3;
	printf("removing %i\n", *r);
	removeItem(my_vector, r, 0);

	Print(my_vector);
	
	deleteItem(my_vector, 1);
	Print(my_vector);
	deleteItem(my_vector, 2);
	Print(my_vector);

	deleteItem(my_vector, 0);
	Print(my_vector);

	deleteItem(my_vector, 0);
	Print(my_vector);
	*
	
	for(int i = 0; i < 5; i++)
	{
		printf("inserting %i\n", i);
		int* j = &i;
		append(my_vector, j, 0);
		Print(my_vector);
		//printf("element added %i\n", (int) my_vector->values[i]);
	}
	printf("here\n");
	for(int i = 0; i < 5; i++)
	{
		if(my_vector->values[i] == NULL)
		{
			printf("problem\n");
		}
		void* a = my_vector->values[i];
		int* b = (int*) a;
		printf("%i\n", *b);
	}

	// erase a list of numbers
}*/
/*
void printMultiwayLinesNodesInContainer(Vector* container)
{
	for(int i = 0; i < container->population; i++)
	{
		//printf("i %i\n", i);
		if(container->values[i] == NULL)
		{
			printf("|NULL|\n");
		}
		else
		{
			printf("i %i\n", i);
			//printf("|%x|", container->values[i]);
			//void* a = container->values[i];
			MultiwayLinesNode* node = getMultiwayLinesNode(getItem(container, i));
			printf("%s\n", node->line.c_str());

			printf("parent %i\n", node->parent_id);

			printf("children\n");
			for(int j = 0; j < node->children_ids->population; j++)
			{
				printf("%i\n", *getInt(getItem(node->children_ids, j)));
			}
			printf("\n\n");
			//int* b = (int*) a;
			//printf("|%i|\n", *b);
			
			//printf("|item|");
		}
	}
}*/

Vector* addStringToVector1(string string_1)
{
	Vector* list_of_strings_1 = initVector();

	string* string_1_ptr = (string*) malloc(sizeof(string));
	*string_1_ptr = string_1;
	append(list_of_strings_1, string_1_ptr);
	return list_of_strings_1;
}

Vector* addStringToVector2(string string_1, string string_2)
{
	Vector* list_of_strings_1 = initVector();

	string* string_1_ptr = (string*) malloc(sizeof(string));
	*string_1_ptr = string_1;
	append(list_of_strings_1, string_1_ptr);

	string* string_2_ptr = (string*) malloc(sizeof(string));
	*string_2_ptr = string_2;

	append(list_of_strings_1, string_2_ptr);
	return list_of_strings_1;
}
Vector* addStringToVector3(string string_1, string string_2, string string_3)
{
	Vector* list_of_strings_1 = initVector();

	string* string_1_ptr = (string*) malloc(sizeof(string));
	*string_1_ptr = string_1;
	append(list_of_strings_1, string_1_ptr);

	string* string_2_ptr = (string*) malloc(sizeof(string));
	*string_2_ptr = string_2;

	append(list_of_strings_1, string_2_ptr);

	string* string_3_ptr = (string*) malloc(sizeof(string));
	*string_3_ptr = string_3;

	append(list_of_strings_1, string_3_ptr);

	return list_of_strings_1;
}

Vector* combineVectors(Vector* source_1, Vector* source_2)
{
	Vector* list_of_lists_of_strings = initVector();

	append(list_of_lists_of_strings, source_1);

	append(list_of_lists_of_strings, source_2);

	return list_of_lists_of_strings;

}