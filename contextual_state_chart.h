#ifndef STATE3
#define STATE3
#include "standard_headers.h"
// #include <stdbool.h>
// #include "stdlib.h"
// #include <stdio.h>
// #include <string.h>
// #include "trie_node.h"
// #include "multiway_lines_node.h"
#include "vector.h"
#include "trie_tree.h"
// #include <map>
// #include <set>
//#include "state_machine.h"
// struct StateMachine;

/*
copying variables up or down the machine
trie tree for destination state name
state machine array for the children variable names(that are stored in the trie tree)
the avariable names then have a number mapping to the official state machine array


*/
// typedef struct Search
// {
// 	int start;
// 	int end;
// 	int mid;
// 	int comparison_type;
// 	Vector* container;

// }Search;
// Search* initSearch();

// typedef struct Insert
// {
// 	struct Search* my_search;
// }Insert;
// Insert* initIners();

// typedef struct Delete
// {
// 	struct Search* my_search;
// }Delete;
// Delete* initDelete();

//enum stack_types{char_p_p, struct_context_state_p_p};
typedef struct Data
{
	int type_id; // enum
	/*
	1 => int
	2 => float
	3 => char
	4 => bool
	*/
	int _int;
	float _float;
	char _char;
	bool _bool;

}Data;



typedef struct ContextualStateChart
{

	// variations of the same state in different situations represent
	// the idea of context and are identified by slightly different state names
	Vector* states;
	TrieTree* state_names;
	// root is position 0



}ContextualStateChart;
typedef struct State
{
	// This state can be multiple things:
	// control flow node
	// primitive value
	// dictionary
	// root for any other data structure
	Vector* name;

	// operating system stuff
	// https://www.enterpriseintegrationpatterns.com/docs/IEEE_Software_Design_2PC.pdf
	// run state if visit_count == threshhold in 1 pass of trying next states from all timelines
	// This is for when asynchronous timelines merge into a synchronous timeline
	// assume 2 different asynchronous states will try this state at the same time
	int threshold;
	int visit_count;
	
	// lets us quickly check if the state's parent is actually the same one as the parent of the timeline
	// prevents us from having a timeline try states(more than 1 in a row at the time of crossover) in a different timeline before the other
	// timeline tries it
	// keep all asynchronous timelines separated even if they visit a state from another timeline
	TrieTree* parents;


	// preventing timeline stalls
	// if we assume this state represents a parent on a timeline
	// then we can time how long it takes for the submachine to finish
	// if the duration > 1 second kill the state(curent state) and all parent states in the timeline
	// exclucding the root state as the root may host more than 1 timeline
	int duration;


	bool next_states_are_parallel_states;
	Vector* next_states;

	bool children_are_parallel_states;
	Vector* children;




	// for copying up saved items after the current submachine is finished
	// whatever data is in the higher level variable name we will overwrite with the data from the lower level

	bool is_copied_up_hierarchy;
	Vector* destination_state_parent_name;



	// for when this state represents a dictionary
	TrieTree* keys;

	bool is_dictionary;
	bool is_primitive;
	bool is_other_data_structure;
	bool is_control_flow_node;


	// for when the state is storing a primitive value
	Data* value;

	// modification flags for the recording user changes system
	bool is_added;
	bool is_deleted;
	bool is_modified;


	Vector* function_name;
	bool (*function) (ContextualStateChart* my_machine, int parent_state, int current_state);

}State;


// dynamic state funcitons
// DynamicState* DynamicStateInitDynamicState(	Vector* name, // strings
// 								Vector* parents,  // array of strings
// 								Vector* start_children,  // array of strings
// 								Vector* children, // array of strings
// 								Vector* next_states, // array of strings
// 								bool (*function) (	DynamicMachine* my_machine,
// 													DynamicState* parent_state,
// 													DynamicState* current_state));

