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

	my_node->value = NULL;
	my_node->links = VectorInitVector();

	memset(my_node->char_links, -1, sizeof(int) * 256);
	my_node->chars_from_edges = VectorInitVector();
	my_node->value_type = 0;
	my_node->state_id = -1;
	my_node->start_of_word = 0;
	my_node->word_counterpart = -1;
	// set the word_letters to null
	// that way only the word nodes have a non-null copy
	my_node->word_letters = NULL;
	return my_node;

}
bool TrieNode2DeleteTrieNode2(TrieNode2* node)
{
	if(node != NULL)
	{
		free(node->value);
		if(node->links != NULL)
		{
				VectorDeleteAllItems(node->links);
				node->links = NULL;

		}
		if(node->chars_from_edges != NULL)
		{
				VectorDeleteAllItems(node->chars_from_edges);
				node->chars_from_edges = NULL;

		}
		//printf("word letters %x\n", *((int*) node->word_letters) );
		if(node->word_letters != NULL)
		{
			//printf("about to erase\n");
			// needs to be initialized for all TrieNode Objects(fix insert)
			VectorDeleteAllItems(node->word_letters);
			node->word_letters = NULL;
			//printf("erased\n");
		}
		free(node);
		return true;
		/*
		if(VectorDeleteAllItems(node->links))
		{
			//printf("erased links\n");
			free(node);
			//node = NULL;
			return true;
		}

		return false;
		*/
	}
	return false;

}
void* TrieNode2GetValue(TrieNode2* node)
{
	if(node != NULL)
	{
		return node->value;

	}
	return NULL;
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
	// root is not the last word
	char root = 'r';
	TrieTreeInsertString(my_trie_tree, root, -1);

	TrieNode2* node = TrieNode2initTrieNode2();

	node->word_letters = VectorInitVector();
	node->links = VectorInitVector();
	//string* node_string = (string*) malloc(sizeof(string));
	//node_string = element;
	//node->value = element;
	//node->my_value = 'r';
	//node->value_type = 1;
	//node->state_id = state_id;

	VectorAppend(my_trie_tree->word_tree, node);


	my_trie_tree->root = 0;
	my_trie_tree->max_state_id = -1;

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
	int* new_item_ptr = (int*) malloc(sizeof(int));
	*new_item_ptr = new_item;
	VectorAppend(container, new_item_ptr);
}
int TrieTreeGetNextNode(TrieTree* my_trie_tree, Vector* node_id_stack, Vector* ith_edge_stack)
{
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
	
		int edge = prev_node->char_links[letter];


		if(edge == -1)
		{
			return -1;
		}
		
		else
		{
			prev_node = (TrieNode2*) VectorGetItem(my_trie_tree->trie_tree, edge);

		}
		
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
		int edge_count = VectorGetPopulation(prev_node->chars_from_edges);
		if(edge_count > 1)
		{
			return -1;
		}
		else if(edge_count == 1 && prev_node->state_id > -1)
		{
			return -1;
		}
		else if(edge_count == 1 && prev_node->state_id == -1)
		{
			int letter = *((int*) VectorGetItem(prev_node->chars_from_edges, 0));
			int edge = prev_node->char_links[letter];
			prev_node = (TrieNode2*) VectorGetItem(my_trie_tree->trie_tree, edge);

		}
	}

	return prev_node->state_id;

}

int TrieTreeSearch(TrieTree* my_trie_tree, Vector* name /* strings*/)
{
	if(my_trie_tree == NULL || name == NULL)
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
	for(int i = 0; i < name->population; i++)
	{

		int size = ((string*) name->values[i])->size();
		for(int j = 0; j < size; j++)
		{

			char letter = (*((string*) name->values[i]))[j];

			int edge = prev_node->char_links[letter];

			int* item_found_location_ptr = (int*) malloc(sizeof(int));
			*item_found_location_ptr = edge;

			if(edge == -1)
			{
				return -1;
			}
			
			else
			{
				prev_node = (TrieNode2*) VectorGetItem(my_trie_tree->trie_tree, edge);

			}
		}		
		
	}
	return prev_node->state_id;
}
void TrieTreeInsertString2(TrieTree* my_trie_tree,
							char element,
							int state_id,
							bool is_end_of_string)
{
	TrieNode2* node = TrieNode2initTrieNode2();

	//string* node_string = (string*) malloc(sizeof(string));
	//node_string = element;
	//node->value = element;
	node->my_value = element;
	node->value_type = 1;
	node->end_of_word = false;
	if(is_end_of_string)
	{
		node->end_of_word = true;
	}
	node->state_id = state_id;
	VectorAppend(my_trie_tree->trie_tree, node);

}


void TrieTreeInsertString(TrieTree* my_trie_tree, char element, int state_id)
{
	TrieNode2* node = TrieNode2initTrieNode2();

	//string* node_string = (string*) malloc(sizeof(string));
	//node_string = element;
	//node->value = element;
	node->my_value = element;
	node->value_type = 1;
	node->parent = -1;
	node->state_id = state_id;
	VectorAppend(my_trie_tree->trie_tree, node);

}

int TrieNode2GetLastNode(TrieTree* my_trie_tree, int prev_node_id)
{
	// getting the last letter edge so in case user adds edges edges to tree this generator made, the generator will not
	// create nodes that already exist
	TrieNode2* prev_node = (TrieNode2*) VectorGetItem(my_trie_tree->trie_tree, prev_node_id);
	// int edge_index = VectorGetPopulation(prev_node->chars_from_edges) - 1;
	int size = VectorGetPopulation(prev_node->chars_from_edges);
	int edge_index = 0;
	if(size > 0)
	{
		edge_index = size - 1;

	}
	// this is the "letter"
	int letter = *((int*) VectorGetItem(prev_node->chars_from_edges, edge_index));
	int next_node = prev_node->char_links[letter];
	return next_node;
}

int TrieNode2GetLastEdge(TrieTree* my_trie_tree, int prev_node_id)
{
	// getting the last letter edge so in case user adds edges edges to tree this generator made, the generator will not
	// create nodes that already exist
	// printf("entered TrieNode2GetLastEdge\n");
	TrieNode2* prev_node = (TrieNode2*) VectorGetItem(my_trie_tree->trie_tree, prev_node_id);
	// printf("got this far\n");
	int size = VectorGetPopulation(prev_node->chars_from_edges);
	int edge_index = 0;
	if(size > 0)
	{
		edge_index = size - 1;
		// printf("got this far 2\n");
		// printf("edge index %i \n", edge_index);
		// this is the "letter"
		int letter = *((int*) VectorGetItem(prev_node->chars_from_edges, edge_index));
		// printf("letter %i\n", letter);
		return letter;

	}
	return -1;
	// if size == 0 there are no edges to collect
}

int TrieNode2GetWordCounterpart(TrieTree* my_trie_tree, int prev_node_id)
{
	TrieNode2* prev_node = (TrieNode2*) VectorGetItem(my_trie_tree->trie_tree, prev_node_id);
	if(prev_node->word_counterpart > -1)
	{
		return prev_node->word_counterpart;
	}
	return -1;
}

