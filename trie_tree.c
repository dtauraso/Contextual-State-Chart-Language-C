#include "trie_tree.h"

Vector* VectorInitVector();
void* VectorGetItem(Vector* container, int i);
void VectorAppend(Vector* container, void* element);
int VectorGetPopulation(Vector* container);
void VectorPrint(Vector* container);

/*
typedef struct TrieNode2
{
	// the links are integers
	void* value;
	// will be unsorted
	Vector* links;  // ints
	int value_type;
	// 0 -> int
	// 1 -> string

	int state_id; // location of state in state vector

}TrieNode2;
*/

TrieNode2* TrieNode2initTrieNode2()
{
	// assume the dafault type to be stored is an integer
	TrieNode2* my_node = (TrieNode2*) malloc(sizeof(TrieNode2));

	my_node->links = VectorInitVector();
	my_node->my_value = 0;
	my_node->state_id = -1;
	my_node->end_of_word = false;
	return my_node;

}
bool TrieNode2DeleteTrieNode2(TrieTree* my_trie_tree, int current)
{
	TrieNode2* temp_node = ((TrieNode2*) my_trie_tree->trie_tree->values[current]);
	// VectorDeleteAllItems( ((TrieNode2*) my_trie_tree->trie_tree->values[current])->links);
	// ((TrieNode2*) my_trie_tree->trie_tree->values[current])->links = NULL;
	// free(my_trie_tree->trie_tree->values[current]);
	// my_trie_tree->trie_tree->values[current] = NULL;
	if(temp_node == NULL)
	{
		return false;
	}
	if(temp_node->links == NULL)
	{
		
		free(my_trie_tree->trie_tree->values[current]);
		my_trie_tree->trie_tree->values[current] = NULL;
		return true;
	}
	// VectorDeleteAllItems(node->links);
	// node->links = NULL;
	// free(node);
	// node = NULL;
	VectorDeleteAllItems(temp_node->links);
	((TrieNode2*) my_trie_tree->trie_tree->values[current])->links = NULL;

	free(my_trie_tree->trie_tree->values[current]);
	my_trie_tree->trie_tree->values[current] = NULL;
	// printf("here %i\n", node);
	// is it possible I'm only deleting the copy of the reference?

	return true;

}
char TrieNode2GetValue(TrieNode2* node)
{
	if(node == NULL)
	{
		return '\0';

	}

	return node->my_value;
}


/*
typedef struct TrieTree
{
	int root;
	// will be unsorted
	Vector* trie_tree;

}TrieTree;
*/
TrieTree* TrieTreeInitTrieTree()
{
	TrieTree* my_trie_tree = (TrieTree*) malloc(sizeof(TrieTree));

	my_trie_tree->trie_tree = VectorInitVector();
	my_trie_tree->word_tree = VectorInitVector();

	// add a node called "root"
	char root = 'r';
	TrieTreeInsertString(my_trie_tree, root, -1);

	TrieNode2* node = TrieNode2initTrieNode2();


	node->links = VectorInitVector();

	VectorAppend(my_trie_tree->word_tree, node);


	my_trie_tree->root = 0;
	my_trie_tree->max_state_id = -1;

	// quickly print the root
	//printf("%s\n", ((string*) ((TrieNode2*) VectorGetItem(my_trie_tree->trie_tree, my_trie_tree->root))->value)->c_str());
	return my_trie_tree;

}
// (id of parent node, ith string, did we find a match for the ith string, location to insert the link for the child node)
// trieTreeInsertStrings
/*

	id of node to start inserting as a child
	ith string to start inserting
	wether we need to insert? is this a valid question, considering everything is inserted?
	the id of the child link where we start inserting
*/

