#ifndef STATE_MACHINE
#define STATE_MACHINE
#include "standard_headers.h"

typedef struct State
{
	int state_id;
	bool (*function)(void*);
}State;
typedef struct StateMachine
{
	int* next_states;
	int current_state;
	int max_neighbors;
	int next_states_size;
	int ith_recursive_call;
	int error_state;
	int end_state;
	int number_of_states_per_level;
	int level_number;
	int first_neighbor_to_test;
	int* parent_status;
	vector<string>* state_names_strings;
	vector<string>* function_names;
	int number_of_states;

	// idea for making a contextual state chart using C
	// current state / number_of_next_states_per_level = level_id

}StateMachine;

// assume the current state is set to 0
StateMachine* stateMachine(int* next_states,
						   int size,
						   int max_neighbors,
						   vector<string>* state_names_strings,
						   int number_of_strings,
						   int* parent_status,
						   vector<string>* function_names);

// all next states are not NULL state
bool keepGoing(StateMachine* machine);
// move current state forward to state that passed
bool updateCurrentState(StateMachine* machine, int winning_state);
StateMachine* addRecursiveCall(StateMachine* machine);
StateMachine* removeRecursiveCall(StateMachine* machine);
bool destroyMachine(StateMachine* machine);
bool testStateMachine(StateMachine* machine);
void prinState(StateMachine* machine);
int getFirstChild(StateMachine* machine, int winning_state);

int getFirstNextStates(StateMachine* machine, int winning_state);

void runMachine(StateMachine* machine, void* object/*Scanner* my_scanner*/, int level, int* counter);

// construction, destruction, tests(not from input files) docstrings for functions and structs, translation
// standard solutions
// new files, same function names
/*
setup_bin_search
	next
		sanity_checks. (before_first | after_last | middle)
sanity_checks
	next
		(before_first | after_last | middle_setup)
before_first
after_last
middle_setup
	next
		middle. (before_mid | after_mid | match)
	function
		setupForMiddle(sanity check and can we keep going)
middle
	next
		(before_mid | after_mid | match)
	function
		none
before_mid
	next
		middle. (before_mid | after_mid | match)
	function
		updateBeforeMid
after_mid
	next
		middle. (before_mid | after_mid | match)
	function
		updateAfterMid
match
	next
		(end_of_perfect_match | target_chain_has_more_words | can_keep_matching | no_more_matching)
end_of_perfect_match
target_chain_has_more_words
can_keep_matching
	next
		middle
no_more_matching

setup_bin_search:  				sanity_checks,			null, 							null, 				null
sanity_checks: 					before_first, 			after_last,						middle_setup, 		null
before_first:					null, 					null, 							null, 				null
after_last:						null, 					null, 							null, 				null
middle_setup: 					middle, 				null, 							null, 				null
middle:							before_mid, 			after_mid, 						match, 				null
before_mid: 					middle, 				null, 							null, 				null
after_mid: 						middle, 				null, 							null, 				null
match: 							end_of_perfect_match, 	target_chain_has_more_words, 	can_keep_matching, 	no_more_matching
end_of_perfect_match:			null, 					null, 							null, 				null
target_chain_has_more_words:	null, 					null, 							null, 				null
can_keep_matching: 				middle, 				null, 							null, 				null
no_more_matching:				null, 					null, 							null, 				null

current_state = setup_bin_search
max_neighbors = 4
*/
#endif