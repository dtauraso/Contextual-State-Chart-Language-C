#include "vector.h"
/*
typedef struct Vector
{
	void** values;
	int size;
	int population;

	// special window variables for the recording user changes system
	int first;
	int last;


}Vector;
// */

Vector* VectorInitVector()
{
	Vector* new_container = (Vector*) malloc(sizeof(Vector));
	new_container->values = NULL;
	new_container->size = 0;
	new_container->population = 0;
	new_container->first = 0;
	new_container->last = 0;
	// new_container->is_empty = true;
	// from C's point of view new_container == NULL

	return new_container;
}
Vector* VectorInitVectorSize(int size)
{
	if(size < 0)
	{
		return NULL;
	}
	Vector* new_container = (Vector*) malloc(sizeof(Vector) * size);
	new_container->values = (void**) malloc(sizeof(void*) * size);
	new_container->size = size;
	new_container->population = 0;
	new_container->first = 0;
	new_container->last = 0;
	// new_container->is_empty = true;
	return new_container;
}
bool VectorDeleteVector(Vector* container)
{
	if(container == NULL)
	{
		return false;
	}
	for(int i = 0; i < container->population; i++)
	{
		free(container->values[i]);
		container->values[i] = NULL;
	}
	free(container->values);
	container->values = NULL;
	// container->is_empty = true;
	return true;
}
Vector* VectorCopyVector(Vector* my_vector)
{
	Vector* new_vector = VectorInitVector();
	for(int i = 0; i < VectorGetPopulation(my_vector); i++)
	{
		int integer_to_append = *((int*) VectorGetItem(my_vector, i));
		VectorAppendInt(new_vector, integer_to_append);
	}
	return new_vector;
}

int VectorGetLastIndex(Vector* container)
{
	if(container == NULL)
	{
		return -1;
	}
	return container->population - 1;
}
// for unsorted only
void* VectorGetItem(Vector* container, int i)
{
	if(container == NULL)
	{
		return NULL;

	}
	// printf("getting item %i, %i\n", i, container->population);
	if(container->population == 0)
	{
		printf("container is empty\n");
		return NULL;
	}
	else if(i < container->population && i >= 0)
	{
		// printf("item |%i|\n", container->values[i]);
		return container->values[i];
	}
	else
	{
		//printf("out of bounds\n");
		return NULL;
	}

}
void VectorSetItemToNull(Vector* container, int i)
{
	// very unsafe to use
	// only use if the population size has already been adjusted
	//printf("set to null\n");
	if(container == NULL)
	{
		return;
	}
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
	if(container == NULL)
	{
		return -1;
	}
	return container->population;
}
void VectorAppendInt(Vector* container, int element)
{
	// printf("adding an integer\n");

	if(container == NULL)
	{
		return;
	}
	int* element_ptr = (int*) malloc(sizeof(int));
	*element_ptr = element;
	VectorAppend(container, element_ptr);
}
void VectorAppend(Vector* container, void* element)
{
	if(container == NULL)
	{
		return;
	}
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
	// container->is_empty = false;
		//printf("result\n");
		//VectorPrint(container);

}
bool VectorPopItem(Vector* container)
{
	if(container == NULL)
	{
		return false;
	}
	//printf("here %i\n", container->population - 1);
	//VectorPrint(container);

	int index = container->population - 1;
	free(container->values[index]);
	container->values[index] = NULL;

	container->population -= 1;
	//VectorPrint(container);
	return true;
;
}
bool VectorPopFirst(Vector* container)
{
	if(container == NULL)
	{
		return false;
	}
	return VectorDeleteItem(container, 0);
}
void VectorIncrementTopInt(Vector* container)
{
	if(container == NULL)
	{
		return;
	}
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
bool VectorDeleteItem(Vector* container, int index)
{
	// needs a special delete function for the object type
	// printf("delete at %i\n", index);
	// set container[index] to null
	// shift all values from [index + 1, end] to the left by 1
	if(container == NULL)
	{
		return false;
	}
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
bool VectorDeleteAllItems(Vector* container)
{
	// assuems all elements are primitives
	if(container == NULL)
	{
		return false;
	}
	for(int i = 0; i < container->population; i++)
	{
		free(container->values[i]);
		container->values[i] = NULL;
	}
	free(container->values);
	container->values = NULL;
	free(container);
	container = NULL;
	return true;
}
bool VectorDeleteAllItems2(Vector* container)
{
	// assuems all elements are primitives
	if(container == NULL)
	{
		return false;
	}
	for(int i = 0; i < container->population; i++)
	{
		free(container->values[i]);
		container->values[i] = NULL;
	}
	free(container->values);
	container->values = NULL;
	container->population = 0;
	container->size = 0;
	// free(container);
	// container = NULL;
	return true;
}

void VectorShiftItems(Vector* container, int index)
{
	if(container == NULL || index >= container->population)
	{
		return;
	}

	for(int i = index + 1; i < container->population; i++)
	{
		container->values[i - 1] = container->values[i];

		container->values[i] = NULL;

	}
	container->population--;
	
}

void VectorShiftLeft(Vector* container, int start, int end)
{
	//printf("insert location bounds %i %i\n", start, end);
	if(container == NULL || start < 0 || end > start)
	{
		return;
	}
	if(container->population <= start + 1)
	{
		return;
	}
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
	if(container == NULL)
	{

		printf("empty container\n");
		return;
	}
	// printf("printing container pop %i, size %i\n", container->population, container->size);
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
			printf("|%c|", *b);
			
			//printf("|item|");
		}
	}
	if(container->population == 0)
	{
		printf("none");
	}
	printf("\n\n");
	

}
// void VectorPrintVectorOfStrings(Vector* container)
// {
// 	if(container == NULL)
// 	{
// 		return;
// 	}
// 	// assume we are passing in a vector of vectors of strings
// 	for(int i = 0; i < VectorGetPopulation(container); i++)
// 	{
// 		Vector* inner_container = (Vector*) VectorGetItem(container, i);
// 		VectorPrintStrings(inner_container);
// 	}
// }

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
	
	// erase a list of numbers
}

Vector* VectorMakeVectorOfChars(char* my_string)
{
	Vector* list_of_chars = VectorInitVector();

	for(int i = 0; i < strlen(my_string); i++)
	{
		int* char_ptr = (int*) malloc(sizeof(int));
		*char_ptr = my_string[i];
		// printf("%i\n", my_string[i]);
		VectorAppend(list_of_chars, char_ptr);
	}

	// printf("we are here\n%s\n", my_string.c_str());
	// VectorPrint(list_of_chars);
	// printf("done\n");
	return list_of_chars;

}
Vector* VectorMakeVectorOfVectorsOfChars(int arg_count, ...)
{
	Vector* list_of_vectors = VectorInitVector();
	
	va_list ap;

	va_start(ap, arg_count);
	for(int i = 0; i < arg_count; i++)
	{
		Vector* current_arg = va_arg(ap, Vector*);
		VectorAppend(list_of_vectors, current_arg);
	}
	return list_of_vectors;
}