#ifndef HASH_NODE
#define HASH_NODE
#include "vector.h"

typedef struct HashNode
{

    void* key; // point to same state name in the main array
    int value; // id number of the state in the main array
    Vector* chain;
    bool is_start_of_chain;
}HashNode;

typedef struct BalancedTreeNode
{
    int parent;
    Vector* keys;
    Vector* children;
}BalancedTreeNode;


void BalancedTreeNodeTest();

#endif