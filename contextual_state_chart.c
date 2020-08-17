#include "contextual_state_chart.h"
#include "balanced_tree_node.h"
/*
init state
init state async merge
init state children and/or next states are async
init variablePrimitive
init variableDictionary
init variableOtherDataStructure
add state
delete state
get state value
set state value
search for state
search for neighbors
print machine
evaluator(dfa with setup data structues for nfa)
tracking system for array manipulations
hierarchy for the log

*/
// #include "state_machine.h"
// #include "vector.h"
// #include "trie_tree.h"
//#include "jsmn/jsmn.h"

// typedef struct State
// {
// 	// This state can be multiple things:
// 	// control flow node
// 	// primitive value
// 	// dictionary
// 	// root for any other data structure
// 	Vector* name;

// 	// operating system stuff
// 	// https://www.enterpriseintegrationpatterns.com/docs/IEEE_Software_Design_2PC.pdf
// 	// Don't run the state untill this value == 0.
// 	// This is for when asynchronous timelines merge into a synchronous timeline
// 	// assume 2 different asynchronous states will try this state at the same time
// 	int threshold;

// 	// run state if visit_count == threshhold in 1 pass of trying next states from all timelines
// 	int visit_count;
	
// 	// lets us quickly check if the state's parent is actually the same one as the parent of the timeline
// 	// prevents us from having a timeline try states(more than 1 in a row at the time of crossover) in a different timeline before the other
// 	// timeline tries it
// 	// keep all asynchronous timelines separated even if they visit a state from another timeline
// 	TrieTree* parents;


// 	// preventing timeline stalls
// 	// if we assume this state represents a parent on a timeline
// 	// then we can time how long it takes for the submachine to finish
// 	// if the duration > 1 second kill the state(curent state) and all parent states in the timeline
// 	// exclucding the root state as the root may host more than 1 timeline
// 	int duration;

// 	bool children_are_parallel_states;
// 	Vector* children;

// 	bool next_states_are_parallel_states;
// 	Vector* next_states;


// 	// for copying up saved items after the current submachine is finished
// 	bool is_copied_up_hierarchy;
// 	Vector* destination_state_parent_name;
// 	// whatever data is in the higher level variable name we will overwrite with the data from the lower level



// 	// for when this state represents a dictionary
// 	TrieTree* keys;

// 	bool is_dictionary;
// 	bool is_primitive;
// 	bool is_other_data_structure;
// 	bool is_control_flow_node;


// 	// for when the state is storing a primitive value
// 	Data* value;

// 	// modification flags for the recording user changes system
// 	bool is_added;
// 	bool is_deleted;
// 	bool is_modified;


// 	Vector* function_name;
// 	bool (*function) (ContextualStateChart* my_machine, int parent_state, int current_state);

// }State;

Data* DataInitInt(int a)
{
	Data* variable = (Data*) malloc(sizeof(Data));
	variable->type_id = 1;
	variable->_int = a;
	// printf("saved %i\n", variable->_int);
	return variable;
}
Data* DataInitChar(char a)
{
	Data* variable = (Data*) malloc(sizeof(Data));
	variable->type_id = 2;
	variable->_char = a;
	return variable;
}

Data* DataInitFloat(float a)
{
	Data* variable = (Data*) malloc(sizeof(Data));
	variable->type_id = 3;
	variable->_float = a;
	return variable;

}
Data* DataInitBool(bool a)
{
	Data* variable = (Data*) malloc(sizeof(Data));
	variable->type_id = 4;
	variable->_bool = a;
	return variable;
}


// init state async merge
// typedef struct ModificationFlags
// {
// 	bool is_added;
// 	bool is_deleted;
// 	bool is_modified;
// constructor for modification flags
ModificationFlags* ModificationFlagsInit()
{
	ModificationFlags* my_modification_flags = (ModificationFlags*) malloc(sizeof(ModificationFlags));

	my_modification_flags->is_added = false;
	my_modification_flags->is_deleted = false;
	my_modification_flags->is_modified = false;

	return my_modification_flags;
}
// }ModificationFlags;
// typedef struct CollectionState
// {
// 	TrieTree* keys;

// 	bool is_dictionary;

// 	bool is_array;



// }CollectionState;
enum CollectionStateType{string, array, set, dictionary};

CollectionState* CollectionStateInit(int collection_type)
{
	CollectionState* my_collection_state = (CollectionState*) malloc(sizeof(CollectionState));

	my_collection_state->is_string = collection_type == string? true: false;
	my_collection_state->is_array = collection_type == array? true: false;
	my_collection_state->is_set = collection_type == set? true: false;
	my_collection_state->is_dictionary = collection_type == dictionary? true: false;
	return my_collection_state;
}
// TrieTree* CollectionStateGetCollection(State* state)
// {
// 	return state->collectionState->keys;
// }
CollectionState* CollectionStateGetState(State* state)
{
	return state->collectionState;
}


// typedef struct PrimitiveState
// {
// 	bool is_primitive;

// 	Data* value;

// }PrimitiveState;
PrimitiveState* PrimitiveStateInit(Data* value)
{
	PrimitiveState* my_primitive_state = (PrimitiveState*) malloc(sizeof(PrimitiveState));

	my_primitive_state->is_primitive = true;
	my_primitive_state->value = value;

	return my_primitive_state;
}
Data* PrimitiveStateGetValue(State* state)
{
	return state->primitiveState->value;
}


// typedef struct CopyVariableDataUpHierarchyState
// {

// 	bool is_copied_up_hierarchy;
// 	Vector* destination_state_parent_name;

// }CopyVariableDataUpHierarchyState;
CopyVariableDataUpHierarchyState* CopyVariableDataUpHierarchyStateInit()
{
	CopyVariableDataUpHierarchyState* copyVariableDataUpHierarchyState = (CopyVariableDataUpHierarchyState*) malloc(sizeof(CopyVariableDataUpHierarchyState));
	copyVariableDataUpHierarchyState->is_copied_up_hierarchy = false;
	copyVariableDataUpHierarchyState->destination_state_parent_name = VectorInitVector();
	return copyVariableDataUpHierarchyState;
}
// typedef struct ChildrenOrNextStatesAreParallelState
// {
// 	bool next_states_are_parallel_states;

// 	bool children_are_parallel_states;


// }ChildrenOrNextStatesAreParallelState;
enum NeighborType{children, next_states};

ChildrenOrNextStatesAreParallelState* ChildrenOrNextStatesAreParallelStateInit(int neighbor_type)
{
	ChildrenOrNextStatesAreParallelState* childrenOrNextStatesAreParallelState = (ChildrenOrNextStatesAreParallelState*) malloc(sizeof(ChildrenOrNextStatesAreParallelState));
	childrenOrNextStatesAreParallelState->children_are_parallel_states = neighbor_type == children? true: false;
	childrenOrNextStatesAreParallelState->next_states_are_parallel_states = neighbor_type == next_states? true: false;
	return childrenOrNextStatesAreParallelState;
}
// typedef struct AsynchronousTimelineMergeState
// {
// 	// int threshold;
// 	// int visit_count;
	
// 	// TrieTree* parents;
// 	int threshold;
// 	int visit_count;
// 	TrieTree* parents;
// 	int duration;

// }AsynchronousTimelineMergeState;
AsynchronousTimelineMergeState* AsynchronousTimelineMergeStateInit()
{
	AsynchronousTimelineMergeState* asynchronousTimelineMergeState = (AsynchronousTimelineMergeState*) malloc(sizeof(AsynchronousTimelineMergeState));
	// 1000 ms = 1 second
	asynchronousTimelineMergeState->duration = 1000;
	asynchronousTimelineMergeState->parents = NULL;
	asynchronousTimelineMergeState->threshold = 0;
	asynchronousTimelineMergeState->visit_count = 0;
	return asynchronousTimelineMergeState;
}
// init state
State* StateInitState(	Vector* name,
						Vector* next_states,
						Vector* children,
						Vector* function_name,
						bool (*function_pointer)(ContextualStateChart* my_machine, int parent_state, int current_state)
				)
{
	State* my_state = (State*) malloc(sizeof(State));

	my_state->name = name;

	my_state->next_states = next_states;
	my_state->children = children;
	my_state->function_name = function_name;
	my_state->function = function_pointer;
	my_state->is_control_flow_node = 1;
	my_state->asynchronousTimelineMergeState = NULL;
	my_state->childrenOrNextStatesAreParallelState = NULL;
	my_state->copyVariableDataUpHierarchyState = NULL;
	my_state->modificationFlags = NULL;
	my_state->collectionState = NULL;
	my_state->primitiveState = NULL;


	return my_state;
}
void StateAddChildEdge(State* my_state, Vector* child)
{
	if(child == NULL)
	{
		return;
	}

	if(my_state->children == NULL)
	{
		my_state->children = VectorInitVector();
	}
	VectorAppend(my_state->children, child);

	return;
}

// init state children and/or next states are async

// init variablePrimitive
State* StateInitVariablePrimitive(	Vector* name,
									Data* value)
{
	State* my_state = StateInitState(	name,
										NULL,
										NULL,
										NULL,
										NULL);
	my_state->primitiveState = PrimitiveStateInit(value);
	// my_state->value = value;
	// my_state->is_primitive = 1;
	return my_state;
}

// init variableDictionary
// init variableOtherDataStructure
State* StateInitVariableCollectionState(Vector* name, int collection_type)
{
	State* my_state = StateInitState(	name,
										NULL,
										VectorInitVector(),
										NULL,
										NULL);
	my_state->collectionState = CollectionStateInit(collection_type);
	if(my_state->collectionState->is_dictionary)
	{
		BalancedTreeNode* empty_node = BalancedTreeNodeInit();
		VectorAppend(my_state->children, empty_node);

	}
	return my_state;
}

State* StateInitKey(Vector* name)
{
	State* my_state = StateInitState(	name,
										NULL,
										NULL,
										NULL,
										NULL);
	return my_state;
}


// typedef struct ContextualStateChart
// {

// 	// variations of the same state in different situations represent
// 	// the idea of context and are identified by slightly different state names
// 	Vector* states;
// 	TrieTree* state_names;
// 	// root is position 0



// }ContextualStateChart;
ContextualStateChart* ContextualStateChartInit()
{
	ContextualStateChart* my_state_chart = (ContextualStateChart*) malloc(sizeof(ContextualStateChart));

	my_state_chart->states = VectorInitVector();
	my_state_chart->state_ids = VectorInitVector();
	BalancedTreeNode* empty_node = BalancedTreeNodeInit();
	VectorAppend(my_state_chart->state_ids, empty_node);

	my_state_chart->root_state_id = 0;
	return my_state_chart;
}
ContextualStateChart* ContextualStateChartInitSmaller(	Vector* states,
														Vector* state_ids,
														int root)
{
	ContextualStateChart* my_state_chart = (ContextualStateChart*) malloc(sizeof(ContextualStateChart));

	my_state_chart->states = states;
	my_state_chart->state_ids = state_ids;
	my_state_chart->root_state_id = root;
	return my_state_chart;

}


// add state
void ContextualStateChartAddState(	ContextualStateChart* contextualStateChart,
									State* state)
{

	VectorAppend(contextualStateChart->states, state);

	int node_id = VectorGetPopulation(contextualStateChart->states);
	BalancedTreeNodeInsert(	contextualStateChart->states,
							contextualStateChart->state_ids,
							contextualStateChart->state_ids->start,
							-1,
							node_id);

}

// delete state
void ContextualStateChartDeleteState(ContextualStateChart* contextualStateChart, Vector* name)
{
	// int node_id = TrieTreeSearch(contextualStateChart->state_names, name);
	// TrieNode* my_node = (TrieNode*) VectorGetItem(contextualStateChart->state_names->trie_tree, node_id);
	// int state_id = my_node->state_id;
	// int passes = TrieTreeDelete(contextualStateChart->state_names, name);
	// if(!passes)
	// {
	// 	return;
		
	// }
	// bool result = VectorDeleteItem(contextualStateChart->states, state_id);
	// if(!result)
	// {
	// 	return;
	// }
	// return;
}
// add state as a variable to a parent
	// make the state
	// insert the state globally
	// add the new name to the parent's trie with the state's id
	// the global version of the 

State* ContextualStateChartGetVariableState(ContextualStateChart* contextualStateChart, Vector* parent_name, Vector* variable_name)
{
	// int parent_id = TrieTreeSearch(contextualStateChart->state_names, parent_name);
	// State* parent_state = (State*) VectorGetItem(contextualStateChart->states, parent_id);
	// // assume parent_state->collectionState->keys has stuff in it
	// int variable_id = TrieTreeSearch(parent_state->collectionState->keys, variable_name);
	// State* variable_state = (State*) VectorGetItem(contextualStateChart->states, variable_id);
	// return variable_state;
	return NULL;
}
int DataGetInt(Data* variable)
{
	return variable->_int;
}
char DataGetChar(Data* variable)
{
	return variable->_char;
}
float DataGetFloat(Data* variable)
{
	return variable->_float;
}
bool DataGetBool(Data* variable)
{
	return variable->_bool;
}

// search for state

// get state value

int StateGetInt(ContextualStateChart* contextualStateChart, Vector* parent_name, Vector* variable_name)
{
	// use the keys property from the parent state
	// my_state->keys
	State* variable_state = ContextualStateChartGetVariableState(contextualStateChart, parent_name, variable_name);
	if(PrimitiveStateGetValue(variable_state)->type_id != 1)
	{
		return 0;
	}
	return DataGetInt(PrimitiveStateGetValue(variable_state));
}
char StateGetChar(ContextualStateChart* contextualStateChart, Vector* parent_name, Vector* variable_name)
{
	// use the keys property from the parent state
	// my_state->keys
	State* variable_state = ContextualStateChartGetVariableState(contextualStateChart, parent_name, variable_name);
	if(PrimitiveStateGetValue(variable_state)->type_id != 2)
	{
		return '\0';
	}
	return DataGetChar(PrimitiveStateGetValue(variable_state));
}
float StateGetFloat(ContextualStateChart* contextualStateChart, Vector* parent_name, Vector* variable_name)
{
	// use the keys property from the parent state
	// my_state->keys
	State* variable_state = ContextualStateChartGetVariableState(contextualStateChart, parent_name, variable_name);
	if(PrimitiveStateGetValue(variable_state)->type_id != 3)
	{
		return 0.0;
	}
	return DataGetFloat(PrimitiveStateGetValue(variable_state));
}
bool StateGetBool(ContextualStateChart* contextualStateChart, Vector* parent_name, Vector* variable_name)
{
	// use the keys property from the parent state
	// my_state->keys
	State* variable_state = ContextualStateChartGetVariableState(contextualStateChart, parent_name, variable_name);
	if(PrimitiveStateGetValue(variable_state)->type_id != 3)
	{
		return 0;
	}
	return DataGetBool(PrimitiveStateGetValue(variable_state));
}


// set state value
void DataSetInt(Data* variable, int new_int)
{
	variable->_int = new_int;
}
void DataSetChar(Data* variable, char new_char)
{
	variable->_char = new_char;
}

void DataSetFloat(Data* variable, float new_float)
{
	variable->_float = new_float;
}
void DataSetBool(Data* variable, bool new_bool)
{
	variable->_bool = new_bool;
}

void StateSetInt(	ContextualStateChart* contextualStateChart,
					Vector* parent_name,
					Vector* variable_name,
					int new_int)
{
	// use the keys property from the parent state
	State* variable_state = ContextualStateChartGetVariableState(contextualStateChart, parent_name, variable_name);
	if(variable_state->primitiveState->value->type_id != 1)
	{
		return;
	}
	DataSetInt(variable_state->primitiveState->value, new_int);
}
void StateSetChar(	ContextualStateChart* contextualStateChart,
					Vector* parent_name,
					Vector* variable_name,
					char new_char)
{
	// use the keys property from the parent state
	// my_state->keys
	State* variable_state = ContextualStateChartGetVariableState(contextualStateChart, parent_name, variable_name);
	if(variable_state->primitiveState->value->type_id != 2)
	{
		return;
	}
	DataSetChar(variable_state->primitiveState->value, new_char);
}
void StateSetFloat(	ContextualStateChart* contextualStateChart,
					Vector* parent_name,
					Vector* variable_name,
					float new_float)
{
	// use the keys property from the parent state
	// my_state->keys
	State* variable_state = ContextualStateChartGetVariableState(contextualStateChart, parent_name, variable_name);
	if(variable_state->primitiveState->value->type_id != 3)
	{
		return;
	}
	DataSetFloat(variable_state->primitiveState->value, new_float);
}
void StateSetBool(	ContextualStateChart* contextualStateChart,
					Vector* parent_name,
					Vector* variable_name,
					bool new_bool)
{
	// use the keys property from the parent state
	// my_state->keys
	State* variable_state = ContextualStateChartGetVariableState(contextualStateChart, parent_name, variable_name);
	if(variable_state->primitiveState->value->type_id != 3)
	{
		return;
	}
	DataSetBool(variable_state->primitiveState->value, new_bool);
}

