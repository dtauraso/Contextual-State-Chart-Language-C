#include "state.h"
#include "state_machine.h"
//#include "vector.h"
#include "trie_tree.h"
//#include "jsmn/jsmn.h"
// this file is compiled last?
//struct Vector;
string makeSpaces(int indent_level);

const char* getInput(Tokens* my_tokens);
int getI(Tokens* my_tokens);
TrieTree* initTrieTree();
void insertString(TrieTree* my_trie_tree, string element);
//int getPopulation(Vector* container);

enum data_types{is_list, is_string, is_empty_case};
enum token_types {_primitive, _object, _array, _string};

/*
typedef struct LispNode
{
	void* value;
	struct LispNode* next;

	int count_of_value_items;
	bool value_type;
}*/

/*
typedef struct DynamicState
{
	Vector* start_children;
	Vector* children;
	Vector* next_states;
	Data* value;
	int level_number;
	bool (*function) (void*);
	//remaining items for the asyncronous nfa evaluator state machine

}DynamicState;

typedef struct DynamicMachine
{
	Vector* states_trie; // numeric
	Vector* state_name_trie; // character
	Vector* function_names_trie; // character
	Vector* parent_status_trie; // boolean
	int nth_name_part;
	StateMachine* static_machine;

	// auxiliary data hierarchy for filling up the vectors
	Vector* trie_being_used_to_match;  // trie_being_used_to_match is set to whatever trie vector is being used
	int type; // 0 == int 1 == char, 2 == bool


	vector<string>* state_name_buffer; // for adding, deleting, modifying



}DynamicMachine;
*/
/*
state machine for control flow and variable modification
parser state graph
nfa asyncronious evaluator state graph
api functions

*/
/*
parsing json
DynamicMachine* parsing_engine
int root_of_output_from_parsing_engine


parser
int root_of_parsing_language_engine
DynamicMachine* parsing_engine but only from the parsing language engine

*/
/*
the "Dynamic" part is for manipulating the "state" variables than the state control flow
DynamicState
	Vector* start_children
	Vector* children
	Vector* next_states
	data* value (includes pointer to a dynamic state)
	bool (*function) (void*)
	remaining items for the asyncronous nfa evaluator state machine


DynamicMachine
1 numeric trie of states (Vector* DynamicState)
1 character trie of state name part (Vector* DynamicState)
1 character trie of function names (Vector* DynamicState)
1 numeric trie of parent statuses (Vector* DynamicState)
1 int for tallying the strings forming the state names
1 int* internal_machine_of_operations(child, next states for each state)

getState(name_1, name_2, name_3)
setStateTypeName(name_1, name_2, name_3, value)
link(state_1, state_2)

setChildren(state_1_name, children_state_names)
setNextStates(state_1_name, next_state_names)




use api for getting states collected from json_parser(static machine) into a state machine object(DynamicMachine)
make evaluator from api to run the parser and the langauge parsed
run through the state machine object(DynamicMachine) to parse the language(evaluator)
run the language(same evaluator)

*/
enum internal_states{

	empty,
	_search,

	root_exists,

	get_id_of_expected_location,

	setup,
	midpoint,
	type_of_match_int,
	type_of_match_char,
	type_of_match_bool,

	no_more_matches_are_possible,
	no_match,
	left,
	right,
	full_match,
	partial_match,
	tree_has_too_little_data_for_a_full_match,
	tree_is_incomplete,
	calculate_expected_location
};
/*


input assembly line
	children
		-name
			next
				start_children
		start_children
			next
				children
		children
			next
				next_states
		next_states
			next
				data
		data

setupNeighbors(make_tree_next_states, input_assembly_line,
											name, 					empty, 				empty, 			empty,
											empty, 					empty, 				empty, 			empty);
setupNeighbors(make_tree_next_states, name,
											list_of_strings, 					empty, 				empty, 			empty,
											start_children, 					empty, 				empty, 			empty);

setupNeighbors(make_tree_next_states, start_children,
											list_of_lists_of_strings, 					empty, 				empty, 			empty,
											children, 					empty, 				empty, 			empty);

setupNeighbors(make_tree_next_states, children,
											list_of_lists_of_strings, 					empty, 				empty, 			empty,
											next_states, 					empty, 				empty, 			empty);

setupNeighbors(make_tree_next_states, next_states,
											list_of_lists_of_strings, 					empty, 				empty, 			empty,
											empty, 					empty, 				empty, 			empty);

setupNeighbors(make_tree_next_states, data,
											empty, 					empty, 				empty, 			empty,
											empty, 					empty, 				empty, 			empty);




api
	children
		-search

		-insert
			next
				search, store
			children
				- input_assembly_line
			
		store
		-delete
			next
				search, erase
		erase
*/
/*
typedef struct Search
{
	int start;
	int end;
	int mid;
	int comparison_type;
	Vector* container;

}Search;
*/

Search* initSearch(Vector* container, int comparison_type)
{
	Search* my_search = (Search*) malloc(sizeof(Search));
	my_search->start = 0;
	my_search->end = 0;
	my_search->comparison_type = comparison_type;
	my_search->container = container;
	return my_search;
}

/*
typedef struct Insert
{
	struct Search* my_search;
}Insert;
*/

Insert* initInsert(Vector* container, int comparison_type)
{
	Insert* my_insert = (Insert*) malloc(sizeof(Insert));
	my_insert->my_search = initSearch(container, comparison_type);
	return my_insert;
}

/*
typedef struct Delete
{
	struct Search* my_search;
}Delete;
*/
Delete* initDelete(Vector* container, int comparison_type)
{
	Delete* my_delete = (Delete*) malloc(sizeof(Delete));
	my_delete->my_search = initSearch(container, comparison_type);
	return my_delete;

}
/*
typedef struct ExtendedState
{
	string next_context;
	map<string, int>* next_next_contexts;
	int id;
}ExtendedState;
*/
ExtendedState* initExtendedState()
{
	ExtendedState* new_extended_state = (ExtendedState*) malloc(sizeof(ExtendedState));
	new_extended_state->data = initVector();
	new_extended_state->next_contexts = new map<string, int>();
	new_extended_state->id = 0;
	new_extended_state->type = 0;
	return new_extended_state;
}
/*
ExtendedState* insertString(ExtendedState* node, string value)
{
	// insert
	string* new_string = (string*) malloc(sizeof(string));
	*new_string = value;
	node->data = new_string;
	node->type = 0;
	return node;
	// set the type of the void*
}*/
ExtendedState* insertDynamicState(ExtendedState* node, DynamicState* value)
{
	// insert
	node->data = value;
	node->type = 1;
	return node;
	// set the type of the void*

}
/*
typedef struct OrderedDict
{
	// ordered dictioanry where the dict part is implemented using a trie
	Vector* items;
	multimap<string, ExtendedState*>* dict;
}OrderedDict;
*/
OrderedDict* initOrderedDict()
{
	OrderedDict* new_dict = (OrderedDict*) malloc(sizeof(OrderedDict));
	new_dict->items = initVector();
	new_dict->dict = new multimap<string, ExtendedState*>();
	multimap<string, ExtendedState*>::iterator it = new_dict->dict->begin();
	new_dict->root = initExtendedState();
	// insert the string
	/*
	new_dict->root = insertString(new_dict->root, "root");

	new_dict->dict->insert(it, pair<string, ExtendedState*>("root", new_dict->root));
	new_dict->max_id = 0;
	*/
	return new_dict;
}
OrderedDict* insertState(OrderedDict* my_ordered_dict, Vector* strings)
{
	// insert the strings into the dict
	// don't need to generate extra strings cause these are only for the neighbor states

	return NULL;
}

