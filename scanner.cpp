#include "scanner.h"

/*

these are the levels at which the input is scanned from lowest level to top level

persistent is the set of variables who don't change on each level


1 line:
	we are only scanning 1 line
	persistent:
		# tabs, word
		the word is the text sequence on each line comming after the tabs
2 lines
	we are processing 2 lines at a time
	persistent:
		2 words, 3 nodes
		first round 2 lines are linked using parent and child nodes and a temp node
		then second line becomes the first and the next second line is scanned
		this chain scans in all the lines


entire file
	we are running a 2 lines process for the entire file
	persistent:
		1 tree, 2 dummy nodes above root

*/
enum make_tree_state_names{


	empty,
	root,
	start, 	// this state is not actually run
	//two_lines,
	one_line_one_1,
	one_line_one_2,
	one_line_two_1,
	one_line_two_2,
	//end_of_2_lines,

	setup_first_2_nodes,
	make_node_for_word_2,
	down_link,
	up_link,
	across_link,
	_cleanup,

	one_line,
	out_of_lines,
	blank_line,
	non_blank_line,
	end_of_start
};



int countLines(string input);
MultiwayLinesNode* initMultiwayLinesNode();
bool deleteMultiwayLinesNode(MultiwayLinesNode* node);
MultiwayLinesNode* getMultiwayLinesNode(void* raw_node);



OneLine* initOneLine()
{
	OneLine* one_line = (OneLine*) malloc(sizeof(OneLine));
	one_line->number_of_tabs = 0;
	one_line->word = "";
	return one_line;
}

bool deleteOneLine(OneLine* one_line)
{

	return true;
}








TwoLines* initTwoLines()
{
	TwoLines* two_lines = (TwoLines*) malloc(sizeof(TwoLines));


	two_lines->first_line = initOneLine();
	two_lines->second_line = initOneLine();
	two_lines->temp_word = "";

	two_lines->temp_number_of_tabs = 0;
	two_lines->parent = initMultiwayLinesNode();
	two_lines->child = initMultiwayLinesNode();

	return two_lines;

}
bool deleteTwoLines(TwoLines* two_lines)
{
	deleteOneLine(two_lines->first_line);
	deleteOneLine(two_lines->second_line);


	deleteMultiwayLinesNode(two_lines->parent);
	deleteMultiwayLinesNode(two_lines->child);
	free(two_lines);
	two_lines = NULL;
	return true;
}









// init
Scanner* initScanner(string input)
{
	if(input.size() > 0)
	{
		Scanner* my_scanner = (Scanner*) malloc(sizeof(Scanner));

		my_scanner->i = 0;
		my_scanner->num_lines = countLines(input);
		my_scanner->count = 0;
		my_scanner->input = input;


		my_scanner->first_line = "";
		my_scanner->second_line = "";
		my_scanner->first_two_lines = true;
		my_scanner->done_reading_data = false;

		my_scanner->lines_graph = initMultiwayLinesNode();

		my_scanner->child = initMultiwayLinesNode();
		return my_scanner;

	}
	return NULL;
}

// delete
bool deleteScanner(Scanner* my_scanner)
{
	if(my_scanner != NULL)
	{
		deleteMultiwayLinesNode(my_scanner->lines_graph);
		deleteMultiwayLinesNode(my_scanner->child);

		free(my_scanner);
		my_scanner = NULL;
		return 1;
	}
	return 1;
}
// utility functions from main
string makeSpaces(int indent_level);
string getNextWord(string input, int i);
bool whiteSpace(char character);
int countTabs(string input, int i);
void swap(int* a, int* b);