// search for neighbors
State* ContextualStateChartGetState(ContextualStateChart* contextualStateChart, Vector* state_name)
{
	// int state_id = TrieTreeSearch(contextualStateChart->state_names, state_name);
	// State* state = (State*) VectorGetItem(contextualStateChart->states, state_id);
	// return state;
	return NULL;
}

// getNeihbors(state_chart, current_state, neighbor_kind) -> vector* of neighbors
Vector* ContextualStateChartGetNextStatesOrChildren(
					ContextualStateChart* contextualStateChart,
					Vector* state_name,
					bool is_next_states)
{
	State* my_state = ContextualStateChartGetState(	contextualStateChart,
													state_name);
	return is_next_states? my_state->next_states: my_state->children;
}
// PRINTING
// print machine
void DataPrintData(Data* variable)
{
	// printf("here %i %i\n", variable->type_id, variable->_int);
	switch(variable->type_id)
	{
		case 1:
		{
			printf("%c", variable->_int);
			break;
		}
		case 2:
		{
			printf("%f", variable->_float);
			break;
		}
		case 3:
		{
			printf("%c", variable->_char);
			break;
		}
		case 4:
		{
			printf("%i", variable->_bool);
			break;
		}
	}
	
}
void StatePrintIntsFromVectorAsChars(Vector* my_ints)
{
	int size = VectorGetPopulation(my_ints);
	// printf("size %i\n", size);
	for(int i = 0; i < size; i++)
	{
		int letter = *((int*) VectorGetItem(my_ints, i));
		printf("%c", letter);
	}

}
enum StateAttributes{_name, _function_name, _next_states, _children};
void StatePrintAttributeSequence(Vector* attribute)
{

	printf("[");

	for(int i = attribute->start; i < attribute->end; i++)
	{
		// printf("i %i\n", i);
		int state_id = *((int*) VectorGetItem(attribute, i));
		printf("%i", state_id);
		// StatePrintIntsFromVectorAsChars((Vector*) VectorGetItem(attribute, i));
		if(i < VectorGetPopulation(attribute) - 1)
		{
			printf(", ");
		}	
	}
	printf("]");

}
void StatePrintAttribute(State* state, int indents, Vector* attribute_name, Vector* attribute, int state_attribute)
{
	// printf("%sname:\n", TrieTreeMakeIndents(indents));
	printf("%s", BalancedTreeNodeMakeIndents(indents));

	StatePrintIntsFromVectorAsChars(attribute_name);
	printf(":\n%s", BalancedTreeNodeMakeIndents(indents));

	if(state_attribute == _name)
	{
		VectorPrintIntsAsChars(attribute);
	}
	else if(state_attribute == _children)
	{
		if(state->collectionState == NULL) return;
		if(state->collectionState->is_dictionary)
		{

			Vector* key_ids = BalancedTreeNodeDFT(attribute, 0, VectorInitVector());

			StatePrintAttributeSequence(key_ids);
		}
		else if(state->collectionState->is_array || state->collectionState->is_string)
		{
			StatePrintAttributeSequence(attribute);
		}
	}
	else
	{
		StatePrintAttributeSequence(attribute);

	}
	// maybe print out a sequence of characters for the function name
	printf("\n");

}
void StatePrintPrimitive(State* state, int indents)
{
	if(state->primitiveState != NULL && state->collectionState != NULL)
	{
		return;
	}
	// if primitive exists
		// print it
	printf("%s", BalancedTreeNodeMakeIndents(indents));

	// printing name of attribute
	StatePrintIntsFromVectorAsChars(VectorMakeVectorOfChars("variable"));

	printf(":\n%s", BalancedTreeNodeMakeIndents(indents));
	
	DataPrintData(PrimitiveStateGetValue(state));
	printf("\n");
}
void StatePrintCollection(ContextualStateChart* contextual_state_chart, State* state, int indents)
{
	// if collection exits
		// if it's an array
			// StatePrintCollection for each state found in array
		// if it's a dict
			// StatePrintCollection for each value from each key in dict(dft to get the keys)
	if(state->primitiveState != NULL && state->collectionState != NULL)
	{
		return;
	}
	if(state->primitiveState != NULL)
	{
		printf("%sprimitive state\n", BalancedTreeNodeMakeIndents(indents));
		// are at the bottom level
		StatePrintPrimitive(state, indents);
	}
	else if(state->collectionState->is_array)
	{
		printf("%sarray\n", BalancedTreeNodeMakeIndents(indents));
		// printf("size %i\n", VectorGetPopulation(state->children));
		StatePrintAttributeSequence(state->children);
		// for(int i = state->children->start; i < state->children->end; i++)
		// {
		// 	// printf("%i\n", i);
		// 	int state_id = *((int*) VectorGetItem(state->children, i));

		// 	// int node_id = TrieTreeSearch(state->collectionState->keys, state_name);

		// 	// TrieNode* node = (TrieNode*) VectorGetItem(state->collectionState->keys->trie_tree, node_id);
		// 	State* my_state = (State*) VectorGetItem(contextual_state_chart->states, state_id);
		// 	// VectorPrint(my_state->name);
		// 	StatePrintCollection(contextual_state_chart, my_state, indents + 3);
		// }
	}
}
void StatePrintState(ContextualStateChart* contextual_state_chart, State* state, int indents)
{

	if(state == NULL)
	{
		return;
	}
	// string my_indents = makeSpaces(indents);
	// State* state = (State*) VectorGetItem(my_machine->states, state_id);
	printf("%sid %i\n", BalancedTreeNodeMakeIndents(indents), state->id);
	if(state->name != NULL)
	{
		StatePrintAttribute(
						state,
						indents,
						VectorMakeVectorOfChars("name"),
						state->name,
						_name);

	}
	if(state->next_states != NULL)
	{
		StatePrintAttribute(
						state,
						indents,
						VectorMakeVectorOfChars("next states"),
						state->next_states,
						_next_states);

	}
	if(state->children != NULL)
	{
		StatePrintAttribute(
						state,
						indents,
						VectorMakeVectorOfChars("children"),
						state->children,
						_children);

	}

	if(state->function_name != NULL)
	{
		StatePrintAttribute(
						state,
						indents,
						VectorMakeVectorOfChars("function name"),
						state->function_name,
						_function_name);

	}
	// printf("here\n");
	// printf("%i\n", state->primitiveState);
	if(state->primitiveState != NULL)
	{
		StatePrintPrimitive(state, indents);
	}
	if(state->collectionState != NULL)
	{
		printf("%stype: ", BalancedTreeNodeMakeIndents(indents));
		if(state->collectionState->is_string)
		{
			printf("string");
		}
		if(state->collectionState->is_array)
		{
			printf("array");
		}
		if(state->collectionState->is_dictionary)
		{
			printf("dictionary");
		}
		printf("\n");
	}
	printf("\n");
	


}
void ContextualStateChartPrintStateTree(ContextualStateChart* my_machine, int state_id, int indents)
{
	if(state_id < 0 || my_machine->states == NULL || my_machine->state_ids == NULL)
	{
		printf("Contextual State Chart is empty\n");
		return;
	}
	State* state = (State*) VectorGetItem(my_machine->states, state_id);

	StatePrintState(my_machine, state, indents);


	for(int i = 0; i < VectorGetPopulation(state->children); i++)
	{
		int child_id = *((int*) VectorGetItem(state->children, i));
		// printf("state id %i\n");
		// int new_id = TrieTreeSearch(my_machine->state_names, child);
		ContextualStateChartPrintStateTree(my_machine, child_id, indents + 3);
	}

}

// evaluator(dfa with setup data structues for nfa)
void ContextualStateChartPrintStates(ContextualStateChart* contextual_state_chart)
{
	for(int i = 0; i < VectorGetPopulation(contextual_state_chart->states); i++)
	{
		// printf("i %i\n", i);
		State* my_state = (State*) VectorGetItem(contextual_state_chart->states, i);
		StatePrintState(contextual_state_chart, my_state, 0);
	}
}

// CONSTRUCTION FUNCTIONS
ContextualStateChart* CSCStateChartFromString(char* my_string)
{
	// ContextualStateChart* (so combining the arrays of states will not have the state chart
	// variable name as part of the paramater list)
	ContextualStateChart* contextual_state_chart = ContextualStateChartInit();

	// using VectorInitVector() lets us autoganerate state names for the array elements

	State* structure_state = StateInitVariableCollectionState(VectorInitVector(), string);
	// structure_state->collectionState = CollectionStateInit(string);
	// adding stuff to dict
	VectorAppend(contextual_state_chart->states, structure_state);
	// where do I add things to keys
	for(int i = 0; i < strlen(my_string); i++)
	{
		// make a 

		State* int_state = StateInitVariablePrimitive(VectorInitVector(), DataInitInt(my_string[i]));


		VectorAppend(contextual_state_chart->states, int_state);
		int int_state_id = VectorGetLastIndex(contextual_state_chart->states);
		// might be a memory leak
		// add int_state_id to the state name
		int_state->name = VectorConvertIntToVectorOfInts(int_state_id);
		int_state->id = int_state_id;
		BalancedTreeNodeInsert(	contextual_state_chart->states,
								contextual_state_chart->state_ids,
								contextual_state_chart->state_ids->start,
								-1,
								int_state_id
								);
		
		VectorAppendInt(structure_state->children, int_state_id);

	}
	return contextual_state_chart;

}
/*
	// printf("print out tree\n");
	// BalancedTreeNodePrintTreeOfStates(
	// 	contextual_state_chart->states,
	// 	contextual_state_chart->state_ids,
	// 	0,
	// 	1);
	// exit(1);
	// ContextualStateChartPrintStates(contextual_state_chart);
	// State* my_state = (State*) VectorGetItem(contextual_state_chart->states, 0);
	// StatePrintState(contextual_state_chart, my_state, 0);
	// StatePrintCollection(contextual_state_chart, my_state, 0);
	// ContextualStateChartPrintStateTree(contextual_state_chart, 0, 0);
	// printf("we are here\n%s\n", my_string.c_str());
	// VectorPrint(list_of_chars);
	// ContextualStateChartPrintStateTree(contextual_state_chart, 0, 1);

	// printf("done\n");

*/
// i -> state id from children -> state

/*
array of states
dict of state ids
*/
/*
'abcd'

'2'
	children
		a, b, c, d

['abcd']
'3'
	children		
		'2'
			children
				a, b, c, d


machineMetrics = {
	nextStates: [startState],
	parent: null,
	indents: indents
}

'machineMetrics'
	children (234 tree)
		'nextStates'
			next
				'3'
					children (array)	
						'2'
							children
								a, b, c, d
				
		'parent'
			next
				state with null value

		'indents'
			next 
				indent_count

key sate
name is the key

value state
variable state

metrics = makeDict(
	2,
	makePair(
			vector('machine metrics'),
			makeDict(
				3,
				makePair(vector('next states'), stateChartNest(stateChartFromString('start state')))
				makePair(vector('parent'), makeNULLStateChart())),
				makePair(vector('parent'), StateChartFromInt(indents))
			)
	),
	
	makePair(
		vector('state metrics'),
		makeDict(
			2,
			makePair(vector('passes'), StateChartFromBool(false)))
			makePair(vector('winning_state_name'), makeEmptyStringStateChart()))
		)
	)

)


makePair(Vector*, StateChart*) -> Vector* [void*, void*]
makeDict(int count, Vector* key_value_1, Vector* key_value_2, ...) -> StateChart*

uses no temporary state variables

getValue(get(get(contextual_state_chart, "my_key_string"), "my_second_key_string"))

contextual_state_chart["my_key_string"]["my_second_key_string"]

get(Vector*, char*) -> Vector*
get([array_of_states, dict_of_ids, root_state_id]) -> 
	[array_of_states, dict_of_child_ids_found_from_the_first_key, id_of_value_state]
// return a new state chart with different values for the dict and the root node id

getValue(state_chart*) -> void* from root



{
	key: value
}

{
	key: {
		key: value
	}
}

*/

ContextualStateChart* CSCNestArray(	int number_of_items, ...)
{

	// make an outer state
	// make an array of contextual_state_chart structs
	// ContextualStateChart* contextual_state_chart
	// [structure_state, ...array1, ...array2]
	ContextualStateChart* my_chart_dict = ContextualStateChartInit();
	State* structure_state = StateInitVariableCollectionState(VectorInitVector(), array);
	VectorAppend(my_chart_dict->states, structure_state);
	structure_state->id = 0;
	BalancedTreeNodeInsert(	my_chart_dict->states,
							my_chart_dict->state_ids,
							0, // root id
							-1, // parent interval
							0 // item to add
							);
	// VectorAppendInt(structure_state->children, 0);
	va_list ap;

	va_start(ap, number_of_items);
	for(int i = 0; i < number_of_items; i++)
	{
		ContextualStateChart* current_chart = va_arg(ap, ContextualStateChart*);
		
		int old_size = VectorGetPopulation(my_chart_dict->states);
		State* root = (State*) VectorGetItem(current_chart->states, 0);
		VectorAppendInt(structure_state->children, root->id + old_size);
		CSCTransfer(my_chart_dict, current_chart);

		// int new_value_state_id = old_size + value_state_id;

		// key_state->next_states = VectorInitVector();

		// VectorAppendInt(key_state->next_states, new_value_state_id);


	}
	// printf("state id %i\n", id);

	// contextual_state_chart->root_state_id = id;
	// root_state_id
	// add it to the begining

	// make a new array state
	// transfer each chart to the new chart and add new edges from the structure state's chilren

	
	return my_chart_dict;

}
Vector* CSCMakePair(Vector* key, ContextualStateChart* value)
{
	Vector* my_pair = VectorInitVector();
	VectorAppend(my_pair, key);
	VectorAppend(my_pair, value);
	return my_pair;	
}

void CSCTAdjustNeighborLinks(Vector* neighbor_links, int old_size)
{
	if(neighbor_links == NULL)
	{
		return;
	}
	// printf("%i\n", )
	for(int j = neighbor_links->start; j < neighbor_links->end; j++)
	{
		int* our_original_number = (int*) neighbor_links->values[j];
		(*our_original_number) += old_size;
	}
	
}
// make an (*our_original_number) += old_size; version for a 234 tree array
void CSCTransfer(	ContextualStateChart* chart_1,
					ContextualStateChart* chart_2)
{
	// transfter states from chart_2 to chart_1
	int old_size = VectorGetPopulation(chart_1->states);
	for(int i = chart_2->states->start; i < chart_2->states->end; i++)
	{
		// printf("%i\n", i);
		State* state = (State*) VectorGetItem(chart_2->states, i);
		// VectorPrintIntsAsChars(state->name);
		// asjust children and next_states links to account for the new items being added
		// the ids will be different in char_1 from what they were in chart_2
		// if our state chart is a dict then maybe we can't assume the children only have int* in them?
		if(state->collectionState == NULL){}
		else if(state->collectionState->is_string || state->collectionState->is_array)
		{
			CSCTAdjustNeighborLinks(state->children, old_size);
		}
		else if(state->collectionState->is_dictionary)
		{
			BalancedTreeNodeDFTUpdateValue(state->children, state->children->start, old_size);
		}
		CSCTAdjustNeighborLinks(state->next_states, old_size);
		// will need to update variable names and parents too

		

		
		VectorAppend(chart_1->states, state);
		int state_id = VectorGetPopulation(chart_1->states) - 1;
		// printf("state id %i\n", state_id);
		state->id = state_id;
	}
	// erase the chart_2->states vector
	free(chart_2->states->values);
	chart_2->states->values = NULL;
	chart_2->states->population = 0;
	chart_2->states->size = 0;
	chart_2->states->start = 0;
	chart_2->states->end = 0;
	free(chart_2->states);
	chart_2->states = NULL;

	free(chart_2->state_ids->values);
	chart_2->state_ids->values = NULL;
	chart_2->state_ids->population = 0;
	chart_2->state_ids->size = 0;
	chart_2->state_ids->start = 0;
	chart_2->state_ids->end = 0;
	free(chart_2->state_ids);
	chart_2->state_ids = NULL;


	// erase the chart_2->state_id vector
	VectorDeleteAllItems2(chart_2->state_ids);

}
ContextualStateChart* CSCMakeDict(int number_of_pairs, ...)
{
	// this function takes in key_value pairs and a count
	// these pairs are added to a new state chart
	// the finished state chart is then returned
	ContextualStateChart* my_chart_dict = ContextualStateChartInit();
	State* structure_state = StateInitVariableCollectionState(VectorInitVector(), dictionary);
	VectorAppend(my_chart_dict->states, structure_state);

	va_list ap;

	va_start(ap, number_of_pairs);
	// do I have a state representing the dict?
	// what if the value is a dict?
	// children edges aren't getting updated when new things(a dict) are added
	for(int i = 0; i < number_of_pairs; i++)
	{
		// printf("%i\n", i);
		Vector* current_pair = va_arg(ap, Vector*);
		
		Vector* key = (Vector*) VectorGetItem(current_pair, 0);
		ContextualStateChart* value = (ContextualStateChart*) VectorGetItem(current_pair, 1);
		
		int value_state_id = value->root_state_id;
		State* value_state = (State*) VectorGetItem(value->states, value_state_id);
		// make "key" state where the key is the name only
		State* key_state = StateInitKey(key);
		
		// add key state to state array and the state id dict
		VectorAppend(my_chart_dict->states, key_state);
		int key_state_id = VectorGetPopulation(my_chart_dict->states) - 1;
		// printf("state id %i\n", key_state_id);
		key_state->id = key_state_id;
		BalancedTreeNodeInsert(	my_chart_dict->states,
								my_chart_dict->state_ids,
								my_chart_dict->state_ids->start,
								-1,
								key_state_id);

		// add each key to the structure states children too
		BalancedTreeNodeInsert(	my_chart_dict->states,
								structure_state->children,
								0,
								-1,
								key_state_id);

		// printf("here\n");
		// ContextualStateChartPrintStateTree(value, value->root_state_id, 0);
		// ContextualStateChartPrintStates(my_chart_dict);

		// transfer all the states in value to my_chart_dict
		// printf("old size %i\n", VectorGetPopulation(my_chart_dict->states));
		int old_size = VectorGetPopulation(my_chart_dict->states);
		// transfter states from value to my_chart_dict
		// the bug involves items that were copied in that where not updated but this should be updating them
		// the dict that was copied over didn't get it's edges copied over properly, but the array and the string was copied over right
		CSCTransfer(my_chart_dict, value);
		// printf("new chart\n");
		// printf("here 2\n");
		// ContextualStateChartPrintStateTree(my_chart_dict, my_chart_dict->root_state_id, 0);
		// printf("new size %i\n", VectorGetPopulation(my_chart_dict->states));

		// ContextualStateChartPrintStateTree(value, value->root_state_id, 0);

		int new_value_state_id = old_size + value_state_id;

		key_state->next_states = VectorInitVector();
		VectorAppendInt(key_state->next_states, new_value_state_id);

		// printf("here %i\n", new_value_state_id);
		// add the "key" state to the structure state's children 234 tree
		// cleanup
	}
	return my_chart_dict;
}

