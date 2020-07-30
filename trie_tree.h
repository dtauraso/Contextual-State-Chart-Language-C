#ifndef TRIE_TREE
#define TRIE_TREE
#include "standard_headers.h"
#include "vector.h"

struct Vector;
typedef struct TrieNode
{

	// all links are integers

	int my_value;


	// save memory for the links in the trie by only storing necessary edges
	Vector* links;  // ints

	int state_id; // location of state in state vector

	bool end_of_word;
	bool is_auto_generated;


}TrieNode;
TrieNode* TrieNodeinitTrieNode();

char TrieNodeGetValue(TrieNode* node);

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


	// the different instance of the same base word are connected and you can use a formula to 
	// generate the next one. Hash tables don't let you connect common words together the same way
	// autogeneration would be possible with a hash table but the extra symbols would grow really fast(linear with the 
	// total number of common words already stored)
	// using a trie tree this space complexity goes from linear to log_{#of children}^{#common words}
	// I have not figured out how to make a decent hash table.
	// will be unsorted
	// trie tree of characters
	// a trie tree is also easier for me to think about and it lets me put in any features that takes advantage of a trie wheras a hash table
	// may not be able to do those things(partial match)


	Vector* trie_tree;
}TrieTree;
bool TrieTreeDeleteTrieNode(TrieTree* my_trie_tree, int current);

TrieTree* TrieTreeInitTrieTree();

int TrieTreeGetJthLink(TrieTree* my_trie_tree, int i, int j);

int TrieTreeDoLinksPointToLeter(TrieTree* my_trie_tree, int current, int letter);

int TrieTreeSearch(TrieTree* my_trie_tree, Vector* name);

void TrieTreeInsertString(TrieTree* my_trie_tree,
							int element,
							int state_id,
							bool is_end_of_string);


TrieNode* TrieTreeGetNode(TrieTree* my_trie_tree, int current);

Vector* TrieTreeGetEdges(TrieTree* my_trie_tree, int current);

int TrieTreeGetFirstNodeId(TrieTree* my_trie_tree, int current);

int TrieTreeGetNextNodeId(TrieTree* my_trie_tree, int current, int ith_link);

int TrieTreeGetLastLink(TrieTree* my_trie_tree, int current);

int TrieTreeGetLinkCount(TrieTree* my_trie_tree, int current);

int TrieTreeGetMyValue(TrieTree* my_trie_tree, int current);

bool TrieTreeGetEndOfWord(TrieTree* my_trie_tree, int current);

void TrieTreeAddNewNode(TrieTree* my_trie_tree, int letter, bool at_end_of_word, int current);

int TrieTreeComputeNextVisibleCharacter(int last_link, int max_visible_character);

Vector* TrieTreeGenerateExtraSymbols(TrieTree* my_trie_tree, int current, Vector* name);

int TrieTreeInsertWordsDictionary(TrieTree* my_trie_tree, Vector* name);

Vector* TrieTreeInsertWords(TrieTree* my_trie_tree, Vector* name);

int TrieTreeDelete(TrieTree* my_trie_tree, Vector* name);

void TrieTreePrintTrie(TrieTree* my_trie_tree);


char* TrieTreeMakeIndents(int number_of_indents);

void TrieTreePrintTrieRecursive(TrieTree* my_trie_tree, int current, int number_of_indents, Vector* word_found);

void TrieTreeTest();

#endif