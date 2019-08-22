#include "state_machine.h"

/*
typedef struct StateMachine
{
	int* next_states;
	int current_state;
	int max_neighbors;
	int next_states_size;
	int ith_recursive_call;
	int error_state;
}StateMachine;

*/
enum test_machine_state_names{
	error,
	setup_bin_search,
	sanity_checks,
	before_first,
	after_last,
	middle_setup,
	middle,
	before_mid,
	after_mid,
	match,
	end_of_perfect_match,
	target_chain_has_more_words,
	can_keep_matching,
	no_more_matching,
	done
};

/*
char* test_machine_state_names_strings[] = {
	"error"
	,
	"setup_bin_search",
	"sanity_checks",
	"before_first",
	"after_last",
	"middle_setup",
	"middle",
	"before_mid",
	"after_mid",
	"match",
	"end_of_perfect_match",
	"target_chain_has_more_words",
	"can_keep_matching",
	"no_more_matching",
	"done"
	

};
*/
// error field and end state field can't be the same
int test_machine_next_states[] = {
/*  error field  				*/	error, 					error, 							error, 				error,
/*  setup_bin_search  			*/  sanity_checks,			error, 							error, 				error,
/*  sanity_checks  				*/ 	before_first, 			after_last,						middle_setup, 		error,
/*  before_first  				*/	error, 					error, 							error, 				error,
/*  after_last  				*/	error, 					error, 							error, 				error,
/*  middle_setup  				*/ 	middle, 				error, 							error, 				error,
/*  middle  					*/	before_mid, 			after_mid, 						match, 				error,
/*  before_mid  				*/ 	middle, 				error, 							error, 				error,
/*  after_mid 					*/ 	middle, 				error, 							error, 				error,
/*  match 						*/ 	end_of_perfect_match, 	target_chain_has_more_words, 	can_keep_matching, 	no_more_matching,
/*  end_of_perfect_match  		*/	error, 					error, 							error, 				error,
/*  target_chain_has_more_words	*/	error, 					error, 							error, 				error,
/*  can_keep_matching  			*/ 	middle, 				error, 							error, 				error,
/*  no_more_matching  			*/	error, 					error, 							error, 				error,
/*  done 						*/  error, 					error, 							error, 				error
};
// this will be called from inside the objects using a state machine
StateMachine* stateMachine(int* next_states,
						   int size,
						   int max_neighbors,
						   vector<string>* state_names_strings,
						   int number_of_strings,
						   int* parent_status,
						   vector<string>* function_names)
{
	if(next_states != NULL)
	{
		StateMachine* new_machine = (StateMachine*) malloc(sizeof(StateMachine));
		new_machine->next_states = (int*) malloc(sizeof(int) * size);
		memcpy(new_machine->next_states, next_states, sizeof(int) * size);
		new_machine->next_states_size = size;
		new_machine->max_neighbors = max_neighbors;
		new_machine->current_state = 1;
		new_machine->error_state = 0;
		//new_machine->end_state = end_state;
		new_machine->level_number = 1;

		new_machine->ith_recursive_call = 0;
		new_machine->first_neighbor_to_test = max_neighbors + max_neighbors;
		new_machine->state_names_strings = state_names_strings;//(char**) malloc(sizeof(char*) * number_of_strings);

		//memcpy(new_machine->state_names_strings, state_names_strings, sizeof(char*) * number_of_strings);

		new_machine->function_names = function_names;//(char**) malloc(sizeof(char*) * number_of_strings);

		//memcpy(new_machine->function_names, function_names, sizeof(char**) * number_of_strings);



		new_machine->parent_status = (int*) malloc(sizeof(int) * number_of_strings);

		memcpy(new_machine->parent_status, parent_status, sizeof(int) * number_of_strings);

		return new_machine;

	}
	return NULL;
}

bool keepGoing(StateMachine* machine)
{
	/*
    trying out_of_lines
	one_line_two_2
	|one_line_two_2|
	can keep going
	counter 6
	trying children
	current state out_of_lines
	offset 0
	i 72
	    trying error
	    trying error
	    trying error
	    trying error
	the below states failed

	   error
	   error
	   error
	   error

	*/
	//printf("in keep going\n");
	if(machine != NULL)
	{
		int current_state = machine->current_state;
		// the # of children tried must equal the 3 of next states tried
		int max_neighbors = machine->max_neighbors;
		//printf("max neighbors %i\n", max_neighbors);
		// go to start of next states for current_state
		// worked all the other times, except the last time
		int i = machine->first_neighbor_to_test;

		//int i = (current_state * (max_neighbors + max_neighbors)) + max_neighbors;
		//printf("current state %i\n", current_state);
		//printf("start of keep going %i\n", i);

		//printf("%i\n", machine->next_states[ (max_neighbors * 2 ) * current_state ]);
		//printf("%i\n", machine->next_states[ i ]);

		//printf("%s\n", machine->state_names_strings[ current_state ]);
		//printf("%s\n", machine->state_names_strings[ machine->next_states[ i ] ]);
		
		// for checking the end of the machine we check the next states
		for(int j = 0; j < max_neighbors; j++)
		{
			//printf("|%s|\n", machine->state_names_strings[ machine->next_states[i + j] ]);
			if(machine->next_states[i + j] != error)
			{
				//printf("can keep going\n");
				//exit(1);
				return true;
			}
		}
		//exit(1);
		// if all next states are error
			// return true
		//printf("%i, %i\n", machine->current_state, machine->end_state);
		return false;//machine->current_state != machine->end_state;
	}
	return false;
	
}
// move current state forward to state that passed
bool updateCurrentState(StateMachine* machine, int winning_state)
{
	if(machine != NULL)
	{

		
		//printf("%i, %i, level %i\n", winning_state, machine->number_of_states_per_level, machine->level_number);
		machine->current_state = winning_state;
	}
	return 0;
}