DynamicState* initDynamicState(	Vector* name, // strings
								Vector* start_children,  // array of strings
								Vector* children, // array of strings
								Vector* next_states, // array of strings
								Data* value)
{
	DynamicState* my_dynamic_state = (DynamicState*) malloc(sizeof(DynamicState));
	my_dynamic_state->name = name;
	my_dynamic_state->start_children = start_children;
	my_dynamic_state->children = children;
	my_dynamic_state->next_states = next_states;
	my_dynamic_state->value = value;
	my_dynamic_state->level_number = 0;
	my_dynamic_state->function = NULL;
	my_dynamic_state->parent_status = false;
	return my_dynamic_state;
}

MapNode* initMapNode()
{
	MapNode* my_map_node = (MapNode*) malloc(sizeof(MapNode));
	//my_map_node->string_1 = new set<string>();
	//my_map_node->states = new map<string, struct DynamicState*>();
	//my_map_node->state = NULL;
	//my_map_node->state_map_is_empty = false;
	my_map_node->current_name_part = "";
	my_map_node->next_name_part_states_s = new map<string, DynamicState*>();

	return my_map_node;
}

DynamicMachine* initDynamicMachine(StateMachine* my_machine)
{
	/*

		typedef struct DynamicMachine
		{
			Vector* states_trie; // numeric
			Vector* state_name_trie; // character
			Vector* function_names_trie; // character
			Vector* parent_status_trie; // boolean
			int nth_name_part;
			StateMachine* internal_machine_of_api;

		}DynamicMachine;
	*/
	DynamicMachine* my_dynamic_machine = (DynamicMachine*) malloc(sizeof(DynamicMachine));

	my_dynamic_machine->static_machine = my_machine;

	// auxiliary data hierarchy for filling up the vectors
	my_dynamic_machine->trie_names = new map<string, MapNode*>();

	// insert root -> mapnode
	map<string, MapNode*>::iterator it = my_dynamic_machine->trie_names->begin();
	my_dynamic_machine->trie_names->insert(it,
						pair<string, MapNode*>("root", initMapNode()));

	// buffers for adding, deleting, modifying
	my_dynamic_machine->name = initVector(); // strings
	my_dynamic_machine->start_children = initVector();  // array of strings
	my_dynamic_machine->children = initVector(); // array of strings
	my_dynamic_machine->next_states = initVector(); // array of strings
	my_dynamic_machine->value = makeDataInt(0);

	my_dynamic_machine->trie_tree_dict = initTrieTree();
	//
	my_dynamic_machine->my_search = NULL;
	my_dynamic_machine->my_insert = NULL;
	my_dynamic_machine->my_delete = NULL;

	return my_dynamic_machine;
}


void printArraysOfStrings(Vector* arrays_of_strings, int indent_level)
{
	if(arrays_of_strings != NULL)
	{
		for(int i = 0; i < arrays_of_strings->population; i++)
		{
			printf("%s", makeSpaces(indent_level).c_str());

			Vector* array_of_strings = (Vector*) arrays_of_strings->values[i];
			for(int j = 0; j < array_of_strings->population; j++)
			{
				string* my_string = (string*) array_of_strings->values[j];
				printf("%s, ", my_string->c_str());
			}
			printf("\n");
		}
	}
	
}
void printArrayOfStrings(Vector* array_of_strings, int indent_level)
{
	if(array_of_strings != NULL)
	{
		printf("%s", makeSpaces(indent_level).c_str());

		for(int i = 0; i < array_of_strings->population; i++)
		{
			string* my_string = (string*) array_of_strings->values[i];
			printf("%s, ", my_string->c_str());
		}
		printf("\n");
	}
	
}
void printState(DynamicState* my_state, int indent_level)
{
	printf("%sname\n", makeSpaces(indent_level).c_str());
	printArrayOfStrings(my_state->name, indent_level + 1);
	printf("%sstart children\n", makeSpaces(indent_level).c_str());

	printArraysOfStrings(my_state->start_children, indent_level + 1);
	printf("%schildren\n", makeSpaces(indent_level).c_str());

	printArraysOfStrings(my_state->children, indent_level + 1);
	printf("%snext states\n", makeSpaces(indent_level).c_str());

	printArraysOfStrings(my_state->next_states, indent_level + 1);
	printf("%sdata\n", makeSpaces(indent_level).c_str());

	printData(my_state->value, indent_level + 1);
}
// functions for makeTreeStateMachine
int computeIndex(int offset, int state_name)
{

	// 8 is the child count(4) + neighbor count(4)
	return offset + (8 * state_name);
}
void setupNeighbors( int* next_states, int state,
										int child_0, int child_1, 	int child_2, 	int child_3,
										int next_0, 	int next_1, 	int next_2, 	int next_3)
{
		// children
		next_states[computeIndex(0, state)] 					= child_0;
		next_states[computeIndex(1, state)] 					= child_1;
		next_states[computeIndex(2, state)] 					= child_2;
		next_states[computeIndex(3, state)] 					= child_3;

		// nexts
		next_states[computeIndex(4, state)] 					= next_0;
		next_states[computeIndex(5, state)] 					= next_1;
		next_states[computeIndex(6, state)] 					= next_2;
		next_states[computeIndex(7, state)] 					= next_3;

}
bool Empty(void* pointer)
{
	return true;
}

StateMachine* setupMachine(int start_state, int end_state)
{
	
		// contextual state chart
		// each state name is a contextual state
		// the state chart is the groups of states per level
		int number_of_states = 18;
		int neighbor_count = 4;
		int children_count = 4;
		int number_of_next_states = number_of_states * (children_count + neighbor_count);

		vector<string>* make_tree_state_names_strings = new vector<string>(number_of_states);

		vector<string>* function_names = new vector<string>(number_of_states);

		function_names->resize(number_of_states);
		int* parent_status = (int*) malloc(sizeof(int) * number_of_states);
		parent_status[empty]											= false;
		parent_status[_search]											= true;




		make_tree_state_names_strings->at(empty) 						= "empty";
		make_tree_state_names_strings->at(_search)						= "_search";




		function_names->at(empty) 										= "true";
		function_names->at(_search)										= "true";

		

		int* make_tree_next_states = (int*) malloc(sizeof(int) * number_of_next_states);

		// may take this out
		// empty field
		setupNeighbors(make_tree_next_states, empty,

													empty, 										empty, 							empty, 				empty, 			
													empty, 										empty, 							empty, 				empty);
		// level 1
		// search
		setupNeighbors(make_tree_next_states, _search,

													root_exists, 										empty, 							empty, 				empty,
													empty, 										empty, 							empty, 				empty);

		return stateMachine2(make_tree_next_states,
							/*size*/ number_of_next_states,
							/*max_neghbors*/ neighbor_count,
							make_tree_state_names_strings,
							number_of_states,
							parent_status,
							function_names,
							start_state,
							end_state);

}
/*
typedef struct DynamicState
{
	Vector* start_children;
	Vector* children;
	Vector* next_states;
	Data* value;
	bool (*function) (void*);  set this directly
	//remaining items for the asyncronous nfa evaluator state machine

}DynamicState;
*/

