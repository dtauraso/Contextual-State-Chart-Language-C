#include "trie_tree.h"

Vector* initVector();
void* getItem(Vector* container, int i);
void append(Vector* container, void* element);
int getPopulation(Vector* container);
void Print(Vector* container);
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

TrieNode2* initTrieNode2()
{
	// assume the dafault type to be stored is an integer
	TrieNode2* my_node = (TrieNode2*) malloc(sizeof(TrieNode2));

	my_node->value = NULL;
	my_node->links = initVector();

	memset(my_node->char_links, -1, sizeof(int) * 256);
	my_node->chars_from_edges = initVector();
	my_node->value_type = 0;
	my_node->state_id = -1;
	my_node->start_of_word = 0;
	my_node->word_counterpart = -1;

	return my_node;

}
bool deleteTrieNode2(TrieNode2* node)
{
	if(node != NULL)
	{
		free(node->value);
		if(node->links != NULL)
		{
				deleteAllItems(node->links);
				node->links = NULL;

		}
		if(node->chars_from_edges != NULL)
		{
				deleteAllItems(node->chars_from_edges);
				node->chars_from_edges = NULL;

		}
		//printf("word letters %x\n", node->word_letters);
		if(node->word_letters != NULL)
		{
			//printf("about to erase\n");
			deleteAllItems(node->word_letters);
			node->word_letters = NULL;
			//printf("erased\n");
		}
		free(node);
		return true;
		/*
		if(deleteAllItems(node->links))
		{
			//printf("erased links\n");
			free(node);
			//node = NULL;
			return true;
		}

		return false;
		*/
	}
	

}
void* getValue(TrieNode2* node)
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
TrieTree* initTrieTree()
{
	TrieTree* my_trie_tree = (TrieTree*) malloc(sizeof(TrieTree));

	my_trie_tree->trie_tree = initVector();
	my_trie_tree->word_tree = initVector();

	// add a node called "root"
	// root is not the last word
	char root = 'r';
	insertString(my_trie_tree, root, -1);

	TrieNode2* node = initTrieNode2();

	node->word_letters = initVector();
	node->links = initVector();
	//string* node_string = (string*) malloc(sizeof(string));
	//node_string = element;
	//node->value = element;
	//node->my_value = 'r';
	//node->value_type = 1;
	//node->state_id = state_id;

	append(my_trie_tree->word_tree, node);


	my_trie_tree->root = 0;
	my_trie_tree->max_state_id = -1;

	//printf("%s\n", ((string*) ((TrieNode2*) getItem(my_trie_tree->trie_tree, my_trie_tree->root))->value)->c_str());
	return my_trie_tree;

}
// (id of parent node, ith string, did we find a match for the ith string, location to insert the link for the child node)
// insertStrings
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
void push(Vector* container, int new_item)
{
	int* new_item_ptr = (int*) malloc(sizeof(int));
	*new_item_ptr = new_item;
	append(container, new_item_ptr);
}
int getNextNode(TrieTree* my_trie_tree, Vector* node_id_stack, Vector* ith_edge_stack)
{
	int top_node_id = *((int*) getItem(node_id_stack, getPopulation(node_id_stack) - 1));
	TrieNode2* top_node = (TrieNode2*) getItem(my_trie_tree->word_tree, top_node_id);

	int top_ith_edge = *((int*) getItem(ith_edge_stack, getPopulation(ith_edge_stack) - 1));
	return *((int*) getItem(top_node->links, top_ith_edge) );

}

// int search
/*
push items to a stack
when done, return a pointer to the stack
*/
Vector* innerSearchForStrings(TrieTree* my_trie_tree, Vector* name /* strings*/)
{
	// composition of stack
	// root, any_matching_strings, location_of_next_insert_location
	/*
	these are only for matching up the words. It's not saying anything if there is a key at the end
	1 match ending with a non-match
	0, 1, -1
	0, 1, 0

	no matches
	0, -1
	0, 0
	
	1 perfect match
	0, 1
	0, 2
	*/
	int prev_node_id = 0;
	TrieNode2* prev_node = (TrieNode2*) getItem(my_trie_tree->trie_tree, 0);
	Vector* stack = initVector();
	int* prev_node_id_ptr = (int*) malloc(sizeof(int));
	*prev_node_id_ptr = 0;
	append(stack, prev_node_id_ptr);
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
			append(stack, item_found_location_ptr);
			// don't have a way to prove if the last found node has a key
			/*
			insert
				if no match, only needs the last node found
				if match, only needs the last node found
			delete
				if match, needs the full history of nodes found
				if no match, needs nothing

			*/
			if(edge == -1)
			{
				return stack;
			}
			else if(j == size - 1)
			{
				return stack;
			}
			else
			{
				prev_node = (TrieNode2*) getItem(my_trie_tree->trie_tree, edge);

			}
		}		
		
	}
	return stack;
}

void insertString(TrieTree* my_trie_tree, char element, int state_id)
{
	TrieNode2* node = initTrieNode2();

	//string* node_string = (string*) malloc(sizeof(string));
	//node_string = element;
	//node->value = element;
	node->my_value = element;
	node->value_type = 1;
	node->state_id = state_id;
	append(my_trie_tree->trie_tree, node);

}
void insertString2(TrieTree* my_trie_tree, string element, int state_id)
{
	TrieNode2* node = initTrieNode2();

	string* node_string = (string*) malloc(sizeof(string));
	*node_string = element;
	node->value = node_string;
	node->value_type = 1;
	node->state_id = state_id;
	append(my_trie_tree->trie_tree, node);

}

