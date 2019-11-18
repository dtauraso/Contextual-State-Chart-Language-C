#ifndef STATE3
#define STATE3
#include <stdbool.h>
#include "stdlib.h"
#include <stdio.h>
#include <string.h>
#include "trie_node.h"
// #include "multiway_lines_node.h"
#include "vector.h"
#include "trie_tree.h"
#include <map>
#include <set>
//#include "state_machine.h"
struct StateMachine;


typedef struct Search
{
	int start;
	int end;
	int mid;
	int comparison_type;
	Vector* container;

}Search;
Search* initSearch();

typedef struct Insert
{
	struct Search* my_search;
}Insert;
Insert* initIners();

typedef struct Delete
{
	struct Search* my_search;
}Delete;
Delete* initDelete();

//enum stack_types{char_p_p, struct_context_state_p_p};
typedef struct Data
{
	int type_id; // enum
	/*
	0 => int
	1 => string
	2 => float
	3 => Vector
	*/
	int _int;

	string _string;
	
	int string_size;

	float _float;

	Vector* container;
	int vector_type_id;
	int container_nesting_level;


}Data;


/*
only made the top level points logn searchable
the lower level points in the state graph are logn searchable
all nodes must be partial matchable
*/
/*
partial matchable(trie)
each state name can contain the same string (children names are unique by id)
all searching must be logn(multimap and map)

*/
/*
multimap<string, ExtendedState*>* and map<string, int>* next_next_contexts provide the trie tree, logn,
int id in each ExtendedState* provides the unique string, ExtendedState* entries in the multimap

int max_id_for_siblings is to prevent the id of each state to be used for the id's of the state's links

also, the chldren must be accessible at random, from an index.  This calls for an ordered dict.


id in DynamicState is so each state is enumerated.  this allows for the next contex name to be string(id) when autogenerating unique id's for adding the same state to the graph.  The same state will be used differently, so they all must be enumerated and the user shouldn't have to know the state name at the context dimention of enumeration
new_state_name1 = add("name") => saves as "name"
new_state_name2 = add("name") => saves as "name", "0"
new_state_name2 = some_state.addChild("name") => saves as "name", "1"
searchChildrenFor(some_state, "name") => "name", "1" as a correct match
should work because we are looking at the children of some_state so only within that child context is "name", ... being searched for


user should only have to use part of the name to search for it, all relevant variations will be returned. there should only be as many varaitions as the user expects from the data structure
*/

// It's okay if it's O(n^2) where n is the number of parts of the state name and the links
// search = O(nlog(m))
// modify = O(1) ; assume item was already found by search

// add = O(n)
// delete = O(nm) ; where m is the number of items being shifted

// size = O(n)

/*
Vector strings for array
Vector trienodes for dict
bool type of container

*/



typedef struct DynamicMachine
{

	Vector* states;
	TrieTree* state_names;
	// root is position 0



}DynamicMachine;
enum container_types {array, trie_tree};
typedef struct DynamicState
{
	Vector* name;
	bool is_start_child;
	bool has_down_links;
	
	Vector* parents;
	// TrieTree* _parents;
	
	Vector* start_children;

	// OrderedDict* _start_children;

	Vector* children;
	TrieTree* _children;

	Vector* next_states;


	// OrderedDict* _next_states;

	Data* value;
	// -1 == NULL
	// 0 == array
	// 1 == trie tree
	int container_type;
	// int level_number;
	string function_name;
	bool (*function) (DynamicMachine* my_machine, DynamicState* parent_state, DynamicState* current_state);
	// bool parent_status;
	// int max_id_for_siblings; // so the max id of machine doesn't grow too fast
	// int id;
	// this part is not the trie tree part
	// ith value in |name|th level, so all states are enumerated with respect to the deepest context dimention they are in(not numbered, but when they are numbered and how many siblings they have)
	//remaining items for the asyncronous nfa evaluator state machine

}DynamicState;


// dynamic state funcitons
DynamicState* DynamicStateInitDynamicState(	Vector* name, // strings
								Vector* parents,  // array of strings
								Vector* start_children,  // array of strings
								Vector* children, // array of strings
								Vector* next_states, // array of strings
								bool (*function) (	DynamicMachine* my_machine,
													DynamicState* parent_state,
													DynamicState* current_state));

DynamicState* DynamicStateInitDynamicState2(	Vector* name, // strings
								bool is_start_child,
								bool has_down_links,
								Vector* parents,  // array of strings
								Vector* start_children,  // array of strings
								Vector* children, // array of strings
								Vector* next_states, // array of strings
								bool (*function) (	DynamicMachine* my_machine,
													DynamicState* parent_state,
													DynamicState* current_state));

// dynamic machine functions
// final 2 structs for trie ordered dict
void TrieTreeInsertString(TrieTree* my_trie_tree, string element);




DynamicMachine* DynamicMachineInitDynamicMachine();
Vector* DynamicMachineAppendState(DynamicMachine* my_machine, DynamicState* state);

bool recordA(DynamicMachine* my_machine, DynamicState* parent_state, DynamicState* current_state);
bool returnTrue(DynamicMachine* my_machine, DynamicState* parent_state, DynamicState* current_state);
bool returnATrueValue(DynamicMachine* my_machine, DynamicState* parent_state, DynamicState* current_state);

