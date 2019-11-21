#ifndef TRIE_TREE
#define TRIE_TREE
#include "standard_headers.h"
#include "vector.h"

// int char_limit = 93 possible visible characters as edges

struct Vector;

typedef struct TrieNode2
{
	// assumptions for this class
	// Each word the chars spell out will end with a unique node(holding a letter), hence the branching in the trie tree
	// Each unique node will link to the corresponding word node
	// Each word node will have a list of children, where each child corresponds to the char from the 
	// char trie tree.
	// This enables a few things: printing out the char trie letters as words,
	// adding new char nodes and tracking them in the char trie and the word trie
	// 

	// all links are integers
	// don't use this variable
	void* value; // has been a string*
	char my_value;
	// will be unsorted
	Vector* links;  // ints, word node links to each other
	int char_links[243]; // any number > 242 doesn't cause a catastrophic error for the program

	Vector* chars_from_edges;

	Vector* word_letters; // ints for word nodes to link to char nodes
	int value_type;
	// 0 -> int
	// 1 -> string
	int state_id; // location of state in state vector

	int word_counterpart; // set in the last character of the word to the word node

	// probably not being used
	bool start_of_word;
	bool end_of_word; // marking the char nodes added so the words can be added in on the second pass
	int parent;


}TrieNode2;
TrieNode2* TrieNode2initTrieNode2();
bool TrieNode2DeleteTrieNode2(TrieNode2* node);

void* TrieNode2GetValue(TrieNode2* node);

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
TrieTree* TrieTreeInitTrieTree();
void TrieTreePush(Vector* container, int new_item);
int TrieTreeGetNextNode(TrieTree* my_trie_tree, Vector* node_id_stack, Vector* ith_edge_stack);
int TrieTreeGetVariable(TrieTree* my_trie_tree, string name);

int TrieTreeSearch(TrieTree* my_trie_tree, Vector* name /* strings*/);


// prepend trieTree to all functions
void TrieTreeInsertString(TrieTree* my_trie_tree, char element, int state_id);
int TrieNode2GetLastNode(TrieTree* my_trie_tree, int prev_node_id);
int TrieNode2GetLastEdge(TrieTree* my_trie_tree, int prev_node_id);
int TrieNode2GetWordCounterpart(TrieTree* my_trie_tree, int prev_node_id);
TrieNode2* TrieNode2GetWord(TrieTree* my_trie_tree, int prev_node_id);
string* TrieNode2MakeStringFromWord(TrieTree* my_trie_tree, int prev_node_id);

bool TrieTreeEdgeIndicatesToMakeChild(int letter_edge);


int TrieTreeFindLastPrevNode(TrieTree* my_trie_tree, Vector* path);

int TrieTreeFindLastWordNode(TrieTree* my_trie_tree, Vector* path);

void TrieTreeAddSoubtleCase(TrieTree* my_trie_tree, int prev_node_id, int prev_proxy_id, Vector* name /* strings*/);


void TrieTreeInsertWord(TrieTree* my_trie_tree, string* new_number_ptr, TrieNode2* node_found2, int state_id);
// testing this version
Vector* TrieTreeInsertWords2(TrieTree* my_trie_tree, Vector* name /* strings*/, int expected_id);

// Vector* TrieTreeInsertWords(TrieTree* my_trie_tree, Vector* name /* strings*/, int expected_id);
TrieTree* TrieTreeInsertEdges(TrieTree* my_general_tree, TrieTree* my_trie_tree, Vector* names /* vectors of strings*/);

int TrieTreeUpdateId(TrieTree* my_trie_tree, int old_id);

void TrieTreeCutLinkToFirstNodeInPath(	TrieTree* my_trie_tree,
								Vector* name,
								int* lower_bound_ptr,
								int start_node,
								int ith_string_in_input);
void TrieTreeEraseEdgeToTopCharNode(Vector* char_nodes_matching,
							int j,
							TrieTree* my_trie_tree,
							char top_node_value);
int TrieTreeDeleteWords(TrieTree* my_trie_tree, Vector* name /* strings*/);

void TrieTreePrintTrie(TrieTree* my_trie_tree);
void TrieTreePrintWordTrie(TrieTree* my_trie_tree);

void TrieTreePrintTrieWords(TrieTree* my_trie_tree);

void TrieTreePrintTrieRecursive(TrieTree* my_trie_tree, int root, string indents);
void TrieTreeTest();

#endif