#ifndef VECTOR
#define VECTOR
#include "standard_headers.h"

typedef struct Vector
{
	void** values;
	int size;
	int population;

	// so I can instantiate vectors and C will not treat them as NULL
	// bool is_empty;

	// special window variables for the recording user changes system
	int first;
	int last;

	// use start and end to indicate the range of data focused on in a slice as nothing is deleted
	// untill after the state function finishes collecting the user changes 
	// any deleted items can just use the deleted flag in the state attribute


}Vector;

Vector* VectorInitVector();
Vector* VectorInitVectorSize(int size);

bool VectorDeleteVector(Vector* container);
Vector* VectorCopyVector(Vector* my_vector);

int VectorGetLastIndex(Vector* container);
void* VectorGetItem(Vector* container, int i);
void VectorSetItemToNull(Vector* container, int i);

int VectorGetPopulation(Vector* container);
void VectorAppendInt(Vector* container, int element);
// void VectorAppendString(Vector* container, string element);

void VectorAppend(Vector* container, void* element);
void VectorSet(Vector* container, void* element, int i);

bool VectorPopItem(Vector* container);
bool VectorPopFirst(Vector* container);

void VectorIncrementTopInt(Vector* container);

bool VectorDeleteItem(Vector* container, int index);
bool VectorDeleteAllItems(Vector* container);
bool VectorDeleteAllItems2(Vector* container);
void VectorShiftItems(Vector* container, int index);


void VectorShiftLeft(Vector* container, int start, int end);



void VectorTest();


void VectorPrint(Vector* container);
void VectorPrintVectorOfStrings(Vector* container);

// void VectorPrintStrings(Vector* container);

Vector* VectorMakeVectorOfChars(char* my_string);
Vector* VectorMakeVectorOfVectorsOfChars(int arg_count, ...);

// Vector* VectorAddStringToVector1(string string_1);
// Vector* VectorAddStringToVector2(string string_1, string string_2);

// Vector* VectorAddStringToVectorGeneral(string strings[], int size);


Vector* VectorCombineVectors1(Vector* source_1);

Vector* VectorCombineVectors2(Vector* source_1, Vector* source_2);


Vector* VectorCombineVectorsGeneral(Vector* vectors[], int size);

#endif