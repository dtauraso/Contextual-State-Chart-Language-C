// this program parses a custom file of context sensitive states


#include "hash_table.h"
#include "forward_declarators.h"
// function to jump to the start of the ith group of 4 next states
// f(state_case) -> int

// next_states, functions, children
// (state, case)'s next states
// "", "", "", ""

 enum states{
	 start,
	 a,
	 indent_increase1,
	 children,
	 is_indent_decrease,
	 collect_state_name,
	 pop_from_stack,
	 indent_stays_same,
	 next,
	 is_indent_decrease1,

	 top_of_word_stack_is_not_children,
	 top_of_word_stack_is_children,

	 set__one__s_ith_child_to__zero_,
	 pop_from_stack1,
	 compute_number_of_state_names,


	 indent_increase2,
	 abcd,
	 indent_stays_same1,

	 parent,
	 indent_increase3,
	 abcd1,
	 indent_stays_same2,
	 indent_decrease2,
	 Functions,
	 indent_increase4,
	 abcd2,
	 indent_stays_same3,
	 indent_decrease3,
	 filler



	 };
 char* getStateString(int current_state)
 	{
 		char* state_name = malloc(sizeof(char) * 20);
 		switch(current_state)
 		{
 			case start:
 			{
 				memcpy(state_name, "start", sizeof(char) * 6);
 				break;
 			}
 			case a:
 			{
 				memcpy(state_name, "a", sizeof(char) * 2);

 				break;

 			}
 			case indent_increase1:
 			{
 				memcpy(state_name, "indent_increase1", sizeof(char) * 17);

 				break;

 			}
 			case children:
 			{
 				memcpy(state_name, "children", sizeof(char) * 9);

 				break;

 			}
 			case is_indent_decrease:
 			{
 				memcpy(state_name, "is_indent_decrease", sizeof(char) * 19);

 				break;

 			}
 			case collect_state_name:
 			{
 				memcpy(state_name, "collect_state_name", sizeof(char) * 19);

 				break;

 			}
 			case pop_from_stack:
 			{
 				memcpy(state_name, "pop_from_stack", sizeof(char) * 15);

 				break;

 			}
 			case indent_stays_same:
 			{
 				memcpy(state_name, "indent_stays_same", sizeof(char) * 18);

 				break;

 			}
 			case next:
 			{
 				memcpy(state_name, "next", sizeof(char) * 5);

 				break;

 			}
			case is_indent_decrease1:
			{
				memcpy(state_name, "is_indent_decrease1", sizeof(char) * 20);

				break;

			}
			case top_of_word_stack_is_not_children:
			{
				memcpy(state_name, "top_of_word_stack_is_not_children", sizeof(char) * 34);

				break;
			}
			case top_of_word_stack_is_children:
			{
				memcpy(state_name, "top_of_word_stack_is_children", sizeof(char) * 30);

				break;
			}
			case set__one__s_ith_child_to__zero_:
			{
				memcpy(state_name, "set__one__s_ith_child_to__zero_", sizeof(char) * 32);

				break;
			}
			case pop_from_stack1:
			{
				memcpy(state_name, "pop_from_stack1", sizeof(char) * 16);

				break;
			}

			case compute_number_of_state_names:
			{
				memcpy(state_name, "compute_number_of_state_names", sizeof(char) * 30);

				break;
			}




 			case indent_increase2:
 			{
 				memcpy(state_name, "indent_increase2", sizeof(char) * 17);

 				break;

 			}
 			case abcd:
 			{
 				memcpy(state_name, "abcd", sizeof(char) * 5);

 				break;

 			}
 			case indent_stays_same1:
 			{
 				memcpy(state_name, "indent_stays_same1", sizeof(char) * 19);

 				break;

 			}

 			case parent:
 			{
 				memcpy(state_name, "parent", sizeof(char) * 7);

 				break;

 			}
 			case indent_increase3:
 			{
 				memcpy(state_name, "indent_increase3", sizeof(char) * 17);

 				break;

 			}
 			case abcd1:
 			{
 				memcpy(state_name, "abcd1", sizeof(char) * 6);

 				break;

 			}
 			case indent_stays_same2:
 			{
 				memcpy(state_name, "indent_stays_same2", sizeof(char) * 19);

 				break;

 			}
 			case indent_decrease2:
 			{
 				memcpy(state_name, "indent_decrease2", sizeof(char) * 17);

 				break;

 			}
 			case Functions:
 			{
 				memcpy(state_name, "Functions", sizeof(char) * 10);

 				break;

 			}
 			case indent_increase4:
 			{
 				memcpy(state_name, "indent_increase4", sizeof(char) * 17);

 				break;

 			}
 			case abcd2:
 			{
 				memcpy(state_name, "abcd2", sizeof(char) * 6);

 				break;

 			}
 			case indent_stays_same3:
 			{
 				memcpy(state_name, "indent_stays_same3", sizeof(char) * 19);

 				break;

 			}
 			case indent_decrease3:
 			{
 				memcpy(state_name, "indent_decrease3", sizeof(char) * 17);

 				break;

 			}
 			case filler:
 			{
 				memcpy(state_name, "filler", sizeof(char) * 7);

 				break;

 			}
 			default:
 			{
 				memcpy(state_name, "no state", sizeof(char) * 9);

 				break;
 			}

 		}
 		return state_name;
 	}

int getFirstForNextStates(int current_state)
{
	int states[] = {
		start,
		a,
		indent_increase1,
		children,
		is_indent_decrease,
		collect_state_name,
		pop_from_stack,
		indent_stays_same,
		next,
		is_indent_decrease1,
		top_of_word_stack_is_not_children,
		top_of_word_stack_is_children,

		set__one__s_ith_child_to__zero_,
		pop_from_stack1,
		compute_number_of_state_names,
		filler
	};
	for(int i = 0; i < 15; i++)
	{
		//printf("testing%s = %s\n", getStateString(states[i]), getStateString(current_state));

		if(current_state == states[i])
		{
			return states[i] * 3;
		}
	}
	//printf("%s\n", getStateString(current_state));
	return -1;


}

//typedef int (*FN)();

/* ) */
void rightParense0()
{
	//return true;

}




/*
char next_states[] = {

			};
*/
#include <stdio.h>

bool fun0()
{
    return 0;
}

bool fun1()
{
    return 1;
}

bool fun2()
{
    return 2;
}

//int main(int argc, char* argv[])
//{

    //return 0;
//}
// store a struct of (name_vector, function_reference) so the data in the files can be associated with the functions



//char* children[] = {

//			};



//char* parents[] = {

//			};


// will need a way to store the function string name with the actual pointer in the computer so the parser can read it after it reads the function name from the file


int getNextI(char* line, int i)
{
	int start;
	for(start = i; line[start] != '\n'; start++);

	// + 1 so i is 1 after '\n'
	return start;// + 1;
}

 struct word_tree_node
 {
	 char* word;
	 struct word_tree_node* parent;
 } word_tree_node;

 int countGapSize(char* line, int i)
 {
	 if(i < strlen(line))
	 {
		 int indent_count = 0;
		 if (line[i] == '\n')
		 {
			 indent_count++;
			 i++;

			 while(line[i] == '\t')
			 {
				 indent_count++;
				 i++;
			 }
			 return indent_count;
		 }
		 //printf("%i\n", indent_count);
		 return 0;
	 }
	 return 0;
 }
 bool isChild(int indent_count_1, int indent_count_2)
 {
	 return indent_count_1 < indent_count_2;
 }
 bool isSibling(int indent_count_1, int indent_count_2)
 {
	 return indent_count_1 == indent_count_2;
 }
 int getEndIndexOfWord(char* line, int i)
 {
	 	int j = i;
		while(line[j] != '\n') j++;

		return j;
 }

 struct StackNode
 {

	char* word;
	int indent;
	struct StackNode* prev;
 };
 struct TreeNode
 {
	 char* word;
	 struct TreeNode* left;
	 struct TreeNode* right;
 };
 void printStack(struct StackNode* tracker)
 {
	 struct StackNode* stack_tracker = malloc(sizeof(struct StackNode));
	 memcpy(stack_tracker, tracker, sizeof(struct StackNode));
	 stack_tracker->indent = tracker->indent;
	 stack_tracker = stack_tracker->prev;
	 while(stack_tracker->prev != NULL)
	 {
		 printf("|%s, %i| ", stack_tracker->word, stack_tracker->indent);
		 stack_tracker = stack_tracker->prev;

	 }
	 printf("|%s, %i| ", stack_tracker->word, stack_tracker->indent);

	 //free(stack_tracker);

 }

char* makeWord(int next_location_of_newline, char* line, int i)
{

	char* word = malloc(sizeof(char) * next_location_of_newline);
 	int size = next_location_of_newline - i;
 	memcpy(word, line + i, sizeof(char) * size );
 	word[size] = '\0';
	return word;
}

/*	a, \n, same number of tab count as count_1

	or
	a, \n, > number of tab count as count_1
		pass hash table in
		make the entry for the current context dimension
		return the current context dimension to the caller(the entry represents the tree)
		the children is supposed to connect to the node below not a nested hash table
	or

	Children | Parents | Next | Functions, \n, some number of tabls,

	*/

bool wordIsChildren(char* word)
{
	if(strcmp(word, "Children") == 0)
	{
	   return true;
	}
	else
	   return false;
}
bool wordIsNext(char* word)
{
	if(strcmp(word, "Next") == 0)
	{
	   return true;
	}
	else
	   return false;
}
bool wordIsCategory(char* word)
{
	//printf("word is category |%s|\n", word);
	 if(strcmp(word, "Children") == 0 ||
		 strcmp(word, "Next") == 0 ||
		 strcmp(word, "Parents") == 0 ||
		 strcmp(word, "Functions") == 0)
	{
		return true;
	}
	 else
	 	return false;
	//return true;
}

 /*struct TreeNode
 {
 	char* word;
 	struct TreeNode* left;
 	struct TreeNode* right;
 };
 */

 /*
if going down failed(indents aren't right )
	return nil
print word
for each indent found that has a = b
	go down
	jump to next word

 */
 void Chilren(char* line, int count_1, int count_2, int* i_ptr, int* loop_count_ptr, struct StackNode* tracker, int* dimension_count_ptr)
 {

 }
 /*
 struct TreeNode
 {
	 char* word;
	 struct TreeNode* left;
	 struct TreeNode* right;
 };*/
 struct State
 {
	 char** name;
	 int name_size;
	 int ith_name;
	 struct State** children;
	 int children_size;
	 char** next;
	 int next_size;
	 char** parents;
	 int parents_size;
	 char** functions;
	 int functions_size;
	 int indent;
	 struct State* prev;
 };

 /*
 void printStack(struct StackNode* tracker)
 {
 	struct StackNode* stack_tracker = malloc(sizeof(struct StackNode));
 	memcpy(stack_tracker, tracker, sizeof(struct StackNode));
 	stack_tracker->indent = tracker->indent;
 	while(stack_tracker->prev != NULL)
 	{
 		printf("|%s, %i| ", stack_tracker->word, stack_tracker->indent);
 		stack_tracker = stack_tracker->prev;

 	}
 	printf("|%s, %i| ", stack_tracker->word, stack_tracker->indent);

 	//free(stack_tracker);

 }
 */
 char* makeIndents(indents)
 {
	if(indents >= 0)
	{
		char* indent_string = malloc(sizeof(char) * (indents + indents));
		memset(indent_string, ' ', sizeof(char) * (indents + indents));
		indent_string[indents + indents] = '\0';

		return indent_string;
	}
	return NULL;
 }
 void postorder(struct State* state_tracker, int indents)
 {

	//printf("%i| %i\n", indents, state_tracker->children_size);
	for(int i = 0;  i < state_tracker->children_size; i++)
 	{
 		postorder(state_tracker->children[i], indents + 1);
 	}
	if(state_tracker->indent == 0)
	{

		printf("%sfirst state\n%s|%i|\n", makeIndents(indents),makeIndents(indents), state_tracker->indent);

		return;
	}
	printf("%sdata from state\n", makeIndents(indents));
	printf("%s|%i|\n", makeIndents(indents), state_tracker->indent);


	// print out data in stat_tracker
	printf("%sstate name\n", makeIndents(indents));
	for(int i = 0; i < state_tracker->name_size; i++)
	{
		printf("  %s|%s|\n", makeIndents(indents), state_tracker->name[i]);
	}
	printf("done printing data from state\n");

}
void printStateStack(struct State* state_tracker)
{
	struct State* stack_tracker = malloc(sizeof(struct State));
	memcpy(stack_tracker, state_tracker, sizeof(struct State));
	//stack_tracker->indent = state_tracker->indent;
	stack_tracker = stack_tracker->prev;
	//printf("%i\n", state_tracker->indent);
	//printf("%i\n", state_tracker->prev->indent);
	//printf("|%i| ", stack_tracker->indent);
	int indents = 0;
	// 					indent_string = makeIndents(count_temp);
	//postorder(stack_tracker);

	while(stack_tracker != NULL)
	{
		// postorder traversal of stack_tracker subtree
		printf("start of ith node\n");
		postorder(stack_tracker, 0);
		printf("end of ith node\n\n");
		/*else
		{
			//printf("%i %i\n", stack_tracker->next[0], stack_tracker->next[0] != 0);
			if (stack_tracker->next != NULL)
			{
				printf("|%i:next = %s| ", stack_tracker->indent, stack_tracker->next[0]);

			}
			else
			{
				printf("|%i| ", stack_tracker->indent);

			}
		}*/
		stack_tracker = stack_tracker->prev;
		//printf("|%i| ", stack_tracker->indent);

	}
	//printf("|%i| ", stack_tracker->indent);

}
void printPartStack(struct StackNode* tracker, int current_indent)
{
	 /*
	 ocationally a problem like this happens
	 |(null), 0| |string_5, 7| |string_4, 6| |string_3, 5| |Children, 4| |string_3, 3| |string_2, 2| |string_1, 0|
                 Children


	|(null), 0| |Children, 8| |, 7| |string_4, 6| |string_3, 5| |Children, 4| |string_3, 3| |string_2, 2| |string_1, 0|
	4 changes here
	|(null), 0| |Children, 8| |, 7| |string_4, 6| |string_3, 5| |Children, 4| |string_3, 3| |string_2, 2| |string_1, 0|
	|Children, 8| |, 7| |string_4, 6| |string_3, 5| |Children, 4|
	         Next


	 */
 	struct StackNode* stack_tracker = malloc(sizeof(struct StackNode));
 	memcpy(stack_tracker, tracker->prev, sizeof(struct StackNode));
 	stack_tracker->indent = tracker->prev->indent;

	//char* first_word = malloc(sizeof(char) * strlen(stack_tracker->word));
	//memcpy(first_word, stack_tracker->word, sizeof(char) * strlen(stack_tracker->word));

	// first word is the first child

	struct TreeNode* first_child  = malloc(sizeof(struct TreeNode));
	first_child->word = malloc(sizeof(char) * strlen(stack_tracker->word));
	memcpy(first_child->word, stack_tracker->word, sizeof(char) * strlen(stack_tracker->word));
	first_child->left = malloc(sizeof(struct TreeNode));
	first_child->left = NULL;
	first_child->right = malloc(sizeof(struct TreeNode));
	first_child->right = NULL;
	//printf("first node %s\n", first_child->word);
	stack_tracker = stack_tracker->prev;

 	while(stack_tracker->indent >= current_indent && stack_tracker->indent >= 0)
 	{
		// all words after the first word is a parent to the leftmost word node made before
		// todo: fix sometime
		if(strlen(stack_tracker->word) == 0)
		{
			printf("problem with the word in stack\n");
			exit(1);
		}
 		printf("|%s, %i| ", stack_tracker->word, stack_tracker->indent);
 		stack_tracker = stack_tracker->prev;
		// last item printed is the parent to be returned

 	}
	printf("\n");
 	//free(stack_tracker);

}

