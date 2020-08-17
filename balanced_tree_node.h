#ifndef HASH_NODE
#define HASH_NODE
#include "standard_headers.h"
#include "vector.h"
typedef struct BalancedTreeNode
{
    int parent;
    Vector* keys;
    Vector* children;
}BalancedTreeNode;

BalancedTreeNode* BalancedTreeNodeInit();
BalancedTreeNode* BalancedTreeNodeInitWithKey(int key);
int BalancedTreeNodeFindInterval(Vector* states, Vector* keys, int new_key, bool (*comparator)(Vector* states, int i, int j));
void BalancedTreeNodeSplitDown(Vector* tree, int current_node);
void BalancedTreeNodeSplit(Vector* tree, int current_node, int parent_interval_id);

int BalancedTreeNodeSplitAcross(Vector* states, Vector* tree, int current_node, int parent_interval_id, int new_key);

void BalancedTreeNodeInsert(Vector* states, Vector* tree, int current_node, int parent_interval_id, int new_key);
void BalancedTreeNodeInsertIntoContainer(Vector* states, Vector* container, int value);
void BalancedTreeNodeInsertTest(Vector* my_tree, int arg_count, ...);

bool BalancedTreeNodeVectorIsGreaterThan2(Vector* states, Vector* search_name, int i);

bool BalancedTreeNodeVectorIsEqual(Vector* states, Vector* search_name, int key);

int BalancedTreeNodeFindMatch(  Vector* states,
                                Vector* keys,
                                Vector* search_key,
                                bool (*comparator)( Vector* states,
                                                    Vector* search_name,
                                                    int key));

int BalancedTreeNodeFindIntervalForSearch(  Vector* states,
                                            Vector* keys,
                                            Vector* search_key,
                                            bool (*comparator)( Vector* states,
                                                                Vector* search_name,
                                                                int i));

int BalancedTreeNodeSearchForVariableName(Vector* states, Vector* state_ids, Vector* parent_state_name, Vector* variable_state_name);

int BalancedTreeNodeSearch(Vector* states, Vector* tree, int current_node, Vector* name);

void BalancedTreeNodePrintTree(Vector* tree, int current_node, int indents);
Vector* BalancedTreeNodeDFT(Vector* tree, int current_node, Vector* nodes);
void BalancedTreeNodeDFTUpdateValue(Vector* tree, int current_node, int offset);

char* BalancedTreeNodeMakeIndents(int number_of_indents);
void BalancedTreeNodePrintTreeOfStates(Vector* states, Vector* tree, int current_node, int indents);





void BalancedTreeNodeTest();

#endif