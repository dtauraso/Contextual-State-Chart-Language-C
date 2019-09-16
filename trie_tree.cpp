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
	my_node->value_type = 0;
	my_node->state_id = -1;

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

	// add a node called "root"
	// root is not the last word
	insertString(my_trie_tree, "root", -1);

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
		printf("i %i\n", i);
		string* new_name = (string*) name->values[i];
		printf("name to search for |%s|\n", new_name->c_str());
		int item_found_location = searchItemTrieDict2(my_trie_tree->trie_tree, prev_node->links, new_name, 0, 2);
		// if item_found_location == -200 the trie tree doesn't exist
		if(item_found_location < 0)
		{
			printf("i last %i\n", i);
			// saving the location of link insert for the insert function
			int* item_found_location_ptr = (int*) malloc(sizeof(int));
			*item_found_location_ptr = item_found_location;
			append(stack, item_found_location_ptr);

			return stack;
		}
		else
		{
			int* item_found_location_ptr = (int*) malloc(sizeof(int));
			*item_found_location_ptr = item_found_location;
			append(stack, item_found_location_ptr);
			Print(stack);

			// input is too short or same sequence as dict
			if(i == name->population - 1)
			{
				return stack;
			}
			else
			{
				prev_node = (TrieNode2*) getItem(my_trie_tree->trie_tree, item_found_location);
			}
		}
	}
	return stack;
}

void insertString(TrieTree* my_trie_tree, string element, int state_id)
{
	TrieNode2* node = initTrieNode2();

	string* node_string = (string*) malloc(sizeof(string));
	*node_string = element;
	node->value = node_string;
	node->value_type = 1;
	node->state_id = state_id;
	append(my_trie_tree->trie_tree, node);

}
bool insertItem(Vector* container, void* element, int type);

