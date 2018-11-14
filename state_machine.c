// this program parses a custom file of context sensitive states

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

// function to jump to the start of the ith group of 4 next states
// f(state_case) -> int

// next_states, functions, children
// (state, case)'s next states
// "", "", "", ""

 enum states{
	 start,
	 a,
	 indent_increase1,
	 Children,
	 is_indent_decrease,
	 collect_state_name,
	 pop_from_stack,
	 indent_stays_same,
	 Next,
	 is_indent_decrease1,
	 indent_increase2,
	 abcd,
	 indent_stays_same1,

	 Parent,
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
 			case Children:
 			{
 				memcpy(state_name, "Children", sizeof(char) * 9);

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
 			case Next:
 			{
 				memcpy(state_name, "Next", sizeof(char) * 5);

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
 			case is_indent_decrease1:
 			{
 				memcpy(state_name, "is_indent_decrease1", sizeof(char) * 20);

 				break;

 			}
 			case Parent:
 			{
 				memcpy(state_name, "Parent", sizeof(char) * 7);

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
		Children,
		is_indent_decrease,
		collect_state_name,
		pop_from_stack,
		indent_stays_same,
		Next,
		is_indent_decrease1,

		filler
	};
	for(int i = 0; i < 11; i++)
	{
		//printf("testing%s = %s\n", getStateString(states[i]), getStateString(current_state));

		if(current_state == states[i])
		{
			return states[i] * 3;
		}
	}
	//printf("%s\n", getStateString(current_state));
	return -1;
	/*
	switch(current_state)
	{
		case start:
			return 0;
		case a:
			return 3;
		case indent_increase1:
			return 6;
		case Children:
			return 9;
		case is_indent_decrease:
			return 12;
		case collect_state_name:
			return 15;
		case pop_from_stack:
			return 18;
		case indent_stays_same:
			return 21;
		case Next:
			return 24;
		case indent_increase2:
			return 27;
		case abcd:
			return 30;
		case indent_stays_same1:
			return 33;
		case indent_decrease1:
			return 36;
		case Parent:
			return 39;
		case indent_increase3:
			return 42;
		case abcd1:
			return 45;
		case indent_stays_same2:
			return 48;
		case indent_decrease2:
			return 51;
		case Functions:
			return 54;
		case indent_increase4:
			return 57;
		case abcd2:
			return 60;
		case indent_stays_same3:
			return 63;
		case indent_decrease3:
			return 66;
		case filler:
			return 69;
		default:
			return -1;
	}*/

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
char* functions[] = {
			// level 1

			/*  start_0  */	"names_0", 		 	"empty", 			"empty", 		"empty",
			/*  names_0*/ 	"attributes_0",  	"empty", 			"empty", 		"empty",
		/*	attributes_0 */	"names_0", 		 	"EOF", 		  		"empty", 		"empty",
			/* EOF_0 */  	"empty", 			"empty", 			"empty", 		"empty",


			// level 2
			/*  name_0*/   	"tab_increase_0", 	"empty", 			"empty", 		"empty",
		/*  tab_increase_0*/   "names_0", 		"\"children\"_0", 	"empty", 		"empty",

			/* name_1 */ 	"empty", 			"empty", 			"empty", 		"empty",
		/* "children"_0 */ 	"tab_increase_1", 	"empty", 			"empty", 		"empty",
		/* tab_increase_1 */"next_0", 			"empty", 			"empty", 		"empty",

		/* next_0 */		"next_0", 			"tab_reduction_0", 	"empty", 		"empty",
		/* tab_reduction_0 */"name_0", 			"empty", 			"empty", 		"empty",

		// level 3
		/* any_string_0 */	"empty", 			"empty", 			"empty", 		"empty",
		/* "children"_1 */	"empty", 			"empty", 			"empty", 		"empty",
		/* "next"_0 */		"empty", 			"empty", 			"empty", 		"empty",
		/* "parents"_0 */	"empty", 			"empty", 			"empty", 		"empty",
		/* "functions"_0 */	"empty", 			"empty", 			"empty", 		"empty",
		/* function */		"empty", 			"empty", 			"empty", 		"empty",
		/* next_state_0 */	"next_state_1", 	"empty", 			"empty", 		"empty",

		// level 4
		/* child */			"empty", 			"empty", 			"empty", 		"empty",
		/* next_state_1 */	"empty", 			"empty", 			"empty", 		"empty",
		/* parent_0 */		"empty", 			"empty", 			"empty", 		"empty",
		/* next_state_2 */	"empty", 			"empty", 			"empty", 		"empty",

		/* ( */				"any_string_1", 	"empty", 			"empty", 		"empty",
		/* any_string_1 */	"' '_0", 			")_0", 				"empty", 		"empty",
		/* ' ' */			"any_string_1", 	"empty", 			"empty", 		"empty",
		/* ) */				"empty", 			"empty", 			"empty", 		"empty",

			};



//char* children[] = {

//			};



//char* parents[] = {

//			};


// will need a way to store the function string name with the actual pointer in the computer so the parser can read it after it reads the function name from the file

struct Bounds {
	int low;
	int high;
};
struct Bounds** collectRanges(char* line)
{
	// collect all int ranges for each next state and return a pointer to the collection
	int i = 0;
	int low = 0;
	int high = 0;
	struct Bounds **ranges = malloc(sizeof(struct Bounds*) * 100);
	int ith_range = 0;
	while (line[i] != '\0')
	{
		if(line[i] == '\'')
		{

			i++;
			high++;

			while(line[i] == ' ')
			{
				i++;
				high++;
			}

			if(line[i] == '\'')
			{
				i++;
				high++;
			}

			while(line[i] != ' ')
			{
				i++;
				high++;
			}
			high--;
		}
		else
		{
			while(line[i] != ' ')
			{

				i++;
				high++;
			}
			high--;

		}
		// 1 full word has been visited

		//printf("%i\n", i);
		struct Bounds *range = malloc(sizeof(struct Bounds));
		range->low = low;
		range->high = high;
		ranges[ith_range] = range;
		while(line[i] == ' ')
			i++;
		low = i;
		high = i;
		ith_range++;
	}

	return ranges;
}
int getNextI(char* line, int i)
{
	int start;
	for(start = i; line[start] != '\n'; start++);

	// + 1 so i is 1 after '\n'
	return start;// + 1;
}
char* getNextStates(char* line)
{
	// gets rid of any character not having to do with next states
	//printf("%s  %lu\n", line, strlen(line));
	int length = strlen(line);

	char* valid = malloc(sizeof(char) * length);
	int ith_valid = 0;
	int i;
	for(i = 0; i < length;)
	{

		char* first_2_chars = malloc(sizeof(char) * 2);
		memcpy(first_2_chars, line + i, sizeof(char) * 2);
		if(strcmp(first_2_chars, "//") == 0)
		{
			i = getNextI(line, i);
		}
		else if(strcmp(first_2_chars, "/*") == 0)
		{
			for(i = i + 2; line[i] != '*'; i++);
			// take i 1 char past "*/"
			i += 2;
			while(line[i] == ' ')
				i++;

			while(line[i] != '\n')
			{
				valid[ith_valid] = line[i];
				i++;
				ith_valid++;
			}
			// token before the newline must have a space between it and the token after the newline
			valid[ith_valid] = ' ';
			ith_valid++;
		}
		free(first_2_chars);
		i++;
	}
	//valid[ith_valid] = ' ';
	//ith_valid++;
	// assumes the last newline has already been replaced with ' ' so split process doesn't have to look for a '\0' as a final delimiter
	valid[ith_valid] = '\0';
	//printf("%s\n", valid);
	int size = sizeof(char) * ith_valid;
	char* next_states = malloc(size);
	memcpy(next_states, valid, size);

	//printf("%s\n", next_states);
	//printf("failed\n");
	free(valid);
	// now we have the next states

	return next_states;
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
char** getContextDimensions(struct StackNode* tracker, int number_of_dimensions)
{

	 // adjuct for indent
	struct StackNode* stack_tracker = malloc(sizeof(struct StackNode));
	memcpy(stack_tracker, tracker, sizeof(struct StackNode));
	//printf("\n");

	//printStack(stack_tracker);
	//printf("\n");
	//printf("%i\n", number_of_dimensions);


	char** state_names = malloc(sizeof(char*) * number_of_dimensions);
	int i = 0;
	// have to skip over the (null) and the Children
	stack_tracker = stack_tracker->prev;
	//printStack(stack_tracker);
	//printf("start loop\n");
	if (number_of_dimensions > 0)
	{
		while(stack_tracker->word != NULL)
		{
			//printf("got into the get\n");

			//printf("*%s* ", stack_tracker->word);
			//printf("\n");
			//if(stack_tracker->word == NULL)
			//	break;

			state_names[i] = malloc(sizeof(char) * strlen(stack_tracker->word));
			memcpy(state_names[i], stack_tracker->word, sizeof(char) * strlen(stack_tracker->word));
			stack_tracker = stack_tracker->prev;
			//printf("%i\n\n", stack_tracker->word);
			//if(stack_tracker->prev == NULL)
			//	break;
			//printf("%i\n", strcmp(stack_tracker->prev->word, "Children"));
			i++;

		}
		//printf("\n");
		//exit(1);
		//char* null_char = malloc(sizeof(char));
		//null_char[0] = '\0';
		//state_names[number_of_dimensions] = null_char;
		return state_names;
	}
	return NULL;
}
void statesCollectContextDimensions(char* line, int count_1, int count_2, int* i_ptr, int* loop_count_ptr, struct StackNode* tracker, int next_location_of_newline, int* dimension_count_ptr)
{

	 printf("inside dimension collector\n");
	 printStack(tracker);
	 printf("\n");
	 exit(1);
	 // collect the dimensions
	 int number_of_dimensions = *dimension_count_ptr;
	 printf("%i state name length\n", number_of_dimensions);
	 //exit(0);
	 char** state_dimensions =  getContextDimensions(tracker, number_of_dimensions);
	 for(int i = 0; i < number_of_dimensions; i++)
	 {
		 printf("%s ", state_dimensions[i]);
	 }
	 //exit(1);
	//malloc(sizeof(char*) * number_of_dimensions);
	 // traverse the stack number_of_dimensions times and add the pointers to state_dimensions([pointer, pointer, *''\0'])
	// a b c d | another indent a | (Children | Parents | Next | Functions)(no data to collect and no subtree)
	count_1 = count_2;
	*i_ptr = next_location_of_newline;

	count_2 = countGapSize(line, *i_ptr);
	printf("\n%i %i %i\n", count_1, count_2, count_2 - count_1);

	if((count_2 - count_1) == 0)
	{
		// we are at the same deepest level
		// |Next| |Children| base case where children has no data to collect
		printf("level\n");
	}
	if((count_2 - count_1) < 0)
	{
		// we are at the deepest level before it rises
		// if the stack says |Next| |Children| then base case where children has no data
		printf("backwards\n");
	}
	if(count_2 - count_1 > 0)
	{
		printf("\nthe next level has started or we have a string with spaces\n");
		// could be the start of another level
			// call collectContextDimensions and reset dimension_count_ptr
		// could be a next state to collect as a value for of our Children key
		// base case where there is data for the key to collect
	}
	//printf("last indent : %i current indent %i\n\n", count_1, count_2);
	*i_ptr += count_2 + 1;
	next_location_of_newline = getEndIndexOfWord(line, *i_ptr);
	//printf("loop_count: %i i: %i next_location_of_newline: %i\n", loop_count, i, next_location_of_newline);
	// put on github under the general_State_machine_program-c version
	// test the variable dimentional machine
	// add the calculator program to the end of the testing
	char* word = makeWord(next_location_of_newline, line, *i_ptr);

	// add word to stack
	// needs +1
	int size = next_location_of_newline - *i_ptr + 1;

	struct StackNode* next_word = malloc(sizeof(struct StackNode));
	next_word->word = malloc(sizeof(char) * size);
	memcpy(next_word->word, word, sizeof(char) * size);
	next_word->prev = tracker->prev;

	tracker->prev = next_word;
	printf("\n");

	printStack(tracker);
	printf("\n");

	//exit(1);
	// print out stack
	//printStack(tracker);
	//printf("\n");
	/*
	a, \n, same number of tab count as count_1

	or
	a, \n, > number of tab count as count_1
		pass hash table in
		make the entry for the current context dimension
		return the current context dimension to the caller(the entry represents the tree)
		the children is supposed to connect to the node below not a nested hash table
	or

	Children | Parents | Next | Functions, \n, some number of tabls,

	*/
}
bool wordIsChildren(char* word)
{
	if(strcmp(word, "Children") == 0)
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
 int stateStackSize(struct State* state_tracker)
 {
	struct State* stack_tracker = malloc(sizeof(struct State));
 	memcpy(stack_tracker, state_tracker, sizeof(struct State));
 	stack_tracker->indent = state_tracker->indent;

 	//printf("%i\n", state_tracker->indent);
 	//printf("%i\n", state_tracker->prev->indent);
	int i = 1;
 	while(stack_tracker != NULL)
 	{
 		//printf("|%i| ", stack_tracker->indent);
 		stack_tracker = stack_tracker->prev;
		i++;
 	}
	return i;
 }
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
 void postorder(struct State* state_tracker)
 {
	if(state_tracker->indent == 0)
	{

		printf("first state\n|%i|\n", state_tracker->indent);

		return;
	}
	printf("data from state\n");
	printf("|%i|\n", state_tracker->indent);


	// print out data in stat_tracker
	for(int i = 0; i < state_tracker->name_size; i++)
	{
		printf("|%s|\n", state_tracker->name[i]);
	}
	printf("done printing data from state\n");
	for(int i = 0; i < state_tracker->children_size; i++)
	{
		postorder(state_tracker->children[i]);
	}
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

	while(stack_tracker != NULL)
	{
		// postorder traversal of stack_tracker subtree
		// need indents too
		postorder(stack_tracker);
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
int next_states_list[] = {
	// if there is at least 1 item of a category, next, parents, functions, children, then the category name will be present
	// else there will be no category name
	/*  start			   	*/		a, 					filler, 				filler,
	/*  a				   	*/		indent_increase1, 	filler, 				filler,
	/*  indent_increase1   	*/		a, 					Children, 				is_indent_decrease/* does next indent decrease*/,

									/* >= 1 child*/
	/*  Children		   	*/		indent_increase1, 	filler, 				filler,
	/*  is_indent_decrease 	*/		collect_state_name, filler, 				filler,
	/*  collect_state_name 	*/		pop_from_stack, 	filler, 				filler,
	/*  pop_from_stack	   	*/		is_indent_decrease1, indent_stays_same, 	filler,
	/*  indent_stays_same  	*/		Next, 				a, 						filler,
	/*  Next				*/ 		filler, 			filler, 				filler,
	// same edges as is_indent_decrease but will be running slightly different code(will check the word stack agains the state stack the same way its earlier enumerated state did with count_1 and count_2)
	/*  is_indent_decrease1	*/ 		collect_state_name, filler, 				filler, // add support for is_indent_decrease1
};

bool isEmpty(int* next_states)
{
	return next_states[0] == filler &&
			next_states[1] == filler &&
			next_states[2] == filler;
}
// count_temp includes newline

#define incrementCountAndGetWord \
	count_temp = countGapSize(line, i);\
	indent_string = makeIndents(count_temp);\
	\
	\
	peek_size = peekAtNode(line, i, count_temp);\
	next_word->word = getValue(line, i + (count_temp), peek_size);

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
void visitNodes()
{
	// https://github.com/protobuf-c/protobuf-c
	// need dummy\n for parser to work
	// count_temp is setting count_2 to the size from findGapSize of the previous string found(is equal to the number of tabs before the current word)
	char* line = "dummy\n\tstring_1\n\t\tstring_2\n\t\t\tstring_3\n\t\t\t\tChildren\n\t\t\t\t\tstring_4\n\t\t\t\t\t\tstring_5\n\t\t\t\t\t\t\tstring_6\n\t\t\t\tNext\n\t\t\t\t\tstring_1 string_2 string_3\n\t\t\t\t\tstring_1_1 string_2_1 string_3_1\n\t\t\t\t\tstring_1_2 string_2_2 string_3_2\n\t\t\t\t\tstring_1_3 string_2_3 string_3_3\n\t\t\t\tParents\n\t\t\t\t\tnull\n\t\t\t\tFunctions\n\t\t\t\t\tstring_7\n\t\t\t\t\tstring_8";
	int size = strlen(line);
	int i = 0;


	//int* i_ptr = &i;
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



	struct StackNode* tracker = malloc(sizeof(struct StackNode));
	tracker->word = NULL;
	tracker->indent = 0;
	tracker->prev = root;

	struct State* state_tracker = malloc(sizeof(struct State));
	state_tracker->name = NULL;
	state_tracker->indent = 0;
	state_tracker->next = NULL;
	state_tracker->prev = state_root;

	int dimension_count = 0;
	int* dimension_count_ptr = &dimension_count;


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
	int next_location_of_newline = 0;

	int* next_location_of_newline_ptr = &next_location_of_newline;
	//int* count_1_ptr = &count_1;
	//int* count_2_ptr = &count_2;
	int winning_state = start;
	char* word;
	char* indent_string;
	int count_temp;
	int peek_size;
	printf("start state %s\n", getStateString(winning_state));

	while(!isEmpty(next_states))
	{
		if(count == 26)
		{
			exit(1);
		}
		// check for out of bounds or null
		// print state
		bool state_changed = false;//malloc(sizeof(bool) * max_next_states);
		//memset(state_changed, false, sizeof(bool));
		for(int k = 0; k < max_next_states; k++)
		{
			// prent next state being tried
			//printf("trying %s\n", getStateString(next_states[k]));
			switch(next_states[k])
			{
				// cases


				case start:
				{

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

					//free(next_word);
					//free(next_word->word);

					state_changed = true;

					break;
				}
				case a:
				{

					// a (first round the a that came before a doesn't exist)
					// countGapSize
						// get the number of indents from i to start of next word = count_2
					// get to node
						// moves i to first char of word i += indent_count + 1
					// peek node
						// moves temp_i to first char of word temp_i = i + indent_count + 1

					count_temp = countGapSize(line, i);

					indent_string = makeIndents(count_temp);

					peek_size = peekAtNode(line, i, count_temp);
					char* word = getValue(line, i + (count_temp), peek_size);
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
						next_word->prev = tracker->prev;

						tracker->prev = next_word;
						//free(word);
						printStack(tracker);
						printf("\n");
						printStateStack(state_tracker);
					    printf("\n");
						//incrementCount

						state_changed = true;
					}
					else
					{
						free(word);
						//free(next_word);
						//free(next_word->word);
					}






					break;

				}
				case indent_increase1:
				{



						//incrementCount
						printf("before %i %i\n", count_1, count_2);

						i += count_temp + peek_size;
						count_1 = count_2;
						count_2 = count_temp;
						printf("after %i %i\n", count_1, count_2);
						if(count_2 > count_1)
						{
							state_changed = true;

						}
						//printf("%i, %i\n", count_1, count_2);





					break;

				}
				case Children:
				{

					//indent_string = makeIndents(*count_2_ptr);



					// haven't proven it is not a child


					count_temp = countGapSize(line, i);
					indent_string = makeIndents(count_temp);


					peek_size = peekAtNode(line, i, count_temp);
					char* word = getValue(line, i + (count_temp), peek_size);

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
						next_state->children = malloc(sizeof(struct State*));
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



						state_changed = true;
					}
					else
					{
						free(word);
						//free(next_word->word);
					}

					break;

				}
				case is_indent_decrease:
				{
					// is the next indent change an indent decrease
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
						next_word->word = getValue(line, i + (count_temp), peek_size);
						//printf("%c %s\n", line[(*i_ptr)+6], word);
						//indent_string = makeIndents(c_2);

						if(wordIsCategory(next_word->word))
						{
							printf("%s%s\n", indent_string, next_word->word);
							printStack(tracker);
							printf("\n");
							printStateStack(state_tracker);
						    printf("\n");
							// have to travel up the word stack untill hit a category name(children) or a null sized string
							// otherwize this version only works for 1 nested states(n level nesting will not work)
							int name_size = tracker->prev->indent - state_tracker->prev->indent;
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
						state_changed = true;
					}



					break;

				}
				case collect_state_name:
				{
					// visit strings in stack untill their indent == indent of top state object
					// save the strings into the top state object as the state name
					// set second to top state's child to the top state in stack
					// pop top state off stack by deleting its prev link
					// for each node in stack
						// print out the node and its subtree


					// visit strings in stack untill their indent == indent of top state object
					// save the strings into the top state object as the state name
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


					state_changed = true;


					break;

				}
				case pop_from_stack:
				{

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
					state_changed = true;


					break;

				}
				case is_indent_decrease1:
				{

					int top_of_state_stack = state_tracker->prev->indent;
					int top_of_word_stack = tracker->prev->indent;
					printf("before %i %i\n", top_of_state_stack, top_of_word_stack);

					//(*i_ptr) += (count_temp) + peek_size;
					//int c_1 = count_2;
					// -1 because count_temp counts newline
					//int c_2 = count_temp-1;

					//printf("after %i %i\n", c_1, c_2);
					if(top_of_state_stack < top_of_word_stack)
					{
							printf("%i still needs to decrease\n", top_of_word_stack);
							state_changed = true;
					}




					break;

				}
				case indent_stays_same:
				{

					state_changed = true;


					break;

				}
				case Next:
				{
					count_temp = countGapSize(line, i);
					indent_string = makeIndents(count_temp);


					peek_size = peekAtNode(line, i, count_temp);
					char* word = getValue(line, i + (count_temp), peek_size);
					// -1 because count_temp takes newline into account
					printf("word next? %s %i\n", word, count_temp - 1);

					// are done with all states having an indent >= next(below next in the tree)
					// have top state be the first child of the second from top state(do for all states having a >= indent value than next)
					state_changed = true;


					break;

				}
				case indent_increase2:
				{

					state_changed = true;


					break;

				}
				case abcd:
				{

					state_changed = true;


					break;

				}
				case indent_stays_same1:
				{

					state_changed = true;


					break;

				}

				case Parent:
				{

					state_changed = true;

					break;

				}
				case indent_increase3:
				{

					state_changed = true;


					break;

				}
				case abcd1:
				{

					state_changed = true;


					break;

				}
				case indent_stays_same2:
				{

					state_changed = true;


					break;

				}
				case indent_decrease2:
				{

					state_changed = true;


					break;

				}
				case Functions:
				{

					state_changed = true;


					break;

				}
				case indent_increase4:
				{

					state_changed = true;


					break;

				}
				case abcd2:
				{

					state_changed = true;


					break;

				}
				case indent_stays_same3:
				{

					state_changed = true;


					break;

				}
				case indent_decrease3:
				{

					state_changed = true;


					break;

				}
				case filler:
				{

					//state_changed = true;


					break;

				}
				default:
				{

					state_changed = false;

					break;
				}


			}

			if(state_changed)
			{
				winning_state = next_states[k];
				printf("winning state %s\n", getStateString(winning_state));

				break;
			}
/*
each number is a base sequence
*/

		//printf("i = %i\n", i);

		}
		printf("------------\n");


		if(state_changed)
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
void Input(char* line,
		   int count_1,
		   int count_2,
		   int* i_ptr,
		   int* loop_count_ptr,
		   struct StackNode* tracker,
		   int* dimension_count_ptr,
	       struct State* state_tracker)
 {
	 // this function collects the context dimensions
	 //Input -> (1st newline) (a|CNPF) newline tab_increase loop
	 // misreading the pattern
	 printStateStack(state_tracker);
	 printf("\n");
	 while(line[*i_ptr] != '\0')
 	{
		printf("%i %i\n", count_1, count_2);
 		//printf("%i\n", loop_count);
 		if (*loop_count_ptr == 20)
 		{
 			printf("end of line\n");
 			exit(1);
 		}
 		if(count_1 < count_2)
 		{
 			//printf("going down\n");

 			// collect the state names

 		}
		printf("\n");

		printStack(tracker);
		printf("\n");
		printStateStack(state_tracker);
		printf("\n");
		// null case
		if (count_1 > count_2)
		{
			printf("%i changes here\n", count_2);
			// at a null node if there is no data between top of stack and a category name
			struct StackNode* stack_tracker = malloc(sizeof(struct StackNode));
			memcpy(stack_tracker, tracker->prev, sizeof(struct StackNode));
			//stack_tracker->indent = tracker->prev->indent;

			if (
				(strcmp(stack_tracker->word, "Children")  == 0) ||
				(strcmp(stack_tracker->word, "Next")      == 0) ||
				(strcmp(stack_tracker->word, "Parents")   == 0) ||
				(strcmp(stack_tracker->word, "Functions") == 0)
			)
			{
				//printf("no data to collect except for name\n");
				printf("the node here at %i is a null node\n", count_1);

				// pop off null state from stack
				// delete the node being freed.

				// assumes there are at least 3 values in both stacks
				struct StackNode* delete_node = tracker->prev;
				tracker->prev = tracker->prev->prev;
				free(delete_node);


				struct State* delete_state_node = state_tracker->prev;
				state_tracker->prev = state_tracker->prev->prev;
				free(delete_state_node);
				//printStateStack(state_tracker);
				//printf("\n");
				//printf("%i\n", state_tracker->indent);



			}
			char** collected_words = malloc(sizeof(char*));
			int number_of_words = 0;

			while(  (strcmp(stack_tracker->word, "Children")  != 0) &&
					(strcmp(stack_tracker->word, "Next")      != 0) &&
					(strcmp(stack_tracker->word, "Parents")   != 0) &&
					(strcmp(stack_tracker->word, "Functions") != 0)
				)
			{
				// need +1 for this to work
				collected_words[number_of_words] = malloc(sizeof(char) * (strlen(stack_tracker->word) +1));
				memcpy(collected_words[number_of_words], stack_tracker->word, sizeof(char) * (strlen(stack_tracker->word)+1));
				number_of_words++;
				collected_words = realloc(collected_words, sizeof(char*) * (number_of_words + 1));

				//printf("collecting data %s \n", stack_tracker->word);
				stack_tracker = stack_tracker->prev;
				if( wordIsCategory(stack_tracker->word))
				{
					printf("name of category is %s\n", stack_tracker->word);
					/*for(int k = 0; k < number_of_words; k++)
					{
						printf("|%s|\n", collected_words[k]);
					}*/
					if(strcmp(stack_tracker->word, "Next")  == 0)
					{
						//printf("in right place\n");
						state_tracker->prev->next = malloc(sizeof(char*) * number_of_words);
						memcpy(state_tracker->prev->next, collected_words, sizeof(char*) * number_of_words);
						//printf("%i\n", state_tracker->prev->indent);
						/*for(int k = 0; k < number_of_words; k++)
						{
							printf("|%s|\n", state_tracker->prev->next[k]);
						}*/
						//printStateStack(state_tracker);
						//printf("\n");

					}
					//printf("\n");
				}
			}

			// travel up the stack until the stack item->indent = count_2
			//printStack(tracker);
			//printf("\n");
			//printPartStack(tracker, count_2);
			//printf("")
		}
		//printf("got here");
		// a
		int next_location_of_newline = getEndIndexOfWord(line, *i_ptr);

		//printf("%i %i\n", *i_ptr, next_location_of_newline);
 		// get next node
 		//printf("loop_count: %i i: %i next_location_of_newline: %i\n", loop_count, i, next_location_of_newline);
 		// put on github under the general_State_machine_program-c version
 		// test the variable dimentional machine
 		// add the calculator program to the end of the testing
 		char* word = makeWord(next_location_of_newline, line, *i_ptr);
		// what is word?
		if(!wordIsCategory(word))
		{


			//printf("process state name\n");
		}
		else
		{
			//printf("%i\n", state_tracker->indent);
			// not sure why > 2 instead of > 1
			printf("does the state for indent level %i already exist? %i\n", count_2, state_tracker->prev->indent == count_2);
			printf("collect data for %i, %i is a marker place\n", state_tracker->prev->indent, count_2);
			printf("attribute for state %i %s\n", count_2, word);
			// move forwards to a spot
			// collect backwards
			// state_tracker->prev is actually the first state on the stack
			if(state_tracker->prev->indent != count_2)
			{
				struct State* next_state = malloc(sizeof(struct State));
				next_state->indent = count_2;
				next_state->prev = state_tracker->prev;
				next_state->children = malloc(sizeof(struct State*));
				next_state->next = NULL;//malloc(sizeof(char*));
				next_state->parents = malloc(sizeof(char*));
				next_state->functions = malloc(sizeof(char*));

				state_tracker->prev = next_state;
			}
			else
			{
				if (!(count_1 > count_2))
				{
					printf("need to back add partial data for indent level %i at %s when next breakpoint is hit\n", count_2, word);

				}

			}
			//printf("%i\n", next_state->indent);
			//printf("\n");

			//printf("\n");
		}

 		// add word to stack
 		// needs +1
 		int size = next_location_of_newline - *i_ptr + 1;

 		struct StackNode* next_word = malloc(sizeof(struct StackNode));
 		next_word->word = malloc(sizeof(char) * size);
 		memcpy(next_word->word, word, sizeof(char) * size);
		next_word->indent = count_2;
		//printf("%i %i\n", next_word->indent, count_2);
		free(word);
 		next_word->prev = tracker->prev;

 		tracker->prev = next_word;


 		// print out stack
 		//printStack(tracker);
 		//printf("\n");
 		// inorder recursion and have each recursive call return the last level down to the bottom level of teh children, next, parents, functions part
 		//printf("indent string2 %s\n", indent_string);
 		// needs to be here or the linked list code interfers with it
 		char* indent_string = makeIndents(count_2);
 		//printf("indent string1 %s\n", indent_string);

 		// process the word
 		printf("%s %s\n\n", indent_string, tracker->prev->word );
		free(indent_string);
 		//printf("%s\n", tracker->prev->word );
		// CNPF

		// newline tab increase
		next_location_of_newline = getEndIndexOfWord(line, *i_ptr);

 		// setup the indents for the next child or sibling
		(*loop_count_ptr)++;

 		count_1 = count_2;
 		*i_ptr = next_location_of_newline;

		// go from \t to next letter
 		count_2 = countGapSize(line, *i_ptr);
		if(count_2 == -1)
		{
			printf("run out of line\n");
			exit(1);

		}
 		//printf("last indent : %i current indent %i\n\n", count_1, count_2);
 		*i_ptr += count_2 + 1;
	}

 }
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
	readLine(state_graph);
	return 0;
	// function that can parse the 3 lines below and give me 	char x[] = "test something_else";
	bool (*function_table[]) (void) = {fun0, fun1, fun2};
	printf("%d\n", function_table[0]());
	printf("%d\n", function_table[1]());
	printf("%d\n", function_table[2]());

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
	char* next_states = getNextStates(next_states_from_file);
	//for(int i = 0; next_states[i] != '\0'; i++)
	//	printf("%i |%c|\n", i, next_states[i]);
	//exit(0);
	//printf("%s\n", next_states);
	//exit(0);

	struct Bounds **ranges = collectRanges(next_states);
	//for(int i = 0; i < 100; i++)
	//	printf("%i, %i\n", ranges[i]->low, ranges[i]->high);

	char** next_state_chart = malloc(sizeof(char*) * 100);

	for(int i = 0; i < 100; i++)
	{
		int size = ranges[i]->high - ranges[i]->low;
		next_state_chart[i] = malloc(sizeof(char) * size);
		// not sure why +1 is needed here
		memcpy(next_state_chart[i], next_states + ranges[i]->low, sizeof(char) * (size + 1));

	}
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