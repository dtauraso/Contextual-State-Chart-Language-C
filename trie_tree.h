#ifndef TRIE_TREE
#define TRIE_TREE
#include "standard_headers.h"

struct Vector;
typedef struct TrieNode2
{
	// the links are integers
	void* value;
	// will be unsorted
	Vector* links;  // ints
	// will be sorted
	Vector* sorted_link_indecies; // ints
	int value_type;
	// 0 -> int
	// 1 -> string
	// will be stored as a DynamicState* but can't put it here because of the circular dependency
	void* state;
}TrieNode2;
TrieNode2* initTrieNode2();


typedef struct TrieTree
{
	int root;
	// will be unsorted
	Vector* trie_tree;

}TrieTree;
TrieTree* initTrieTree();

void insertString(TrieTree* my_trie_tree, string element);
void printTrie(TrieTree* my_trie_tree);

#endif