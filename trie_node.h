#ifndef TRIENODE
#define TRIENODE
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "jsmn/jsmn.h"
#include "state.h"

// for storing the name -> ContextState map
typedef struct TrieNode
{

	char* word;
	struct TrieNode** neighbors;
	int neighbors_count;

	int size; // power of 2
	struct ContextState* object;
}TrieNode;

/*
dummy node
		root2->word = NULL;
		root2->object = NULL;
		root2->neighbors = malloc(sizeof(TrieNode*) * root->call_count);
		root2->neighbors_count = 0;
		root2->size = 0;

*/

typedef struct TrieNodePackage
{
	TrieNode* dict_trie_node;
	TrieNode* context_state_attribute_trie_node;
	bool context_state_is_found;
	bool is_first_mismatch;
	bool need_to_append_more_name;
}TrieNodePackage;

TrieNode* initTrieNode();
TrieNode* initTrieNodeWithNeighborCount(int number_of_possible_neighbors);
TrieNode* arrayOfArrays(int* i, jsmntok_t tokens[], const char* input, int token_count);
int isMatch(char* ith_word, TrieNode* node);
TrieNodePackage* findInTrie2(TrieNode* root, TrieNode* sequence_of_strings);
TrieNode* appendWord(TrieNode* node, char* ith_name);
TrieNode* appendTrieChain(TrieNode* root, struct ContextState* state, TrieNode* name);
void insert(TrieNode* root, struct ContextState* state);
TrieNode* convertLispChainToTrieNodeChain(LispNode* root);

#endif