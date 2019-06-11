#include "trie_node.h"
#include "lisp_node.h"
#include "jsmn/jsmn.h"

enum token_types {_primitive, _object, _array, _string};
enum data_types{is_list, is_string, is_empty_case};
TrieNode* initTrieNode()
{
	TrieNode* node = malloc(sizeof(TrieNode));

	node->word = NULL;
	node->object = NULL;
	node->neighbors = NULL;
	node->neighbors_count = 0;
	node->size = 0;

	return node;

}
TrieNode* initTrieNodeWithNeighborCount(int number_of_possible_neighbors)
{
	TrieNode* node = malloc(sizeof(TrieNode));

	node->word = NULL;
	node->object = NULL;
	if(number_of_possible_neighbors == 0)
	{
		node->neighbors = NULL;
		node->size = 0;
	}
	else
	{
		node->neighbors = malloc(sizeof(TrieNode*) * number_of_possible_neighbors);
		node->size = number_of_possible_neighbors;

	}
	node->neighbors_count = 0;

	return node;

}
// each function consuming tokens advance the index
// to the token for the next function
TrieNode* arrayOfArrays(int* i,
				   jsmntok_t tokens[],
				   const char* input,
				   int token_count)
{
	// returns a TrieNode* type
	// the word and object attributes will be set to null
	/*
		typedef struct StringNode
		{
			char* word;
			struct StringNode* next;
		}StringNode;

		typedef struct TrieNode
		{

			char* word;
			struct TrieNode** neighbors;
			int neighbors_count;

			struct ContextState* object;
		}TrieNode;

	*/



	// the array token is also [] or [stuff]
	// current token is at an array
	// automaticall sets i to the next token
	jsmntok_t token = tokens[*i];
	if(token.type != _array) exit(1);
	//*i += 1;
	//token = tokens[*i];
	LispNode* root = makeLispNode();
	char* token_string = collectChars(token, input);
	//printf("%s\n", token_string);
	if(strcmp(token_string, "\"[]\"") == 0)
	{
		//printf("empty array\n");
		*i += 1;
		// return list;

		return NULL;

	}
	else
	{
		// current token is at first array in the sequence:
		// array array strings array strings
		// array strings not_array
		//printf("%s\n", tokenType(tokens[ ( *i ) ]));
		//printf("number of nested items %i\n", tokens[ ( *i ) ].size);
		int items_in_array = tokens[ ( *i ) ].size;
		// for the top level, we want to record a size of 1 for the container of n lists
		int items_in_high_level = 1;
		if(tokens[ *i ].type 		 == _array &&
		   tokens[ ( *i ) + 1 ].type == _array)
		{
			*i += 1;
			items_in_high_level = items_in_array;
		}
		//printf("items in outer array %i\n", items_in_array);
		//printf("%s\n", tokenType(tokens[ ( *i ) ]));
		// inner cons for the array of lists count
		// outer cons to tell the difference from a list of lists of strings and a list of strings
		//printf("about to convert to a lisp node chain\n");
		LispNode* x = array(i, tokens, input, 0, token_count);
		root = cons(cons(x, NULL, is_list, items_in_array, x->call_count), NULL, is_list, items_in_high_level, x->call_count);
		//root->count = items_in_array;
		//printf("items at top level %i\n", root->count);

		TrieNode* trie_tree_of_names = convertLispChainToTrieNodeChain(root);
		//printf("conversion complete\n");
		//printTrieNodeTreeFlat(trie_tree_of_names);
		//printf("printed\n");
		deleteLispNodes(root);

		//printLispNodes(root->value, 1);

		//printf("\nreturning trie_tree_of_names\n");
		return trie_tree_of_names;

		

	}
}
// list of lists -> lisp chain -> char pointers
TrieNode* convertLispChainToTrieNodeChain(LispNode* root)
{

	// assume root has 2 levels of strings and 1 level of root
	if(root != NULL)
	{
		// test with 
		/*
		["indent_number", "0", "76543"]
     	
     	[]

		[["child", "nexts"],
	       ["sibling"],
	       ["new_parent"]]

	    [["root"], ["0"]]
		*/
		//printf("total = %i\n", root->call_count);
		

		// storing the list of list of strings

		TrieNode* root2 = initTrieNodeWithNeighborCount(root->call_count);

		LispNode* list_of_lists_tracker = root->value;
		int count = list_of_lists_tracker->count;

		list_of_lists_tracker = (LispNode*) list_of_lists_tracker->value;
		int i = 0;
		while(list_of_lists_tracker != NULL && i < root->count)
		{
			//printf("# of sub items LIST %i: %i, %i\n", list_of_lists_tracker->count, i, root->count);
			TrieNode* trie_node_sequence = initTrieNodeWithNeighborCount(1);
			TrieNode* trie_node_squence_tracker = trie_node_sequence;
			LispNode* list_of_strings_tracker = list_of_lists_tracker->value;
			int j = 0;
			while(list_of_strings_tracker != NULL && j < list_of_lists_tracker->count)
			{

				// add word to trie_node_squence_tracker
				trie_node_squence_tracker->word = malloc(sizeof(char) * (strlen(list_of_strings_tracker->value) + 1) );

				memcpy(trie_node_squence_tracker->word,
					   list_of_strings_tracker->value,
					   sizeof(char) * (strlen(list_of_strings_tracker->value) + 1));
				// to match the parallel states in state charts for version 1, considering doing this
				// an extra bit
				// dashed lines for parallel states
				// the parser must ensure all states are either parallel or not
				// just need an example to prove the state were visited
				// the functions don't need to be fancy

				// check for last one here
				
				if(j == list_of_lists_tracker->count - 1)
				{
					//free(new_node->neighbors);
					//new_node->neighbors = NULL;
					trie_node_squence_tracker->neighbors = NULL;
					trie_node_squence_tracker->neighbors_count = 0;
					trie_node_squence_tracker->size = 0;


				}
				else
				{
					TrieNode* new_node = initTrieNodeWithNeighborCount(1);
					trie_node_squence_tracker->neighbors[0] = new_node;
					trie_node_squence_tracker->neighbors_count = 1;

					trie_node_squence_tracker = trie_node_squence_tracker->neighbors[0];
					list_of_strings_tracker = list_of_strings_tracker->next;

				}
				//printf("size == %i, count == %i\n", trie_node_squence_tracker->size, trie_node_squence_tracker->neighbors_count);
				j++;


			}


			list_of_lists_tracker = list_of_lists_tracker->next;

			root2->neighbors[i] = trie_node_sequence;

			if(root2->neighbors_count == root2->size)
			{
				if(root2->size == 0)
				{
					root2->size = 1;
				}
				else
				{
					root2->size = root2->size * 2;

				}

			}
			root2->neighbors_count += 1;
			//printf("size 2 == %i, count 2 == %i\n", root2->size, root2->neighbors_count);

			if(list_of_lists_tracker != NULL)
			{
				i++;

			}
			else
			{

				break;
			}



		}
		//printf("size 2 == %i, count 2 == %i\n", root2->size, root2->neighbors_count);

		return root2;	
	}
	return NULL;
}

