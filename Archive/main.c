#include "state2.h"
#include <stdio.h>
#include <stdlib.h>
/*
    30 min a day on this
    root

    current_root
    loop

        if same(next indent == current indent)
            connect current_root to next item(as the next child)


        if pulling out(next indent < current indent)
            loop until next indent == current indent - 1
                set root to parent
                decrement current indent
            now root is 1 level above the next index
            connect current_root to next item(as the next child)



        if more depth(next indent > current indent)
            connect current_root to next item
            set current_root to next item

     state coordinates stay consistent with the state
     the level indicates where we are

*/
struct ContextState;
char* getNextWord(char* input, int i)
{
 	// this function gets the next word

	/*
	collect the word
	return word
	*/
}

struct ContextState* makeTree(char* input, int i)
{
	struct ContextState* VectorTest = newState();

	/*
	get the word
	past newline
	get next indent
	if more depth(next indent > current indent)
		connect current_root to next item
		set current_root to next item

	*/
}
char* readFile(char* file_name)
{
	FILE* file = fopen(file_name, "r");
	char* string;
	size_t n = 0;
	int c;

	if(file == NULL)
	   return NULL; // file can't be opened
   fseek(file, 0, SEEK_END);
   long f_size = ftell(file);
   fseek(file, 0, SEEK_SET);
   string = malloc(f_size);

   while((c = fgetc(file)) != EOF)
   {
	   string[n++] = (char) c;
   }
   string[n] = '\0';
   return string;
}

int main(int argc, char** argv)
{
	char* input = readFile(argv[1]);
	printf("%s\n", input);
	return 0;
}