void printStateTrie(DynamicMachine* my_dynamic_machine, string root, int indent_level)
{
	/*
		get the state if exists
			print state
		go through the neighbors in the nested map
		printStateTrie(neighbor string in nested map)
	*/
	//printf("printStateTrie\n");
	if(my_dynamic_machine != NULL)
	{
		if(root.size() > 0)
		{
			//printf("not null\n");
			// map<string, MapNode*>* trie_tree_dict
			map<string, MapNode*>::iterator it = my_dynamic_machine->trie_names->find(root);
			if(	it != my_dynamic_machine->trie_names->end() )
			{
				//printf("item exists\n");
				MapNode* node = it->second;
				if(node->current_name_part.size() > 0)
				{
					map<string, DynamicState*>::iterator it2 = node->next_name_part_states_s->find(node->current_name_part);
					DynamicState* state = it2->second;

					//printf("%s\n", node->current_name_part.c_str());
					printf("%s%s\n", makeSpaces(indent_level).c_str(), node->current_name_part.c_str());
					printState(state, indent_level);

				}
				else
				{
					//printf("none\n");
				}
				for(map<string, DynamicState*>::iterator it = node->next_name_part_states_s->begin();
					it != node->next_name_part_states_s->end();
					it++
					)
				{
					//printf("%s\n", it->first.c_str());
					printStateTrie(my_dynamic_machine,
						it->first,
						indent_level + 2);
				}

				
			}
		}
		
	}
}


// api's, not state functions
// for testing and using
// entrypoint to building the dynamic state machine
TrieTree* insertState1(
							TrieTree* my_trie_tree,
							Vector* name, // strings
							Vector* start_children,  // array of strings
							Vector* children, // array of strings
							Vector* next_states, // array of strings
							Data* value) // primitive
{
	// call machine to run path A to N with the state name in the buffer
	//StateMachine* my_machine = setupMachine(_search, empty);
	//printf("got here\n");
	// need to make a different StateMachine constructor to make the start and end states be parameters
	//DynamicMachine* my_dynamic_machine = initDynamicMachine(my_machine);
	// put the parameters into the my_dynamic_machine buffers
	/*

		string current_name_part; // first one is first state
		map<string, struct DynamicState*>* next_name_part_states_s
		map<string, MapNode*>* trie_names

	*/

	/*
	MapNode* my_root = my_dynamic_machine->trie_names->find("root").second;

	map<string, DynamicState*>::iterator it2 = my_root->next_name_part_states_s->begin();

	my_map_node->next_name_part_states_s->insert(it2,
						pair<string, DynamicState*>("root", NULL));
	*/



	// 1 take a sequence of items and add them to an ordered trie dict
	// 2 make some examples of states as input
	//printf("testing sorted\n");
	//testSorted();
	//exit(1);
	//TrieTree* my_trie_tree = initTrieTree();

	// input vector comes in
	// possibly modified input vector comes out with all the strings stored as a trie
	// all leaf nodes will have a link to the sate object
	int prev_node_id = 0;
	TrieNode2* prev_node = (TrieNode2*) getItem(my_trie_tree->trie_tree, 0);

	//printf("made trie tree\n");
	// make a search function this uses this(copy, paste, delete)
	for(int i = 0; i < name->population; i++)
	{
		string* new_name = (string*) name->values[i];
		printf("%s\n", new_name->c_str());
		// searching the int edges then the ith TrieNode* element for the string
		// 0 means int, 2 means TrieNode2*
		Match* was_item_found = searchItemTrieDict(my_trie_tree->trie_tree, prev_node->sorted_link_indecies, new_name, 0, 2);
		if(was_item_found == NULL)
		{
			printf("neighbors don't exist\n");
			// add item
			insertString(my_trie_tree, *new_name);
			int* i_ptr = (int*) malloc(sizeof(int));
			*i_ptr = getPopulation(my_trie_tree->trie_tree) - 1;
			append(prev_node->links, i_ptr);
			// 0 means int
			insertItem(prev_node->sorted_link_indecies, i_ptr, 0);

			//printf("added item\n");
			prev_node = (TrieNode2*) getItem(my_trie_tree->trie_tree, *i_ptr);

		}
		// separated from case 1 to prevent segfault if evaluation isn't a short circuit
		else if(!was_item_found->exists)
		{
			printf("has neighbors but item doesn't exists\n");
			// add item
			insertString(my_trie_tree, *new_name);
			int* i_ptr = (int*) malloc(sizeof(int));
			*i_ptr = getPopulation(my_trie_tree->trie_tree) - 1;
			append(prev_node->links, i_ptr);
			// 0 means int
			insertItem(prev_node->sorted_link_indecies, i_ptr, 0);

			//printf("added item 2\n");
			prev_node = (TrieNode2*) getItem(my_trie_tree->trie_tree, *i_ptr);

		}
		// case 3 (may reduce to case 2)
		else if(was_item_found->exists)
		{
			printf("partial match\n");

			TrieNode2* node_found = (TrieNode2*) getItem(my_trie_tree->trie_tree, was_item_found->index);
			int number_of_neighbors = getPopulation(node_found->links);
			printf("number_of_neighbors %i\n", number_of_neighbors);
			// input is too short or same sequence as dict
			if(i == name->population - 1)
			{
				// it being the last work doesn't mean we will always add a new context to it
				printf("at last word\n");
				// need to make new branch to enforce the uniqueness of inserting states
				// need a number relative to the final name's children
				// get cound of final name's neighbors
				printf("total count of neighbors %i\n", number_of_neighbors);
				// don't make new context for a subpath match
				// make a new context only if the current node(node_found) already has a state
				
				// convert the int to string
				stringstream s;
				s << number_of_neighbors;
				string new_number;
				s >> new_number;
				string* new_number_ptr = (string*) malloc(sizeof(string));
				*new_number_ptr = new_number;
				printf("annexing %s\n", new_number_ptr->c_str());

				// add it as the child of final name
				insertString(my_trie_tree, *new_number_ptr);
				int* i_ptr = (int*) malloc(sizeof(int));
				*i_ptr = getPopulation(my_trie_tree->trie_tree) - 1;
				append(node_found->links, i_ptr);
				insertItem(node_found->sorted_link_indecies, i_ptr, 0);
				// add it as the next node in vector name
			
				
			}
			// input is too long( this may already be addressed by the second case)
			else if(number_of_neighbors == 0 && i < name->population - 1)
			{
				printf("can't match anymore\n");
			}
			
			else
			{
				printf("more words to go %i\n", was_item_found->index);
				prev_node = (TrieNode2*) getItem(my_trie_tree->trie_tree, was_item_found->index);
				//printf("next node to match %s\n", ((string*) prev_node->value )->c_str() );
			}
			//exit(1);
		}
		//printTrie(my_trie_tree);

		// void* findItem(Vector* container, void* element, int type);

		// need it to use the sorted links to find the items in the trie tree
		//TrieNode2* prev_node_neighbors = findItem(prev_node->sorted_link_indecies, new_name, 1)
	}
	return my_trie_tree;
	//exit(1);
	/*
	OrderedDict* my_ordered_dict = initOrderedDict();
	my_ordered_dict->items = name;

	//string prev_word = "root";
	ExtendedState* prev_node = my_ordered_dict->root;
	string prev_word = *((string*) prev_node->data);
	printf("root |%s|\n", prev_word.c_str());
	//exit(1);
	// getting the next part from root -> next
	// assume root-> (next, root_id) already exists
	map<string, ExtendedState*>::iterator it5 = my_dynamic_machine->dict->find(prev_word);

	// assume root was inserted from the constructor
	printf("size %i\n", name->population);
	// because all links are enumerated the duplicate entries can be considered unique
	for(int i = 0; i < name->population; i++)
	{
		string new_name =  *((string*) name->values[i]);

		// for the first round this is the root node
		ExtendedState* prev_node = it5->second;
		int prev_id = it5->second->id;

		// validating the prev_word -> new_name link
		// use (string, int) map to check for existing links
		map<string, int>::iterator it6 = prev_node->next_contexts->find(new_name);
		// new_name link already exists
		// any links that exist will have a corresponding entry in the multimap
		if(it6 != prev_node->next_contexts_end())
		{
			// need to use the edge to get the item so we can link from it
			// will need to use equal range and then do a linear search
			// if there are too many duplicate entries then search will be O(n^2)
			if()
			{
				// the entire state name already exists
				if(i == name->population - 1)
				{
					// make a new link with an object
				}
				else  // only part of the state name already exists
				{
					// update trackers to get to the next one
				}
			}
			
		}
		else  // new_name link doesn't exist
		{
				// entire state name doesn't exist
				if(i == name->population - 1)
				{
					// make a new link with an object
					my_dynamic_machine->dict->max_id++;
					int new_id = my_dynamic_machine->dict->max_id;

					ExtendedState* new_node = initExtendedState();
					new_node->id = new_id;
					new_node->data = initDynamicState(	name,
														start_children,
														children,
														next_states,
														value);
					// add to multimap
					multimap<string, ExtendedState*>::iterator it7 = my_dynamic_machine->dict->begin();
					my_dynamic_machine->dict->insert(it7,
						pair<string, ExtendedState*>(new_name, new_node));
					// add an edge from the map to the multimap
					map<string, int>::iterator it8 = prev_node->next_contexts->begin();
					prev_node->next_contexts->insert(it8,
						pair<string, int>(new_name, new_id));
					// store data in prev_node
					// make a new id
					// save the new id into the ExtendedState object from prev_word
				}
				else // part of the state name doesn't exist
				{
					// make a link
					// update trackers to new link
				}
		}
		
		// is the state name part of ?
		// string is the edge to map<string, MapNode*>
		// is the edge actually there?
			// is the edge -> MapNode* there?
		//map<string, DynamicState*>::iterator it6 = prev_node->next_name_part_states_s->find(new_name);

		
		if(it6 != prev_node->next_name_part_states_s->end())
		{
			// doesn't allow duplicates
			// if multimap doesn't allow for the duplicates to be enumerated
			map<string, MapNode*>::iterator it7 = my_dynamic_machine->trie_names->find(new_name);
			if(it7 != my_dynamic_machine->trie_names->end())
			{
				printf("item already exists\n");
				// create new context
				// context_a, context_b(state)
				//map<string, DynamicState*>::iterator it = my_node->next_name_part_states_s->begin();

				// last state name part exists, ie, state is already in the trie
				if(i == name->population - 1)
				{
					
					DynamicState* new_state = initDynamicState(	name,
															start_children,
															children,
															next_states,
															value);
					my_node->next_name_part_states_s->insert(it,
						pair<string, DynamicState*>(new_name, new_state));
					
					prev_node->next_name_part_states_s->insert(it6,
						pair<string, DynamicState*>(new_name, NULL));
				}
				else
				{
					
					prev_node->next_name_part_states_s->insert(it6,
						pair<string, DynamicState*>(new_name, NULL));
					

				}
				
				my_node->current_name_part = new_name;

				// add it to trie_names

				map<string, MapNode*>::iterator it2 = my_dynamic_machine->trie_names->begin();

				// use init so my_dynamic_machine->trie_names->find(prev_word)->second works next
				// round

				my_dynamic_machine->trie_names->insert(it2,
							pair<string, MapNode*>(new_name, initMapNode()));

				prev_word = new_name;
				
			}
			// last state part doesn't exist
			else
			{
				map<string, DynamicState*>::iterator it = prev_node->next_name_part_states_s->begin();

				if(i == name->population - 1)
				{
					// add a new link with the state
					
					DynamicState* new_state = initDynamicState(	name,
															start_children,
															children,
															next_states,
															value);
					prev_node->next_name_part_states_s->insert(it,
						pair<string, DynamicState*>(new_name, new_state));
					
				}
				else
				{
					// add a new link w no state
					
					prev_node->next_name_part_states_s->insert(it,
						pair<string, DynamicState*>(new_name, NULL));
					
				}
				// put it in as root's child
				
				prev_node->current_name_part = new_name;

				// add it to trie_names

				map<string, MapNode*>::iterator it2 = my_dynamic_machine->trie_names->begin();

				// use init so my_dynamic_machine->trie_names->find(prev_word)->second works next
				// round

				my_dynamic_machine->trie_names->insert(it2,
							pair<string, MapNode*>(new_name, initMapNode()));

				prev_word = new_name;
				
			}
		}*/





















		

		//printf("%i\n", i);
		//MapNode* my_node;
		

		// if find works and i == name->population - 1
			// append a context name 1 greater than the max id number
			// return the new name
		// get the name
		//printf("link to add %s\n", new_name.c_str());
		// add it to root's children
		/*
		map<string, DynamicState*>::iterator it = my_node->next_name_part_states_s->begin();

		if(i == name->population - 1)
		{
			
		}
		else
		{
			my_node->next_name_part_states_s->insert(it,
					pair<string, DynamicState*>(new_name, NULL));

		}*/
		
	//}
	/*
	printf("printing states\n");
	
	for(map<string, MapNode*>::iterator it3 = my_dynamic_machine->trie_names->begin();
		it3 != my_dynamic_machine->trie_names->end();
		it3++
		)
	{
		printf("%s\n", it3->first.c_str());
		for(map<string, struct DynamicState*>::iterator it = it3->second->next_name_part_states_s->begin();
				it != it3->second->next_name_part_states_s->end();
				it++
				)
		{
			printf("          %s\n", it->first.c_str());
		}
	}
	
	//exit(1);
	printf("print tree\n");
	printStateTrie(my_dynamic_machine, "root", 1);
	//exit(1);
	//printStateTrie(my_dynamic_machine, "start");
	printf("\n");
	*/
	//return my_dynamic_machine;
	//my_dynamic_machine->name = name; // strings
	//my_dynamic_machine->start_children = start_children;  // array of strings
	//my_dynamic_machine->children = children; // array of strings
	//my_dynamic_machine->next_states = next_states; // array of strings
	//my_dynamic_machine->value = value;

	// use the name to insert the state

	// dict = string -> MapNode
	// MapNode = string 2 -> state
	// MapNode =  state

	//printf("ready to run\n");
	/*int counter = 0;
	int* counter_ptr = &counter;
	int debug_states_run = 1;
	int* debug_states_run_ptr = &debug_states_run;
	// run states function is the same name as the version in the scanner file
	runMachine2(	my_dynamic_machine->static_machine,
					my_dynamic_machine,
					0,
					counter_ptr,
					debug_states_run_ptr);
	*/
	//return true;
}