/*
'''
	currently lots of separate data structures for interacting with 1 node
	next_states
	stack list
	indents
	maybe_parent
	new parent
	state
	case

	new idea
	have extra keys for the node helper procedures

have 1 key for each kind of role the node plays
	state name
	ith context(for granulity)

	children(for the hierarchy)

	stack edge(visiting tree)
	indents(printing)
	parent(for adding a stack edge)

	function(code to run for the state)

	next states(choices at each time step)


	iteration_count(more accurate simulation, automatic pda simulation, like a graph of extra vars to be used in a context free grammer)

	prev states(many backtracking options for making stack edges)

	last ran state(actual backtrack choice for knowing where to find the stack edge)(>1 for NFA)
	histories(visit this path to know the ith history of the run)
		only want to store the unique paths in the overall history(just a history of what was tested, not a timeline of all runs)

	make a past edge for the tracker to visit as it goes backwards
	readjust the back edge
	no extra bottom stack


'''
*/
// increase, stay the same, decrease
// increase, decrease
/*
pop from stack
if indent dicreases
	repeat
if indent stays the same
	go to stays the same

for stays the same
	if word is non category
		to gack to a
	if word is next
		go to next
*/

/*
while word list[0] at indent > current input string at indent 4(is_indent_decrease1)


	word list [0] = non children
		word list reduce 1(entire loop for this), state list
	word list [0] = children
		make tree(state list)

top_of_word_stack_is_children
top_of_word_stack_is_not_children
set_[1]_s_ith_child_to_[0]

works:
is_indent_decrease1 -> top_of_word_stack_is_children(new), top_of_word_stack_is_not_children(new)
top_of_word_stack_is_not_children -> collect_state_name -> pop_from_stack -> is_indent_decrease1

not implemented yet:
top_of_word_stack_is_children -> set [1]'s ith child to [0](new) -> is_indent_decrease1, indent_stays_same

*/
bool isEmpty(int* next_states)
{
	return next_states[0] == filler &&
			next_states[1] == filler &&
			next_states[2] == filler;
}
// count_temp includes newline


int peekAtNode(char* line, int i, int indent_count)
{
	// indent_count = gap size
	//printf("peekat node\n");
	//printf("%i %i\n", indent_count, i);
	// get the size of the string node
	int temp_i = i + indent_count;
	int node_size = 0;
	while(((line[temp_i] >= 'A' && line[temp_i] <= 'Z') ||
		(line[temp_i] >= 'a' && line[temp_i] <= 'z') ||
		line[temp_i] == '_' ||
		line[temp_i] == ' ' ||
		(line[temp_i] >= '0' && line[temp_i] <= '9')))
	{
		//printf("%c\n", line[temp_i]);
		temp_i++;
		node_size++;
	}

	return node_size;
}

char* getValue(char* line, int i, int size)
{

	// temp_i = len(value)
	// not using size ++ because we want to ignore the newline char before the null in the old string
	//size++; // null char requires size of string + 1
	char* value = malloc(sizeof(char) * size);
	memcpy(value, line + i, size);
	value[size] = '\0';
	//printf("%i\n", strlen(value));
	return value;
}
// count_1 and count_2 start as 0
// a (first round the a that came before a doesn't exist)
// countGapSize
	// get the number of indents from i to start of next word = count_2
// get to node
	// moves i to first char of word i += indent_count + 1
// peek node
	// moves temp_i to first char of word temp_i = i + indent_count + 1

// get value
	// collects the word i points to

// category of indent for reading from prev a to a
// should know count_1 c count_2
// jump value
	// sets i to i += len(word)
// shift counts 1 and 2
// a= collect data
// indent category = find out what the data collected means(up down across in tree)
/*
tree of hash tables
	1 level = 1 dimension
name, max context_i


	struct0
indents0  word0
*/
struct StateMachineVars
{
		char* line;
		int size;
		int i;
		// for measuring indent levels and finding the next word
		int count_1;
		int count_2;

		int loop_count;
		int level_count;
		int* loop_count_ptr;
		// bottom of stack for the nodes being made
		struct StackNode* root;
		struct State* state_root;
		struct StackNode* tracker;
		struct State* state_tracker;
		int dimension_count;
		int* dimension_count_ptr;
		int count;
		int next_location_of_newline;
		int* next_location_of_newline_ptr;
		char* word;
		char* indent_string;
		int count_temp;
		int peek_size;
		bool state_changed;
};
bool Start(struct StateMachineVars* main_state_recorder_tree)
{
	//  get past the "dummy" part of the string
	int count_temp 			= 	main_state_recorder_tree->count_temp;
	int i 					=	main_state_recorder_tree->i;
	int peek_size 			=	main_state_recorder_tree->peek_size;
	int count_2 			= 	main_state_recorder_tree->count_2;
	char* indent_string 	= 	main_state_recorder_tree->indent_string;
	char* line 				= 	main_state_recorder_tree->line;
	count_temp = countGapSize(line, i);
	//printf("%i\n", countGapSize(line, i));
	indent_string = makeIndents(count_temp);

	//
	//
	// next is supposed to have the same indent measurement as first Children
	//printf("here\n");
	peek_size = peekAtNode(line, i, count_temp);
	//next_word->word = getValue(line, i + (count_temp), peek_size);


	i += count_2 + peek_size;
	printf("count_temp %i i %i\n", count_temp, i);

	main_state_recorder_tree->count_temp 		= count_temp;
	main_state_recorder_tree->indent_string 	= indent_string;
	main_state_recorder_tree->i 				= i;
	main_state_recorder_tree->peek_size 		= peek_size;
	main_state_recorder_tree->state_changed 	= true;

	return true;
}