// DynamicState* DynamicStateInitDynamicState2(	Vector* name, // strings
// 								bool is_start_child,
// 								bool has_down_links,
// 								Vector* parents,  // array of strings
// 								Vector* start_children,  // array of strings
// 								Vector* children, // array of strings
// 								Vector* next_states, // array of strings
// 								bool (*function) (	DynamicMachine* my_machine,
// 													DynamicState* parent_state,
// 													DynamicState* current_state));

// dynamic machine functions
// final 2 structs for trie ordered dict
// void TrieTreeInsertString(TrieTree* my_trie_tree
// // , string element
// );




ContextualStateChart* DynamicMachineInitDynamicMachine();
Vector* DynamicMachineAppendState(ContextualStateChart* my_machine, State* state);

bool returnTrue(ContextualStateChart* my_machine, int parent_state, int current_state);

bool returnFalse(ContextualStateChart* my_machine, int parent_state, int current_state);

bool recordA(ContextualStateChart* my_machine, int parent_state, int current_state);
bool returnTrue(ContextualStateChart* my_machine, int parent_state, int current_state);
bool returnATrueValue(ContextualStateChart* my_machine, int parent_state, int current_state);

// DynamicState* DynamicMachineRunStates(DynamicMachine* my_machine, Vector* state_names);

State* DynamicStateMakeVariable(
	// string variable_name,
										Vector* parents,  // array of strings
										Data* value);

// DynamicState* DynamicStateMakeVariable2(string variable_name,
// 										Vector* parents,  // array of strings
// 										Data* value);

void DynamicMachineTest2();

void DynamicMachineTest();

void printArraysOfStrings(Vector* arrays_of_strings, int indent_level);
void printArrayOfStrings(Vector* array_of_strings, int indent_level);
void printState(State* my_state, int indent_level);
int computeIndex(int offset, int state_name);

TrieTree* searchState1(
					TrieTree* my_trie_tree,
					Vector* name, // strings
					Vector* start_children,  // array of strings
					Vector* children, // array of strings
					Vector* next_states, // array of strings
					Data* value); // primitive

TrieTree* insertState1(
					TrieTree* my_trie_tree,
					Vector* name, // strings
					Vector* start_children,  // array of strings
					Vector* children, // array of strings
					Vector* next_states, // array of strings
					Data* value); // primitive

void printStateTrie(ContextualStateChart* my_dynamic_machine
// , string root
, int indent_level);

int computeIndex(int offset, int state_name);
void setupNeighbors( int* next_states, int state,
										int child_0, int child_1, 	int child_2, 	int child_3,
										int next_0, 	int next_1, 	int next_2, 	int next_3);

bool Empty(void* pointer);

// DynamicMachine* makeDynamicMachine(StateMachine* my_machine);

// StateMachine* setupMachine(int start_state, int end_state);




// int runState(StateMachine* machine, int start_of_next_states, void* object/*Scanner* my_scanner*/, int level);

	// we are going to recognize a context-sensitive grammer
	// a^nb^nc^n with 4 states without using text rewriting rules
	// each state is very clear on the expected sequence following it
	// there is no need for a hierarchy in the state structure
			// all we know is the variables are addressed by unique names

// (word##)
		// (#word#)
		// ()

		// (Im_a_word5)
		// (Im_a_word56)
		// (4Im_a_word5)
		// ()
// struct Tokens;

// struct TrieNode;

// can't group it like this
// need to think by letter than by word
// typedef only seems to let me use "ContextState" outside the struct definition

// typedef struct ContextState
// {
// 		char* name;
// 		struct TrieNode* state_name;


// 		struct TrieNode* start_children;

// 		// for the language input tree
// 		struct ContextState** parents;


// 		//char** parents_names;
// 		int parents_size;

// 		struct TrieNode* parents_;


// 		// no recursion, have an indent on/off var in the stack
// 		// when the child state is at a higher level than the current state
// 			// deactivate the indent
// 		// use last indent on/off value to find out if indents should be on or off
// 		// (current state, prev item on stack, is_indent_on)