ContextualStateChart* get(ContextualStateChart* contextual_state_chart, char* key)
{
	Vector* my_key =  VectorMakeVectorOfChars(key);
	BalancedTreeNodePrintTree(contextual_state_chart->state_ids, 0, 0);

	int our_key = BalancedTreeNodeSearch(	contextual_state_chart->states,
											contextual_state_chart->state_ids,
											0,
											my_key);
	printf("id %i\n", our_key);
	// works as of here
	State* key_state = (State*) VectorGetItem(contextual_state_chart->states, our_key);
	// printf("population %i\n", VectorGetPopulation(key_state->children));

	int value_id = *((int*) VectorGetItem(key_state->next_states, 0));


	State* value_state = (State*) VectorGetItem(contextual_state_chart->states, value_id);

	// we need to update the root because the root is where we start in the machine
	ContextualStateChart* smaller_chart = ContextualStateChartInitSmaller(
													contextual_state_chart->states,
													value_state->children,
													value_id);
	// make a smaller contextual state chart via the current list of states and the new key's children
	// return the smaller chart
	return smaller_chart;
}

// PRINT ContextualStateChart DICTIONARY
void CSCPrintString(ContextualStateChart* contextual_state_chart, int current_state_id, int indents)
{
	if(contextual_state_chart == NULL || current_state_id < 0) return;
	State* current_state = (State*) VectorGetItem(contextual_state_chart->states, current_state_id);

	// printf("%i\n", current_state_id);

	for(int i = current_state->children->start; i < current_state->children->end; i++)
	{
		// printf("%i\n", i);
		int char_state_id = *((int*) VectorGetItem(current_state->children, i));
		State* char_state = (State*) VectorGetItem(contextual_state_chart->states, char_state_id);
		if(char_state->primitiveState == NULL) return;
		DataPrintData(char_state->primitiveState->value);
	}
}
void CSCPrintArray(ContextualStateChart* contextual_state_chart, int current_state_id, int indents)
{
	if(contextual_state_chart == NULL || current_state_id < 0) return;
	State* current_state = (State*) VectorGetItem(contextual_state_chart->states, current_state_id);
	for(int i = current_state->children->start; i < current_state->children->end; i++)
	{
		int value_state_id = *((int*) VectorGetItem(current_state->children, i));
		printf("%s", BalancedTreeNodeMakeIndents(indents + 3));

		CSCPrintDict(contextual_state_chart, value_state_id, indents);
		if(i < current_state->children->end - 1) printf(", \n");

	}
}
void CSCPrintDict(	ContextualStateChart* contextual_state_chart,
					int current_state_id,
					int indents)
{

	if(contextual_state_chart == NULL || current_state_id < 0) return;
	// printf("here %i\n", current_state_id);
	State* current_state = (State*) VectorGetItem(contextual_state_chart->states, current_state_id);
	if(current_state == NULL) return;
	if(current_state->collectionState == NULL) return;

	// printf("%i\n", current_state->collectionState);

	char* indent_string = BalancedTreeNodeMakeIndents(indents);
	if(current_state->collectionState->is_string)
	{
		printf("\"");
		// printf("trashed string\n");
		
		CSCPrintString(contextual_state_chart, current_state_id, indents);
		// exit(1);
		printf("\"");

		// exit(1);
	}
	else if(current_state->collectionState->is_array)
	{
		printf("[\n");

		// printf("trashed array\n");

		CSCPrintArray(contextual_state_chart, current_state_id, indents);
		printf("\n%s]", indent_string);
		// printf("\n%s}\n", indent_string);	

	}
	else if(current_state->collectionState->is_dictionary)
	{
		printf("{\n");
		// get the key value pair
		Vector* keys = BalancedTreeNodeDFT(current_state->children, 0, VectorInitVector());
		for(int i = keys->start; i < keys->end; i++)
		{
			// print key
			// printf("our new key index %i\n", i);

			int key_state_id = *((int*) VectorGetItem(keys, i));
			// CSCPrintDict(contextual_state_chart, key_state_id, indents);
			State* key_state = (State*) VectorGetItem(contextual_state_chart->states, key_state_id);
			printf("%s\"", BalancedTreeNodeMakeIndents(indents + 3));
			// printf("trashed string\n");
			StatePrintIntsFromVectorAsChars(key_state->name);
			// CSCPrintString(contextual_state_chart, key_state_id, indents);
			// exit(1);
			printf("\" : ");
			// printf("key state id %i\n", key_state_id);
			int value_id = *((int*) VectorGetItem(key_state->next_states, 0));
			// printf("value state id %i\n", value_id);

			CSCPrintDict(contextual_state_chart, value_id, indents + 10);
			if(i < keys->end - 1) printf(", \n");

		}

		printf("\n%s}", BalancedTreeNodeMakeIndents(indents + 3));
	}
}
void visit(ContextualStateChart* graph, Vector* start_state, int indents)
{

	int i = 0;

	/*
		let machineMetrics = {
		nextStates: [startState],
		parent: null,
		indents: indents
	}

	*/
	// add a state called "machine_metrics"
/*
	
	VectorOfInts("my string") -> Vector*
	ArrayOfVectorsCollectionState(	2,
					VectorOfInts("my string 1"),
					VectorOfInts("my string 2")) -> State*
	f(Vector*, Vector*, Vector*) -> State*
	State*:
		{
			collectionState:
			{
				TrieTree* keys
				bool is_array
			}
		}
	buildDict(
		VectorPair(VectorOfInts("my key"), ArrayOfVectorsCollectionState(2,
										VectorOfInts("my string 1"),
										VectorOfInts("my string 2")))
						)
		VectorPair(Vector*|> void* key, State*|> void* value)
	buildDict(Vector* key_value_pairs)
	{
		for pair in key_value_pairs
			key = pair[0]   // Vector* -> [int*]
			value = pair[1] // State*


	}
	
	
	*/
	// State* machine_metrics = StateInitDictionary(
	// 							VectorMakeVectorOfChars("machine metrics"),
	// 							NULL,
	// 							VectorMakeVectorOfVectorsOfChars(
	// 								3,
	// 								VectorMakeVectorOfChars("next states"),
	// 								VectorMakeVectorOfChars("parent"),
	// 								VectorMakeVectorOfChars("indents")
	// 								)
	// 						);
	// StatePrintState(machine_metrics, 0);

	// ArrayOfVectorsCollectionState(1, VectorMakeVectorOfChars("start state name")) -> State*
	/*
	state*(array of stuff)
			state*, state*, (array of states)
				|state*, state*|, |state*, state*| (int state)
	for ["a", "b c"]

	*/
	// State* next_states = StateInitVariableCollectionState(
	// 						VectorMakeVectorOfChars("next states"),
	// 						array);

	// next_states->keys = TrieTreeInitTrieTree();
	// loop through start_state
		// make an int state that holds each int in the vector
		// add each new name as an empty vector to the keys
		// take each uniquely formed name and add it to the children vector
	// make a state* for "abcd"
	// make a state* for state* from above
	// VectorMakeVectorOfChars("start state name") -> state*
	// simulate a vector of ints with state*'s
	// for(int i = 0; i < VectorGetPopulation(start_state); i++)
	// {
	// 	// Vector* test = VectorInitVector();
	// 	Vector* new_name = TrieTreeInsertWords(	next_states->collectionState->keys,
	// 											VectorInitVector());
	// 	// printf("%i\n", i);
	// 	// VectorPrint(new_name);
	// 	// VectorPrint(start_state);
	// 	int int_value = *((int*) VectorGetItem(start_state, i));
	// 	// printf("%i\n", int_value);
	// 	State* int_state = StateInitVariablePrimitive(
	// 								new_name,
	// 								DataInitInt(int_value));
	// 	// printf("from state %i\n", int_state->value->_int);
	// 	// add to graph
	// 	// add id from graph to next_states->keys[new_name]
	// 	StatePrintState(int_state, 0);
	// }
	// StatePrintState(next_states, 0);

	// StateAddChildEdge(next_states, start_state);

	/*
	"machine metrics"
		key: {"next states"}
	
	"next states"
		children: ["start state name"] should be [s, t, a, r]
	

	*/

	printf("\ndone\n");
}
// tracking system for array manipulations
// hierarchy for the log
#define s(a) CSCStateChartFromString(a) 		 // string
#define a(i, ...) CSCNestArray(i, ##__VA_ARGS__) // array
#define v(a) VectorMakeVectorOfChars(a)			// vector
#define p(a, b) CSCMakePair(a, b)				// pair
// variadic macro
#define d(i, ...) CSCMakeDict(i, ##__VA_ARGS__) // dictonary

void ContextualStateChartTest()
{
	ContextualStateChart* graph = ContextualStateChartInit();


	// ContextualStateChartAddState(
	// 		graph,
	// 		StateInitVariablePrimitive(VectorMakeVectorOfChars2("my_string"),
	// 		DataInitInt(5)));

	// ContextualStateChart* contextual_state_chart = CSCNestArray(
	// 													CSCStateChartFromString("start state name"));
									// VectorMakeVectorOfChars
	/*
	s("my string") = CSCStateChartFromString("start state")
	a[state_chart] = CSCNestArray(state_chart)


	a[s("myString")]
	*/
	// root needs to be the first logical node(not necessarily position 0)
	// array needs to be able to handle a list of state charts
	// for variadic macros to work we have to use the original names the first time they are invoced
	// all remainin times we can use the macro shortened name
	ContextualStateChart* contextual_state_chart = 

		// a(2, s("start state"), s("another state"))
			CSCMakeDict(1,
				p(	v("master key"),
					d(	2,
						p(v("next states"), a(2, s("start state"), s("another state"))),
						p(v("another key"), s("value")))))
						// ,
			// d(1,
			// 	p(v("another key 2"), a(2, s("first value"), s("value")))
			// )
		;
	// recognize this a^nb^nc^nd^n
	/*
	// [{"master key": {"next states": , }}]
	*/
	/*
	id 1
	name:
	|master key|

	next states:
	[2]

	id 2
	name:
	||none

	children:
	[15, 1]
	type: dictionary
	*/
	ContextualStateChartPrintStates(contextual_state_chart);
	printf("\n\n\n");

	// contextual_state_chart = CSCMakeDict(
	// 									2,
	// 									CSCMakePair(
	// 											VectorMakeVectorOfChars("next states"),
	// 											CSCNestArray(CSCStateChartFromString("start state"))),
	// 									CSCMakePair(
	// 											VectorMakeVectorOfChars("another key"),
	// 											CSCStateChartFromString("value"))
	// 							);

	/*
	id 0
	name:
	|another key|
	*/
	// ContextualStateChartPrintStates(contextual_state_chart);
	BalancedTreeNodePrintTree(	contextual_state_chart->state_ids,
								contextual_state_chart->state_ids->start,
								0);
	// printf("root %i\n", contextual_state_chart->state_ids->start);
	CSCPrintDict(contextual_state_chart, 0, 0);

	printf("\n");
	ContextualStateChart* smaller_chart = get(contextual_state_chart, "master key");

	BalancedTreeNodePrintTree(	smaller_chart->state_ids,
							smaller_chart->state_ids->start,
							0);

	CSCPrintDict(smaller_chart, smaller_chart->root_state_id, 0);
	printf("\n");

	// failed becuase the id of the next item isn't the array of strings, it's the start of the string
	// need a systematic system of addressing what kind of state ids are stored in what containers so
	// nested gets will work
	// redo as a dictionary system
	ContextualStateChart* smaller_chart2 = get(smaller_chart, "another key");
	BalancedTreeNodePrintTree(	smaller_chart2->state_ids,
							smaller_chart2->state_ids->start,
							0);

	CSCPrintDict(smaller_chart2, smaller_chart2->root_state_id, 0);
	printf("\n");

	// make sure the data structure flags are appropriately set for the data structure states

	// printf("start %i\n", contextual_state_chart->root_state_id);
	// ContextualStateChartPrintStateTree(contextual_state_chart, contextual_state_chart->root_state_id, 0);
	// "next states" : ["start state name"]
	// visit(graph, VectorMakeVectorOfChars("start state name"), 0);

}
/*
ExtendedState* TrieTreeInsertString(ExtendedState* node, string value)
{
	// insert
	string* new_string = (string*) malloc(sizeof(string));
	*new_string = value;
	node->data = new_string;
	node->type = 0;
	return node;
	// set the type of the void*
}*/
// ExtendedState* insertDynamicState(ExtendedState* node, DynamicState* value)
// {
// 	// insert
// 	node->data = value;
// 	node->type = 1;
// 	return node;
// 	// set the type of the void*

// }
/*
typedef struct OrderedDict
{
	// ordered dictioanry where the dict part is implemented using a trie
	Vector* items;
	multimap<string, ExtendedState*>* dict;
}OrderedDict;
*/
// OrderedDict* initOrderedDict()
// {
// 	OrderedDict* new_dict = (OrderedDict*) malloc(sizeof(OrderedDict));
// 	new_dict->items = VectorInitVector();
// 	new_dict->dict = new multimap<string, ExtendedState*>();
// 	multimap<string, ExtendedState*>::iterator it = new_dict->dict->begin();
// 	new_dict->root = initExtendedState();
// 	// insert the string
// 	/*
// 	new_dict->root = TrieTreeInsertString(new_dict->root, "root");

// 	new_dict->dict->insert(it, pair<string, ExtendedState*>("root", new_dict->root));
// 	new_dict->max_id = 0;
// 	*/
// 	return new_dict;
// }
// OrderedDict* insertState(OrderedDict* my_ordered_dict, Vector* strings)
// {
// 	// insert the strings into the dict
// 	// don't need to generate extra strings cause these are only for the neighbor states

// 	return NULL;
// }

// DynamicState* DynamicStateInitDynamicState(	Vector* name, // strings
// 								Vector* parents,  // array of strings
// 								Vector* start_children,  // array of strings
// 								Vector* children, // array of strings
// 								Vector* next_states, // array of strings
// 								bool (*function) (DynamicMachine* my_machine,
// 												  DynamicState* parent_state,
// 												  DynamicState* current_state),
// 								Data* value)
// {
// 	DynamicState* my_dynamic_state = (DynamicState*) malloc(sizeof(DynamicState));
// 	my_dynamic_state->name = name;
// 	my_dynamic_state->parents = parents;
// 	my_dynamic_state->start_children = start_children;
// 	my_dynamic_state->children = children;
// 	my_dynamic_state->_children = NULL;
// 	my_dynamic_state->next_states = next_states;
// 	my_dynamic_state->container_type = -1;
// 	my_dynamic_state->value = value;
// 	// my_dynamic_state->level_number = 0;
// 	// my_dynamic_state->function = function;
// 	// my_dynamic_state->parent_status = false;
// 	return my_dynamic_state;
// }