bool A(struct StateMachineVars* main_state_recorder_tree)
{
	// get the word
	int count_temp 		=	 main_state_recorder_tree->count_temp;
	int i 				=	 main_state_recorder_tree->i;
	int peek_size 		=	 main_state_recorder_tree->peek_size;
	int count_2 		=	 main_state_recorder_tree->count_2;
	char* line 			=	 main_state_recorder_tree->line;
	char* indent_string =	 main_state_recorder_tree->indent_string;

	count_temp = countGapSize(line, i);

	indent_string = makeIndents(count_temp);

	peek_size = peekAtNode(line, i, count_temp);
	char* word = getValue(line, i + count_temp, peek_size);
	// make a word to check
	// use data to get word to get new_word->word
	// free word
	printf("%s\n", word);
	if(!wordIsCategory(word))
	{

		struct StackNode* next_word = malloc(sizeof(struct StackNode));

		// can't use free here because it interfeers with the allocation of next_word->word
		//free(word);

		next_word->word = malloc(sizeof(char) * peek_size); //getValue(line, i + (count_temp), peek_size);
		memcpy(next_word->word, word, sizeof(char) * peek_size);
		//next_word->word[peek_size] = '\0';
		// can't have free in this if statement until not printing
		//free(word);
		printf("%s%s %i\n\n", indent_string, next_word->word, count_2 );
		//free(word);
		free(indent_string);

		//  		int size = next_location_of_newline - i + 1;
		// make the size of the string smaller by 1
		// the word should be set to next_word->word not word
			// this way we only have to free next_word->word at the very end of the program

		//memcpy(next_word->word, word, sizeof(char) * size);
		next_word->indent = count_2;
		//printf("%i %i\n", next_word->indent, count_2);
		//free(word);
		next_word->prev = main_state_recorder_tree->tracker->prev;

		main_state_recorder_tree->tracker->prev = next_word;
		//free(word);
		printStack(main_state_recorder_tree->tracker);
		printf("\n");
		printStateStack(main_state_recorder_tree->state_tracker);
		printf("\n");
		main_state_recorder_tree->count_temp = count_temp;
		main_state_recorder_tree->peek_size = peek_size;
		main_state_recorder_tree->state_changed = true;
		return true;
	}

	else
	{
		free(word);
		//free(next_word);
		//free(next_word->word);
		return false;
	}
}
bool incrementCount(struct StateMachineVars* main_state_recorder_tree)
{
	// move the indent counts 1 unit down the tree
	int count_1 	=	 main_state_recorder_tree->count_1;
	int count_2 	=	 main_state_recorder_tree->count_2;
	int i 			=	 main_state_recorder_tree->i;
	int count_temp 	=	 main_state_recorder_tree->count_temp;
	int peek_size 	=	 main_state_recorder_tree->peek_size;

	printf("before %i %i\n", count_1, count_2);

	i += count_temp + peek_size;
	count_1 = count_2;
	count_2 = count_temp;
	printf("after %i %i\n", count_1, count_2);
	if(count_2 > count_1)
	{
		main_state_recorder_tree->count_1 = count_1;
		main_state_recorder_tree->count_2 = count_2;
		main_state_recorder_tree->i = i;

		main_state_recorder_tree->state_changed = true;
		return true;
	}
	return false;
}
bool Children(struct StateMachineVars* main_state_recorder_tree)
{

	// is the next word "Children"?
	int count_temp 				=	 main_state_recorder_tree->count_temp;
	int i 						=	 main_state_recorder_tree->i;
	int peek_size 				=	 main_state_recorder_tree->peek_size;
	int count_2 				=	 main_state_recorder_tree->count_2;
	char* indent_string 		=	 main_state_recorder_tree->indent_string;
	char* line 					=	 main_state_recorder_tree->line;
	struct StackNode* tracker 	=	 main_state_recorder_tree->tracker;
	struct State* state_tracker =	 main_state_recorder_tree->state_tracker;

	count_temp = countGapSize(line, i);
	indent_string = makeIndents(count_temp);


	peek_size = peekAtNode(line, i, count_temp);
	char* word = getValue(line, i + count_temp, peek_size);

	if(wordIsChildren(word))
	{
		struct StackNode* next_word = malloc(sizeof(struct StackNode));

		//printf("again|%s|\n", indent_string);
		next_word->word = malloc(sizeof(char) * peek_size); //getValue(line, i + (count_temp), peek_size);
		memcpy(next_word->word, word, sizeof(char) * peek_size);
		free(word);
		printf("%s%s%i\n\n", indent_string, next_word->word , count_2);


		free(indent_string);

		//next_word->word = malloc(sizeof(char) * size);
		//memcpy(next_word->word, word, sizeof(char) * size);
		next_word->indent = count_2;
		//printf("%i %i\n", next_word->indent, count_2);
		//free(word);
		next_word->prev = tracker->prev;

		tracker->prev = next_word;



		struct State* next_state = malloc(sizeof(struct State));
		next_state->indent = count_2;
		next_state->prev = state_tracker->prev;

		// assume children starts with 10 uninitialized slots
		next_state->children = malloc(sizeof(struct State*) * 10);
		next_state->children_size = 0;
		next_state->next = NULL;//malloc(sizeof(char*));
		next_state->name = NULL;
		next_state->ith_name = -1;
		next_state->parents = malloc(sizeof(char*));
		next_state->functions = malloc(sizeof(char*));

		state_tracker->prev = next_state;
		printf("%i\n", next_state->indent);


		printStack(tracker);
		printf("\n");
		printStateStack(state_tracker);
		printf("\n");


		main_state_recorder_tree->count_temp 	= count_temp;
		main_state_recorder_tree->peek_size 	= peek_size;
		main_state_recorder_tree->tracker 		= tracker;
		main_state_recorder_tree->state_tracker = state_tracker;

		main_state_recorder_tree->state_changed = true;
		return true;
	}
	else
	{
		free(word);
		//free(next_word->word);
		return false;
	}
}
bool isIndentDecrease(struct StateMachineVars* main_state_recorder_tree)
{
	// is the ith indent <  i + 1 th indent?

	int count_1 				=	 main_state_recorder_tree->count_1;
	int count_2 				=	 main_state_recorder_tree->count_2;
	int count_temp 				=	 main_state_recorder_tree->count_temp;
	int i 						=	 main_state_recorder_tree->i;
	int peek_size 				=	 main_state_recorder_tree->peek_size;
	char* line 					=	 main_state_recorder_tree->line;
	char* indent_string 		=	 main_state_recorder_tree->indent_string;
	struct StackNode* tracker 	=	 main_state_recorder_tree->tracker;
	struct State* state_tracker =	 main_state_recorder_tree->state_tracker;

	//printf("%i, %i\n", count_1, count_2);
	printf("before %i %i\n", count_1, count_2);

	//(*i_ptr) += (count_temp) + peek_size;
	int c_1 = count_2;
	// -1 because count_temp counts newline
	int c_2 = count_temp-1;

	printf("after %i %i\n", c_1, c_2);

	if(c_2 < c_1)
	{
		printf("here\n");


		struct StackNode* next_word = malloc(sizeof(struct StackNode));

		count_temp = countGapSize(line, i);
		indent_string = makeIndents(count_temp);


		peek_size = peekAtNode(line, i, count_temp);
		next_word->word = getValue(line, i + count_temp, peek_size);
		//printf("%c %s\n", line[(*i_ptr)+6], word);
		//indent_string = makeIndents(c_2);

		if(wordIsCategory(next_word->word))
		{
			printf("%s%s\n", indent_string, next_word->word);
			printStack(tracker);
			printf("\n");
			printStateStack(state_tracker);
			printf("\n");
			struct StackNode* stack_tracker = malloc(sizeof(struct StackNode));
			stack_tracker->prev = tracker->prev;
			int name_size = 0;
			//printf("first wohhhhhhhhrd is %s\n", stack_tracker->prev->word);
			// have to travel up the word stack untill hit a category name(children) or a null sized string
			while(!wordIsCategory(stack_tracker->prev->word) || (strlen(stack_tracker->prev->word) == 0))
			{
				//printf("counting %s\n", stack_tracker->prev->word);
				stack_tracker = stack_tracker->prev;
				name_size++;
			}
			//tracker->prev->indent - state_tracker->prev->indent;
			//printf("size = %i\n", size);
			state_tracker->prev->name = malloc(sizeof(char*) * name_size);
			//printf("state tracker size %i %i\n", sizeof(state_tracker->prev->name)/sizeof(char*), name_size);
			state_tracker->prev->name_size = name_size;
			state_tracker->prev->ith_name = name_size - 1;

		}

		// make sure typing -> state tree works for all text entry


		//exit(1);



		// haven't proven it is not a child
		//incrementCount
		//int prev_location_of_newline_ptr = *next_location_of_newline_ptr;
		//incrementCount
		//*next_location_of_newline_ptr = getEndIndexOfWord(line, i);\
		//word = makeWord(*next_location_of_newline_ptr, line, i);\
		//printf("|%s| %s\n\n", indent_string, word );
		main_state_recorder_tree->count_1		= count_1;
		main_state_recorder_tree->count_2 		= count_2;
		main_state_recorder_tree->count_temp 	= count_temp;
		main_state_recorder_tree->indent_string = indent_string;
		main_state_recorder_tree->peek_size 	= peek_size;
		main_state_recorder_tree->tracker 		= tracker;
		main_state_recorder_tree->state_tracker = state_tracker;
		main_state_recorder_tree->state_changed = true;
		return true;
	}
	return false;
}
bool collectStateName(struct StateMachineVars* main_state_recorder_tree)
{
	// store the name as the ((size - 1) - i)th state name

	struct StackNode* tracker 	= main_state_recorder_tree->tracker;
	struct State* state_tracker = main_state_recorder_tree->state_tracker;



	printStack(tracker);
	printf("\n");
	printStateStack(state_tracker);
	printf("\n");
	// grap the first item and set it to the end of the name array
	// array size ++

	printf("ith name %i\n", state_tracker->prev->ith_name);
	state_tracker->prev->name[state_tracker->prev->ith_name] = malloc(sizeof(char) * strlen(tracker->prev->word));

	memcpy(state_tracker->prev->name[state_tracker->prev->ith_name],
		tracker->prev->word,
		sizeof(char) * strlen(tracker->prev->word));
	state_tracker->prev->ith_name--;
	printStateStack(state_tracker);
	printf("\n");

	main_state_recorder_tree->tracker 		= tracker;
	main_state_recorder_tree->state_tracker = state_tracker;
	main_state_recorder_tree->state_changed = true;
	return true;
}
bool popFromStack(struct StateMachineVars* main_state_recorder_tree)
{
	// pop the top word from the word stack
	struct StackNode* tracker 	= main_state_recorder_tree->tracker;
	struct State* state_tracker = main_state_recorder_tree->state_tracker;

	printStack(tracker);
	printf("\n");
	printStateStack(state_tracker);
	printf("\n");
	printf("%i\n", state_tracker->prev->indent);
	//free(tracker->prev->prev);


	struct StackNode* stack_tracker = malloc(sizeof(struct StackNode));
	stack_tracker->prev = tracker->prev;
	struct StackNode* new_head = malloc(sizeof(struct StackNode));
	new_head->prev = tracker->prev->prev;
	//printStack(new_head);
	//printf("\n");

	// can only pop 1 item from stack
	// the initializeation requires that we stop 1 before(we already starte past the first item) not anymore
	//for(int l = 0; l < state_tracker->prev->name_size; l++)
	//{
	free(stack_tracker->prev);
	stack_tracker->prev = new_head;
	new_head = new_head->prev;
	//}
	/*while(stack_tracker->prev->indent > state_tracker->prev->indent)
	{

	}*/
	// this allows use to start deleting all state_tracker->prev->name_size items in loop
	tracker->prev = new_head;
	printStack(tracker);
	printf("\n");
	printStateStack(state_tracker);
	printf("\n");
	//stack_tracker = stack_tracker->prev;




	// set state_tracker->prev->prev->children[0] to state_tracker->prev
	// set state_tracker->prev to nil
	// print the stac and all subtrees
	main_state_recorder_tree->tracker 		= tracker;
	main_state_recorder_tree->state_tracker = state_tracker;
	main_state_recorder_tree->state_changed = true;
	return true;
}

bool isIndentDecrease1(struct StateMachineVars* main_state_recorder_tree)
{

	// is the ith indent <  i + 1 th indent?
	struct StackNode* tracker 	= main_state_recorder_tree->tracker;
	int count_temp 				= main_state_recorder_tree->count_temp;
	int top_of_state_stack 		= tracker->prev->indent;
	int indent_decrease 		= count_temp-1;  // from the indent value of "Next", only indent_increase1 sets count_2 to it
	//int top_of_word_stack = tracker->prev->indent;

	printf("before %i %i\n", top_of_state_stack, indent_decrease);

	//(*i_ptr) += (count_temp) + peek_size;
	//int c_1 = count_2;
	// -1 because count_temp counts newline
	//int c_2 = count_temp-1;

	//printf("after %i %i\n", c_1, c_2);
	if(top_of_state_stack > indent_decrease)
	{
			printf("%i still needs to decrease\n", top_of_state_stack);

			main_state_recorder_tree->state_changed = true;
			return true;
	}
	return false;

}
bool topOfWordStackIsNotChildren(struct StateMachineVars* main_state_recorder_tree)
{

	struct StackNode* tracker 	= main_state_recorder_tree->tracker;
	char* top_of_word_stack 	= tracker->prev->word;
	// could be the source of future problems
	if(!wordIsChildren(top_of_word_stack))
	{
		printf("%s is top of word stack\n", top_of_word_stack);

		main_state_recorder_tree->state_changed = true;
		return true;
	}
	return false;
}
bool topOfWordStackIsChildren(struct StateMachineVars* main_state_recorder_tree)
{

	struct StackNode* tracker 	= main_state_recorder_tree->tracker;
	struct State* state_tracker = main_state_recorder_tree->state_tracker;

	char* top_of_word_stack = tracker->prev->word;
	if(wordIsChildren(top_of_word_stack))
	{
		printf("%s is top of word stack\n", top_of_word_stack);
		printStateStack(state_tracker);
		printf("\n\n\n");
		main_state_recorder_tree->state_changed = true;
		return true;
	}
	return false;
}
bool setOneSIthChildToZero(struct StateMachineVars* main_state_recorder_tree)
{
	// set_[1]_s_ith_child_to_[0]
	struct State* state_tracker = main_state_recorder_tree->state_tracker;

	printStack(main_state_recorder_tree->tracker);
	printf("\n");
	printStateStack(state_tracker);
	printf("\n");

	struct State* top_of_state_stack = malloc(sizeof(struct State));
	top_of_state_stack->prev = state_tracker->prev;

	// not making the links correctly
	// assume this (loop) will be run lots of times to represent the branches of state objects in the level below the state whose next we are at in the input
	//while(top_of_state_stack->prev->indent >= tracker->prev->indent)
	//{
	//printf("%s\n", top_of_state_stack->prev->name[0]);
	//printf("%i\n", top_of_state_stack->prev->prev->indent);
	// the size can be used as an index because it hasn't been incremented yet
	// top_of_state_stack->prev is the top of the stack
	top_of_state_stack->prev->prev->children[top_of_state_stack->prev->prev->children_size] = top_of_state_stack->prev;
	top_of_state_stack->prev->prev->children_size++;
	//printf("%i\n", top_of_state_stack->prev->prev->children_size);



	//printf("\n");
	top_of_state_stack = top_of_state_stack->prev;
	//printf("value of conditon %i\n", top_of_state_stack->prev->indent >= tracker->prev->indent);
	//}
	printf("\n\n\n");
	state_tracker->prev = top_of_state_stack->prev;
	printStateStack(state_tracker);
	printf("\n");

	// need to deal with the "children" words on the word stack
	// may need another state
	printf("\n\n\n");
	//postorder(state_tracker->prev);
	//postorder(state_tracker->prev->prev, 0);
	printf("\n\n\n");

	main_state_recorder_tree->state_tracker = state_tracker;
	main_state_recorder_tree->state_changed = true;
	return true;

}
bool popFromStack1(struct StateMachineVars* main_state_recorder_tree)
{

	struct StackNode* tracker 	= main_state_recorder_tree->tracker;
	struct State* state_tracker = main_state_recorder_tree->state_tracker;

	printStack(tracker);
	printf("\n");
	printStateStack(state_tracker);
	printf("\n");
	printf("%i\n", state_tracker->prev->indent);
	//free(tracker->prev->prev);


	struct StackNode* stack_tracker = malloc(sizeof(struct StackNode));
	stack_tracker->prev = tracker->prev;
	struct StackNode* new_head = malloc(sizeof(struct StackNode));
	new_head->prev = tracker->prev->prev;
	//printStack(new_head);
	//printf("\n");

	// can only pop 1 item from stack
	// the initializeation requires that we stop 1 before(we already starte past the first item) not anymore
	//for(int l = 0; l < state_tracker->prev->name_size; l++)
	//{
	free(stack_tracker->prev);
	stack_tracker->prev = new_head;
	new_head = new_head->prev;
	//}
	/*while(stack_tracker->prev->indent > state_tracker->prev->indent)
	{

	}*/
	// this allows use to start deleting all state_tracker->prev->name_size items in loop
	tracker->prev = new_head;
	printStack(tracker);
	printf("\n");
	printStateStack(state_tracker);
	printf("\n");
	main_state_recorder_tree->tracker 		= tracker;
	main_state_recorder_tree->state_tracker = state_tracker;
	main_state_recorder_tree->state_changed = true;
	return true;
}
bool computeNumberOfStateNames(struct StateMachineVars* main_state_recorder_tree)
{
	struct StackNode* tracker 	= main_state_recorder_tree->tracker;
	struct State* state_tracker = main_state_recorder_tree->state_tracker;

	struct StackNode* stack_tracker = malloc(sizeof(struct StackNode));
	stack_tracker->prev = tracker->prev;
	int name_size = 0;
	// decrementing the size so the actual items are hidden
	// called 1 time for each item that is not a child so it is remeasuring the size
	//printf("first wohhhhhhhhrd is %s\n", stack_tracker->prev->word);
	// have to travel up the word stack untill hit a category name(children) or a null sized string
	while(!wordIsChildren(stack_tracker->prev->word) || (strlen(stack_tracker->prev->word) == 0))
	{
		//printf("counting %s\n", stack_tracker->prev->word);
		stack_tracker = stack_tracker->prev;
		name_size++;
	}


	//tracker->prev->indent - state_tracker->prev->indent;
	printf("size = %i\n", name_size);
	state_tracker->prev->name = malloc(sizeof(char*) * name_size);
	//printf("state tracker size %i %i\n", sizeof(state_tracker->prev->name)/sizeof(char*), name_size);
	state_tracker->prev->name_size = name_size;
	state_tracker->prev->ith_name = name_size - 1;
	printStack(tracker);
	printf("\n");
	printStateStack(state_tracker);
	printf("\n");
	printf("%s\n", state_tracker->prev->name[state_tracker->prev->ith_name]);
	//exit(0);
	main_state_recorder_tree->tracker 		= tracker;
	main_state_recorder_tree->state_tracker = state_tracker;
	main_state_recorder_tree->state_changed = true;
	return true;
}
bool indentStaysSame(struct StateMachineVars* main_state_recorder_tree)
{

	struct StackNode* tracker = main_state_recorder_tree->tracker;
	struct State* state_tracker = main_state_recorder_tree->state_tracker;

	int top_of_state_stack = state_tracker->prev->indent;
	int top_of_word_stack = tracker->prev->indent;
	printf("before %i %i\n", top_of_state_stack, top_of_word_stack);

	//(*i_ptr) += (count_temp) + peek_size;
	//int c_1 = count_2;
	// -1 because count_temp counts newline
	//int c_2 = count_temp-1;

	//printf("after %i %i\n", c_1, c_2);
	if(top_of_state_stack == top_of_word_stack)
	{
			printf("indent stays the same\n");
			//printf("%i still needs to decrease\n", top_of_word_stack);
			main_state_recorder_tree->state_changed = true;
			return true;
	}
	return false;
}
bool Next(struct StateMachineVars* main_state_recorder_tree)
{
	int count_temp 					= 	main_state_recorder_tree->count_temp;
	char* line 						= 	main_state_recorder_tree->line;
	int i 							= 	main_state_recorder_tree->i;
	char* indent_string 			= 	main_state_recorder_tree->indent_string;
	int peek_size 					= 	main_state_recorder_tree->peek_size;
	struct StackNode* tracker 		= 	main_state_recorder_tree->tracker;
	struct State* state_tracker 	= 	main_state_recorder_tree->state_tracker;

	count_temp = countGapSize(line, i);
	indent_string = makeIndents(count_temp);


	peek_size = peekAtNode(line, i, count_temp);
	char* word = getValue(line, i + count_temp, peek_size);
	// -1 because count_temp takes newline into account
	printf("word next? %s %i\n\n", word, count_temp - 1);
	printStack(tracker);
	printf("\n");
	printStateStack(state_tracker);
	printf("\n\n\n");
	if(wordIsNext(word))
	{
		main_state_recorder_tree->count_temp 	= count_temp;
		main_state_recorder_tree->peek_size 	= peek_size;
		main_state_recorder_tree->state_changed = true;
		return true;
	}

	// are done with all states having an indent >= next(below next in the tree)
	// have top state be the first child of the second from top state(do for all states having a >= indent value than next)
	struct State* top_of_state_stack = malloc(sizeof(struct State));
	top_of_state_stack->prev = state_tracker->prev;

	// not making the links correctly
	// assume this (loop) will be run lots of times to represent the branches of state objects in the level below the state whose next we are at in the input
	printf("top of stack loop\n");
	/*while(top_of_state_stack->prev->indent >= tracker->prev->indent)
	{
		printf("%s\n", top_of_state_stack->prev->name[0]);
		printf("%i\n", top_of_state_stack->prev->prev->indent);
		// the size can be used as an index because it hasn't been incremented yet
		top_of_state_stack->prev->prev->children[top_of_state_stack->prev->prev->children_size] = top_of_state_stack->prev;
		top_of_state_stack->prev->prev->children_size++;
		//printf("%i\n", top_of_state_stack->prev->prev->children_size);



		printf("\n");
		top_of_state_stack = top_of_state_stack->prev;
		printf("value of conditon %i\n", top_of_state_stack->prev->indent >= tracker->prev->indent);
	}*/
	// need to deal with the "children" words on the word stack
	// may need another state

	// move the indent counts 1 unit down the tree
	int count_1 	=	 main_state_recorder_tree->count_1;
	int count_2 	=	 main_state_recorder_tree->count_2;

	printf("before %i %i\n", count_1, count_2);

	i += count_temp + peek_size;
	count_1 = count_2;
	count_2 = count_temp;
	printf("after %i %i\n", count_1, count_2);
	count_temp = countGapSize(line, i);
	indent_string = makeIndents(count_temp);

	//free(word)
	peek_size = peekAtNode(line, i, count_temp);
	word = getValue(line, i + count_temp, peek_size);
	printf("link: %s\n", word);
	printf("\n\n\n");
	//postorder(state_tracker->prev);
	//postorder(state_tracker->prev->prev, 0);
	printf("\n\n\n");
	main_state_recorder_tree->count_temp 	= count_temp;
	main_state_recorder_tree->peek_size 	= peek_size;
	main_state_recorder_tree->state_changed = true;
	return true;
}


