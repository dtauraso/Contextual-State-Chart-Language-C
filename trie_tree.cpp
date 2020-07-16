#include "trie_tree.h"

Vector* VectorInitVector();
void* VectorGetItem(Vector* container, int i);
void VectorAppend(Vector* container, void* element);
int VectorGetPopulation(Vector* container);
void VectorPrint(Vector* container);
string makeSpaces(int indent_level);

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

int TrieTreeGetVariable(TrieTree* my_trie_tree, string name)
{
	/*
	if the 1 word matches traverse the rest of the trie to get the integer
	assume there is only 1 unique path
	return -1 if there is no unique path to the item that exists(multiple paths and a path that has a dead end are both fails)
	*/
	if(my_trie_tree == NULL || name.length() == 0)
	{
		return -1;
	}
	int prev_node_id = 0;
	TrieNode2* prev_node = (TrieNode2*) VectorGetItem(my_trie_tree->trie_tree, 0);
	//Vector* stack = VectorInitVector();
	int* prev_node_id_ptr = (int*) malloc(sizeof(int));
	*prev_node_id_ptr = 0;
	//VectorAppend(stack, prev_node_id_ptr);
	// search untill no match is possible, or input is empty
	// insert untill input runs out
	for(int i = 0; i < name.size(); i++)
	{


		char letter = name[i];
		// make sure this is valid
		// are there chars_from_edges?
	
		// int edge = prev_node->char_links[letter];


		// if(edge == -1)
		// {
		// 	return -1;
		// }
		
		// else
		// {
		// 	prev_node = (TrieNode2*) VectorGetItem(my_trie_tree->trie_tree, edge);

		// }
		
	}
	// the name is matched
	// while the current node has no state data
	/*
			if # of edges > 1
				return -1
			else if # of edges == 1 and there is state data
				return -1
			else if # of edges == 1 and no state data
				get the next node
		
		should run untill we hit the last node that also has state data
	*/
	while(prev_node->state_id == -1)
	{
		// int edge_count = VectorGetPopulation(prev_node->chars_from_edges);
		// if(edge_count > 1)
		// {
		// 	return -1;
		// }
		// else if(edge_count == 1 && prev_node->state_id > -1)
		// {
		// 	return -1;
		// }
		// else if(edge_count == 1 && prev_node->state_id == -1)
		// {
		// 	// int letter = *((int*) VectorGetItem(prev_node->chars_from_edges, 0));
		// 	// int edge = prev_node->char_links[letter];
		// 	prev_node = (TrieNode2*) VectorGetItem(my_trie_tree->trie_tree, edge);

		// }
	}

	return prev_node->state_id;

}

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
			return id;
		}
	}
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
			// difference between this one and doLinksPointToLeter
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
		int next_node_id = doLinksPointToLeter(my_trie_tree, current, letter);

		if(next_node_id == -1)
		{
			return -1;			
		}
		else
		{

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
	int max_visible_character = 2; 

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
		int next_node_id = doLinksPointToLeter(my_trie_tree, current, letter);

		if(next_node_id == -1)
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
							char top_node_value)
{
	if(char_nodes_matching == NULL || my_trie_tree == NULL)
	{
		return;
	}
	if(VectorGetPopulation(char_nodes_matching) == 0)
	{
		return;
	}

	// assumes all pointers exist
	int prev_node_id_2 = *((int*) VectorGetItem(char_nodes_matching, j));
	//printf("prev node id %i\n", prev_node_id_2);
	TrieNode2* prev_node_2 = (TrieNode2*) VectorGetItem(my_trie_tree->trie_tree, prev_node_id_2);
	//printf("before find loop\n");

		// find the index of the correct letter edge using the char value of the top char node
		char prev_edge_letter = top_node_value;
		int id_of_edge_to_delete = 0;
		// 
		// for(int i = 0; i < VectorGetPopulation(prev_node_2->chars_from_edges); i++)
		// {
		// 	//printf("%i, ", *((int* )  VectorGetItem(prev_node_2->chars_from_edges, i) ));
		// 	char letter_edge = ((char) *((int* )  VectorGetItem(prev_node_2->chars_from_edges, i) ) );
		// 	if(letter_edge == prev_edge_letter)
		// 	{
		// 		//printf("found match %i\n", i);
		// 		id_of_edge_to_delete = i;
		// 	}

		// }
		// VectorDeleteItem(prev_node_2->chars_from_edges, id_of_edge_to_delete);
		// prev_node_2->char_links[prev_edge_letter] = -1;
	// }
	// VectorDeleteItem(prev_node_2->chars_from_edges, id_of_edge_to_delete);
	// prev_node_2->char_links[prev_edge_letter] = -1;


}