// DynamicState* DynamicStateInitDynamicState2(	Vector* name, // strings
// 								bool is_start_child,
// 								bool has_down_links,
// 								Vector* parents,  // array of strings
// 								Vector* start_children,  // array of strings
// 								Vector* children, // array of strings
// 								Vector* next_states, // array of strings
// 								bool (*function) (	DynamicMachine* my_machine,
// 													DynamicState* parent_state,
// 													DynamicState* current_state),
// 								Data* value)
// {
// 	DynamicState* my_dynamic_state = (DynamicState*) malloc(sizeof(DynamicState));
// 	my_dynamic_state->name = name;
// 	my_dynamic_state->is_start_child = is_start_child;
// 	my_dynamic_state->has_down_links = has_down_links;

// 	my_dynamic_state->parents = parents;
// 	my_dynamic_state->start_children = start_children;
// 	my_dynamic_state->children = children;
// 	my_dynamic_state->_children = NULL;
// 	my_dynamic_state->next_states = next_states;
// 	my_dynamic_state->container_type = -1;
// 	my_dynamic_state->value = value;
// 	// my_dynamic_state->level_number = 0;
// 	// my_dynamic_state->function = function;
// 	// my_dynamic_state->parent_status = false;
// 	return my_dynamic_state;

// }


// DynamicState* DynamicStateInitDynamicStateVariableContainer(
// 								Vector* name, // strings
// 								Vector* parents,  // array of strings
// 								TrieTree* _children,
// 								int container_type)
// {
// 	DynamicState* my_dynamic_state = (DynamicState*) malloc(sizeof(DynamicState));
// 	my_dynamic_state->name = name;
// 	my_dynamic_state->is_start_child = 0;
// 	my_dynamic_state->has_down_links = 0;

// 	my_dynamic_state->parents = parents;
// 	my_dynamic_state->start_children = VectorInitVector();
// 	my_dynamic_state->children = VectorInitVector();
// 	my_dynamic_state->_children = _children;
// 	my_dynamic_state->next_states = VectorInitVector();
// 	my_dynamic_state->container_type = container_type;
// 	my_dynamic_state->value = NULL;
// 	// my_dynamic_state->level_number = 0;
// 	// my_dynamic_state->function = returnTrue;
// 	// my_dynamic_state->parent_status = false;
// 	return my_dynamic_state;

// }
// DynamicState* DynamicStateMakeVariable(
// 										// string variable_name,
// 										Vector* parents,   // array of strings
// 										Data* value)
// {

// 	return DynamicStateInitDynamicState(VectorAddStringToVector1(variable_name),
// 							parents,
// 							VectorInitVector(),
// 							VectorInitVector(),
// 							VectorInitVector(),
// 							returnTrue,
// 							value
// 							);

// }
// DynamicState* DynamicStateMakeVariable2(
// 										// string variable_name,
// 										Vector* parents,   // array of strings
// 										Data* value)
// {

	// return DynamicStateInitDynamicState2(VectorAddStringToVector1(variable_name),
	// 						!is_start_child,
	// 						!has_down_links,
	// 						parents,
	// 						NULL,
	// 						NULL,
	// 						NULL,
	// 						returnTrue,
	// 						value
	// 						);

// }
// MapNode* initMapNode()
// {
// 	MapNode* my_map_node = (MapNode*) malloc(sizeof(MapNode));
// 	//my_map_node->string_1 = new set<string>();
// 	//my_map_node->states = new map<string, struct DynamicState*>();
// 	//my_map_node->state = NULL;
// 	//my_map_node->state_map_is_empty = false;
// 	my_map_node->current_name_part = "";
// 	my_map_node->next_name_part_states_s = new map<string, DynamicState*>();

// 	return my_map_node;
// }

// DynamicMachine* DynamicMachineInitDynamicMachine()
// {
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
	// DynamicMachine* my_dynamic_machine = (DynamicMachine*) malloc(sizeof(DynamicMachine));

	// my_dynamic_machine->state_names = TrieTreeInitTrieTree();
	// my_dynamic_machine->states = VectorInitVector();
	// store the name
	// TrieTree* state_names;

	// Vector* states;
	

	// my_dynamic_machine->static_machine = my_machine;

	// auxiliary data hierarchy for filling up the vectors
	// my_dynamic_machine->trie_names = new map<string, MapNode*>();

	// insert root -> mapnode
	// map<string, MapNode*>::iterator it = my_dynamic_machine->trie_names->begin();
	// my_dynamic_machine->trie_names->insert(it,
	// 					pair<string, MapNode*>("root", initMapNode()));

	// buffers for adding, deleting, modifying
	// my_dynamic_machine->name = VectorInitVector(); // strings
	// my_dynamic_machine->start_children = VectorInitVector();  // array of strings
	// my_dynamic_machine->children = VectorInitVector(); // array of strings
	// my_dynamic_machine->next_states = VectorInitVector(); // array of strings
	// my_dynamic_machine->value = DataInitDataInt(0);

	// my_dynamic_machine->trie_tree_dict = TrieTreeInitTrieTree();
	//
	// my_dynamic_machine->my_search = NULL;
	// my_dynamic_machine->my_insert = NULL;
	// my_dynamic_machine->my_delete = NULL;

// 	return my_dynamic_machine;
// }

// Vector* DynamicMachineAppendState(ContextualStateChart* my_machine, State* state)
// {
// 	// append state
// 	VectorAppend(my_machine->states, state);
// 	// insert word into trie

// 	Vector* new_state_name = TrieTreeInsertWords(my_machine->state_names, state->name);

// 	// update the state's name
// 	// copy the extra parts over
// 	for(int i = 0; i < VectorGetPopulation(new_state_name); i++)
// 	{
// 		// we are out of bounds for the current state name
// 		if(i >= VectorGetPopulation(state->name))
// 		{
// 			// string new_name_part = *((string*) VectorGetItem(new_state_name, i));
// 			// // copy the string
// 			// string next_name_part = new_name_part;
// 			// VectorAppendString(state->name, next_name_part);
// 		}
// 	}
// 	return new_state_name;
// }
// State* DynamicStateGetState(ContextualStateChart* my_machine, Vector* name)
// {
// 	return (State*) VectorGetItem(
// 									my_machine->states,
// 									TrieTreeSearch(	my_machine->state_names,
// 													name));
// }

// State* DynamicMachineRunStates(ContextualStateChart* my_machine, State* parent_state, State* current_state/* unused */, Vector* state_names)
// { 
	// Vector* state_names is a vector of vectors holding strings
	// run through a vector of state names and record the index values of the passing states
	// if(state_names != NULL)
	// {
		// if(parent_state != NULL)
		// {
		// 	VectorPrintStrings(parent_state->name);

		// }
		// if(current_state != NULL)
		// {
		// 	VectorPrintStrings(current_state->name);

		// }
		// VectorPrintStrings(parent_state->name);
		// VectorPrintStrings(current_state->name);

// 		Vector* winning_state = NULL;
// 		bool state_changed = false;
// 		// printf()
// 		// 
// 		for(int i = 0; i < VectorGetPopulation(state_names); i++)
// 		{
// 			Vector* state_name = (Vector*) VectorGetItem(state_names, i);
// 			// VectorPrintStrings(state_name);
// 			if(state_name != NULL)
// 			{
// 				// get the state id
// 				int state_id = TrieTreeSearch(my_machine->state_names, state_name);
// 				if(state_id == -1)
// 				{
// 					printf("this state doesn't exist\n");
// 					// VectorPrintStrings(state_name);
// 					printf("\n");
// 					exit(1);

// 				}
// 				// printf("state id %i\n", state_id);
// 				// get the state
// 				State* state = (State*) VectorGetItem(my_machine->states, state_id);
// 				// run the state
// 				// if(state->function(my_machine, parent_state, state))
// 				// {
// 				// 	// printf("winning state\n");

// 				// 	winning_state = state_name;
// 				// 	// VectorPrintStrings(winning_state);
// 				// 	// printf("\n");
// 				// 	state_changed = true;
// 				// 	break;
// 				// }
// 				// else
// 				// {
// 				// 	// printf("state failed\n");
// 				// }
				
// 			}

// 		}
// 		if(!state_changed)
// 		{
// 			return NULL;
// 		}
// 		// get the state

// 		return DynamicStateGetState(my_machine, winning_state);
// 	}
// 	return NULL;
// }


// int DynamicMachineRunStates2(ContextualStateChart* my_machine, State* parent_state, Vector* state_names)
// {
	// Vector* state_names is a vector of vectors holding strings
	// run through a vector of state names and record the index values of the passing states
	// if(state_names != NULL)
	// {
		// if(parent_state != NULL)
		// {
		// 	VectorPrintStrings(parent_state->name);

		// }
		// if(current_state != NULL)
		// {
		// 	VectorPrintStrings(current_state->name);

		// }
		// VectorPrintStrings(parent_state->name);
		// VectorPrintStrings(current_state->name);

// 		int winning_state_id = -1;
// 		bool state_changed = false;
// 		// printf()
// 		// 
// 		for(int i = 0; i < VectorGetPopulation(state_names); i++)
// 		{
// 			Vector* state_name = (Vector*) VectorGetItem(state_names, i);
// 			// VectorPrintStrings(state_name);
// 			if(state_name != NULL)
// 			{
// 				// get the state id
// 				int state_id = TrieTreeSearch(my_machine->state_names, state_name);
// 				if(state_id == -1)
// 				{
// 					printf("this state doesn't exist\n");
// 					// VectorPrintStrings(state_name);
// 					printf("\n");
// 					exit(1);

// 				}
// 				// printf("state id %i\n", state_id);
// 				// get the state
// 				State* state = (State*) VectorGetItem(my_machine->states, state_id);
// 				// run the state
// 				// if(state->function(my_machine, parent_state, state))
// 				// {
// 				// 	// printf("winning state\n");

// 				// 	winning_state_id = i;//state_name;
// 				// 	// VectorPrintStrings(winning_state);
// 				// 	// printf("\n");
// 				// 	state_changed = true;
// 				// 	break;
// 				// }
// 				// else
// 				// {
// 				// 	// printf("state failed\n");
// 				// }
				
// 			}

// 		}
// 		if(!state_changed)
// 		{
// 			return -1;
// 		}
// 		// get the state

// 		return winning_state_id;//DynamicStateGetState(my_machine, winning_state);
// 	}
// 	return -1;
// }


// DynamicState* DynamicStateGetVariable(DynamicMachine* my_machine, TrieTree* variables_trie_tree, DynamicState* current_state
// // , string variable
// )
// {

	// also fails if the variables aren't actually in the trie to begin with
	// will always fail unless the variables's children is a trie tree
	// int state_id =  TrieTreeGetVariable(variables_trie_tree, variable);
	// if(state_id <= -1)
	// {
	// 	return NULL;

	// }
	// // TrieTreePrintTrie(variables_trie_tree);
	// // TrieTreePrintTrieWords(variables_trie_tree);

	// DynamicState* state_retrieved = (DynamicState*) VectorGetItem(my_machine->states, state_id);
	// return state_retrieved;

// }

// Data* DataGetVariable(ContextualStateChart* my_machine, State* current_state
// ,string variable
// )
// {
	// machine, parent, variable_name
	// for each item in current_state.children
	/*
		root
			variables
				var1
				var2
			start_child_1
	*/
	// printf("variable to find %s\n", variable.c_str());
	// VectorPrintStrings(current_state->name);
	// for(int i = 0; i < VectorGetPopulation(current_state->children); i++)
	// {
		
	// 	Vector* child = (Vector*) VectorGetItem(current_state->children, i);
	// 	// VectorPrintStrings(child);
	// 	if(VectorGetPopulation(child) >= 1)
	// 	{
			// printf("got here\n");
			// string first_name = *((string*) VectorGetItem(child, 0));
			// will have many of "variables" in the general machine
			// if(first_name == "variables")
			// {
			// 	// printf("in variables\n");
			// 	int state_id = TrieTreeSearch(my_machine->state_names, child);
			// 	if(state_id == -1)
			// 	{
			// 		printf("failed\n");
			// 		return NULL;
			// 	}
			// 	// printf("state id %i\n", state_id);
			// 	DynamicState* variables_state = (DynamicState*) VectorGetItem(my_machine->states, state_id);
			// 	// VectorPrintStrings(variables_state->name);
			// 	// for(int i = 0; i < VectorGetPopulation(variables_state->_children); i++)
			// 	// {
			// 	// 	VectorPrintStrings( (Vector*) VectorGetItem(variables_state->_children, i) );

			// 	// }

			// 	DynamicState* variable_state = DynamicStateGetVariable(my_machine, variables_state->_children, current_state, variable);
			// 	if(variable_state == NULL)
			// 	{
			// 		printf("no state\n");
			// 		return NULL;
			// 	}
			// 	// VectorPrintStrings(variable_state->name);

			// 	return variable_state->value;

			// }
	// 	}

	// }
	// return NULL;
		// if the item has length 1 and the first string == "variables"
			// search the variable's children for a variable having the first name == variable
				// complete the pattern and get the state the variable links to
				// DynamicStateGetVariable

// }
// Data* getVariable2(DynamicMachine* my_machine, DynamicState* parent_state, string variable)
// {
// 	// machine, parent, variable_name
// 	// assume we have the following tree
// 	/*
// 		root
// 			variables
// 				var1
// 				var2
// 			start_child_1
// 	*/
// 	// for each item in current_state.children
// 	printf("variable to find %s\n", variable.c_str());
// 	for(int i = 0; i < VectorGetPopulation(parent_state->children); i++)
// 	{
		
// 		Vector* child = (Vector*) VectorGetItem(parent_state->children, i);
// 		VectorPrintStrings(child);
// 		if(VectorGetPopulation(child) >= 1)
// 		{
// 			// printf("got here\n");
// 			string first_name = *((string*) VectorGetItem(child, 0));
// 			// will have many of "variables" in the general machine
// 			if(first_name == "variables")
// 			{
// 				printf("in variables\n");
// 				int state_id = TrieTreeSearch(my_machine->state_names, child);
// 				if(state_id == -1)
// 				{
// 					printf("failed\n");
// 					return NULL;
// 				}
// 				printf("state id %i\n", state_id);
// 				DynamicState* variables_state = (DynamicState*) VectorGetItem(my_machine->states, state_id);
// 				VectorPrintStrings(variables_state->name);
// 				DynamicState* variable_state = DynamicStateGetVariable(my_machine, variables_state->_children, parent_state, variable);
// 				if(variable_state == NULL)
// 				{
// 					printf("no state\n");
// 					return NULL;
// 				}
// 				return variable_state->value;

// 			}
// 		}

// 	}
// 	return NULL;
// 		// if the item has length 1 and the first string == "variables"
// 			// search the variable's children for a variable having the first name == variable
// 				// complete the pattern and get the state the variable links to
// 				// DynamicStateGetVariable

// }