// use oop too
struct Data {

	int _int;
	bool _is_int;

	char* _string;
	bool _is_string;

	int string_size;

	float _float;
	bool _is_float;

	int* _int_p;
	bool _is_int_p;

	char** _string_p;
	bool _is_string_p;

	int string_p_size;

	float* _float_p;
	bool _is_float_p;
	// only for the compiler to use
	struct SparseMatrix* levels;
	bool is_levels;
};

// each ContextState is a state
struct ContextState {
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
};
struct ContextState* addFunction(struct ContextState* node,
								bool (*function_pointer)(struct Names* , struct SparseMatrix* ),
							 	 char* function_pointer_name)
{
 	node->function_pointer = function_pointer;
	node->function_pointer_name = function_pointer_name;
	return node;
}

enum attributes {_StartChildren, _Parents, _Children, _Nexts, _int, _string, string_size, _float, _int_p, _string_p, string_p_size, _float_p, sparse_matrix_levels};
struct Data* addInt(int var)
{
	struct Data* variable = malloc(sizeof(struct Data));
	variable->_int = var;
	variable->_is_int = true;
	variable->_is_string = false;
	variable->_is_float = false;
	variable->_is_int_p = false;
	variable->_is_string_p = false;
	variable->_is_float_p = false;
	variable->is_levels = false;

	return variable;
}
struct Data* addString(char* var)
{
	struct Data* variable = malloc(sizeof(struct Data));
	variable->_string = var;
	variable->_is_int = false;
	variable->_is_string = true;
	variable->_is_float = false;
	variable->_is_int_p = false;
	variable->_is_string_p = false;
	variable->_is_float_p = false;
	variable->is_levels = false;

	return variable;
}
struct Data* addFloat(float var)
{
	struct Data* variable = malloc(sizeof(struct Data));
	variable->_float = var;
	variable->_is_int = false;
	variable->_is_string = false;
	variable->_is_float = true;
	variable->_is_int_p = false;
	variable->_is_string_p = false;
	variable->_is_float_p = false;
	variable->is_levels = false;
	return variable;
}

struct Data* addIntPointer(int* var)
{
	struct Data* variable = malloc(sizeof(struct Data));
	variable->_int_p = var;
	variable->_is_int = false;
	variable->_is_string = false;
	variable->_is_float = false;
	variable->_is_int_p = true;
	variable->_is_string_p = false;
	variable->_is_float_p = false;
	variable->is_levels = false;
	return variable;
}

struct Data* addStringPointer(char** var)
{
	struct Data* variable = malloc(sizeof(struct Data));
	variable->_string_p = var;
	variable->_is_int = false;
	variable->_is_string = false;
	variable->_is_float = false;
	variable->_is_int_p = false;
	variable->_is_string_p = true;
	variable->_is_float_p = false;
	variable->is_levels = false;
	return variable;
}

struct Data* addFloatPointer(float* var)
{
	struct Data* variable = malloc(sizeof(struct Data));
	variable->_float_p = var;
	variable->_is_int = false;
	variable->_is_string = false;
	variable->_is_float = false;
	variable->_is_int_p = false;
	variable->_is_string_p = false;
	variable->_is_float_p = true;
	variable->is_levels = false;
	return variable;
}

struct Data* addSparseMatrixLevels(struct SparseMatrix* var)
{
	struct Data* variable = malloc(sizeof(struct Data));
	variable->levels = var;
	variable->_is_int = false;
	variable->_is_string = false;
	variable->_is_float = false;
	variable->_is_int_p = false;
	variable->_is_string_p = false;
	variable->_is_float_p = false;
	variable->is_levels = true;
	return variable;
}

struct ContextState* makeState(struct Names* names)
{

	struct ContextState* state = malloc(sizeof(struct ContextState));

	state->name = malloc(sizeof(struct Names));
	memcpy(state->name, names, sizeof(struct Names));
	//printf("%s, %s\n", state->name->strings[0], state->name->strings[1]);



	state->start_children_size = 0;
	state->parents_size = 0;
	state->children_size = 0;
	state->nexts_size = 0;

	state->var = malloc(sizeof(struct Data));
	state->var->_int = 0;
	state->var->_string = NULL;
	state->var->_float = 0.0;
	state->var->_int_p = NULL;
	state->var->_string_p = NULL;
	state->var->_float_p = NULL;
	state->var->levels = NULL;


	state->var->_is_int = false;
	state->var->_is_string = false;
	state->var->_is_float = false;
	state->var->_is_int_p = false;
	state->var->_is_string_p = false;
	state->var->_is_float_p = false;
	state->var->is_levels = false;
	return state;

}
void deleteState(struct ContextState* node)
{
	free(node->name);
	for(int i = 0; i < node->start_children_size; i++)
		free(node->start_children[i]);
	for(int i = 0; i < node->parents_size; i++)
		free(node->parents[i]);
	for(int i = 0; i < node->children_size; i++)
		free(node->children[i]);
	for(int i = 0; i < node->nexts_size; i++)
		free(node->nexts[i]);

}
// add name
struct Names** makeNew(struct Names** handle, int* handle_size, struct Names* add_node)
{
	//printf("here\n");
	// fix
	int size = *handle_size;
	//printf("handkle size: %i\n", size);
	if(size == 0)
	{
		handle = malloc(sizeof(struct Names*));
	}
	else
	{
		struct Names** x = realloc(handle, size * sizeof(struct Names*));
		if(x != NULL)
		{
			handle = x;
		}
		else
		{
			//failure
		}
	}
	//printf("before\n");
	handle[size] = add_node;
	//memcpy(handle + size, add_node, sizeof(struct Names));
	//printf("after \n%s %s\n", handle[0]->strings[0], handle[0]->strings[1]);
	//printf("after\n");

	*handle_size += 1;
	//printf("%i\n", *handle_size);
	return handle;
}
struct ContextState* addNode(struct ContextState* node,
							 int attribute_name,
							 struct Names* add_node)
{
	switch(attribute_name)
	{
		case _StartChildren:
		{
			//printf("here2\n");
			//printf("%s %s\n", add_node->strings[0], add_node->strings[1]);

			//node->start_children = malloc(sizeof(struct Names*));

			node->start_children = makeNew(node->start_children, &node->start_children_size, add_node);
			//printf("%s ", node->start_children[0]->strings[0]);
			//printf("%s\n", node->start_children[0]->strings[1]);
			//exit(1);
			break;
		}
		case _Parents:
		{
			//node->parents = malloc(sizeof(struct Names*));
			node->parents = makeNew(node->parents, &node->parents_size, add_node);

			break;
		}

		case _Children:
		{
			//node->children = malloc(sizeof(struct Names*));
			node->children = makeNew(node->children, &node->children_size, add_node);

			break;

		}
		case _Nexts:
		{
			//node->nexts = malloc(sizeof(struct Names*));
			node->nexts = makeNew(node->nexts, &node->nexts_size, add_node);
		}
		default:
		{
			// failure
		}

	}

	return node;
}


const int max_states = 20;
struct SparseMatrix {
	struct ContextState** state_list;//[max_states];
	int state_population;   // needed so when visiting the level for the nth time, not resetting the state_id back to 0(as there are now states in this level)
};