void insertEdge(TrieNode2* last_node_matched,
				int edge_position,
				int* id)
{
	// insert id at last_node_matched.edges[edge_position]
	// shift items to the right
	// set
	// 0 because we are inserting an integer
	insertItem(last_node_matched->links, id, edge_position, 0);

}

Vector* insertWords(TrieTree* my_trie_tree, Vector* name /* strings*/)
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
	printStrings(name);
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
	TrieNode2* prev_node = (TrieNode2*) getItem(my_trie_tree->trie_tree, 0);

	int prev_proxy_id = 0;
	TrieNode2* prev_proxy = (TrieNode2*) getItem(my_trie_tree->word_tree, 0);
	// what if part of the input matches and part of it doesn't
	// what if all the input matches?
	for(int i = 0; i < name->population; i++)
	{
		TrieNode2* proxy_node = initTrieNode2();

		proxy_node->word_letters = initVector();
		proxy_node->links = initVector();


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
				//string x = new_number_ptr->append(new_number);
				//(*new_number_ptr) += new_number;
				//new_number_ptr = 
				//printf("new data item %c\n", letter);

				insertString(my_trie_tree, letter, -1);
				int* sequence_id = (int*) malloc(sizeof(int));
				*sequence_id = getPopulation(my_trie_tree->trie_tree) - 1;

				append(proxy_node->word_letters, sequence_id);
				//printf("sequence id %i\n", getPopulation(my_trie_tree->trie_tree) - 1);
				prev_node->char_links[letter] = getPopulation(my_trie_tree->trie_tree) - 1;

				int next_edge = prev_node->char_links[letter];

				// append letter to the end of the char_edges(for the printing function)
				int* letter_number = (int*) malloc(sizeof(int));
				*letter_number = letter;
				append(prev_node->chars_from_edges, letter_number);

				if(j == 0)
				{
					// get item inserted
					TrieNode2* new_node = (TrieNode2*) getItem(my_trie_tree->trie_tree,
															   next_edge);
					//printf("here %i\n", j);

					new_node->start_of_word = 1;
					// start of word is total size of word
					if(j == size - 1)
					{
						my_trie_tree->max_state_id++;
						new_node->state_id = my_trie_tree->max_state_id;

					}
					//printf("here 2 %i\n", j);

					// set start of word flag
				}

				// what if last char is not found?
				else if(i == name->population - 1 && j == size - 1)
				{
					TrieNode2* just_added_node = (TrieNode2*) getItem(my_trie_tree->trie_tree,
										   next_edge);

					my_trie_tree->max_state_id++;
					just_added_node->state_id = my_trie_tree->max_state_id;

				}

				// visit node added
				prev_node = (TrieNode2*) getItem(my_trie_tree->trie_tree,
												 next_edge);

			}
			// untested
			// last char was found
			else if(i == name->population - 1 && j == size - 1)
			{
				//printf("%c\n", letter);
				TrieNode2* node_found = (TrieNode2*) getItem(my_trie_tree->trie_tree, edge);
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

						TrieNode2* node_found2 = (TrieNode2*) getItem(my_trie_tree->trie_tree, last_item_on_stack);
						int number_of_neighbors = getPopulation(node_found2->links);

						stringstream s;
						s << number_of_neighbors;
						string new_number;
						s >> new_number;
						string* new_number_ptr = (string*) malloc(sizeof(string));
						*new_number_ptr = new_number;
						*/
					}
					/*
					if no key
						put in key
					else
						add a 0 to the end of the sequence
						insert the next item to the end of last char found at tree[edge]
					*/
				}
				
			}
			// untested
			// match was found
			else
			{
				// collect letter
				prev_proxy_id = edge;
				int* sequence_id = (int*) malloc(sizeof(int));
				*sequence_id = prev_proxy_id;
				//printf("letters saved %i\n", prev_proxy_id);
				append(proxy_node->word_letters, sequence_id);

				
				prev_node = (TrieNode2*) getItem(my_trie_tree->trie_tree, edge);

			}


		}

		// add any new proxy(word) nodes needed
		//Print(proxy_node->word_letters);

		// prev_node is now the node holding the last letter
		// # of new letters > 0 and on last letter
		//printf("%s %i %i\n", (*((string*) name->values[i])).c_str(), number_of_new_letters, getPopulation(proxy_node->word_letters));
		if(number_of_new_letters > 0)
		{
			// entire word is new, so add as the next word from prev word
			// set last prev letter's word counterpart to the id of the new word added


			// have to connect prev_node to proxy_node
			append(my_trie_tree->word_tree, proxy_node);
			// will be used to find the next prev_proxy(next word node)
			// It's the one place guaranteed to point to a single word reguardless of how many siblings there are or where you are in the sequence(many different sequences, but same single ansestor is stored). as long as the last node corresponds with the last letter in the search word, there should be no confusion as to what the next word is
			prev_node->word_counterpart = getPopulation(my_trie_tree->word_tree) - 1;

			int* link = (int*) malloc(sizeof(int));
			*link = getPopulation(my_trie_tree->word_tree) - 1;

			// append population - 1 to prev proxy node's links
			append(prev_proxy->links, link);

			// get last proxy node added (proxy_node)
			prev_proxy_id = getPopulation(my_trie_tree->word_tree) - 1;
			prev_proxy = (TrieNode2*) getItem(my_trie_tree->word_tree, prev_proxy_id);

		}
		else
		{
			// entire word is old, so visit it by using the prev letter's id of the next word and erasing the word collected

			// delete proxy_node

			deleteAllItems(proxy_node->word_letters);
			deleteAllItems(proxy_node->links);
			free(proxy_node);


			prev_proxy = (TrieNode2*) getItem(my_trie_tree->word_tree, prev_node->word_counterpart);

		}
		
	}
	return name;

}
/*
delete
traverse all the way to the last word
save index of the last fork found and ith word tracking
use next match after index to be the first node to delete
delete the word chain


visit entire path
record the next fork found(a fork is a node with > 1 neighbors)
the last fork is where we stop
the index of the next match is the start of the path we need to delete

if current is also a fork
	can't delete any path
prev(last fork) and curent(first node diverging from fork that is part of our name to delete) are integers
one node coming after the last fork or n node
deleting
erase link to current from prev
prev = current
update current

loop
erase link to current from prev
erase datat in slot at prev

prev = current
update current
at some point current will not be able to be updated(last current can't be updated)
pull off the pointer state stored at last node and return it
*/
/*
tests for insert cases
test for insert cases and delete cases

make some tries and link them to insert and insert and delete

*/
int updateId(TrieTree* my_trie_tree, int old_id)
{
	if(old_id < my_trie_tree->trie_tree->population)
	{
		// assumes tree[old_id] has <= 1 links in it
		TrieNode2* node = (TrieNode2*) getItem(my_trie_tree->trie_tree, old_id);
		if(node->links->population > 0)
		{
			return *((int*) getItem(node->links, 0));
		}

	}
	return old_id;
}
/*
void deleteWord(TrieTree* my_trie_tree, int word_id)
{
	// delete the word object at word_id
}
*/
/*
void cutLinkToFirstNodeInPath(	TrieTree* my_trie_tree,
								Vector* name,
								int* lower_bound_ptr,
								int start_node,
								int ith_string_in_input)
{
	*lower_bound_ptr = searchItemTrieDict2(
		my_trie_tree->trie_tree,
		((TrieNode2*) getItem(my_trie_tree->trie_tree, start_node))->links,
		(string*) name->values[ith_string_in_input],
		0,
		2);

	// delete connection from root to first node in sequence
	TrieNode2* root_node = (TrieNode2*) getItem(my_trie_tree->trie_tree, start_node);

	int* find_item = (int*) malloc(sizeof(int));
	*find_item = *lower_bound_ptr;
	// 0 is for int
	int link_location = searchItem(root_node->links, find_item, 0);

	deleteItem(root_node->links, link_location);
}
*/
void appendNode(Vector* collected_nodes_to_delete, int tracker)
{
	int* tracker_ptr = (int*) malloc(sizeof(int));
	*tracker_ptr = tracker;
	append(collected_nodes_to_delete, tracker_ptr);

}
void appendNodes(Vector* collected_nodes_to_delete,
					int tracker,
					int last_partial_match,
					TrieTree* my_trie_tree)
{

	while(tracker < last_partial_match)
	{
		// printf("tracker %i, last_partial_match %i\n", tracker, last_partial_match);
		// collect the ids of the first link(there will be no forks here)
		appendNode(collected_nodes_to_delete, tracker);

		tracker = updateId(my_trie_tree, tracker);
		//printf("tracker %i, last_partial_match %i\n", tracker, last_partial_match);

		if(tracker == last_partial_match)
		{
			appendNode(collected_nodes_to_delete, tracker);

			return;//collected_nodes_to_delete;
		}
	}
}
int deleteNodes(Vector* nodes_to_delete, TrieTree* my_trie_tree)
{
	int state_id_to_delete = -1;
	for(int i = 0; i < nodes_to_delete->population; i++)
	{
		int word_id = *((int*) getItem(nodes_to_delete, i));
		TrieNode2* word = (TrieNode2*) getItem(my_trie_tree->trie_tree, word_id);


		int state_id = word->state_id;
		
		if(i == nodes_to_delete->population - 1)
		{
			state_id_to_delete = state_id;
		}

		//printf("here 2 {%i}\n", state_id);
		TrieNode2* item_to_delete = (TrieNode2*) getItem(my_trie_tree->trie_tree, word_id);
		deleteTrieNode2(item_to_delete);
		setItemToNull(my_trie_tree->trie_tree, word_id);
		//item_to_delete = NULL;
		//printf("deleted %x\n", (TrieNode2*) getItem(my_trie_tree->trie_tree, state_id));
		//printf("done here 2\n");


	}
	return state_id_to_delete;
}