TrieNode2* TrieNode2GetWord(TrieTree* my_trie_tree, int prev_node_id)
{
	TrieNode2* prev_node = (TrieNode2*) VectorGetItem(my_trie_tree->trie_tree, prev_node_id);
	if(prev_node->word_counterpart > -1)
	{

		return (TrieNode2*) VectorGetItem(my_trie_tree->word_tree, prev_node->word_counterpart);
	}
	return NULL;
}
string* TrieNode2MakeStringFromWord(TrieTree* my_trie_tree, int prev_node_id)
{
	string word;
	// insert 
	// printf("inside TrieNode2MakeStringFromWord\n");
	TrieNode2* prev_proxy = TrieNode2GetWord(my_trie_tree, prev_node_id);
	// printf("prev node id %i\n", prev_node_id);
	// for(int j = 0; j < VectorGetPopulation(prev_proxy->word_letters); j++)
	// {
	// 	printf("%i\n", j);
	// 	int k = *((int*) VectorGetItem(prev_proxy->word_letters, j));
	// 	// TrieTreePrintTrie(my_trie_tree);
	// 	TrieTreePrintWordTrie(my_trie_tree);

	// 	printf("k %i\n", k);

	// 	TrieNode2* char_node = (TrieNode2*) VectorGetItem(my_trie_tree->trie_tree, 0);
	// 	printf("got here\n");
	// 	if(char_node != NULL)
	// 	{
	// 		printf("%i", char_node->my_value);
	// 		word += char_node->my_value;

	// 	}

	// }
	if(prev_proxy != NULL)
	{
		if(prev_proxy->word_letters != NULL)
		{
			// printf("got here %i\n", VectorGetPopulation(prev_proxy->word_letters));

			for(int j = 0; j < VectorGetPopulation(prev_proxy->word_letters); j++)
			{
				// printf("%i\n", j);
				// printf("population %i\n", prev_proxy->word_letters->population);
				int k = *((int*) VectorGetItem(prev_proxy->word_letters, j));
				// printf("%i\n", k);
				TrieNode2* char_node = (TrieNode2*) VectorGetItem(my_trie_tree->trie_tree, k);
				//printf("char_node %x\n", char_node);

				//printf("|%i|", k);
				if(char_node != NULL)
				{
					// printf("%c\n", char_node->my_value);
					word += char_node->my_value;

				}
			}
		}
	}
	
	string* new_context_word = (string*) malloc(sizeof(string));
	*new_context_word = word;
	return new_context_word;
}
bool TrieTreeEdgeIndicatesToMakeChild(int letter_edge)
{
		// case 1 where the same item is added a second time
		// there will be no edges so we make a child

	if(letter_edge == -1)   // only true when VectorGetPopulation(path) == 1 is true
	{
		// printf("make child\n");
		return true;

	}
	// if before last possible visible number
	else if(letter_edge < 126 && letter_edge >= 0) 	// only true when VectorGetPopulation(path) > 1 is trie
	{
		// correct
		// printf("make sibling\n");
		return false;
	}
	// ~ case
	// this could be true if the first extra letter added was ~
	// generally true when VectorGetPopulation(path) > 1 is trie
	else  // if at last possible visible number
	{
		// untested(very likely to be correct too)
		// printf("make child\n");
		return true;

	}

}
int TrieTreeFindLastPrevNode(TrieTree* my_trie_tree, Vector* path)
{
	int parent_location;
	// first time inserting
	if(VectorGetPopulation(path) == 1)
	{
		int parent_index = 0;
		parent_location = *((int*) VectorGetItem(path, parent_index));
		return parent_location;

	}
	else if(VectorGetPopulation(path) > 1)
	{
		// printf("have a longer path char\n");
		/* 
			get penultimate node and find out if it's edge exceeds '~' 
		 */

		int penultimate_node_index = VectorGetPopulation(path) - 2;
		int penultimate_node_id =  *((int*) VectorGetItem(path, penultimate_node_index));
		int letter = TrieNode2GetLastEdge(my_trie_tree, penultimate_node_id);
		// printf("%c\n", letter);
		if(letter >= 0 && letter < 126)  // there is room to add a sibling
		{

			// return penultimate_node_id;
			TrieNode2* char_node = (TrieNode2*) VectorGetItem(my_trie_tree->trie_tree, penultimate_node_id);
			// starting at the penultimate node
			// working so far
			while(char_node->word_counterpart == -1)
			{
				penultimate_node_index--;
				penultimate_node_id =  *((int*) VectorGetItem(path, penultimate_node_index));
				char_node = (TrieNode2*) VectorGetItem(my_trie_tree->trie_tree, penultimate_node_id);
			}
			// printf("node stopped at %i\n", penultimate_node_id);
			return penultimate_node_id;
		}
		else if(letter == 126)
		{
			// printf("have to reset\n");
			int final_node_location = VectorGetPopulation(path) - 1;
			int final_node_id  = *(int*) VectorGetItem(path, final_node_location);
			return final_node_id;
		}
		
		
		// TrieNode2* penultimate_char_node = (TrieNode2*) VectorGetItem(my_trie_tree->trie_tree, penultimate_node_id);
		// printf("%c\n", penultimate_char_node->my_value);

	}
	
	return 0;
	
	
}