// functions for makeTreeStateMachine
int computeIndexForMakeTree(int offset, int state_name)
{

	// 8 is the child count(4) + neighbor count(4)
	return offset + (8 * state_name);
}
void setNeighbors(int* next_states, int state, int child_0, int child_1, 	int child_2, 	int child_3,
											   int next_0, 	int next_1, 	int next_2, 	int next_3)
{
		// children
		next_states[computeIndexForMakeTree(0, state)] 					= child_0;
		next_states[computeIndexForMakeTree(1, state)] 					= child_1;
		next_states[computeIndexForMakeTree(2, state)] 					= child_2;
		next_states[computeIndexForMakeTree(3, state)] 					= child_3;

		// nexts
		next_states[computeIndexForMakeTree(4, state)] 					= next_0;
		next_states[computeIndexForMakeTree(5, state)] 					= next_1;
		next_states[computeIndexForMakeTree(6, state)] 					= next_2;
		next_states[computeIndexForMakeTree(7, state)] 					= next_3;

}

StateMachine* setupMachineForMakeTree()
{
		// similar to a contextual state chart(no children, only nexts)
		// each state name is a contextual state
		// the state chart is the groups of states per level
		int number_of_states = 21;
		int neighbor_count = 4;
		int children_count = 4;
		int number_of_next_states = number_of_states * (children_count + neighbor_count);

		vector<string>* make_tree_state_names_strings = new vector<string>(number_of_states);

		vector<string>* function_names = new vector<string>(number_of_states);

		function_names->resize(number_of_states);
		int* parent_status = (int*) malloc(sizeof(int) * number_of_states);
		parent_status[empty]										= false;
		parent_status[root]											= true;
		parent_status[start]										= true;
		//parent_status[two_lines]									= true;
		parent_status[one_line_one_1]								= true;
		parent_status[one_line_one_2]								= false;
		parent_status[one_line_two_1]								= true;
		parent_status[one_line_two_2]								= false;
		//parent_status[end_of_2_lines]								= false;

		parent_status[setup_first_2_nodes]  						= false;
		parent_status[make_node_for_word_2] 						= false;
		parent_status[down_link] 									= false;
		parent_status[up_link]										= false;
		parent_status[across_link]									= false;
		parent_status[_cleanup]										= false;


		parent_status[one_line]										= true;
		parent_status[out_of_lines]									= false;
		parent_status[blank_line]									= false;
		parent_status[non_blank_line]								= false;
		parent_status[end_of_start]									= false;


		make_tree_state_names_strings->at(empty) 					= "empty";
		make_tree_state_names_strings->at(root)						= "root";
		make_tree_state_names_strings->at(start) 					= "start";


		//make_tree_state_names_strings->at(two_lines)				= "two_lines";
		make_tree_state_names_strings->at(one_line_one_1)			= "one_line_one_1";
		make_tree_state_names_strings->at(one_line_one_2)			= "one_line_one_2";
		make_tree_state_names_strings->at(one_line_two_1)			= "one_line_two_1";
		make_tree_state_names_strings->at(one_line_two_2)			= "one_line_two_2";
		//make_tree_state_names_strings->at(end_of_2_lines)			= "end_of_2_lines";

		make_tree_state_names_strings->at(setup_first_2_nodes) 		= "setup_first_2_nodes";
		make_tree_state_names_strings->at(make_node_for_word_2) 	= "make_node_for_word_2";
		make_tree_state_names_strings->at(down_link)				= "down_link";
		make_tree_state_names_strings->at(up_link)					= "up_link";
		make_tree_state_names_strings->at(across_link)				= "across_link";
		make_tree_state_names_strings->at(_cleanup)					= "_cleanup";

		make_tree_state_names_strings->at(one_line)					= "one_line";
		make_tree_state_names_strings->at(out_of_lines)				= "out_of_lines";
		make_tree_state_names_strings->at(blank_line)				= "blank_line";
		make_tree_state_names_strings->at(non_blank_line)			= "non_blank_line";
		make_tree_state_names_strings->at(end_of_start)				= "end_of_start";




		function_names->at(empty) 									= "true";
		function_names->at(root)									= "true";
		function_names->at(start) 									= "true";


		//function_names->at(two_lines)								= "true";
		function_names->at(one_line_one_1)							= "oneLineOneOne";
		function_names->at(one_line_one_2)							= "oneLineOneTwo";
		function_names->at(one_line_two_1)							= "true";
		function_names->at(one_line_two_2)							= "oneLineTwoTwo";
		//function_names->at(end_of_2_lines)						= "true";

		function_names->at(setup_first_2_nodes) 					= "setupFirstTwoNodes";
		function_names->at(make_node_for_word_2) 					= "makeNodeForWordTwo";
		function_names->at(down_link)								= "downLink";
		function_names->at(up_link)									= "upLink";
		function_names->at(across_link)								= "acrossLink";
		function_names->at(_cleanup)								= "cleanupTrackers";

		function_names->at(one_line)								= "true";
		function_names->at(out_of_lines)							= "outOfLines";
		function_names->at(blank_line)								= "blankLine1";
		function_names->at(non_blank_line)							= "nonBlankLine";
		function_names->at(end_of_start)							= "endOfStart";

		

		int* make_tree_next_states = (int*) malloc(sizeof(int) * number_of_next_states);

		// may take this out
		// empty field
		setNeighbors(make_tree_next_states, empty, 				empty, 			 	empty, 					empty, 			empty,
																empty, 			 	empty, 					empty, 			empty);

		setNeighbors(make_tree_next_states, root, 				start, 				 empty, 				empty, 			empty,
																empty, 				 empty, 				empty, 			empty);
		// level 1
		// start
		setNeighbors(make_tree_next_states, start, 				one_line_one_1, 	 empty, 				empty, 			empty,
																end_of_start, 		 empty, 				empty, 			empty);
		// level 2
		// two_lines
		//setNeighbors(make_tree_next_states, two_lines, 		one_line_one_1, 	 empty, 				empty, 			empty,
		//														end_of_start, 		 empty, 				empty, 			empty);

		/*
		tab change, 2 words, 2 nodes, 
		*/

		// level 3
		// one_line_one_1
		setNeighbors(make_tree_next_states, one_line_one_1, 	one_line, 			 empty, 				empty, 			empty,
																one_line_one_2, 	 empty, 				empty, 			empty);
		// one_line_one_2
		setNeighbors(make_tree_next_states, one_line_one_2, 	empty, 				 empty, 				empty, 			empty,
																one_line_two_1, 	 empty, 				empty, 			empty);
		// one_line_two_1
		setNeighbors(make_tree_next_states, one_line_two_1, 	one_line, 			 empty, 				empty, 			empty,
																end_of_start, 		 one_line_two_2, 		empty, 			empty);
		// one_line_two_2
		setNeighbors(make_tree_next_states, one_line_two_2, 	empty, 				 empty, 				empty, 			empty,
																setup_first_2_nodes, make_node_for_word_2, 	empty, 			empty);
		// end_of_2_lines
		//setNeighbors(make_tree_next_states, end_of_2_lines, 	empty, 				 empty, 				empty, 			empty,
		//														empty, 				 empty, 				empty, 			empty);

		///////
		// if setup_first_2_nodes is false program needs to halt
		// new states
		// setup_first_2_nodes
		setNeighbors(make_tree_next_states, setup_first_2_nodes, empty, 			 empty, 				empty, 			empty,
																 one_line_two_1,	 empty, 				empty, 			empty);

		// make_node_for_word_2
		setNeighbors(make_tree_next_states, make_node_for_word_2,empty, 			 empty, 				empty, 			empty,
																 down_link, 		 up_link, 				across_link,	empty);

		// down_link
		setNeighbors(make_tree_next_states, down_link, 			empty, 				 empty, 				empty, 			empty,
																_cleanup, 			 empty, 				empty, 			empty);
		// up_link
		setNeighbors(make_tree_next_states, up_link, 			empty, 				 empty, 				empty, 			empty,
																_cleanup, 			 empty, 				empty, 			empty);
		// across_link
		setNeighbors(make_tree_next_states, across_link, 		empty, 				 empty, 				empty, 			empty,
																_cleanup, 			 empty, 				empty, 			empty);

		// _cleanup
		setNeighbors(make_tree_next_states, _cleanup, 			empty, 				 empty, 				empty, 			empty,
																 one_line_two_1,	 empty, 				empty, 			empty);
		////
		// currently 2 methods to ending machine
			// trick with 2 states after all lines have been read in
			// input index out of bounds
		// level 4
		// one_line
		setNeighbors(make_tree_next_states, one_line, 			out_of_lines, 		 blank_line, 			non_blank_line, empty,
																empty,				 empty, 		 		empty,  		empty);
		// out_of_lines
		setNeighbors(make_tree_next_states, out_of_lines, 		empty, 				 empty, 				empty, 			empty,
																empty, 				 empty, 				empty, 			empty);
		// blank_line
		setNeighbors(make_tree_next_states, blank_line, 		empty, 				 empty, 				empty, 			empty,
																out_of_lines, 		 blank_line, 			non_blank_line, empty);
		// non_blank_line
		setNeighbors(make_tree_next_states, non_blank_line, 	empty,		 		 empty, 				empty, 			empty,
																empty, 				 empty, 				empty, 			empty);
		// end_of_start
		setNeighbors(make_tree_next_states, end_of_start, 		empty, 				 empty, 				empty, 			empty,
																empty, 				 empty, 				empty, 			empty);
		
		return stateMachine(make_tree_next_states,
							/*size*/ number_of_next_states,
							/*max_neghbors*/ neighbor_count,
							make_tree_state_names_strings,
							number_of_states,
							parent_status,
							function_names);

}
string getNextWord1(string input, int i)
{
 	// this function gets the next word
	int j = 0;
	int count = 0;
	//printf("%i, %i\n", i, input.size());
	if(i >= input.size())
	{
		return "out of range";
	}
	while(input[i + j] != '\n')
	{
		//printf("%c ", input[i + j]);
		// can't trust the input
		/*if((i + j) >= strlen(input))
		{
			j--;
			break;
		}*/
		j++;
		count++;
	}
	//printf("character count %i\n", count);
	string word = input.substr(i, j);
	//char* word = malloc(sizeof(char) * j );
	//printf("%i\n", j);
	//memcpy(word, input + i, j);
	//word[j] = '\0';
	//printf("|%s|\n", word);
	//printf("chars in word %lu\n", strlen(word));
	/*
	collect the word
	return word
	*/
	return word;
}
bool errorFunction(Scanner* my_scanner)
{
	printf("\ncan't advance\n");
	return true;
	//exit(1);
}