void eraseEdgeToTopCharNode(Vector* char_nodes_matching,
							int j,
							TrieTree* my_trie_tree,
							char top_node_value)
{
	if(getPopulation(char_nodes_matching) > 0)
	{
		// assumes all pointers exist
		int prev_node_id_2 = *((int*) getItem(char_nodes_matching, j));
		//printf("prev node id %i\n", prev_node_id_2);
		TrieNode2* prev_node_2 = (TrieNode2*) getItem(my_trie_tree->trie_tree, prev_node_id_2);
		//printf("before find loop\n");


		// find the index of the correct letter edge using the char value of the top char node
		char prev_edge_letter = top_node_value;
		int id_of_edge_to_delete = 0;
		// 
		for(int i = 0; i < getPopulation(prev_node_2->chars_from_edges); i++)
		{
			//printf("%i, ", *((int* )  getItem(prev_node_2->chars_from_edges, i) ));
			char letter_edge = ((char) *((int* )  getItem(prev_node_2->chars_from_edges, i) ) );
			if(letter_edge == prev_edge_letter)
			{
				//printf("found match %i\n", i);
				id_of_edge_to_delete = i;
			}

		}
		deleteItem(prev_node_2->chars_from_edges, id_of_edge_to_delete);
		prev_node_2->char_links[prev_edge_letter] = -1;
	}
	

}