int TrieTreeFindLastWordNode(TrieTree* my_trie_tree, Vector* path)
{
	int parent_location;

	if(VectorGetPopulation(path) == 1)
	{
		int parent_index = 0;
		parent_location = *((int*) VectorGetItem(path, parent_index));
		TrieNode2* node = (TrieNode2*) VectorGetItem(my_trie_tree->trie_tree, parent_location);
		int word_node_id = node->word_counterpart;
		return word_node_id;
	}
	else if(VectorGetPopulation(path) > 1)
	{
		// printf("have a longer path word\n");
		int penultimate_node_index = VectorGetPopulation(path) - 2;
		int penultimate_node_id =  *((int*) VectorGetItem(path, penultimate_node_index));
		int letter = TrieNode2GetLastEdge(my_trie_tree, penultimate_node_id);
		// case 1 (sibling)
			// the penultimate char node has < '~' as an edge
			// look in range [penultimate, 0]
			// locate the penultimate

		if(letter >= 0 && letter < 126)  // there is room to add a sibling
		{
			// printf("find the penultimate char node for the word node\n");
			// printf("the edge found is %c\n", letter);
			// loop backwards to 
			TrieNode2* char_node = (TrieNode2*) VectorGetItem(my_trie_tree->trie_tree, penultimate_node_id);
			// starting at the penultimate node
			// working so far
			while(char_node->word_counterpart == -1)
			{
				penultimate_node_index--;
				penultimate_node_id =  *((int*) VectorGetItem(path, penultimate_node_index));
				char_node = (TrieNode2*) VectorGetItem(my_trie_tree->trie_tree, penultimate_node_id);
			}
			// printf("node stopped at %i\n", penultimate_node_id);
			// worked earlier cause the counterpart id == the char node id
			return char_node->word_counterpart;//penultimate_node_id;
		}
		else if(letter == 126)
		{
			penultimate_node_index = VectorGetPopulation(path) - 1;
			penultimate_node_id =  *((int*) VectorGetItem(path, penultimate_node_index));
			TrieNode2* char_node = (TrieNode2*) VectorGetItem(my_trie_tree->trie_tree, penultimate_node_id);
			return char_node->word_counterpart;
		}
		

		// case 2 (child)
			// the penultimate char node has '~' as an edge
			// the last char node is the char node we want
		// int parent_index = VectorGetPopulation(path) - 1;
		// parent_location = *((int*) VectorGetItem(path, parent_index));
		// TrieNode2* node = (TrieNode2*) VectorGetItem(my_trie_tree->trie_tree, parent_location);
		// i [last - 1, 0]
		// case 2
		// while(node->word_counterpart == -1)
		// {

		// }
	}


	return 0;

}
// TrieNode2* TrieNodeGetTrieNode()
void TrieTreeAddSoubtleCase(TrieTree* my_trie_tree, int prev_node_id, int prev_proxy_id, Vector* name /* strings*/)
{
	// case where no prior item has been generated works
	// case where any sibling or child nod must be created around prior items doesn't work
	/*
	i
	i, 0 done
	i, 1 testing(got i, 3 instead)
	i, 0, 1

	how do we know 1 item was already generated
	*/
	// TrieNode2* prev_node = (TrieNode2*) VectorGetItem(my_trie_tree->trie_tree, prev_node_id);
	// int edge_index = VectorGetPopulation(prev_node->chars_from_edges) - 1;
	// int edge_location = *((int*) VectorGetItem(prev_node->chars_from_edges, edge_index));
	// int edge_value = *((int*) VectorGetItem(prev_node->char_links, edge_location));
	// what if there is no edge? prev_node_id is the last node
	// printf("got here\n");

	TrieNode2* prev_proxy = (TrieNode2*) VectorGetItem(my_trie_tree->word_tree, prev_proxy_id);
	// how is this -1 after puting into a tree
	int last_child_letter = TrieNode2GetLastEdge(my_trie_tree, prev_node_id);
	// printf("last child %i\n", last_child_letter);
	int prev_prev_node_id = prev_node_id;
	// TrieNode2* last_prev_word_node;
	int last_word_counterpart = prev_node_id;
	// TrieTreePrintWordTrie(my_trie_tree);
	bool make_child = false;
	bool make_parent = false;
	Vector* path = VectorInitVector();
	VectorAppendInt(path, prev_node_id);
	// 4 problems to solve
	// last string in state name is the start of the path
	// get the path of char nodes along the largest edge in tree
	// determine if we are making a sibling or child node
	// find the last possible word node for sibling and child
	// find the last possible char node for sibling and chld
// |i||~||~||~||4||5|
	// get last char untill there is no edge
	while(last_child_letter > -1)
	{
		// there is a node we can get
		prev_node_id = TrieNode2GetLastNode(my_trie_tree, prev_node_id);
		VectorAppendInt(path, prev_node_id);

		
		// get the next edge
		last_child_letter = TrieNode2GetLastEdge(my_trie_tree, prev_node_id);
		// make sure the last item in existing path is not added to the adjusted name
		if(last_child_letter > -1)
		{
			string* x = TrieNode2MakeStringFromWord(my_trie_tree, prev_node_id);

			VectorAppend(name, x);

		}


	}
	// need the last string of the name to be the first node in the path
	// printf("our path\n");
	// VectorPrint(path);
	
	
	// printf("%i\n", TrieTreeIsChild(my_trie_tree, path));
	// find prev_node
	int last_prev_node_2 = TrieTreeFindLastPrevNode(my_trie_tree, path);
	// find prev_word_node
	int last_word_node_2 = TrieTreeFindLastWordNode(my_trie_tree, path);

	// printf("char hook %i, word hook %i\n", last_prev_node_2, last_word_node_2);
	// TrieTreePrintTrie(my_trie_tree);
	// TrieTreePrintWordTrie(my_trie_tree);
	// TrieTreePrintTrieWords(my_trie_tree);

	// assumes we alway make a new context to the tree
	// what if we are only adding a sibline nod to the tree?
	
	// printf("got past loop\n");
	// assume this will always exist from previous rounds of insert - generator and generator
	// link routine below works
	// assuming we are always making a child
	// the difference as shown above is who the parent is
	TrieNode2* last_prev_word_node = (TrieNode2*) VectorGetItem(my_trie_tree->word_tree, last_word_node_2/*TrieNode2GetWordCounterpart(my_trie_tree, prev_node_id)*/);//TrieNode2GetWord(my_trie_tree, prev_node_id);
	TrieNode2* last_prev_char_node = (TrieNode2*) VectorGetItem(my_trie_tree->trie_tree, last_prev_node_2);
	// printf("got here\n");

	/*
	link prev_proxy to final_word node
	link prev_node to final_char_node
	link prev_node to prev_proxy
	link prevy_proxy to prev_node
	*/
	// make last dimention and update trees
	// TrieNode2* final_char_node = TrieNode2initTrieNode2();
	// TrieNode2* final_word_node = TrieNode2initTrieNode2();

	// link char to word
	// store the char id into the word links
	// if there are no links?
	// why am I using the word nodes to get the letter edge that needs to be incremented?
	int link_count = VectorGetPopulation(last_prev_char_node->chars_from_edges);
	// printf("got here 2\n");
	char dummy_value = (char) 33;
	if(link_count > 0)
	{

		int last_index = VectorGetPopulation(last_prev_char_node->chars_from_edges) - 1;
		int last_letter = *((int*) VectorGetItem(last_prev_char_node->chars_from_edges, last_index));
		// printf("last letter %c\n", last_letter);
		if(last_letter < 126 && last_letter >= 0)
		{

			// new dimention name
			dummy_value = (char) (last_letter + 1);  // 0 <= last_index < 256
		}
		

	}
	// printf("got here 3\n");
	// printf("dummy value %c\n", dummy_value);
	// last index  VectorGetPopulation(prev_node->links) - 1
	// int last_index = VectorGetPopulation(last_prev_word_node->links) - 1;
	// int last_item = *((int*) VectorGetItem(last_prev_word_node->links, last_index));
	// // new dimention name
	// char dummy_value = (char) (last_index + 1);  // 0 <= last_index <= 256

	// final_char_node->my_value = dummy_value;


	// use the last value of the item at last index(the user will use values in a certain range and we want to come after all values already used)
	my_trie_tree->max_state_id++;
		// prev_node->state_id = my_trie_tree->max_state_id;
	TrieTreeInsertString(my_trie_tree, dummy_value, my_trie_tree->max_state_id);
	// the last char node has been made, stored into the char tree, and set to the next generated char value
	// printf("got here 4\n");
	// dummy_value is the char linking last_prev_char_node to new char node
	// char_id is the location of new char node in tree
	int char_id = VectorGetPopulation(my_trie_tree->trie_tree) - 1;

	int* dummy_value_ptr = (int*) malloc(sizeof(int));
	*dummy_value_ptr = dummy_value;

		// need to add an edge from prev_node and an edge from prev_proxy

	VectorAppend(last_prev_char_node->chars_from_edges, dummy_value_ptr);

	last_prev_char_node->char_links[dummy_value] = char_id;
	// haven't linked prev_node with new node
	// printf("got here 5\n");
	// make word node
	TrieNode2* word = TrieNode2initTrieNode2();
	word->word_letters = VectorInitVector();
	// word node -> char node
	// store char_id into word node
	int* char_id_ptr = (int*) malloc(sizeof(int));
	*char_id_ptr = char_id;
	VectorAppend(word->word_letters, char_id_ptr);
	// printf("char id %i\n", char_id);
	// VectorPrint(word->word_letters);
	// printf("got here 6\n");
	// insert word node into word tree
	VectorAppend(my_trie_tree->word_tree, word);
	// TrieTreePrintTrie(my_trie_tree);

	// TrieTreePrintWordTrie(my_trie_tree);


	int word_id = VectorGetPopulation(my_trie_tree->word_tree) - 1;
	// printf("got here 7\n");
	// frogot the word counterpart
	TrieNode2* added_node = (TrieNode2*) VectorGetItem(my_trie_tree->trie_tree, char_id);
	// word node  <- char node
	added_node->word_counterpart = word_id;
	// printf("got here 8\n");
	int* word_id_ptr = (int*) malloc(sizeof(int));
	*word_id_ptr = word_id;
	VectorAppend(last_prev_word_node->links, word_id_ptr);
	// printf("got here 9\n");
	// both nodes are made and their prevs link to them
	// link prev_word with new word
	// char node <--> word node
	// add new word added to state name
	// TrieTreePrintTrie(my_trie_tree);
	// TrieTreePrintWordTrie(my_trie_tree);
	// TrieTreePrintTrieWords(my_trie_tree);

	// printf("char id %i\n", char_id);
	// printf("got here 9.5\n");

	string* new_context_word = TrieNode2MakeStringFromWord(my_trie_tree, char_id);

	// append from path the node values in the range to the name
	// i: [1, end]
	VectorDeleteAllItems(path);

	// printf("got here 10\n");
	VectorAppend(name, new_context_word);

	// VectorAppend(my_trie_tree->trie_tree, final_char_node);

	// VectorAppend(my_trie_tree->word_tree, final_word_node);

	// int char_id = VectorGetPopulation(my_trie_tree->trie_tree) - 1;
	// int word_id = VectorGetPopulation(my_trie_tree->word_tree) - 1;


	// now we only have [0, n] possible children, where n < 257 
	// prev_node is now the parent of the final node to add
	/*
	add an extra word to tree
	while prev_node has children
		set prev_node to largest child

	add child to last child of prev_node(could be first one, middle one, or last one)
	*/

// missed a link
// result from first round
// 0 |r| word -1 state -1
// links
// |1|

// 1 |i| word 1 state 0
// links


// 2 |0| word 2 state 1
// links


// 0 ||
// links
// |1|

// 1 |i|
// links
// |2|

// 2 |0|
// links

}

