
/*
This is an experimenal dictionary implementation as we just need decent efficency and ease of implementation
for a small number of states. The current goal isn't to code up the most effective dict in C.
The contextual state chart is the main goal for now.
''
hash function using the sdbm hash formula
hash(i) = hash(i - 1) * 65599 + str[i];
hash(0) = 0
efficient version
hash = 0
hash = str[i] + (hash << 6) + (hash << 16) - hash;
this is to keep collisions lower than if I made one myself
approximating O(1) time

most cases time is O(1)
when container doubles or halves time for that insert or delete is O(n)


Quick and rough observation:
we will be doing alot of insertion deletion and searching

space complexity
constant for each operation

time complexity
sorted array via sorting fails cause that means lots of nlogn

sorted array via binsearch style insert fails cause that means alot of nlogn

hash table has O(#collisions) for all operations and the aboe hash function will keep that number small
hash table does have O(n) when we resize using powers of 2

bst has O(n) search time

balanced bst has O(logn) for all but it's more complex to setup and test

we have 1 main array for storing all states
each state has a child array for storing children state and can be used to store the children states as a dictionary

We need a quick solution as Trie Trees were used but they require twice as much space(holding the state name), and require more complexity
2 different ways and 2 different data structures just to deal with a dict/array
using [i] requires accessing the chilren list for the state name, using state_name to accessing the trie inside the parent state, using the state id to get the state
using [key] requires using using state_name to accessing the trie inside the parent state, using the state id to get the state

using an array styled as a hash table let's us save 50% memory and encode each state name as an array index in the master array
and lets us use 1 array to store the state id numbers in the child array
*/

// typedef struct HashNode
// {

//     void* key; // point to same state name in the main array
//     void* value; // points to an integer representing the id number of the state in the main array
//     Vector* chain;
//     bool is_start_of_chain;
// }HashNode;
#include "balanced_tree_node.h"
#include "vector.h"
#include "contextual_state_chart.h"

// HashNode* HashNodeInitStartNode(Vector* key, int value)
// {
//     HashNode* my_hash_node = (HashNode*) malloc(sizeof(HashNode));


//     my_hash_node->key = key;
//     my_hash_node->value = value;
//     my_hash_node->chain = VectorInitVector();
//     my_hash_node->is_start_of_chain = true;
// }
// HashNode* HashNodeInitChainedNode(Vector* key, int value)
// {
//     HashNode* my_hash_node = (HashNode*) malloc(sizeof(HashNode));
//     my_hash_node->key = key;
//     my_hash_node->value = value;
//     my_hash_node->chain = NULL;
//     my_hash_node->is_start_of_chain = false;

// }
// int HashNodeHashFunction(Vector* container, Vector* input)
// {
//     int hash = 0;
//     for(int i = 0; i < VectorGetPopulation(input); i ++)
//     {
//         int element = *((int*) VectorGetItem(input, i));
//         hash = element + (hash << 6) + (hash << 16) - hash;

//     }
//     int size = VectorGetPopulation(container);
//     if(size > 0)
//     {
//         hash %= VectorGetPopulation(container);
//     }
//     hash = size == 0? hash: hash %= VectorGetPopulation(container);
//     return hash;

// }

// void HashNodeInsertChildEdge(Vector* states, State* added_state)
// {
//     // hash(state_name) -> [(state_name, state_id)]
//     Vector* children = added_state->children;

//     int hash = HashNodeHashFunction(children, added_state->name);

//     // added_state.children[hash] = added_state->id
//     HashNode* item = NULL;

//     if(VectorGetPopulation(children) == 0)
//     {
//         HashNode* new_node = HashNodeInitChainedNode(added_state->name, added_state->id);
//         VectorAppend(children, new_node);
//     }

//     item = (HashNode*) VectorGetItem(children, hash);
//     if(item == NULL)
//     {

//         HashNode* new_node = HashNodeInitStartNode(added_state->name, added_state->id);

//         // new_node is used as item when there is a collision
//         VectorSet(children, new_node, hash);
//     }
//     else
//     {
//         HashNode* new_node = HashNodeInitChainedNode(added_state->name, added_state->id);
//         VectorAppend(item->chain, new_node);
//     }