int deleteWords(TrieTree* my_trie_tree, Vector* name /* strings*/)
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
	Vector* char_nodes_matching = initVector();
	Vector* word_nodes_matching = initVector();
	int prev_node_id = 0;
	if(name == NULL)
	{
		return -1;
	}
	// assume name is not a sequence of null strings
	TrieNode2* prev_node = (TrieNode2*) getItem(my_trie_tree->trie_tree, 0);
	push(char_nodes_matching, 0);
	push(word_nodes_matching, 0);

	// getting the stack of char node ids matching the input
	for(int i = 0; i < name->population; i++)
	{
		//TrieNode2* proxy_node = initTrieNode2();

		//proxy_node->word_letters = initVector();
		//proxy_node->links = initVector();


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
				push(char_nodes_matching, edge);

			}
			else
			{
				// exit cause there is no match
				printf("can't delete because it doesn't exist\n");
				return -1;
			}
			prev_node = (TrieNode2*) getItem(my_trie_tree->trie_tree, edge);

		}
		
		if(prev_node->word_counterpart > -1)
		{
			push(word_nodes_matching, prev_node->word_counterpart);
		}
	}
	// there will be at least 1 word represented by char_nodes_matching
	Print(char_nodes_matching);
	//exit(1);

	// erase the char path, final edge, and char stack
	// assuming there will always be a node whose edge has to be deleted
	//printf("here\n");
	//Vector* words_stack = initVector();
	int j = getPopulation(char_nodes_matching) - 1;
	int top_edge = *((int*) getItem(char_nodes_matching, j));
	TrieNode2* top_node = (TrieNode2*) getItem(my_trie_tree->trie_tree, top_edge);

	
	// for deleting the hanging edge
	char poped_node_value;
	poped_node_value = top_node->my_value;
	// delete the node
	deleteTrieNode2(top_node);
	setItemToNull(my_trie_tree->trie_tree, top_edge);
	top_node = NULL;


	popItem(char_nodes_matching);

	j = getPopulation(char_nodes_matching) - 1;
	top_edge = *((int*) getItem(char_nodes_matching, j));
	top_node = (TrieNode2*) getItem(my_trie_tree->trie_tree, top_edge);

	// deleting char nodes and poping from char stack
	while(getPopulation(top_node->chars_from_edges) <= 1 && top_node->state_id == -1 )
	{

			

		// this will always the the last char deleted from char trie tree
		poped_node_value = top_node->my_value;

		deleteTrieNode2(top_node);
		setItemToNull(my_trie_tree->trie_tree, top_edge);
		top_node = NULL;

		popItem(char_nodes_matching);

		if(getPopulation(char_nodes_matching) == 0)
		{
			break;
		}

		j = getPopulation(char_nodes_matching) - 1;
		top_edge = *((int*) getItem(char_nodes_matching, j));
		top_node = (TrieNode2*) getItem(my_trie_tree->trie_tree, top_edge);
	}
	// delete the hanging edge
	if(getPopulation(char_nodes_matching) > 0)
	{
		eraseEdgeToTopCharNode(char_nodes_matching,
							   j,
							   my_trie_tree,
							   poped_node_value);
	}
	printf("after lots of deleting\n");
	Print(char_nodes_matching);
		Print(word_nodes_matching);
	printWordTrie(my_trie_tree);

	printf("delete word nodes\n");
	// there will always be at least 1 word matching the input
	int top_word_id = getPopulation(word_nodes_matching) - 1;

	int deleted_word_edge = *((int*) getItem(word_nodes_matching, top_word_id));
	TrieNode2* top_word = (TrieNode2*) getItem(my_trie_tree->word_tree, deleted_word_edge);
	// loop is still wrong
	while(getPopulation(word_nodes_matching) > 1)
	{

		Print(word_nodes_matching);
	//printWordTrie(my_trie_tree);

		deleteTrieNode2(top_word);
					printf("here\n");
		printf("deleted_word_edge %i\n", deleted_word_edge);
		// node 5 is erased and node 2's links are erased
		setItemToNull(my_trie_tree->word_tree, deleted_word_edge);
		top_word = NULL;
		printWordTrie(my_trie_tree);
		popItem(word_nodes_matching);
		if(getPopulation(word_nodes_matching) == 1)
		{
			break;
		}
		top_word_id = getPopulation(word_nodes_matching) - 1;
		deleted_word_edge = *((int*) getItem(word_nodes_matching, top_word_id));
		top_word = (TrieNode2*) getItem(my_trie_tree->word_tree, deleted_word_edge);

	}
	printWordTrie(my_trie_tree);

	printf("after word stack deleting %i\n", deleted_word_edge);
		Print(word_nodes_matching);

	// delete word nodes and word stack
	// delete final word edge
	//printf("%i\n", poped_word_id);
	int edge = *((int*) getItem(word_nodes_matching, 0));
	TrieNode2* word_node = (TrieNode2*) getItem(my_trie_tree->word_tree, edge);
	int location_of_word_edge = 0;
	for(int i = 0; i < getPopulation(word_node->links); i++)
	{
		int word_node_edge = *((int*) getItem(word_node->links, i));
		if(word_node_edge == deleted_word_edge)
		{
			location_of_word_edge = i;
			break;
		}
	}
	printf("location fo word edge %i\n", location_of_word_edge);
	deleteItem(word_node->links, location_of_word_edge);
	// cleanup words containing same chars as previous deleted char paths
	// wasn't deleted earlier because the char node linking to it is a fork char
	// if the last word's edges have now been deleted, delete the node and the link to it
	//if(getPopulation(word_node->links) == 0)
	//{
	//	printf("word node %i can be deleted\n", edge);
	//}
	/*
	// first ancestor word may link to a sibling word instead(if the 2 words overlap)
	int ancestor_word = findAncestorWord(char_nodes_matching, my_trie_tree);
	printf("ansestor word %i\n", ancestor_word);
	push(words_stack, 0);

	deleteAllItems(char_nodes_matching);
	printf("my word stack\n");
	//Print(words_stack);

	// erase the edge from the prev node before deleting the current node
	// don't erase the edge from the final node on the stack
	for(int i = 0; i < getPopulation(words_stack); i++)
	{
		Print(words_stack);

		int edge = *((int*) getItem(words_stack, i));
		if(edge > 0)
		{
			TrieNode2* word_node = (TrieNode2*) getItem(my_trie_tree->word_tree, edge);
			deleteTrieNode2(word_node);
			setItemToNull(my_trie_tree->word_tree, edge);

		}
		else
		{

		}

	}
	deleteAllItems(words_stack);
	*/
	deleteAllItems(char_nodes_matching);
	deleteAllItems(word_nodes_matching);
	// deleteAllItems should have already set these to NULL
	char_nodes_matching = NULL;
	word_nodes_matching = NULL;
	printf("done %x, %x\n", char_nodes_matching, word_nodes_matching);
	//Print(char_nodes_matching);
	//Print(word_nodes_matching);

	/*

	start
		start 1
			start 2

	delete start, start 1, start 2


	start
		start 1
			start 2
				0

	delete start, start 1, start 2
	delete start, start 1, start 2, 0


	start
		start 1
			start 2
				0
	another start
		2
	
	delete start, start 1, start 2
	delete start, start 1, start 2, 0
	delete another start, 2

	start
		start 1
			start 2
				0
				1
					0
						0
	another start
		2
	
	delete start, start 1, start 2  (fork and last node are same)
	delete start, start 1, start 2, 0 (1 unit from fork)
	delete start, start 1, start 2, 1
	delete start, start 1, start 2, 1, 0, 0 (3 units from fork)
	delete another start, 2 (no fork)
	*/

	/*
	path has 0 forks and ends at an internal node(return id)
	path has 0 forks and ends at a leaf node(delete all nodes and return id)
	path has n forks and ends at a leaf node(delete unique path part and return id)
	*/
	// return -1 if there is no state to delete
	// delete the unique path name is saved as(may be a path or not)
	// remove the data part and return it	
	// input vector comes in
	// possibly modified input vector comes out with all the strings stored as a trie
	// all leaf nodes will have a link to the sate object
	// returns the id of the last node found
	/*
	int prev_node_id = 0;
	TrieNode2* prev_node = (TrieNode2*) getItem(my_trie_tree->trie_tree, 0);

	// search untill no match is possible, or input is empty

	//bool match_found = false;
	int i = 0;
	int last_partial_match = 0;
	int last_fork = 0;
	int name_matched_at_fork = 0;
	bool found_1_fork = false;
	int node_before_match_having_data = 0;
	int name_before_match_having_data = 0;
	// path is right size and there is data
	// path	// what happens if the item doesn't exist(input is too long)
	// what if I made sure each word matches up with the path?
	for(; i < name->population; i++)
	{
		string* new_name = (string*) name->values[i];
		//printf("name to search for |%s|\n", new_name->c_str());
		// 0 cause prev_node->links are ints, 2 because my_trie_tree->trie_tree are TrieNode2s
		int item_location = searchItemTrieDict2(my_trie_tree->trie_tree, prev_node->links, new_name, 0, 2);
		if(item_location == -1)
		{
			// can't delete an item that doesn't exist
			//printf("neighbors don't exist\n");
			// return the prev_node_id and the ith name		
			// last match was prev_node->value	
			//break;
			printf("can't find it\n");
			return -1;
		}
		else
		{
			//printf("partial match\n");
			TrieNode2* node_found = (TrieNode2*) getItem(my_trie_tree->trie_tree, item_location);
			// test the nodes before the last node for the presence of at least 1 fork
			if(	getPopulation(node_found->links) > 1 &&
				i < name->population - 1)
			{
				//printf("problem\n");
				last_fork = item_location; // case 1: 1 or more forks
				name_matched_at_fork = i;  // case 1: 1 or more forks
				found_1_fork = true;	   // case 1: 1 or more forks
			}
			// didn't recored the last node before last_partial_match that had data(so that node would be deleted by accident)
			if( ((TrieNode2*) getItem(my_trie_tree->trie_tree, item_location))->state_id > -1 &&
				 i < name->population - 1)
			{
				// case 1.1, 2.1: path length >= 1 and we are before the last node in the path
				node_before_match_having_data = item_location;
				name_before_match_having_data = i;
			}
			// if my_trie_tree[was_item_found].links.population > 1
				// last_fork = was_item_found
			// input is too short or same sequence as dict
			if(i == name->population - 1)
			{
				// last match was node_found->value
				// case 1, 2: end of path with 0 or more forks
				last_partial_match = item_location;
				//match_found = true;
				break;
			}
			else
			{
				//printf("more words to go %i\n", was_item_found);
				prev_node = (TrieNode2*) getItem(my_trie_tree->trie_tree, item_location);
			}
		}
	}

	// prove node at last_partial_match actually has data
	// if last node has a state id > -1
		// we have found a match
	// printf("after matching\n");
	// printf("%i\n", last_partial_match);
	// printf("%s\n", ( (string*)  ((TrieNode2*) getItem(my_trie_tree->trie_tree, last_partial_match))->value)->c_str() );
	// printf("%i\n",   ((TrieNode2*) getItem(my_trie_tree->trie_tree, last_partial_match))->state_id );
	
	the pre lower bound is the fork
	another pre lower bound is the second to last node with data
	
	// path has 0 forks but ends at an internal node that is a fork
	if( ((TrieNode2*) getItem(my_trie_tree->trie_tree, last_partial_match))->state_id > -1 )
	{
		// case 2: 0 forks
		if(!found_1_fork)
		{
			// printf("no fork\n");
			int population = getPopulation(((TrieNode2*) getItem(my_trie_tree->trie_tree, last_partial_match))->links);

			// path has 0 forks and ends at an internal node(return id)

			if(population > 0)
			{
				return ((TrieNode2*) getItem(my_trie_tree->trie_tree, last_partial_match))->state_id;

			}
			// path has 0 forks and ends at a leaf node(delete all nodes and return id)

			else if(population == 0)
			{
				// printf("pop = 0\n");
				// passes(only for paths > 1)
				// enters for paths = 1 but fails
				// path from root to last_partial_match can be deleted
				// cutLinkToFirstNodeInPath(TrieTree* my_trie_tree,  int start_node, int ith_string_in_input)
				// need lower_bound to be changed by cutLinkToFirstNodeInPath
				int lower_bound = 0;
				int* lower_bound_ptr = &lower_bound;

				printf("%i, %i\n", node_before_match_having_data, name_before_match_having_data);
				// node_before_match_having_data is int start_node
				// name_before_match_having_data is int ith_string_in_input
				cutLinkToFirstNodeInPath(	my_trie_tree, name,
											lower_bound_ptr,
											node_before_match_having_data,
											name_before_match_having_data wrong );

				Vector* nodes_to_delete = initVector();
				int tracker = lower_bound;
				// the id's in the earlier part of the path < the ids in the later part of the path
				// path length == 1
				if(tracker == last_partial_match)
				{
					Vector* collected_nodes_to_delete = initVector();

					//printf("first node matching is the last one matching\n");
					appendNode(collected_nodes_to_delete, tracker);

					nodes_to_delete = collected_nodes_to_delete;

				}
				// path length > 1
				else if(tracker < last_partial_match)
				{
					Vector* collected_nodes_to_delete = initVector();

					appendNodes(	collected_nodes_to_delete,
									tracker,
									last_partial_match,
									my_trie_tree);

					nodes_to_delete = collected_nodes_to_delete;


				}
				
				//Print(nodes_to_delete);
				// delete the collected nodes

				int state_id_to_delete = deleteNodes(nodes_to_delete, my_trie_tree);

				return state_id_to_delete;


			}
		}
		///////////////
		else // deleting the path coming after a fork(path length > 1)
		{
			int population = getPopulation(((TrieNode2*) getItem(my_trie_tree->trie_tree, last_partial_match))->links);
			// path has n forks and ends at an internal node node(return id)
			if(population > 0)
			{
				return ((TrieNode2*) getItem(my_trie_tree->trie_tree, last_partial_match))->state_id;

			}

			// path has n forks and ends at a leaf node(delete unique path part and return id)
			else if(population == 0)
			{
				// delete the first link and then get the nodes to delete
				int pre_lower_bound;
				///////////
				// have to check if the fork_id < second to last node with data
				// if fork_id is smaller
					// cut link at second to last node with data
					// pre_lower_bound = second to last node with data
				// else
					// cut link at fork_id
					// pre_lower_bound = fork_id
				//////////

				// fork

				// get the lower bound
				int lower_bound = searchItemTrieDict2(
					my_trie_tree->trie_tree,
					((TrieNode2*) getItem(my_trie_tree->trie_tree, last_fork))->links,
					(string*) name->values[name_matched_at_fork + 1],
					0,
					2);

				// delete connection from fork to lower bound
				TrieNode2* fork_node = (TrieNode2*) getItem(my_trie_tree->trie_tree, last_fork);

				// lower_bound happens to equal the value of the integer being deleted
				// delete the TrieNode2 object
				// call shiftBack from vector struct to reposition the elements
				deleteItem(fork_node->links, lower_bound);

				// get the nodes to delete
				// traverse from lower_bound to last_partial_match

				Vector* nodes_to_delete = initVector();
				int tracker = lower_bound;
				// the id's in the earlier part of the path < the ids in the later part of the path
				while(tracker < last_partial_match)
				{
					int* tracker_ptr = (int*) malloc(sizeof(int));
					*tracker_ptr = tracker;

					// collect the ids of the first link(there will be no forks here)
					append(nodes_to_delete, tracker_ptr);

					tracker = updateId(my_trie_tree, tracker);
					if(tracker == last_partial_match)
					{
						append(nodes_to_delete, tracker_ptr);
						break;
					}
				}

				// delete the collected nodes
				int state_id_to_delete = -1;
				for(int i = 0; i < nodes_to_delete->population; i++)
				{
					int state_id = *((int*) getItem(nodes_to_delete, i));
					
					if(i == nodes_to_delete->population - 1)
					{
						state_id_to_delete = state_id;
					}


					deleteTrieNode2(  (TrieNode2*) getItem(my_trie_tree->trie_tree, state_id)  );

				}

				return state_id_to_delete;
			}

			
		}
		//////////////

		
	}
	
		// how to change prev and current to integers
		
		erase link to current from prev
		prev = current
		update current

		loop until current == last_partial_match (graph is automatically topologically sorted and the id's are increasing, therefore the first name part has an id < the id of the second name part)
		erase link to current from prev
		erase datat in slot at prev

		prev = current
		update current
		


	*/
	return -1;

}