Vector* TrieTreeInsertWords2(TrieTree* my_trie_tree, Vector* name /* strings*/, int expected_id)
{
	// each node is doubly linked
	// only char nodes
	int current_node_id = 0;
	TrieNode2* current_node;
	// VectorPrintStrings(name);

	// TrieNode2* prev_node = (TrieNode2*) VectorGetItem(my_trie_tree->trie_tree, 0);

	// make current node
	// use current node to find out if the ege to current actually exists
	// link them
	// prev node = current node
	// repeat
	// mark when the end of the word shoes up
	// generate state after hitting end
	// if entire string already exists then do soubtle add
	for(int i = 0; i < name->population; i++)
	{
		// printf("i %i\n", i);
		// TrieNode2* proxy_node = TrieNode2initTrieNode2();

		// proxy_node->word_letters = VectorInitVector();
		// proxy_node->links = VectorInitVector();


		// search through string and make path
		int number_of_new_letters = 0;
		int size = ((string*) name->values[i])->size();
		for(int j = 0; j < size; j++)
		{
			current_node = (TrieNode2*) VectorGetItem(my_trie_tree->trie_tree, current_node_id);

			char letter = (*((string*) name->values[i]))[j];
			// printf("letter to add %i\n", letter);
			//string letter_str;
			//letter_str += letter;
			int edge = current_node->char_links[letter];
			// printf("|%c| %i\n", letter, edge);

			// TrieNode2* current_node = (TrieNode2*) VectorGetItem(my_trie_tree->trie_tree, current_node_id);
			if(edge == -1)  // if this is true once it's always true for this function call
			{
				// make new node
				TrieTreeInsertString2(my_trie_tree, letter, -1, j == size - 1);
				
				// prev_node_id = current_node_id;
				int next_edge = VectorGetPopulation(my_trie_tree->trie_tree) - 1;



				// TrieNode2* current_node = (TrieNode2*) VectorGetItem(my_trie_tree->trie_tree, current_node_id);

				current_node->char_links[letter] = next_edge;
				VectorAppendInt(current_node->chars_from_edges, letter);

				current_node_id = next_edge;
				// prev_node_id = current_edge;


			}
			// starts out being true or never being true
			else if(edge > 0)
			{
				
				// keep moving
				
				current_node_id = edge;


			}

		}
	}
	// printf("the chars should be added in\n");
	// run through the trie made and make the word trie 
	// printf("creating the word tree now\n");
	int current_node_id_2 = 0;
	TrieNode2* current_node_2;
	int current_word_node_id = 0;
	TrieNode2* current_word_node;
	for(int i = 0; i < name->population; i++)
	{
		current_word_node = (TrieNode2*) VectorGetItem(my_trie_tree->word_tree, current_word_node_id);
		int number_of_new_letters = 0;
		int size = ((string*) name->values[i])->size();
		TrieNode2* new_word_node = TrieNode2initTrieNode2();

		for(int j = 0; j < size; j++)
		{
			current_node_2 = (TrieNode2*) VectorGetItem(my_trie_tree->trie_tree, current_node_id_2);

			char letter = (*((string*) name->values[i]))[j];
			// printf("letter to add %i\n", letter);
			//string letter_str;
			//letter_str += letter;
			int edge = current_node_2->char_links[letter];
			// printf("|%c| %i\n", letter, edge);
			if(edge == -1)
			{
				// we have no where else to go and the input should be already done
				printf("should not be happening |%c| %i\n", letter, edge);
			}
			else if(edge > 0)
			{
				// what if our word already exists?
				// collect everything then find out if a word already exists

				if(j == 0)
				{
					new_word_node->word_letters = VectorInitVector();
				}

				// [0, size - 2] only if size > 1
				if(j < size - 1)
				{
					// collect the edge
					VectorAppendInt(new_word_node->word_letters, edge);
				}
				// [size - 1]
				else if(j < size)
				{
					// collect the edge
					VectorAppendInt(new_word_node->word_letters, edge);
					// is the word node already there?
					TrieNode2* next_node = (TrieNode2*) VectorGetItem(my_trie_tree->trie_tree, edge);
					if(next_node->word_counterpart == -1)
					{
						// add word to word trie
						VectorAppend(my_trie_tree->word_tree, new_word_node);

						// add word's node id as the edge nodes's word counterpart
						next_node->word_counterpart = VectorGetPopulation(my_trie_tree->word_tree) - 1;

						// append the added word to the end of the current word node's edges
						VectorAppendInt(current_word_node->links, next_node->word_counterpart);

						// set the current word node to the added word node
						// current_word_node_id = next_node->word_counterpart;
						current_word_node_id = next_node->word_counterpart;
						// current_node_id_2 = edge;

					}
					else if(next_node->word_counterpart > -1)
					{
						// erase the sequence
						VectorDeleteAllItems(new_word_node->word_letters);

						free(new_word_node);

						// set the current word node to whatever word node the counterpart is
						current_word_node_id = next_node->word_counterpart;
						// current_node_id_2 = edge;

					}
				}
				current_node_id_2 = edge;

			}
		}
	}

	// TrieTreePrintWordTrie(my_trie_tree);
	TrieNode2* current_node_3 = (TrieNode2*) VectorGetItem(my_trie_tree->trie_tree, current_node_id_2);

	if(current_node_3->state_id == -1)
	{
		// This is for storing a subset of the general trie tree into a class local trie tree
		// all the data from the general trie tree must be preserved
		// don't mix these conditions when multiple items are inserted
		if(expected_id > -1)
		{
			// if this code is run the else below can't be run anymore for the local trie tree
			current_node_3->state_id = expected_id;

		}
		else
		{
			my_trie_tree->max_state_id++;
			current_node_3->state_id = my_trie_tree->max_state_id;
		}
		// TrieTreePrintTrie(my_trie_tree);

		

	}
	else
	{
		/* code */
		printf("item has already been added so generate a new case for it\n");
		TrieTreeAddSoubtleCase(my_trie_tree, current_node_id_2, current_word_node_id, name);
	}
	
	return name;


}

