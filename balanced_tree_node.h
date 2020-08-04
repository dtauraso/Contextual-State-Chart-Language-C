#ifndef HASH_NODE
#define HASH_NODE
#include "vector.h"

typedef struct BalancedTreeNode
{
    int parent;
    Vector* keys;
    Vector* children;
}BalancedTreeNode;

BalancedTreeNode* BalancedTreeNodeInit();
BalancedTreeNode* BalancedTreeNodeInitWithKey(int key);
int BalancedTreeNodeFindInterval(Vector* keys, int new_key);
void BalancedTreeNodeSplit(Vector* tree, int current_node, int parent_interval_id);
void BalancedTreeNodeInsert(Vector* tree, int current_node, int interval_id, int new_key);
void BalancedTreeNodePrintTree(Vector* tree, int current_node, int indents);





void BalancedTreeNodeTest();

#endif