void printTrie(TrieTree* my_trie_tree)
{
	printf("printing ordered dict trie\n");
	// loop through all elements
		// loop thorugh all attributes
	for(int i = 0; i < getPopulation(my_trie_tree->trie_tree); i++)
	{

		TrieNode2* node = (TrieNode2*) getItem(my_trie_tree->trie_tree, i);
		if(node != NULL)
		{
			//printf("printing array\n");

			printf("%i |%c| word %i state %i\n", i, node->my_value, node->word_counterpart, node->state_id);
			printf("links\n");
			for(int j = 0; j < getPopulation(node->chars_from_edges); j++)
			{
				int k = *((int*) getItem(node->chars_from_edges, j));
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

void printWordTrie(TrieTree* my_trie_tree)
{
	printf("printing ordered dict word tree\n");
	// loop through all elements
		// loop thorugh all attributes
	for(int i = 0; i < getPopulation(my_trie_tree->word_tree); i++)
	{

		TrieNode2* node = (TrieNode2*) getItem(my_trie_tree->word_tree, i);
		//("node %x\n", node);
		if(node != NULL)
		{
			//printf("printing array\n");

			//printf("%i |%c| %i %i\n", i, node->my_value, node->start_of_word, node->state_id);
			printf("%i |", i);
			//printf("%x %i\n", node->word_letters, getPopulation(node->word_letters));
			//printf("here\n");
			//Print(node->word_letters);
			//printf("done\n");
			if(node->word_letters != NULL)
			{
				for(int j = 0; j < getPopulation(node->word_letters); j++)
				{
					int k = *((int*) getItem(node->word_letters, j));
					//printf("k %i\n", k);
					TrieNode2* char_node = (TrieNode2*) getItem(my_trie_tree->trie_tree, k);
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
				printf("%i\n", getPopulation(node->links));
				for(int l = 0; l < getPopulation(node->links); l++)
				{
					int k = *((int*) getItem(node->links, l));
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
		push to stack
	else if there is no letter found(not able to find a successive letter)
		pop from top
		choose the next edge from penultimate to push or pop again if can't
		indent level -- if the item poped is the start of a word

*/
string collectWord(TrieTree* my_trie_tree, Vector* node_id_stack)
{
	int size = getPopulation(node_id_stack);

	int node_id_tracker = *((int*) getItem(node_id_stack, size - 1) );
	//printf("here\n");
	//printf("%i\n", node_id_tracker);
	TrieNode2* tracker_node = (TrieNode2*) getItem(my_trie_tree->trie_tree, node_id_tracker);
	string word;
	// if size == 1

	// the top node should not be the start of a word
	while(size > 1 && (!tracker_node->start_of_word))
	{
		//printf("collecting %i\n", size);
		char letter = tracker_node->my_value;
		//printf("|%s|\n", letter.c_str());
		word = letter + word;
		size--;
		if(size >= 0)
		{
			node_id_tracker = *((int*) getItem(node_id_stack, size - 1) );
			tracker_node = (TrieNode2*) getItem(my_trie_tree->trie_tree, node_id_tracker);

		}
	}
	// don't want the root word
	if(size > 1)
	{
		char letter = tracker_node->my_value;
		word = letter + word;

	}
	return word;
}
void printTrieWords(TrieTree* my_trie_tree)
{
	// printing the trie tree using the word tree
	// node_id_stack
	Vector* node_id_stack = initVector();
	// ith_edge_stack
	Vector* ith_edge_stack = initVector();
	// indent_level
	int indent_level = 0;
	// put root on stack
	// root shouldn't be printed out but it's not causing problems
	int start_ith_edge = 0;
	int* start_ith_edge_ptr = (int*) malloc(sizeof(int));
	*start_ith_edge_ptr = start_ith_edge;
	append(ith_edge_stack, start_ith_edge_ptr);


	int start_node_id = 0;
	int* start_node_id_ptr = (int*) malloc(sizeof(int));
	*start_node_id_ptr = start_node_id;
	append(node_id_stack, start_node_id_ptr);

	// get next node after root
	int top_node_id = *((int*) getItem(node_id_stack, 0));
	TrieNode2* top_node = (TrieNode2*) getItem(my_trie_tree->word_tree, top_node_id);
	if(getPopulation(top_node->links) == 0)
	{
		printf("empty graph\n");
		return;
	}
	int top_ith_edge = *((int*) getItem(ith_edge_stack, 0));
	//int next_letter = *((int*) getItem(top_node->chars_from_edges, top_ith_edge) );
	//Print(top_node->links);
	int next_edge = *((int*) getItem(top_node->links, top_ith_edge) );//top_node->char_links[next_letter];

	//printf("next edge %i\n", next_edge);
	int loop_count = 0;
	TrieNode2* next_letter_node;// = (TrieNode2*) getItem(my_trie_tree->trie_tree, next_edge);

	int* first_node_id_ptr = (int*) malloc(sizeof(int));
	*first_node_id_ptr = next_edge;
	append(node_id_stack, first_node_id_ptr);


	int* first_ith_edge_ptr = (int*) malloc(sizeof(int));
	*first_ith_edge_ptr = 0;
	append(ith_edge_stack, first_ith_edge_ptr);
	indent_level += 3;
	//indent_level += 3;
	// push first node to stack
	// update indent_leve
	//Print(ith_edge_stack);
	//Print(node_id_stack);
	// status of stacks
	// 0, next_edge(first node)
	// 0, 0
	//printf("here\n");
	// first letter is the first letter of the first sequence
	while(/*loop_count < 6 &&  */getPopulation(node_id_stack) > 0)
	{
		//printf("node id %i\n", next_edge);

		// use the node id for tracking, not the node pointer

		// first round this is the first child from root
		next_letter_node = (TrieNode2*) getItem(my_trie_tree->word_tree, next_edge);
		// process 1 node per round
		//printf("loop %i\n", loop_count);
		//printf("here\n");
 		//printf("node id %i\n", top_node_id);
		//printf("here 2\n");
		//printf("node %i\n\n", next_letter_node);
		
		//Print(ith_edge_stack);
		//Print(node_id_stack);

		// print word
		printf("%s|", makeSpaces(indent_level).c_str());
		for(int j = 0; j < getPopulation(next_letter_node->word_letters); j++)
		{
			int k = *((int*) getItem(next_letter_node->word_letters, j));
			//printf("|%i|", k);

			TrieNode2* char_node = (TrieNode2*) getItem(my_trie_tree->trie_tree, k);

			printf("%c", char_node->my_value);
			if(j == getPopulation(next_letter_node->word_letters) - 1)
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
		if(getPopulation(next_letter_node->links) > 0)
		{
			// find the next edge and add it here
			push(node_id_stack, getNextNode(my_trie_tree, node_id_stack, ith_edge_stack));
			push(ith_edge_stack, 0);
			//printf("after push\n");
			//Print(ith_edge_stack);
			//Print(node_id_stack);
			indent_level += 3;
			next_edge = *((int*) getItem(node_id_stack, getPopulation(node_id_stack) - 1));

		}
		else
		{
			int top_node_id_2 = *((int*) getItem(node_id_stack,
													 getPopulation(node_id_stack) - 1));
			TrieNode2* top_node_2 = (TrieNode2*) getItem(my_trie_tree->word_tree, top_node_id_2);

			// exit when stack is empty or there is a new node to visit
			while(getPopulation(node_id_stack) > 0 /* may simply be here to keep something true */)
			{
				// pop from both stacks
				//printf("before pop\n");
				popItem(ith_edge_stack);
				popItem(node_id_stack);
				//printf("after pop\n");
				//Print(ith_edge_stack);
				//Print(node_id_stack);
				indent_level -= 3;
				if(getPopulation(node_id_stack) == 0)
				{
					break;
				}
				// decriment indent_level
				top_node_id_2 = *((int*) getItem(node_id_stack,
													 getPopulation(node_id_stack) - 1));

				top_node_2 = (TrieNode2*) getItem(my_trie_tree->word_tree, top_node_id_2);

				top_ith_edge = *((int*) getItem(ith_edge_stack, getPopulation(ith_edge_stack) - 1));

				//printf("top node id %i, population %i, top edge %i\n", top_node_id_2, getPopulation(top_node_2->links), top_ith_edge);
				// have to use the edge for the below comparison too
				// if edge at top of stack can be incremented(edge + 1 < node's links length)
				if(top_ith_edge + 1 < getPopulation(top_node_2->links))
				{
					// wrong
					//printf("need to push\n");
					incrementTopInt(ith_edge_stack);

					// push new node(will be next_letter_node) and 0 to stacks
					// increment indent_level

					next_edge = getNextNode(my_trie_tree, node_id_stack, ith_edge_stack);

					push(node_id_stack, next_edge);
					push(ith_edge_stack, 0);
					indent_level += 3;

					break;

				}
			}
			//printf("done with poping\n");
		}
		
		//Print(ith_edge_stack);
		//Print(node_id_stack);
		
		loop_count++;


	}
	
}

void printTrieRecursive(TrieTree* my_trie_tree, int root, string indents)
{

	TrieNode2* node = (TrieNode2*) getItem(my_trie_tree->trie_tree, root);

	string my_string = *((string*) node->value);
	if(node->state_id > -1)
	{
		printf("%s %s -> %i\n\n", indents.c_str(), my_string.c_str(), node->state_id);

	}
	else
	{
		printf("%s %s\n\n", indents.c_str(), my_string.c_str());

	}
	for(int j = 0; j < getPopulation(node->links); j++)
	{
		printTrieRecursive(my_trie_tree, *((int*) getItem(node->links, j)), indents + "  ");
	}

}