bool oneLineOneOne(Scanner* my_scanner)
{

	if(my_scanner != NULL)
	{
		my_scanner->_lines_graph = initVector();
		my_scanner->root = 0;
		int* x = (int*) malloc(sizeof(int));
		*x = my_scanner->root;

		MultiwayLinesNode* dummy_dummy_root_node = initMultiwayLinesNode();
		dummy_dummy_root_node = setName(dummy_dummy_root_node, "dummy_dummy_root");

		append(my_scanner->_lines_graph, dummy_dummy_root_node);

		MultiwayLinesNode* dummy_root_node = initMultiwayLinesNode();
		dummy_root_node = setName(dummy_root_node, "dummy_root");

		append(my_scanner->_lines_graph, dummy_root_node);
		// doubly link root_node and dummy_root_node
		/*
		append(1) to root_node's child vector
		set dummy_root_node's parent value to 0
		*/

		doubleLink2(my_scanner->_lines_graph, 0, 1);



		MultiwayLinesNode* root_node = initMultiwayLinesNode();
		root_node = setName(root_node, "root");



		append(my_scanner->_lines_graph, root_node);
		doubleLink2(my_scanner->_lines_graph, 1, 2);

		my_scanner->two_lines = initTwoLines();

		my_scanner->two_lines->_parent = 2;
		my_scanner->two_lines->_child = 0;

		my_scanner->two_lines->_temp_child = 0;


		return true;
	}
	return false;
}