// string DataGetString(Data* variable)
// {
// 	return variable->_string;
// }
// int DataGetInt(Data* variable)
// {
// 	return variable->_int;
// }
// float DataGetFloat(Data* variable)
// {
// 	return variable->_float;
// }
// void DataSetString(Data* variable
// // , string new_string
// )
// {
// 	// variable->_string = new_string;
// }
// void DataSetInt(Data* variable, int new_int)
// {
// 	variable->_int = new_int;
// }
// void DataSetFloat(Data* variable, float new_float)
// {
// 	variable->_float = new_float;
// }
// what if parent_state is the control flow state(current state is child variable)
// parent state holds the parent state as a variable(so the machine's parent state can be found and the 
// varaible obtained)
bool recordA(ContextualStateChart* my_machine, int parent_state, int current_state)
{
	printf("recordA\n");
	// string input_string = DataGetString(DataGetVariable(my_machine, parent_state, "input_string"));

	// printf("input_string = %s\n", my_variable.c_str());

	// int i = DataGetInt(DataGetVariable(my_machine, parent_state, "i"));

	// int a_count = DataGetInt(DataGetVariable(my_machine, parent_state, "a_count"));
	// printf("i = %i\n", i);
	// printf("a_count %i\n", a_count);

	// printf("first character %c\n", my_variable[i]);
	// ++my_a_count returns the value after incrementing it, my_a_count++ returns the value before incrememnting it
	// DataSetInt(DataGetVariable(my_machine, parent_state, "i"), ++my_a_count);
	// int x = DataGetInt(DataGetVariable(my_machine, parent_state, "i"));
	// printf("i = %i\n", x);

	// get vars using current state

	// if the current char at input is 'a'
	// if(i < input_string.size())
	// {
	// 	if(input_string[i] == 'a')
	// 	{
	// 		DataSetInt(DataGetVariable(my_machine, parent_state, "i"), i + 1);
	// 		DataSetInt(DataGetVariable(my_machine, parent_state, "a_count"), a_count + 1);
	// 		return true;
	// 	}
	// }
	
	
		// increment a count
		// return true
	// return false
	return false;
}
bool recordB(ContextualStateChart* my_machine, int parent_state, int current_state)
{
	printf("recordB \n");
	// string input_string = DataGetString(DataGetVariable(my_machine, parent_state, "input_string"));


	// int i = DataGetInt(DataGetVariable(my_machine, parent_state, "i"));
	// int a_count = DataGetInt(DataGetVariable(my_machine, parent_state, "a_count"));
	// int b_count = DataGetInt(DataGetVariable(my_machine, parent_state, "b_count"));

	// if the current char at input is 'a'
	// if(i < input_string.size())
	// {
	// 	if(input_string[i] == 'b')
	// 	{
	// 		i += 1;
	// 		b_count += 1;

	// 		if(b_count <= a_count)
	// 		{

	// 			DataSetInt(DataGetVariable(my_machine, parent_state, "i"), i);
	// 			DataSetInt(DataGetVariable(my_machine, parent_state, "b_count"), b_count);

	// 			return true;
	// 		}

	// 		return false;
	// 	}
	// }
	
	
	return false;
}
bool recordC(ContextualStateChart* my_machine, int parent_state, int current_state)
{
	printf("recordC \n");
	// string input_string = DataGetString(DataGetVariable(my_machine, parent_state, "input_string"));


	// int i = DataGetInt(DataGetVariable(my_machine, parent_state, "i"));
	// int b_count = DataGetInt(DataGetVariable(my_machine, parent_state, "b_count"));
	// int c_count = DataGetInt(DataGetVariable(my_machine, parent_state, "c_count"));
	// printf("%i %i %i\n", i, input_string.size(), i < input_string.size());
	// if the current char at input is 'a'
	// if(i < input_string.size())
	// {
	// 	if(input_string[i] == 'c')
	// 	{
	// 		i += 1;
	// 		c_count += 1;
	// 		if(c_count <= b_count)
	// 		{
	// 			DataSetInt(DataGetVariable(my_machine, parent_state, "i"), i);
	// 			DataSetInt(DataGetVariable(my_machine, parent_state, "c_count"), c_count);

	// 			return true;
	// 		}

	// 		return false;
	// 	}
	// }
	
	return false;

	
}
// bool endOfInput(DynamicMachine* my_machine, DynamicState* parent_state, DynamicState* current_state)
// {
// 	printf("endOfInput \n");
// 	// string input_string = DataGetString(DataGetVariable(my_machine, parent_state, "input_string"));


// 	// int i = DataGetInt(DataGetVariable(my_machine, parent_state, "i"));
// 	// return i >= input_string.size();
// }

bool returnTrue(ContextualStateChart* my_machine, int parent_state, int current_state)
{
	return true;
}
bool returnFalse(ContextualStateChart* my_machine, int parent_state, int current_state)
{
	printf("returning false\n");
	return false;
}

				// DataGetVariable(my_machine, current_state, "i")  
				// 	start at current state
				// 	go to the variables child
				// 	get the variables child with name starting at "i"
				// 		this could be just "i" or ["i", "x", "y"]
				// 		assume the unique "i" is attached to "control flow graph" at child "variables"

void DynamicMachineTest()
{
	// ContextualStateChart* my_machine = DynamicMachineInitDynamicMachine();
	// Vector* name, // strings
	// 	Vector* start_children,  // array of array of strings
	// 	Vector* children, // array of array of strings
	// 	Vector* next_states, // array of array of strings
	//  bool (*function) (DynamicMachine* my_machine, DynamicState* current_state)
	// Data* value

	// make a sequence to parse
	// a^nb^nc^n

	/*
	control flow graph
		children
			variables
				children
					a_count
						Data
							0
					b_count
						Data
							0
					c_count
						Data
							0
					input_string
						Data
							"abc"
					i
						Data
							0
			a
				f
					recordA
				next
					a | (b | c)
			b
				f
					recordBAndCheckWithA
				next
					b | c
			c
				f
					recordCAndCheckWithA
				next
					c | end
			end
				f
					returnTrue
				next
					none
	*/
	// DynamicMachineAppendState(
	// 	my_machine,
	// 	DynamicStateInitDynamicState(
	// 		VectorAddStringToVectorGeneral(
	// 			(string [])
	// 			{
	// 				"state 1", "x", "y\""
	// 			}, 3
	// 		),
	// 		// VectorAddStringToVector3("state 1", "x", "y\""),

	// 		NULL,
	// 		NULL,
	// 		NULL,
	// 		NULL,
	// 		returnFalse,
	// 		DataInitDataInt(2)
	// 	)
	// );
	// state name in trie test
	// TrieTreePrintTrieWords(my_machine->state_names);
	// State* x = (State*) VectorGetItem(my_machine->states, 0);
	// out of bounds with VectorGetItem
	// string* y = (string*) VectorGetItem(x->name, 2);
	// state object name test
	// printf("%s\n", y->c_str());
	// data mutation test
	// x->value->_int++;

	// retreive item again
	// State* x1 = (State*) VectorGetItem(my_machine->states, 0);

	// Data* z = x1->value;
	// printf("%i\n", z->_int);

	// x->function = returnFalse;
	// x->function(NULL, NULL, NULL);
	// Vector* state_names = VectorInitVector();
	// VectorAppend(
	// 	state_names,
	// 	VectorAddStringToVectorGeneral(
	// 		(string [])
	// 		{
	// 			"state 1", "x", "y\""
	// 		}, 3
	// 	)

	// );

	// State* winning_state = DynamicMachineRunStates(my_machine, NULL, x, state_names);
	// printf("winning state \n");
	// if(winning_state == NULL)
	// {
	// 	printf("no state one\n");
	// }
	// VectorPrintStrings(winning_state->name);
	// we are going to recognize a context-sensitive grammer
	// a^nb^nc^n with 4 states without using text rewriting rules
	// each state is very clear on the expected sequence following it
	// there is no need for a hierarchy in the state structure
			// all we know is the variables are addressed by unique names
	// Vector* a_count = 	DynamicMachineAppendState(
	// 						my_machine,
	// 						DynamicStateMakeVariable(
	// 							"a_count",
	// 							VectorCombineVectors1(VectorAddStringToVector1("variables")),
	// 							DataInitDataInt(0)
	// 						)
	// 					);

	// Vector* b_count = 	DynamicMachineAppendState(
	// 						my_machine,
	// 						DynamicStateMakeVariable(
	// 							"b_count",
	// 							VectorCombineVectors1(VectorAddStringToVector1("variables")),
	// 							DataInitDataInt(0)
	// 						)
	// 					);

	// Vector* c_count = 	DynamicMachineAppendState(
	// 						my_machine,
	// 						DynamicStateMakeVariable(
	// 							"c_count",
	// 							VectorCombineVectors1(VectorAddStringToVector1("variables")),
	// 							DataInitDataInt(0)
	// 						)
	// 					);

	// Vector* input_string = 	DynamicMachineAppendState(
	// 							my_machine,
	// 							DynamicStateMakeVariable(
	// 								"input_string",
	// 								VectorCombineVectors1(VectorAddStringToVector1("variables")),
	// 								DataInitDataString("aabbcc")
	// 							)
	// 						);
	// will not appear in printouts, but does exist in the trie tree
	// there is no word setup to connect to it
	// Vector* i_1 = 	DynamicMachineAppendState(
	// 					my_machine,
	// 					DynamicStateMakeVariable(
	// 						"i",
	// 						VectorCombineVectors1(VectorAddStringToVector1("variables")),
	// 						DataInitDataInt(0)
	// 					)
	// 				);
	// TrieTreePrintTrie(my_machine->state_names);
	// TrieTreePrintWordTrie(my_machine->state_names);
	// works to here
	// exit(1);
	// children needs to be a trie tree but constructor has no support for it
	// DynamicState* DynamicStateInitDynamicStateVariableContainer(
	// 					Vector* name, // strings
	// 					TrieTree* _children,
	// 					int container_type)
	// TrieTree* TrieTreeInsertEdges(TrieTree* my_trie_tree, Vector* names /* vectors of strings*/)
// Vector* VectorCombineVectorsGeneral(Vector* vectors[], int size)

	// this creates a local scode so the variable name chosen by the user will work
	// Vector* variables_1 = 	DynamicMachineAppendState(
	// 							my_machine,
	// 							DynamicStateInitDynamicStateVariableContainer(
	// 								VectorAddStringToVector1("variables"),
	// 								VectorCombineVectors1(VectorAddStringToVector1("control flow graph")),
	// 								// returns the trie tree with items inserted										
	// 								TrieTreeInsertEdges(
	// 									my_machine->state_names,
	// 									TrieTreeInitTrieTree(),
	// 									// inserting to the local trie resulted in
	// 									// new state ids to be generated
	// 									VectorCombineVectorsGeneral( (Vector* []) {
	// 											a_count,
	// 											b_count,
	// 											c_count,
	// 											input_string,
	// 											i_1
	// 										},
	// 										5
	// 									)
	// 								),
	// 								// container type id
	// 								trie_tree
	// 							)
	// 						);

	// Vector* variables_2 = 	DynamicMachineAppendState(
	// 							my_machine,
	// 							DynamicStateInitDynamicState(
	// 								VectorAddStringToVector1("variables"),
	// 								NULL,
	// 								NULL,
	// 								VectorCombineVectorsGeneral((Vector* []) {
	// 									a_count,
	// 									b_count,
	// 									c_count,
	// 									i_1
	// 									},
	// 									4
										
	// 								),
	// 								NULL,
	// 								returnTrue,
	// 								NULL
	// 							)
	// 						);
			// TrieTreeDeleteWords(my_machine->state_names, variables_2);


	// control flow graph
	// Vector* control_flow_graph = 	DynamicMachineAppendState(
	// 									my_machine,
	// 									DynamicStateInitDynamicState(
	// 										VectorAddStringToVector1("control flow graph"),
	// 										NULL,
	// 										NULL,
	// 										VectorCombineVectors2(
	// 											// must be same name as the variables state
	// 											variables_1,
	// 											VectorAddStringToVector1("root")

	// 										),
	// 										NULL,
	// 										returnTrue,
	// 										NULL
	// 									)
	// 								);

	// DynamicMachineAppendState(
	// 	my_machine,
	// 	DynamicStateInitDynamicState(
	// 		VectorAddStringToVector1("root"),
	// 		NULL,
	// 		NULL,
	// 		VectorCombineVectors1(VectorAddStringToVector1("a")),
	// 		NULL,
	// 		returnTrue,
	// 		NULL
	// 	)
	// );
				
	// a
	// 	f
	// 		recordA
	// 	next
	// 		a | (b | c) => a | b
	// It's assumed the state names are added in as a unique sequence of string literals
	// DynamicMachineAppendState(
	// 	my_machine,
	// 	DynamicStateInitDynamicState(
	// 		VectorAddStringToVector1("a"),
	// 		NULL,
	// 		NULL,
	// 		NULL,
	// 		VectorCombineVectors2(
	// 			VectorAddStringToVector1("a"),
	// 			VectorAddStringToVector1("b")
	// 		),
	// 		recordA,
	// 		NULL
	// 	)
	// );
	// DynamicMachineAppendState(
	// 	my_machine,
	// 	DynamicStateInitDynamicState(
	// 		VectorAddStringToVector1("b"),
	// 		NULL,
	// 		NULL,
	// 		NULL,
	// 		VectorCombineVectors2(
	// 			VectorAddStringToVector1("b"),
	// 			VectorAddStringToVector1("c")
	// 		),
	// 		recordB,
	// 		NULL
	// 	)
	// );
	// DynamicMachineAppendState(
	// 	my_machine,
	// 	DynamicStateInitDynamicState(
	// 		VectorAddStringToVector1("c"),
	// 		NULL,
	// 		NULL,
	// 		NULL,
	// 		VectorCombineVectors2(
	// 			VectorAddStringToVector1("c"),
	// 			VectorAddStringToVector1("end of input")
	// 		),
	// 		recordC,
	// 		NULL
	// 	)
	// );
	// DynamicMachineAppendState(
	// 	my_machine,
	// 	DynamicStateInitDynamicState(
	// 		VectorAddStringToVector1("end of input"),
	// 		NULL,
	// 		NULL,
	// 		NULL,
	// 		VectorInitVector(),
	// 		endOfInput,
	// 		NULL
	// 	)
	// );

			// if current_state == "control flow graph"
			/*
				DataGetVariable(current_state, "i")  
					start at current state
					go to the variables child
					get the variables child with name starting at "i"
						this could be just "i" or ["i", "x", "y"]
						assume the unique "i" is attached to "control flow graph" at child "variables"
				"OOP"
					has a variables category
					access variables using dot "style" in a function call
					
				"functional"
					each function can run functional code
					each state translates to 1 line of code or n lines of relativelly flat code(1-2 levels of nesting)

				"logic"
					parent child relationships
					sibling relationships
					second context in name can also be an edge category

				all
					each state can run code in a turing complete language
			*/
		// TrieTreePrintTrieWords(my_machine->state_names);
		// TrieTreePrintTrie(my_machine->state_names);
		// exit(1);
		// TrieTreePrintWordTrie(my_machine->state_names);
		// int state_id = TrieTreeSearch(my_machine->state_names, VectorAddStringToVector1("input_string"));

		// DynamicState* x2 = (DynamicState*) VectorGetItem(my_machine->states, state_id);

		// printf("%s\n", ((string*) VectorGetItem(x2->name, 0))->c_str());
		// Data* z2 = x2->value;
		// printf("%s done\n", z2->_string.c_str());

		// printf("find variable\n");
		// parent of current state
		// got to be a better way to get the state
		// DynamicStateGetState(my_machine, Vector* name)
		// DynamicState* my_control_flow_graph = (DynamicState*) VectorGetItem(
		// 															my_machine->states,
		// 															TrieTreeSearch(	my_machine->state_names,
		// 																			control_flow_graph));
		// VectorPrintStrings(my_control_flow_graph->name);
		// string my_variable = DataGetString(DataGetVariable(my_machine, my_control_flow_graph, "input_string"));
		// printf("%i\n", my_variable);
		// printf("input_string = %s\n", my_variable.c_str());

		// Data* my_a_count = (Data*) DataGetVariable(my_machine, my_control_flow_graph, "i");
		// DataSetInt(my_a_count, 0);
		// printf("i = %i\n", my_a_count->_int);
		// bool result = recordA(my_machine, my_control_flow_graph, NULL);
		// printf("recordA is %i and i is %i\n", 	result,
		// 										DataGetInt(DataGetVariable(my_machine, my_control_flow_graph, "i")));
	// 	Vector* state_names = VectorInitVector();
	// 	VectorAppend(state_names, VectorAddStringToVector3(
		// have to get each item from the next states vector from a state state->next_states
	// 						"state 1",
	// 						"x",
	// 						"y\""));

		// printf("\n\nrunning\n");
		// (parent_state(child state at above level), child_state, ith_child(might need to save when poping), result of machine on current level)
		// take the current state(a parent state) and run this for the child machine
		// pretend the state works
		// DynamicState* working_state = DynamicStateGetState(my_machine, VectorAddStringToVector1("root"));
		// Vector* next_states = working_state->children;

		// while(working_state != NULL)
		// {
		// 	// need terms for handling the different kinds of neighbors for manually running
		// 	// more than 1 level
		// 	// the state that doesn't exists is ||?
		// 	// working_state = DynamicMachineRunStates(my_machine,
		// 	// 										// the parent state
		// 	// 										my_control_flow_graph,
		// 	// 										// this state is supposed to have a function associated with it
		// 	// 										working_state,
		// 	// 										// first time, should be the next states from root
		// 	// 										next_states);
		// 	printf("the winning state is\n");
		// 	if(working_state == NULL)
		// 	{
		// 		// no state won and there are neighbors
		// 		if(VectorGetPopulation(next_states) > 0)
		// 		{
		// 			printf("no state won so shut down machine or return false to the parent machine.\n");
		// 			// return false to caller
		// 		}
		// 		else // no state won but there were no neighbors
		// 		{
		// 			printf("at end of machine\n");
		// 			// return true to caller
		// 		}
		// 	}
		// 	else
		// 	{
		// 		// VectorPrintStrings(working_state->name);
		// 		next_states = working_state->next_states;

		// 	}
		// }
		printf("done\n\n");
		// exit(1);
		// input tested is "aabbcc"
		


}

// bool checkStateChar(string state, char my_char)
// {
// 	printf("%s %c\n", state.c_str(), my_char);
// 	if(state == "letters")
// 	{
		
// 		return (my_char >= 'A' && my_char <= 'Z') ||
// 				(my_char >= 'a' && my_char <= 'z');
// 	}
// 	else if(state == "digit")
// 	{
// 		return my_char >= '0' && my_char <= '9';
// 	}
// 	else if(state == "(")
// 	{