// 		// for the language input tree
// 		struct ContextState** children;


// 		//char** children_names;
// 		int children_size;

// 		struct TrieNode* children_;

// 		// can't delete this yet
// 		// for the language input tree
// 		struct ContextState** nexts;

// 		struct TrieNode* nexts_;

// 		// tri tree for partial state name matches(can match only 1 name at a time)
// 		//struct TrieNode* tri_children;

// 		// the next level from name's perspective

// 		// when parts of a full name are linked to a context state object
// 		// the context state object may be a dummy node
// 		//bool dummy_node;

// 		// can only be a function state or a data state
// 		bool (*function_pointer)(struct ContextState* state);
// 		char* function_pointer_name;

// 		Data* var_data;
// 		int context_id;  // each context is enumerated
		
// 		// used by visitor function
// 		// set in parser
// 		bool start_children_are_parallel;
// 		bool nexts_are_parallel;
// 		bool is_start_child;
// 		bool is_child;
// 		bool is_parent;
// 		bool is_start_state;
// 		bool is_end_state;
// 		bool is_data_state;

// 		// set in visitor
// 		bool is_visited;
// 		int total_start_children_who_failed;

// 		// set by an api the state function uses
// 		char* debugging_log;

// }ContextState;
Data* DataInitDataInt(int a);

Data* DataInitDataFloat(float a);

// Data* DataInitDataString(string a);
void DataDeleteData(Data* variable);

Data* DataInitDataVector(Vector* container);
void DataDeleteDataVector(Data* variable);




// ContextState* initContextState();
// void printContextState2(ContextState* node);
// int isMatch(char* ith_word, struct TrieNode* node);

// struct TrieNode* appendNode(struct TrieNode* node, char* ith_name);
// void addToTrie(struct TrieNode* root, ContextState* state);
// char* lispNodeType(int type_value);

// char* copyString(char* b);

// void printData(Data* var_data, int indent_level);
// void printTrieNodeTree(struct TrieNode* root, int indent);
// void printContextState(ContextState* node);
// void printTrieNodes(struct TrieNode* trie_node_sequence);
// void printTrieNodeTreeFlat(struct TrieNode* root);
// ContextState* duplicate(ContextState* item);
// ContextState* initContextState();
// ContextState* makeContextState(/*int* i, jsmntok_t tokens[], const char* input*/struct Tokens* my_tokens, int token_count);

// int countTabs(char* input, int i);
// void swap(int* a, int* b);
// int countLines(char* input);


// //////
// char* getNextWord(char* input, int i);
// // char* collectChars(jsmntok_t token, const char* input);


// ContextState* makeFullContextState2(
// 	struct TrieNode* name,
// 	struct TrieNode* nexts,
// 	struct TrieNode* start_children,
// 	struct TrieNode* children,
// 	char* function_name,
// 	Data* variable_from_json_dict,
// 	struct TrieNode* parents,
// 	bool (*function_pointer)(struct ContextState* state),
// 	bool start_children_are_parallel,
// 	bool nexts_are_parallel,
// 	bool is_start_child,
// 	bool is_child,
// 	bool is_parent,
// 	bool is_start_state,
// 	bool is_end_state,
// 	bool is_data_state);

// ContextState* makeFullContextState(
// 	struct TrieNode* name,
// 	struct TrieNode* nexts,
// 	struct TrieNode* start_children,
// 	struct TrieNode* children,
// 	char* function_name,
// 	Data* variable_from_json_dict,
// 	struct TrieNode* parents,
// 	bool start_children_are_parallel,
// 	bool nexts_are_parallel,
// 	bool is_start_child,
// 	bool is_child,
// 	bool is_parent,
// 	bool is_start_state,
// 	bool is_end_state,
// 	bool is_data_state);
// void deleteContextState(ContextState* node);
void ContextualStateChartTest();

#endif