// deleteStrings
/*
	id of node where we start deleting the child(requires another search because search doesn't look for this node)

	
*/
void TrieTreePush(Vector* container, int new_item)
{
	if(container == NULL)
	{
		return;
	}
	int* new_item_ptr = (int*) malloc(sizeof(int));
	*new_item_ptr = new_item;
	VectorAppend(container, new_item_ptr);
}
int TrieTreeGetNextNode(TrieTree* my_trie_tree, Vector* node_id_stack, Vector* ith_edge_stack)
{
	if(my_trie_tree == NULL || node_id_stack == NULL || ith_edge_stack == NULL)
	{
		return -1;
	}
	int top_node_id = *((int*) VectorGetItem(node_id_stack, VectorGetPopulation(node_id_stack) - 1));
	TrieNode2* top_node = (TrieNode2*) VectorGetItem(my_trie_tree->word_tree, top_node_id);

	int top_ith_edge = *((int*) VectorGetItem(ith_edge_stack, VectorGetPopulation(ith_edge_stack) - 1));
	return *((int*) VectorGetItem(top_node->links, top_ith_edge) );

}

// int search
/*
TrieTreePush items to a stack
when done, return a pointer to the stack
*/


int getLinkCount(TrieTree* my_trie_tree, int i)
{
	return VectorGetPopulation( ((TrieNode2*) VectorGetItem(my_trie_tree->trie_tree, i)) ->links);
}
int getJthLink(TrieTree* my_trie_tree, int i, int j)
{
	TrieNode2* current = (TrieNode2*) VectorGetItem(my_trie_tree->trie_tree, i);
	return *((int*) VectorGetItem(current->links, j));
}
int doLinksPointToLeter(TrieTree* my_trie_tree, int current, int letter)
{

	return -1;
}

int doLinksPointToLeter2(TrieTree* my_trie_tree, int current, int letter)
{
	// printf("problem\n");
	// printf("%x\n", my_trie_tree);
	// printf("%x\n", node);

	if(my_trie_tree == NULL)
	{

		return -1;
	}
	// printf("about to search\n");

	int size = getLinkCount(my_trie_tree, current);
	// printf("size %i\n", size);
	// loop through the links for a match to the letter
	for(int j = 0; j < size; j++)
	{
		// printf("%i\n", j);
		// printf("node id %i\n", *((int*) VectorGetItem(node->links, j)));
		// TrieTreePrintTrie(my_trie_tree);
		// printf("size of trie %i\n", VectorGetPopulation(my_trie_tree->trie_tree));
		// have to save this as an integer first or the accessing will not work
		int id = getJthLink(my_trie_tree, current, j);
		// the ndoe at id 1 exists but can't be accessed
		TrieNode2* node = (TrieNode2*) VectorGetItem(my_trie_tree->trie_tree, id);
		// printf("node %i", node);
		// printf("here\n");
		if(node == NULL){}
		else if(node->my_value == letter)
		{
			return j;
		}
	}
	return -1;
}

int TrieTreeSearch(TrieTree* my_trie_tree, Vector* name)
{
	// name vector uses integers
	// we can show them as chars when printing them out
	if(my_trie_tree == NULL || name == NULL)
	{
		return -1;
	}

	int current = 0;

	// search untill no match is possible, or input is empty


	int size = VectorGetPopulation(name);

	for(int i = 0; i < size; i++)
	{
		// printf("current %i\n", current);
		// void* -> int* -> int
		int letter =  *((int*) name->values[i]);

		// printf("here char %c current %i\n", letter, current);
		// next_node_id is the index of the next letter cell in trie tree
		int j = doLinksPointToLeter2(my_trie_tree, current, letter);
		// printf("j %i\n", j);

		// no more edges to visit
		if(j == -1)
		{
			return -1;			
		}
		else
		{
			int next_node_id = getJthLink(my_trie_tree, current, j);
			// printf("next_node_id %i\n", next_node_id);
			current = next_node_id;
		}
	}
	return current;
}
void TrieTreeInsertString2(TrieTree* my_trie_tree,
							int element,
							int state_id,
							bool is_end_of_string)
{
	if(my_trie_tree == NULL)
	{
		return;
	}
	// printf("inserting string\n");
	TrieNode2* node = TrieNode2initTrieNode2();

	//string* node_string = (string*) malloc(sizeof(string));
	//node_string = element;
	//node->value = element;
	node->my_value = element;
	// node->value_type = 1;
	node->end_of_word = false;
	if(is_end_of_string)
	{
		node->end_of_word = true;
	}
	// this is to measure the dimentions by using space (32) as a delimiter
	if(element == 32)
	{
		node->end_of_word = true;
	}
	node->state_id = state_id;
	VectorAppend(my_trie_tree->trie_tree, node);
	// printf("done adding\n");
}