int TrieTreeDeleteWords(TrieTree* my_trie_tree, Vector* name /* strings*/)
{
	if(my_trie_tree == NULL || name == NULL)
	{
		return -1;
	}
	/*
	find the char and word paths

	erase the char and word nodes and accompinying stacks

	erase the final char and word links(requires saving data from stacks before poping)

	erase auxiliary stacks

	the root is deleted if there is only 1 char path in trie

	haven't tested this on paths where the root doesn't have the final edge to be deleted
	*/
	// VectorPrintStrings(name);
	// printf("delete\n");
	Vector* char_nodes_matching = VectorInitVector();
	Vector* word_nodes_matching = VectorInitVector();
	int prev_node_id = 0;
	if(name == NULL)
	{
		return -1;
	}
	// assume name is not a sequence of null strings
	TrieNode2* prev_node = (TrieNode2*) VectorGetItem(my_trie_tree->trie_tree, 0);
	TrieTreePush(char_nodes_matching, 0);
	TrieTreePush(word_nodes_matching, 0);

	// getting the stack of char node ids matching the input
	for(int i = 0; i < name->population; i++)
	{
		//TrieNode2* proxy_node = TrieNode2initTrieNode2();

		//proxy_node->word_letters = VectorInitVector();
		//proxy_node->links = VectorInitVector();


		// search through string and make path
		//int number_of_new_letters = 0;
		int size = ((string*) name->values[i])->size();
		
		for(int j = 0; j < size; j++)
		{
			char letter = (*((string*) name->values[i]))[j];

			// int edge = prev_node->char_links[letter];
			// printf("%c ", letter);

			// printf("%i\n", edge);

			// if(edge > -1)
			// {
			// 	TrieTreePush(char_nodes_matching, edge);

			// }
			// else
			// {
			// 	// exit cause there is no match
			// 	printf("can't delete because it doesn't exist\n");
			// 	return -1;
			// }
			// prev_node = (TrieNode2*) VectorGetItem(my_trie_tree->trie_tree, edge);

		}
		
		// if(prev_node->word_counterpart > -1)
		// {
		// 	TrieTreePush(word_nodes_matching, prev_node->word_counterpart);
		// }
	}
	// there will be at least 1 word represented by char_nodes_matching
	// VectorPrint(char_nodes_matching);
	// VectorPrint(word_nodes_matching);

	//exit(1);

	// erase the char path, final edge, and char stack
	// assuming there will always be a node whose edge has to be deleted
	//printf("here\n");
	//Vector* words_stack = VectorInitVector();
	int j = VectorGetPopulation(char_nodes_matching) - 1;
	int top_edge = *((int*) VectorGetItem(char_nodes_matching, j));
	TrieNode2* top_node = (TrieNode2*) VectorGetItem(my_trie_tree->trie_tree, top_edge);
	
	// if(top_node->state_id > -1 && VectorGetPopulation(top_node->chars_from_edges) >= 1)
	// {
	// 	// printf("at internal node\n");
	// 	top_node->state_id = -1;
	// 	return -1;
	// }

	// for deleting the hanging edge
	char poped_node_value;
	poped_node_value = top_node->my_value;
	// delete the node
	// TrieNode2DeleteTrieNode2(top_node);
	VectorSetItemToNull(my_trie_tree->trie_tree, top_edge);
	top_node = NULL;

	VectorPopItem(char_nodes_matching);

	j = VectorGetPopulation(char_nodes_matching) - 1;
	top_edge = *((int*) VectorGetItem(char_nodes_matching, j));
	top_node = (TrieNode2*) VectorGetItem(my_trie_tree->trie_tree, top_edge);
	if(top_node == NULL)
	{
		return -1;
	}

	// if no items from the stack can be deleted
	// the item shares a path with other items
	// top_node->state_id will be > -1 for this case
	// deleting char nodes and poping from char stack
	// while(VectorGetPopulation(top_node->chars_from_edges) <= 1 && top_node->state_id == -1 )
	// {

			
	// 	//VectorPrint(char_nodes_matching);

	// 	// this will always the the last char deleted from char trie tree
	// 	poped_node_value = top_node->my_value;
	// 	//printf("here %x\n", top_node);
	// 	TrieNode2DeleteTrieNode2(top_node);
	// 	//printf("last edge %i, j %i\n", top_edge, j);

	// 	VectorSetItemToNull(my_trie_tree->trie_tree, top_edge);
	// 	top_node = NULL;

	// 	VectorPopItem(char_nodes_matching);
	// 	// can't delete the root node
	// 	// wrong
	// 	if(VectorGetPopulation(char_nodes_matching) == 1)
	// 	{
	// 		// printf("last j %i\n", j);
	// 		break;
	// 	}

	// 	j = VectorGetPopulation(char_nodes_matching) - 1;
	// 	top_edge = *((int*) VectorGetItem(char_nodes_matching, j));
	// 	top_node = (TrieNode2*) VectorGetItem(my_trie_tree->trie_tree, top_edge);
	// }
		//VectorPrint(char_nodes_matching);
	// delete the hanging edge
	if(VectorGetPopulation(char_nodes_matching) > 0)
	{
		j = VectorGetPopulation(char_nodes_matching) - 1;

		//printf("problem is in here %i\n", j);
		TrieTreeEraseEdgeToTopCharNode(char_nodes_matching,
							   j,
							   my_trie_tree,
							   poped_node_value);
	}

	//printf("after lots of deleting\n");
	//VectorPrint(char_nodes_matching);
	//VectorPrint(word_nodes_matching);
	//TrieTreePrintWordTrie(my_trie_tree);
	// printf("words\n");
	// VectorPrint(word_nodes_matching);
	// VectorPrint(char_nodes_matching);

	// int word_counterpart = top_node->word_counterpart;
	// printf("word counterpart %i\n", word_counterpart);
	// check each word as it is erase and find out if it's = the id on the stack
	// the char node on the top of the char stack always links to a word node
	// yes, because 1 single word will always be deleted if the state in question ends in a leaf node
	// there is no concern about if the counterpart char node was one of the deleted items
	// what is the word the top of the finished char stack?

	//printf("delete word nodes\n");
	// there will always be at least 1 word matching the input

	int top_word_id = VectorGetPopulation(word_nodes_matching) - 1;

	int deleted_word_edge = *((int*) VectorGetItem(word_nodes_matching, top_word_id));
	TrieNode2* top_word = (TrieNode2*) VectorGetItem(my_trie_tree->word_tree, deleted_word_edge);
	if(top_word == NULL)
	{
		return -1;
	}
	// loop is still wrong
	// printf("start\n");
	int prev_deleted_word_edge = 0;
	// while(VectorGetPopulation(word_nodes_matching) > 1 && deleted_word_edge != word_counterpart)
	// {
	// 	// seems to go 1 iteration too far and the target value is rest with the lin before it
	// 	// VectorPrint(word_nodes_matching);
	// 	// printf("deleted word edge %i\n", deleted_word_edge);
	// //TrieTreePrintWordTrie(my_trie_tree);
	
	// 	TrieNode2DeleteTrieNode2(top_word);
	// 	//			printf("here\n");
	// 	//printf("deleted_word_edge %i\n", deleted_word_edge);
	// 	// node 5 is erased and node 2's links are erased
	// 	VectorSetItemToNull(my_trie_tree->word_tree, deleted_word_edge);
	// 	top_word = NULL;
	// 	//TrieTreePrintWordTrie(my_trie_tree);
	// 	VectorPopItem(word_nodes_matching);
	// 	if(VectorGetPopulation(word_nodes_matching) == 1)
	// 	{
	// 		break;
	// 	}
	// 	top_word_id = VectorGetPopulation(word_nodes_matching) - 1;
	// 	prev_deleted_word_edge = deleted_word_edge;
	// 	deleted_word_edge = *((int*) VectorGetItem(word_nodes_matching, top_word_id));
	// 	top_word = (TrieNode2*) VectorGetItem(my_trie_tree->word_tree, deleted_word_edge);

	// }
		

	/*
		moved to the next item
		target value was reset
		loop ended with unwanted value
	*/
	//TrieTreePrintWordTrie(my_trie_tree);

	// printf("after word stack deleting %i\n", prev_deleted_word_edge);
	// VectorPrint(word_nodes_matching);
	// VectorPrint(char_nodes_matching);

	// delete word nodes and word stack
	// delete final word edge
	//printf("%i\n", top_word_id);
	// printf("got here\n");

	int edge = *((int*) VectorGetItem(word_nodes_matching, VectorGetPopulation(word_nodes_matching) - 1));
	TrieNode2* word_node = (TrieNode2*) VectorGetItem(my_trie_tree->word_tree, edge);
	if(word_node == NULL)
	{
		return -1;
	}
	int location_of_word_edge = 0;
	// printf("%i\n", VectorGetPopulation(word_node->links));
	for(int i = 0; i < VectorGetPopulation(word_node->links); i++)
	{
		// printf("%i\n", i);
		int word_node_edge = *((int*) VectorGetItem(word_node->links, i));
		if(word_node_edge == prev_deleted_word_edge)
		{
			location_of_word_edge = i;
			break;
		}
	}
	// printf("got here 2\n");
	//printf("location of word edge %i\n", location_of_word_edge);
	//VectorPrint(word_node->links);
	VectorDeleteItem(word_node->links, location_of_word_edge);
	// VectorPrint(word_node->links);
	// printf("population %i\n", VectorGetPopulation(word_node->links));

	// printf("%i\n", deleted_word_edge);
	// VectorSetItemToNull(word_node->links, deleted_word_edge);
	//top_word = NULL;

	//printf("when delete is over\n");
	//VectorPrint(char_nodes_matching);
	//VectorPrint(word_nodes_matching);
	//printf()
	//TrieTreePrintTrie(my_trie_tree);
	//TrieTreePrintWordTrie(my_trie_tree);

	VectorDeleteAllItems(char_nodes_matching);
	VectorDeleteAllItems(word_nodes_matching);
	// VectorDeleteAllItems should have already set these to NULL
	char_nodes_matching = NULL;
	word_nodes_matching = NULL;
	return -1;

}

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
	// printf("here\n");
}