// }

// 2-3-4 tree
// typedef struct BalancedTreeNode
// {
//     Vector* keys;
//     Vector* children;
// }BalancedTreeNode;

BalancedTreeNode* BalancedTreeNodeInit()
{
    BalancedTreeNode* my_node = (BalancedTreeNode*) malloc(sizeof(BalancedTreeNode));

    my_node->parent = -1;
    my_node->keys = VectorInitVector();
    my_node->children = VectorInitVector();
    return my_node;
}

BalancedTreeNode* BalancedTreeNodeInitWithKey(int key)
{
    BalancedTreeNode* my_node = (BalancedTreeNode*) malloc(sizeof(BalancedTreeNode));

    my_node->parent = -1;
    my_node->keys = VectorInitVector();
    my_node->children = VectorInitVector();

    VectorAppendInt(my_node->keys, key);
    return my_node;
}

bool isGreaterThan(int i, int j)
{
    return i > j;
}
int BalancedTreeNodeFindInterval(Vector* keys, int new_key, bool (*comparator)(int i, int j))
{

    // find the interval
    int interval = -1;

    // halt when new_key < key
    int i = 0;
    if(i >= VectorGetPopulation(keys))
    {
        return 0;
    }
    int key = *(int*) VectorGetItem(keys, i);
    while(comparator(new_key, key))
    {
        // printf("here\n");
        i++;
        if(i >= VectorGetPopulation(keys))
        {
            break;
        }
        key = *(int*) VectorGetItem(keys, i);
    }
    interval = i;
    // printf("interval %i\n", interval);
    // if it's larger than all the keys it must be in the last interval
    if(interval == -1)
    {
        interval = VectorGetPopulation(keys);
    }
    return interval;
}
// void BalancedTreeNodeSplitRoot(Vector* tree, int current_node, int parent_interval_id)
// {
//     // node is root

//     BalancedTreeNode* node = (BalancedTreeNode*) VectorGetItem(tree, current_node);
//     if(node == NULL)
//     {
//         return;
//     }
//     // make 2 leaf nodes
//     BalancedTreeNode* a = BalancedTreeNodeInit();
//     a->parent = current_node;
//     BalancedTreeNode* b = BalancedTreeNodeInit();
//     b->parent = current_node;


//     // copy the outside values down
//     VectorAppendInt(a->keys, *((int*) VectorGetItem(node->keys, 0)));
//     // if 4-Node has children send 2 of them to a
//     VectorAppendInt(b->keys, *((int*) VectorGetItem(node->keys, 2)));
//     // printf( "values copied down %i, %i\n",
//     //         *((int*) a->keys->values[0]),
//     //         *((int*) b->keys->values[0]));

//     if(VectorGetPopulation(node->children) == 4)
//     {
//         // printf("doesn't come here\n");
//         VectorAppendInt(a->children, *((int*) VectorGetItem(node->children, 0)));
//         VectorAppendInt(a->children, *((int*) VectorGetItem(node->children, 1)));

//         VectorAppendInt(b->children, *((int*) VectorGetItem(node->children, 2)));
//         VectorAppendInt(b->children, *((int*) VectorGetItem(node->children, 3)));

//     }
//     // free the excess memory in the former 4-Node
//     int middle_value = *((int*) node->keys->values[1]);

//     for(int i = 0; i < VectorGetPopulation(node->keys); i++)
//     {
//         free(node->keys->values[i]);
//     }

//     node->keys->values = (void**) malloc(sizeof(void*));
//     node->keys->population = 0;
//     node->keys->size = 1;

//     VectorAppendInt(node->keys, middle_value);

//     // printf( "rest of 4-Node %i, %i\n",
//     //         *((int*) node->keys->values[0]),
//     //         VectorGetPopulation(node->keys));
//     // right up to here
//     // clear out all children from former 4-Node
//     for(int i = 0; i < VectorGetPopulation(node->children); i++)
//     {
//         free(node->children->values[i]);
//     }
//     node->children->values = (void**) malloc(sizeof(void*) * 2);
//     node->children->population = 0;
//     node->children->size = 2;

