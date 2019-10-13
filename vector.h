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

void VectorAppend(Vector* container, void* element);
bool VectorPopItem(Vector* container);
bool VectorPopFirst(Vector* container);

void VectorIncrementTopInt(Vector* container);

bool VectorDeleteItem(Vector* container, int index);
bool VectorDeleteAllItems(Vector* container);
void VectorShiftItems(Vector* container, int index);


void VectorShiftLeft(Vector* container, int start, int end);
//bool VectorInsertItem(Vector* container, void* element, int type);
bool VectorInsertItem(Vector* container, void* element, int insert_location, int type);

bool VectorIsEqualInt(void* a, void* b);
bool VectorIsEqualString(void* a, void* b);
bool VectorIsGreaterThanOrEqualInt(void* a, void* b);
bool VectorIsGreaterThanOrEqualString(void* a, void* b);
bool VectorIsGreaterThanInt(void* a, void* b);
bool VectorIsGreaterThanString(void* a, void* b);


bool VectorIsLessThanInt(void* a, void* b);
bool VectorIsLessThanString(void* a, void* b);
int VectorSearchItem(Vector* container, void* element, int type);



void VectorTest();
void VectorTestSorted();

void* VectorFindItem(Vector* container, void* element, int type);
Match* VectorSearchItemTrieDict(Vector* trie_tree_dict, Vector* edges, void* element, int type, int dict_type);

int VectorSearchItemTrieDict2(Vector* trie_tree_dict, Vector* edges, void* element, int type, int dict_type);


void VectorPrint(Vector* container);
void VectorPrintStrings(Vector* container);

Vector* VectorAddStringToVector1(string string_1);
Vector* VectorAddStringToVector2(string string_1, string string_2);
Vector* VectorAddStringToVector3(string string_1, string string_2, string string_3);
Vector* VectorAddStringToVector4(string string_1, string string_2, string string_3, string string_4);

Vector* VectorCombineVectors(Vector* source_1, Vector* source_2);

#endif