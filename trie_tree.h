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

		"I am a state. I am a little bit more detailed. I am describing many dimentions of complexity"

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

		I see this as a high level inefficiency that may be addressed more in the comming decades.
		The languages do their job very well and I'm not interested in replacing them.  My interest
		is to give them flexible features to provide more clarity and expressability to the programmer.

		I could be misguided about how much the field can be improved, but adding meaningful and valuable features
		to programming languages seems like a good idea if it can be done.



	*/


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


char* makeIndents(int number_of_indents);

void TrieTreePrintTrieRecursive(TrieTree* my_trie_tree, int current, int number_of_indents, Vector* word_found);

void TrieTreeTest();

#endif