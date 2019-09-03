#include "trie_tree.h"

Vector* initVector();
void* getItem(Vector* container, int i);
void append(Vector* container, void* element);
int getPopulation(Vector* container);
void Print(Vector* container);

/*
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
*/
TrieNode2* initTrieNode2()
{
	// assume the dafault type to be stored is an integer
	TrieNode2* my_node = (TrieNode2*) malloc(sizeof(TrieNode2));

	my_node->value = NULL;
	my_node->links = initVector();
	my_node->sorted_link_indecies = initVector();
	my_node->value_type = 0;
	my_node->state = NULL;

	return my_node;

}


/*
typedef struct TrieTree
{
	int root;
	// will be unsorted
	Vector* trie_tree;

}TrieTree;
*/
TrieTree* initTrieTree()
{
	TrieTree* my_trie_tree = (TrieTree*) malloc(sizeof(TrieTree));

	my_trie_tree->trie_tree = initVector();

	// add a node called "root"
	insertString(my_trie_tree, "root");

	my_trie_tree->root = 0;


	//printf("%s\n", ((string*) ((TrieNode2*) getItem(my_trie_tree->trie_tree, my_trie_tree->root))->value)->c_str());
	return my_trie_tree;

}
void insertString(TrieTree* my_trie_tree, string element)
{
	TrieNode2* node = initTrieNode2();

	string* node_string = (string*) malloc(sizeof(string));
	*node_string = element;
	node->value = node_string;
	node->value_type = 1;

	append(my_trie_tree->trie_tree, node);

}
void printTrie(TrieTree* my_trie_tree)
{
	printf("printing ordered dict trie\n");
	// loop through all elements
		// loop thorugh all attributes
	for(int i = 0; i < getPopulation(my_trie_tree->trie_tree); i++)
	{

		TrieNode2* node = (TrieNode2*) getItem(my_trie_tree->trie_tree, i);
		//printf("printing array\n");
		string my_string = *((string*) node->value);

		printf("%i %s\n", i, my_string.c_str());
		printf("links\n");
		Print(node->links);
		printf("sorted_link_indecies\n");
		Print(node->sorted_link_indecies);

	}
}