//     VectorAppend(tree, a);
//     int id_a = VectorGetLastIndex(tree);

//     VectorAppend(tree, b);
//     int id_b = VectorGetLastIndex(tree);

//     // for(int i = 0; i < )

//     // store the ids of the 2-Nodes in tree as the first 2 children of the
//     VectorAppendInt(node->children, id_a);
//     VectorAppendInt(node->children, id_b);
//     // printf("size of new 2-Node %i\n", VectorGetPopulation(node->children));
//     // for(int i = 0; i < VectorGetPopulation(node->children); i++)
//     // {
//     //     int child = *((int*) VectorGetItem(node->children, i));
//     //     BalancedTreeNode* child_node = (BalancedTreeNode*) VectorGetItem(tree, child);
//     //     printf("child key %i\n", *((int*) child_node->keys->values[0]));
//     // }
//     // former 4-Node
//     // the former 4-Node should now be a 2-Node
//     // printf("print split tree\n");
//     // BalancedTreeNodePrintTree(tree, current_node, 0);        

// }
void BalancedTreeNodeSplit(Vector* tree, int current_node, int parent_interval_id)
{
    // We should be spliting a 4-Node
    if(tree == NULL)
    {
        return;
    }
    // if we are at a 4-Node
    BalancedTreeNode* node = (BalancedTreeNode*) VectorGetItem(tree, current_node);
    if(node == NULL)
    {
        return;
    }
    /*
    what is different if we have children?
    we should have 4 children if there is a second case
    a gets first 2 children
    b gets the second 2 children
    */
   
   if(VectorGetPopulation(node->keys) == 3)
    {
        printf("parent %i\n", node->parent);
        if(node->parent == -1)
        {
            // BalancedTreeNodeSplitRoot(tree, current_node, parent_interval_id);
        }
        
        else
        {
            /*
            make one extra child node with the data and any grandchildren links
            clean and replace data for the node we will split
            insert the middle key to the parent node
            store the 3 values into a vector and use it to find the currect child node to return
            via interval finding
            use the cases for finding out how to adjust the parent's child links

            */
            // the parent isn't a 4-Node as we would have converted it last recursive call
            // if it was
            BalancedTreeNode* parent = (BalancedTreeNode*) VectorGetItem(tree, node->parent);

            if(parent_interval_id == 1 && VectorGetPopulation(parent->children) == 3)
            {
                // middle chld is the 4-Node we want to split
            }
            else if(parent_interval_id == 0)
            {
                // first node is the 4-Node we want to split
            }
            else if(parent_interval_id == VectorGetPopulation(parent->children))
            {
                // last node is the 4-Node we want to split
            }
            printf("node has a parent so split differently\n");
        }
    }
        
    
}
void BalancedTreeNodeUpdateParentOnNewlyShiftedChildren(Vector* tree,
                                                        BalancedTreeNode* node,
                                                        int node_id)
{
    for(int i = node->children->start; i < node->children->end; i++)
    {
        int child_node_id = *(int*) VectorGetItem(node->children, i);
        BalancedTreeNode* child_node = (BalancedTreeNode*) VectorGetItem(tree, child_node_id);
        child_node->parent = node_id;

    }

}
void BalancedTreeNodeSplitDown(Vector* tree, int current_node)
{
    BalancedTreeNode* node = (BalancedTreeNode*) VectorGetItem(tree, current_node);
    if(node == NULL)
    {
        return;
    }
    // make 2 leaf nodes
    BalancedTreeNode* a = BalancedTreeNodeInit();
    a->parent = current_node;
    BalancedTreeNode* b = BalancedTreeNodeInit();
    b->parent = current_node;

    VectorAppend(tree, a);
    int id_a = VectorGetLastIndex(tree);

    VectorAppend(tree, b);
    int id_b = VectorGetLastIndex(tree);

    // copy the outside values down
    VectorAppendInt(a->keys, *((int*) VectorGetItem(node->keys, 0)));
    // if 4-Node has children send 2 of them to a
    VectorAppendInt(b->keys, *((int*) VectorGetItem(node->keys, 2)));

    // printf( "values copied down %i, %i\n",
    //         *((int*) a->keys->values[0]),
    //         *((int*) b->keys->values[0]));
    int original_children_size = VectorGetPopulation(node->children);
    printf("size %i\n", original_children_size);
    // somehow this test doesn't always work
    // the population of items isn't correct
    if(VectorGetPopulation(node->children) == 4)
    {
        printf("doesn't come here\n");
        VectorAppendInt(a->children, *((int*) VectorGetItem(node->children, 0)));
        VectorAppendInt(a->children, *((int*) VectorGetItem(node->children, 1)));

        VectorAppendInt(b->children, *((int*) VectorGetItem(node->children, 2)));
        VectorAppendInt(b->children, *((int*) VectorGetItem(node->children, 3)));

        // update the children's parents on the newly shifted children
        BalancedTreeNodeUpdateParentOnNewlyShiftedChildren(tree, a, id_a);
        BalancedTreeNodeUpdateParentOnNewlyShiftedChildren(tree, b, id_b);

        // clear out all children from the 4-Node
        VectorReset(node->children);

    }

    // free the excess memory in the former 4-Node
    int middle_value = *((int*) node->keys->values[1]);

    VectorReset(node->keys);

    VectorAppendInt(node->keys, middle_value);

    // store the ids of the 2-Nodes in tree as the first 2 children of the reset 4-Node
    VectorAppendInt(node->children, id_a);
    VectorAppendInt(node->children, id_b);

    // the former 4-Node should now be a 2-Node
}
int BalancedTreeNodeSplitAcross(Vector* tree, int current_node, int parent_interval_id, int new_key)
{
    // split across
    printf("current node %i, parent interval id %i new key %i\n",
            current_node, parent_interval_id, new_key);
    BalancedTreeNode* node = (BalancedTreeNode*) VectorGetItem(tree, current_node);
    if(node == NULL)
    {
        return -1;
    }
    BalancedTreeNode* parent = (BalancedTreeNode*) VectorGetItem(tree, node->parent);
    if(parent == NULL)
    {
        return -1;
    }

    // setup right node
    BalancedTreeNode* right_node = BalancedTreeNodeInit();
    right_node->parent = node->parent;
    VectorAppendInt(right_node->keys, *((int*) VectorGetItem(node->keys, 2)));

    VectorAppend(tree, right_node);

    int right_node_id = VectorGetLastIndex(tree);
    
    // setup data to copy to parent
    int middle_key = *((int*) VectorGetItem(node->keys, 1));

    // setup collection of keys for interval finding laster
    Vector* keys_for_interval_finding = VectorInitVector();

    printf("here\n");
    // printf("size %i\n", VectorGetPopulation(node->keys));
    // has items but the start index hasn't been updated to 0 yet
    for(int i = node->keys->start; i < node->keys->end; i++)
    {
        // printf("%i\n", i);
        VectorAppendInt(keys_for_interval_finding, *((int*) VectorGetItem(node->keys, i)));

    }
    // VectorAppendInt(keys_for_interval_finding, *((int*) VectorGetItem(node->keys, 0));
    // VectorAppendInt(keys_for_interval_finding, *((int*) VectorGetItem(node->keys, 0));
    // VectorAppendInt(keys_for_interval_finding, *((int*) VectorGetItem(node->keys, 0));

    // restructure current node as the "left" node
    int first_key = *((int*) VectorGetItem(node->keys, 0));
    VectorReset(node->keys);
    printf("here 2\n");
    VectorAppendInt(node->keys, first_key);

    // redistribute children from current node to "left" node and right node
    if(VectorGetPopulation(node->children) == 4)
    {
        Vector* children = VectorInitVector();

        // printf("here 3\n");
        for(int i = node->children->start; i < node->children->end; i++)
        {
            // printf("%i\n", i);
            VectorAppendInt(children, *((int*) VectorGetItem(node->children, i)));

        }
        // printf("here 4\n");
        VectorReset(node->children);

        VectorAppendInt(node->children, *((int*) VectorGetItem(children, 0)));
        VectorAppendInt(node->children, *((int*) VectorGetItem(children, 1)));
        // printf("here 5\n");

        VectorAppendInt(right_node->children, *((int*) VectorGetItem(children, 2)));
        // printf("here 6\n");

        VectorAppendInt(right_node->children, *((int*) VectorGetItem(children, 3)));

        // update the children's parents on the newly shifted children
        BalancedTreeNodeUpdateParentOnNewlyShiftedChildren(tree, node, current_node);
        BalancedTreeNodeUpdateParentOnNewlyShiftedChildren(tree, right_node, right_node_id);


        // erase the children vector
        VectorDeleteAllItems2(children);
        free(children);
    }
    printf("insert %i into node %i's keys\n", middle_key, node->parent);
    // printf("parent's children size %i\n", parent->children->population);

    // left is restructured and has it's new key and new children
    // right has been made with it's new key and new children

    // insert middle item to parent by finding the interval
    BalancedTreeNodeInsertKey(parent, middle_key);

    printf("parent_interval_id %i, population %i\n",
            parent_interval_id,
            VectorGetPopulation(parent->children));
    printf("parent %i old child count %i\n", node->parent, parent->children->population);

    // rearange parent's children by case
    // middle child or leftmost node
    if((parent_interval_id == 1 && VectorGetPopulation(parent->children) == 3) ||
        (parent_interval_id == 0))
    {
        // middle chld is the 4-Node we want to split
        // first node is the 4-Node we want to split

        // right shift for parent's children

        // right shift [parent_interval_id + 1, end] by 1 unit
        // [1, 2] end = 2 and it's the rightmost place we copy data into
        // leftmost node works for below cases
        // works for 2-Nodes -> 3-Nodes
        // works for 3-Nodes -> 4-Nodes
        VectorShiftRight(parent->children, parent_interval_id + 1);

    }
    else if(parent_interval_id == parent->children->end - 1)
    {
        // last node is the 4-Node we want to split
        // left shift
        // realloc memory to the right by 1 unit
        printf("left shift\n");
        VectorShiftLeft(parent->children);
        // return current_node;

    }
    // insert parent->children[parent_interval_id + 1]
    VectorSetInt(parent->children, right_node_id, parent_interval_id + 1);
    printf("parent %i new child count %i\n", node->parent, parent->children->population);
    VectorPrintInts(keys_for_interval_finding);
    int interval = BalancedTreeNodeFindInterval(keys_for_interval_finding, new_key, isGreaterThan);
    // printf("our interval %i\n", interval);
    // printf("avaliable nodes current %i, right %i\n", current_node, right_node_id);
    int chosen_node = 0;
    if(interval >= 0 && interval <= 1)
    {
        // printf("node is %i\n", current_node);
        chosen_node = current_node;
    }
    else if(interval >= 2 && interval <= 3)
    {
        // printf("node is %i\n", right_node_id);
        chosen_node = right_node_id;
    }
    return chosen_node;


    // insert the right node as a new child to parent

    // use another interval to find out what child node to return
    // interval range -> node
    // [0, 1] -> "left" node
    // [2, 3] -> right node



    


    // store the integers into a vector
    // find the interval of insert
    // choose the currect newly split node and return it's id
    return 0;
}
void BalancedTreeNodeInsertKey(BalancedTreeNode* node, int new_key)
{
    int interval = BalancedTreeNodeFindInterval(node->keys, new_key, isGreaterThan);

    // nth interval
    if(interval == VectorGetPopulation(node->keys))
    {
        VectorAppendInt(node->keys, new_key);
    }
    // [0, n - 1] intervals consistent with i: [0, len(keys) - 1]
    else
    {
        // printf("%i right shift time, location for key %i\n", new_key, interval);
        VectorShiftRight(node->keys, interval);
        VectorSetInt(node->keys, new_key, interval);
    }

}
void BalancedTreeNodeInsert(Vector* tree, int current_node, int parent_interval_id, int new_key)
{
    if(tree == NULL)
    {
        return;
    }
    BalancedTreeNode* node = (BalancedTreeNode*) VectorGetItem(tree, current_node);

    if(node == NULL)
    {
        return;
    }
    int children_count = VectorGetPopulation(node->children);
    int key_count = VectorGetPopulation(node->keys);
    /*

    tree examples

    parent is a 2-Node and it's right most child is a 4-Node
    a1
        a2|a3
        a4|a5|a6
    
    split
    a5|a1
        a2|a3
        a4|a6
    
    4 different insert places that require the 4-Node to split across

    */ 
    // preprocess the 4-Node to a 2-Node or 3-Node
    // 4-Nodes
    // root
    if(node->parent == -1 && key_count == 3)
    {
        printf("split down\n");
        // split down
        BalancedTreeNodeSplitDown(tree, current_node);
        // // split
        // BalancedTreeNodeSplit(tree, current_node, -1);
    }
    // internal node or leaf node
    else if(node->parent >= 0)
    {
        if(key_count == 3)
        {
            if(children_count == 4 || children_count == 0)
            {
                // split across
                printf("split across\n");
                
                int chosen_child_node = BalancedTreeNodeSplitAcross(
                                            tree,
                                            current_node,
                                            parent_interval_id,
                                            new_key);
                // printf("node id for insert %i\n", chosen_child_node);
                // BalancedTreeNodePrintTree(tree, 0, 1);

                
                // update node using chosen_child_node
                node = (BalancedTreeNode*) VectorGetItem(tree, chosen_child_node);
            }
        }
    }
    // recalculate after preprocessing
    children_count = VectorGetPopulation(node->children);
    key_count = VectorGetPopulation(node->keys);


    // 2-Node, 3-Node internal node
    if(children_count >= 2 && children_count <= 3)
    {
        // find interval for recurse

        int interval = BalancedTreeNodeFindInterval(node->keys, new_key, isGreaterThan);

        // printf("2<= children_count <= 3\n");
        int next_node = *(int*) VectorGetItem(node->children, interval);
        // printf("here\n");
        // recurse
        BalancedTreeNodeInsert(tree, next_node, interval, new_key);
    }
    // 2-Node, 3-Node leaf node
    else if(children_count == 0)
    {
        printf("insert only\n");
        // printf("new value %i our interval %i, %i\n", new_key, interval, VectorGetPopulation(node->keys));
        BalancedTreeNodeInsertKey(node, new_key);
    }
}
char* TrieTreeMakeIndents(int number_of_indents)
{
	// printf("indents to make %i\n", number_of_indents);
	char* indents = (char*) malloc(sizeof(char) * (number_of_indents + 1));
	memset(indents, ' ', number_of_indents);
	indents[number_of_indents] = '\0';
	return indents;
}