// 		return my_char == '(';
// 	}
// 	else if(state == ")")
// 	{
// 		return my_char == ')';
// 	}
// 	return false;
// }

bool charDispatch(ContextualStateChart* my_machine, int parent_state, int current_state)
{
	printf("charDispatch\n");
	// string input = DataGetString(DataGetVariable(my_machine, parent_state, "input"));


	// int i = DataGetInt(DataGetVariable(my_machine, parent_state, "i"));
	// if(i < input.size())
	// {
	// 	// string my_state = *((string*) VectorGetItem(current_state->name, 0));
	// 	if(checkStateChar(my_state, input[i]))
	// 	{
	// 		i += 1;
	// 		DataSetInt(DataGetVariable(my_machine, parent_state, "i"), i);

	// 		return true;
	// 	}
	// }
	
	return false;
}

// bool isNull(DynamicMachine* my_machine, DynamicState* parent_state, DynamicState* current_state)
// {
// 	printf("isNull\n");

// 	// string input = DataGetString(DataGetVariable(my_machine, parent_state, "input"));

// 	// int i = DataGetInt(DataGetVariable(my_machine, parent_state, "i"));
// 	// return i >= input.size();

// }

// Vector* duplicateNestedVectorsOfStrings(Vector* nested_vectors_of_strings)
// {
// 	Vector* new_collection_vectors = VectorInitVector();
// 	for(int i = 0; i < VectorGetPopulation(nested_vectors_of_strings); i++)
// 	{
// 		Vector* new_collection_strings = VectorInitVector();
// 		Vector* collection_strings = (Vector*) VectorGetItem(nested_vectors_of_strings, i);
// 		for(int j = 0; j < VectorGetPopulation(collection_strings); j++)
// 		{
// 			// string old_string = *((string*) VectorGetItem(collection_strings, j));
// 			// string new_string = old_string;
// 			// VectorAppendString(new_collection_strings, new_string);
// 		}
// 		VectorAppend(new_collection_vectors, new_collection_strings);
// 	}
// 	return new_collection_vectors;
// }
// void appendChildren(ContextualStateChart* machine,
// 					int last_state_added,
					
// 					int parent,
// 					int child,
// 					int ith_child,
// 					bool current_machine_status
// 					)
// {
// 	// take the integers and make states holding them as data so last_state_added has the state trackers setup for
// 	// the current level
// 	if(machine == NULL || last_state_added < 0 || parent < 0 || child < 0)
// 	{
// 		printf("we have no data to use\n");
// 		exit(1);
// 	}
// 	// storing the state in the memory is different from setting up the parent child relationships
// 	// in the _children
// 	// have to make the level_data state not link from the slot state
// 	State* last_state_added_state = (State*) VectorGetItem(machine->states, last_state_added);
// 	Vector* parent_level_name = last_state_added_state->name;
	// make another state holding the int as data not retreiving the states that already exist, because we are making trackers
	// Vector* parents = VectorCombineVectors1(parent_level_name);
	// make separate parent vectors or use same one?
	// separate so debugging is easier
	// Vector* parents_1 = duplicateNestedVectorsOfStrings(parents);
	// Vector* parents_2 = duplicateNestedVectorsOfStrings(parents);
	// Vector* parents_3 = duplicateNestedVectorsOfStrings(parents);

	// DynamicState* parent_data_state = DynamicStateMakeVariable2("parent", parents_1, DataInitDataInt(parent));
	// DynamicMachineAppendState(machine, parent_data_state);
	// DynamicState* child_data_state = DynamicStateMakeVariable2("child", parents_2, DataInitDataInt(child));
	// DynamicMachineAppendState(machine, child_data_state);

	// DynamicState* ith_child_data_state = DynamicStateMakeVariable2("ith_child", parents_3, DataInitDataInt(ith_child));
	// DynamicMachineAppendState(machine, ith_child_data_state);


	// TrieTreeInsertWords(last_state_added_state->_children, parent_data_state->name);
	// TrieTreeInsertWords(last_state_added_state->_children, child_data_state->name);
	// TrieTreeInsertWords(last_state_added_state->_children, ith_child_data_state->name);
	// last_state_added_state->container_type = 1;  // trie tree
	// get the state variable
	// add in the integers as state children variable
	// variable is now a container
	// DynamicState* DynamicStateInitDynamicStateVariableContainer(
	// 							Vector* name, // strings
	// 							Vector* parents,  // array of strings
	// 							TrieTree* _children,
	// 							int container_type)
	// maybe need a function to convert a variable state to a variable container state

// }
// push(StateMachine* machine, int parent, int child, int ith_child, int parent_slot_state )
// 		{
// 			append(state("stack_item", "level_data"]))
// 			appendChilren(state_added, parent, child, ith_child, false)

// 			append(state(["stack_item", "slot"]))
// 			appendParent(machine, ["stack_item", "slot"], parent_slot_state)

// 			history tree
// 			append(state(["stack_item", "history_level_data"]))
// 			appendStateChilren(parent, child, ith_child, false)

// 			append(state(["stack_item", "history_slot"]))
// 			appendParent(machine, ["stack_item", "history_slot"], parent_slot_state)

// 			getChildCounterpart(machine, ["control trackers"], "history_slot") -> 	
// 			state having children set as (parent, child, ith_child, false) from history_leveL_data
		
// 			["control trackers"]
// 				["stack_item", "history_slot", id.......]
// 				["stack_item", "slot", id......]

// 			// return history tracker and slot tracker

// 			return last state in machine(top of stack["stack_item", "slot", id......] because it was the last one added)
// 		}

// void DynamicStatePrintState(ContextualStateChart* my_machine, int state_id, int indents)
// {

// 	if(state_id < 0)
// 	{
// 		return;
// 	}
// 	// string my_indents = makeSpaces(indents);
// 	State* state = (State*) VectorGetItem(my_machine->states, state_id);
// 	// name
// 	// printf("%sname:\n%s", my_indents.c_str(), my_indents.c_str());
// 	// VectorPrintStrings(state->name);
// 	// flags
// 	// parents
// 	// printf("%sparents:\n%s", my_indents.c_str(), my_indents.c_str());	// the newlines are done in here
// 	// VectorPrintVectorOfStrings(state->parents);

// 	// start children
// 	// printf("%sstart children:\n%s", my_indents.c_str(), my_indents.c_str());
// 	// VectorPrintVectorOfStrings(state->start_children);

// 	// children
// 	// printf("%schildren:\n%s", my_indents.c_str(), my_indents.c_str());
// 	// VectorPrintVectorOfStrings(state->children);

// 	// _children
// 	// printf("%s_children:\n%s", my_indents.c_str(), my_indents.c_str());

// 	// TrieTreePrintTrieRecursive(my_machine->state_names, 0, my_indents);


// 	// next states
// 	// printf("%snext states:\n%s", my_indents.c_str(), my_indents.c_str());
// 	// VectorPrintVectorOfStrings(state->next_states);

// 	// function name
// }
// void DynamicMachinePrintStateTree(ContextualStateChart* my_machine, int state_id, int indents)
// {
// 	if(state_id < 0)
// 	{
// 		return;
// 	}
// 	DynamicStatePrintState(my_machine, state_id, indents);

// 	State* state = (State*) VectorGetItem(my_machine->states, state_id);

// 	for(int i = 0; i < VectorGetPopulation(state->children); i++)
// 	{
// 		Vector* child = (Vector*) VectorGetItem(state->children, i);
// 		int new_id = TrieTreeSearch(my_machine->state_names, child);
// 		DynamicMachinePrintStateTree(my_machine, new_id, indents + 3);
// 	}