StateMachine* addRecursiveCall(StateMachine* machine)
{
	if(machine != NULL)
	{
		machine->ith_recursive_call++;
		return machine;
	}
	return 0;
}
StateMachine* removeRecursiveCall(StateMachine* machine)
{
	if(machine != NULL)
	{
		machine->ith_recursive_call--;
		return machine;
	}
	return 0;
}
bool destroyMachine(StateMachine* machine)
{
	if(machine != NULL)
	{
		machine->next_states = NULL;
		machine->current_state = 0;
		machine->max_neighbors = 0;
		machine->next_states_size = 0;
		machine->ith_recursive_call = 0;
		machine->error_state = 0;
		return true;
	}
	return false;
}
void prinState(StateMachine* machine)
{

	printf("current state %s\n", machine->state_names_strings->at(machine->current_state).c_str());
}
bool testStateMachine(StateMachine* machine)
{
	if(machine != NULL)
	{
		// machine is finished the moment the current state == done
		while(keepGoing(machine))
		{
			// loop all next states and try them
			int current_state = machine->current_state;
			int max_neighbors = machine->max_neighbors;

			// go to start of next states for current_state
			int i = current_state * max_neighbors;


			for(int j = 0; j < max_neighbors; j++)
			{
				bool state_changed = false;
				int winning_state = 0;
				switch(machine->next_states[i + j])
				{
					case error:
					{
						printf("can't advance\n");
						exit(1);
					}
					case setup_bin_search:
					{
						winning_state = setup_bin_search;
						state_changed = true;
						break;
					}
					case sanity_checks:
					{
						winning_state = sanity_checks;
						state_changed = true;

						break;
					}
					case before_first:
					{
						winning_state = before_first;
						state_changed = true;

						break;
					}
					case after_last:
					{
						winning_state = after_last;
						state_changed = true;

						break;
					}
					case middle_setup:
					{
						winning_state = middle_setup;
						state_changed = true;

						break;
					}
					case middle:
					{
						winning_state = middle;
						state_changed = true;

						break;
					}
					case before_mid:
					{
						winning_state = before_mid;
						state_changed = true;

						break;
					}
					case after_mid:
					{
						winning_state = after_mid;
						state_changed = true;

						break;
					}
					case match:
					{
						winning_state = match;
						state_changed = true;

						break;
					}
					case end_of_perfect_match:
					{
						winning_state = end_of_perfect_match;
						state_changed = true;

						break;
					}
					case target_chain_has_more_words:
					{
						winning_state = target_chain_has_more_words;
						state_changed = true;

						break;
					}
					case can_keep_matching:
					{
						winning_state = can_keep_matching;
						state_changed = true;

						break;
					}
					case no_more_matching:
					{
						winning_state = no_more_matching;
						state_changed = true;

						break;
					}
					case done:
					{
						// here for completion only

					}
					default:
					{
						break;
					}
				}
				if(state_changed)
				{
					updateCurrentState(machine, winning_state);

					break;
				}
			}
		}



		return true;
	}
	return false;
}
int runStates(StateMachine* machine, int start_of_next_states, void* object/*Scanner* my_scanner*/, int level);

int getFirstChild(StateMachine* machine, int winning_state)
{
	return winning_state * (2 * machine->max_neighbors);
}
int getFirstNextStates(StateMachine* machine, int winning_state)
{
	return getFirstChild(machine, winning_state) + machine->max_neighbors;
}

void runMachine(StateMachine* machine, void* object/*Scanner* my_scanner*/, int level, int* counter)
{
	//int counter = 0;
	machine->first_neighbor_to_test = getFirstChild(machine, machine->current_state);

	// quitting machine if this is false
	while(keepGoing(machine))
	{
		
		// failing at 455
		// last working time is 950
		//printf("%i\n", counter);
		// 304
		/*
		if(counter == 310)
		{
			printf("ran too many states\n");

			exit(1);
		}
		*/
		//printf("counter %i\n", *counter);
		int current_state = machine->current_state;
		// loop all next states and try them
		// if there are children to run
		// run children
		// (machine->current_state * (machine->max_neighbors + machine->max_neighbors)) + offset_to_next
		int winning_state = runStates(machine,
								  machine->first_neighbor_to_test,
							 	  object,
							 	  level);

		bool success = false;
		if(winning_state)
		{
			//printf("%s%s (f=%s)\n", makeSpaces(level).c_str(), machine->state_names_strings->at(winning_state).c_str(), machine->function_names->at(winning_state).c_str());

			updateCurrentState(machine, winning_state);

			if(machine->parent_status[winning_state])
			{

				machine->first_neighbor_to_test = getFirstChild(machine, winning_state);
				//printf("running children\n");
				if(keepGoing(machine))
				{
					/*success = */runMachine(machine, object, level + 3, counter);
					//printf("running next states after submachine %i\n", success);

				}

			}
			
			machine->first_neighbor_to_test = getFirstNextStates(machine, winning_state);
		}
		/*else if(!winning_state && machine->next_states[location_of_first_next_states] == empty)
		{
			return false;
		}*/
		else if(!winning_state && machine->next_states[machine->first_neighbor_to_test] != 0/*empty*/)
		{
			printf("the below states failed\n\n");
			for(int k = 0; k < machine->max_neighbors; k++)
			{
				printf("   %s\n", machine->state_names_strings->at( machine->next_states[machine->first_neighbor_to_test + k] ).c_str() );
			}
			exit(1);
			//return false;
		}

		
		(*counter)++;
	}
	//return true;

}