const int max_levels = 3;
struct SparseMatrix* levels;//[max_levels];
/*
def doesNextStatesExist(next_states):

	return len(next_states) > 0 and len(next_states[0]) > 0


def isParent(children):

	return children != od()



def hasParent(graph, state, case_):
	return len(graph['parents'][state][case_].keys()) > 0

class ChildParent():
	def __init__(self, child, parent):
		self.child = child
		self.parent = parent


def getIndents(count):

	indent = ''

	while (count > 0):

		indent += '    '
		count -= 1

	return indent


def printStack(bottom):

	tracker = bottom[0]
	stack = []
	print('start stack')
	while (tracker != None):

		stack.append(tracker.child)
		tracker = tracker.parent

	for i, item in enumerate(stack):

		print(stack[i])
	print('end stack')



def isBottomAtTheParentOfCurrentState(parent_cases, bottom_state, bottom_case):

	for p, parent_case in enumerate(parent_cases):

		parent = parent_cases[p][0]

		parent_case = parent_cases[p][1]

		if(bottom_state == parent and bottom_case == parent_case):

			return True


	return False

def getNextStates(tracker, continuing_next_states, indents, graph):


	#print(tracker.parent, tracker.child)
	state1 = tracker.child[0]
	case1 = tracker.child[1]

	# todo: need to delete the bottom of the list as we ascend it, not ignore it
	# for python tracker.parent is to what javascript is to tracker
	while (tracker.parent != None and len(continuing_next_states) == 0):

		indents -= 1
		tracker = tracker.parent
		state1 = tracker.child[0]
		case1 = tracker.child[1]
		# need to exit the main loop
		if (state1 == 'root'):

			return [tracker, [], indents]


		continuing_next_states = [list(a) for a in graph['node_graph2'][state1]['next'][case1].items()]


	return [tracker, continuing_next_states, indents]


def makeNextStates(next_states):
	new_next_states = []

	next_states = [list(a) for a in next_states]

	for n, next_state in enumerate(next_states):

		new_next_states.append([next_states[n][0], next_states[n][1]])




	return new_next_states

def printLevel(graph, state, case_, indents, m, chosen_level):

	if (indents == chosen_level):

		print(getIndents(indents), '|'+ state + '|', case_, 'passed', 'i', '|' + graph['input'][m] + '|', m)




def printLevels(graph, state, case_, indents, m, chosen_level):

	if (indents >= chosen_level):

		print(getIndents(indents), '|'+ state + '|', case_, 'passed', 'i', '|' + graph['input'][m] + '|', m)





def printLevelsBounds(graph, state, case_, indents, m, input_length, chosen_start_level, chosen_end_level):


	print(getIndents(indents), '('+  '\'' + state + '\'' + ',' , case_ + ',', 'f=' + graph['node_graph2'][state]['functions'][case_].__name__ + ',', str(indents) + ')')#, '|' + graph['input'][m] + '|','i ='*///, //m, input_length*/)
	//	#console.log()




/*
def printVarStore(graph):

	m = graph['input']
	return '|' + graph['input'][m] + '|'

*/
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


struct NextStatesPackage* getNextStates(struct ChildParent* tracker,
										struct Names** continuing_next_states,
										int size_of_continuing_next_states,
										int indents,
										struct SparseMatrix* graph,
										state_x_y_hash_table* 	state_x_y_table)
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

		return_package->next_states = levels[state_location->level_id].state_list[state_location->state_id]->nexts;

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
	return levels[point->level_id].state_list[point->state_id]->parents_size > 0;
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

void visit(struct SparseMatrix* levels,
		   struct ContextState* start_node,
		   state_x_y_hash_table* state_x_y_table)
{

	// test by making each function do nothing but return true or false
	struct Names** next_states = malloc(sizeof(struct Names*));
	next_states[0] = start_node->name;
	int next_states_size = 1;
	struct Names* current_state_name = start_node->name;

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
	struct ContextState* dummy_node = malloc(sizeof(struct ContextState));
	dummy_node->name = malloc(sizeof(struct Names));
	dummy_node->name->strings = malloc(sizeof(char*));
	dummy_node->name->strings[0] = "root";
	dummy_node->name->strings[1] = "0";
	dummy_node->name->strings_size = 2;
	ht_insert2(state_x_y_table, dummy_node->name, newPoint(-1, -1));

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
			int maybe_parent = levels[point->level_id].state_list[point->state_id]->start_children_size;
			//printf("maybe_parent = %i", maybe_parent)
			//maybe_parent = graph['node_graph2'][ state ]['children'][ case_ ]
			bool did_function_pass = levels[point->level_id].state_list[point->state_id]->function_pointer(current_state_name, levels);

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
					struct Names** parents = levels[point->level_id].state_list[point->state_id]->parents;
					int num_parents = levels[point->level_id].state_list[point->state_id]->parents_size;

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
					struct Names** start_children = levels[point->level_id].state_list[point->state_id]->start_children;
					int start_children_size = levels[point->level_id].state_list[point->state_id]->start_children_size;
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
					struct Names** nexts = levels[point->level_id].state_list[point->state_id]->nexts;
					int nexts_size = levels[point->level_id].state_list[point->state_id]->nexts_size;
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
				/*struct SparseMatrix**/ 	levels,
				/*state_x_y_hash_table**/ 	state_x_y_table);

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
void printAttribute(int node_size, struct Names** container)
{


	for(int i = 0; i < node_size; i++)
	{
		for(int j = 0; j < container[i]->strings_size; j++)
		{
			printf("  %s", container[i]->strings[j]);

		}
		printf("\n");

	}
}
void print(level_id_state_id* point, struct SparseMatrix* levels, state_x_y_hash_table* state_x_y_table)
{
	printf("node %i, %i\n", point->level_id, point->state_id);
	printf("name:\n");
	printAttribute(1, &levels[point->level_id].state_list[point->state_id]->name);
	printf("\n");

	struct ContextState* node = levels[point->level_id].state_list[point->state_id];
	if(node->start_children_size > 0)
	{
		printf("start children:\n");

		printAttribute(node->start_children_size, node->start_children);
	}


	if(node->parents_size > 0)
	{
		printf("parents:\n");
		printAttribute(node->parents_size, node->parents);

	}

	if(node->children_size > 0)
	{
		printf("children:\n");

		printAttribute(node->children_size, node->children);

	}

	if(node->nexts_size > 0)
	{
		printf("nexts:\n");

		printAttribute(node->nexts_size, node->nexts);

	}

	printf("f=%s\n", node->function_pointer_name);

	struct Data* var = node->var;
	if(var->_is_int)
	{
		printf("%i\n", var->_int);
	}
	else if(var->_is_string)
	{
		printf("%s\n", var->_string);

	}
	else if(var->_is_float)
	{
		printf("%f\n", var->_float);

	}
	else if(var->_is_int_p)
	{
		printf("%p\n", (void*) var->_int_p);

	}
	else if(var->_is_string_p)
	{
		printf("%p\n", (void*) var->_string_p);

	}
	else if(var->_is_float_p)
	{
		printf("%p\n", (void*) var->_float_p);

	}
	// will not overflow, because the addDataType functions will set this to false
	else if(var->is_levels)
	{
		/*
		const int max_states = 20;
		struct SparseMatrix {
			struct ContextState** state_list;//[max_states];
			int state_population;   // needed so when visiting the level for the nth time, not resetting the state_id back to 0(as there are now states in this level)
		};

		const int max_levels = 3;
		struct SparseMatrix* levels;//[max_levels];
		*/

		for(int i = 0; i < 3; i++)
		{
			for(int j = 0; j < levels->state_population; j++)
			{
				level_id_state_id* point_ = ht_search2(state_x_y_table, levels[i].state_list[j]->name);
				print(point_, levels, state_x_y_table);
				printf("|");
			}
			printf("\n");
		}
		printf("\n");

		//printf("%x", var->_float_p);

	}

	// only for the compiler to use
	//struct SparseMatrix* levels;
	//bool is_levels;
}

bool returnTrue(struct Names* current_state, struct SparseMatrix* levels)
{
	printf("got here.  We have entered returnTrue\n\n");
	return true;
}
bool returnFalse(struct Names* current_state, struct SparseMatrix* levels)
{
	return false;
}

void makeTree()
{
	/*
	This makes a sparse matrix to organize the states acording to the level they are at
	there is a hash table that maps state names to coordinates in the matrix

	Here is how the code is laid out.
	Think of each tree from the top level node to the leaves as 1 pyramid
	define 1 pyramid at a time

	*/
	levels = malloc(sizeof(struct SparseMatrix) * max_levels);

	for(int i = 0; i < max_levels; i++)
	{
		levels[i].state_list = malloc(sizeof(struct ContextState*) * max_states);
	}
	//printf("ddd\n");
	/*
	stack = [(level_id, last_state_enumerated, indent level)] have to compare the indent that is too large in indent_decrease to the
	// deepest level's indent value
	*/
	//printf("here1\n");
	state_x_y_hash_table* state_x_y_table =  ht_new2();
	//levels[0].state_list[0] = malloc(sizeof(struct Names*));
	levels[0].state_list[0] = makeState(makeName2("states", "state"));
	//printf("%s|%s %i\n", levels[0].state_list[0]->name->strings[0], levels[0].state_list[0]->name->strings[1], levels[0].state_list[0]->name->strings_size);
	levels[0].state_list[0] = addNode(levels[0].state_list[0], _StartChildren, 	makeName2("names", "0"));
	levels[0].state_list[0] = addNode(levels[0].state_list[0], _Parents, 		makeName2("root", "0"));
	levels[0].state_list[0] = addNode(levels[0].state_list[0], _Children, 		makeName2("start_children", "0"));
	levels[0].state_list[0] = addFunction(levels[0].state_list[0], returnTrue, "returnTrue");



	//levels[0].state_list[0]->function(levels[0].state_list[0]->name, levels);
	/*struct ContextState* addFunction(struct ContextState* node,
									bool* (*function)(struct Names* , struct SparseMatrix* ),
								 	 char* function_name)
	 */
	/*for(int i = 0; i < levels[0].state_list[0]->name->strings_size; i++)
	{
		printf("%s \n", levels[0].state_list[0]->name->strings[i]);

	}*/
	// (root, 0), (tracking, level_state), (tracking, tree), (sparse_matrix, 0)
	// int my_var = getVar(makeNames2("a", "b"), levels)->_int
	ht_insert2(state_x_y_table, levels[0].state_list[0]->name, newPoint(0, 0));
	print(ht_search2(state_x_y_table, levels[0].state_list[0]->name), levels, state_x_y_table);

	levels[0].state_list[1] = makeState(makeName("level_number"));
	levels[0].state_list[1]->var = addInt(0);
	ht_insert2(state_x_y_table, levels[0].state_list[1]->name, newPoint(0, 1));
	print(ht_search2(state_x_y_table, levels[0].state_list[1]->name), levels, state_x_y_table);


	levels[0].state_list[2] = makeState(makeName("state_id"));
	levels[0].state_list[2]->var = addInt(0);
	ht_insert2(state_x_y_table, levels[0].state_list[2]->name, newPoint(0, 2));
	print(ht_search2(state_x_y_table, levels[0].state_list[2]->name), levels, state_x_y_table);



	levels[0].state_list[3] = makeState(makeName("indent_1"));
	levels[0].state_list[3]->var = addInt(0);
	ht_insert2(state_x_y_table, levels[0].state_list[3]->name, newPoint(0, 3));
	print(ht_search2(state_x_y_table, levels[0].state_list[3]->name), levels, state_x_y_table);


	levels[0].state_list[4] = makeState(makeName("indent_2"));
	levels[0].state_list[4]->var = addInt(0);
	ht_insert2(state_x_y_table, levels[0].state_list[4]->name, newPoint(0, 4));
	print(ht_search2(state_x_y_table, levels[0].state_list[4]->name), levels, state_x_y_table);

	levels[0].state_list[5] = makeState(makeName2("tracking", "level_state"));
	levels[0].state_list[5]->var = addInt(0);
	ht_insert2(state_x_y_table, levels[0].state_list[5]->name, newPoint(0, 5));
	print(ht_search2(state_x_y_table, levels[0].state_list[5]->name), levels, state_x_y_table);

	levels[0].state_list[6] = makeState(makeName2("tracking", "tree"));
	levels[0].state_list[6]->var = addInt(0);
	ht_insert2(state_x_y_table, levels[0].state_list[6]->name, newPoint(0, 6));
	print(ht_search2(state_x_y_table, levels[0].state_list[6]->name), levels, state_x_y_table);


	levels[0].state_list[7] = makeState(makeName("sparse_matrix"));
	struct SparseMatrix* sparse_matrix = malloc(sizeof(struct SparseMatrix) * max_levels);
	for(int i = 0; i < max_levels; i++)
	{
		sparse_matrix[i].state_list = malloc(sizeof(struct ContextState*) * max_states);
	}
	levels[0].state_list[7]->var = addSparseMatrixLevels(sparse_matrix);
	ht_insert2(state_x_y_table, levels[0].state_list[7]->name, newPoint(0, 7));
	print(ht_search2(state_x_y_table, levels[0].state_list[7]->name), levels, state_x_y_table);


	printf("\n\n");


		levels[1].state_list[0] = makeState(makeName2("names", "0"));
		levels[1].state_list[0] = addNode(levels[1].state_list[0], _StartChildren, 	makeName2("name", "0"));
		levels[1].state_list[0] = addNode(levels[1].state_list[0], _Parents, 		makeName2("states", "state"));
		levels[1].state_list[0] = addNode(levels[1].state_list[0], _Nexts, 			makeName2("start_children", "0"));
		levels[1].state_list[0] = addFunction(levels[1].state_list[0], returnTrue, "returnTrue");

		ht_insert2(state_x_y_table, levels[1].state_list[0]->name, newPoint(1, 0));
		print(ht_search2(state_x_y_table, levels[1].state_list[0]->name), levels, state_x_y_table);
		printf("\n\n");

			levels[2].state_list[0] = makeState(makeName2("name", "0"));
			levels[2].state_list[0] = addNode(levels[2].state_list[0], _Parents, makeName2("names", "0"));
			levels[2].state_list[0] = addNode(levels[2].state_list[0], _Nexts, 	makeName2("indent_increase", "0"));
			levels[2].state_list[0] = addNode(levels[2].state_list[0], _Nexts, 	makeName2("indent_decrease", "0"));
			levels[2].state_list[0] = addFunction(levels[2].state_list[0], returnTrue, "returnTrue");

			ht_insert2(state_x_y_table, levels[2].state_list[0]->name, newPoint(2, 0));
			print(ht_search2(state_x_y_table, levels[2].state_list[0]->name), levels, state_x_y_table);
			printf("\n\n");

			levels[2].state_list[1] = makeState(makeName2("indent_increase", "0"));
			//levels[2].state_list[1] = addNode(levels[2].state_list[1], _Nexts, 	makeName2("name", "0"));
			levels[2].state_list[1] = addNode(levels[2].state_list[1], _Nexts, 	makeName2("\"Start Children\"", "0"));
			levels[2].state_list[1] = addFunction(levels[2].state_list[1], returnTrue, "returnTrue");


			ht_insert2(state_x_y_table, levels[2].state_list[1]->name, newPoint(2, 1));
			print(ht_search2(state_x_y_table, levels[2].state_list[1]->name), levels, state_x_y_table);
			printf("\n\n");

			levels[2].state_list[2] = makeState(makeName2("indent_increase", "1"));
			levels[2].state_list[2] = addNode(levels[2].state_list[2], _Nexts, 	makeName2("states", "substates"));

			ht_insert2(state_x_y_table, levels[2].state_list[2]->name, newPoint(2, 2));
			print(ht_search2(state_x_y_table, levels[2].state_list[2]->name), levels, state_x_y_table);
			printf("\n\n");

			// the recursion will be detected by the positive level difference between the current state and the Start Children State
			levels[2].state_list[3] = makeState(makeName2("indent_increase", "2"));
			levels[2].state_list[3] = addNode(levels[2].state_list[3], _StartChildren, 	makeName2("names", "0"));
			levels[2].state_list[3] = addNode(levels[2].state_list[3], _Nexts, 	makeName2("indent_decrease", "1"));

			ht_insert2(state_x_y_table, levels[2].state_list[3]->name, newPoint(2, 3));
			print(ht_search2(state_x_y_table, levels[2].state_list[3]->name), levels, state_x_y_table);
			printf("\n\n");


			levels[2].state_list[4] = makeState(makeName2("\"Start Children\"", "0"));
			//levels[2].state_list[4] = addNode(levels[2].state_list[4], _StartChildren, 	makeName2("names", "0"));
			levels[2].state_list[4] = addFunction(levels[2].state_list[4], returnTrue, "returnTrue");
			// has no neighbors the stack should shrink after this state runs
			ht_insert2(state_x_y_table, levels[2].state_list[4]->name, newPoint(2, 4));
			print(ht_search2(state_x_y_table, levels[2].state_list[4]->name), levels, state_x_y_table);
			printf("\n\n");



			levels[2].state_list[5] = makeState(makeName2("indent_decrease", "0"));
			levels[2].state_list[5] = addFunction(levels[2].state_list[5], returnFalse, "returnFalse");

			ht_insert2(state_x_y_table, levels[2].state_list[5]->name, newPoint(2, 5));
			print(ht_search2(state_x_y_table, levels[2].state_list[5]->name), levels, state_x_y_table);
			printf("\n\n");

			levels[2].state_list[6] = makeState(makeName2("indent_decrease", "1"));

			ht_insert2(state_x_y_table, levels[2].state_list[6]->name, newPoint(2, 6));
			print(ht_search2(state_x_y_table, levels[2].state_list[6]->name), levels, state_x_y_table);
			printf("\n\n");

		// can't define a second state with the same name

		//start_children
			//0
		// https://stackoverflow.com/questions/4823177/reading-a-file-character-by-character-in-c
		visit(levels, levels[0].state_list[0], state_x_y_table);

		exit(0);
}