Vector* TrieTreeInsertWords(TrieTree* my_trie_tree, Vector* name /* strings*/, int expected_id)
{
	// this function is not for a user to work with 
	// insert the char nodes with end of word id's and state id's
	printf("trie tree insert words\n");
	exit(1);
	// read the nodes added and make a word path from them
	// if the node collected is at the end of the word(but only for the state it's assigned to)
		// if the node already links to a word
			// wipe out the word and restart on the next original char parent
		// copy the shorter word out of the longer word [0, current position]
	// if the node collected is at the end of the word(and not assgined to any state)
		// we have reached the end of the word
		// if the node already links to a word
			// wipe out the word and restart on the next original char parent

		// save word collected
		// make the next word as a child of the prev word saved
		// set original char parent to the char node stopped on
	// if all the char nodes were linked to their word
		// we would know when to start collecting chars for the word

	// composition of stack
	// root, any_matching_strings, location_of_next_insert_location

	// main ideas
	// char trie storing only chars
	// word trie storing proxy nodes linking to subsequences in the char trie
	// the word trie is mainly for printing the char trie in a friendly way
	// how they are connected:
	// each proxy node has links to the next proxy node and to the char nodes making up the sequence it represents
	// the last char node made from each input string links to its counterpart proxy node

	// 3 different sets of numbers used: char node id's, word id's, state id's
	// printf("inserting\n");
	// VectorPrintStrings(name);
	// printf("\n");
	// 1 take a sequence of items and add them to an ordered trie dict
	// 2 make some examples of states as input
	
	// input vector comes in
	// possibly modified input vector comes out with all the strings stored as a trie
	// all leaf nodes will have a link to the state object

	/*
	dfs strings
		if letter is not the next item
			add it in
		if hit the end and no key
			make new node and put key on it

	*/
	// there is a differene between making a functional data structure
	// and adding UI friendly features to it

	// as the characters are being added add them to the word node
	int prev_node_id = 0;
	TrieNode2* prev_node = (TrieNode2*) VectorGetItem(my_trie_tree->trie_tree, 0);

	int prev_proxy_id = 0;
	TrieNode2* prev_proxy = (TrieNode2*) VectorGetItem(my_trie_tree->word_tree, 0);
	// what if part of the input matches and part of it doesn't
	// what if all the input matches?
	// wht if all names are 1 character and they already have edges?
	// list of char numbers
	// list of flags saying if the char number marks the end of a word
	// already_has_edge flag
	// [a, b, c]
	// [0, 1, 1]
	// [0, 0, 0]

	// [i]
	// [1]
	// [1]

	// [i, c, d]
	// [1, 1, 1]
	// [1, 1, 1]

	// number, is last char, has edges already
	// at least 1 item is new

	// if item is at the end of word
		// put word together from [first char, current char]
		// put curser to current char + 1 position
		// somehow char node has to exist to link to end of word
	// if item has no edges
		// it's new
		// add it
		// if it's the last item
			// generate a state id
			// 
		
	for(int i = 0; i < name->population; i++)
	{
		// printf("i %i\n", i);
		TrieNode2* proxy_node = TrieNode2initTrieNode2();

		proxy_node->word_letters = VectorInitVector();
		proxy_node->links = VectorInitVector();


		// search through string and make path
		int number_of_new_letters = 0;
		int size = ((string*) name->values[i])->size();
		for(int j = 0; j < size; j++)
		{
			char letter = (*((string*) name->values[i]))[j];
			// printf("letter to add %i\n", letter);
			//string letter_str;
			//letter_str += letter;
			int edge = prev_node->char_links[letter];
			printf("|%c| %i\n", letter, edge);

			// didn't find a match
			// passes
			if(edge == -1)
			{
				number_of_new_letters++;
				// add node
				//string new_number;
				//new_number += letter;
				//new_number_ptr->resize(new_number_ptr->size() + 1);
				//string x = new_number_ptr->VectorAppend(new_number);
				//(*new_number_ptr) += new_number;
				//new_number_ptr = 
				//printf("new data item %c\n", letter);

				TrieTreeInsertString(my_trie_tree, letter, -1);
				
				int* sequence_id = (int*) malloc(sizeof(int));
				*sequence_id = VectorGetPopulation(my_trie_tree->trie_tree) - 1;

				VectorAppend(proxy_node->word_letters, sequence_id);
				//printf("sequence id %i\n", VectorGetPopulation(my_trie_tree->trie_tree) - 1);
				prev_node->char_links[letter] = VectorGetPopulation(my_trie_tree->trie_tree) - 1;

				int next_edge = prev_node->char_links[letter];

				// VectorAppend letter to the end of the char_edges(for the printing function)
				int* letter_number = (int*) malloc(sizeof(int));
				*letter_number = letter;
				VectorAppend(prev_node->chars_from_edges, letter_number);

				// if(j == 0)
				// {
					// get item inserted
					// TrieNode2* new_node = (TrieNode2*) VectorGetItem(my_trie_tree->trie_tree,
					// 										   next_edge);
					//printf("here %i\n", j);

					// new_node->start_of_word = 1;
					// start of word is total size of word
					/*
					if(j == size - 1)
					{
						my_trie_tree->max_state_id++;
						new_node->state_id = my_trie_tree->max_state_id;

					}
					*/
					//printf("here 2 %i\n", j);

					// set start of word flag
				// }

				// what if last char is not found?
				/*
				else if(i == name->population - 1 && j == size - 1)
				{
					TrieNode2* just_added_node = (TrieNode2*) VectorGetItem(my_trie_tree->trie_tree,
										   next_edge);

					my_trie_tree->max_state_id++;
					just_added_node->state_id = my_trie_tree->max_state_id;

				}*/
				prev_node_id = next_edge;  //////
				// visit node added
				prev_node = (TrieNode2*) VectorGetItem(my_trie_tree->trie_tree,
												 prev_node_id);

			}
			// |i| 69 <- edge
			// the single letter word doesn't map to a word becasue the edge already exists
			// if edge already exists but at last char in word
				// number_of_new_letters++
			// else if(edge > -1 && size == 1)
			// {
			// 	// our node already exists
			// 	// add to proxy_node
			// 	int* sequence_id = (int*) malloc(sizeof(int));
			// 	*sequence_id = edge;

			// 	VectorAppend(proxy_node->word_letters, sequence_id);
			// 	prev_proxy_id = edge;
			// 	int* sequence_id2 = (int*) malloc(sizeof(int));
			// 	*sequence_id2 = prev_proxy_id;
			// 	//printf("letters saved %i\n", prev_proxy_id);
			// 	VectorAppend(proxy_node->word_letters, sequence_id2);

			// }

			// untested
			// last char was found
			/*else if(i == name->population - 1 && j == size - 1)
			{
				//printf("%c\n", letter);
				TrieNode2* node_found = (TrieNode2*) VectorGetItem(my_trie_tree->trie_tree, edge);
				if(node_found != NULL)
				{
					// no key
					if(node_found->state_id == -1)
					{

						my_trie_tree->max_state_id++;
						node_found->state_id = my_trie_tree->max_state_id;

					}
					// has a key
					else
					{
						printf("already exists so making a new dimension\n");
						
						make another node
						store a '0' in it
						make an edge from node_found to another node at char = '0'

						TrieNode2* node_found2 = (TrieNode2*) VectorGetItem(my_trie_tree->trie_tree, last_item_on_stack);
						int number_of_neighbors = VectorGetPopulation(node_found2->links);

						stringstream s;
						s << number_of_neighbors;
						string new_number;
						s >> new_number;
						string* new_number_ptr = (string*) malloc(sizeof(string));
						*new_number_ptr = new_number;
						*/
					//}
					/*
					if no key
						put in key
					else
						add a 0 to the end of the sequence
						insert the next item to the end of last char found at tree[edge]
					*/
				//}
				
			//}
			// untested
			// match was found
			else
			{
				// collect letter
				prev_proxy_id = edge;
				int* sequence_id = (int*) malloc(sizeof(int));
				*sequence_id = prev_proxy_id;
				//printf("letters saved %i\n", prev_proxy_id);
				VectorAppend(proxy_node->word_letters, sequence_id);

				prev_node_id = edge; ///////
				prev_node = (TrieNode2*) VectorGetItem(my_trie_tree->trie_tree, prev_node_id);

			}


		}

		// add any new proxy(word) nodes needed
		//VectorPrint(proxy_node->word_letters);

		// prev_node is now the node holding the last letter
		// # of new letters > 0 and on last letter
		//printf("%s %i %i\n", (*((string*) name->values[i])).c_str(), number_of_new_letters, VectorGetPopulation(proxy_node->word_letters));
		if(number_of_new_letters > 0)
		{
			// entire word is new, so add as the next word from prev word
			// set last prev letter's word counterpart to the id of the new word added


			// have to connect prev_node to proxy_node
			VectorAppend(my_trie_tree->word_tree, proxy_node);
			// will be used to find the next prev_proxy(next word node)
			// It's the one place guaranteed to point to a single word reguardless of how many siblings there are or where you are in the sequence(many different sequences, but same single ansestor is stored). as long as the last node corresponds with the last letter in the search word, there should be no confusion as to what the next word is
			prev_node->word_counterpart = VectorGetPopulation(my_trie_tree->word_tree) - 1;

			int* link = (int*) malloc(sizeof(int));
			*link = VectorGetPopulation(my_trie_tree->word_tree) - 1;

			// VectorAppend population - 1 to prev proxy node's links
			VectorAppend(prev_proxy->links, link);

			// get last proxy node added (proxy_node)
			prev_proxy_id = VectorGetPopulation(my_trie_tree->word_tree) - 1;
			prev_proxy = (TrieNode2*) VectorGetItem(my_trie_tree->word_tree, prev_proxy_id);

		}
		else
		{
			// if(size == 1)
			// {
			// 				VectorAppend(my_trie_tree->word_tree, proxy_node);
			// // will be used to find the next prev_proxy(next word node)
			// // It's the one place guaranteed to point to a single word reguardless of how many siblings there are or where you are in the sequence(many different sequences, but same single ansestor is stored). as long as the last node corresponds with the last letter in the search word, there should be no confusion as to what the next word is
			// prev_node->word_counterpart = VectorGetPopulation(my_trie_tree->word_tree) - 1;

			// int* link = (int*) malloc(sizeof(int));
			// *link = edge;

			// // VectorAppend population - 1 to prev proxy node's links
			// VectorAppend(prev_proxy->links, link);

			// get last proxy node added (proxy_node)
			// prev_proxy_id = VectorGetPopulation(my_trie_tree->word_tree) - 1;
			// prev_proxy = (TrieNode2*) VectorGetItem(my_trie_tree->word_tree, prev_proxy_id);

			// }
			// entire word is old, so visit it by using the prev letter's id of the next word and erasing the word collected

			// delete proxy_node

			VectorDeleteAllItems(proxy_node->word_letters);
			VectorDeleteAllItems(proxy_node->links);
			free(proxy_node);

			prev_proxy_id = prev_node->word_counterpart;   ///////
			prev_proxy = (TrieNode2*) VectorGetItem(my_trie_tree->word_tree, prev_proxy_id);

		}
		
	}
	// prev_node should be last node checked so check for state there
	if(prev_node->state_id == -1)
	{
		// This is for storing a subset of the general trie tree into a class local trie tree
		// all the data from the general trie tree must be preserved
		// don't mix these conditions when multiple items are inserted
		if(expected_id > -1)
		{
			// if this code is run the else below can't be run anymore for the local trie tree
			prev_node->state_id = expected_id;

		}
		else
		{
			my_trie_tree->max_state_id++;
			prev_node->state_id = my_trie_tree->max_state_id;
		}
		

	}
	else
	{
		/* code */
		// printf("item has already been added so generate a new case for it\n");
		TrieTreeAddSoubtleCase(my_trie_tree, prev_node_id, prev_proxy_id, name);
	}
	
	return name;

}
TrieTree* TrieTreeInsertEdges(TrieTree* my_general_tree, TrieTree* my_trie_tree, Vector* names /* vectors of strings*/)
{
	for(int i = 0; i < VectorGetPopulation(names); i++)
	{
		int state_id = TrieTreeSearch(my_general_tree, (Vector*) VectorGetItem(names, i));
		// pass in the ith name and the state id
		// insert(tree, name, id)
		TrieTreeInsertWords2(my_trie_tree, (Vector*) VectorGetItem(names, i), state_id);
	}
	return my_trie_tree;
}


