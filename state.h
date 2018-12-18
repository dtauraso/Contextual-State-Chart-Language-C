#ifdef STATE
#define STATE


// each ContextState is a state
typedef struct ContextState {
	struct Names* name;

	struct Names** start_children;
	int start_children_size;

	struct Names** parents;
	int parents_size;


	// no recursion, have an indent on/off var in the stack
	// when the child state is at a higher level than the current state
		// deactivate the indent
	// use last indent on/off value to find out if indents should be on or off
	// (current state, prev item on stack, is_indent_on)

	struct Names** children;
	int children_size;

	struct Names** nexts;
	int nexts_size;

	bool (*function_pointer)(struct Names* a, struct SparseMatrix* b);
	char* function_pointer_name;

	struct Data* var;
} ContextState;


struct ContextState* makeNewState();
void setFunctionPointer(struct ContextState* node, bool (*function_pointer)(struct Names* a, struct SparseMatrix* b), char* function_pointer_name);
void setNames(struct ContextState* state, struct Names* names);
void initializeSizes(struct ContextState* state);
void initializeVars(struct ContextState* state);
void setIsInt(struct ContextState* state, bool on_off);
void setIsString(struct ContextState* state, bool on_off);
void setIsFloat(struct ContextState* state, bool on_off);
void setIsIntPtr(struct ContextState* state, bool on_off);
void setIsStringPtr(struct ContextState* state, bool on_off);
void setIsFloatPtr(struct ContextState* state, bool on_off);
void setIsLevels(struct ContextState* state, bool on_off);
struct Names* getName(struct ContextState* state);
struct Names** getStartChildren(struct ContextState* state);
struct Names** getParents(struct ContextState* state);
struct Names** getChildren(struct ContextState* state);
struct Names** getNexts(struct ContextState* state);
struct Data* getVar(struct ContextState* state);
int getStartChildrenSize(struct ContextState* state);
int getParentsSize(struct ContextState* state);
int getChildrenSize(struct ContextState* state);
int getNextsSize(struct ContextState* state);
void setName(struct ContextState* state, struct Names* name);
void setStartChildren(struct ContextState* state, struct Names** start_children);
void setParents(struct ContextState* state, struct Names** parents);
void setChildren(struct ContextState* state, struct Names** children);
void setNexts(struct ContextState* state, struct Names** nexts);
void setVar(struct ContextState* state, struct Data* var);





#endif