void TrieTreeInsertString(TrieTree* my_trie_tree, char element, int state_id)
{
	if(my_trie_tree == NULL)
	{
		return;
	}
	TrieNode2* node = TrieNode2initTrieNode2();

	//string* node_string = (string*) malloc(sizeof(string));
	//node_string = element;
	//node->value = element;
	node->my_value = element;
	// node->value_type = 1;
	// node->parent = -1;
	node->state_id = state_id;
	VectorAppend(my_trie_tree->trie_tree, node);

}




// TrieNode2* TrieNodeGetTrieNode()

TrieTree *TrieTreeInsertEdges(TrieTree *my_general_tree, TrieTree *my_trie_tree, Vector *names)
{
	return NULL;
}
TrieNode2* getNode(TrieTree* my_trie_tree, int current)
{
	return (TrieNode2*) VectorGetItem(my_trie_tree->trie_tree, current);
}
Vector* getEdges(TrieTree* my_trie_tree, int current)
{
	TrieNode2* current_node = (TrieNode2*) VectorGetItem(my_trie_tree->trie_tree, current);
	return current_node->links;
}
int getFirstNodeId(TrieTree* my_trie_tree, int current)
{
	// get the current node
	// void* -> TrieNode2*
	TrieNode2* current_node = (TrieNode2*) VectorGetItem(my_trie_tree->trie_tree, current);

	// void* -> int* -> int
	return *((int*) VectorGetItem(current_node->links, 0));
}

