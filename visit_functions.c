#include "state.h"
//#include "states.h"
#include "visit_functions.h"
#include "hash_table.h"
level_id_state_id* ht_search2(state_x_y_hash_table* ht, struct Names* key);
struct Names** getNexts(struct ContextState* state);
struct ContextState* getState(struct SparseMatrix* levels, level_id_state_id* point);
struct Names** getParents(struct ContextState* state);
struct Names** getStartChildren(struct ContextState* state);
struct Names** getNexts(struct ContextState* state);


int getParentsSize(struct ContextState* state);
int getStartChildrenSize(struct ContextState* state);
int getNextsSize(struct ContextState* state);


struct Names* getName(struct ContextState* state);
int getStartChildrenSize(struct ContextState* state);

void setNames(struct ContextState* state, struct Names* names);

bool runFunction(struct ContextState* state, struct SparseMatrix* levels, struct Names* current_state_name);

struct ContextState* makeNewState();

level_id_state_id* newPoint(int level_id, int state_id);

void ht_insert2(state_x_y_hash_table* ht, struct Names* key, level_id_state_id* value);



struct NextStatesPackage* getNextStates(struct ChildParent* tracker,
										struct Names** continuing_next_states,
										int size_of_continuing_next_states,
										int indents,
										state_x_y_hash_table* 	state_x_y_table,
                                        struct SparseMatrix* levels)
{

	// bottom[0], next_states, indents, graph
	// bottom of stack,
	//print(tracker.parent, tracker.child)
	struct NextStatesPackage* return_package = malloc(sizeof(struct NextStatesPackage));
	return_package->bottom_of_shortened_stack = tracker;
	return_package->next_states = continuing_next_states;
	return_package->next_states_size = size_of_continuing_next_states;
	return_package->indents = indents;
	struct Names* state = return_package->bottom_of_shortened_stack->child;
	//state1 = tracker.child[0]
	//case1 = tracker.child[1]

	// todo: need to delete the bottom of the list as we ascend it, not ignore it
	// for python tracker.parent is to what javascript is to tracker
	// not at root of stack and current level of the machine has been finished
	while (return_package->bottom_of_shortened_stack->parent != NULL && return_package->next_states_size == 0)
	{
		indents -= 1;
		return_package->bottom_of_shortened_stack = return_package->bottom_of_shortened_stack->parent;
		state = return_package->bottom_of_shortened_stack->child;
		//state1 = tracker.child[0]
		//case1 = tracker.child[1]
		// need to exit the main loop
		if(strcmp(state->strings[0], "root") == 0  && strcmp(state->strings[1], "0") == 0)
		{
			return_package->next_states = NULL;
			return_package->next_states_size = 0;
			return return_package;
			//return [tracker, [], indents]

		}

		// get point of state
		level_id_state_id* state_location = ht_search2(state_x_y_table, state);

		return_package->next_states = getNexts(getState(levels, state_location));

		//continuing_next_states = [list(a) for a in graph['node_graph2'][state1]['next'][case1].items()]

	}


	return return_package;
	//return [tracker, continuing_next_states, indents]
}

bool isParent(int maybe_parent)
{
	//printf("entering isParent\n");
	// does this node contain any children names?
	return maybe_parent > 0;
}

bool isBottomAtTheParentOfCurrentState(struct Names** 			parents,
									   int 						num_parents,
									   struct Names* 			bottom_state,
									   state_x_y_hash_table* 	state_x_y_table)
{
	//printf("entered isBottomAtTheParentOfCurrentState\n");
	for(int i = 0; i < num_parents; i++)
	{
		level_id_state_id* ith_parent_point 	= 	ht_search2(state_x_y_table, parents[i]);
		level_id_state_id* bottom_state_point 	= 	ht_search2(state_x_y_table, bottom_state);
		//printf("got here\n");
		//printf("%s, %s\n", parents[i]->strings[0], parents[i]->strings[1]);
		//printf("%s, %s\n", bottom_state->strings[0],  bottom_state->strings[1]);

		//printf("%i, %i\n", ith_parent_point->level_id, ith_parent_point->state_id);
		//printf("%i, %i\n", bottom_state_point->level_id, bottom_state_point->state_id);

		if(ith_parent_point->level_id == bottom_state_point->level_id &&
		   ith_parent_point->state_id == bottom_state_point->state_id)
		{
			//printf("true exiting isBottomAtTheParentOfCurrentState\n");
			return true;
		}
	}
	//printf("false exiting isBottomAtTheParentOfCurrentState\n");
	return false;

}

bool hasParent(struct SparseMatrix* levels, level_id_state_id* point)
{
	//printf("entered hasParent\n");
    ;
	return getParentsSize(getState(levels, point)) > 0;
	//return len(graph['parents'][state][case_].keys()) > 0

}

