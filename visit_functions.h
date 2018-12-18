#ifndef VISIT_FUNCTIONS
#define VISIT_FUNCTIONS
struct ChildParent
{
	struct Names* child;
	struct ChildParent* parent;
};

struct NextStatesPackage
{
	struct ChildParent* bottom_of_shortened_stack;
	struct Names** next_states;
	int indents;

	int next_states_size;
};
#endif