void BalancedTreeNodePrintTree(Vector* tree, int current_node, int indents)
{
    if(tree == NULL)
    {
        return;
    }
    BalancedTreeNode* node = (BalancedTreeNode*) VectorGetItem(tree, current_node);

    if(node == NULL)
    {
        return;
    }
    // printf("size %i\n", VectorGetPopulation(node->keys));
    printf( "%s(%i) parent %i ",
            TrieTreeMakeIndents(indents),
            current_node,
            node->parent);
    for(int i = 0; i < VectorGetEnd(node->keys); i++)
    {
        int key = *((int*) VectorGetItem(node->keys, i));

        printf("|%i|", key);
    }
    printf( "\n%s-----------\n",
            TrieTreeMakeIndents(indents));
    for(int i = 0; i < VectorGetEnd(node->children); i++)
    {
        int child = *((int*) VectorGetItem(node->children, i));
        BalancedTreeNodePrintTree(tree, child, indents + 3);

    }

}

void BalancedTreeNodeTest()
{
    Vector* my_tree = VectorInitVector();

    BalancedTreeNode* empty_node = BalancedTreeNodeInit();

    VectorAppend(my_tree, empty_node);



    // insert for leftmost node and rightmost node
    // leftmost node works for below cases
    // works for 2-Nodes -> 3-Nodes
    // works for 3-Nodes -> 4-Nodes
    // BalancedTreeNodeInsertTest(my_tree, 11, 3, 2, 1, -1, 4, -2, 0, -3, -4, -5, 5);



    // rightmost node works for below cases
    // works for 2-Nodes -> 3-Nodes
    // works for 3-Nodes -> 4-Nodes

    // 18, 0, 1, 2, 3, 4, 5, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21 works till 21
    // the split down fails on inserting 21
    // works now as the population is right
    BalancedTreeNodeInsertTest(my_tree, 18, 0, 1, 2, 3, 4, 5, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21);//, 10, 11, 12, 13);

    // middle node test for 3-Nodes -> 4-Nodes

    /*

(0) |3|
-----------
   (5) |1|
   -----------
      (1) |0|
      -----------
      (2) |2|
      -----------
   (6) |5|
   -----------
      (3) |4|
      -----------
      (4) |10||11||12|
      -----------
      inserting 13
(0) |3||11|
-----------
   (5) |1|
   -----------
      (1) |0|
      -----------
      (2) |2|
      -----------
   (6) |5|
   -----------
      (3) |4|
      -----------
      (4) |10|
      -----------
   (7) |12||13|
   -----------

     */
    /*
    (0) parent is -1, key count 1|3|
        ----------- children count 2
        (5) parent is 0, key count 1|1|
        ----------- children count 2
            (1) parent is 5, key count 1|0|
            ----------- children count 0
            (2) parent is 5, key count 1|2|
            ----------- children count 0
        (6) parent is 0, key count 3|5||11||13|
        ----------- children count 4
            (3) parent is 6, key count 1|4|
            ----------- children count 0
            (4) parent is 6, key count 1|10|
            ----------- children count 0
            (7) parent is 6, key count 1|12|
            ----------- children count 0
            (8) parent is 6, key count 2|14||15|
            ----------- children count 0
    
    split across
    right shift
    (0) parent is -1, key count 2|3||11|
        ----------- children count 2
        (5) parent is 0, key count 1|1|
        ----------- children count 2
            (1) parent is 5, key count 1|0|
            ----------- children count 0
            (2) parent is 5, key count 1|2|
            ----------- children count 0
        (6) parent is 0, key count 1|5|
        ----------- children count 2
            (3) parent is 6, key count 1|4|
            ----------- children count 0
            (4) parent is 6, key count 1|10|
            ----------- children count 0
        (9) parent is 0, key count 1|13|
        ----------- children count 2
            (7) parent is 9, key count 1|12|
            ----------- children count 0
            (8) parent is 9, key count 3|14||15||16|
            ----------- children count 0
    */
    // BalancedTreeNodeInsertTest(my_tree, 6, 3, 2, 1, 4, -1, 0);

    // BalancedTreeNodeInsert(my_tree, 0, -1, 3);

    // BalancedTreeNodePrintTree(my_tree, 0, 0);
    exit(1);
    // BalancedTreeNodeInsert(my_tree, 0, -1, 1);

    // BalancedTreeNodePrintTree(my_tree, 0, 0);

    // BalancedTreeNodeInsert(my_tree, 0, -1, 5);

    // BalancedTreeNodeInsert(my_tree, 0, -1, 4);

    // BalancedTreeNodePrintTree(my_tree, 0, 0);

    // exit(1);
    // BalancedTreeNodeInsert(my_tree, 0, -1, 2);



    // BalancedTreeNodeInsert(my_tree, 0, -1, 9);

    // BalancedTreeNodeInsert(my_tree, 0, -1, 10);

    // BalancedTreeNodeInsert(my_tree, 0, 5);

    // BalancedTreeNodeInsert(my_tree, 0, 7);

    // BalancedTreeNodeInsert(my_tree, 0, 8);
    // BalancedTreeNodePrintTree(my_tree, 0, 0);

}
void BalancedTreeNodeInsertTest(Vector* my_tree, int arg_count, ...)
{


	Vector* list_of_vectors = VectorInitVector();
	
	va_list ap;

	va_start(ap, arg_count);
	for(int i = 0; i < arg_count; i++)
	{
		int current_arg = va_arg(ap, int);
        printf("inserting %i\n", current_arg);
        BalancedTreeNodeInsert(my_tree, 0, -1, current_arg);
        BalancedTreeNodePrintTree(my_tree, 0, 0);

	}
    return;
}