// }
void DynamicMachineTest2()
{
	// '''
		// (word##)
		// (#word#)
		// ()

		// (Im_a_word5)
		// (Im_a_word56)
		// (4Im_a_word5)
		// ()
		// '''
		/*
		start
			vars
				input
				i
			(
				letters_numbers_null
					null (done)
					letters## (done)
					#letters# (done)

			)
		*/
	// ContextualStateChart* my_machine_2 = DynamicMachineInitDynamicMachine();

	// add a root

// DynamicMachineAppendState(
// 		my_machine_2,
// 		DynamicStateInitDynamicState2(
// 			VectorAddStringToVector1("root"),
// 			// child and start child of "root" and parent to (, ), variables, and letters_digits_null
// 			!is_start_child,
// 			has_down_links,
// 			// the none state is fake
// 			VectorCombineVectors1(
// 				VectorAddStringToVector1("none")),
// 			VectorCombineVectors1(
// 				VectorAddStringToVector1("start")),
// 			VectorCombineVectorsGeneral((Vector* []) {
// 				// defined name for variables in DataGetVariable
// 				VectorAddStringToVector1("start")},
// 				1
// 			),
// 			VectorInitVector(),
// 			returnTrue,
// 			NULL
// 		)
// 	);

	// DynamicMachineAppendState(
	// 	my_machine_2,
	// 	DynamicStateInitDynamicState2(
	// 		VectorAddStringToVector1("start"),
	// 		// child and start child of "root" and parent to (, ), variables, and letters_digits_null
	// 		is_start_child,
	// 		has_down_links,
	// 		// the root is fake
	// 		VectorCombineVectors1(
	// 			VectorAddStringToVector1("root")),
	// 		VectorCombineVectors1(
	// 			VectorAddStringToVector1("(")),
	// 		VectorCombineVectorsGeneral((Vector* []) {
	// 			// defined name for variables in DataGetVariable
	// 			VectorAddStringToVector1("variables"),
	// 			VectorAddStringToVector1("("),
	// 			VectorAddStringToVector1("letters_digits_null"),
	// 			VectorAddStringToVector1(")")},
	// 			4
	// 		),
	// 		VectorInitVector(),
	// 		returnTrue,
	// 		NULL
	// 	)
	// );

	// Vector* input = DynamicMachineAppendState(
	// 					my_machine_2,
	// 					DynamicStateMakeVariable(
	// 						"input",
	// 						VectorCombineVectors1(
	// 							VectorAddStringToVector1("variables")),
	// 						DataInitDataString("(Im_a_word5)")
	// 						)
	// 				);

	// Vector* i = DynamicMachineAppendState(
	// 				my_machine_2,
	// 				DynamicStateMakeVariable(
	// 					"i",
	// 					VectorCombineVectors1(
	// 						VectorAddStringToVector1("variables")),
	// 					DataInitDataInt(0)
	// 				)
	// 			);
	// DynamicMachineAppendState(	my_machine_2,
	// 	DynamicStateInitDynamicStateVariableContainer(
	// 		VectorAddStringToVector1("variables"),
	// 		VectorCombineVectors1(
	// 			VectorAddStringToVector1("start")),
	// 		// assumes input and i already are in the tree
	// 		TrieTreeInsertEdges(
	// 			my_machine_2->state_names,
	// 			TrieTreeInitTrieTree(),
	// 			// inserting to the local trie resulted in
	// 			// new state ids to be generated
	// 			VectorCombineVectors2(
	// 				input,
	// 				i
	// 				)
	// 			)
	// 		,
	// 		trie_tree
	// 	)
	// );
	


	// DynamicMachineAppendState(
	// 	my_machine_2,
	// 	DynamicStateInitDynamicState2(
	// 		VectorAddStringToVector1("("),
	// 		is_start_child,
	// 		!has_down_links,
	// 		VectorCombineVectors1(
	// 			VectorAddStringToVector1("start")),
	// 		// start children
	// 		VectorInitVector(),
	// 		// children
	// 		VectorInitVector(),
	// 		// next states
	// 		VectorCombineVectors1(
	// 			VectorAddStringToVector1("letters_digits_null")),
	// 		charDispatch,
	// 		NULL
	// 	)
	// );
	// DynamicMachineAppendState(
	// 	my_machine_2,
	// 	DynamicStateInitDynamicState2(
	// 		VectorAddStringToVector1("letters_digits_null"),
	// 		!is_start_child,
	// 		has_down_links,
	// 		VectorCombineVectors1(
	// 			VectorAddStringToVector1("start")),
	// 		VectorCombineVectorsGeneral(
	// 			(Vector* [])
	// 			{
	// 				VectorAddStringToVector2("letters", "0"),
	// 				VectorAddStringToVector2("digit", "2"),
	// 				VectorAddStringToVector1("null")
	// 			}, 3
	// 		),
	// 		// func((type[]){val1,val2,val3,val4,0});
	// 		VectorCombineVectorsGeneral((Vector* []) {
	// 			VectorAddStringToVector2("letters", "0"),
	// 			VectorAddStringToVector2("letters", "1"),
	// 			VectorAddStringToVector2("digit", "0"),
	// 			VectorAddStringToVector2("digit", "1"),
	// 			VectorAddStringToVector2("digit", "2"),
	// 			VectorAddStringToVector1("null")},
	// 			6

	// 		),
	// 		VectorInitVector(),
	// 		returnTrue,
	// 		NULL
	// 	)
	// );
	// letters 0, digit 0, digit 1
	// digit 2, letters 1, digit 3
	// DynamicMachineAppendState(
	// 	my_machine_2,
	// 	DynamicStateInitDynamicState2(
	// 		VectorAddStringToVector2("letters", "0"),
	// 		is_start_child,
	// 		!has_down_links,
	// 		VectorCombineVectors1(
	// 			VectorAddStringToVector1("letters_digits_null")),
	// 		// start children
	// 		VectorInitVector(),
	// 		// children
	// 		VectorInitVector(),
	// 		// next states
	// 		VectorCombineVectors1(
	// 			VectorAddStringToVector2("digit", "0")),
	// 		// for now
	// 		charDispatch,
	// 		NULL
	// 	)
	// );
	// DynamicMachineAppendState(
	// 	my_machine_2,
	// 	DynamicStateInitDynamicState2(
	// 		VectorAddStringToVector2("letters", "1"),
	// 		!is_start_child,
	// 		!has_down_links,
	// 		VectorCombineVectors1(
	// 			VectorAddStringToVector1("letters_digits_null")),
	// 		// start children
	// 		VectorInitVector(),
	// 		// children
	// 		VectorInitVector(),
	// 		// next states
	// 		VectorCombineVectors1(
	// 			VectorAddStringToVector2("digit", "3")),
	// 		// for now
	// 		charDispatch,
	// 		NULL
	// 	)
	// );

	// DynamicMachineAppendState(
	// 	my_machine_2,
	// 	DynamicStateInitDynamicState2(
	// 		VectorAddStringToVector2("digit", "0"),
	// 		is_start_child,
	// 		!has_down_links,
	// 		VectorCombineVectors1(
	// 			VectorAddStringToVector1("letters_digits_null")),
	// 		// start children
	// 		VectorInitVector(),
	// 		// children
	// 		VectorInitVector(),
	// 		// next states
	// 		VectorCombineVectors1(
	// 			VectorAddStringToVector2("digit", "1")),
	// 		// for now
	// 		charDispatch,
	// 		NULL
	// 	)
	// );
	
	// DynamicMachineAppendState(
	// 	my_machine_2,
	// 	DynamicStateInitDynamicState2(
	// 		VectorAddStringToVector2("digit", "1"),
	// 		!is_start_child,
	// 		!has_down_links,
	// 		VectorCombineVectors1(
	// 			VectorAddStringToVector1("letters_digits_null")),
	// 		// start children
	// 		VectorInitVector(),
	// 		// children
	// 		VectorInitVector(),
	// 		// next states
	// 		VectorInitVector(),
	// 		// for now
	// 		charDispatch,
	// 		NULL
	// 	)
	// );
	// DynamicMachineAppendState(
	// 	my_machine_2,
	// 	DynamicStateInitDynamicState2(
	// 		VectorAddStringToVector2("digit", "2"),
	// 		!is_start_child,
	// 		!has_down_links,
	// 		VectorCombineVectors1(
	// 			VectorAddStringToVector1("letters_digits_null")),
	// 		// start children
	// 		VectorInitVector(),
	// 		// children
	// 		VectorInitVector(),
	// 		// next states
	// 		VectorCombineVectors1(
	// 			VectorAddStringToVector2("letters", "1")),
	// 		// for now
	// 		charDispatch,
	// 		NULL
	// 	)
	// );
	// DynamicMachineAppendState(
	// 	my_machine_2,
	// 	DynamicStateInitDynamicState2(
	// 		VectorAddStringToVector2("digit", "3"),
	// 		!is_start_child,
	// 		!has_down_links,
	// 		VectorCombineVectors1(
	// 			VectorAddStringToVector1("letters_digits_null")),
	// 		// start children
	// 		VectorInitVector(),
	// 		// children
	// 		VectorInitVector(),
	// 		// next states
	// 		VectorInitVector(),
	// 		// for now
	// 		charDispatch,
	// 		NULL
	// 	)
	// );
	// DynamicMachineAppendState(
	// 	my_machine_2,
	// 	DynamicStateInitDynamicState2(
	// 		VectorAddStringToVector1("null"),
	// 		is_start_child,
	// 		!has_down_links,
	// 		VectorCombineVectors1(
	// 			VectorAddStringToVector1("letters_digits_null")),
	// 		// start children
	// 		VectorInitVector(),
	// 		// children
	// 		VectorInitVector(),
	// 		// next states
	// 		VectorInitVector(),
	// 		// for now
	// 		isNull,
	// 		NULL
	// 	)
	// );
	// TrieTreePrintTrieWords(my_machine_2->state_names);

	printf("ready to start machine\n");
	// need a stack (parent, child, ith_child, did_machine_pass)
	// each stack item ["stack_item", level_data", stack_item_id]
		// children => (parent, child, ith_child, did_machine_pass)

	// ["stack_item", "slot", stack_item_id]
		// children => [["stack_item", "slot", stack_item_id].....]
	// track ["stack_item", "slot" ,...]
	// change pattern to refer to ["stack_item", "level_data", ....]
	// both items must be added at the same time for a pattern change to work
	// Vector* control_flow_graph = DynamicMachineAppendState(	my_machine,
	// 				DynamicStateInitDynamicState(VectorAddStringToVector1(
	// 									"control flow graph"),
	// 									NULL,
	// 								NULL,
	// 								VectorCombineVectors2(
	// 									// must be same name as the variables state
	// 									variables_1,
	// 									VectorAddStringToVector1("root")

	// 								),
	// 								NULL,
	// 								returnTrue,
	// 								NULL
	// 								)
	// 				);

	// DynamicState* working_state = DynamicStateGetState(my_machine_2, VectorAddStringToVector1("start"));
	// what if a stack item was made
	// Vector* parent = (Vector*) VectorGetItem(working_state->parents, 0);
	// VectorPrintStrings(parent);
	// printf("printing state machine\n");
	// DynamicMachinePrintStateTree(my_machine_2, 0, 0);
	// make sure the slot sate and level data state are made at the same time and have the same parent(so debugging
	// 1 to 3 timelines is possible and not a headache problem)
	// just make it all here then put it into a function
	// what do we have?
	// parent state (no)
	// child state (yes, start)
	// ith child (yes, 0)
	// value of machine when it's over (yes, false for now)
	// slot state for the stack (no)
	// level state for the data associated with a slot (no)
	// root of stack
	// Vector* stack_item_name = DynamicMachineAppendState(	my_machine_2,
	// // name, parents, _children
	// 	DynamicStateInitDynamicStateVariableContainer(
	// 		VectorAddStringToVector2("stack item", "slot"),
	// 		VectorCombineVectors1(
	// 			VectorAddStringToVector1("root")),
	// 		TrieTreeInitTrieTree(),
	// 		trie_tree
	// 	)
	// );
	// get the root
	// State* root = (State*) VectorGetItem(my_machine_2->states, 0);
	// set roots child to
	// VectorAppend(root->children, stack_item_name);
	// slot 1 of stack
	// Vector* stack_item_name_1 = DynamicMachineAppendState(	my_machine_2,
	// // name, parents, _children
	// 	DynamicStateInitDynamicStateVariableContainer(
	// 		VectorAddStringToVector2("stack item", "slot"),
	// 		VectorCombineVectors1(
	// 			VectorAddStringToVector2("stack item", "slot")),
	// 		// slot 2 of all timelines would go here
	// 		TrieTreeInitTrieTree(),
	// 		trie_tree
	// 	)
	// );
	// DynamicState* root_stack_item = (DynamicState*) VectorGetItem(my_machine_2->states,
	// 	TrieTreeSearch(my_machine_2->state_names, stack_item_name));
	
	// VectorAppend(root_stack_item->children, stack_item_name_1);

	// make the data states
	// make a state holding the name of the root
	// need a vector container constructor for the Data* type
	// Data* DataInitDataVector(Vector* container)
	// Vector* saved_root = DynamicMachineAppendState(
	// 						my_machine_2,
	// 						DynamicStateMakeVariable(
	// 							"root",
	// 							VectorInitVector(),
	// 							DataInitDataVector(root->name)
	// 						)
	// 					);

	// Vector* stack_item_level_data = DynamicMachineAppendState(	my_machine_2,
	// 									// name, parents, _children
	// 									DynamicStateInitDynamicStateVariableContainer(
	// 										VectorAddStringToVector2("stack item", "level_data"),
	// 										VectorInitVector(),
	// 										TrieTreeInsertEdges(
	// 											my_machine_2->state_names,
	// 											TrieTreeInitTrieTree(),
	// 											// inserting to the local trie resulted in
	// 											// new state ids to be generated
	// 											VectorCombineVectors1(
	// 												saved_root
	// 												)
	// 											),
	// 										trie_tree
	// 									)
	// 								);
	// VectorAppend(root_stack_item->children, stack_item_level_data);

	// DynamicState* stack_item_level_data_item = (DynamicState*) VectorGetItem(my_machine_2->states);
		// TrieTreeSearch(my_machine_2->state_names, stack_item_level_data));
	// int location = TrieTreeSearch(stack_item_level_data_item->_children, saved_root);
	// printf("location %i\n", location);
	// DynamicState* saved_root_state = (DynamicState*) VectorGetItem(my_machine_2->states, location);
	// Data* variable = saved_root_state->value;
	// can store the data in a level data item and show it
	// can store the slot data items in a linear sequence and show it
	// before continuing
		// clean up files
		// separate files
		// make all functions bullet proof(at least quit with error message)
		// generalize all functios with multi object used(like using the trie tree print to print assuming there are indents from a state print function)
		// comment on assumptions the functions use
	// Vector* root_name = variable->container;
	// VectorPrintStrings(root_name);
	// DynamicMachinePrintStateTree(my_machine_2, 0, 0);


	// need to append a slot state before running this

	// void appendChildren(DynamicMachine* machine,
	// 			int last_state_added,
				
	// 			int parent,
	// 			int child,
	// 			int ith_child,
	// 			bool current_machine_status
	// 			)

	// (root, start, 0, false)
	// keep tracke of bottom
	// use the coordinate swap to access the data at bottom of stack
	// Vector* next_states = working_state->start_children;
	// for(int i = 0; i < VectorGetPopulation(next_states); i++)
	// {
	// 	VectorPrintStrings( (Vector*) VectorGetItem(next_states, i) );

	// }

	// if i was returned it could be stored and the correct state could be found from next_states
	// int winning_state_position = DynamicMachineRunStates2(my_machine_2,
	// 										// the parent state
	// 										working_state,
	// 										// first time, should be the next states from root
	// 										next_states);
	// if(winning_state_position == -1)
	// {
	// 	printf("no state worked\n");
	// 	exit(1);
	// }
	// make a secondary possibility so digits letters null can go for a while then fail so the 
	// next option can be tried
	// ("start", "(", 0, false ) -> ("start", "digits letters null", 0, false )
	/*

	test one part at a time
	stack_item pair 1
	stack_item pair 2
	tracker pair
	["stack_item", "history_slot", id......]
	setup for 1 timeline
	push(StateMachine* machine, State* parent, State* child, int ith_child, State* parent_slot_state )
	{
		append(state("stack_item", "level_data"]))
		appendChilren(state_added, parent, child, ith_child, false)

		append(state(["stack_item", "slot"]))
		appendParent(machine, ["stack_item", "slot"], parent_slot_state)

		history tree
		append(state(["stack_item", "history_level_data"]))
		appendStateChilren(parent, child, ith_child, false)

		append(state(["stack_item", "history_slot"]))
		appendParent(machine, ["stack_item", "history_slot"], parent_slot_state)

		getChildCounterpart(machine, ["control trackers"], "history_slot") -> 	
		state having children set as (parent, child, ith_child, false) from history_leveL_data
	
		["control trackers"]
			["stack_item", "history_slot", id.......]
			["stack_item", "slot", id......]

		// return history tracker and slot tracker

		return last state in machine(top of stack["stack_item", "slot", id......] because it was the last one added)
	}
	push
	("start", "digits letters null", 0, false )
	(["start"], ["letter" "0"], 0, false )

	pop
	("start", "digits letters null", 0, false )

	get next one to test because the one below it(["letter" "0"]) was false
	("start", "option 2", 1, false )
	
	*/
	// Vector* winning_state_name = (Vector*) VectorGetItem(next_states, winning_state_position);

	// working_state = DynamicStateGetState( my_machine_2,
	// 							(Vector*) VectorGetItem(next_states, winning_state_position));

	// printf("passing state\n");
	// VectorPrintStrings(working_state->name);
	// printf("start child %i parent %i\n",
	// 											working_state->is_start_child,
	// 											working_state->has_down_links);
	// (root, start, 0, false)
	// (start, (, 0, false)

	// parent and start child, but not child?
	// can have a link to parent but not be a child?

	// if(working_state->is_start_child)
	// {
	// 	// push back working_state	
	// }

	// implies a state can be either a parent or a child
	// has_down_links
	// if(working_state->has_down_links)
	// {
	// 	// get children states
	// 	printf("get children states\n");
	// }
	// else
	// {
	// 	// get next states
	// 	printf("get next states\n");

	// 	for(int i = 0; i < VectorGetPopulation(working_state->next_states); i++)
	// 	{
	// 		VectorPrintStrings( (Vector*) VectorGetItem(working_state->next_states, i) );

	// 	}

	// }

	
	
	// was design to work with a root holding vars and the root of the machine
	// 2 roots not 1(current system has 1 root with start children and variable category)
	// while(working_state != NULL)
	// {
	// 	// need terms for handling the different kinds of neighbors for manually running
	// 	// more than 1 level
	// 	// the state that doesn't exists is ||?
	// 	working_state = DynamicMachineRunStates(my_machine,
	// 											// the parent state
	// 											my_control_flow_graph,
	// 											// this state is supposed to have a function associated with it
	// 											working_state,
	// 											// first time, should be the next states from root
	// 											next_states);
	// 	printf("the winning state is\n");
	// 	if(working_state == NULL)
	// 	{
	// 		// no state won and there are neighbors
	// 		if(VectorGetPopulation(next_states) > 0)
	// 		{
	// 			printf("no state won so shut down machine or return false to the parent machine.\n");
	// 			// return false to caller
	// 		}
	// 		else // no state won but there were no neighbors
	// 		{
	// 			printf("at end of machine\n");
	// 			// return true to caller
	// 		}
	// 	}
	// 	else
	// 	{
	// 		VectorPrintStrings(working_state->name);
	// 		next_states = working_state->next_states;

	// 	}
	// }
	// printf("done\n\n");


}

void printArraysOfStrings(Vector* arrays_of_strings, int indent_level)
{
	if(arrays_of_strings != NULL)
	{
		for(int i = 0; i < arrays_of_strings->population; i++)
		{
			// printf("%s", makeSpaces(indent_level).c_str());

			// Vector* array_of_strings = (Vector*) arrays_of_strings->values[i];
			// for(int j = 0; j < array_of_strings->population; j++)
			// {
			// 	string* my_string = (string*) array_of_strings->values[j];
			// 	printf("%s, ", my_string->c_str());
			// }
			printf("\n");
		}
	}
	
}
void printArrayOfStrings(Vector* array_of_strings, int indent_level)
{
	if(array_of_strings != NULL)
	{
		// printf("%s", makeSpaces(indent_level).c_str());

		for(int i = 0; i < array_of_strings->population; i++)
		{
			// string* my_string = (string*) array_of_strings->values[i];
			// printf("%s, ", my_string->c_str());
		}
		printf("\n");
	}
	
}
// void printState(State* my_state, int indent_level)
// {
// 	// printf("%sname\n", makeSpaces(indent_level).c_str());
// 	printArrayOfStrings(my_state->name, indent_level + 1);
// 	// printf("%sstart children\n", makeSpaces(indent_level).c_str());

// 	// printArraysOfStrings(my_state->start_children, indent_level + 1);
// 	// printf("%schildren\n", makeSpaces(indent_level).c_str());

// 	printArraysOfStrings(my_state->children, indent_level + 1);
// 	// printf("%snext states\n", makeSpaces(indent_level).c_str());

// 	printArraysOfStrings(my_state->next_states, indent_level + 1);
// 	// printf("%sdata\n", makeSpaces(indent_level).c_str());

// 	printData(my_state->value, indent_level + 1);
// }
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

// StateMachine* setupMachine(int start_state, int end_state)
// {
	
// 		// contextual state chart
// 		// each state name is a contextual state
// 		// the state chart is the groups of states per level
// 		int number_of_states = 18;
// 		int neighbor_count = 4;
// 		int children_count = 4;
// 		int number_of_next_states = number_of_states * (children_count + neighbor_count);

// 		// vector<string>* make_tree_state_names_strings = new vector<string>(number_of_states);

// 		// vector<string>* function_names = new vector<string>(number_of_states);

// 		// function_names->resize(number_of_states);
// 		int* parent_status = (int*) malloc(sizeof(int) * number_of_states);
// 		parent_status[empty]											= false;
// 		parent_status[_search]											= true;




// 		// make_tree_state_names_strings->at(empty) 						= "empty";
// 		// make_tree_state_names_strings->at(_search)						= "_search";




// 		// function_names->at(empty) 										= "true";
// 		// function_names->at(_search)										= "true";

		

// 		int* make_tree_next_states = (int*) malloc(sizeof(int) * number_of_next_states);

// 		// may take this out
// 		// empty field
// 		setupNeighbors(make_tree_next_states, empty,

// 													empty, 										empty, 							empty, 				empty, 			
// 													empty, 										empty, 							empty, 				empty);
// 		// level 1
// 		// search
// 		setupNeighbors(make_tree_next_states, _search,

// 													root_exists, 										empty, 							empty, 				empty,
// 													empty, 										empty, 							empty, 				empty);

// 		return stateMachine2(make_tree_next_states,
// 							/*size*/ number_of_next_states,
// 							/*max_neghbors*/ neighbor_count,
// 							// make_tree_state_names_strings,
// 							// number_of_states,
// 							// parent_status,
// 							// function_names,
// 							start_state//,
// 							// end_state
// 							);

// }
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

// void printStateTrie(DynamicMachine* my_dynamic_machine, string root, int indent_level)
// {
// 	/*
// 		get the state if exists
// 			VectorPrint state
// 		go through the neighbors in the nested map
// 		printStateTrie(neighbor string in nested map)
// 	*/
// 	//printf("printStateTrie\n");
// 	if(my_dynamic_machine != NULL)
// 	{
// 		if(root.size() > 0)
// 		{
// 			//printf("not null\n");
// 			// map<string, MapNode*>* trie_tree_dict
// 			map<string, MapNode*>::iterator it = my_dynamic_machine->trie_names->find(root);
// 			if(	it != my_dynamic_machine->trie_names->end() )
// 			{
// 				//printf("item exists\n");
// 				MapNode* node = it->second;
// 				if(node->current_name_part.size() > 0)
// 				{
// 					map<string, DynamicState*>::iterator it2 = node->next_name_part_states_s->find(node->current_name_part);
// 					DynamicState* state = it2->second;

// 					//printf("%s\n", node->current_name_part.c_str());
// 					printf("%s%s\n", makeSpaces(indent_level).c_str(), node->current_name_part.c_str());
// 					printState(state, indent_level);

// 				}
// 				else
// 				{
// 					//printf("none\n");
// 				}
// 				for(map<string, DynamicState*>::iterator it = node->next_name_part_states_s->begin();
// 					it != node->next_name_part_states_s->end();
// 					it++
// 					)
// 				{
// 					//printf("%s\n", it->first.c_str());
// 					printStateTrie(my_dynamic_machine,
// 						it->first,
// 						indent_level + 2);
// 				}

				
// 			}
// 		}
		
// 	}
// }


// api's, not state functions
// for testing and using
// entrypoint to building the dynamic state machine





// bool insertState2(string name_1, string name_2)
// {
// 	return true;
// }
// bool insertState3(string name_1, string name_2, string name_3)
// {
// 	return true;
// }


// implementation
// state functions
bool searchForItem(void* object)
{
	ContextualStateChart* my_machine = (ContextualStateChart*) object;
	// obtain the state from buffer
	// setup things in auxiliary object
	return true;
}
// int runState(StateMachine* machine, int start_of_next_states, void* object/*Scanner* my_scanner*/, int level)
// {
// 	// children links come before next links
	
	

// 	int current_state = machine->current_state;

// 	int max_neighbors = machine->max_neighbors;
// 	// go to start of next states for current_state
// 	int i = start_of_next_states;
// 	//printf("going to run some states\n");
// 	bool state_changed = false;
// 	for(int j = 0; j < max_neighbors; j++)
// 	{
// 		// printf("%strying %s\n",
// 		// 		makeSpaces(level).c_str(),
// 		// 		machine->state_names_strings->at( machine->next_states[i + j] ).c_str() );

// 		int winning_state = 0;

// 		switch(machine->next_states[i + j])
// 		{
			

// 			case _search:
// 			{
// 				winning_state = _search;
// 				state_changed = true;
// 				break;
// 			}
// 			case root_exists:
// 			{
// 				winning_state = root_exists;
// 				state_changed = true;


