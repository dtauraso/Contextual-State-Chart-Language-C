#ifndef TRIENODE
#define TRIENODE
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "jsmn/jsmn.h"
#include "state.h"


typedef struct Tokens
{
	int i;
	const char* input;
	jsmntok_t* _tokens;
	jsmntok_t current_token;
	int total_tokens;

}Tokens;

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
	// 
	TrieNode* dict_trie_node;
	TrieNode* context_state_attribute_trie_node;
	bool context_state_is_found;
	bool is_first_mismatch;
	bool need_to_append_more_name;
}TrieNodePackage;

// locations to visit in the trie tree arrays
typedef struct Locations
{
	int* locations;
	int size;
}Locations;
typedef struct TrieNodePackage2
{
	TrieNode* tree_pointer;
	TrieNode* target_pointer;
	int location;
	bool state_there;
	struct ContextState* object_found;

}TrieNodePackage2;

TrieNode* initTrieNode();
TrieNode* initTrieNodeWithNeighborCount(int number_of_possible_neighbors);
int isMatch(char* ith_word, TrieNode* node);
TrieNodePackage* findInTrie2(TrieNode* root, TrieNode* sequence_of_strings);
TrieNode* appendWord(TrieNode* node, char* ith_name);
TrieNode* appendTrieChain(TrieNode* root, struct ContextState* state, TrieNode* name);
void insert(TrieNode* root, struct ContextState* state);
char* copyString(char* b);


int computeLocation(int low, int size,  TrieNode* node, char* target);

bool areNeighborsNull(TrieNode* node, TrieNode* target_chain);

bool canWeSearchWithTheDataAvaliable(TrieNode* node, TrieNode* target_chain);

int matchEdgeCases(TrieNode* node, TrieNode* target_chain);

TrieNodePackage2* makePackage(TrieNode* tree_pointer,
							 TrieNode* target_pointer,
							 int location,
							 bool state_there,
							 struct ContextState* object_found);

TrieNodePackage2* binSearch(TrieNode* node, TrieNode* target_chain);



TrieNode** insertItem(int pos, TrieNode* node, TrieNode* value);


int distance(int pos, int size);


TrieNode* newTrieNode();

TrieNode** newTrieNodes(char* word, int location, int neighbor_count);

bool insert1Item(TrieNode* node, TrieNode* target_chain, int location);



TrieNodePackage2* searchForInsertId(TrieNode* node, TrieNode* target_chain, struct ContextState* target_state);

int insert2(TrieNode* node, TrieNode* target_chain, struct ContextState* target_state);

int lessThan(char* string_1, char* string_2);



void addItem(int* i, jsmntok_t tokens[], const char* input, int j, struct TrieNode* root);
TrieNode* makeTrieTree(Tokens* my_tokens);




Tokens* makeTokens(jsmntok_t tokens[], const char* input, int total_tokens);
jsmntok_t getIthToken(Tokens* my_tokens, int i);

jsmntok_t getToken(Tokens* my_tokens);
bool noTokensLeft(Tokens* my_tokens);

void advanceToken(Tokens* my_tokens);


#endif