/*
def visit(node, graph, indents, debug):
	# assume graph is nested lists
	# does depth first tranversal for each subgraph(each subgraph is a state name that has children)
	# does breath first traversal for within each subgraph
	#print("got here")
	graph['node_graph2'] = od([ makedTupleOfOrderedDicts(a) for a in graph['node_graph2']])
	x = node[0]
	y = node[1]
	next_states = [node]
	action = {}
	bottom = []
	# assumes [state, case_] actually runs
	parent = ChildParent(['root', 0], None)
	bottom.append(parent)
	ii = 0
	#console.log(getIndents(indents), 'start state', node)
	while(len(next_states) != 0):

		#print(ii)

		if(ii == 200):
			#exit(1)
			pass


		#print(getIndents(indents), 'next_states', next_states)

		state = ''
		case_ = 0
		state_changed = False

		# machine will stop running if all have failed(there must be more than 0 states for this to be possible) or error state runs
		# loop ends after the first state passes
		j = 0
		while(j < len(next_states)):

			#print('next_states', next_states)
			state = next_states[j][0]
			case_ = next_states[j][1]
			#print(cases)
			# for same next state at multiple cases
			#for case__ in cases:
			#	case_ = case__
			#print('|' + state + '|', case_)

			maybe_parent = graph['node_graph2'][ state ]['children'][ case_ ]
			did_function_pass = graph['node_graph2'][state]['functions'][case_]([state, case_], graph)
			#print(did_function_pass)
			if (did_function_pass):
				#print('next states', graph['node_graph2'][state]['next'][case_])
				#print(maybe_parent)

				#if (state == 'error'):

				#	print('you have invalid input')
				#	exit()

				# this case is for getting the children from the parent
				# needs to always check before the isParent
				if (hasParent(graph, state, case_)):
					# x = (lowest_bottom, indent_number)
					# push the state to the bottom if bottom happens to be one of state's parents
					# only checks the state and not the case
					bottom_state = bottom[0].child[0]
					bottom_case = bottom[0].child[1]

					parent_cases = [list(a) for a in graph['parents'][state][case_].items()]
					#print('next_states', parent_cases)
					parent_cases = makeNextStates(parent_cases)
					if (isBottomAtTheParentOfCurrentState(parent_cases, bottom_state, bottom_case)):

						new_parent = ChildParent([state, case_], bottom[0])
						# link passing state to its parent on bottom of stack, extending the stack by 1, vertically
						bottom[0] = new_parent
						indents += 1
						#print('indent increasing', indents)



				#print('maybe_parent', maybe_parent, isParent(maybe_parent))

				# for when passing the current state(it is in the current next states) has a child(called next states)
				if (isParent(maybe_parent)):
					# x = (lowest_bottom, next_states)
					#print('here')
					# add passing state horizontally
					bottom[0].child = [state, case_]

					# getting the children
					children = [list(a) for a in graph['node_graph2'][state]['children'][case_].items()]
					#print('next_states', children)
					children = makeNextStates(children)
					next_states = []
					for i, child in enumerate(children):

						next_states.append(children[i])

					if debug:

						m = graph['i']
						printLevelsBounds(graph, state, case_, indents, m, len(graph['input']), 0, -1)




				# for when passing the current state(it is in the current next states) does not have a child but has neighbor states(called next states)
				else:
					# x = (next_states)
					# x_total = (lowest_bottom, next_states, indent_number)
					# there is a problem with how dict_items is being used

					#print(graph['node_graph2'][state]['next'])
					next_states = [list(a) for a in graph['node_graph2'][state]['next'][case_].items()]


					next_states = makeNextStates(next_states)
					#print('next_states', next_states)
					if debug:
						m = graph['i']
						printLevelsBounds(graph, state, case_, indents, m, len(graph['input']), 0, -1)
					# add passing state horizontally
					bottom[0].child = [state, case_]



				state_changed = True

				break


			j += 1
			#if state_changed:
			#	break

		#printStack(bottom)
		# if a child fails and
		#print(next_states, state_changed)
		# hit end state at any level below top level
		if (len(next_states) == 0):

			# x_total = (lowest_bottom, next_states, indent_number)

			# have linked list representing the stack
			# first item is in bottom[0]

			# travel up stack untill either hits root or hits neighbors of a prev visited level
			tracker_continuing_next_states_indents = getNextStates(bottom[0], next_states, indents, graph)
			#print(tracker_continuing_next_states_indents)
			tracker = tracker_continuing_next_states_indents[0]
			continuing_next_states = tracker_continuing_next_states_indents[1]
			indents = tracker_continuing_next_states_indents[2]


			bottom[0] = tracker
			next_states = continuing_next_states
			#print('next_states 5', next_states)

			state_changed = True
			# might not actually be true ever
			'''

			if (tracker == null)
				console.log('done runing machine')
			*/
			//'''


		/*#print( )
		# if all fail then all will be rerun unless this condition is here
		if(not state_changed and len(next_states) > 0):
			# all next_states failed so this level cannot be finished
			# travel up like before but choose the next child after the tracker

			print('error at ')
			print(getIndents(indents), next_states, 'on')
			print(getIndents(indents), '('+  '\'' + state + '\'' + ',' , case_ + ',', 'f=' + graph['node_graph2'][state]['functions'][case_].__name__ + ',', str(indents) + ')')
			break

			#print(next_states, 'have failed so your state machine is incomplete')
			#exit()
		#if(not state_changed):
		#	print("we are screwed", len(next_states))
		ii += 1


	#print(getIndents(indents), '1state machine is finished', '|'+ state + '|', case_)
	#print(getIndents(indents), 'exit visit', node)
	#print(graph)
*/
/*
ContextState
	char* name
	char** contexts
	ContextState* start_children
	ContextState* parents
	ContextState* children
	ContextState* nexts

*/
/*
for the parser control flow, and the intermediate state table(the details for the control flow will be slightly different than the state table)
level\state pairs

for the final state tree
reacd through the table and make a hash table

save the partial data in the same control flow table under different contexts

(current entry index, current level) stack
names, start children, parent, children, next, functions
levels\states
-------------------------------------
0 	| (root, 0)
1	| (states, state), (level_number), (state_id), (indent_1), (indent_2), (tracking, level_state), (tracking, tree), (sparse_matrix)
2	| (names, 0), (start_children, 0)
3	| (name, 0) , (indent_increase, 0) (indent_increase, 1), (indent_increase, 2) (start_children, 0), (indent_decrease, 0)
(indent_decrease, 1)

states
	state (order = 1, level = 1)
		Start Chdildren
			names
				0 (order = 2, level = 2)
					Start Chilren
						name
							0 (order = 3, level = 3)
								Next
									indent_increase 0, indent_decrease 0
						indent_increase
							0  (order = 4, level = 3)
								Next
									name 0, "Start Children" 0
							1  (order = 5, level = 3)
								Next
									states substates
							2
								Start Children
									names 0
								Next
									indent_decrease 1

						"Start Children"
							0  (order = 6, level = 3)
								Start Children
									names 0 (the function can return false after )
								Functions
									appendPartialEntryToTable:
										increment current entry
						indent_decrease
							0  (order = 7, level = 3)
							1  (order = 13(wrong), level = 3)

					Parent
						states state
					Next
						start_children 0
		Children
			start_children
				0  (order = 8, level = 2)
					Start Children
						"Start Children"
							0
								Start Children
									indent_increase 2
					Next
						parent 0

make sure the above works



						"Parent" 0
			"Parent"
				0   (order = 9, level = 2)
						indent_increase 1
		Function
			increaseLevelNumber
	substates  (order = 10, level = 1)
		Recursive
			states 0






		Start Children
			parent
				0  (order = 11, level = 2)
					Start Children
						link
							0  (order = 12, level = 3)
								Next
									link 0
									indent_decrease 1
					Parent
						state substates
	Next
		state, end
end

states_to_coordinates = [(x_i, y_i)]
states_to_coordinates.hash(state_name_i) = (x_i, y_i)

sparse_matrix = [level_i]

level_i = [state_i]
state_i
	state attributes

*/
int next_states_list[] = {
	// if there is at least 1 item of a category, next, parents, functions, children, then the category name will be present
	// else there will be no category name
	/*  start			   	*/		a, 					filler, 				filler,
	/*  a				   	*/		indent_increase1, 	filler, 				filler,
	/*  indent_increase1   	*/		a, 					children, 				is_indent_decrease/* does next indent decrease*/,

									/* >= 1 child*/
	/*  children		   	*/		indent_increase1, 	filler, 				filler,
	/*  is_indent_decrease 	*/		collect_state_name, filler, 				filler,
	/*  collect_state_name 	*/		pop_from_stack, 	filler, 				filler,
	/*  pop_from_stack	   	*/		is_indent_decrease1, indent_stays_same/* all of the states below the "Next" at 4 have been collected */, 	filler,
	/*  indent_stays_same  	*/		next, 				a, 						filler,
	/*  next				*/ 		filler/*indent_increase2*/, 			filler, 				filler,
	// same edges as is_indent_decrease but will be running slightly different code(will check the word stack agains the state stack the same way its earlier enumerated state did with count_1 and count_2)
	/*  is_indent_decrease1	*/ 		top_of_word_stack_is_not_children, top_of_word_stack_is_children, 				filler, // add support for is_indent_decrease1
	/* top_of_word_stack_is_not_children */ collect_state_name, filler, filler,

	/* top_of_word_stack_is_children */ set__one__s_ith_child_to__zero_, filler, filler,

	/* set__one__s_ith_child_to__zero_ */ pop_from_stack1, filler, filler,
	/* pop_from_stack1 */ compute_number_of_state_names, filler, filler,
	/* compute_number_of_state_names */ is_indent_decrease1, filler, filler//,
	// link  link, is_indent_decrease2  same as decrease1 //, filler
	// indent_stays_same is guaranteed because the items poped from the stack are analyzed quite closely from the is_indent_decrease1 option
	// need a state or 2 to be at the first state name after children to set up the size for the state names
	// pop_from_stack1 -> compute_number_of_state_names -> is_indent_decrease1, indent_stays_same

	// next -> indent increases -> link
	// link -> link, indent decrease
};
/*

struct State
{
	char** name;
	int name_size;
	int ith_name;
	struct State** children;
	int children_size;
	char** next;
	int next_size;
	char** parents;
	int parents_size;
	char** functions;
	int functions_size;
	int indent;
	struct State* prev;
};

*/