int getNextNodeId(TrieTree* my_trie_tree, int current, int ith_link)
{
	// get the current node
	// void* -> TrieNode2*
	TrieNode2* current_node = (TrieNode2*) VectorGetItem(my_trie_tree->trie_tree, current);

	// void* -> int* -> int
	return *((int*) VectorGetItem(current_node->links, ith_link));
}
int getLastLink(TrieTree* my_trie_tree, int current)
{
	TrieNode2* current_node = (TrieNode2*) VectorGetItem(my_trie_tree->trie_tree, current);
	return VectorGetPopulation(current_node->links) - 1;
}
int getLinkCount2(TrieTree* my_trie_tree, int current)
{
	TrieNode2* current_node = (TrieNode2*) VectorGetItem(my_trie_tree->trie_tree, current);
	return VectorGetPopulation(current_node->links);
}
int getMyValue(TrieTree* my_trie_tree, int current)
{
	TrieNode2* current_node = (TrieNode2*) VectorGetItem(my_trie_tree->trie_tree, current);
	return current_node->my_value;
}
bool getEndOfWord(TrieTree* my_trie_tree, int current)
{
	TrieNode2* current_node = (TrieNode2*) VectorGetItem(my_trie_tree->trie_tree, current);
	return current_node->end_of_word;
}
void addNewNode(TrieTree* my_trie_tree, int letter, bool at_end_of_word, int current)
{
	TrieTreeInsertString2(	my_trie_tree,
							letter,
							-1,
							// are we at end of word?
							at_end_of_word);

	// add it into the link at the prev cell
	VectorAppendInt(	((TrieNode2*) VectorGetItem(my_trie_tree->trie_tree, current))->links,
						VectorGetPopulation(my_trie_tree->trie_tree) - 1);
}
int computeNextVisibleCharacter(int last_link, int max_visible_character)
{
	return ((last_link + 1) % max_visible_character) + 33;
}
Vector* generateExtraSymbols(TrieTree* my_trie_tree, int current, Vector* name)
{
	// we either have 0 extra symbols to traverse or n

	// we can allow 93 children to be an extra symbol(93 different viewable integers)
	// We start at 33 and count 93 letters to get to the ascii value of 126
	int max_visible_character = 126; 

	int count = getLinkCount2(my_trie_tree, current);
	// we have 0 extra symbols to traverse
	if(count >= 0 && count < max_visible_character)
	{
		int last_link, next_link;
		last_link = 0;
		next_link = 33;
		if(count > 0)
		{
			last_link = getLastLink(my_trie_tree, current);
			next_link = computeNextVisibleCharacter(last_link, max_visible_character);
		}
		
		addNewNode(my_trie_tree, next_link, /*at_end_of_word*/ 1, current);
		VectorAppendInt(name, next_link);
		// TrieTreePrintTrie(my_trie_tree);
		// VectorPrint(name);
		return name;
	}
	// we have n extra symbols to traverse
	while(getLinkCount2(my_trie_tree, current) == max_visible_character)
	{
		// get to the next node
		current = getNextNodeId( 	my_trie_tree,
										current,
										getLastLink(my_trie_tree, current));
		// add the next node's value to name
		VectorAppendInt(name, getMyValue(my_trie_tree, current));
	}
	int last_link = getLastLink(my_trie_tree, current);

	int next_link = computeNextVisibleCharacter(last_link, max_visible_character);

	addNewNode(my_trie_tree, next_link, /*at_end_of_word*/ 1, current);

	VectorAppendInt(name, next_link);
	// TrieTreePrintTrie(my_trie_tree);
	// VectorPrint(name);
	return name;
}
Vector* TrieTreeInsertUniqueWord(TrieTree* my_trie_tree, Vector* name)
{
	
	return NULL;
}
Vector* TrieTreeInsertWords2(TrieTree* my_trie_tree, Vector* name)
{
	// insert characters of name into the trie tree
	// if the name is already in there, generate a new name so the user can add the same name
	// uniquely. It's different from how you usually use a trie tree by design.
	// integers are used as the trackers because it's easier to work with an integer than a void pointer
	if(my_trie_tree == NULL || name == NULL)
	{
		return NULL;
	}


	int current = 0;

	// search untill no match is possible, or input is empty


	int size = VectorGetPopulation(name);
	int matches = 0;
	for(int i = 0; i < size; i++)
	{
		// printf("current %i\n", current);
		// void* -> int* -> int
		int letter =  *((int*) name->values[i]);

		// printf("here char %c current %i\n", letter, current);
		// next_node_id is the index of the next letter cell in trie tree
		int j = doLinksPointToLeter2(my_trie_tree, current, letter);
		// printf("j %i\n", j);

		
		// there are no edges to search to
		if(j == -1)
		{
			// add a new node with letter
			addNewNode(my_trie_tree, letter, /*at_end_of_word*/ i == size - 1, current);

			current = getNextNodeId( 	my_trie_tree,
										current,
										getLastLink(my_trie_tree, current));
		}
		else
		{
			matches++;
			int next_node_id = getJthLink(my_trie_tree, current, j);//doLinksPointToLeter(my_trie_tree, current, letter);
			current = next_node_id;
		}
	}


	if(matches < VectorGetPopulation(name))
	{
		return name;
	}

	name = generateExtraSymbols(my_trie_tree, current, name);
	return name;
}
// outer insert function that the regular insert uses
// inner insert function that only inserts unique items for the hash table
int TrieTreeDelete(TrieTree* my_trie_tree, Vector* name)
{
	// name vector uses integers
	// we can show them as chars when printing them out
	if(my_trie_tree == NULL || name == NULL)
	{
		return -1;
	}

	int current = 0;

	// search untill no match is possible, or input is empty

	int last_fork = 0;
	int edge_id_after_last_fork = 0;
	int size = VectorGetPopulation(name);
	// TrieTreePrintTrie(my_trie_tree);

	for(int i = 0; i < size; i++)
	{
		// printf("current %i\n", current);
		// void* -> int* -> int
		int letter =  *((int*) name->values[i]);
		
		// printf("here char %c current %i last fork %i\n", letter, current, last_fork);
		// next_node_id is the index of the next letter cell in trie tree
		int j = doLinksPointToLeter2(my_trie_tree, current, letter);
		// printf("j %i\n", j);
		if(j == -1)
		{
			return -1;
		}
		else
		{
			// branch of at least 2 is a fork
			if(getLinkCount2(my_trie_tree, current) > 1)
			{
				// printf("link count at current %i is %i\n", current, getLinkCount2(my_trie_tree, current) );
				last_fork = current;
				edge_id_after_last_fork = j;
			}
			current = getNextNodeId(my_trie_tree, current, j);
		}
	}
	// if current has edges, don't delete anything
	if(getLinkCount2(my_trie_tree, current) > 0)
	{
		// don't delete anything but the delete function ran successfully
		return 1;
	}
	// TrieTreePrintTrie(my_trie_tree);
	// printf("last fork %i, edge id %i\n", last_fork, edge_id_after_last_fork);
	// printf("about to delete \n");
	int first_node_to_delete = getNextNodeId( 	my_trie_tree,
										last_fork,
										edge_id_after_last_fork);
	
	VectorDeleteItem(getEdges(my_trie_tree, last_fork), edge_id_after_last_fork);
	// TrieTreePrintTrie(my_trie_tree);
	// start from last_fork at edge_id_after_last_fork and erase all the nodes
	// delete the edge
	// delete all nodes from the edge
	while(first_node_to_delete != current)
	{
		// printf("first_node_to_delete %i, current %i\n", first_node_to_delete, current);

		// save node id
		int node_to_delete = first_node_to_delete;
		// printf("delete node at %i\n", node_to_delete);
		// move to the next node

		first_node_to_delete = getFirstNodeId( 	my_trie_tree,
										first_node_to_delete);
		// delete previous node
		TrieNode2DeleteTrieNode2(my_trie_tree, node_to_delete);

		// TrieNode2DeleteTrieNode2(getNode(my_trie_tree, node_to_delete));

		// TrieTreePrintTrie(my_trie_tree);
	}
	// printf("first_node_to_delete %i, current %i\n", first_node_to_delete, current);

	TrieNode2DeleteTrieNode2(my_trie_tree, current);
	// TrieTreePrintTrie(my_trie_tree);
	return 1;
}