bool endOfStart(Scanner* my_scanner)
{
	//printf("current line %i, total lines %i, -> %i\n", my_scanner->count, my_scanner->num_lines, my_scanner->count > my_scanner->num_lines);
	// from outOfLines
	
	if(my_scanner->done_reading_data)
	{
		return true;
	}
	return false;
}

bool outOfLines(Scanner* my_scanner)
{
	// when we hit line 200 the function call sequence for endOfStart and outOfLines is endOfStart, outOfLines, endOfStart
	//printf("current line1 %i, total lines %i, -> %i\n", my_scanner->count, my_scanner->num_lines, my_scanner->count == my_scanner->num_lines);
	// assume the input has all been read in
	if(my_scanner != NULL)
	{
		if(my_scanner->i >= my_scanner->input.size())
		{

			my_scanner->done_reading_data = true;
			return true;
		}
		return false;
	}

	return false;
}


bool oneLineOneTwo(Scanner* my_scanner)
{
	if(my_scanner != NULL)
	{
		my_scanner->two_lines->first_line->word = my_scanner->two_lines->temp_word;

		my_scanner->two_lines->first_line->number_of_tabs = my_scanner->two_lines->temp_number_of_tabs;

		return true;
	}

	return false;
}

bool oneLineTwoTwo(Scanner* my_scanner)
{
	if(my_scanner != NULL)
	{
		my_scanner->two_lines->second_line->word = my_scanner->two_lines->temp_word;

		my_scanner->two_lines->second_line->number_of_tabs = my_scanner->two_lines->temp_number_of_tabs;


		return true;
	}

	return false;
}
//setup_first_2_nodes
	// setup first 2 nodes
	/*

		parent node is first line
		child node is second line
	*/
