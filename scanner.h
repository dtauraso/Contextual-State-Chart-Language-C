#ifndef SCANNER
#define SCANNER
#include "standard_headers.h"
#include "multiway_lines_node.h"
#include "state_machine.h"
#include "vector.h"


typedef struct OneLine
{
	int number_of_tabs;
	string word;
}OneLine;
OneLine* initOneLine();
bool deleteOneLine(OneLine* one_line);

typedef struct TwoLines
{
	OneLine* first_line;
	OneLine* second_line;
	string temp_word;
	int temp_number_of_tabs;

	int _parent;
	int _child;
	int _temp_child;
}TwoLines;
TwoLines* initTwoLines();
bool deleteTwoLines(TwoLines* two_lines);

typedef struct Scanner
{
	// the input is scanned and results are put into _lines_graph
	int i;
	int num_lines;
	int count;

	string input;

	bool first_two_lines;


	bool done_reading_data;
	// holding all the nodes representing each non-blank line
	Vector* _lines_graph;
	int root;

	TwoLines* two_lines;


}Scanner;
// init
Scanner* initScanner(string input);

// delete
bool deleteScanner(Scanner* my_scanner);

int computeIndexForMakeTree(int offset, int state_name);
StateMachine* setupMachineForMakeTree();
void deleteMachineForMakeTree(StateMachine* machine);

// state machine functions
////////////
string getNextWord1(Scanner* my_scanner);

bool cleanup(Scanner* my_scanner);

bool shiftChildUp(Scanner* my_scanner);
bool shiftChildDown(Scanner* my_scanner);

bool goDown(Scanner* my_scanner);
bool goUp(Scanner* my_scanner);
bool goAcross(Scanner* my_scanner);

bool advanceBuffer(Scanner* my_scanner);
//bool quitEarly(Scanner* my_scanner);

bool nonBlankLine0(Scanner* my_scanner);
bool nonBlankLine1(Scanner* my_scanner);
bool blankLine(Scanner* my_scanner);


bool haveNoMoreLinesToRead(Scanner* my_scanner);
bool onLastLine(Scanner* my_scanner);

bool setup(Scanner* my_scanner);
string getNextWord1(string input, int i);

bool errorFunction(Scanner* my_scanner);
///////////
MultiwayLinesNode* makeTree(Scanner* my_scanner, char* input);
void runMachine(StateMachine* machine, void* object/*Scanner* my_scanner*/, int level, int* counter);

bool makeTreeStateMachine(Scanner* my_scanner);

#endif