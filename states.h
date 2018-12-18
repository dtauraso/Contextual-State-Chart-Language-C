#ifndef STATES
#define STATES
typedef struct SparseMatrix {
	struct ContextState** state_list;//[max_states];
	int state_population;   // needed so when visiting the level for the nth time, not resetting the state_id back to 0(as there are now states in this level)
}SparseMatrix;
/*
struct level_id_state_id;
struct ContextState* getState(struct SparseMatrix* levels, level_id_state_id* point)
{
	return levels[point->level_id].state_list[point->state_id];
}*/
#endif