#ifndef TRIE_TREE
#define TRIE_TREE
#include "standard_headers.h"
#include "vector.h"

// int char_limit = 93 possible visible characters as edges

struct Vector;

typedef struct TrieNode2
{
	// assumptions for this struct
	// Each word the chars spell out will end with a unique node(holding a letter), hence the branching in the trie tree
	// Each unique node will link to the corresponding word node
	// Each word node will have a list of children, where each child corresponds to the char from the 
	// char trie tree.
	
	// This enables a few things:

	// printing out the char trie letters as words,
	// adding new char nodes and tracking them in the char trie and the word trie
	// deleting char nodes and tracking them in the char trie and the word trie


	// all links are integers

	char my_value;


	// save memory for the links in the trie by only storing necessary edges
	Vector* links;  // ints

	int state_id; // location of state in state vector

	bool end_of_word;


}TrieNode2;
TrieNode2* TrieNode2initTrieNode2();
bool TrieNode2DeleteTrieNode2(TrieNode2* node);

char TrieNode2GetValue(TrieNode2* node);

typedef struct TrieTree
{
	// features the user should be able to do with state "variables"
	// add variable
	// add same variable n times
	// all variables have a unique name
	// conditions we want for this
	// each instance of a class has local variables unique to that instance
	// global scope is the entire state machine
	// each state(class) will have local scope for the submachine
	// 
	/*
		i, 0
		i, 1
		i, 2
		That way the user can make as many "i"'s as they want as long as each
		"i" will be stored in a different submachine
		this is like having many instances of a class each having their own "i"

		This is needed because the state machine represents all control flow elements(if, while)
		and all data elements(class, int, string, container) so we must have the ability for the user
		to treat making variables in the state machine to be as close as possible to how variables
		are made in programming languages.

		This is a trie tree to enable n dimensions when describing a state.

		["I am a state", "I am a little bit more detailed", "I am describing 3 dimentions of complexity"]

		We want any complexity level to approximate the complex states of mind present in a humand mind
		That requires represening complex states in a general way(General AI).  Numenta has done a great job
		with this, and while AGI isn't here, parts of it are here and can be used as a programming tool
		to aid the programmer.

		Why would we want this?  We already have many programming languages that can do any computable task.
		There are many different kinds of languages for different tasks.

		That is true, but computers hardly have a way of relating to how we think.  Based on the current
		general ai thought, we have a single way of representing all kinds of information.  It's much harder
		for the brain to have hundreds of different kinds of representations in the same organ
		and still maintain high efficiency.  This happens to be exactly what the programming languages and frameworks
		represent.

		I see this as a very high level inefficiency that may be addressed more in the comming decades.
		The languages do their job very well and I'm not interested in replacing them.  My interest
		is to give them flexible features to provide more clarity and expressability to the programmer.

		I could be misguided about how much the field can be improved, but adding meaningful and valuable features
		to programming languages seems like a good idea if it can be done.



	*/


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
Vector* TrieTreeInsertWords2(TrieTree* my_trie_tree, Vector* name /* strings*/);

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