void TrieTreeEraseEdgeToTopCharNode(Vector* char_nodes_matching,
							int j,
							TrieTree* my_trie_tree,
							char top_node_value){}

int TrieTreeDeleteWords(TrieTree* my_trie_tree, Vector* name /* strings*/){return 0;}

void TrieTreePrintTrie(TrieTree* my_trie_tree)
{
	if(my_trie_tree == NULL)
	{
		return;
	}
	printf("printing ordered dict trie\n");
	// loop through all elements
		// loop thorugh all attributes
	for(int i = 0; i < VectorGetPopulation(my_trie_tree->trie_tree); i++)
	{
	
		TrieNode2* node = (TrieNode2*) VectorGetItem(my_trie_tree->trie_tree, i);
		if(node == NULL)
		{
			printf("%i empty\n\n", i);

		}
		else
		{
			printf("printing array\n");

			printf("%i |%c| end of word %i state %i\n", i, node->my_value, node->end_of_word, node->state_id);
			printf("links\n");
			for(int j = 0; j < VectorGetPopulation(node->links); j++)
			{
				int k = *((int*) VectorGetItem(node->links, j));
				printf("|%i|", k);

			}
			if(VectorGetPopulation(node->links) == 0)
			{
				printf("||");
			}

			printf("\n\n");
		}
	}
}

