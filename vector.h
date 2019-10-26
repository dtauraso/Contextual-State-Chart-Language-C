#ifndef VECTOR
#define VECTOR
#include "standard_headers.h"
//#include "trie_tree.h"

typedef struct Match
{
	bool exists;
	int index;
}Match;
Match* MatchInitMatch();

typedef struct Vector
{
	void** values;
	int size;
	int population;


}Vector;

Vector* VectorInitVector();
Vector* VectorInitVectorSize(int size);

bool VectorDeleteVector(Vector* container);
int VectorGetLastIndex(Vector* container);
void* VectorGetItem(Vector* container, int i);
void VectorSetItemToNull(Vector* container, int i);

int VectorGetPopulation(Vector* container);
void VectorAppendInt(Vector* container, int element);

void VectorAppend(Vector* container, void* element);
bool VectorPopItem(Vector* container);
bool VectorPopFirst(Vector* container);

void VectorIncrementTopInt(Vector* container);

bool VectorDeleteItem(Vector* container, int index);
bool VectorDeleteAllItems(Vector* container);
void VectorShiftItems(Vector* container, int index);


void VectorShiftLeft(Vector* container, int start, int end);



void VectorTest();


void VectorPrint(Vector* container);
void VectorPrintStrings(Vector* container);

Vector* VectorAddStringToVector1(string string_1);
Vector* VectorAddStringToVector2(string string_1, string string_2);
Vector* VectorAddStringToVector3(string string_1, string string_2, string string_3);
Vector* VectorAddStringToVector4(string string_1, string string_2, string string_3, string string_4);

Vector* VectorCombineVectors(Vector* source_1, Vector* source_2);

#endif