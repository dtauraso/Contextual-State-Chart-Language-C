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
	// don't use this variable
	void* value; // has been a string*
	char my_value;
	// will be unsorted
	Vector* links;  // ints
	int char_links[256];
	Vector* chars_from_edges;
	// will be sorted
	//Vector* sorted_link_indecies; // ints

	Vector* word_letters; // for word tree
	int value_type;
	// 0 -> int
	// 1 -> string
	int state_id; // location of state in state vector

	int word_counterpart; // set in the last character of the word to the word node
	bool start_of_word;

}TrieNode2;
TrieNode2* initTrieNode2();
bool deleteTrieNode2(TrieNode2* node);

void* getValue(TrieNode2* node);

typedef struct TrieTree
{
	int root;
	// will be unsorted
	// trie tree of characters
	Vector* trie_tree;

	// trie tree of words(just a tree refering to the character trie)
	Vector* word_tree;
	int max_state_id;

}TrieTree;
TrieTree* initTrieTree();

Vector* innerSearchForString(TrieTree* my_trie_tree, Vector* name /* strings*/);

void insertString(TrieTree* my_trie_tree, char element, int state_id);
void insertWord(TrieTree* my_trie_tree, string* new_number_ptr, TrieNode2* node_found2, int state_id);
Vector* insertWords(TrieTree* my_trie_tree, Vector* name /* strings*/);
int updateId(TrieTree* my_trie_tree, int old_id);

void cutLinkToFirstNodeInPath(	TrieTree* my_trie_tree,
								Vector* name,
								int* lower_bound_ptr,
								int start_node,
								int ith_string_in_input);

int deleteWords(TrieTree* my_trie_tree, Vector* name /* strings*/);

void printTrie(TrieTree* my_trie_tree);
void printWordTrie(TrieTree* my_trie_tree);

void printTrieWords(TrieTree* my_trie_tree);

void printTrieRecursive(TrieTree* my_trie_tree, int root, string indents);

#endif