void TrieTreePrintWordTrie(TrieTree* my_trie_tree){}
void TrieTreePrintTrieWords(TrieTree* my_trie_tree){}
char* makeIndents(int number_of_indents)
{
	// printf("indents to make %i\n", number_of_indents);
	char* indents = (char*) malloc(sizeof(char) * (number_of_indents + 1));
	memset(indents, ' ', number_of_indents);
	indents[number_of_indents] = '\0';
	return indents;
}
void TrieTreePrintTrieRecursive2(TrieTree* my_trie_tree, int current, int number_of_indents, Vector* word_found)
{

	if(current < 0)
	{
		return;
	}
	// printf("current %i\n", current);
	// VectorPrint(word_found);
	int current_letter = getMyValue(my_trie_tree, current);
	// printf("letter |%c|\n", current_letter);
	VectorAppendInt(word_found, current_letter);
	// printf("added letter\n");
	if(getEndOfWord(my_trie_tree, current))
	{
		// printf("end of word\n");
		printf("%s|", makeIndents(number_of_indents));
		int size = VectorGetPopulation(word_found);
		for(int i = 0; i < size; i++)
		{
			int letter = *((int*) VectorGetItem(word_found, i));
			printf("%c", letter);
		}
		printf("|\n");
		// VectorPrint(word_found);
		// empty container
		VectorDeleteAllItems2(word_found);
		// printf("here after vector was emptied\n");
		// can't print out an empty vector
		// VectorPrint(word_found);
		number_of_indents += (size) + 2;
		// printf("indents %i\n", size);

	}
	// printf("getting the link count\n");
	// printf("link count %i\n", getLinkCount2(my_trie_tree, current));
	if(getLinkCount2(my_trie_tree, current) == 1)
	{
		// printf("1 link\n");
		int x = getNextNodeId(my_trie_tree, current, 0);
		// printf("%i\n", x);
		TrieTreePrintTrieRecursive2(	my_trie_tree,
										x,
										number_of_indents,
										word_found);
	}
	else
	{
		int link_count = getLinkCount2(my_trie_tree, current);
		// printf("%i links\n", link_count);
		for(int i = 0; i < link_count; i++)
		{
			Vector* branch_vector = VectorCopyVector(word_found);
			
			TrieTreePrintTrieRecursive2(my_trie_tree,
										getNextNodeId(my_trie_tree, current, i),
										number_of_indents,
										branch_vector);
		}	
	}
}