void printStack2(struct ChildParent* bottom_tracker)
{
	printf("stack\n");
	struct ChildParent* bottom_tracker2 = bottom_tracker;
	// supposed to show the root but it's okay
	while(bottom_tracker2->parent != NULL)
	{
		for(int i = 0; i < bottom_tracker2->child->strings_size; i++)
		{
			printf("%s ", bottom_tracker2->child->strings[i]);
		}
		printf("|");
		bottom_tracker2 = bottom_tracker2->parent;
	}
	for(int i = 0; i < bottom_tracker2->child->strings_size; i++)
	{
		printf("%s ", bottom_tracker2->child->strings[i]);
	}
	printf("|\n");
}
void printNextStates(struct Names** next_states, int next_states_size)
{
	printf("next states\n");
	for(int i = 0; i < next_states_size; i++)
	{
		for(int j = 0; j < next_states[i]->strings_size; j++)
		{
			printf("%s ", next_states[i]->strings[j]);
		}
		printf("\n");
	}
}
void printCurrentState(struct Names* current_state_name)
{
	printf("\n\ncurrent state:\n");
	for(int i = 0; i < current_state_name->strings_size; i++)
	{
		printf("%s ", current_state_name->strings[i]);
	}
	printf("\n");
}
 struct Names* makeName2(char* name_1, char* name_2);