/*
delete
traverse all the way to the last word
save index of the last fork found and ith word tracking
use next match after index to be the first node to delete
delete the word chain

*/

bool insertState2(string name_1, string name_2)
{
	return true;
}
bool insertState3(string name_1, string name_2, string name_3)
{
	return true;
}


// implementation
// state functions
bool searchForItem(void* object)
{
	DynamicMachine* my_machine = (DynamicMachine*) object;
	// obtain the state from buffer
	// setup things in auxiliary object
	return true;
}
int runState(StateMachine* machine, int start_of_next_states, void* object/*Scanner* my_scanner*/, int level)
{
	// children links come before next links
	
	

	int current_state = machine->current_state;

	int max_neighbors = machine->max_neighbors;
	// go to start of next states for current_state
	int i = start_of_next_states;
	//printf("going to run some states\n");
	bool state_changed = false;
	for(int j = 0; j < max_neighbors; j++)
	{
		printf("%strying %s\n",
				makeSpaces(level).c_str(),
				machine->state_names_strings->at( machine->next_states[i + j] ).c_str() );

		int winning_state = 0;

		switch(machine->next_states[i + j])
		{
			

			case _search:
			{
				winning_state = _search;
				state_changed = true;
				break;
			}
			case root_exists:
			{
				winning_state = root_exists;
				state_changed = true;


				break;
			}
			case get_id_of_expected_location:
			{
				winning_state = get_id_of_expected_location;
				state_changed = true;

				break;
			}
			case setup:
			{
				winning_state = setup;
				state_changed = true;
				break;
			}
			case midpoint:
			{
				winning_state = midpoint;
				state_changed = true;

				break;
			}
			case type_of_match_int:
			{
				winning_state = type_of_match_int;
				state_changed = true;

				break;
			}
			case type_of_match_char:
			{
				winning_state = type_of_match_char;
				state_changed = true;

				break;
			}
			case type_of_match_bool:
			{
				winning_state = type_of_match_bool;
				state_changed = true;

				break;
			}

			case no_more_matches_are_possible:
			{
				winning_state = no_more_matches_are_possible;
				state_changed = true;

				break;
			}
			case no_match:
			{
				winning_state = no_match;
				state_changed = true;

				break;
			}
			/*
			case left:
			{
				winning_state = left;
				state_changed = true;

				break;
			}
			case right:
			{
				winning_state = right;
				state_changed = true;

				break;
			}
			*/

			case full_match:
			{
				winning_state = full_match;
				state_changed = true;

				break;
			}

			case partial_match:
			{
				winning_state = partial_match;
				state_changed = true;
				break;
			}
			case tree_has_too_little_data_for_a_full_match:
			{
				winning_state = tree_has_too_little_data_for_a_full_match;
				state_changed = true;

				break;
			}
			case tree_is_incomplete:
			{
				winning_state = tree_is_incomplete;
				state_changed = true;


				break;
			}
			case calculate_expected_location:
			{
				winning_state = calculate_expected_location;
				state_changed = true;

			
				break;
			}
			
			default:
			{
				break;
			}
		}
		if(state_changed)
		{
			return winning_state;
		}

	}
	if(!state_changed)
	{
		return false;
	}
	return -10;

}
bool makeStateMachine(DynamicMachine* my_machine)
{

	if(my_machine != NULL)
	{

		StateMachine* machine = my_machine->static_machine;
		// the first state doesn't get run
		// machine is finished the moment the current state == done
		//int counter = 0;
		printf("start state machine\n");
		//int current_state = machine->current_state;
		// loop through and try the children
		int level = 0;
		int counter = 0;
		int* counter_ptr = &counter;
		int debug_states_run = -1;
		int* debug_states_run_ptr = &debug_states_run;
		runMachine(machine, my_machine, level, counter_ptr, debug_states_run_ptr);
		//printMultiwayLinesNodesInContainer(my_scanner->_lines_graph);

		//machine->current_state = current_state
		//deleteMachineForMakeTree(machine);

		//printf("machine is done\n");
		//printTree(my_scanner->lines_graph, 0);

		return true;
	}

	return false;
}


