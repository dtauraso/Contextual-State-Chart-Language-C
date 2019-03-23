#include "state3.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>


struct ContextState;


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
char* getNextWord(char* input, int i)
{
 	// this function gets the next word
	int j = 0;
	int count = 0;
	while(input[i+j] != '\n')
	{
		//printf("%c+ ", input[i+j]);
		j++;
		count ++;
	}
	//printf("character count %i\n", count);
	char* word = malloc(sizeof(char) * j);
	memcpy(word, input + i, j);
	word[j] = '\0';
	//printf("chars in word %lu\n", strlen(word));
	/*
	collect the word
	return word
	*/
	return word;
}
int countTabs(char* input, int i)
{
	int k = 0;
	//printf("|%x|\n", input[i+k]);
	// this 't' is actually invisable from Atom when used as a tab character
	while(input[i+k] == '\t')
		k++;
	return k;
}

void printTree(ContextState* root)
{
	if(root == NULL)
		return;
	else
	{
		printf("%s\n\n", root->name);
		//printf("screwed\n");
		for(int i = 0; i < root->children_size; i++)
		{
			//printf("%i\n", i);
			printTree(root->children[i]);
		}

	}
	return;
}
void swap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = *a;
}
void doubleLink(ContextState* tracker, ContextState* child)
{
	child = appendParent(child, tracker);
	tracker = appendChild(tracker, child);

}
ContextState* makeTree(char* input)
{
	int current_indent = 0;
	int next_indent = 0;
	int i = 0;
	//printf("%s\n %i\n", input, i);
	ContextState* root = ContextState1();
	ContextState* tracker = root;
	int count = 0;
	while(count < 40)
	{
		char* word = getNextWord(input, i);
		tracker = setName(tracker, word);
		// strlen(word) > strlen(tracker->name)
		printf("%s|%s|%i|%lu|%lu\n", tracker->name, word, i, strlen( tracker->name), strlen(word));
		free(word);

		i += strlen(tracker->name)+1;
		printf("middle i %i\n", i);
		next_indent = countTabs(input, i);
		printf("%i %i\n", current_indent, next_indent);

		//printf("%i|%i\n", next_indent, i);
		// is this run for all new children?
		// yes
		if(next_indent > current_indent)
		{
			printf("going down\n");
			//printf("here\n");
			ContextState* child = ContextState1();
			if(child == NULL) exit(1);

			doubleLink(tracker, child);

			printf("^%s\n", child->parents[0]->name);
			// going down
			tracker = child;
			i += next_indent;
			printf("final i %i\n", i);
			swap(&current_indent, &next_indent);


		}
		else if(next_indent < current_indent)
		{
			printf("climb up\n");
			printf("%s|%i\n", tracker->name, i);
			// save item
			ContextState* child = ContextState1();
			if(child == NULL) exit(1);

			doubleLink(tracker, child);


			//tracker = child;
			i += next_indent;

			/*
			wrong
			6 4
			climb up
			["a": 0, "b": 0]|92
			*/
			int target_indent = current_indent;
			while(target_indent >= next_indent)
			{
				// have tracker go up 1 parent
				tracker = tracker->parents[tracker->parents_size-1]; // last path visited
				// target_indent--
				target_indent--;
			}
			// setup 2nd child
			printf("done%s|%i\n", tracker->name, i);
			ContextState* child2 = ContextState1();
			if(child2 == NULL) exit(1);
			doubleLink(tracker, child2);

			printf("^%s\n", child->parents[0]->name);
			// set tracker to child2 so child2 is named next round
			tracker = child2;

			// tracker should be at parent of the next line to be scanned

			// swap the indents
			swap(&current_indent, &next_indent);

		}
		// second "Children" was swapped with "lex_vars"
		printf("tree -------------------------\n");
		printTree(root);
		printf("-------------------------\n");


		count++;
	}
	/*
	get the word
	past newline
	get next indent
	if more depth(next indent > current indent)
		connect current_root to next item
		set current_root to next item

	*/
	return 0;
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
	//printf("%s\n", input);
	// todo
	// get rid of all blank lines
	makeTree(input);
	return 0;
}