void visitNodes()
{
	makeTree();
	struct StateMachineVars* main_state_recorder_tree = malloc(sizeof(struct StateMachineVars));

	// https://github.com/protobuf-c/protobuf-c
	// need dummy\n for parser to work
	// count_temp is setting count_2 to the size from findGapSize of the previous string found(is equal to the number of tabs before the current word)
	// read a file from input from now on
	main_state_recorder_tree->line = "dummy\n\tstring_1\n\t\tstring_2\n\t\t\tstring_3\n\t\t\t\tChildren\n\t\t\t\t\tstring_4\n\t\t\t\t\t\tstring_5\n\t\t\t\t\t\t\tstring_6\n\t\t\t\t\t\t\t\tChildren\n\t\t\t\t\t\t\t\t\tstring_9\n\t\t\t\t\t\t\t\t\t\tstring_10\n\t\t\t\t\t\t\t\t\t\t\tstring_11\n\t\t\t\tNext\n\t\t\t\t\tstring_1 string_2 string_3\n\t\t\t\t\tstring_1_1 string_2_1 string_3_1\n\t\t\t\t\tstring_1_2 string_2_2 string_3_2\n\t\t\t\t\tstring_1_3 string_2_3 string_3_3\n\t\t\t\tParents\n\t\t\t\t\tnull\n\t\t\t\tFunctions\n\t\t\t\t\tstring_7\n\t\t\t\t\tstring_8";
	main_state_recorder_tree->size = strlen(main_state_recorder_tree->line);
	main_state_recorder_tree->i = 0;


	//int* i_ptr = &i;
	main_state_recorder_tree->count_1 = 0;
	main_state_recorder_tree->count_2 = 0;
	main_state_recorder_tree->loop_count = 0;
	main_state_recorder_tree->level_count = 0;
	int* loop_count_ptr = &main_state_recorder_tree->loop_count;
	// is just the bottom of the word stack(It is not used for anything else)
	main_state_recorder_tree->root = malloc(sizeof(struct StackNode));

	main_state_recorder_tree->root->word = NULL;
	main_state_recorder_tree->root->prev = NULL;
	main_state_recorder_tree->root->indent = 0;


	// this is the actual root state
	main_state_recorder_tree->state_root = malloc(sizeof(struct State));
	main_state_recorder_tree->state_root->name = NULL;
	main_state_recorder_tree->state_root->prev = NULL;
	main_state_recorder_tree->state_root->next = NULL;
	main_state_recorder_tree->state_root->children = malloc(sizeof(struct State*) * 10);
	main_state_recorder_tree->state_root->children_size = 0;
	main_state_recorder_tree->state_root->indent = 0;



	main_state_recorder_tree->tracker = malloc(sizeof(struct StackNode));
	main_state_recorder_tree->tracker->word = NULL;
	main_state_recorder_tree->tracker->indent = 0;
	main_state_recorder_tree->tracker->prev = main_state_recorder_tree->root;

	main_state_recorder_tree->state_tracker = malloc(sizeof(struct State));
	main_state_recorder_tree->state_tracker->name = NULL;
	main_state_recorder_tree->state_tracker->indent = 0;
	main_state_recorder_tree->state_tracker->next = NULL;
	main_state_recorder_tree->state_tracker->prev = main_state_recorder_tree->state_root;

	main_state_recorder_tree->dimension_count = 0;
	main_state_recorder_tree->dimension_count_ptr = &main_state_recorder_tree->dimension_count;


	int max_next_states = 3;
	int* next_states = malloc(sizeof(int) * max_next_states);

	next_states[0] = start;
	next_states[1] = filler;
	next_states[2] = filler;
	//memcpy(next_states,
	//	next_states_list + getFirstForNextStates(start),
	//	sizeof(int) * max_next_states);

	// state history
	// bool array length = |states|

	int count = 0;
	// pointers for incrementing
	main_state_recorder_tree->next_location_of_newline = 0;

	main_state_recorder_tree->next_location_of_newline_ptr = &main_state_recorder_tree->next_location_of_newline;
	//int* count_1_ptr = &count_1;
	//int* count_2_ptr = &count_2;
	int winning_state = start;
	//main_state_recorder_tree->word;
	//main_state_recorder_tree->indent_string;
	//main_state_recorder_tree->count_temp;
	//main_state_recorder_tree->peek_size;

	bool (*function_table[]) (struct StateMachineVars*) = {
			Start,
			A,
			incrementCount,   // indent_increase1

			Children,
			isIndentDecrease,
			collectStateName,

			popFromStack,
			indentStaysSame,
			Next,

			isIndentDecrease1,
			topOfWordStackIsNotChildren,
			topOfWordStackIsChildren,
			setOneSIthChildToZero,
			popFromStack1,

			computeNumberOfStateNames,


			};
/*
start,
a,
indent_increase1,
children,
is_indent_decrease,
collect_state_name,
pop_from_stack,
indent_stays_same,
next,
is_indent_decrease1,

top_of_word_stack_is_not_children,
top_of_word_stack_is_children,

set__one__s_ith_child_to__zero_,
pop_from_stack1,
compute_number_of_state_names,


indent_increase2,
abcd,
indent_stays_same1,

parent,
indent_increase3,
abcd1,
indent_stays_same2,
indent_decrease2,
Functions,
indent_increase4,
abcd2,
indent_stays_same3,
indent_decrease3,
filler
*/
	printf("start state %s\n", getStateString(winning_state));

	while(!isEmpty(next_states))
	{
		if(count == 53)
		{
			exit(1);
		}
		// check for out of bounds or null
		// print state
		main_state_recorder_tree->state_changed = false;//malloc(sizeof(bool) * max_next_states);
		//memset(state_changed, false, sizeof(bool));
		for(int k = 0; k < max_next_states; k++)
		{
			// soemthing is off with the indexes
			//printf("trying state %s|%i\n", getStateString(next_states[k]), next_states[k]);
			bool result = function_table[ next_states[k] ](main_state_recorder_tree);
			//printf("f = %i\n", result);
			if (result)
			{
				winning_state = next_states[k];
				//printf("winning state %s\n", getStateString(winning_state));

				main_state_recorder_tree->state_changed = true;
				break;
			}
			// prent next state being tried
			//printf("trying %s\n", getStateString(next_states[k]));
			//switch(next_states[k])
			//{
				// cases

/*
bool (*function_table[]) (void) = {fun0, fun1, fun2};
printf("%d\n", function_table[0]());
printf("%d\n", function_table[1]());
printf("%d\n", function_table[2]());

*/
				//case start:
				//{

					// should not be doing much

					//struct StackNode* next_word = malloc(sizeof(struct StackNode));
					/*incrementCountAndGetWord
					printf("got here\n");

					// indents + the string so i is at next indent
					i += count_2 + peek_size;

					printf("%s%s%i\n\n", indent_string, next_word->word, count_2);
					//exit(1);
					// jump value
						// sets i to i += len(word)
					*i_ptr += strlen(word);
					// shift counts 1 and 2

					free(indent_string);

					//free(word);



					//next_word->word = malloc(sizeof(char) * size);
					//memcpy(next_word->word, word, sizeof(char) * size);
					next_word->indent = count_2;
					//printf("%i %i\n", next_word->indent, count_2);
					//free(word);
					next_word->prev = tracker->prev;

					tracker->prev = next_word;
					printStack(tracker);
					printf("\n");
					//printStateStack(state_tracker);
					//printf("\n");

					*/
					//function_table[ start ](main_state_recorder_tree);

					//Start(main_state_recorder_tree);

					//free(next_word);
					//free(next_word->word);

					//state_changed = true;

					//break;
				//}
				//case a:
				//{

					// a (first round the a that came before a doesn't exist)
					// countGapSize
						// get the number of indents from i to start of next word = count_2
					// get to node
						// moves i to first char of word i += indent_count + 1
					// peek node
						// moves temp_i to first char of word temp_i = i + indent_count + 1
					//function_table[ a ](main_state_recorder_tree);

					//A(main_state_recorder_tree);
						//incrementCount

						//state_changed = true;







					//break;

				//}
				//case indent_increase1:
				//{



						//incrementCount
						//incrementCount(main_state_recorder_tree);
						//printf("%i, %i\n", count_1, count_2);





					//break;

				//}
				//case children:
				//{

					//indent_string = makeIndents(*count_2_ptr);



					//Children(main_state_recorder_tree);



					//break;

				//}
				//case is_indent_decrease:
				//{
					// is the next indent change an indent decrease
					//isIndentDecrease(main_state_recorder_tree);




					//break;

				//}
				//case collect_state_name:
				//{
					// visit strings in stack untill their indent == indent of top state object
					// save the strings into the top state object as the state name
					// set second to top state's child to the top state in stack
					// pop top state off stack by deleting its prev link
					// for each node in stack
						// print out the node and its subtree


					// visit strings in stack untill their indent == indent of top state object
					// save the strings into the top state object as the state name

					//collectStateName(main_state_recorder_tree);

					//break;

				//}
				//case pop_from_stack:
				//{

					//popFromStack(main_state_recorder_tree);


					//break;

				//}
				//case is_indent_decrease1:
				//{
					//isIndentDecrease1(main_state_recorder_tree);




					//break;

				//}
				//case top_of_word_stack_is_not_children:
				//{
					//topOfWordStackIsNotChildren(main_state_recorder_tree);

					//break;
				//}
				//case top_of_word_stack_is_children:
				//{
					//topOfWordStackIsChildren(main_state_recorder_tree);

					//break;
				//}
				//case set__one__s_ith_child_to__zero_:
				//{
					//setOneSIthChildToZero(main_state_recorder_tree);
					//break;
				//}
				//case pop_from_stack1:
				//{
					//popFromStack1(main_state_recorder_tree);
					//break;
				//}
				//case compute_number_of_state_names:
				//{
					//computeNumberOfStateNames(main_state_recorder_tree);
					//break;
				//}
				//case indent_stays_same:
				//{
					// indent staying the same is supposed to be related to the indent level at 'Next' in the input
					//indentStaysSame(main_state_recorder_tree);
					//state_changed = true;


					//break;

				//}
				//case next:
				//{
					//Next(main_state_recorder_tree);

					//break;

				//}
				//case filler:
				//{

					//state_changed = true;


					//break;

				//}
				//default:
				//{

					//main_state_recorder_tree->state_changed = true;

					//break;
				//}


			//}

			/*if(main_state_recorder_tree->state_changed)
			{
				winning_state = next_states[k];
				printf("winning state %s\n", getStateString(winning_state));

				break;
			}*/
/*
each number is a base sequence
*/

		//printf("i = %i\n", i);

		}
		printf("------------\n");


		if(main_state_recorder_tree->state_changed)
		{
			//printf("location of next first is %i\n", getFirstForNextStates(winning_state));
			memcpy(next_states,
				next_states_list + getFirstForNextStates(winning_state),
				sizeof(int) * max_next_states);
		}
		else
		{
			printf("all states failed\n");
			//printf("%i\n", filler);

			for(int j = 0; j < max_next_states; j++)
			{
				//printf("%i\n", next_states[i]);
				printf("%s\n", getStateString(next_states[j]));
			}
			printf("\n");
			free(next_states);
			next_states = malloc(sizeof(int) * max_next_states);

			next_states[0] = filler;
			next_states[1] = filler;
			next_states[2] = filler;


			// print out next states
		}
		count++;
	}
	// print completion

}
 /*
 assume \n\t is just part of normal increment
start -> S
S->a tab_increase S | children Child_structure next NextStructure parents ParentStructure
Child_structure -> a tab_increase S | next(backtrack)
NextStructure -> a tab_consittency b tab_consittency c tab_consittency d NextStructure | parents(backtrack)
ParentStructure -> a b c d ParentStructure | functions(backtrack)

next states
each state is a switch statement
each state resets the next states

start -> a
a -> indent_increase1
indent_increase1 -> a, Children

Children -> indent_increase1, is_indent_decrease, indent_stays_same
is_indent_decrease -> collect_state_name
collect_state_name -> pop_from_stack
pop_from_stack -> is_indent_decrease
indent_stays_same -> Next

Next -> indent_increase2, indent_stays_same
indent_increase2 -> a b c d
a b c d -> indent_stays_same1
indent_stays_same1 -> a b c d, indent_decrease1
indent_decrease1 -> Parent

Parent -> indent_increase3, indent_stays_same1
indent_increase3 -> a b c d1
a b c d1 -> indent_stays_same2
indent_stays_same2 -> a b c d1, indent_decrease2
indent_decrease2 -> Functions

Functions -> indent_increase4, indent_stays_same2
indent_increase4 -> a b c d2
a b c d2 -> indent_stays_same3
indent_stays_same3 -> a b c d2, indent_decrease3
indent_decrease3 -> a




 */

 /*
 struct TreeNode
 {
	 char* word;
	 struct TreeNode* left;
	 struct TreeNode* right;
 };*/

 void readLine(char* line)
 {
	 // this program reads in a line of words separated by a sequence of 1 newline and and increasing number of tabs.  the differing number of tabs is used to treat the sequence like a multiway tree
	 // the words are stored in a reverse stack
	 // the next, children, functions (null) are markers on the stack.
	 // they mark when to stop collecting words.
	 // the sequences of words are then stored in a hash table as keys
	 // the values are the tree structures implied by the structure started by next, children, functions


	 // each call is responsable for the following subtree
	 /*
	 a
	 	b
			c
				.
					.
						children
							a b c d | f()
						next
							a b c d | f()
						parents
							a b c d | f()
						functions
							a b c d | f()
	1 function for each line

	input will be set up a certain way so any ambiguous grammer will not affect the process
	setup ->S
	S -> aA | Children
	A -> aA | childrenChildren
	Children -> nextNext | a b c d | aS
	Children -> a b c d | collectContextDimensions | null
	Next->a b c d | collectContextDimensions | null
	Parents->a b c d | collectContextDimensions | null
	Functions ->a b c d | collectContextDimensions | null


	{something} = current part working on
	setup -> {Input} newline loop
	Input -> (1st newline) (a|CNPF) newline tab_increase loop
	CNPF -> Chilren Next Parents Functions
	Chilren -> children newline (tab_increase (StateTuple | Input) | tab_same | tab_decrease)

	Next

	Parents

	Funcitons
	StateTuple -> a b c d | null
	 */
	printf("\n");
	int i = 0;
	int* i_ptr = &i;
	int count_1 = 0;
	int count_2 = 0;
	int loop_count = 0;
	int level_count = 0;
	int* loop_count_ptr = &loop_count;
	struct StackNode* root = malloc(sizeof(struct StackNode));

	root->word = NULL;
	root->prev = NULL;
	root->indent = 0;



	struct State* state_root = malloc(sizeof(struct State));
	state_root->name = NULL;
	state_root->prev = NULL;
	state_root->next = NULL;
	state_root->indent = 0;
	//int next_location_of_newline = getEndIndexOfWord(line, *i_ptr);
	//printf("loop_count: %i i: %i next_location_of_newline: %i\n", loop_count, i, next_location_of_newline);

	// current node

	// size = next_location_of_newline - i
	//char* word = NULL;// = makeWord(next_location_of_newline, line, *i_ptr);
	//int size = next_location_of_newline - *i_ptr;

	/*struct StackNode* first_word = malloc(sizeof(struct StackNode));
	first_word->word = malloc(sizeof(char) * size);
	memcpy(first_word->word, word, sizeof(char) * size);
	first_word->prev = root;
*/

	struct StackNode* tracker = malloc(sizeof(struct StackNode));
	tracker->word = NULL;
	tracker->indent = 0;
	tracker->prev = root;

	struct State* state_tracker = malloc(sizeof(struct State));
	state_tracker->name = NULL;
	state_tracker->indent = 0;
	state_tracker->next = NULL;
	state_tracker->prev = state_root;


	//printStack(tracker);
	//printf("\n");

	//first_word->prev = root;

	//printf("%s\n", tracker->prev->word );
	//printf("level number %i\n", level_count);

	//*i_ptr = next_location_of_newline;
	//count_2 = countGapSize(line, *i_ptr);
	//printf("last indent : %i current indent %i\n\n", count_1, count_2);
	// \n is not counted in countGapSize
	//*i_ptr += count_2 + 1;
	//count_1 = count_2;
	// start S here
	int dimension_count = 0;
	int* dimension_count_ptr = &dimension_count;

	visitNodes();
	//Input(line, count_1, count_2, i_ptr, loop_count_ptr, tracker, dimension_count_ptr, state_tracker);

 }
