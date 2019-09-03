#ifndef MULTIWAY_LINES_NODE
#define MULTIWAY_LINES_NODE
#include "standard_headers.h"
#include "vector.h"
/*
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

void append(Vector* container, void* element);
bool deleteItem(Vector* container, int index);

void test();
*/

typedef struct MultiwayLinesNode
{
	string line;
	struct MultiwayLinesNode** parents;
	int parent_id;
	int parents_size;
	struct MultiwayLinesNode** children;
	Vector* children_ids;
	int children_size;
}MultiwayLinesNode;
void printMultiwayLinesNodesInContainer(Vector* container);

// create
MultiwayLinesNode* initMultiwayLinesNode();
// destroy
bool deleteMultiwayLinesNode(MultiwayLinesNode* node);



MultiwayLinesNode* setName(MultiwayLinesNode* node, string name);
MultiwayLinesNode* appendParent(MultiwayLinesNode* node, MultiwayLinesNode* parent);
MultiwayLinesNode* appendChild(MultiwayLinesNode* node, MultiwayLinesNode* child);
void printTree(MultiwayLinesNode* root, int indent_level);
void printTree2(Vector* container, int root, int indent_level);

void printParentPath(Vector* container, int start);

MultiwayLinesNode* getMultiwayLinesNode(void* raw_node);
int* getInt(void* raw_node);

void doubleLink(MultiwayLinesNode* parent, MultiwayLinesNode* child);
void doubleLink2(Vector* container, int parent, int child);

#endif