DynamicState* DynamicMachineRunStates(DynamicMachine* my_machine, Vector* state_names);

DynamicState* DynamicStateMakeVariable(	string variable_name,
										Vector* parents,  // array of strings
										Data* value);

DynamicState* DynamicStateMakeVariable2(string variable_name,
										Vector* parents,  // array of strings
										Data* value);

void DynamicMachineTest2();

void DynamicMachineTest();

void printArraysOfStrings(Vector* arrays_of_strings, int indent_level);
void printArrayOfStrings(Vector* array_of_strings, int indent_level);
void printState(DynamicState* my_state, int indent_level);
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

void printStateTrie(DynamicMachine* my_dynamic_machine, string root, int indent_level);

int computeIndex(int offset, int state_name);
void setupNeighbors( int* next_states, int state,
										int child_0, int child_1, 	int child_2, 	int child_3,
										int next_0, 	int next_1, 	int next_2, 	int next_3);

bool Empty(void* pointer);

DynamicMachine* makeDynamicMachine(StateMachine* my_machine);

StateMachine* setupMachine(int start_state, int end_state);




int runState(StateMachine* machine, int start_of_next_states, void* object/*Scanner* my_scanner*/, int level);


struct Tokens;

struct TrieNode;

// can't group it like this
// need to think by letter than by word
// typedef only seems to let me use "ContextState" outside the struct definition

typedef struct ContextState
{
		char* name;
		struct TrieNode* state_name;


		struct TrieNode* start_children;

		// for the language input tree
		struct ContextState** parents;


		//char** parents_names;
		int parents_size;

		struct TrieNode* parents_;


		// no recursion, have an indent on/off var in the stack
		// when the child state is at a higher level than the current state
			// deactivate the indent
		// use last indent on/off value to find out if indents should be on or off
		// (current state, prev item on stack, is_indent_on)

		// for the language input tree
		struct ContextState** children;


		//char** children_names;
		int children_size;

		struct TrieNode* children_;

		// can't delete this yet
		// for the language input tree
		struct ContextState** nexts;

		struct TrieNode* nexts_;

		// tri tree for partial state name matches(can match only 1 name at a time)
		//struct TrieNode* tri_children;

		// the next level from name's perspective

		// when parts of a full name are linked to a context state object
		// the context state object may be a dummy node
		//bool dummy_node;

		// can only be a function state or a data state
		bool (*function_pointer)(struct ContextState* state);
		char* function_pointer_name;

		Data* var_data;
		int context_id;  // each context is enumerated
		
		// used by visitor function
		// set in parser
		bool start_children_are_parallel;
		bool nexts_are_parallel;
		bool is_start_child;
		bool is_child;
		bool is_parent;
		bool is_start_state;
		bool is_end_state;
		bool is_data_state;

		// set in visitor
		bool is_visited;
		int total_start_children_who_failed;

		// set by an api the state function uses
		char* debugging_log;

}ContextState;
Data* DataInitDataInt(int a);

Data* DataInitDataFloat(float a);

Data* DataInitDataString(string a);
void DataDeleteData(Data* variable);

Data* DataInitDataVector(Vector* container);
void DataDeleteDataVector(Data* variable);




ContextState* initContextState();
void printContextState2(ContextState* node);
int isMatch(char* ith_word, struct TrieNode* node);

struct TrieNode* appendNode(struct TrieNode* node, char* ith_name);
void addToTrie(struct TrieNode* root, ContextState* state);
char* lispNodeType(int type_value);

char* copyString(char* b);

void printData(Data* var_data, int indent_level);
void printTrieNodeTree(struct TrieNode* root, int indent);
void printContextState(ContextState* node);
void printTrieNodes(struct TrieNode* trie_node_sequence);
void printTrieNodeTreeFlat(struct TrieNode* root);
ContextState* duplicate(ContextState* item);
ContextState* initContextState();
ContextState* makeContextState(/*int* i, jsmntok_t tokens[], const char* input*/struct Tokens* my_tokens, int token_count);

int countTabs(char* input, int i);
void swap(int* a, int* b);
int countLines(char* input);


//////
char* getNextWord(char* input, int i);
char* collectChars(jsmntok_t token, const char* input);


ContextState* makeFullContextState2(
	struct TrieNode* name,
	struct TrieNode* nexts,
	struct TrieNode* start_children,
	struct TrieNode* children,
	char* function_name,
	Data* variable_from_json_dict,
	struct TrieNode* parents,
	bool (*function_pointer)(struct ContextState* state),
	bool start_children_are_parallel,
	bool nexts_are_parallel,
	bool is_start_child,
	bool is_child,
	bool is_parent,
	bool is_start_state,
	bool is_end_state,
	bool is_data_state);

ContextState* makeFullContextState(
	struct TrieNode* name,
	struct TrieNode* nexts,
	struct TrieNode* start_children,
	struct TrieNode* children,
	char* function_name,
	Data* variable_from_json_dict,
	struct TrieNode* parents,
	bool start_children_are_parallel,
	bool nexts_are_parallel,
	bool is_start_child,
	bool is_child,
	bool is_parent,
	bool is_start_state,
	bool is_end_state,
	bool is_data_state);
void deleteContextState(ContextState* node);

#endif