int main()
{
	//printf("%lu %s %x %i \n", sizeof(char*), next_states[1], next_states[1], next_states[1] == NULL);

	//ht_hash_table* ht = ht_new();
	// add stuff to hash table
	//ht_del_hash_table(ht);
	//return 0;
	char* state_graph = "string_1\n\t\tstring_2\n\t\t\tstring_3\n\t\t\t\tChildren\n\t\t\t\t\tstring_3\n\t\t\t\t\t\tstring_4\n\t\t\t\t\t\t\tstring_5\n\t\t\t\t\t\t\t\tChildren\n\t\t\t\tNext\n\t\t\t\t\tstring_1 string_2 string_3\n\t\t\t\t\tstring_1_1 string_2_1 string_3_1\n\t\t\t\t\tstring_1_2 string_2_2 string_3_2\n\t\t\t\t\tstring_1_3 string_2_3 string_3_3\n\t\t\t\tParents\n\t\t\t\tFunctions\n\t\t\t\t\tstring_6\n\t\t\t\t\tstring_7";
	/*

	count # of \t from \n to letter
	have 2 counts
		current node count
		child node count
		child -> current
		use child as current
	if hit word then \n\t...
		save it in child node
	if hit words with spaces then \n\t...
		go from current to children, next, parents, or functions
	*/
	/*bool (*function_table[]) (void) = {fun0, fun1, fun2};
	printf("%d\n", function_table[0]());
	printf("%d\n", function_table[1]());
	printf("%d\n", function_table[2]());
	*/
	readLine(state_graph);
	return 0;
	// function that can parse the 3 lines below and give me 	char x[] = "test something_else";


	// level 1
	FILE* fptr;
	fptr = fopen("next_states.txt","r");
	// make sure this works for next_states, children, and parents input files
	int number_of_characters_in_file = 1926;
	char* next_states_from_file = malloc(sizeof(char) * number_of_characters_in_file);
	int k = 0;
	// put in a char* using realloc
	if(fptr != NULL)
	{
		while(k <= number_of_characters_in_file)
		{
			next_states_from_file[k] = fgetc(fptr);

			k++;
		}
	}
	next_states_from_file[k] = '\0';
	//for(int i = 0; next_states[i] != '\0'; i++)
	//	printf("%i |%c|\n", i, next_states[i]);
	//exit(0);
	//printf("%s\n", next_states);
	//exit(0);

	//for(int i = 0; i < 100; i++)
	//	printf("%i, %i\n", ranges[i]->low, ranges[i]->high);


	// practice c hash table
	//for(int i = 0; i < 100; i++)
	//	printf("%s\n", next_state_chart[i]);
	// next_states is missing a state that children has (next_state_2)
	//printf("%s\n", next_state_chart[0]);
	//printf("%s\n", next_state_chart[1]);

	//printf("%i\n", strlen(next_states));
	//printf("%s", next_states_from_file);
	exit(0);


	//for(int i = 0; i < 100; i++)
	//	printf("%s\n", next_state_chart[i]);
	exit(0);
	//for(int i = 0; i < 29; )
	//{
	//	if (upper_bound - start > 0)
	//	{
	//		char* line = collectLine(start, upper_bound, next_states_from_file);
	//		lines[i] = line;
	//		i++;

	//	}
		//line = processLine(line);
		/*if (strcmp(line, "null") == 0)
		{
			//printf("%s\n", line);

		}
		else
		{
			int j = 0;
			while( line[j] != '\0')
			{
				int k = getUpperBoundForLine(j, line, ' ');
				//char* word = collectLine(j, k, line);
				printf("%s\n", word);
				//char* word = malloc(sizeof(char) * (k - j));
				//words[k - j] = '\0';

				j = k + 1;

				//printf("%i\n", k);
			}
		}
		*/
		// break up the line into just the word
		// put the words in next_states
		// put next_states in next_state_chart
		// first == 0
		// while index is not past line
			// get second = location in line where next whitespace is
			// memcpy to word
			// store word in next_states
		//printf("%s\n", line);
	//	start = upper_bound + 1;
	//	upper_bound = getUpperBoundForLine(start, next_states_from_file, '\n');

	//}
	/*
	for(int i = 0; i < 37; i++)
		printf("%s\n", lines[i]);
	*/
	/*
	int ith_valid_line = 0;
	for(int i = 0; i < 37; i++)
	{
		printf("%i  \n", i);
		char* is_valid_line;// = isValid(lines[i]);
		if(strcmp(is_valid_line, "null") != 0 )
		{
			valid_lines[ith_valid_line] = is_valid_line;
			//printf("%s\n", valid_lines[ith_valid_line]);
			ith_valid_line++;
		}
	}*/
	// close file pointer
	// free the memory of the original string from the file

	// current bug in hierarchial context sensitive state machine design
	// same state can't have >= 2 next_states that go to the same state but have different contexts

	// maybe group the different contexts into a list the the state maps to to keep the (key,value design the same)

	/*line = collectLine(0, upper_bound, next_states_from_file);
	printf("%s\n", line);

	int upper_bound2 = getUpperBoundForLine(upper_bound + 1, next_states_from_file);

	line = collectLine(upper_bound, upper_bound2, next_states_from_file);
	printf("%s\n", line);

	int upper_bound3 = getUpperBoundForLine(upper_bound2 + 1, next_states_from_file);

	line = collectLine(upper_bound2, upper_bound3, next_states_from_file);
	printf("%s\n", line);
	*/
	exit(0);
	// get the locations of \n = A
	// use the ranges in A to memcpy each line into strip()
	// using realloc to add more blocks of chars from strip()
	// get back  empty empty empty empty...
	// replace the ' ' with '\0'
	// get the locations of all first chars = B
	// store all references to each item in B into next_states
	/*  start_0  */	//"names_0", 		 	"empty", 			"empty", 		"empty",
	/*  start_0  */	//"names_0", 		 	"empty", 			"empty", 		"empty"

	/*
	// enumerated dfa
	// table version of adjacency list (not edge column table)
	start -> line_comment, multiline_comment_start
	line_comment -> ignore line
	multiline_comment_start -> char, multiline_comment_end
	char -> char
	multiline_comment_end -> letter, '1
	letter -> letter, ' '
	'1 -> collect_char
	collect_char -> '2
	'2 -> letter
	' ' -> ' ', letter


	*/
	char* states[] = {
	// level 1
	"start_0", "names_0", "attributes_0", "EOF_0",


	// level 2
	"name_0", "tab_increase_0", "name_1", "\"children\"_0", "tab_increase_1", "next_0", "tab_reduction_0",

	// level 3
	"any_string_0", "\"children\"_1", "\"next\"_0", "\"parents\"_0", "\"functions\"_0", "function_0", "next_state_0",

	// level 4
	"child_0", "next_state_1", "parent_0", "(_0", "any_string_1", "\' \'_0", ")_0"};

	int states_len = 25;

	char label[] = "Single";
	char label2[10] = "Married";
	char **labelPtr = malloc(sizeof(char*) * 2);//[2];

	labelPtr[0] = label;
	labelPtr[1] = label2;
	printf("%s\n", labelPtr[1]);
	//exit(0);
	// static array of char* is somehow very different than an dynamic array of chars (not the dynamic part)
	char* row = malloc(sizeof(char*) * 4);
	// pointing to the 0th slot
	//printf("%s\n", next_states[4]);
	//printf("a string %s\n", next_states[0 + 4]);
	char* x = "test\0something_else\0ttt";
	//printf("%s", x+7);

	// pointer to a dynamic array
	// dynamic array = pointer to an array
	char** y = malloc(sizeof(char*) * 3);
	// x + 0 turns char[] into char*
	y[0] = x;
	// y[0] seems to store the t as t\0
	//printf("%s\n", y[0]  );
	//printf("%s\n", x);

	//exit(0);
	int j = 1;
	for(int i = 0; i < 22; i++)
	{
		printf("%c\n", x[i]/*(next_states + 0)*/);

		if (x[i] == '\0')
		{
			printf("%c\n", x[i]/*(next_states + 0)*/);

			y[j] = &x[i+1];
			j++;
			//printf("%c", x[i+3]/*(next_states + 0)*/);

			//break;
		}
		//printf("%c", x[i]/*(next_states + 0)*/);
	}
	printf("y\n");
	printf("\n%s\n", y[0]);
	//printf("\n%s\n", y[0]);

	printf("%s\n", y[1]);
	printf("%s\n", y[2]);

	//y[2] = y[0];
	char** z = malloc(sizeof(char*) * 2);
	memcpy(z, y+1, sizeof(char*) * 2);
	printf("z\n");
	printf("\n%s\n", z[0]);
	//printf("\n%s\n", y[0]);

	printf("%s\n", z[1]);

	exit(0);
	//int i = 0;
	//for(; i < states_len; i++)
	//{
		//printf("current state: %s\n", states[i]);
		//int start_position = getStartOfRowForCurrentStateCase(states[i]);
		//printf("start positions %i %i \n", start_position, 4);
		//char* location_of_first_item = &(next_states[start_position * 4]);
		//printf("%s %s\n", location_of_first_item, (&location_of_first_item) + 6);
		//printf("%s\n", next_states + 1/*(next_states + 0)*/);
		//row[0] = next_states;
		printf("%lu\n", sizeof(char*));
		//row = next_states;
		//row[1] = *next_states[1];
		//memcpy(row, next_states, sizeof(char*) * 4);//(unsigned long)&location_of_first_item + 4);
		printf("%s ", (row + 8));

		//printf("%s ", &row[1]);
		//for(int j = 0; j < 4; j++)
		//	printf("%s ", row[j]);

		printf("\n");
	//}
	return 0;
}
