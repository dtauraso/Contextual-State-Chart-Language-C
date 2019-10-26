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
void* TrieNode2GetValue(TrieNode2* node);

Vector* VectorInitVector()
{
	// printf("here\n");
	Vector* new_container = (Vector*) malloc(sizeof(Vector));
	new_container->values = NULL;
	new_container->size = 0;
	new_container->population = 0;
	return new_container;
}
Vector* VectorInitVectorSize(int size)
{
	Vector* new_container = (Vector*) malloc(sizeof(Vector) * size);
	new_container->values = (void**) malloc(sizeof(void*) * size);
	new_container->size = size;
	new_container->population = 0;
	return new_container;
}
bool VectorDeleteVector(Vector* container)
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

int VectorGetLastIndex(Vector* container)
{
	return container->population - 1;
}
// for unsorted only
void* VectorGetItem(Vector* container, int i)
{
	if(container != NULL)
	{
		// printf("getting item %i, %i\n", i, container->population);
		if(container->population == 0)
		{
			printf("container is empty\n");
			return NULL;
		}
		else if(i < container->population && i >= 0)
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
	return NULL;

}
void VectorSetItemToNull(Vector* container, int i)
{
	// very unsafe to use
	// only use if the population size has already been adjusted
	//printf("set to null\n");
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
int VectorGetPopulation(Vector* container)
{
	return container->population;
}
void VectorAppendInt(Vector* container, int element)
{
	int* element_ptr = (int*) malloc(sizeof(int));
	*element_ptr = element;
	VectorAppend(container, element_ptr);
}
void VectorAppend(Vector* container, void* element)
{
	if(container != NULL)
	{
		//printf("TrieTreePush %i, size %i\n", container->population, container->size);

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
		//VectorPrint(container);
	}

}
bool VectorPopItem(Vector* container)
{
	if(container != NULL)
	{
		//printf("here %i\n", container->population - 1);
		//VectorPrint(container);

		int index = container->population - 1;
		free(container->values[index]);
		container->values[index] = NULL;

		container->population -= 1;
		//VectorPrint(container);
		return true;
	}
	return false;
}
bool VectorPopFirst(Vector* container)
{
	return VectorDeleteItem(container, 0);
}
void VectorIncrementTopInt(Vector* container)
{
	if(container != NULL)
	{
		//printf("here %i\n", container->population);
		//		VectorPrint(container);
		if(container->population > 0)
		{
			int index = container->population - 1;
			//free(container->values[index]);
			//container->values[index] = NULL;
			*((int*) container->values[index]) += 1;
			//container->population -= 1;
			//VectorPrint(container);

		}
	}
}
bool VectorDeleteItem(Vector* container, int index)
{
	// needs a special delete function for the object type
	// printf("delete at %i\n", index);
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
			// printf("%i %i\n", index + 1, container->population);
			for(int i = index + 1; i < container->population; i++)
			{
				container->values[i - 1] = container->values[i];

				container->values[i] = NULL;

			}
			// VectorPrint(container);

			container->population--;
			// printf("%i\n", container->population);
		}
		return true;
	}
	return false;
}
bool VectorDeleteAllItems(Vector* container)
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
void VectorShiftItems(Vector* container, int index)
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

void VectorShiftLeft(Vector* container, int start, int end)
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




void VectorPrint(Vector* container)
{
	if(container != NULL)
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
	else
	{
		printf("empty container\n");
	}
	

}
void VectorPrintStrings(Vector* container)
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

void VectorTest()
{
	// make a vector
	Vector* my_vector = VectorInitVector();

	// add a list of numbers

	int* a = (int*) malloc(sizeof(int));
	*a = 0;
	VectorAppend(my_vector, a);
	VectorPrint(my_vector);
	int* b = (int*) malloc(sizeof(int));
	*b = 1;
	VectorAppend(my_vector, b);
	VectorPrint(my_vector);

	int* c = (int*) malloc(sizeof(int));
	*c = 2;
	VectorAppend(my_vector, c);
	VectorPrint(my_vector);

	int* d = (int*) malloc(sizeof(int));
	*d = 2;
	VectorAppend(my_vector, d);
	VectorPrint(my_vector);


	VectorDeleteItem(my_vector, 1);
	VectorPrint(my_vector);
	VectorDeleteItem(my_vector, 2);
	VectorPrint(my_vector);

	VectorDeleteItem(my_vector, 0);
	VectorPrint(my_vector);

	VectorDeleteItem(my_vector, 0);
	VectorPrint(my_vector);	
	/*
	for(int i = 0; i < 5; i++)
	{
		printf("inserting %i\n", i);
		int* j = &i;
		VectorAppend(my_vector, j, 0);
		VectorPrint(my_vector);
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


Vector* VectorAddStringToVector1(string string_1)
{
	// printf("got here 1\n");
	Vector* list_of_strings_1 = VectorInitVector();

	// printf("got here 2\n");

	string* string_1_ptr = (string*) malloc(sizeof(string));
	// printf("got here 3\n");

	*string_1_ptr = string_1;

	VectorAppend(list_of_strings_1, string_1_ptr);
	// printf("got here 4\n");

	return list_of_strings_1;
}

Vector* VectorAddStringToVector2(string string_1, string string_2)
{
	Vector* list_of_strings_1 = VectorInitVector();

	string* string_1_ptr = (string*) malloc(sizeof(string));
	*string_1_ptr = string_1;
	VectorAppend(list_of_strings_1, string_1_ptr);

	string* string_2_ptr = (string*) malloc(sizeof(string));
	*string_2_ptr = string_2;

	VectorAppend(list_of_strings_1, string_2_ptr);
	return list_of_strings_1;
}
Vector* VectorAddStringToVector3(string string_1, string string_2, string string_3)
{
	Vector* list_of_strings_1 = VectorInitVector();

	string* string_1_ptr = (string*) malloc(sizeof(string));
	*string_1_ptr = string_1;
	VectorAppend(list_of_strings_1, string_1_ptr);

	string* string_2_ptr = (string*) malloc(sizeof(string));
	*string_2_ptr = string_2;

	VectorAppend(list_of_strings_1, string_2_ptr);

	string* string_3_ptr = (string*) malloc(sizeof(string));
	*string_3_ptr = string_3;

	VectorAppend(list_of_strings_1, string_3_ptr);

	return list_of_strings_1;
}
Vector* VectorAddStringToVector4(string string_1, string string_2, string string_3, string string_4)
{
	Vector* list_of_strings_1 = VectorInitVector();

	string* string_1_ptr = (string*) malloc(sizeof(string));
	*string_1_ptr = string_1;
	VectorAppend(list_of_strings_1, string_1_ptr);

	string* string_2_ptr = (string*) malloc(sizeof(string));
	*string_2_ptr = string_2;

	VectorAppend(list_of_strings_1, string_2_ptr);

	string* string_3_ptr = (string*) malloc(sizeof(string));
	*string_3_ptr = string_3;

	VectorAppend(list_of_strings_1, string_3_ptr);


	string* string_4_ptr = (string*) malloc(sizeof(string));
	*string_4_ptr = string_4;

	VectorAppend(list_of_strings_1, string_4_ptr);

	return list_of_strings_1;
}

Vector* VectorCombineVectors(Vector* source_1, Vector* source_2)
{
	Vector* list_of_lists_of_strings = VectorInitVector();

	VectorAppend(list_of_lists_of_strings, source_1);

	VectorAppend(list_of_lists_of_strings, source_2);

	return list_of_lists_of_strings;

}