
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

// typedef struct BalancedTreeNode
// {
//     Vector* keys;
//     Vector* children;
// }BalancedTreeNode;