void TrieTreePrintWordTrie(TrieTree* my_trie_tree)
{
	if(my_trie_tree == NULL)
	{
		return;
	}
	printf("printing ordered dict word tree\n");
	// loop through all elements
		// loop thorugh all attributes
	for(int i = 0; i < VectorGetPopulation(my_trie_tree->word_tree); i++)
	{

		TrieNode2* node = (TrieNode2*) VectorGetItem(my_trie_tree->word_tree, i);
		//("node %x\n", node);
		if(node == NULL)
		{
			printf("%i empty\n\n", i);
		}
		else
		{
			//printf("printing array\n");

			//printf("%i |%c| %i %i\n", i, node->my_value, node->start_of_word, node->state_id);
			printf("%i |", i);
			//printf("%x %i\n", node->word_letters, VectorGetPopulation(node->word_letters));
			//printf("here\n");
			//VectorPrint(node->word_letters);
			//printf("done\n");
			// if(node->word_letters != NULL)
			// {
			// 	for(int j = 0; j < VectorGetPopulation(node->word_letters); j++)
			// 	{
			// 		int k = *((int*) VectorGetItem(node->word_letters, j));
			// 		// printf("%i", k);
			// 		TrieNode2* char_node = (TrieNode2*) VectorGetItem(my_trie_tree->trie_tree, k);
			// 		//printf("char_node %x\n", char_node);

			// 		//printf("|%i|", k);
			// 		if(char_node != NULL)
			// 		{
			// 			printf("%c", char_node->my_value);

			// 		}
			// 	}
			// }
			
			printf("|\nlinks\n");
			if(node->links == NULL)
			{
				printf("empty\n\n");
			}
			else
			{

				// does insert recreate root's links?
				printf("number of links %i\n", VectorGetPopulation(node->links));
				for(int l = 0; l < VectorGetPopulation(node->links); l++)
				{
					// printf("%i\n", i);
					int k = *((int*) VectorGetItem(node->links, l));
					printf("|%i|", k);

				}
				printf("\n\n");
			}

			

		}
		

	}
}


