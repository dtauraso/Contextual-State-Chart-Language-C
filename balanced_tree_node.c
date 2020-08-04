
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
int BalancedTreeNodeFindInterval(Vector* keys, int new_key)
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
    while(new_key > key)
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
void BalancedTreeNodeSplitRoot(Vector* tree, int current_node, int parent_interval_id)
{
    // node is root

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


    // copy the outside values down
    VectorAppendInt(a->keys, *((int*) VectorGetItem(node->keys, 0)));
    // if 4-Node has children send 2 of them to a
    VectorAppendInt(b->keys, *((int*) VectorGetItem(node->keys, 2)));
    // printf( "values copied down %i, %i\n",
    //         *((int*) a->keys->values[0]),
    //         *((int*) b->keys->values[0]));

    if(VectorGetPopulation(node->children) == 4)
    {
        // printf("doesn't come here\n");
        VectorAppendInt(a->children, *((int*) VectorGetItem(node->children, 0)));
        VectorAppendInt(a->children, *((int*) VectorGetItem(node->children, 1)));

        VectorAppendInt(b->children, *((int*) VectorGetItem(node->children, 2)));
        VectorAppendInt(b->children, *((int*) VectorGetItem(node->children, 3)));

    }
    // free the excess memory in the former 4-Node
    int middle_value = *((int*) node->keys->values[1]);

    for(int i = 0; i < VectorGetPopulation(node->keys); i++)
    {
        free(node->keys->values[i]);
    }

    node->keys->values = (void**) malloc(sizeof(void*));
    node->keys->population = 0;
    node->keys->size = 1;

    VectorAppendInt(node->keys, middle_value);

    // printf( "rest of 4-Node %i, %i\n",
    //         *((int*) node->keys->values[0]),
    //         VectorGetPopulation(node->keys));
    // right up to here
    // clear out all children from former 4-Node
    for(int i = 0; i < VectorGetPopulation(node->children); i++)
    {
        free(node->children->values[i]);
    }
    node->children->values = (void**) malloc(sizeof(void*) * 2);
    node->children->population = 0;
    node->children->size = 2;

    VectorAppend(tree, a);
    int id_a = VectorGetLastIndex(tree);

    VectorAppend(tree, b);
    int id_b = VectorGetLastIndex(tree);

    // for(int i = 0; i < )

    // store the ids of the 2-Nodes in tree as the first 2 children of the
    VectorAppendInt(node->children, id_a);
    VectorAppendInt(node->children, id_b);
    // printf("size of new 2-Node %i\n", VectorGetPopulation(node->children));
    // for(int i = 0; i < VectorGetPopulation(node->children); i++)
    // {
    //     int child = *((int*) VectorGetItem(node->children, i));
    //     BalancedTreeNode* child_node = (BalancedTreeNode*) VectorGetItem(tree, child);
    //     printf("child key %i\n", *((int*) child_node->keys->values[0]));
    // }
    // former 4-Node
    // the former 4-Node should now be a 2-Node
    // printf("print split tree\n");
    // BalancedTreeNodePrintTree(tree, current_node, 0);        

}
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
            BalancedTreeNodeSplitRoot(tree, current_node, parent_interval_id);
        }
        
        else
        {
            // cases are right but the code blocks may be different than expected
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
int splitAcross(Vector* tree, int current_node, int parent_interval_id, int new_key)
{
    // split across
    // store the integers into a vector
    // find the interval of insert
    // choose the currect newly split node and return it's id
    return 0;
}
void BalancedTreeNodeInsert(Vector* tree, int current_node, int interval_id, int new_key)
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
    // if the 4-Node has a parent
        // find the interval
        // split
        // use the interval to figure out the child to recurse on
        /*
        kinds of 4-Nodes(preprocess the 4-Node into a 3-Node or 2-Node before processing the node)
        when splitting across make the nodes first, then use the cases for making the connections
        root node
            split down
        internal node
            get the interval
            f()
            {
                split across
                check both new children and the parent to figure out what node to pick
                use a vector holding pointers to all 4 items
                return the node_id found that I should be currently on after splitting and before processing the insert cases
                so next part can figure out what child's child to find

                find interval
                use the interval with newly dsitributed child nodes to find the right child
                split across to make the new child nodes
                return the interval_id(fails cause we will not see the children locations anymore)
                original intervals [0, 1](left child) [2, 3] (right chld)
                use %2 to select the proper child's children after picking the child
                to recurse on the child's children

                return the id number of the newly added child so we can recurse on the new child
                BalancedTreeNodeInsert(tree, new_child_id, interval_id = -1, new_key)

            }

        leaf node(not the root)
            find interval
            split across
            do differently cause we don't need to recurse as we have found the node to insert at
            split across
            use the interval with newly dsitributed child nodes to find the right child
            the interval in this case is only used to find the child, not used for recursing or inserting
        
        kinds of 3-Nodes
            internal
                find interval and recurse
            leaf
                insert item
        
        kinds of 2-Nodes
            internal
                find interval and recurse
            leaf
                insert item

        tree examples

        parent is a 2-Node and it's right most child is a 4-Node
        a1
            a2|a3
            a4|a5|a6
        
        4 different insert places that require the 4-Node to split across
    

        
        */ 
    // preprocess the 4-Node to a 2-Node or 3-Node
    // 4-Nodes
    // root
    if(node->parent == -1 && key_count == 3)
    {
        // split down
        // splitDown(Vector* tree, int current_node)
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
                /*
                    chosen_child_node = splitAcross(Vector* tree,
                                                    int current_node,
                                                    int parent_interval_id,
                                                    int new_key)

                */
                // update node using chosen_child_node

            }
        }
    }
    // find interval for recurse or to insert
    int interval = BalancedTreeNodeFindInterval(node->keys, new_key);

    // 2-Node, 3-Node internal node
    if(children_count >= 2 && children_count <= 3)
    {
        // printf("2<= children_count <= 3\n");
        int next_node = *(int*) VectorGetItem(node->children, interval);
        // printf("here\n");
        // recurse
        BalancedTreeNodeInsert(tree, next_node, interval, new_key);
    }
    // 2-Node, 3-Node leaf node
    else if(children_count == 0)
    {

        // printf("new value %i our interval %i, %i\n", new_key, interval, VectorGetPopulation(node->keys));
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
    printf("%s", TrieTreeMakeIndents(indents));
    for(int i = 0; i < VectorGetPopulation(node->keys); i++)
    {
        int key = *((int*) VectorGetItem(node->keys, i));

        printf("|%i|", key);
    }
    printf("\n%s-----------\n", TrieTreeMakeIndents(indents));
    for(int i = 0; i < VectorGetPopulation(node->children); i++)
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

    BalancedTreeNodeInsert(my_tree, 0, -1, 3);

    // BalancedTreeNodePrintTree(my_tree, 0, 0);

    BalancedTreeNodeInsert(my_tree, 0, -1, 1);

    // BalancedTreeNodePrintTree(my_tree, 0, 0);

    BalancedTreeNodeInsert(my_tree, 0, -1, 5);

    BalancedTreeNodeInsert(my_tree, 0, -1, 4);

    // BalancedTreeNodePrintTree(my_tree, 0, 0);

    // exit(1);
    BalancedTreeNodeInsert(my_tree, 0, -1, 2);



    BalancedTreeNodeInsert(my_tree, 0, -1, 9);

    // BalancedTreeNodeInsert(my_tree, 0, -1, 10);

    // BalancedTreeNodeInsert(my_tree, 0, 5);

    // BalancedTreeNodeInsert(my_tree, 0, 7);

    // BalancedTreeNodeInsert(my_tree, 0, 8);
    BalancedTreeNodePrintTree(my_tree, 0, 0);

}