bool setupFirstTwoNodes(Scanner* my_scanner)
{
	if(my_scanner != NULL)
	{
		if(my_scanner->first_two_lines)
		{

			my_scanner->two_lines->_child = 4;

			MultiwayLinesNode* parent_node = initMultiwayLinesNode();
			parent_node = setName(parent_node, my_scanner->two_lines->first_line->word);

			MultiwayLinesNode* child_node = initMultiwayLinesNode();
			child_node = setName(child_node, my_scanner->two_lines->second_line->word);

			append(my_scanner->_lines_graph, parent_node);
			append(my_scanner->_lines_graph, child_node);
			
			doubleLink2(my_scanner->_lines_graph,
						my_scanner->two_lines->_parent,
						3);
			doubleLink2(my_scanner->_lines_graph,
						my_scanner->two_lines->_parent + 1,
						my_scanner->two_lines->_child);
			my_scanner->two_lines->_parent++;

			if(my_scanner->two_lines->first_line->number_of_tabs == my_scanner->two_lines->second_line->number_of_tabs)
			{
				printf("the input has a tab mistake\n");
				return false;
			}
			// get second word as first and wipe first word out
			// get second tab count as first and wipe first tab count out

			my_scanner->two_lines->first_line->word = my_scanner->two_lines->second_line->word;
			my_scanner->two_lines->first_line->number_of_tabs = my_scanner->two_lines->second_line->number_of_tabs;

			my_scanner->two_lines->second_line->word = "";
			my_scanner->two_lines->second_line->number_of_tabs = 0;

			my_scanner->first_two_lines = false;
			return true;
		}
		
	}
	return false;
}
bool makeNodeForWordTwo(Scanner* my_scanner)
{
	if(my_scanner != NULL)
	{

		MultiwayLinesNode* temp_child_node = initMultiwayLinesNode();
		temp_child_node = setName(temp_child_node, my_scanner->two_lines->second_line->word);


		append(my_scanner->_lines_graph, temp_child_node);
		my_scanner->two_lines->_temp_child = my_scanner->_lines_graph->population - 1;


		return true;
	}
	return false;
}
//make_node_for_word_2
		/*

		new node is second line
		*/