/*

level 1 states are the json chars (chars)
	persistent
		1 string
level 2 states are read 1 string from level 1 states (tokens)
	persistent
		list of lists of strings
		list of strings
		1 object
		1 trie of strings
		1 trie of objects

level 3
	persistent
		1 trie of objects
list
	next
		object
	children
		[
			-list
			string

			string_part_start
				children
					& " opening, (character  " closing), (','  between_strings, " opening | ]  string_part_end)
				next
					string_part_end
			string_part_end

			nested_list_start
				next
					& [ string, [  string_part_start, & " opening, (character | " closing), (',' between_strings, " opening | ]  string_part_end),  (',' between_strings, [ string | ] nested_list_end)
			nested_list_end

		','
			between_strings
				next
					& " opening
			between_pairs
				next
					& " opening



	object
		repeat
			next
				object repeat
			children
				object stay_on_object
		stay_on_object
			next
				name_key, list_of_strings
			children
				-{
		name_key
			children
				"
					-opening
						next
							(character | " closing)
					closing
				character
					next
						(character | " closing)

		list_of_strings
			children
				-start_char
					children
						-[ string
					next
						-(string | no more strings)
				string
					children
						& " opening
			next
				nexts_key

		nexts_key
			children
				& " opening


*/



void printData(Data* var_data, int indent_level)
{
	if(var_data != NULL)
	{
		switch(var_data->type_id)
		{
			case 0:
			{

				printf("%s%i\n", makeSpaces(indent_level).c_str(), var_data->_int);
				break;
			}
			case 1:
			{
				printf("%s%s\n", makeSpaces(indent_level).c_str(), var_data->_string);

				break;
			}
			case 2:
			{

				printf("%s%f\n", makeSpaces(indent_level).c_str(), var_data->_float);

				break;
			}

		}
		printf("\n");
	}
	else
	{
		printf("%sno data\n", makeSpaces(indent_level).c_str());
	}
	
}

void printTrieNodeTree(TrieNode* root, int indent)
{
	//printf("printing\n");
	TrieNode* root_tracker = root;
	if(root_tracker != NULL)
	{
		if(root_tracker->word != NULL)
		{
			printf("%s%s\n", makeSpaces(indent).c_str(), root_tracker->word);
		}
		//printf("%x\n", root_tracker->neighbors);
		//printf("%x\n", root_tracker->object);

		if(root_tracker->neighbors != NULL)
		{
			if(root_tracker->object != NULL)
			{
				printf("%s", makeSpaces(indent + 2).c_str());
				printContextState2(root_tracker->object);
				printf("\n");

			}
			//printf("# of neighbors %i\n", root_tracker->neighbors_count);
			//printf("size %i\n", root_tracker->size);
			for(int i = 0; i < root_tracker->size; i++)
			{
				if(root_tracker->neighbors[i] != NULL)
				{
					printTrieNodeTree(root_tracker->neighbors[i], indent + 2);

				}
			}
		}
		else
		{
			if(root_tracker->object != NULL)
			{
				printf("%s", makeSpaces(indent + 2).c_str());
				printContextState2(root_tracker->object);
				printf("\n");

			}
		}
	}
	else
	{
		printf("[]\n");
	}
}

void printContextState(ContextState* node)
{
	/*
		nexts,
		start_children,
		children,
		function_name,
		variable_from_json_dict,
		parents
	*/
	printf("state name\n");
	printTrieNodeTree(node->state_name, 0);
	printf("\n");

	printf("nexts\n");

	printTrieNodeTree(node->nexts_, 0);
	printf("\n");

	printf("start children\n");
	printTrieNodeTree(node->start_children, 0);
	printf("\n");

	printf("children\n");
	printTrieNodeTree(node->children_, 0);
	printf("\n");

	printf("function name\n");
	printf("%s\n\n", node->function_pointer_name);
	printf("\n");

	printf("data\n");
	printData(node->var_data, 0);
	printf("\n");


	printf("parents\n");
	printTrieNodeTree(node->parents_, 0);
	printf("\n");

	printf("start_children_are_parallel\n");
	printf("%i\n", node->start_children_are_parallel);
	printf("\n");

	printf("nexts_are_parallel\n");
	printf("%i\n", node->nexts_are_parallel);
	printf("\n");
	
	printf("is_start_child\n");
	printf("%i\n", node->is_start_child);
	printf("\n");
	
	printf("is_child\n");
	printf("%i\n", node->is_child);
	printf("\n");
	
	printf("is_parent\n");
	printf("%i\n", node->is_parent);
	printf("\n");

	printf("is_start_state\n");
	printf("%i\n", node->is_start_state);
	printf("\n");

	printf("is_end_state\n");
	printf("%i\n", node->is_end_state);
	printf("\n");
	
	printf("is_data_state\n");
	printf("%i\n", node->is_data_state);
	printf("\n");



}
void printTrieNodes(TrieNode* trie_node_sequence)
{
	TrieNode* trie_node_sequence_tracker = trie_node_sequence;
	while(trie_node_sequence_tracker != NULL)
	{
		if(trie_node_sequence_tracker->word != NULL)
		{
			printf("%s\n", trie_node_sequence_tracker->word);
			

		}
		if(trie_node_sequence_tracker->neighbors != NULL)
		{
			trie_node_sequence_tracker = trie_node_sequence_tracker->neighbors[0];

		}
		else
		{
			//printf("at last node\n");
			if(trie_node_sequence_tracker->object != NULL)
			{
				printContextState(trie_node_sequence_tracker->object);
			}
			
			break;
		}

	}
	printf("\n");
}

