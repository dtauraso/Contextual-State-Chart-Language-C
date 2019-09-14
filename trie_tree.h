#ifndef TRIE_TREE
#define TRIE_TREE
#include "standard_headers.h"
#include "vector.h"

struct Vector;
// only for ensuring insert follows a linear control flow from searching to inserting
typedef struct TrieMatch
{
	// (id of parent node, ith string, did we find a match for the ith string, location to insert the link for the child node)
	int parent_node;
	int ith_string;
	bool did_find_a_match;
	int exptected_location_in_parent_node_children;
}TrieMatch;
typedef struct TrieNode2
{
	// the links are integers
	void* value; // has been a string*
	// will be unsorted
	Vector* links;  // ints
	// will be sorted
	//Vector* sorted_link_indecies; // ints
	int value_type;
	// 0 -> int
	// 1 -> string
	int state_id; // location of state in state vector

}TrieNode2;
TrieNode2* initTrieNode2();
bool deleteTrieNode2(TrieNode2* node);

void* getValue(TrieNode2* node);

typedef struct TrieTree
{
	int root;
	// will be unsorted
	Vector* trie_tree;
	int max_state_id;

}TrieTree;
TrieTree* initTrieTree();

void insertString(TrieTree* my_trie_tree, string element, bool is_last_word);
void insertWord(TrieTree* my_trie_tree, string* new_number_ptr, TrieNode2* node_found2, bool is_last_word);
Vector* insertWords(TrieTree* my_trie_tree, Vector* name /* strings*/);
int updateId(TrieTree* my_trie_tree, int old_id);

int deleteWords(TrieTree* my_trie_tree, Vector* name /* strings*/);

void printTrie(TrieTree* my_trie_tree);
void printTrieRecursive(TrieTree* my_trie_tree, int root, string indents);

#endif