void TrieTreeEraseEdgeToTopCharNode(Vector* char_nodes_matching,
							int j,
							TrieTree* my_trie_tree,
							char top_node_value)
{
	if(VectorGetPopulation(char_nodes_matching) > 0)
	{
		// assumes all pointers exist
		int prev_node_id_2 = *((int*) VectorGetItem(char_nodes_matching, j));
		//printf("prev node id %i\n", prev_node_id_2);
		TrieNode2* prev_node_2 = (TrieNode2*) VectorGetItem(my_trie_tree->trie_tree, prev_node_id_2);
		//printf("before find loop\n");


		// find the index of the correct letter edge using the char value of the top char node
		char prev_edge_letter = top_node_value;
		int id_of_edge_to_delete = 0;
		// 
		for(int i = 0; i < VectorGetPopulation(prev_node_2->chars_from_edges); i++)
		{
			//printf("%i, ", *((int* )  VectorGetItem(prev_node_2->chars_from_edges, i) ));
			char letter_edge = ((char) *((int* )  VectorGetItem(prev_node_2->chars_from_edges, i) ) );
			if(letter_edge == prev_edge_letter)
			{
				//printf("found match %i\n", i);
				id_of_edge_to_delete = i;
			}

		}
		VectorDeleteItem(prev_node_2->chars_from_edges, id_of_edge_to_delete);
		prev_node_2->char_links[prev_edge_letter] = -1;
	}
	

}