void TrieTreeTest()
{
	TrieTree* my_trie_tree = TrieTreeInitTrieTree();
	printf("inserting\n");
	// each name in the tree is made to be unique so duplicates get extra symbols
	Vector* name2 = TrieTreeInsertWords2(my_trie_tree, VectorMakeVectorOfChars("abvf t"));
	VectorPrint(name2);
	printf("result 2 %i\n\n", TrieTreeSearch(my_trie_tree, name2));

	Vector* name31 = TrieTreeInsertWords2(my_trie_tree, VectorMakeVectorOfChars("abvs o"));
	VectorPrint(name31);
	printf("result 31 %i\n\n", TrieTreeSearch(my_trie_tree, name31));

	Vector* name32 = TrieTreeInsertWords2(my_trie_tree, VectorMakeVectorOfChars("abvs x"));
	VectorPrint(name32);
	printf("result 32 %i\n\n", TrieTreeSearch(my_trie_tree, name32));

	Vector* name35 = TrieTreeInsertWords2(my_trie_tree, VectorMakeVectorOfChars("abvs x"));
	VectorPrint(name35);
	printf("result 35 %i\n\n", TrieTreeSearch(my_trie_tree, name35));

	Vector* name36 = TrieTreeInsertWords2(my_trie_tree, VectorMakeVectorOfChars("abvs x"));
	VectorPrint(name36);
	printf("result 36 %i\n\n", TrieTreeSearch(my_trie_tree, name36));

	Vector* name37 = TrieTreeInsertWords2(my_trie_tree, VectorMakeVectorOfChars("abvs x"));
	VectorPrint(name37);
	printf("result 37 %i\n\n", TrieTreeSearch(my_trie_tree, name37));

	Vector* name38 = TrieTreeInsertWords2(my_trie_tree, VectorMakeVectorOfChars("abvs x"));
	VectorPrint(name38);
	printf("result 38 %i\n\n", TrieTreeSearch(my_trie_tree, name38));

	Vector* name39 = TrieTreeInsertWords2(my_trie_tree, VectorMakeVectorOfChars("abvs x"));
	VectorPrint(name39);
	printf("result 39 %i\n\n", TrieTreeSearch(my_trie_tree, name39));

	Vector* name40 = TrieTreeInsertWords2(my_trie_tree, VectorMakeVectorOfChars("abvs x"));
	VectorPrint(name40);
	printf("result 40 %i\n\n", TrieTreeSearch(my_trie_tree, name40));
	TrieTreePrintTrie(my_trie_tree);
	printf("insert tests pass\n");
	TrieTreePrintTrieRecursive2(my_trie_tree, 0, 1, VectorInitVector());

	// exit(1);
	// erase each item
	// name40 is the longest branch so if it's deleted all subranches will follow
	// TrieTreeDelete(my_trie_tree, name40);
	// it cannot erase a path that doesn't terminate at end of path
	TrieTreeDelete(my_trie_tree, name39);
	printf("result 39 %i\n", TrieTreeSearch(my_trie_tree, name39));

	// |a||b||v||s||x||"||"|
	TrieTreeDelete(my_trie_tree, name38);
	printf("result 38 %i\n", TrieTreeSearch(my_trie_tree, name38));
	TrieTreePrintTrie(my_trie_tree);
	TrieTreeDelete(my_trie_tree, name37);
	printf("result 37 %i\n", TrieTreeSearch(my_trie_tree, name37));

	TrieTreeDelete(my_trie_tree, name36);
	printf("result 36 %i\n", TrieTreeSearch(my_trie_tree, name36));

	TrieTreeDelete(my_trie_tree, name35);
	printf("result 35 %i\n", TrieTreeSearch(my_trie_tree, name35));

	TrieTreeDelete(my_trie_tree, name32);
	printf("result 32 %i\n", TrieTreeSearch(my_trie_tree, name32));

	// abvso
	TrieTreeDelete(my_trie_tree, name31);
	printf("result 31 %i\n", TrieTreeSearch(my_trie_tree, name31));

	TrieTreeDelete(my_trie_tree, name2);
	printf("result 2 %i\n", TrieTreeSearch(my_trie_tree, name32));
	// TrieTreeDelete(my_trie_tree, name40);
	// delete seems to work

	TrieTreePrintTrie(my_trie_tree);
	TrieTreePrintTrieRecursive2(my_trie_tree, 0, 1, VectorInitVector());
	exit(1);

// |a| -> 1
//       |tgrfede|
//          |f| -> 2
//    |i| -> 5
//       |!| -> 6
//       |"| -> 7
//       |#| -> 8
//       |![[)| -> 10
//       |$| -> 12
//       |%| -> 14
//       |&| -> 16
//       |'| -> 18
//       |(| -> 20
//    |j| -> 9
		// |a| -> 1
		// 	|tgrfede|
		// 		|f| -> 2
		// |i| -> 5
		// 	|!| -> 6
		// 	|"| -> 7
		// 	|#| -> 8
		// 	|![[)| -> 10
		// 	|$| -> 11
		// 	|%| -> 12
		// 	|&| -> 13
		// 	|'| -> 14
		// 	|(| -> 15
		// 	|)| -> 16
		// 	|*| -> 17
		// 	|+| -> 18
		// 	|,| -> 19
		// 	|-| -> 20
		// 	|.| -> 21
		// |j| -> 9
		// TrieTreePrintTrieWords(my_trie_tree);

	//}
	// TrieTreePrintTrieWords(my_trie_tree);

	// printf("erase every other\n");
	// for(int i = 0; i < 100; i++)
	// {
	// 	 if(i % 3 == 0)
	// 	 {
	// 		printf("erase\n");
	// 		Vector* my_word = (Vector*) VectorGetItem(collections_of_words, i);
	// 				// VectorAppend(collections_of_words, i4);

	// 		VectorPrintStrings(my_word);


	// 		TrieTreeDeleteWords(my_trie_tree, my_word);
	// 		printf("after delete\n");
	// 		// TrieTreePrintWordTrie(my_trie_tree);
	// 		int a1 = TrieTreeSearch(my_trie_tree, my_word);
	// 		printf("found %i\n", a1);


	// 	 }
	// }
	// TrieTreePrintTrieWords(my_trie_tree);

	// printf("testing user interfeering with the generator\n");

	
}