void printTrieNodeTreeFlat(TrieNode* root)
{
	// printContextState2 calls this
	//printf("printing flat name\n");

	TrieNode* root_tracker = root;
	if(root_tracker != NULL)
	{
		//printf("\nabout to print word root_tracker->word %x, root_tracker->neighbors %x\n", root_tracker->word, root_tracker->neighbors);

		if(root_tracker->word != NULL)
		{

			printf("%s", root_tracker->word);
		}
		//printf("neighbors count %i\n", root_tracker->neighbors_count);
		//printf("tracker size %i\n", root_tracker->size);
		//printf("neighbors %x\n", root_tracker->neighbors);

		if(root_tracker->neighbors != 0)
		{
			printf(" | ");
			//printf("neighbors 2 %x\n", root_tracker->neighbors);

			// can't check it, doesn't happen all the time, the nodes are set correctly
			//if(root_tracker->neighbors_count != NULL)
			//	printf("# of neighbors %i\n", root_tracker->neighbors_count);
			//else
			//	printf("no neighbor count\n");
			//printf("size %i\n", root_tracker->size);
			//printf("# of neighbors %i, size %i\n", root_tracker->neighbors_count, root_tracker->size);
			//printf("will the loop happen\n");
			//printf("%i\n", root_tracker->neighbors_count);
			for(int i = 0; i < root_tracker->neighbors_count; i++)
			{
				//printf("%i problem? %i\n", i, root_tracker->size);
				if(root_tracker->neighbors[i] != NULL)
				{
					printTrieNodeTreeFlat(root_tracker->neighbors[i]);

				}
			}
		}
	}
	else
	{
		printf("[]\n");
	}
}

void printContextState2(ContextState* node)
{

	if(node != NULL)
	{
		if(node->state_name != NULL)
		{

			printf("-> ");
			printTrieNodeTreeFlat(node->state_name->neighbors[0]);

		}

	}
}

/*
typedef struct Data
{
	int type_id; // enum
	
	0 => int
	1 => string
	2 => float

	int _int;

	char* _string;
	int string_size;

	float _float;

}Data;

*/