int isMatch(char* ith_word, TrieNode* node)
{
	// finds out if ith_word is a neighbor of node
	if(ith_word != NULL && node != NULL)
	{
		//printf("isMatch\n");
		//printf("# of neighbors %i\n", node->neighbors_count);
		// returns the index on the first match
		for(int j = 0; node != NULL && j < node->neighbors_count; j++)
		{
			if(node->neighbors[j] != NULL)
			{
				if(node->neighbors[j]->word != NULL)
				{
					//printf("%s == %s\n", ith_word, node->neighbors[j]->word);
					if(strcmp(ith_word, node->neighbors[j]->word) == 0)
					{
						//printf("passes\n");
						return j;
					}
				}
				else
				{
					return -1;
				}
			}
			else
			{
				return -1;
			}
		}
	}	
	return -1;
}

TrieNodePackage3* findInTrie2(TrieNode* root, TrieNode* sequence_of_strings)
{

	// sequence_of_strings is the address of the first word in the state name
	// sequence_of_strings attribute set
	// word has a word stored
	// neighbors has 1 neighbor
	// neighbors_count == 1
	// size == 2
	// object = null
	// we are returning the node where we will start appending the words remaining
	// and the index of the first word remaining
	/*
	how does this work?
	*/
	/*
	typedef struct TrieNodePackage2
	{
		TrieNode* address;
		bool address_is_match;

	}TrieNodePackage;
	*/
	//printf("findInTrie2\n");

	/*
	typedef struct TrieNodePackage3
	{
		TrieNode* dict_trie_node;
		TrieNode* context_state_attribute_trie_node;
		bool context_state_is_found;
		bool is_first_mismatch;
		bool need_to_append_more_name;
	}TrieNodePackage3;
	*/
	TrieNodePackage3* package3 = malloc(sizeof(TrieNodePackage3));

	package3->dict_trie_node = root;
	package3->context_state_attribute_trie_node = sequence_of_strings;

	package3->context_state_is_found = NULL;
	package3->is_first_mismatch = NULL;
	package3->need_to_append_more_name = NULL;

	//TrieNode* dict_trie_node_prev = root;  // can't be null cause isMatch may return -1


	//prev = root;
	//printf("root->neighbors %x\n", root->neighbors);
	// replace this with something cleaner
	/*

	null, null case 1(assume both tree and input are null)
	loop
		

		a, b (no match stop)

		a, a(keep matching)
			null, null case 2(perfect match) enumerate this (match)
				context state doesn't exist
				else
					reutrn a found flag
			*, null(input was completely found but tree still has more nodes)(match)
				context state doesn't exist
				else
					return a found flag
			

			null, *(tree ran out of input first)


	tree, input
	a, b (no match stop)
	a, null(input was completely found)
	null, b(tree ran out of input first)
	null, null case 1(assume both tree and input are null)

	null, null case 2(perfect match)
	a, a

	any matching doesn't prove there is a context node or not
	matching and checking for a context node are separate
	*/
	/*
	found
	current
	string_tracker
	is_partial_match
	need_to_append_more_name
	*/
	if(package3->dict_trie_node == NULL || package3->context_state_attribute_trie_node == NULL)
	{
		// return null package
		return NULL;
	}

	/*
	these entries are also in the code where they are set
	need_to_append_more_name, context_state_is_found
	0, 0
	0, 1
	1, 0
	1, 0
	*/
	int i = 0;
	while(package3->dict_trie_node != NULL &&
		  package3->context_state_attribute_trie_node != NULL)
	{
		/*
		if(package3->dict_trie_node->word != NULL &&
		  package3->context_state_attribute_trie_node->word != NULL)
		{
			printf("%s, %s\n", package3->dict_trie_node->word, package3->context_state_attribute_trie_node->word);

		}
		*/
		// first time the root's neighbors are checked with the first name
		int ith_branch = isMatch(package3->context_state_attribute_trie_node->word,
								 package3->dict_trie_node);
		if(ith_branch >= 0) // match
		{
			//printf("perfect match\n");
			package3->is_first_mismatch = false;
			// stop conditiions
			// perfect match(full match) or
			// input was completely found but tree still has more nodes (full match)

			//null, null case 2(perfect match)
			// *, null(input was completely found but tree still has more nodes)(match)

			if(
				(package3->context_state_attribute_trie_node->neighbors == NULL) 		||  // safety check only(not a case)

				(package3->dict_trie_node->neighbors[ith_branch] 			== NULL &&
			   package3->context_state_attribute_trie_node->neighbors[0] 	== NULL) 	||

				(package3->dict_trie_node->neighbors[ith_branch] 			 != NULL &&
			   	   package3->context_state_attribute_trie_node->neighbors[0] == NULL)
				)
			{
				if(
					(package3->context_state_attribute_trie_node->neighbors == NULL) 		||

					(package3->dict_trie_node->neighbors[ith_branch] 		!= NULL))
				{
					//printf("perfect match 2\n");

				}
				package3->need_to_append_more_name = false;
				//printf("%x\n", package3->dict_trie_node->neighbors[ith_branch]->object);

				if(package3->dict_trie_node->neighbors[ith_branch]->object != NULL)
				{
					// return a found flag
					package3->context_state_is_found = true;	// 	0, 1
					return package3;
				}
				else
				{
					// already existing objects are being put in here as an objectless internal node
					//printf("can add as an internal node\n");
					// need to add it
					package3->context_state_is_found = false;  // 	0, 0
					if((package3->context_state_attribute_trie_node->neighbors == NULL) 		||
						(package3->dict_trie_node->neighbors[ith_branch] 		!= NULL))
					{
						// advance the dict tracker to the next one because it already matched and will be the location of the next
						// ContextState object
						// the contest state attribute tracker is null because we have no new trie nodes to insert
						package3->dict_trie_node = package3->dict_trie_node->neighbors[ith_branch];
						//package3->context_state_attribute_trie_node = NULL;
						//package3->dict_trie_node = package3->dict_trie_node->neighbors;

						/*if(package3->dict_trie_node->word != NULL &&
								  package3->context_state_attribute_trie_node->word != NULL)
						{
							printf("%s, %s\n", package3->dict_trie_node->word, package3->context_state_attribute_trie_node->word);

						}*/

					}
					//package3->dict_trie_node = package3->dict_trie_node->neighbors[ith_branch];
					return package3;
				}
			}
			// relationship with ith_branch < 0
			/*
			ran out of input = not present
			mismatch == the character present is wrong 
			*/
			// null, *(tree ran out of input first)
			// tree ran out of input first(partial match)
			else if(package3->dict_trie_node->neighbors[ith_branch] 	     == NULL &&
			   	   package3->context_state_attribute_trie_node->neighbors[0] != NULL)
			{
				//printf("partial match\n");

				// 	1, 0

				// sequence of strings doesn't exists
				package3->context_state_is_found = false;

				// need to append more names to trie tree dict
				package3->need_to_append_more_name = true;
				return package3;

				// return current and string tracker
			}
			// a, a(keep matching)
			// all good, so advance
			else
			{
				//printf("advance\n");
				//dict_trie_node_prev = package3->dict_trie_node;
				package3->dict_trie_node = package3->dict_trie_node->neighbors[ith_branch];
				package3->context_state_attribute_trie_node = package3->context_state_attribute_trie_node->neighbors[0];
			}
		
		}
		// a, b case 
		// can't use the current versions of the trackers cause appending would have this for a future check
		// a, b
		// b
		// current->neighbors == NULL should be in here
		// 1, 0
		else // ith_branch < 0
		{
			//printf("mismatch\n");
			//printf("%s, %s\n", package3->dict_trie_node->word, package3->context_state_attribute_trie_node->word);
			// need to know if it was the first mismatch
			if(i == 0)
			{
				package3->is_first_mismatch = true;
			}
			else
			{
				package3->is_first_mismatch = false;
			}
			//printf("here neighbors\n");
			// 	NULL, 1, 0
			// return dict_trie_node and context_state_attribute_trie_node
			package3->context_state_is_found = false;
			package3->need_to_append_more_name = true;
			// package3->is_partial_match is not set cause we don't know if the first one was a mismatch or the nth one
			// was a mismatch
			// need to return the node in the dict path right before the mismatch occurred so the future checks looks like this
			// [a, b] are neighbors
			// b
			// which will be a match next time
			// actually did go in right place entire time(not sure why)
			//package3->dict_trie_node = dict_trie_node_prev;
			return package3;
		}
		i++;
	}


	return NULL;
}
/*
	typedef struct TrieNode
	{

		char* word;
		struct TrieNode** neighbors;
		int neighbors_count;

		struct ContextState* object;
	}TrieNodee;

	
*/
/*
typedef struct NeighborNames
{
	char** list_of_names;
	int number_of_names;
	int* start_names;
	int number_of_start_names;
}NeighborNames;

*/
TrieNode* appendWord(TrieNode* node, char* ith_name)
{
	///printf("appendWord\n");
	// what happens the first time?
	// size and neighbors_count still being set by compiler
	if(ith_name != NULL)
	{
		// make sure node->neighbors_count > node->size is not happening anywhere these are updated
		// node->neighbors_count > node->size is wrong
		//printf("before size %i, count %i\n",node->size, node->neighbors_count);

		//TrieNode** neighbors = NULL;//node->neighbors;
		// 
		// new item was stored at node->neighbors_count + 1 and node->neighbors_count == 0
		//int neighbors_count = node->neighbors_count + 1;
		//printf("neighbors_count %i\n", neighbors_count);
		int sizeof_new_neighbors;
		// not safely making a trinode*
		TrieNode** new_neighbors = NULL;
		if(node->neighbors_count == node->size)
		{
			if(node->size == 0)
			{
				sizeof_new_neighbors = sizeof(TrieNode*);
				new_neighbors = malloc(sizeof_new_neighbors);
			}
			else
			{
				sizeof_new_neighbors = sizeof(TrieNode*) * (node->size * 2);
				new_neighbors = malloc(sizeof_new_neighbors);

			}
			memcpy(new_neighbors,
			   node->neighbors,
			   sizeof(TrieNode*) * node->neighbors_count);

		}
		else if(node->neighbors_count < node->size)
		{
			new_neighbors = node->neighbors;
		}
		// might be a problem when node->neighbors_count < node->size

		//printf("here\n");

		

		// add (k+1)th word
		//printf("got here\n");
		// make a tracker pointing to the 
		// maybe this pattern doesn't work when there was nothing originally in the array
		new_neighbors[node->neighbors_count] = malloc(sizeof(TrieNode));
		//printf("here now %s\n", ith_name);
		int sizeof_ith_name = strlen(ith_name) + 1;

		new_neighbors[node->neighbors_count]->word = malloc(sizeof(char) * sizeof_ith_name);
		//printf("reached here\n");

		

		new_neighbors[node->neighbors_count]->neighbors = NULL;
		new_neighbors[node->neighbors_count]->object = NULL;
		new_neighbors[node->neighbors_count]->neighbors_count = 0;
		new_neighbors[node->neighbors_count]->size = 0;



		memcpy(new_neighbors[node->neighbors_count]->word,
			   ith_name,
			   sizeof(char) * sizeof_ith_name);

		// only for copying over entire array
		// delete node_to_put_context_state_at->neighbors
		if(node->neighbors_count == node->size)
		{
			// might need to change this later
			free(node->neighbors);

			node->neighbors = new_neighbors;

		}
		//printf("after size %i, count %i\n",node->size, node->neighbors_count);

		// will not work
		// doesn't work if size == 0
		if(node->neighbors_count == node->size)
		{
			if(node->size == 0)
			{
				node->size = 1;
			}
			else
			{
				node->size = node->size * 2;

			}

		}
		if(node->neighbors_count < node->size)
		{
			node->neighbors_count += 1;

		}
		// the node appended to end of array
		//printf("saved string %s\n", node->neighbors[node->neighbors_count - 1]->word);
		return node;
	}
	else
	{
		return NULL;
	}
	
}
TrieNode* appendTrieChain(TrieNode* root, ContextState* state, TrieNode* name)
{
	TrieNode* root_tracker = root;
	TrieNode* name_tracker = name;
	int count = 0;
	//printf("appendTrieChain\n");
	//if(root->word != NULL)
		//printf("%s\n\n", root->word);

	while(name_tracker != NULL && root_tracker != NULL)
	{
		// sometimes the final word can't be added and segfault happens
		//printf("%i\n", count);
		//printf("%s   %s\n", root_tracker->word, name_tracker->word);
		//printf("before root_tracker %i, %i\n", root_tracker->size, root_tracker->neighbors_count);

		//printf("name_tracker %x\n", name_tracker);
		//printf("about to append\n");
		// messed up before this line
		// messes up on the second x 
		// not updating root_tracker correctly

		// appending and then root gets ille
		root_tracker = appendWord(root_tracker, name_tracker->word);
		//printf("after root_tracker %i, %i\n", root_tracker->neighbors[root_tracker->neighbors_count - 1]->size, root_tracker->neighbors[root_tracker->neighbors_count - 1]->neighbors_count);
		//printTrieNodeTree(root, 1);
		//printf("appended\n");
		if(name_tracker->neighbors != NULL)
		{
			// the root has nothing to move to?

			name_tracker = name_tracker->neighbors[0];
			// go to the last one found

			root_tracker = root_tracker->neighbors[root_tracker->neighbors_count - 1];
		}
		else
		{
			//printf("problem\n");
			// no more words left to add so go to the last word added
			root_tracker = root_tracker->neighbors[root_tracker->neighbors_count - 1];
			//printf("last word %s\n", root_tracker->word);

			break;
		}
		count++;
	}
	// setting the state to the last word
	root_tracker->object = state;
	//printf("object added %x\n", root_tracker->object);
	// need to add indents and a thumbnail attribute so not all of the state is printed out

	return root;
}