bool downLink(Scanner* my_scanner)
{
	//printf("go down %i, %i -> %i\n", my_scanner->two_lines->first_line->number_of_tabs, my_scanner->two_lines->second_line->number_of_tabs, my_scanner->two_lines->first_line->number_of_tabs < my_scanner->two_lines->second_line->number_of_tabs);


	if(my_scanner->two_lines->first_line->number_of_tabs < my_scanner->two_lines->second_line->number_of_tabs)
	{

		doubleLink2(my_scanner->_lines_graph, my_scanner->two_lines->_child,

			my_scanner->_lines_graph->population - 1);


		MultiwayLinesNode* x =  getMultiwayLinesNode(getItem(my_scanner->_lines_graph,
				my_scanner->two_lines->_parent));
		int x_parent_size = x->children_ids->population;
		int* next_parent = getInt(getItem(x->children_ids, x_parent_size - 1));
		//printf("next parent %i\n", *next_parent);
		my_scanner->two_lines->_parent = *next_parent;

		MultiwayLinesNode* y = getMultiwayLinesNode(getItem(my_scanner->_lines_graph, my_scanner->two_lines->_child));

		int y_child_size = y->children_ids->population;

		int* next_child = getInt(getItem(y->children_ids, y_child_size - 1));

		my_scanner->two_lines->_child = *next_child;
		

		return true;
	}
	return false;
}



bool upLink(Scanner* my_scanner)
{

	//printf("go up %i, %i -> %i\n", my_scanner->two_lines->first_line->number_of_tabs,
	//	my_scanner->two_lines->second_line->number_of_tabs,
	//	my_scanner->two_lines->first_line->number_of_tabs > my_scanner->two_lines->second_line->number_of_tabs);
	//printf("new child |%s|\n", my_scanner->two_lines->temp_child->line.c_str());

	if(my_scanner->two_lines->first_line->number_of_tabs > my_scanner->two_lines->second_line->number_of_tabs)
	{



		int target_indent = my_scanner->two_lines->first_line->number_of_tabs;

		while(target_indent > my_scanner->two_lines->second_line->number_of_tabs)
		{

			// have parent go up 1 parent
			// have child go up 1 parent

			MultiwayLinesNode* x =  getMultiwayLinesNode(getItem(my_scanner->_lines_graph,
			my_scanner->two_lines->_parent));

			int next_parent = x->parent_id;

			my_scanner->two_lines->_parent = next_parent;

			MultiwayLinesNode* y = getMultiwayLinesNode(getItem(my_scanner->_lines_graph, my_scanner->two_lines->_child));



			int next_child = y->parent_id;

			my_scanner->two_lines->_child = next_child;

			target_indent--;
		}

		doubleLink2(my_scanner->_lines_graph,
					my_scanner->two_lines->_parent,
					my_scanner->two_lines->_temp_child);
		my_scanner->two_lines->_child = my_scanner->two_lines->_temp_child;
		
		return true;
	}
	return false;
}



bool acrossLink(Scanner* my_scanner)
{
	//printf("go across %i, %i -> %i\n", my_scanner->two_lines->first_line->number_of_tabs,
	//	my_scanner->two_lines->second_line->number_of_tabs,
	//	my_scanner->two_lines->first_line->number_of_tabs == my_scanner->two_lines->second_line->number_of_tabs);
	//printf("new child |%s|\n", my_scanner->two_lines->temp_child->line.c_str());

	if(my_scanner != NULL)
	{

		doubleLink2(my_scanner->_lines_graph,
					my_scanner->two_lines->_parent,
					my_scanner->two_lines->_temp_child);
		my_scanner->two_lines->_child = my_scanner->two_lines->_temp_child;
		return true;
	}
	return false;
}