int TrieTreeDeleteWords(TrieTree* my_trie_tree, Vector* name /* strings*/)
{

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

			int edge = prev_node->char_links[letter];
			// printf("%c ", letter);

			// printf("%i\n", edge);

			if(edge > -1)
			{
				TrieTreePush(char_nodes_matching, edge);

			}
			else
			{
				// exit cause there is no match
				printf("can't delete because it doesn't exist\n");
				return -1;
			}
			prev_node = (TrieNode2*) VectorGetItem(my_trie_tree->trie_tree, edge);

		}
		
		if(prev_node->word_counterpart > -1)
		{
			TrieTreePush(word_nodes_matching, prev_node->word_counterpart);
		}
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
	
	if(top_node->state_id > -1 && VectorGetPopulation(top_node->chars_from_edges) >= 1)
	{
		// printf("at internal node\n");
		top_node->state_id = -1;
		return -1;
	}

	// for deleting the hanging edge
	char poped_node_value;
	poped_node_value = top_node->my_value;
	// delete the node
	TrieNode2DeleteTrieNode2(top_node);
	VectorSetItemToNull(my_trie_tree->trie_tree, top_edge);
	top_node = NULL;

	VectorPopItem(char_nodes_matching);

	j = VectorGetPopulation(char_nodes_matching) - 1;
	top_edge = *((int*) VectorGetItem(char_nodes_matching, j));
	top_node = (TrieNode2*) VectorGetItem(my_trie_tree->trie_tree, top_edge);


	// if no items from the stack can be deleted
	// the item shares a path with other items
	// top_node->state_id will be > -1 for this case
	// deleting char nodes and poping from char stack
	while(VectorGetPopulation(top_node->chars_from_edges) <= 1 && top_node->state_id == -1 )
	{

			
		//VectorPrint(char_nodes_matching);

		// this will always the the last char deleted from char trie tree
		poped_node_value = top_node->my_value;
		//printf("here %x\n", top_node);
		TrieNode2DeleteTrieNode2(top_node);
		//printf("last edge %i, j %i\n", top_edge, j);

		VectorSetItemToNull(my_trie_tree->trie_tree, top_edge);
		top_node = NULL;

		VectorPopItem(char_nodes_matching);
		// can't delete the root node
		// wrong
		if(VectorGetPopulation(char_nodes_matching) == 1)
		{
			// printf("last j %i\n", j);
			break;
		}

		j = VectorGetPopulation(char_nodes_matching) - 1;
		top_edge = *((int*) VectorGetItem(char_nodes_matching, j));
		top_node = (TrieNode2*) VectorGetItem(my_trie_tree->trie_tree, top_edge);
	}
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

	int word_counterpart = top_node->word_counterpart;
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
	// loop is still wrong
	// printf("start\n");
	int prev_deleted_word_edge = 0;
	while(VectorGetPopulation(word_nodes_matching) > 1 && deleted_word_edge != word_counterpart)
	{
		// seems to go 1 iteration too far and the target value is rest with the lin before it
		// VectorPrint(word_nodes_matching);
		// printf("deleted word edge %i\n", deleted_word_edge);
	//TrieTreePrintWordTrie(my_trie_tree);
	
		TrieNode2DeleteTrieNode2(top_word);
		//			printf("here\n");
		//printf("deleted_word_edge %i\n", deleted_word_edge);
		// node 5 is erased and node 2's links are erased
		VectorSetItemToNull(my_trie_tree->word_tree, deleted_word_edge);
		top_word = NULL;
		//TrieTreePrintWordTrie(my_trie_tree);
		VectorPopItem(word_nodes_matching);
		if(VectorGetPopulation(word_nodes_matching) == 1)
		{
			break;
		}
		top_word_id = VectorGetPopulation(word_nodes_matching) - 1;
		prev_deleted_word_edge = deleted_word_edge;
		deleted_word_edge = *((int*) VectorGetItem(word_nodes_matching, top_word_id));
		top_word = (TrieNode2*) VectorGetItem(my_trie_tree->word_tree, deleted_word_edge);

	}
		

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
	printf("printing ordered dict trie\n");
	// loop through all elements
		// loop thorugh all attributes
	for(int i = 0; i < VectorGetPopulation(my_trie_tree->trie_tree); i++)
	{

		TrieNode2* node = (TrieNode2*) VectorGetItem(my_trie_tree->trie_tree, i);
		if(node != NULL)
		{
			//printf("printing array\n");

			printf("%i |%c| word %i state %i\n", i, node->my_value, node->word_counterpart, node->state_id);
			printf("links\n");
			for(int j = 0; j < VectorGetPopulation(node->chars_from_edges); j++)
			{
				int k = *((int*) VectorGetItem(node->chars_from_edges, j));
				printf("|%i|", node->char_links[k]);

			}
			
			printf("\n\n");

		}
		else
		{
			printf("%i empty\n\n", i);
		}

	}
}