// 				break;
// 			}
// 			case get_id_of_expected_location:
// 			{
// 				winning_state = get_id_of_expected_location;
// 				state_changed = true;

// 				break;
// 			}
// 			case setup:
// 			{
// 				winning_state = setup;
// 				state_changed = true;
// 				break;
// 			}
// 			case midpoint:
// 			{
// 				winning_state = midpoint;
// 				state_changed = true;

// 				break;
// 			}
// 			case type_of_match_int:
// 			{
// 				winning_state = type_of_match_int;
// 				state_changed = true;

// 				break;
// 			}
// 			case type_of_match_char:
// 			{
// 				winning_state = type_of_match_char;
// 				state_changed = true;

// 				break;
// 			}
// 			case type_of_match_bool:
// 			{
// 				winning_state = type_of_match_bool;
// 				state_changed = true;

// 				break;
// 			}

// 			case no_more_matches_are_possible:
// 			{
// 				winning_state = no_more_matches_are_possible;
// 				state_changed = true;

// 				break;
// 			}
// 			case no_match:
// 			{
// 				winning_state = no_match;
// 				state_changed = true;

// 				break;
// 			}
// 			/*
// 			case left:
// 			{
// 				winning_state = left;
// 				state_changed = true;

// 				break;
// 			}
// 			case right:
// 			{
// 				winning_state = right;
// 				state_changed = true;

// 				break;
// 			}
// 			*/

// 			case full_match:
// 			{
// 				winning_state = full_match;
// 				state_changed = true;

// 				break;
// 			}

// 			case partial_match:
// 			{
// 				winning_state = partial_match;
// 				state_changed = true;
// 				break;
// 			}
// 			case tree_has_too_little_data_for_a_full_match:
// 			{
// 				winning_state = tree_has_too_little_data_for_a_full_match;
// 				state_changed = true;

// 				break;
// 			}
// 			case tree_is_incomplete:
// 			{
// 				winning_state = tree_is_incomplete;
// 				state_changed = true;


// 				break;
// 			}
// 			case calculate_expected_location:
// 			{
// 				winning_state = calculate_expected_location;
// 				state_changed = true;

			
// 				break;
// 			}
			
// 			default:
// 			{
// 				break;
// 			}
// 		}
// 		if(state_changed)
// 		{
// 			return winning_state;
// 		}

// 	}
// 	if(!state_changed)
// 	{
// 		return false;
// 	}
// 	return -10;

// }
// bool makeStateMachine(DynamicMachine* my_machine)
// {

// 	if(my_machine != NULL)
// 	{

// 		StateMachine* machine = my_machine->static_machine;
// 		// the first state doesn't get run
// 		// machine is finished the moment the current state == done
// 		//int counter = 0;
// 		printf("start state machine\n");
// 		//int current_state = machine->current_state;
// 		// loop through and try the children
// 		int level = 0;
// 		int counter = 0;
// 		int* counter_ptr = &counter;
// 		int debug_states_run = -1;
// 		int* debug_states_run_ptr = &debug_states_run;
// 		runMachine(machine, my_machine, level, counter_ptr, debug_states_run_ptr);
// 		//printMultiwayLinesNodesInContainer(my_scanner->_lines_graph);

// 		//machine->current_state = current_state
// 		//deleteMachineForMakeTree(machine);

// 		//printf("machine is done\n");
// 		//printTree(my_scanner->lines_graph, 0);

// 		return true;
// 	}

// 	return false;
// }


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

				// printf("%s%i\n", makeSpaces(indent_level).c_str(), var_data->_int);
				break;
			}
			case 1:
			{
				// printf("%s%s\n", makeSpaces(indent_level).c_str(), var_data->_string.c_str());

				break;
			}
			case 2:
			{

				// printf("%s%f\n", makeSpaces(indent_level).c_str(), var_data->_float);

				break;
			}

		}
		printf("\n");
	}
	else
	{
		// printf("%sno data\n", makeSpaces(indent_level).c_str());
	}
	
}

// void printTrieNodeTree(TrieNode* root, int indent)
// {
// 	//printf("printing\n");
// 	TrieNode* root_tracker = root;
// 	if(root_tracker != NULL)
// 	{
		// if(root_tracker->word != NULL)
		// {
		// 	printf("%s%s\n", makeSpaces(indent).c_str(), root_tracker->word);
		// }
		//printf("%x\n", root_tracker->neighbors);
		//printf("%x\n", root_tracker->object);

	// 	if(root_tracker->neighbors != NULL)
	// 	{
	// 		if(root_tracker->object != NULL)
	// 		{
	// 			printf("%s", makeSpaces(indent + 2).c_str());
	// 			printContextState2(root_tracker->object);
	// 			printf("\n");

	// 		}
	// 		//printf("# of neighbors %i\n", root_tracker->neighbors_count);
	// 		//printf("size %i\n", root_tracker->size);
	// 		for(int i = 0; i < root_tracker->size; i++)
	// 		{
	// 			if(root_tracker->neighbors[i] != NULL)
	// 			{
	// 				printTrieNodeTree(root_tracker->neighbors[i], indent + 2);

	// 			}
	// 		}
	// 	}
	// 	else
	// 	{
	// 		if(root_tracker->object != NULL)
	// 		{
	// 			printf("%s", makeSpaces(indent + 2).c_str());
	// 			printContextState2(root_tracker->object);
	// 			printf("\n");

	// 		}
	// 	}
	// }
	// else
	// {
	// 	printf("[]\n");
	// }
// }

// void printContextState(ContextState* node)
// {
	/*
		nexts,
		start_children,
		children,
		function_name,
		variable_from_json_dict,
		parents
	*/
	// printf("state name\n");
	// printTrieNodeTree(node->state_name, 0);
	// printf("\n");

	// printf("nexts\n");

	// printTrieNodeTree(node->nexts_, 0);
	// printf("\n");

	// printf("start children\n");
	// printTrieNodeTree(node->start_children, 0);
	// printf("\n");

	// printf("children\n");
	// // printTrieNodeTree(node->children_, 0);
	// printf("\n");

	// printf("function name\n");
	// // printf("%s\n\n", node->function_pointer_name);
	// printf("\n");

	// printf("data\n");
	// // printData(node->var_data, 0);
	// printf("\n");


	// printf("parents\n");
	// // printTrieNodeTree(node->parents_, 0);
	// printf("\n");

	// printf("start_children_are_parallel\n");
	// // printf("%i\n", node->start_children_are_parallel);
	// printf("\n");

	// printf("nexts_are_parallel\n");
	// // printf("%i\n", node->nexts_are_parallel);
	// printf("\n");
	
	// printf("is_start_child\n");
	// // printf("%i\n", node->is_start_child);
	// printf("\n");
	
	// printf("is_child\n");
	// // printf("%i\n", node->is_child);
	// printf("\n");
	
	// printf("is_parent\n");
	// // printf("%i\n", node->is_parent);
	// printf("\n");

	// printf("is_start_state\n");
	// // printf("%i\n", node->is_start_state);
	// printf("\n");

	// printf("is_end_state\n");
	// // printf("%i\n", node->is_end_state);
	// printf("\n");
	
	// printf("is_data_state\n");
	// // printf("%i\n", node->is_data_state);
	// printf("\n");



// }
// void printTrieNodes(TrieNode* trie_node_sequence)
// {
// 	TrieNode* trie_node_sequence_tracker = trie_node_sequence;
// 	while(trie_node_sequence_tracker != NULL)
// 	{
// 		// if(trie_node_sequence_tracker->word != NULL)
// 		// {
// 		// 	printf("%s\n", trie_node_sequence_tracker->word);
			

// 		// }
// 		// if(trie_node_sequence_tracker->neighbors != NULL)
// 		// {
// 		// 	trie_node_sequence_tracker = trie_node_sequence_tracker->neighbors[0];

// 		// }
// 		// else
// 		// {
// 		// 	//printf("at last node\n");
// 		// 	if(trie_node_sequence_tracker->object != NULL)
// 		// 	{
// 		// 		printContextState(trie_node_sequence_tracker->object);
// 		// 	}
			
// 		// 	break;
// 		// }

// 	}
// 	printf("\n");
// }

// void printTrieNodeTreeFlat(TrieNode* root)
// {
// 	// printContextState2 calls this
// 	//printf("printing flat name\n");

// 	TrieNode* root_tracker = root;
// 	if(root_tracker != NULL)
// 	{
// 		//printf("\nabout to VectorPrint word root_tracker->word %x, root_tracker->neighbors %x\n", root_tracker->word, root_tracker->neighbors);

// 		if(root_tracker->word != NULL)
// 		{

// 			printf("%s", root_tracker->word);
// 		}
// 		//printf("neighbors count %i\n", root_tracker->neighbors_count);
// 		//printf("tracker size %i\n", root_tracker->size);
// 		//printf("neighbors %x\n", root_tracker->neighbors);

// 		if(root_tracker->neighbors != 0)
// 		{
// 			printf(" | ");
// 			//printf("neighbors 2 %x\n", root_tracker->neighbors);

// 			// can't check it, doesn't happen all the time, the nodes are set correctly
// 			//if(root_tracker->neighbors_count != NULL)
// 			//	printf("# of neighbors %i\n", root_tracker->neighbors_count);
// 			//else
// 			//	printf("no neighbor count\n");
// 			//printf("size %i\n", root_tracker->size);
// 			//printf("# of neighbors %i, size %i\n", root_tracker->neighbors_count, root_tracker->size);
// 			//printf("will the loop happen\n");
// 			//printf("%i\n", root_tracker->neighbors_count);
// 			for(int i = 0; i < root_tracker->neighbors_count; i++)
// 			{
// 				//printf("%i problem? %i\n", i, root_tracker->size);
// 				if(root_tracker->neighbors[i] != NULL)
// 				{
// 					printTrieNodeTreeFlat(root_tracker->neighbors[i]);

// 				}
// 			}
// 		}
// 	}
// 	else
// 	{
// 		printf("[]\n");
// 	}
// }

// void printContextState2(ContextState* node)
// {

// 	if(node != NULL)
// 	{
// 		if(node->state_name != NULL)
// 		{

// 			printf("-> ");
// 			printTrieNodeTreeFlat(node->state_name->neighbors[0]);

// 		}

// 	}
// }

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

Data* DataInitDataInt(int a)
{
	Data* variable = (Data*) malloc(sizeof(Data));
	variable->type_id = 0;
	variable->_int = a;
	return variable;
}
// Data* DataInitDataFloat(float a)
// {
// 	Data* variable = (Data*) malloc(sizeof(Data));
// 	variable->type_id = 2;
// 	variable->_float = a;
// 	return variable;

// }

// Data* DataInitDataString(
// 	// string a
// 	)
// {
// 	Data* variable = (Data*) malloc(sizeof(Data));
// 	variable->type_id = 1;
// 	// variable->_string = a;
// 	return variable;

// }
void DataDeleteData(Data* variable)
{
	// if(variable->_string.size() > 0)
	// {
	// 	// wierd
	// 	free(&variable->_string);
	// 	// variable->_string = NULL;
	// }
	free(variable);
	variable = NULL;
}

Data* DataInitDataVector(Vector* container)
{
	Data* variable = (Data* ) malloc(sizeof(Data));
	variable->type_id = 3;
	
	// variable->container = container;
	// variable->vector_type_id = 1;
	// variable->container_nesting_level = 1;
	return variable;

}

void DataDeleteDataVector(Data* variable)
{
	if(variable == NULL)
	{
		return;
	}
	// not doing deep delete now
	// for(int i = 0; i < )
	// VectorDeleteVector(variable->container);

}
// ContextState* initContextState()
// {
// 	ContextState* test = (ContextState*) malloc(sizeof(ContextState));
// 	test->parents_size = 0;
// 	test->children_size = 0;

	//test->name = malloc(sizeof(char) * 50);
	//memcpy(test->name, input, sizeof(char) * strlen(input));

// 	return test;
// }
// ContextState* makeFullContextState2(
// 	TrieNode* name,
// 	TrieNode* nexts,
// 	TrieNode* start_children,
// 	TrieNode* children,
// 	char* function_name,
// 	Data* variable_from_json_dict,
// 	TrieNode* parents,
// 	bool (*function_pointer)(struct ContextState* state),
// 	bool start_children_are_parallel,
// 	bool nexts_are_parallel,
// 	bool is_start_child,
// 	bool is_child,
// 	bool is_parent,
// 	bool is_start_state,
// 	bool is_end_state,
// 	bool is_data_state)
// {
	// printf("got here\n");

	// ContextState* state = makeFullContextState(
	// name,
	// nexts,
	// start_children,
	// children,
	// function_name,
	// variable_from_json_dict,
	// parents,
	// start_children_are_parallel,
	// nexts_are_parallel,
	// is_start_child,
	// is_child,
	// is_parent,
	// is_start_state,
	// is_end_state,
	// is_data_state);
	// state->function_pointer = function_pointer;
// 	return state;

// }
// ContextState* makeFullContextState(
// 	TrieNode* name,
// 	TrieNode* nexts,
// 	TrieNode* start_children,
// 	TrieNode* children,
// 	char* function_name,
// 	Data* variable_from_json_dict,
// 	TrieNode* parents,
// 	bool start_children_are_parallel,
// 	bool nexts_are_parallel,
// 	bool is_start_child,
// 	bool is_child,
// 	bool is_parent,
// 	bool is_start_state,
// 	bool is_end_state,
// 	bool is_data_state)
// {
// 	// name, nexts, start_children, children, parents are all dummy nodes
// 	//printf("got here\n");

// 	int sizeof_trie_node = sizeof(TrieNode);

// 	int sizeof_context_state = sizeof(ContextState);

// 	int sizeof_data = sizeof(Data);
// 	//printf("got here\n");

// 	int sizeof_function_name = 0;
// 	if(function_name != NULL)
// 	{
// 		sizeof_function_name = sizeof(char) * (strlen(function_name) + 1);

// 	}
// 	ContextState* node 			= (ContextState*) malloc(sizeof_context_state);
// 	//printf("got here\n");

// 	if(name == NULL &&
// 		nexts == NULL &&
// 		start_children == NULL &&
// 		children == NULL &&
// 		function_name == NULL &&
// 		variable_from_json_dict == NULL &&
// 		parents == NULL)
// 	{
// 		//printf("all null\n");
// 		return node;
// 	}
// 	node->state_name 			= (TrieNode*) malloc(sizeof_trie_node);
	// node->nexts_ 				= NULL;
	// node->start_children 		= NULL;
	// node->children_ 			= NULL;
	// node->parents_ 				= NULL;
	
	// node->function_pointer_name = NULL;
	
	// node->var_data 				= NULL;


	// only need to copy over the pointers inside NeighborNames

	// if(name != NULL)
	// {

	// 	memcpy(node->state_name,
	// 		   name,
	// 		   sizeof_trie_node);
	// }

	// if(nexts != NULL)
	// {
	// 	node->nexts_ = (TrieNode*) malloc(sizeof_trie_node);
	// 	memcpy(node->nexts_,
	// 		   nexts,
	// 		   sizeof_trie_node);
	// }

	// if(start_children != NULL)
	// {
	// 	//printf("added start children\n");
	// 	node->start_children = (TrieNode*) malloc(sizeof_trie_node);

	// 	memcpy(node->start_children,
	// 		   start_children,
	// 		   sizeof_trie_node);
	// }
	

	// if(children != NULL)
	// {
	// 	//printf("added children\n");
	// 	node->children_ = (TrieNode*) malloc(sizeof_trie_node);

	// 	memcpy(node->children_,
	// 		   children,
	// 		   sizeof_trie_node);
	// }
	// if(parents != NULL)
	// {
	// 	//printf("added parents\n");
	// 	node->parents_ = (TrieNode*) malloc(sizeof_trie_node);

	// 	memcpy(node->parents_,
	// 		   parents,
	// 		   sizeof_trie_node);
	// }
	// if(function_name != NULL)
	// {
	// 	node->function_pointer_name = (char*) malloc(sizeof_function_name);

	// 	memcpy(node->function_pointer_name,
	// 		   function_name,
	// 		   sizeof(char) * (strlen(function_name) + 1));
		
	// }
	// if(variable_from_json_dict != NULL)
	// {
	// 	node->var_data = (Data*) malloc(sizeof_data);
	// 	memcpy(node->var_data,
	// 		   variable_from_json_dict,
	// 		   sizeof_data);
	// }

	
	// node->start_children_are_parallel = start_children_are_parallel;
	// node->nexts_are_parallel = nexts_are_parallel;
	// node->is_start_child = is_start_child;
	// node->is_child = is_child;
	// node->is_parent = is_parent;
	// node->is_start_state = is_start_state;
	// node->is_end_state = is_end_state;
	// node->is_data_state = is_data_state;
	// return node;

// }
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
		DataDeleteData(node->var_data);
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