/*

dfs using stack

node id stack
ith edge stack
indent level
loop while stack is not empty

	if letter is start of word
		go down the stack and collect the string from top to previous start of word
		how to line up the indents with the strings
		increment the indent level each time a word is collected

	else if letter is not start of word
		TrieTreePush to stack
	else if there is no letter found(not able to find a successive letter)
		pop from top
		choose the next edge from penultimate to TrieTreePush or pop again if can't
		indent level -- if the item poped is the start of a word

*/
/*
slider stack traversal
slide forward
	pushEnd untill hit end of word
	popFront untill ht end of word

	slide backward
		pushFront untill hit the one before end of word
		popEnd
		if node has anothe edge
			pushEnd untill we hit end of word
			slide forward
		repeat

*/


void TrieTreePrintTrieWords(TrieTree* my_trie_tree)
{
	if(my_trie_tree == NULL)
	{
		return;
	}
	// printing the trie tree using the word tree
	// node_id_stack
	Vector* node_id_stack = VectorInitVector();
	// ith_edge_stack
	Vector* ith_edge_stack = VectorInitVector();
	// indent_level
	int indent_level = 0;
	// put root on stack
	// root shouldn't be printed out but it's not causing problems
	int start_ith_edge = 0;
	int* start_ith_edge_ptr = (int*) malloc(sizeof(int));
	*start_ith_edge_ptr = start_ith_edge;
	VectorAppend(ith_edge_stack, start_ith_edge_ptr);


	int start_node_id = 0;
	int* start_node_id_ptr = (int*) malloc(sizeof(int));
	*start_node_id_ptr = start_node_id;
	VectorAppend(node_id_stack, start_node_id_ptr);

	// get next node after root
	int top_node_id = *((int*) VectorGetItem(node_id_stack, 0));
	TrieNode2* top_node = (TrieNode2*) VectorGetItem(my_trie_tree->word_tree, top_node_id);
	if(top_node == NULL)
	{
		return;
	}
	if(VectorGetPopulation(top_node->links) == 0)
	{
		printf("empty graph\n");
		return;
	}
	int top_ith_edge = *((int*) VectorGetItem(ith_edge_stack, 0));
	//int next_letter = *((int*) VectorGetItem(top_node->chars_from_edges, top_ith_edge) );
	//VectorPrint(top_node->links);
	int next_edge = *((int*) VectorGetItem(top_node->links, top_ith_edge) );//top_node->char_links[next_letter];

	//printf("next edge %i\n", next_edge);
	int loop_count = 0;
	TrieNode2* next_letter_node;// = (TrieNode2*) VectorGetItem(my_trie_tree->trie_tree, next_edge);

	int* first_node_id_ptr = (int*) malloc(sizeof(int));
	*first_node_id_ptr = next_edge;
	VectorAppend(node_id_stack, first_node_id_ptr);


	int* first_ith_edge_ptr = (int*) malloc(sizeof(int));
	*first_ith_edge_ptr = 0;
	VectorAppend(ith_edge_stack, first_ith_edge_ptr);
	indent_level += 3;
	//indent_level += 3;
	// TrieTreePush first node to stack
	// update indent_leve
	//VectorPrint(ith_edge_stack);
	//VectorPrint(node_id_stack);
	// status of stacks
	// 0, next_edge(first node)
	// 0, 0
	//printf("here\n");
	// looking for expecting a link and getting NULL

	// first letter is the first letter of the first sequence
	while(/*loop_count < 6 &&  */VectorGetPopulation(node_id_stack) > 0)
	{
		//printf("node id %i\n", next_edge);

		// use the node id for tracking, not the node pointer

		// first round this is the first child from root
		next_letter_node = (TrieNode2*) VectorGetItem(my_trie_tree->word_tree, next_edge);
		if(next_letter_node == NULL)
		{
			return;
		}
		// process 1 node per round
		//printf("loop %i\n", loop_count);
		//printf("here\n");
 		//printf("node id %i\n", top_node_id);
		//printf("here 2\n");
		//printf("node %i\n\n", next_letter_node);
		
		//VectorPrint(ith_edge_stack);
		//VectorPrint(node_id_stack);

		// VectorPrint word
		printf("%s|", makeSpaces(indent_level).c_str());
		// for(int j = 0; j < VectorGetPopulation(next_letter_node->word_letters); j++)
		// {
		// 	int k = *((int*) VectorGetItem(next_letter_node->word_letters, j));
		// 	//printf("|%i|", k);

		// 	TrieNode2* char_node = (TrieNode2*) VectorGetItem(my_trie_tree->trie_tree, k);

		// 	printf("%c", char_node->my_value);
		// 	if(j == VectorGetPopulation(next_letter_node->word_letters) - 1)
		// 	{
		// 		if(char_node->state_id > -1)
		// 		{
		// 			printf("| -> %i", char_node->state_id);
		// 		}
		// 		else
		// 		{
		// 			printf("|");
		// 		}

		// 	}

		// }

		printf("\n");
		//printf("got here\n");
		// have to check before getting the next edge cause the last possible node in the current path is on the stack(because it was just printed)
		//printf("next node id %i\n", next_edge);
		if(VectorGetPopulation(next_letter_node->links) > 0)
		{
			// find the next edge and add it here
			TrieTreePush(node_id_stack, TrieTreeGetNextNode(my_trie_tree, node_id_stack, ith_edge_stack));
			TrieTreePush(ith_edge_stack, 0);
			//printf("after TrieTreePush\n");
			//VectorPrint(ith_edge_stack);
			//VectorPrint(node_id_stack);
			indent_level += 3;
			next_edge = *((int*) VectorGetItem(node_id_stack, VectorGetPopulation(node_id_stack) - 1));

		}
		else
		{
			int top_node_id_2 = *((int*) VectorGetItem(node_id_stack,
													 VectorGetPopulation(node_id_stack) - 1));
			TrieNode2* top_node_2 = (TrieNode2*) VectorGetItem(my_trie_tree->word_tree, top_node_id_2);
			if(top_node_2 == NULL)
			{
				return;
			}
			// exit when stack is empty or there is a new node to visit
			while(VectorGetPopulation(node_id_stack) > 0 /* may simply be here to keep something true */)
			{
				// pop from both stacks
				//printf("before pop\n");
				VectorPopItem(ith_edge_stack);
				VectorPopItem(node_id_stack);
				//printf("after pop\n");
				//VectorPrint(ith_edge_stack);
				//VectorPrint(node_id_stack);
				indent_level -= 3;
				if(VectorGetPopulation(node_id_stack) == 0)
				{
					break;
				}
				// decriment indent_level
				top_node_id_2 = *((int*) VectorGetItem(node_id_stack,
													 VectorGetPopulation(node_id_stack) - 1));

				top_node_2 = (TrieNode2*) VectorGetItem(my_trie_tree->word_tree, top_node_id_2);
				if(top_node_2 == NULL)
				{
					return;
				}
				top_ith_edge = *((int*) VectorGetItem(ith_edge_stack, VectorGetPopulation(ith_edge_stack) - 1));

				//printf("top node id %i, population %i, top edge %i\n", top_node_id_2, VectorGetPopulation(top_node_2->links), top_ith_edge);
				// have to use the edge for the below comparison too
				// if edge at top of stack can be incremented(edge + 1 < node's links length)
				if(top_ith_edge + 1 < VectorGetPopulation(top_node_2->links))
				{

					//printf("need to TrieTreePush\n");
					VectorIncrementTopInt(ith_edge_stack);

					// TrieTreePush new node(will be next_letter_node) and 0 to stacks
					// increment indent_level

					next_edge = TrieTreeGetNextNode(my_trie_tree, node_id_stack, ith_edge_stack);

					TrieTreePush(node_id_stack, next_edge);
					TrieTreePush(ith_edge_stack, 0);
					indent_level += 3;

					break;

				}
			}
			//printf("done with poping\n");
		}
		
		//VectorPrint(ith_edge_stack);
		//VectorPrint(node_id_stack);
		
		loop_count++;


	}
	
}