void TrieTreePrintWordTrie(TrieTree* my_trie_tree)
{
	printf("printing ordered dict word tree\n");
	// loop through all elements
		// loop thorugh all attributes
	for(int i = 0; i < VectorGetPopulation(my_trie_tree->word_tree); i++)
	{

		TrieNode2* node = (TrieNode2*) VectorGetItem(my_trie_tree->word_tree, i);
		//("node %x\n", node);
		if(node != NULL)
		{
			//printf("printing array\n");

			//printf("%i |%c| %i %i\n", i, node->my_value, node->start_of_word, node->state_id);
			printf("%i |", i);
			//printf("%x %i\n", node->word_letters, VectorGetPopulation(node->word_letters));
			//printf("here\n");
			//VectorPrint(node->word_letters);
			//printf("done\n");
			if(node->word_letters != NULL)
			{
				for(int j = 0; j < VectorGetPopulation(node->word_letters); j++)
				{
					int k = *((int*) VectorGetItem(node->word_letters, j));
					// printf("%i", k);
					TrieNode2* char_node = (TrieNode2*) VectorGetItem(my_trie_tree->trie_tree, k);
					//printf("char_node %x\n", char_node);

					//printf("|%i|", k);
					if(char_node != NULL)
					{
						printf("%c", char_node->my_value);

					}
				}
			}
			
			printf("|\nlinks\n");
			if(node->links != NULL)
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
			else
			{
				printf("empty\n\n");
			}

			

		}
		else
		{
			printf("%i empty\n\n", i);
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
		for(int j = 0; j < VectorGetPopulation(next_letter_node->word_letters); j++)
		{
			int k = *((int*) VectorGetItem(next_letter_node->word_letters, j));
			//printf("|%i|", k);

			TrieNode2* char_node = (TrieNode2*) VectorGetItem(my_trie_tree->trie_tree, k);

			printf("%c", char_node->my_value);
			if(j == VectorGetPopulation(next_letter_node->word_letters) - 1)
			{
				if(char_node->state_id > -1)
				{
					printf("| -> %i", char_node->state_id);
				}
				else
				{
					printf("|");
				}

			}

		}

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

				top_ith_edge = *((int*) VectorGetItem(ith_edge_stack, VectorGetPopulation(ith_edge_stack) - 1));

				//printf("top node id %i, population %i, top edge %i\n", top_node_id_2, VectorGetPopulation(top_node_2->links), top_ith_edge);
				// have to use the edge for the below comparison too
				// if edge at top of stack can be incremented(edge + 1 < node's links length)
				if(top_ith_edge + 1 < VectorGetPopulation(top_node_2->links))
				{
					// wrong
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
	if(node == NULL)
	{
		return;
	}
	if(node->value == NULL)
	{
		return;
	}
	string my_string = *((string*) node->value);

	if(node->state_id > -1)
	{
		printf("%s %s -> %i\n\n", indents.c_str(), my_string.c_str(), node->state_id);

	}
	else
	{
		printf("%s %s\n\n", indents.c_str(), my_string.c_str());

	}
	for(int j = 0; j < VectorGetPopulation(node->links); j++)
	{
		TrieTreePrintTrieRecursive(my_trie_tree, *((int*) VectorGetItem(node->links, j)), indents + "  ");
	}

}


void TrieTreeTest()
{
	TrieTree* my_trie_tree = TrieTreeInitTrieTree();
	printf("inserting\n");
	Vector* name2 = TrieTreeInsertWords2(my_trie_tree, VectorAddStringToVector2("abvf", "tgrfede"), -1);
	VectorPrintStrings(VectorAddStringToVector2("abvf", "tgrfede"));
	int a = TrieTreeSearch(my_trie_tree, VectorAddStringToVector2("abvf", "tgrfede"));
	printf("found state id %i\n", a);


	Vector* name1 = TrieTreeInsertWords2(my_trie_tree, VectorAddStringToVector1("abvf"), -1);


	TrieTreeDeleteWords(my_trie_tree, VectorAddStringToVector2("abvf", "tgrfede"));

	Vector* name3 = TrieTreeInsertWords2(my_trie_tree, VectorAddStringToVector3("abvf", "tgrfede", "f"), -1);



	Vector* name4 = TrieTreeInsertWords2(my_trie_tree, VectorAddStringToVector3("abvf", "tgrfede", "hijk"), -1);
	
	Vector* name5 = TrieTreeInsertWords2(
						my_trie_tree,
						VectorAddStringToVectorGeneral(
							(string [])
							{
								"abvf", "tgrfede", "hijk", "i"
							}, 4
						),
						-1
					);
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

	Vector* name6 = TrieTreeInsertWords2(my_trie_tree, VectorAddStringToVector1("input_string"), -1);
	Vector* name7 = TrieTreeInsertWords2(my_trie_tree, VectorAddStringToVector1("i"), -1);

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
	Vector* x =  TrieTreeInsertWords2(my_trie_tree, VectorAddStringToVector1("i"), -1);
	// printf("got here\n");
	Vector* i = TrieTreeInsertWords2(my_trie_tree, VectorAddStringToVector1("iii"), -1);
	// TrieTreePrintTrie(my_trie_tree);
	// TrieTreePrintWordTrie(my_trie_tree);
	// exit(1);

	// TrieTreePrintTrieWords(my_trie_tree);

	Vector* i1 = TrieTreeInsertWords2(my_trie_tree, VectorAddStringToVector1("iii"), -1);
	// TrieTreePrintTrie(my_trie_tree);
	VectorPrintStrings(i1);
	printf("\n");
	TrieTreePrintTrieWords(my_trie_tree);

	// exit(1);
	// printf("\n");

	// TrieTreePrintTrieWords(my_trie_tree);
	Vector* i2 = TrieTreeInsertWords2(my_trie_tree, VectorAddStringToVector1("iii"), -1);
	// // TrieTreePrintTrie(my_trie_tree);
	VectorPrintStrings(i2);
	// printf("\n");

	Vector* i3 = TrieTreeInsertWords2(my_trie_tree, VectorAddStringToVector1("iii"), -1);
	// // TrieTreePrintTrie(my_trie_tree);
	VectorPrintStrings(i3);
	// printf("\n");
	// TrieTreePrintTrieWords(my_trie_tree);

	// according to the logs, it probably went out of bounds
	// fix bounds problem
	// the max number of visible chars is 96
	Vector* i4 = TrieTreeInsertWords2(my_trie_tree, VectorAddStringToVector1("j"), -1);
	VectorPrintStrings(i4);
	// wondering why this would work as it could throw off the letter counter
	i4 = TrieTreeInsertWords2(my_trie_tree, VectorAddStringToVector2("iii", "![[)"), -1);
	VectorPrintStrings(i4);
	i4 = TrieTreeInsertWords2(my_trie_tree, VectorAddStringToVector2("iii", "![[)8[)"), -1);
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

		i4 = TrieTreeInsertWords2(my_trie_tree, VectorAddStringToVector1("iii"), -1);
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