bool cleanupTrackers(Scanner* my_scanner)
{
	if(my_scanner != NULL)
	{

		my_scanner->two_lines->first_line->word = my_scanner->two_lines->second_line->word;
		my_scanner->two_lines->second_line->word = "";


		my_scanner->two_lines->first_line->number_of_tabs = my_scanner->two_lines->second_line->number_of_tabs;
		my_scanner->two_lines->second_line->number_of_tabs = 0;

		return true;
	}
	return false;
}



bool isBlankLine(string current_word)
{
	if(current_word.size() > 0)
	{
		int size = current_word.size();
		for(int i = 0; i < size; i++)
		{
			if(!whiteSpace(current_word[i]))
			{
				return false;
			}
		}
		return true;

	}
	return true;
}

bool blankLine1(Scanner* my_scanner)
{
	// my_scanner->i should be on the first character after the newline
	//printf("blank line1 %i, %i\n", my_scanner->count, my_scanner->num_lines);
	//printf("next line |%s|\n", getNextWord1(my_scanner->input, my_scanner->i).c_str());
	if(my_scanner != NULL)
	{
		

		int i = my_scanner->i;
		string current_word = getNextWord1(my_scanner->input, my_scanner->i);
		my_scanner->i += current_word.size() + 1;
		my_scanner->count++;
		if(isBlankLine(current_word))
		{
			return true;
			
		}
		else
		{
			// roll back changes, because current_word is not a blank line
			my_scanner->i = i;
			my_scanner->count--;

			current_word = "";

			// save current_word as first_line
			return false;
		}

	
	}
	return false;

}


bool nonBlankLine(Scanner* my_scanner)
{
	// my_scanner->i should be on the first character after the newline
	// get the line
	// scan it for non-whitespace characters
	// use the count to determine what line to save to after it's a valid line
	// if it passes, store it and increment the count
	if(my_scanner != NULL)
	{
		string current_word = getNextWord1(my_scanner->input, my_scanner->i);
		my_scanner->i += current_word.size() + 1;


		my_scanner->count++;
		if(!isBlankLine(current_word))
		{

			

				my_scanner->two_lines->temp_number_of_tabs = countTabs(current_word, 0);


				int size2 = current_word.size() + 1 - my_scanner->two_lines->temp_number_of_tabs;

				my_scanner->two_lines->temp_word = current_word.substr(my_scanner->two_lines->temp_number_of_tabs, size2);

				current_word = "";

				// save current_word as first_line
				return true;
			

		}
		else
		{
			return false;
		}

	}
	return false;
	
}


void deleteMachineForMakeTree(StateMachine* machine)
{
	
	/*int* next_states;
	int current_state;
	int max_neighbors;
	int next_states_size;
	int ith_recursive_call;
	int error_state;
	int end_state;
	char** state_names_strings;
	int number_of_states;
	*/
	if(machine != NULL)
	{
		free(machine->next_states);
		machine->next_states = NULL;
		// each string was statically allocated
		free(machine->state_names_strings);
		machine->state_names_strings = NULL;
		free(machine);
		machine = NULL;
	}
}