Data* makeDataInt(int a)
{
	Data* variable = (Data*) malloc(sizeof(Data));
	variable->type_id = 0;
	variable->_int = a;
	return variable;
}
Data* makeDataFloat(float a)
{
	Data* variable = (Data*) malloc(sizeof(Data));
	variable->type_id = 2;
	variable->_float = a;
	return variable;

}
/*
Data* makeDataString(char* a)
{
	Data* variable = (Data*) malloc(sizeof(Data));
	variable->type_id = 1;
	variable->_string = copyString(a);
	return variable;

}*/
void deleteData(Data* variable)
{
	if(variable->_string)
	{
		free(variable->_string);
		variable->_string = NULL;
	}
	free(variable);
	variable = NULL;
}
ContextState* initContextState()
{
	ContextState* test = (ContextState*) malloc(sizeof(ContextState));
	test->parents_size = 0;
	test->children_size = 0;

	//test->name = malloc(sizeof(char) * 50);
	//memcpy(test->name, input, sizeof(char) * strlen(input));

	return test;
}
ContextState* makeFullContextState2(
	TrieNode* name,
	TrieNode* nexts,
	TrieNode* start_children,
	TrieNode* children,
	char* function_name,
	Data* variable_from_json_dict,
	TrieNode* parents,
	bool (*function_pointer)(struct ContextState* state),
	bool start_children_are_parallel,
	bool nexts_are_parallel,
	bool is_start_child,
	bool is_child,
	bool is_parent,
	bool is_start_state,
	bool is_end_state,
	bool is_data_state)
{
	// printf("got here\n");

	ContextState* state = makeFullContextState(
	name,
	nexts,
	start_children,
	children,
	function_name,
	variable_from_json_dict,
	parents,
	start_children_are_parallel,
	nexts_are_parallel,
	is_start_child,
	is_child,
	is_parent,
	is_start_state,
	is_end_state,
	is_data_state);
	state->function_pointer = function_pointer;
	return state;

}
ContextState* makeFullContextState(
	TrieNode* name,
	TrieNode* nexts,
	TrieNode* start_children,
	TrieNode* children,
	char* function_name,
	Data* variable_from_json_dict,
	TrieNode* parents,
	bool start_children_are_parallel,
	bool nexts_are_parallel,
	bool is_start_child,
	bool is_child,
	bool is_parent,
	bool is_start_state,
	bool is_end_state,
	bool is_data_state)
{
	// name, nexts, start_children, children, parents are all dummy nodes
	//printf("got here\n");

	int sizeof_trie_node = sizeof(TrieNode);

	int sizeof_context_state = sizeof(ContextState);

	int sizeof_data = sizeof(Data);
	//printf("got here\n");

	int sizeof_function_name = 0;
	if(function_name != NULL)
	{
		sizeof_function_name = sizeof(char) * (strlen(function_name) + 1);

	}
	ContextState* node 			= (ContextState*) malloc(sizeof_context_state);
	//printf("got here\n");

	if(name == NULL &&
		nexts == NULL &&
		start_children == NULL &&
		children == NULL &&
		function_name == NULL &&
		variable_from_json_dict == NULL &&
		parents == NULL)
	{
		//printf("all null\n");
		return node;
	}
	node->state_name 			= (TrieNode*) malloc(sizeof_trie_node);
	node->nexts_ 				= NULL;
	node->start_children 		= NULL;
	node->children_ 			= NULL;
	node->parents_ 				= NULL;
	
	node->function_pointer_name = NULL;
	
	node->var_data 				= NULL;


	// only need to copy over the pointers inside NeighborNames

	if(name != NULL)
	{

		memcpy(node->state_name,
			   name,
			   sizeof_trie_node);
	}

	if(nexts != NULL)
	{
		node->nexts_ = (TrieNode*) malloc(sizeof_trie_node);
		memcpy(node->nexts_,
			   nexts,
			   sizeof_trie_node);
	}

	if(start_children != NULL)
	{
		//printf("added start children\n");
		node->start_children = (TrieNode*) malloc(sizeof_trie_node);

		memcpy(node->start_children,
			   start_children,
			   sizeof_trie_node);
	}
	

	if(children != NULL)
	{
		//printf("added children\n");
		node->children_ = (TrieNode*) malloc(sizeof_trie_node);

		memcpy(node->children_,
			   children,
			   sizeof_trie_node);
	}
	if(parents != NULL)
	{
		//printf("added parents\n");
		node->parents_ = (TrieNode*) malloc(sizeof_trie_node);

		memcpy(node->parents_,
			   parents,
			   sizeof_trie_node);
	}
	if(function_name != NULL)
	{
		node->function_pointer_name = (char*) malloc(sizeof_function_name);

		memcpy(node->function_pointer_name,
			   function_name,
			   sizeof(char) * (strlen(function_name) + 1));
		
	}
	if(variable_from_json_dict != NULL)
	{
		node->var_data = (Data*) malloc(sizeof_data);
		memcpy(node->var_data,
			   variable_from_json_dict,
			   sizeof_data);
	}

	
	node->start_children_are_parallel = start_children_are_parallel;
	node->nexts_are_parallel = nexts_are_parallel;
	node->is_start_child = is_start_child;
	node->is_child = is_child;
	node->is_parent = is_parent;
	node->is_start_state = is_start_state;
	node->is_end_state = is_end_state;
	node->is_data_state = is_data_state;
	return node;

}
/*
void deleteContextState(ContextState* node)
{
	printf("deleteContextState\n");

	if(node != NULL)
	{
		//TrieNode* name(delete)
		deleteTrieNode(node->state_name);
		node->state_name = NULL;
		printf("passes state_name\n");
		free(node->name);
		node->name = NULL;
		//TrieNode* nexts
		deleteTrieNode(node->nexts_);
		node->nexts_ = NULL;
		printf("passes nexts_\n");

		// struct doesn't support this yet
		
		for(int i = 0; i < node->nexts_size; i++)
		{
			deleteContextState(node->children[i]);

		}
		//TrieNode* start_children
		deleteTrieNode(node->start_children);
		node->start_children = NULL;
		for(int i = 0; i < node->parents_size; i++)
		{
			deleteContextState(node->parents[i]);
			node->parents[i] = NULL;
		}
		node->parents = NULL;
		//TrieNode* children
		deleteTrieNode(node->children_);
		node->children_ = NULL;
		for(int i = 0; i < node->children_size; i++)
		{
			deleteContextState(node->children[i]);
			node->children[i] = NULL;


		}
		node->children = NULL;
		//char* function_pointer_name
		free(node->function_pointer_name);
		node->function_pointer_name = NULL;
		//Data* var_data(delete)
		deleteData(node->var_data);
		node->var_data = NULL;
		//TrieNode* parents
		deleteTrieNode(node->parents_);
		node->parents_ = NULL;
		//bool (*function_pointer)(struct ContextState* state)
		free(&node->function_pointer);
		node->function_pointer = NULL;
		free(node);
		node = NULL;
		printf("done deleting ContextState\n");
	}
	else
	{
		printf("done deleting ContextState\n");

	}

}*/
/*
void printState(ContextState* node)
{
	if(node != NULL)
	{
		printf("\nname: %s\n", node->name);
		printf("parents: size = %i\n", node->parents_size);
		for(int i = 0; i < node->parents_size; i++)
		{
			printf("%s, ", node->parents_names[i]);
		}
		printf("\n");
		printf("children: size = %i\n", node->children_size);
		for(int i = 0; i < node->children_size; i++)
		{
			printf("%s, ", node->children_names[i]);
		}
		printf("\n");

	}
}*/
/*
Data* variable(Tokens* my_tokens)
{
	//if(getToken(my_tokens).type != _object) exit(1);
	//printf("%s\n", tokenType(token));
	//printf("%s\n", collectChars(token, input));
	char* token_string = collectChars(getToken(my_tokens), getInput(my_tokens));
	
	typedef struct Data
	{
	int type_id; // enum

	int _int;

	char* _string;
	int string_size;

	float _float;
	}Data;
	
	Data* variable = (Data*) malloc(sizeof(Data));

	if(strcmp(token_string, "\"{}\"") == 0)
	{

		// *i += 1;
		advanceToken(my_tokens);
		variable = NULL;
	}
	else
	{

		// *i += 1;
		advanceToken(my_tokens);
		//token = tokens[*i];
		char* type_name = collectChars(getToken(my_tokens), getInput(my_tokens));


		// *i += 1;
		//token = tokens[*i];
		advanceToken(my_tokens);
		char* data = collectChars(getToken(my_tokens), getInput(my_tokens));

		// *i += 1;
		advanceToken(my_tokens);
		if(strcmp(data, "\"NULL\"") == 0)
		{
			variable = NULL;
		}
		else
		{
			if(strcmp(type_name, "\"int\"") == 0)
			{
				int integer;
				// skip over the '\"'
				sscanf(data + 1, "%i", &integer);
				variable->_int = integer;

				variable->type_id = 0;
			}
			else if(strcmp(type_name, "\"char*\"") == 0)
			{
				if(strcmp(data, "\"\"") == 0)
				{
					variable = NULL;
				}
				else
				{
					int sizeof_string = sizeof(char) * (strlen(data) + 1);
					variable->_string = (char*) malloc(sizeof_string);
					memcpy(variable->_string, data, sizeof_string);
					variable->string_size = strlen(data);
					variable->type_id = 1;

				}
			}
			else if(strcmp(type_name, "\"float\"") == 0)
			{
				float float_value;

				// skip over the '\"'
				sscanf(data + 1, "%f", &float_value);
				variable->_float = float_value;
				variable->type_id = 2;

			}
		}
		
	}
	return variable;

}
*/
bool getBinaryValue(char* json_value)
{
	if(strcmp(json_value, "0"))
	{
		return 0;
	}
	else if(strcmp(json_value, "1"))
	{
		return 1;
	}
	else
	{
		printf("not a valid binary value\n");
		exit(1);
	}
}
/*
ContextState* makeContextState( int* i, jsmntok_t tokens[], const char* input Tokens* my_tokens, int token_count)
{
	//printf("object to run |%s|\n", collectChars(tokens[*i], input));
	//TrieTree* name_context_state = makeDict();
	//jsmntok_t token = tokens[*i];
	//printf("%s\n", tokenType(getToken(my_tokens).type));
	//printf("object to run\n");
	//printf("%s\n", collectChars(getToken(my_tokens), getInput(my_tokens)));

	//if(getToken(my_tokens).type != _object) exit(1);
	//printf("%s\n", collectChars(getToken(my_tokens), getInput(my_tokens)));

	// *i += 1;
	//token = tokens[*i];
	advanceToken(my_tokens);
	//printf("%s\n", tokenType(token));
	//if(getToken(my_tokens).type != _string) exit(1);
	// *i += 1;
	//token = tokens[*i];
	advanceToken(my_tokens);
	//printf("%s\n", tokenType(getToken(my_tokens)));
	//printf("name\n");
	//printf("%s\n", collectChars(getToken(my_tokens), getInput(my_tokens)));

	//TrieNode* makeTrieTree(int i, jsmntok_t tokens[], const char* input)
	//printf("%i\n", getI(my_tokens));
	TrieNode* name = makeTrieTree(my_tokens);//arrayOfArrays(i, tokens, input, token_count);
	//printTrieNodeTreeFlat(name);
	//	printf("%i\n", getI(my_tokens));
	//printf("%s\n", collectChars(getToken(my_tokens), getInput(my_tokens)));

	
	printf("printing trie tree\n");
	printTrieNodeTree(name, 0);
	printf("\n\n");
	
	
	typedef struct NeighborNames
		{
			char** list_of_names;
			int number_of_names;
			int* start_names;
			int number_of_start_names;
		}NeighborNames;
	
	//printListOfListsOfStrings(name);
	
	
	
	//printf("got here\n");

	// tokens[i] == "nexts"
	//token = tokens[*i];

	//printf("%s\n", collectChars(token, input));
	//printf("%s\n", tokenType(token));

	//printf("%s\n", collectChars(token, input));

	// at keyword now
	// *i += 1;
	advanceToken(my_tokens);
	//token = tokens[*i];
	//printf("%s\n", collectChars(token, input));

	//printf("%s\n", tokenType(token));
	//printf("nexts\n");
	TrieNode* nexts = makeTrieTree(my_tokens);//arrayOfArrays(i, tokens, input, token_count);
	
	printf("printing trie tree\n");
	printTrieNodeTree(nexts, 0);
	printf("\n\n");
	
	//printListOfListsOfStrings(nexts);
	//token = tokens[*i];

	//printf("%s\n", collectChars(token, input));
	//printf("%s\n", collectChars(token, input));
	//printf("%s\n", collectChars(getToken(my_tokens), getInput(my_tokens)));

	// at keyword now
	advanceToken(my_tokens);
	// *i += 1;
	//token = tokens[*i];
	//printf("%s\n", tokenType(token));
	//printf("start children\n");
	TrieNode* start_children = makeTrieTree(my_tokens);//arrayOfArrays(i, tokens, input, token_count);
	
	printf("printing trie tree\n");
	printTrieNodeTree(start_children, 0);
	printf("\n\n");
	
	//printListOfListsOfStrings(start_children);

	//token = tokens[*i];

	//printf("%s\n", collectChars(token, input));
	//printf("%s\n", collectChars(token, input));
	//printf("%s\n", collectChars(getToken(my_tokens), getInput(my_tokens)));

	// at keyword now
	advanceToken(my_tokens);
	// *i += 1;
	//token = tokens[*i];
	//printf("%s\n", tokenType(token));
	//printf("children\n");
	TrieNode* children = makeTrieTree(my_tokens);//arrayOfArrays(i, tokens, input, token_count);
	
	printf("printing trie tree\n");
	printTrieNodeTree(children, 0);
	printf("\n\n");
	
	//printListOfListsOfStrings(children);
	//token = tokens[*i];
	//printf("%s\n", tokenType(token));
	//printf("%s\n", collectChars(token, input));

	//printf("%s\n", collectChars(getToken(my_tokens), getInput(my_tokens)));
	advanceToken(my_tokens);
	// *i += 1;
	//token = tokens[*i];
	//printf("%s\n", tokenType(token));
	char* function_name = collectChars(getToken(my_tokens), getInput(my_tokens));
	// n time for this
	// add to a trienode
	// insert into a functions trie	
	//printf("function name %s\n", function_name);
	advanceToken(my_tokens);

	//printf("%s\n", collectChars(getToken(my_tokens), getInput(my_tokens)));
	advanceToken(my_tokens);

	// *i += 1;
	//token = tokens[*i];
	//printf("%s\n", tokenType(token));
	//printf("%s\n", collectChars(token, input));

	// *i += 1;
	//token = tokens[*i];
	Data* variable_from_json_dict = variable(my_tokens);
	//printf("variable\n");
	//printData(variable_from_json_dict);
	//token = tokens[*i];
	//printf("%s\n", collectChars(token, input));

	//printf("%s\n", collectChars(getToken(my_tokens), getInput(my_tokens)));
	advanceToken(my_tokens);

	// *i += 1;
	//token = tokens[*i];
	//printf("before arrayOfArrays %s\n", tokenType(token));

	TrieNode* parents = makeTrieTree(my_tokens);//arrayOfArrays(i, tokens, input, token_count);
	//printListOfListsOfStrings(parents);
	// *i += 1;

	//printf("%s\n", collectChars(getToken(my_tokens), getInput(my_tokens)));
	advanceToken(my_tokens);
	//printf("%s\n", collectChars(tokens[*i], input));
	bool start_children_are_parallel = getBinaryValue(collectChars(getToken(my_tokens), getInput(my_tokens)));
	//printf("%i\n", start_children_are_parallel);
	advanceToken(my_tokens);



	// *i += 1;

	//printf("%s\n", collectChars(getToken(my_tokens), getInput(my_tokens)));
	advanceToken(my_tokens);

	//printf("%s\n", collectChars(getToken(my_tokens), getInput(my_tokens)));

	bool nexts_are_parallel = getBinaryValue(collectChars(getToken(my_tokens), getInput(my_tokens)));
	advanceToken(my_tokens);
	//printf("%i\n", nexts_are_parallel);



	//	*i += 1;


	//printf("%s\n", collectChars(getToken(my_tokens), getInput(my_tokens)));
	advanceToken(my_tokens);

	bool is_start_child = getBinaryValue(collectChars(getToken(my_tokens), getInput(my_tokens)));
	//printf("%i\n", is_start_child);
	advanceToken(my_tokens);

	//	*i += 1;

	//printf("%s\n", collectChars(getToken(my_tokens), getInput(my_tokens)));
	advanceToken(my_tokens);
	bool is_child = getBinaryValue(collectChars(getToken(my_tokens), getInput(my_tokens)));
	//printf("%i\n", is_child);
	advanceToken(my_tokens);

	//	*i += 1;



	//printf("%s\n", collectChars(getToken(my_tokens), getInput(my_tokens)));
	advanceToken(my_tokens);
	bool is_parent = getBinaryValue(collectChars(getToken(my_tokens), getInput(my_tokens)));
	//printf("%i\n", is_parent);
	advanceToken(my_tokens);


	//	*i += 1;
	//printf("%s\n", collectChars(getToken(my_tokens), getInput(my_tokens)));
	advanceToken(my_tokens);

	bool is_start_state = getBinaryValue(collectChars(getToken(my_tokens), getInput(my_tokens)));
	//printf("%i\n", is_start_state);
	advanceToken(my_tokens);
	//	*i += 1;



	//printf("%s\n", collectChars(getToken(my_tokens), getInput(my_tokens)));
	advanceToken(my_tokens);

	bool is_end_state = getBinaryValue(collectChars(getToken(my_tokens), getInput(my_tokens)));
	//printf("%i\n", is_end_state);
	advanceToken(my_tokens);
	//	*i += 1;


	//printf("%s\n", collectChars(getToken(my_tokens), getInput(my_tokens)));
	advanceToken(my_tokens);


	bool is_data_state = getBinaryValue(collectChars(getToken(my_tokens), getInput(my_tokens)));

	//printf("%i\n", is_data_state);
	advanceToken(my_tokens);
	//printf("\n\n\n\n");
	//exit(1);
	
	printf("printing trie tree\n");
	printTrieNodeTree(parents, 0);
	printf("\n\n");
	
		
	{
	    "name":           ["start"],
	    "nexts":          [],
	    "start_children": [["("]],
	    "children":       [["test_data"],
	                       ["letters_and_digits"],
	                       [")"]],
	    "function_name":  "returnTrue",
	    "data":           {"nothing": "null"},
	    "parents":        [["NONE"]],
	    "start_children_are_parallel" : 0,
	    "nexts_are_parallel" : 0,
	    "is_start_child" : 0,
	    "is_child" : 0,
	    "is_parent" : 1,
	    "is_start_state" : 0,
	    "is_end_state" : 0,
	    "is_data_state" : 0
	  }
  
	  // also should add the actual functions to the state
	  // f(state, parent)
	
	ContextState* current_state = makeFullContextState(
		name,
		nexts,
		start_children,
		children,
		function_name,
		variable_from_json_dict,
		parents,
		start_children_are_parallel,
		nexts_are_parallel,
		is_start_child,
		is_child,
		is_parent,
		is_start_state,
		is_end_state,
		is_data_state);
	
	//printf("printing state\n\n");
	//printContextState(current_state);
	// now we are at the next object
	//printf("next\n");
	//exit(1);

	// may be out of tokens
	
	if(*i < token_count)
	{
		token = tokens[*i];
		//printf("done\n");
		return current_state;
	}
	return current_state;
	
}*/
