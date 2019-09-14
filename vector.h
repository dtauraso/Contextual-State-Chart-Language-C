#ifndef VECTOR
#define VECTOR
#include "standard_headers.h"
//#include "trie_tree.h"

typedef struct Match
{
	bool exists;
	int index;
}Match;
Match* initMatch();

typedef struct Vector
{
	void** values;
	int size;
	int population;


}Vector;

Vector* initVector();
Vector* initVectorSize(int size);

bool deleteVector(Vector* container);
int getLastIndex(Vector* container);
void* getItem(Vector* container, int i);
void setItemToNull(Vector* container, int i);

int getPopulation(Vector* container);

void append(Vector* container, void* element);
bool deleteItem(Vector* container, int index);
bool deleteAllItems(Vector* container);
void shiftItems(Vector* container, int index);


void shiftLeft(Vector* container, int start, int end);
//bool insertItem(Vector* container, void* element, int type);
bool isEqualInt(void* a, void* b);
bool isEqualString(void* a, void* b);
bool isGreaterThanOrEqualInt(void* a, void* b);
bool isGreaterThanOrEqualString(void* a, void* b);
bool isLessThanInt(void* a, void* b);
bool isLessThanString(void* a, void* b);
int searchItem(Vector* container, void* element, int type);



void test();
void testSorted();

void* findItem(Vector* container, void* element, int type);
Match* searchItemTrieDict(Vector* trie_tree_dict, Vector* edges, void* element, int type, int dict_type);

int searchItemTrieDict2(Vector* trie_tree_dict, Vector* edges, void* element, int type, int dict_type);


void Print(Vector* container);
void printStrings(Vector* container);

Vector* addStringToVector1(string string_1);
Vector* addStringToVector2(string string_1, string string_2);
Vector* addStringToVector3(string string_1, string string_2, string string_3);

Vector* combineVectors(Vector* source_1, Vector* source_2);

#endif