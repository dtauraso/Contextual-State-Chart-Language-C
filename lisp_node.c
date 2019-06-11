#include "lisp_node.h"


enum data_types{is_list, is_string, is_empty_case};
 enum token_types {_primitive, _object, _array, _string};

char* lispNodeType(int type_value)
{
	if(type_value == is_list)
	{
		return "is_list";
	}
	else if(type_value == is_string)
	{
		return "is_string";
	}
	else if(type_value == is_empty_case)
	{
		return "is_empty_case";
	}
	else
	{
		return NULL;
	}
}

void printLispNodes(LispNode* root, int indent_level)
{
	//LispNode* root_list = (LispNode*) root->value;
	//printf("%x\n", root);
	// can't seem to get the last list
	if(root != NULL)
	{

		// root could have a list in value or a string
		// each node containing a string points to the next one
		if(root->value_type == is_string)
		{
			//printf("indent level %i\n", indent_level);
			//printf("|%s|\n", makeSpaces(indent_level));
			if(root->value != NULL)
			{
				char* string = (char*) root->value;
				//printf("%s%s\n", makeSpaces(indent_level), string);
				// returns NamesSize*
				printLispNodes(root->next, indent_level);

			}	
		}
		else if(root->value_type == is_list)
		{
			// visiting a list of lists
			//printf("list\n");
			LispNode* list_of_lists_tracker = root;
			LispNode* list_of_strings = (LispNode*) root->value;
			int count = 0;
			while(list_of_lists_tracker != NULL && list_of_strings != NULL)
			{
				//printf("%i\n", count);
				//printf("count %i\n", list_of_lists_tracker->count);
				// doesn't return anything to use
				printLispNodes(list_of_strings, indent_level + 1);
				list_of_lists_tracker = list_of_lists_tracker->next;
				if(list_of_lists_tracker == NULL)
						break;
				list_of_strings = (LispNode*) list_of_lists_tracker->value;
				count++;
			}
		}
		
	}

	
}
void deleteLispNodes(LispNode* root)
{
	//LispNode* root_list = (LispNode*) root->value;
	//printf("%x\n", root);
	// can't seem to get the last list
	if(root != NULL)
	{

		// root could have a list in value or a string
		// each node containing a string points to the next one
		if(root->value_type == is_string)
		{
			//printf("indent level %i\n", indent_level);
			//printf("|%s|\n", makeSpaces(indent_level));
			if(root->value != NULL)
			{
				//printf("%s%s\n", makeSpaces(indent_level), string);
				// returns NamesSize*
				deleteLispNodes(root->next);
				if(root->value != NULL)
				{
					free(root->value);
				}
				if(root->next != NULL)
				{
					free(root->next);
					//free(root);  // temp's value from call in while loop
				}
			}

		}
		else if(root->value_type == is_list)
		{
			// visiting a list of lists
			//printf("list\n");
			LispNode* list_of_lists_tracker = root;
			LispNode* list_of_strings = (LispNode*) root->value;
			int count = 0;
			while(list_of_lists_tracker != NULL && list_of_strings != NULL)
			{
				//printf("%i\n", count);
				//printf("count %i\n", list_of_lists_tracker->count);
				// doesn't return anything to use
				deleteLispNodes(list_of_strings);
				LispNode* temp = list_of_lists_tracker;
				list_of_lists_tracker = list_of_lists_tracker->next;

				if(list_of_lists_tracker == NULL)
						break;
				list_of_strings = (LispNode*) list_of_lists_tracker->value;
				
				if(temp->value != NULL)
				{
					free(temp->value);

				}
				if(temp != NULL)
				{
					free(temp);
				}
				count++;
			}
		}
		
	}

	
}
LispNode* strings(int* i, jsmntok_t tokens[], const char* input, int number_of_strings_left, int call_count)
{
	jsmntok_t current_token = tokens[*i];
	char* current_string = collectChars(current_token, input);
	//printf("current string %s\n", current_string);
	//printf("items remaining %i\n", number_of_strings_left);
	if(number_of_strings_left == 1)
	{
		//printf("type %s\n", tokenType(current_token));
		//printf("last case keword\n");
		*i += 1;
		return cons(current_string, NULL, is_string, 0, call_count);
	}
	
	else //if(current_token.type == _string)
	{
		//printf("got here 2\n %s\n", current_string);

		*i += 1;
		LispNode* n = strings(i, tokens, input, number_of_strings_left - 1, call_count + 1);
		//printf("total count %i\n", n->call_count);
		LispNode* x = cons(current_string,
						   n,
						   is_string,
						   0,
						   n->call_count);
		// how many more items from this one?
		//printLispNodes(x, 1);
		return x;
	}
	
}
// record # of total calls
LispNode* array(int* i, jsmntok_t tokens[], const char* input, int call_count, int token_count)
{


	// count # of calls to obtain a total # of strings in adition to counting how many strings in each list
	// return a lisp style linked list holding the strings collected

	jsmntok_t current_token = tokens[*i];
	if(current_token.type != _array)  	// error
	{
		//printf("we have a problem\n");
		return cons(NULL, NULL, is_empty_case, 0, call_count);
	}
	//printf("number of nested items %i\n", current_token.size);
	// null array
	if(strcmp(collectChars(current_token, input), "\"[]\"") == 0)
	{
		// done with all inner arrays and outer arrays
		//printf("null array\n");
		return cons(NULL, NULL, is_empty_case, 0, call_count);
	}
	
	*i += 1;
	int items_in_array = current_token.size;
	current_token = tokens[*i];
	//printf("second time\n");
	if(current_token.type != _string)
	{
		//printf("we have a problem\n");
		return cons(NULL, NULL, is_empty_case, 0, call_count);
	}
	LispNode* string_coll = strings(i, tokens, input, items_in_array, call_count + 1);
	//printf("collected the strings\n");
	if(*i == token_count)
	{
		return cons(string_coll, NULL, is_list, items_in_array, string_coll->call_count);
	}
	//string_coll->count = items_in_array;
	// token is o keyword or array
	//printf("i %i\n", *i);
	//printf("%i, %i\n", *i, max_tokens);
	//if(*i >= max_tokens)
	//	return cons(string_coll, NULL, is_list);
	current_token = tokens[*i];
	//printf("array or keyword %s\n", tokenType(current_token));

	if(tokenIsKeyWord(collectChars(current_token, input)))  // end of outer array, still in object
	{

		//printf("at keyword\n");
		//printf("%s %s\n", tokenType(current_token), collectChars(current_token, input));
		// setting the number of items in string_coll would not be meaningfull
		return cons(string_coll, NULL, is_list, items_in_array, string_coll->call_count);
	}
	else if(current_token.type == _array)  // end of inner array, still in object
	{
		//printf("items in array %i\n", items_in_array);
		LispNode* x = array(i, tokens, input, string_coll->call_count, token_count);
		return cons(string_coll, x, is_list, items_in_array, x->call_count);
	}
	else  // end of object
	{
		//printf("items in array 2 %i\n", items_in_array);
		// setting the number of items in string_coll would not be meaningfull
		return cons(string_coll, NULL, is_list, items_in_array, string_coll->call_count);
	}

	//printf("got here object\n");

}



LispNode* cons(void* data, void* link, int data_type, int count, int call_count)
{
	LispNode* new_ob = malloc(sizeof(LispNode));
	new_ob->value = data;
	new_ob->next = link;
	new_ob->count = count;
	new_ob->call_count = call_count;
	//printf("void link %i\n", link);
	//printf("void data %i\n", data);
	
	/*if(data_type == is_string)
	{
		char* x = (char*) new_ob->value;
		printf("saved string %s\n", x);
	}*/
	if(data_type == is_list)
		new_ob->value_type = is_list;
	else if(data_type == is_string)
		new_ob->value_type = is_string;
	else if(data_type == is_empty_case)
		new_ob->value_type = is_empty_case;
	return new_ob;

}
LispNode* makeLispNode()
{
	LispNode* node = malloc(sizeof(LispNode));
	node->value = NULL;
	node->next = NULL;
	node->count = 0;

	node->value_type = 2;


	// not valid anymore
	// char* = 0
	// LispNode* = 1

	// unset = 2
	return node;
}