int runStates(StateMachine* machine, int start_of_next_states, void* object/*Scanner* my_scanner*/, int level)
{
	// children links come before next links
	
	

	int current_state = machine->current_state;

	int max_neighbors = machine->max_neighbors;
	// go to start of next states for current_state
	int i = start_of_next_states;

	bool state_changed = false;
	Scanner* my_scanner = (Scanner*) object;
	for(int j = 0; j < max_neighbors; j++)
	{
		//printf("%strying %s\n", makeSpaces(level).c_str(),
		//						 machine->state_names_strings->at( machine->next_states[i + j] ).c_str() );

		int winning_state = 0;

		switch(machine->next_states[i + j])
		{
			

			case start:
			{
				winning_state = start;
				state_changed = true;
				break;
			}
			/*
			case two_lines:
			{

				winning_state = two_lines;
				state_changed = true;


				break;
			}*/
			case one_line_one_1:
			{
				if(oneLineOneOne(my_scanner))
				{
					winning_state = one_line_one_1;
					state_changed = true;

				}
				break;
			}
			case one_line_one_2:
			{
				if(oneLineOneTwo(my_scanner))
				{
					winning_state = one_line_one_2;
					state_changed = true;

				}
				break;
			}
			case one_line_two_1:
			{
				winning_state = one_line_two_1;
				state_changed = true;
				break;
			}
			case one_line_two_2:
			{
				if(oneLineTwoTwo(my_scanner))
				{
					winning_state = one_line_two_2;
					state_changed = true;

				}
				break;
			}
			/*
			case end_of_2_lines:
			{
				winning_state = end_of_2_lines;
				state_changed = true;
				break;
			}*/

			case setup_first_2_nodes:
			{
				if(setupFirstTwoNodes(my_scanner))
				{
					winning_state = setup_first_2_nodes;
					state_changed = true;

				}
				break;
			}
			case make_node_for_word_2:
			{
				if(makeNodeForWordTwo(my_scanner))
				{
					winning_state = make_node_for_word_2;
					state_changed = true;

				}
				break;
			}
			case down_link:
			{
				if(downLink(my_scanner))
				{
					winning_state = down_link;
					state_changed = true;

				}
				break;
			}
			case up_link:
			{
				if(upLink(my_scanner))
				{
					winning_state = up_link;
					state_changed = true;

				}
				break;
			}
			case across_link:
			{
				if(acrossLink(my_scanner))
				{
					winning_state = across_link;
					state_changed = true;

				}
				break;
			}


			case _cleanup:
			{
				if(cleanupTrackers(my_scanner))
				{
					winning_state = _cleanup;
					state_changed = true;

				}
				break;
			}

			case one_line:
			{
				winning_state = one_line;
				state_changed = true;
				break;
			}
			case out_of_lines:
			{
				if(outOfLines(my_scanner))
				{
					winning_state = out_of_lines;
					state_changed = true;

				}
				break;
			}
			case blank_line:
			{
				if(blankLine1(my_scanner))
				{
					winning_state = blank_line;
					state_changed = true;

				}
				break;
			}
			case non_blank_line:
			{
				if(nonBlankLine(my_scanner))
				{
					winning_state = non_blank_line;
					state_changed = true;

				}
				break;
			}
			case end_of_start:
			{
				if(endOfStart(my_scanner))
				{
					winning_state = end_of_start;
					state_changed = true;

				}
				break;
			}
			default:
			{
				break;
			}
		}
		if(state_changed)
		{
			return winning_state;
		}

	}
	if(!state_changed)
	{
		return false;
	}
	return -10;

}



bool makeTreeStateMachine(Scanner* my_scanner)
{

	if(my_scanner != NULL)
	{

		StateMachine* machine = setupMachineForMakeTree();
		// the first state doesn't get run
		// machine is finished the moment the current state == done
		//int counter = 0;
		printf("start state machine\n");
		//int current_state = machine->current_state;
		// loop through and try the children
		int level = 0;
		int counter = 0;
		int* counter_ptr = &counter;
		runMachine(machine, my_scanner, level, counter_ptr);
		//printMultiwayLinesNodesInContainer(my_scanner->_lines_graph);
		printTree2(my_scanner->_lines_graph, 2, 0);

		//machine->current_state = current_state
		deleteMachineForMakeTree(machine);

		//printf("machine is done\n");
		//printTree(my_scanner->lines_graph, 0);

		return true;
	}

	return false;
}