void TrieTreePrintTrieRecursive(TrieTree* my_trie_tree, int root, string indents)
{
	if(my_trie_tree == NULL)
	{
		return;
	}
	if(VectorGetPopulation(my_trie_tree->trie_tree) == 0)
	{
		return;
	}
	TrieNode2* node = (TrieNode2*) VectorGetItem(my_trie_tree->trie_tree, root);

	// string my_string = *((string*) node->value);
	if(node->state_id > -1)
	{
		// printf("%s %s -> %i\n\n", indents.c_str(), my_string.c_str(), node->state_id);

	}
	else
	{
		// printf("%s %s\n\n", indents.c_str(), my_string.c_str());

	}
	for(int j = 0; j < VectorGetPopulation(node->links); j++)
	{
		TrieTreePrintTrieRecursive(my_trie_tree, *((int*) VectorGetItem(node->links, j)), indents + "  ");
	}

}
void TrieTreePrintTrieRecursive2(TrieTree* my_trie_tree, int current, int number_of_indents, Void* word_found)
{
	/*
	if current doesn't exist
		return
	else
		add curent letter to word
		if we are at end of word
			print out the word_found
			erase word_found
		if current has many edges
			make n copies of word_found
			pass each one to the recursive call
	*/
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
	exit(1);
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

	// delete seems to work

	// TrieTreePrintTrie(my_trie_tree);
	exit(1);

	VectorPrintStrings(VectorAddStringToVector2("abvf", "tgrfede"));
	int a = TrieTreeSearch(my_trie_tree, VectorAddStringToVector2("abvf", "tgrfede"));
	printf("found state id %i\n", a);


	Vector* name1 = TrieTreeInsertWords2(my_trie_tree, VectorAddStringToVector1("abvf"));


	TrieTreeDeleteWords(my_trie_tree, VectorAddStringToVector2("abvf", "tgrfede"));

	Vector* name3 = TrieTreeInsertWords2(
						my_trie_tree,
						VectorAddStringToVectorGeneral(
							(string [])
							{
								"abvf", "tgrfede", "f"
							}, 3
						));



	Vector* name4 = TrieTreeInsertWords2(
						my_trie_tree,
						VectorAddStringToVectorGeneral(
							(string [])
							{
								"abvf", "tgrfede", "hijk"
							}, 3
						));
	
	Vector* name5 = TrieTreeInsertWords2(
						my_trie_tree,
						VectorAddStringToVectorGeneral(
							(string [])
							{
								"abvf", "tgrfede", "hijk", "i"
							}, 4
						));
	TrieTreeDeleteWords(
		my_trie_tree,
		VectorAddStringToVectorGeneral(
			(string [])
			{
				"abvf", "tgrfede", "hijk"
			}, 3
		)

	);

	TrieTreeDeleteWords(
		my_trie_tree,
		VectorAddStringToVectorGeneral(
			(string [])
			{
				"abvf", "tgrfede", "hijk", "i"
			}, 4
		)
						
	);

	Vector* name6 = TrieTreeInsertWords2(my_trie_tree, VectorAddStringToVector1("input_string"));
	Vector* name7 = TrieTreeInsertWords2(my_trie_tree, VectorAddStringToVector1("i"));

	TrieTreePrintTrie(my_trie_tree);
	// TrieTreePrintWordTrie(my_trie_tree);
	TrieTreePrintTrieWords(my_trie_tree);
	printf("passes this far\n");
	// exit(1);
	// //TrieTreeSearch
	
	// Vector* name6 = TrieTreeInsertWords(my_trie_tree, VectorAddStringToVector3("a", "e", "g"));
	
	// Vector* name7 = TrieTreeInsertWords(my_trie_tree, VectorAddStringToVector1("b"));
	
	// Vector* name8 = TrieTreeInsertWords(my_trie_tree, VectorAddStringToVector1("c"));
	
	// Vector* name9 = TrieTreeInsertWords(my_trie_tree, VectorAddStringToVector2("c", "d"));
	// TrieTreeDeleteWords(my_trie_tree, VectorAddStringToVector1("c"));



	// TrieTreePrintTrie(my_trie_tree);
	// TrieTreePrintTrieWords(my_trie_tree);
	
	printf("testing the generator case and the user interfeering with the generator case\n");
	Vector* x =  TrieTreeInsertWords2(my_trie_tree, VectorAddStringToVector1("i"));
	// printf("got here\n");
	Vector* i = TrieTreeInsertWords2(my_trie_tree, VectorAddStringToVector1("iii"));
	// TrieTreePrintTrie(my_trie_tree);
	// TrieTreePrintWordTrie(my_trie_tree);
	// exit(1);

	// TrieTreePrintTrieWords(my_trie_tree);

	Vector* i1 = TrieTreeInsertWords2(my_trie_tree, VectorAddStringToVector1("iii"));
	// TrieTreePrintTrie(my_trie_tree);
	VectorPrintStrings(i1);
	printf("\n");
	TrieTreePrintTrieWords(my_trie_tree);

	// exit(1);
	// printf("\n");

	// TrieTreePrintTrieWords(my_trie_tree);
	Vector* i2 = TrieTreeInsertWords2(my_trie_tree, VectorAddStringToVector1("iii"));
	// // TrieTreePrintTrie(my_trie_tree);
	VectorPrintStrings(i2);
	// printf("\n");

	Vector* i3 = TrieTreeInsertWords2(my_trie_tree, VectorAddStringToVector1("iii"));
	// // TrieTreePrintTrie(my_trie_tree);
	VectorPrintStrings(i3);
	// printf("\n");
	// TrieTreePrintTrieWords(my_trie_tree);

	// according to the logs, it probably went out of bounds
	// fix bounds problem
	// the max number of visible chars is 96
	Vector* i4 = TrieTreeInsertWords2(my_trie_tree, VectorAddStringToVector1("j"));
	VectorPrintStrings(i4);
	// wondering why this would work as it could throw off the letter counter
	i4 = TrieTreeInsertWords2(my_trie_tree, VectorAddStringToVector2("iii", "![[)"));
	VectorPrintStrings(i4);
	i4 = TrieTreeInsertWords2(my_trie_tree, VectorAddStringToVector2("iii", "![[)8[)"));
	VectorPrintStrings(i4);
	TrieTreePrintTrieWords(my_trie_tree);

	// the ! char node is also connected to the other word starting with !
	// so the last official edge from i is # not !
	// sort of wierd from the word perspective(It's displayed as a separate path), but prevents the letter incrementer from accidentally
	// going to an edge already used
	// works up to 10
	Vector* collections_of_words = VectorInitVector();
	for(int i = 0; i < 100; i++)
	{

		i4 = TrieTreeInsertWords2(my_trie_tree, VectorAddStringToVector1("iii"));
		VectorAppend(collections_of_words, i4);
		// TrieTreePrintTrie(my_trie_tree);
		// TrieTreePrintWordTrie(my_trie_tree);
		// TrieTreePrintTrieWords(my_trie_tree);
		// printf("\n");

		// VectorPrintStrings(i4);

		
		// VectorPrintStrings(i4);
		int a1 = TrieTreeSearch(my_trie_tree, i4);
		printf("found %i\n", a1);
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

	}
	TrieTreePrintTrieWords(my_trie_tree);

	printf("erase every other\n");
	for(int i = 0; i < 100; i++)
	{
		 if(i % 3 == 0)
		 {
			printf("erase\n");
			Vector* my_word = (Vector*) VectorGetItem(collections_of_words, i);
					// VectorAppend(collections_of_words, i4);

			VectorPrintStrings(my_word);


			TrieTreeDeleteWords(my_trie_tree, my_word);
			printf("after delete\n");
			// TrieTreePrintWordTrie(my_trie_tree);
			int a1 = TrieTreeSearch(my_trie_tree, my_word);
			printf("found %i\n", a1);


		 }
	}
	TrieTreePrintTrieWords(my_trie_tree);

	printf("testing user interfeering with the generator\n");

	
}