// adding a ContextState to a 
void insert(TrieNode* root, ContextState* state)
{
	//printf("insert\n");
	// tracker is always pointing to root
	TrieNode* root_tracker = root;
	//printf("neighbors_count %i\n", root_tracker->neighbors_count);

	// take the name
	// search for name in the trienode
	TrieNodePackage3* last_word_index_correctly_matched_package = findInTrie2(root_tracker, state->state_name->neighbors[0]);
	/*
	typedef struct TrieNodePackage3
	{
		TrieNode* dict_trie_node;
		TrieNode* context_state_attribute_trie_node;
		bool context_state_is_found;
		bool is_partial_match;
		bool need_to_append_more_name;
	}TrieNodePackage3;
	*/

	if(last_word_index_correctly_matched_package == NULL)
	{
		// root is empty
		//printf("root is empty\n");
		// root_tracker = f(state, )
		root_tracker = appendTrieChain(root_tracker, state, state->state_name->neighbors[0]);

		//printf("last word associated with state %s\n\n", root_tracker->word);

		//printTrieNodes(root_tracker);
		//printf("\n");
		//printContextState(root_tracker->object);
		//exit(1);
		//root_tracker = appendNode(root_tracker,
		//							  getIthWord(state->state_name, 0));
	}

	else
	{
		//printf("have node data to add\n");
		// the trackers have already be adjusted acording to their situation
		TrieNode* dict_trie_node = last_word_index_correctly_matched_package->dict_trie_node;
		TrieNode* context_state_attribute_trie_node = last_word_index_correctly_matched_package->context_state_attribute_trie_node;
		//printf("%x, %x\n", dict_trie_node, context_state_attribute_trie_node);
		bool context_state_is_found = last_word_index_correctly_matched_package->context_state_is_found;
		bool need_to_append_more_name = last_word_index_correctly_matched_package->need_to_append_more_name;
		bool is_first_mismatch = last_word_index_correctly_matched_package->is_first_mismatch;

		if(!context_state_is_found)
		{
			if(need_to_append_more_name)
			{
				if(is_first_mismatch)
				{
					//printf("first mismatch\n");
					// wrong
					root_tracker = appendTrieChain(dict_trie_node, state, state->state_name->neighbors[0]);

					//printf("\n\nprint out tree\n");
					//printTrieNodeTree(root_tracker, 1);
				}
				else
				{
					//printf("2 to nth mismatch\n");

					// need to add stuff
					root_tracker = appendTrieChain(dict_trie_node, state, context_state_attribute_trie_node);
				}
				

			}
			else
			{
				//printf("add as an internal node\n");
				root_tracker = appendTrieChain(dict_trie_node, state, NULL);
			}

		}
		
	}
	
}