void visit(struct SparseMatrix* levels,
		   struct ContextState* start_node,
		   state_x_y_hash_table* state_x_y_table)
{

	// test by making each function do nothing but return true or false
	struct Names** next_states = malloc(sizeof(struct Names*));
	next_states[0] = getName(start_node);
	int next_states_size = 1;
	struct Names* current_state_name = getName(start_node);

	struct ChildParent* bottom = malloc(sizeof(struct ChildParent));
	//parent = ChildParent(['root', 0], None)
	bottom->child = malloc(sizeof(struct Names));  // make root
	bottom->child->strings = malloc(sizeof(char*));
	bottom->child->strings[0] = "root";
	bottom->child->strings[1] = "0";
	bottom->child->strings_size = 2;
	bottom->parent = NULL;
	struct ChildParent* bottom_tracker = bottom;
	// have to add to table
	//struct ContextState {
	//	struct Names* name;
	// so the root can be found in state_x_y_table in isBottomAtTheParentOfCurrentState
	struct ContextState* dummy_node = makeNewState();
    setNames(dummy_node, makeName2("root", "0"));

    //dummy_node->name = makeName2("root", '0');
	/*dummy_node->name = malloc(sizeof(struct Names));
	dummy_node->name->strings = malloc(sizeof(char*));
	dummy_node->name->strings[0] = "root";
	dummy_node->name->strings[1] = "0";
	dummy_node->name->strings_size = 2;
    */
	ht_insert2(state_x_y_table, getName(dummy_node), newPoint(-1, -1));

	// the stack is not getting hooked up properly
	int ii = 0;
	int indents = 0;

	while(next_states_size > 0)
	{
		if(ii == 5)
		{
			printf("too many states run\n");
			exit(1);

		}

		bool state_changed = false;

		int j = 0;
		while(j < next_states_size)
		{
			printCurrentState(current_state_name);
			current_state_name = next_states[j];

			// get point of current_state_name
			level_id_state_id* point = ht_search2(state_x_y_table, current_state_name);
            
			int maybe_parent = getStartChildrenSize(getState(levels, point));
			//printf("maybe_parent = %i", maybe_parent)
			//maybe_parent = graph['node_graph2'][ state ]['children'][ case_ ]
            //bool 
            
			bool did_function_pass = runFunction(getState(levels, point), levels, current_state_name);//levels[point->level_id].state_list[point->state_id]->function_pointer(current_state_name, levels);

			if(did_function_pass)
			{

				//printf("function passed\n");
				// what happens if it has a parent but has a child too?
				// did_function_pass = graph['node_graph2'][state]['functions'][case_]([state, case_], graph)
				if(hasParent(levels, point))
				{
					//printf("hasParent is true\n");
					/*
					bottom_state = bottom[0].child[0]
					bottom_case = bottom[0].child[1]
					*/
					struct Names* bottom_state = bottom_tracker->child;
					// struct Names** all_parents = parents of current state
                    
					struct Names** parents = getParents(getState(levels, point));
					int num_parents = getParentsSize(getState(levels, point));

					//parent_cases = [list(a) for a in graph['parents'][state][case_].items()]
					//if (isBottomAtTheParentOfCurrentState(parent_cases, bottom_state, bottom_case)):
					if(isBottomAtTheParentOfCurrentState(parents,
														 num_parents,
														 bottom_state,
														 state_x_y_table))
					 {
						struct ChildParent* new_parent = malloc(sizeof(struct ChildParent));
						//parent = ChildParent(['root', 0], None)

						new_parent->child = malloc(sizeof(struct Names));
						//new_parent->child->strings_size = 1;
						new_parent->child = current_state_name;
						new_parent->parent = bottom_tracker;   // now new_parent is behind bottom_tracker
						bottom_tracker = new_parent;
						//struct ChildParent* bottom_tracker2 = bottom_tracker;
						// supposed to show the root but it's okay

						//exit(1);
						indents++;
						/*new_parent = ChildParent([state, case_], bottom[0])
						# link passing state to its parent on bottom of stack, extending the stack by 1, vertically
						bottom[0] = new_parent
						indents += 1
						*/
						printCurrentState(current_state_name);

					 }

				}
				if(isParent(maybe_parent))
				{
					/*
					# add passing state horizontally
					bottom[0].child = [state, case_]

					# getting the children
					children = [list(a) for a in graph['node_graph2'][state]['children'][case_].items()]
					#print('next_states', children)
					children = makeNextStates(children)
					next_states = []
					for i, child in enumerate(children):

						next_states.append(children[i])
					*/

					//printf("isParent is true\n");


					bottom_tracker->child = current_state_name;
                    
					struct Names** start_children = getStartChildren(getState(levels, point));
					int start_children_size = getStartChildrenSize(getState(levels, point));
					// reset next_states and fill it with children
					next_states_size = start_children_size;
					free(next_states);
					next_states = malloc(sizeof(struct Names*) * start_children_size);
					for(int i = 0; i < start_children_size; i++)
					{
						next_states[i] = start_children[i];
					}

				}
				else
				{
					//printf("isParent is false\n");

					// x = (next_states)
					// x_total = (lowest_bottom, next_states, indent_number)
					// there is a problem with how dict_items is being used

					//print(graph['node_graph2'][state]['next'])
					//next_states = [list(a) for a in graph['node_graph2'][state]['next'][case_].items()]
                    
					struct Names** nexts = getNexts(getState(levels, point));
					int nexts_size = getNextsSize(getState(levels, point));
					// reset next_states and fill it with children
					next_states_size = nexts_size;
					free(next_states);
					next_states = malloc(sizeof(struct Names*) * nexts_size);
					for(int i = 0; i < next_states_size; i++)
					{
						next_states[i] = nexts[i];
					}

					//next_states = makeNextStates(next_states)
					//print('next_states', next_states)
					//if debug:
					//	m = graph['i']
					//	printLevelsBounds(graph, state, case_, indents, m, len(graph['input']), 0, -1)
					// add passing state horizontally
					//bottom[0].child = [state, case_]
					bottom_tracker->child = current_state_name;


				}

				state_changed = true;
				break;
			}

		}

		// print stack
		printf("state changed? %i", state_changed);
		printStack2(bottom_tracker);

		printNextStates(next_states, next_states_size);

		if (next_states_size == 0)
		{
			// x_total = (lowest_bottom, next_states, indent_number)

			// have linked list representing the stack
			// first item is in bottom[0]
			printf("time to shorten stack\n");
			struct NextStatesPackage* tracker_continuing_next_states_indents = getNextStates(
				/*struct ChildParent**/ 	bottom,
				/*struct Names***/ 			next_states,
				/*int*/ 					next_states_size,
				/*int*/ 					indents,
				/*state_x_y_hash_table**/ 	state_x_y_table,
                /*struct SparseMatrix**/ 	levels);

			next_states = tracker_continuing_next_states_indents->next_states;
			indents = tracker_continuing_next_states_indents->indents;
			bottom = tracker_continuing_next_states_indents->bottom_of_shortened_stack;
			bottom_tracker = bottom;
			// travel up stack untill either hits root or hits neighbors of a prev visited level
			//tracker_continuing_next_states_indents = getNextStates(bottom[0], next_states, indents, graph)
			//print(tracker_continuing_next_states_indents)

			/*tracker = tracker_continuing_next_states_indents[0]
			continuing_next_states = tracker_continuing_next_states_indents[1]
			indents = tracker_continuing_next_states_indents[2]


			bottom[0] = tracker
			next_states = continuing_next_states
			*/
			//print('next_states 5', next_states)

			/*state_changed = True*/
			// might not actually be true ever
			//'''
			/*
			if (tracker == null)
				console.log('done runing machine')
			*/
			//'''

			printStack2(bottom_tracker);
			printNextStates(next_states, next_states_size);

		}

		// if all fail then all will be rerun unless this condition is here
		if(!state_changed && next_states_size > 0)
		{
			// all next_states failed so this level cannot be finished
			// travel up like before but choose the next child after the tracker

			printf("error at ");
			//printf(getIndents(indents), next_states, "on");
			level_id_state_id* point = ht_search2(state_x_y_table, current_state_name);

			//printf(getIndents(indents), '('+  '\'' + current_state_name + '\'' + ',' , case_ + ',', "f=" +
			//	   levels[point->level_id].state_list[point->state_id]->function_name + ',', str(indents) + ')');
			break;

			//print(next_states, 'have failed so your state machine is incomplete')
			//exit()
		}

		//if(not state_changed):
		//	print("we are screwed", len(next_states))
		ii += 1;


	}
	printf("state machine is done\n");
}