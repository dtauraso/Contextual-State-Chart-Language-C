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
	free(node->value);
	if(deleteAllItems(node->links))
	{
		//printf("erased links\n");
		free(node);
		//node = NULL;
		return true;
	}
	return false;

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
void deleteWord(TrieTree* my_trie_tree, int word_id)
{
	// delete the word object at word_id
}
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

int deleteWords(TrieTree* my_trie_tree, Vector* name /* strings*/)
{



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
	/*
	the pre lower bound is the fork
	another pre lower bound is the second to last node with data
	*/
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
											name_before_match_having_data/* wrong */);

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
		/*
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
		if(node != NULL)
		{
			//printf("printing array\n");

			//printf("%i |%c| %i %i\n", i, node->my_value, node->start_of_word, node->state_id);
			printf("%i |", i);
			//printf("%i\n", node->word_letters);
			for(int j = 0; j < getPopulation(node->word_letters); j++)
			{
				int k = *((int*) getItem(node->word_letters, j));
				TrieNode2* char_node = (TrieNode2*) getItem(my_trie_tree->trie_tree, k);

				//printf("|%i|", k);
				printf("%c", char_node->my_value);
			}
			printf("|\nlinks\n");
			//printf("%i\n", node->links);
			for(int l = 0; l < getPopulation(node->links); l++)
			{
				int k = *((int*) getItem(node->links, l));
				printf("|%i|", k);

			}

			
			printf("\n\n");

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
	/*
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


	int top_node_id = *((int*) getItem(node_id_stack, getPopulation(node_id_stack) - 1));
	TrieNode2* top_node = (TrieNode2*) getItem(my_trie_tree->word_tree, top_node_id);

	// failes here
	int top_ith_edge = *((int*) getItem(ith_edge_stack, getPopulation(ith_edge_stack) - 1));
	//int next_letter = *((int*) getItem(top_node->chars_from_edges, top_ith_edge) );

	int next_edge = *((int*) getItem(top_node->links, top_ith_edge) );//top_node->char_links[next_letter];
	
	int loop_count = 0;
	TrieNode2* next_word_node = (TrieNode2*) getItem(my_trie_tree->trie_tree, next_edge);

	int* first_node_id_ptr = (int*) malloc(sizeof(int));
	*first_node_id_ptr = next_edge;
	append(node_id_stack, start_node_id_ptr);


	int* first_ith_edge_ptr = (int*) malloc(sizeof(int));
	*first_ith_edge_ptr = 0;
	append(ith_edge_stack, start_ith_edge_ptr);
	indent_level += 3;
	//indent_level += 3;
	// push first node to stack
	// update indent_leve
	//Print(ith_edge_stack);
	//Print(node_id_stack);
	// first letter is the first letter of the first sequence
	while(/*loop_count < 20 &&  getPopulation(node_id_stack) > 0)
	{
		next_letter_node = (TrieNode2*) getItem(my_trie_tree->trie_tree, next_edge);
		// process 1 node per round
		//printf("loop %i\n", loop_count);
		//printf("here\n");
 		//printf("node id %i\n", top_node_id);
		//printf("here 2\n");
		//printf("node %i\n\n", next_letter_node->start_of_word);
		/*
		dfs with stack
		get word
		print with indent
		get next word if can
		else
			loop
				pop words off untill stack is empty or find one with more edges
				decrement indent level for each pop

			push new node onto stack
			increment indent level


			
		if(next_letter_node->start_of_word)
		{
			//printf("start collecting\n");
			// traverse nodes from stack in reverse order to collect the string
			// stop collecting when hit the root or a previous start of word
			string word = collectWord(my_trie_tree, node_id_stack);
			if(word.size() > 0)
			{


				printf("%s|%s|", makeSpaces(indent_level).c_str(), word.c_str());
				if(top_node->state_id > -1)
				{
					printf(" -> %i\n", top_node->state_id);
				}
				else
				{
					printf("\n");
				}
				//indent_level += 3;

			}
			// print out the string with indents


			


		}
		//printf("%c %i\n", next_letter_node->my_value, next_letter_node->start_of_word);

		if(next_letter_node->start_of_word)
		{
			//if()
			printf("increment indent\n");
			indent_level += 3;

		}
		// push(node_id_stack, next_edge)
		// push(ith_edge_stack, 0)
		// how to know when to stop? doesn't need to stop here
		int start_node_id = next_edge;
		int* start_node_id_ptr = (int*) malloc(sizeof(int));
		*start_node_id_ptr = start_node_id;
		append(node_id_stack, start_node_id_ptr);
		
		int start_ith_edge = 0;
		int* start_ith_edge_ptr = (int*) malloc(sizeof(int));
		*start_ith_edge_ptr = start_ith_edge;
		append(ith_edge_stack, start_ith_edge_ptr);
		// update some more things so next_edge is ready for start of loop
		top_node_id = *((int*) getItem(node_id_stack, getPopulation(node_id_stack) - 1));
		top_node = (TrieNode2*) getItem(my_trie_tree->trie_tree, top_node_id);


		top_ith_edge = *((int*) getItem(ith_edge_stack, getPopulation(ith_edge_stack) - 1));

		// 
		//printf("# of edges %i\n", getPopulation(top_node->chars_from_edges));
		// only get the next item if there is an edge
		// if there are no edges
			// don't know
		if(getPopulation(top_node->chars_from_edges) > 0)
		{
			
			next_letter = *((int*) getItem(top_node->chars_from_edges, top_ith_edge) );
			// at some point we try to get to a node that doesn't exist
			//printf("next letter %i\n", next_letter);
			next_edge = top_node->char_links[next_letter];
			//printf("next edge %i\n", next_edge);

			next_letter_node = (TrieNode2*) getItem(my_trie_tree->trie_tree, next_edge);
		}
		else
		{

			// pop and push next one
			string word = collectWord(my_trie_tree, node_id_stack);
			printf("%s|%s|", makeSpaces(indent_level).c_str(), word.c_str());
			if(top_node->state_id > -1)
			{
				printf(" -> %i\n", top_node->state_id);
			}
			else
			{
				printf("\n");
			}
			//indent_level += 3;

			//printf("%s|%s| -> %i\n", makeSpaces(indent_level).c_str(), word.c_str(),
			//	top_node->state_id);

			//printf("pop and push next one\n");

			//Print(ith_edge_stack);
			//Print(node_id_stack);

			/*
			if top node is the start of a word
				indents--
			loop while stack is not empty
				pop
				check if top node is the start of a word
					yes, then indents--
				if we can increment the children of top node
					increment the children of top node
					push new node to the top
					indents++
					break

			currently, the ability to decrement the indents is completely dependent on wether or not the top node has >= 2 children
			because the part I'm looking at has 2 children this happens to word

			have a word tree
				each node has a vector of node ids holding the sequence of the letters
			
			popItem(ith_edge_stack);
			popItem(node_id_stack);
			//printf("decrement indents\n");

					//indent_level -= 3;
			//Print(ith_edge_stack);
			//Print(node_id_stack);
			/*
			top_node_id = *((int*) getItem(node_id_stack, getPopulation(node_id_stack) - 1));
			top_node = (TrieNode2*) getItem(my_trie_tree->trie_tree, top_node_id);
			
			//int top_ith_edge = *((int*) getItem(ith_edge_stack, getPopulation(ith_edge_stack) - 1));
			//printf("incrementing\n");

			// update top edge id
			incrementTopInt(ith_edge_stack);
			//Print(ith_edge_stack);
			int top_ith_edge_x = *((int*) getItem(ith_edge_stack, getPopulation(ith_edge_stack) - 1));

			int top_node_id_x = *((int*) getItem(node_id_stack, getPopulation(node_id_stack) - 1));
			TrieNode2* top_node_x = (TrieNode2*) getItem(my_trie_tree->trie_tree, top_node_id_x);

			//printf("top ith edge %i, %i\n", top_ith_edge_x, getPopulation(top_node_x->chars_from_edges));

			// while top edge id >= top node's edge count
			while(top_ith_edge_x >= getPopulation(top_node_x->chars_from_edges))
			{
				// pop from both stacks
				// get top node
				// update top edge id

				popItem(ith_edge_stack);
				popItem(node_id_stack);
				//printf("stacks\n");
				//Print(ith_edge_stack);
				//Print(node_id_stack);
				if(getPopulation(ith_edge_stack) > 0)
				{
					incrementTopInt(ith_edge_stack);
					//printf("after incrementing\n");
					top_ith_edge_x = *((int*) getItem(ith_edge_stack, getPopulation(ith_edge_stack) - 1));
					top_node_id_x = *((int*) getItem(node_id_stack, getPopulation(node_id_stack) - 1));


					top_node_x = (TrieNode2*) getItem(my_trie_tree->trie_tree, top_node_id_x);

					if(top_node_x != NULL)
					{
						// don't decrement if we are at the last round
						if(top_node_id_x != 0)
						{
							// root may be visited
							if(top_node_x->start_of_word)
							{

								printf("decrement indents %i\n", top_node_id_x);
								//printf("indent_level %i\n", indent_level);

								indent_level -= 3;
								//printf("indent_level %i\n", indent_level);


							}
						}
						

				
					}
					//printf("%x\n", top_node_x);
					//printf("indent level %i\n", indent_level);

				}
				else
				{
					//printf("indent level %i\n", indent_level);
					
					// quit loop when stacks are empty
					//printf("stack is empty\n");
					break;
				}

			}
			if(getPopulation(ith_edge_stack) > 0)
			{
				printf("after iteration\n");
				Print(ith_edge_stack);
				Print(node_id_stack);
				// get the trackers ready for the next loop iteration
				top_ith_edge = *((int*) getItem(ith_edge_stack, getPopulation(ith_edge_stack) - 1));

				top_node_id = *((int*) getItem(node_id_stack, getPopulation(node_id_stack) - 1));
				top_node = (TrieNode2*) getItem(my_trie_tree->trie_tree, top_node_id);

				top_ith_edge = *((int*) getItem(ith_edge_stack, getPopulation(ith_edge_stack) - 1));
				next_letter = *((int*) getItem(top_node->chars_from_edges, top_ith_edge) );

				next_edge = top_node->char_links[next_letter];

				int start_ith_edge = 0;
				int* start_ith_edge_ptr = (int*) malloc(sizeof(int));
				*start_ith_edge_ptr = start_ith_edge;
				append(ith_edge_stack, start_ith_edge_ptr);


				int start_node_id = next_edge;
				int* start_node_id_ptr = (int*) malloc(sizeof(int));
				*start_node_id_ptr = start_node_id;
				append(node_id_stack, start_node_id_ptr);
				Print(ith_edge_stack);
				Print(node_id_stack);
				printf("next edge %i\n", next_edge);
				indent_level += 3;

			}
			// where does this go?
			//indent_level += 3;


		}
		//Print(ith_edge_stack);
		//Print(node_id_stack);
		
		loop_count++;


	}
	*/
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


