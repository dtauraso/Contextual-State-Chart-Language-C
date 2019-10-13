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


int TrieTreeSearch(TrieTree* my_trie_tree, Vector* name /* strings*/)
{

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
void TrieTreeInsertString(TrieTree* my_trie_tree, char element, int state_id)
{
	TrieNode2* node = TrieNode2initTrieNode2();

	//string* node_string = (string*) malloc(sizeof(string));
	//node_string = element;
	//node->value = element;
	node->my_value = element;
	node->value_type = 1;
	node->state_id = state_id;
	VectorAppend(my_trie_tree->trie_tree, node);

}

int TrieNode2GetLastNode(TrieTree* my_trie_tree, int prev_node_id)
{
	// getting the last letter edge so in case user adds edges edges to tree this generator made, the generator will not
	// create nodes that already exist
	TrieNode2* prev_node = (TrieNode2*) VectorGetItem(my_trie_tree->trie_tree, prev_node_id);
	int edge_index = VectorGetPopulation(prev_node->chars_from_edges) - 1;
	// this is the "letter"
	int letter = *((int*) VectorGetItem(prev_node->chars_from_edges, edge_index));
	int next_node = prev_node->char_links[letter];
	return next_node;
}

int TrieNode2GetLastEdge(TrieTree* my_trie_tree, int prev_node_id)
{
	// getting the last letter edge so in case user adds edges edges to tree this generator made, the generator will not
	// create nodes that already exist
	TrieNode2* prev_node = (TrieNode2*) VectorGetItem(my_trie_tree->trie_tree, prev_node_id);
	int edge_index = VectorGetPopulation(prev_node->chars_from_edges) - 1;
	// this is the "letter"
	int letter = *((int*) VectorGetItem(prev_node->chars_from_edges, edge_index));

	return letter;
}

int TrieNode2GetWordCounterpart(TrieTree* my_trie_tree, int prev_node_id)
{
	TrieNode2* prev_node = (TrieNode2*) VectorGetItem(my_trie_tree->trie_tree, prev_node_id);
	if(prev_node->word_counterpart > -1)
	{
		return prev_node->word_counterpart;
	}
}

TrieNode2* TrieNode2GetWord(TrieTree* my_trie_tree, int prev_node_id)
{
	TrieNode2* prev_node = (TrieNode2*) VectorGetItem(my_trie_tree->trie_tree, prev_node_id);
	if(prev_node->word_counterpart > -1)
	{

		return (TrieNode2*) VectorGetItem(my_trie_tree->word_tree, prev_node->word_counterpart);
	}
}
string* TrieNode2MakeStringFromWord(TrieTree* my_trie_tree, int prev_node_id)
{
	string word;
	// insert 
	TrieNode2* prev_proxy = TrieNode2GetWord(my_trie_tree, prev_node_id);
	for(int j = 0; j < VectorGetPopulation(prev_proxy->word_letters); j++)
	{
		int k = *((int*) VectorGetItem(prev_proxy->word_letters, j));

		TrieNode2* char_node = (TrieNode2*) VectorGetItem(my_trie_tree->trie_tree, k);

		
		// printf("%c", char_node->my_value);
		word += char_node->my_value;

	}
	string* new_context_word = (string*) malloc(sizeof(string));
	*new_context_word = word;
	return new_context_word;
}

// TrieNode2* TrieNodeGetTrieNode()
void TrieTreeAddSoubtleCase(TrieTree* my_trie_tree, int prev_node_id, int prev_proxy_id, Vector* name /* strings*/)
{
	// TrieNode2* prev_node = (TrieNode2*) VectorGetItem(my_trie_tree->trie_tree, prev_node_id);
	// int edge_index = VectorGetPopulation(prev_node->chars_from_edges) - 1;
	// int edge_location = *((int*) VectorGetItem(prev_node->chars_from_edges, edge_index));
	// int edge_value = *((int*) VectorGetItem(prev_node->char_links, edge_location));
	int last_child = TrieNode2GetLastEdge(my_trie_tree, prev_node_id);
	
	TrieNode2* prev_proxy = (TrieNode2*) VectorGetItem(my_trie_tree->word_tree, prev_proxy_id);

	// getting the nth dimention added in previous rounds

	// prev_node = (TrieNode2*) VectorGetItem(my_trie_tree->trie_tree, prev_node_id);



	// int last_child = VectorGetPopulation(prev_node->links);
	// there can not be -n children
	// while there is no room to add another child
	// the words and charas grow at different rates
	// make sure we get all dimentions already stored in the tree
	// ["256", "255, 256" ]
	// 256, 255: 256  char sequence[256, 255, 256]
	// w1, w2
	//     w1
	// w1,       w2
	// (256, state1, word1), (255, -1, -1), (256, state3, word3) 
	// (256, state1, word1), (256, -1, -1), (255, state3, word3) 

	// (256, state1, word1), (256, -1, -1), (256, state3, word3) 
	// 256, 256, 256
 
	while(last_child == 256)
	{
		// need to add each edge to name

		if(TrieNode2GetWordCounterpart(my_trie_tree, prev_node_id) > -1)
		{

			string* new_context_word = TrieNode2MakeStringFromWord(my_trie_tree, prev_node_id);
			VectorAppend(name, new_context_word);

			last_child = TrieNode2GetLastEdge(my_trie_tree, prev_node_id);

		}

		// advance to last node
		prev_node_id = TrieNode2GetLastNode(my_trie_tree, prev_node_id);
		


	}
	// assume this will always exist from previous rounds of insert - generator and generator
	TrieNode2* last_prev_word_node = (TrieNode2*) VectorGetItem(my_trie_tree->word_tree, last_child);//TrieNode2GetWord(my_trie_tree, prev_node_id);
	TrieNode2* last_prev_char_node = (TrieNode2*) VectorGetItem(my_trie_tree->trie_tree, prev_node_id);

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
	int link_count = VectorGetPopulation(last_prev_word_node->chars_from_edges);
	char dummy_value = '\0';
	if(link_count > 0)
	{
		int last_index = VectorGetPopulation(last_prev_word_node->chars_from_edges) - 1;
		int last_letter = *((int*) VectorGetItem(last_prev_word_node->chars_from_edges, last_index));
		// new dimention name
		dummy_value = (char) (last_letter + 1);  // 0 <= last_index <= 256

	}
	
	// last index  VectorGetPopulation(prev_node->links) - 1
	// int last_index = VectorGetPopulation(last_prev_word_node->links) - 1;
	// int last_item = *((int*) VectorGetItem(last_prev_word_node->links, last_index));
	// // new dimention name
	// char dummy_value = (char) (last_index + 1);  // 0 <= last_index <= 256

	// final_char_node->my_value = dummy_value;


	// use the last value of the item at last index(the user will use values in a certain range and we want to come after all values already used)
	my_trie_tree->max_state_id++;
		// prev_node->state_id = my_trie_tree->max_state_id;
	// need to add an edge from prev_node and an edge from prev_proxy

	TrieTreeInsertString(my_trie_tree, dummy_value, my_trie_tree->max_state_id);
	// the last char node has been made, stored into the char tree, and set to the next generated char value

	// dummy_value is the char linking last_prev_char_node to new char node
	// char_id is the location of new char node in tree
	int char_id = VectorGetPopulation(my_trie_tree->trie_tree) - 1;
	last_prev_char_node->char_links[dummy_value] = char_id;
	// haven't linked prev_node with new node

	// make word node
	TrieNode2* word = TrieNode2initTrieNode2();
	// word node -> char node
	// store char_id into word node
	char* char_id_ptr = (char*) malloc(sizeof(char));
	*char_id_ptr = char_id;
	VectorAppend(word->word_letters, char_id_ptr);
	// insert word node into word tree
	VectorAppend(my_trie_tree->word_tree, word);
	int word_id = VectorGetPopulation(my_trie_tree->word_tree) - 1;
	// frogot the word counterpart
	TrieNode2* added_node = (TrieNode2*) VectorGetItem(my_trie_tree->trie_tree, char_id);
	// word node  <- char node
	added_node->word_counterpart = word_id;

	int* word_id_ptr = (int*) malloc(sizeof(int));
	*word_id_ptr = word_id;
	VectorAppend(last_prev_word_node->links, word_id_ptr);
	// both nodes are made and their prevs link to them
	// link prev_word with new word
	// char node <--> word node
	// add new word added to state name

	string* new_context_word = TrieNode2MakeStringFromWord(my_trie_tree, char_id);
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

}

Vector* TrieTreeInsertWords(TrieTree* my_trie_tree, Vector* name /* strings*/)
{
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
	printf("inserting\n");
	VectorPrintStrings(name);
	printf("\n");
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
	for(int i = 0; i < name->population; i++)
	{
		TrieNode2* proxy_node = TrieNode2initTrieNode2();

		proxy_node->word_letters = VectorInitVector();
		proxy_node->links = VectorInitVector();


		// search through string and make path
		int number_of_new_letters = 0;
		int size = ((string*) name->values[i])->size();
		for(int j = 0; j < size; j++)
		{
			char letter = (*((string*) name->values[i]))[j];
			//string letter_str;
			//letter_str += letter;
			int edge = prev_node->char_links[letter];
			//printf("|%c| %i\n", letter, edge);

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

				if(j == 0)
				{
					// get item inserted
					TrieNode2* new_node = (TrieNode2*) VectorGetItem(my_trie_tree->trie_tree,
															   next_edge);
					//printf("here %i\n", j);

					new_node->start_of_word = 1;
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
				}

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
						/*
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

		my_trie_tree->max_state_id++;
		prev_node->state_id = my_trie_tree->max_state_id;

	}
	else
	{
		/* code */
		//addSoubtleCase(my_trie_tree, prev_node_id, prev_proxy_id);
	}
	
	return name;

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
	printf("delete\n");
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

			//printf("%c\n", letter);

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
	//VectorPrint(char_nodes_matching);
	//VectorPrint(word_nodes_matching);

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
		printf("at internal node\n");
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
			printf("last j %i\n", j);
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
	printf("words\n");
	VectorPrint(word_nodes_matching);
	VectorPrint(char_nodes_matching);

	int word_counterpart = top_node->word_counterpart;
	printf("word counterpart %i\n", word_counterpart);
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
	printf("start\n");
	int prev_deleted_word_edge = 0;
	while(VectorGetPopulation(word_nodes_matching) > 1 && deleted_word_edge != word_counterpart)
	{
		// seems to go 1 iteration too far and the target value is rest with the lin before it
		VectorPrint(word_nodes_matching);
		printf("deleted word edge %i\n", deleted_word_edge);
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

	printf("after word stack deleting %i\n", prev_deleted_word_edge);
	VectorPrint(word_nodes_matching);
	VectorPrint(char_nodes_matching);

	// delete word nodes and word stack
	// delete final word edge
	//printf("%i\n", top_word_id);
	int edge = *((int*) VectorGetItem(word_nodes_matching, VectorGetPopulation(word_nodes_matching) - 1));
	TrieNode2* word_node = (TrieNode2*) VectorGetItem(my_trie_tree->word_tree, edge);
	int location_of_word_edge = 0;
	for(int i = 0; i < VectorGetPopulation(word_node->links); i++)
	{
		int word_node_edge = *((int*) VectorGetItem(word_node->links, i));
		if(word_node_edge == prev_deleted_word_edge)
		{
			location_of_word_edge = i;
			break;
		}
	}
	//printf("location of word edge %i\n", location_of_word_edge);
	//VectorPrint(word_node->links);
	VectorDeleteItem(word_node->links, location_of_word_edge);
	VectorSetItemToNull(word_node->links, deleted_word_edge);
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
					//printf("k %i\n", k);
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
				//printf("%i\n", VectorGetPopulation(node->links));
				for(int l = 0; l < VectorGetPopulation(node->links); l++)
				{
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

	TrieNode2* node = (TrieNode2*) VectorGetItem(my_trie_tree->trie_tree, root);

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