void insertWord(TrieTree* my_trie_tree,
				string* new_number_ptr,
				TrieNode2* node_found2,
				int state_id)
{
	insertString(my_trie_tree, *new_number_ptr, state_id);
	int* i_ptr = (int*) malloc(sizeof(int));
	*i_ptr = getPopulation(my_trie_tree->trie_tree) - 1;
	// can't append, have to insert at the position saved as a negative number
	append(node_found2->links, i_ptr);
}
Vector* insertWords(TrieTree* my_trie_tree, Vector* name /* strings*/)
{
	// composition of stack
	// root, any_matching_strings, location_of_next_insert_location

	/*
	these are only for matching up the words. It's not saying anything if there is a key at the end
	1 match ending with a non-match
	0, 1, -1




	no matches
	0, -1
	0, 0 no edges or 1 edge


	1 perfect match
	0, 1
	0, 2

	0, 0
	0, 1, 0

	0, 1, 3, 4
	0, 2, 4, 5

	0, #*, -number(0, or 1)


	last_match_word_id[0, #]:
		-1, (>=0)

	next_insert_location_for_edges[-#, #]:
	ends in -1 but there are no neighbors to add anything
	if ends in 0 assumes there was a match with 1 item(0 for 1 item is also valid)
	|stack| >= 2:

		0, 0    	0, 1, 0
		stack[|stack| - 1] == 0
			case 1: did match with location 0


			case 2: there are no edges
			go to object and find out if it has 0 or 1 items in its edges
						if there are no edges
							use 0 differently
						go to object at trie[  trie[]   ]

					|trie[ stack[|stack| - 2] ].edges| > 0
		0, -1     	0, 3, -2
		stack[|stack| - 1] < 0
			no matches and have an insert position
			|stack| == 2: 0, -1
				
					
				none of the strings matched
				the stack[0]th object's edge at -(stack[1]) is the next insert position

				first position of string to add == 0

			|stack| >= 2: 0, -1    0, 1, -1         0, 1, 3, -1
				last string matched at position |stack| - 2
				the stack[|stack| - 2]th object's edge at -(stack[|stack| - 1]) is the next insert position

				names[|stack| - 2] so next name is names[0],
												   names[1],
												   names[2]
				same value but used differently in different containers
				last object matched(0, 1, 2)
				first name to add(0, 1, 2)
				should be different kinds of numbers
				last one correclty matched can't be the first one to add
				stack[0], stack[1], stack[2] is last one matched
				names[0], names[1], names[2] is the first one to add
		0, 1 		0, 2, 4, 5
		stack[|stack| - 1] >= 0
			1 match
			data at stack[len() - 1]
				data
				make new context with key
			no data at stack[len() - 1]
				no data
				put key

	*/
	printf("inserting\n");
	printStrings(name);
	printf("\n");
	// 1 take a sequence of items and add them to an ordered trie dict
	// 2 make some examples of states as input
	
	// input vector comes in
	// possibly modified input vector comes out with all the strings stored as a trie
	// all leaf nodes will have a link to the sate object
	// returns the id of the last node found
	// |path| - 1 = # of strings matched
	// names[# matched + 1] = next string to add to tree
	// a, b, c
	// root, a, b, c
	// root
	Vector* stack = innerSearchForStrings(my_trie_tree, name);
	printf("stack\n");
	Print(stack);
	printf("\n");
	//exit(1);
	if(stack->population >= 2)
	{

		// no matches and have an insert position
		if(*((int*) getItem(stack, stack->population - 1)) < 0)
		{
			// stack: 0, -1
			if(stack->population == 2)
			{
				printf("here 45678\n");
				/*
				none of the strings matched
				the stack[0]th object's edge at -(stack[1]) is the next insert position

				first position of string to add == 0

				*/
				int id_of_last_object_matched = *((int*) getItem(stack, 0));
				TrieNode2* last_node_matched = (TrieNode2*) getItem(my_trie_tree->trie_tree,
																id_of_last_object_matched);
				// insert the node
				// insert the edge from last_node_matched to the new node
				// need to actually insert the string to get the id to insert at edge_position
				// appendString(TrieTree, names[0])
				// id = trie_tree->population - 1
				int edge_position = -1 * (   *((int*) getItem(stack, 1))  );


				// insertEdge(last_node_matched, edge_position, id/* value to be put into edge[edge_position] */)

				// have a tracking id for the last node added for looping
			}
		}
	}










	/*
	// first element in stack is root
	// if only the root was in there, then the next string to add is from pos 0
	int total_words_matched = stack->population - 1;
	int next_string_to_add;
	if(total_words_matched == 0)
	{
		next_string_to_add = 0;
	}
	else if(total_words_matched > 0)
	{
		next_string_to_add = total_words_matched - 1;
	}
	printf("next_string_to_add %i\n", next_string_to_add);
	// last one didn't get reached
	if(next_string_to_add < name->population - 1)
	{
		printf("last one didn't get reached\n");
		// start inserting
		//int start_node = name[name->population - 1];
		// current node is start_node
		int next_string_id = *((int*) getItem(stack, stack->population - 1));
		TrieNode2* current_node = (TrieNode2*) getItem(my_trie_tree->trie_tree, next_string_id);
		// use start_node to get the node to start linking to
		// when inserting the string use -1 for state id unless it's the last word
		for(int i = next_string_id; i < name->population; i++)
		{
			string* new_name = (string*) name->values[i];

			// pass in -1 or the next my_trie_tree->max_state_id

			// need to put the state id into the final node
			if(i < name->population - 1)
			{
				printf("inserting the next ones\n");

				insertWord(my_trie_tree, new_name, current_node, -1);

			}
			else // last word
			{
				printf("inserting the last one\n");
				my_trie_tree->max_state_id++;

				insertWord(my_trie_tree, new_name, current_node, my_trie_tree->max_state_id);
			}
			current_node = (TrieNode2*) getItem(my_trie_tree->trie_tree,
												getPopulation(my_trie_tree->trie_tree) - 1);
 		}
	}
	// last one did get reached
	else if(next_string_to_add == name->population)
	{
		printf("the last one was reached\n");
		int last_item = *((int*) getItem(stack, stack->population - 1));
		// name matches and data
		if( ((TrieNode2*) getItem(my_trie_tree->trie_tree, last_item))->state_id > -1 )
		{
			printf("make new context\n");
			// make a new context and insert it in
			// adding a new node to stack[stack->population - 1]
			TrieNode2* node_found2 = (TrieNode2*) getItem(my_trie_tree->trie_tree, last_item);
			int number_of_neighbors = getPopulation(node_found2->links);

			stringstream s;
			s << number_of_neighbors;
			string new_number;
			s >> new_number;
			string* new_number_ptr = (string*) malloc(sizeof(string));
			*new_number_ptr = new_number;
			//printf("annexing %s\n", new_number_ptr->c_str());
			// need to put the state id into the final node
			// add it as the child of final name
			// last word
			insertWord(my_trie_tree, new_number_ptr, node_found2, 1);
			// append to end of name and return the name
			append(name, new_number_ptr);

		}
		// name matches but no data
		else
		{
			printf("add key to word\n");
			// insert number
			TrieNode2* node_found2 = (TrieNode2*) getItem(my_trie_tree->trie_tree, last_item);
			my_trie_tree->max_state_id++;
			node_found2->state_id = my_trie_tree->max_state_id;

		}
	}
	*/



	/*
	int prev_node_id = 0;
	TrieNode2* prev_node = (TrieNode2*) getItem(my_trie_tree->trie_tree, 0);

	// search untill no match is possible, or input is empty
	// insert untill input runs out
	bool match_found = false;
	int i = 0;
	int last_partial_match = 0;
	for(; i < name->population; i++)
	{
		string* new_name = (string*) name->values[i];
		//printf("name to search for |%s|\n", new_name->c_str());
		int was_item_found = searchItemTrieDict2(my_trie_tree->trie_tree, prev_node->links, new_name, 0, 2);
		if(was_item_found == -1)
		{
			//printf("neighbors don't exist\n");
			// return the prev_node_id and the ith name		
			// last match was prev_node->value
			//printf("can't find it\n");

			break;
		}
		
		else
		{
			//printf("partial match\n");

			// input is too short or same sequence as dict
			if(i == name->population - 1)
			{
				// last match was node_found->value
				last_partial_match = was_item_found;
				match_found = true;
				break;
			}
			else
			{
				//printf("more words to go %i\n", was_item_found);
				prev_node = (TrieNode2*) getItem(my_trie_tree->trie_tree, was_item_found);
			}
		}
	}
	if(((TrieNode2*) getItem(my_trie_tree->trie_tree, last_partial_match))->state_id > -1)
	{
		//printf("here\n");
		// add the number as context
		// last word in name should have already been used

		TrieNode2* node_found2 = (TrieNode2*) getItem(my_trie_tree->trie_tree, last_partial_match);
		int number_of_neighbors = getPopulation(node_found2->links);

		stringstream s;
		s << number_of_neighbors;
		string new_number;
		s >> new_number;
		string* new_number_ptr = (string*) malloc(sizeof(string));
		*new_number_ptr = new_number;
		//printf("annexing %s\n", new_number_ptr->c_str());
		// need to put the state id into the final node
		// add it as the child of final name
		// last word
		insertWord(my_trie_tree, new_number_ptr, node_found2, 1);
		// append to end of name and return the name
		append(name, new_number_ptr);
		
	}
	else // final word matched doesn't link to a node
	{
		TrieNode2* node_found2 = (TrieNode2*) getItem(my_trie_tree->trie_tree, last_partial_match);
		// match and last node is an internal node
		if(	match_found &&
			getPopulation(node_found2->links) > 0)
		{
			my_trie_tree->max_state_id++;
			node_found2->state_id = my_trie_tree->max_state_id;

		}
		else if(!match_found)
		{
			// automaticall handles branching attributed to a non match, a match, and when final word matched doesn't link to a node
			// forces a new subpath to branch off using a copy of child node
			// loop from i to name->population to insert remaining words
			for(; i < name->population; i++)
			{
				string* new_name = (string*) name->values[i];

				// need to put the state id into the final node
				if(i < name->population - 1)
				{
					insertWord(my_trie_tree, new_name, prev_node, 0);

				}
				else // last word
				{
					insertWord(my_trie_tree, new_name, prev_node, 1);
				}
				prev_node = (TrieNode2*) getItem(my_trie_tree->trie_tree,
													getPopulation(my_trie_tree->trie_tree) - 1);
	 		}
		}
		
	}
	*/


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
			string my_string = *((string*) node->value);

			printf("%i %s %i\n", i, my_string.c_str(), node->state_id);
			printf("links\n");
			Print(node->links);

		}
		else
		{
			printf("%i empty\n\n", i);
		}

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
