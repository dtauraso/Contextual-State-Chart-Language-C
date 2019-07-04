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

// binary search
// find the midpoint after the search fails
// append to the right
/*
int searchInsert(vector<int>& nums, int target) {
        
        int low = 0;
        int high = nums.size();
        while(low < high)
        {
            int mid = (low + high) / 2;
            if( nums[mid] == target)
            {
                return mid;
            }
            else if( target > nums[mid])
            {
                low = mid + 1;
            }
            else if( target < nums[mid])
            {
                high = mid - 1;
            }


        }
        if(low == nums.size())
            return nums.size();
        if(nums[low] < target) return low + 1;
        return low;
    }
*/

// searching
int computeLocation(int low,  int size,  TrieNode* node, char* target)
{
	//printf("computeLocation\n");
	//printf("low %i, size %i\n", low, size);
	// segfaults here
	//printf("%s, %s\n", node->neighbors[low]->word, target);
	// if low == 0 and size == 0
	//printf("%i\n", lessThan(node->neighbors[low]->word, target));
	//if(low == 0 && size == 0)
	// low can't be >= size
	if(low == size)
	{
		return size;
	}
	if(low < size)
	{
		// size must reflect the actual size of the array not the array before it
		if(strcmp(target, node->neighbors[low]->word) >= 0)
		{
			//printf("%i\n", low + 1);
			// don't need low + 1 because mid is set to mid + 1
			return low;
		}
	}
	
	
	
	return low;
}
bool areNeighborsNull(TrieNode* node, TrieNode* target_chain)
{
	if(node != NULL && target_chain != NULL)
	{
		if(node->neighbors == NULL)
		{
			return true;
		}
	}
	return false;
}
bool canWeSearchWithTheDataAvaliable(TrieNode* node, TrieNode* target_chain)
{
	if(node != NULL && target_chain != NULL)
	{
		if(node->neighbors != NULL && target_chain->word != NULL)
		{
			return true;
		}
	}
	return false;
}

// binsearch edge cases for matching
enum edgeCases{end_of_perfect_match, target_chain_has_more_words, can_keep_matching, state_already_exists};
int matchEdgeCases(TrieNode* node, TrieNode* target_chain)
{
	// check ahead for the possible end conditions
	// some will result in more searching
	// some are termination cases
	// can we keep going or not?

	if(node != NULL && target_chain != NULL)
	{
		if((node->neighbors != NULL && target_chain->neighbors == NULL) ||
		(node->neighbors == NULL && target_chain->neighbors == NULL)
		)
		{
			//printf("end of perfect match\n");
			// end of perfect match
			// check for state existing
			if(node->object)
			{
				//printf("state already exists\n");
				return state_already_exists;
				// if state is there
					// return state exists
			}
			return end_of_perfect_match;
		}
		// case 1 tree has nothing left to match but target chain has more words

		// canWeSearchWithTheDataAvaliable?
		if(node->neighbors == NULL && target_chain->neighbors != NULL)
		{
			//printf("target chain has more words\n");
			// target_chain_has_more_words
			return target_chain_has_more_words;
		}
		else // node->neighbors != NULL && target_chain->neighbors != NULL
		{
			//printf("can keep matching\n");
			if(target_chain->word != NULL)
				// can keep matching
				return can_keep_matching;
		}
	}
	return -1;
}
////
/*
typedef struct TrieNodePackage2
{
	TrieNode* tree_pointer;
	TrieNode* target_pointer;
	int location;
	bool state_there;
}
*/
TrieNodePackage2* makePackage(TrieNode* tree_pointer,
							 TrieNode* target_pointer,
							 int location,
							 bool state_there,
							 ContextState* object_found)
{
	TrieNodePackage2* package = malloc(sizeof(TrieNodePackage2));
	package->tree_pointer = malloc(sizeof(TrieNode));
	package->target_pointer = malloc(sizeof(TrieNode));
	package->tree_pointer = tree_pointer;
	package->target_pointer = target_pointer;

	package->location = location;
	
	package->state_there = state_there;
	//printf("%i %i\n", state_there, object_found);
	if(state_there)
	{
		package->object_found = malloc(sizeof(ContextState));
		package->object_found = object_found;
		//memcpy(package->object_found, object_found, sizeof(ContextState));

	}
	else
	{
		package->object_found = NULL;
	}

	return package;
}
TrieNodePackage2* mainBinSearch(TrieNode* node, TrieNode* target_chain)
{
	int low = 0;
	int high = node->size - 1;
	int mid = (low + high) / 2;
	TrieNode* node_tracker = node;
	TrieNode* target_chain_tracker = target_chain;
	//TrieNode* mid_node = node_tracker->neighbors[mid];
	if(node_tracker->neighbors[mid] != NULL)
	{
		//char* key;
		//char* value;
		//printf("low and high\n");
		while(low <= high)
		{
			//key = mid_node->word;
			//value = target_chain_tracker->word;
			//printf("%i, %i\n", low, high);

			int is_less_than = strcmp(target_chain_tracker->word,
									  node_tracker->neighbors[mid]->word);
			// key is always the same
			// still not always finding the correct location to insert
			//printf("target %s, tree %s\n", target_chain_tracker->word,
			//							   node_tracker->neighbors[mid]->word);
			//printf("%i\n", mid);
			if(strcmp(target_chain_tracker->word,
				      node_tracker->neighbors[mid]->word) == 0)
			{
				// deal with match
				// check ahead for conditions
				// 

				int edge_case_result = matchEdgeCases(node_tracker, target_chain_tracker);
				//printf("edge case result %i\n", edge_case_result);
				/*
				is the state there?
					don't add
				else
					if chain is null
						add in state
					else

						add chain in and state
				*/
				if(end_of_perfect_match == edge_case_result)
				{
					//printf("end_of_perfect_match\n");
					// (tree_pointer, null, mid, !state_there)
					return makePackage(node_tracker, NULL, mid, 1, node_tracker->neighbors[mid]->object);
				}
				else if(target_chain_has_more_words == edge_case_result)
				{
					//printf("target_chain_has_more_words\n");
					//printf("mid %i\n", mid);
					// (tree_pointer, target_pointer, mid, !state_there)
					return makePackage(node_tracker, target_chain_tracker, mid, 0, NULL);
				}
				else if(can_keep_matching == edge_case_result)
				{
					//printf("can_keep_matching\n");
					// update the locations

					// reset the values mid, low, high
					// advance the pointers
					//node_tracker = mid_node;
					node_tracker = node_tracker->neighbors[mid];

					target_chain_tracker = target_chain_tracker->neighbors[0];
					low = 0;
					high = node_tracker->size;

					mid = (low + high) / 2;
					// low and high == 0

					//key = mid_node->word;
					//value = target_chain_tracker->word;

					// can keep matching but not mid node neighbor, so target_chain_has_more_words
					if(node_tracker == NULL || node_tracker->size == 0)
					{
						// return what we have
						// (tree_pointer, target_pointer, mid, !state_there)
						return makePackage(node_tracker, target_chain_tracker, mid, 0, NULL);
					}

					
				}
				else //if(state_already_exists)
				{
					//printf("state_already_exists\n");
					// (tree_pointer, target_pointer, 0, state_there)
					return makePackage(node_tracker, target_chain_tracker, 0, 1, node_tracker->neighbors[mid]->object);
				}

			}
			else if(is_less_than < 0)
			{
				//printf("is_less_than\n");
				high = mid - 1;
				mid = (low + high) / 2;
			}
			else if(is_less_than >= 0)
			{
				//printf("!is_less_than\n");
				low = mid + 1;
				mid = (low + high) / 2;
				//printf("%i, %i, %i\n", high, mid, low);
			}
			
			
			
		}
		//printf("finding location\n");
		// can't use the size of the original array
		int location_of_insert = computeLocation(low, node_tracker->size, node_tracker, target_chain->word);
		//printf("location of insert %i\n", location_of_insert);
		// we have the location of item
		// can't be put before any words similar to item at location
		// "item", "items"
		// must go after items not item
		// should be alot less linear search space than if binsearch is not used
		// if mostly random then O(logn)
		// 
		if(location_of_insert < node_tracker->size)
		{

			while(strcmp(target_chain_tracker->word,
						 node_tracker->neighbors[location_of_insert]->word) > 0)
			{
				location_of_insert++;
			}
		}
		// return state of pointers where the new name part will be added
		// (tree_pointer, target_pointer, location_of_insert, !state_there)
		return makePackage(node_tracker, target_chain_tracker, location_of_insert, 0, NULL);
		
	}
	else
	{
		return NULL;
	}
}
TrieNodePackage2* binSearch(TrieNode* node, TrieNode* target_chain)
{
	//printf("binSearch\n");
	// need to record each location of the match and the size
	// we may be able to make at least 1 match
	// canWeSearchWithTheDataAvaliable has already been done
	if(canWeSearchWithTheDataAvaliable(node, target_chain))
	{
		int largest_size;
		int location_of_insert = 0;
		if(node->size == 0)
		{
			largest_size = 0;
		}
		else
		{
			largest_size = node->size;
		}
		// target < first word
		if(strcmp(target_chain->word, node->neighbors[0]->word) < 0)
		{
			//printf("done 0\n");
			location_of_insert = 0;
			return makePackage(node,
							   target_chain,
							   location_of_insert,
							   0, NULL);
		}
		// target > last word
		else if(strcmp(target_chain->word,
					   node->neighbors[largest_size - 1]->word) > 0)
		{
			//printf("done %i\n", node->size);
			location_of_insert = node->size;
			return makePackage(node,
							   target_chain,
							   location_of_insert,
							   0, NULL);
		}
		return mainBinSearch(node, target_chain);
		
	}
	else
	{
		return NULL;
	}
	
}
// f(TrieNode* node, TrieNode* target_chain, ContextState* target_state, int insert_location)
TrieNodePackage2* searchForInsertId(TrieNode* node,
								    TrieNode* target_chain,
								    ContextState* target_state)
{
	// made no assumptions on if the pointers are null
	// O(longest list of strings)
	// return 0 if can't find the state
	// return -1 if it will not be able to insert the state
	// return 1 if state was inserted

	// what is returned
	// tree node where any new nodes are to be inserted
	// the target_chain pointer where the new nodes to the tree will be copied
	// the contextstate to be added to the last tree node
	// the index of where to insert the first new node to the neighbors
	// is_found
	// has_neighbors

	// can we do any searching?
		// is there anything to check the target with?
			// no, so can't find anthing at this point
		// is there data we can use to search?
			// binSearch loop
				// we can search and there are neighbors we can check on and the target word exists
				// does the midpoint exist?
					// is there a match?
						// move the pointers up by 1
						// ask if we can search and there are neighbors we can check on and the target word exists
	// can we check the target with neighbors?
	// can we search with the data avaliable?
		// binSearchLoop
			// does the midpoint exist?
				// is there a match?
					// can we check the target with neighbors?
					// can we search with the data avaliable?
	// sanity check
		// search
			// midpoint check
				// if match
					// sanity check for the next searching round
	//TrieNode* node_tracker = node;
	//TrieNode* target_chain_tracker = target_chain;
	if(areNeighborsNull(node, target_chain))  // are we at base case?
	{
		// there are no nodes in neighbor
		//printf("this case\n");
		return makePackage(node, target_chain, 0, 0, NULL);
	}
	
	TrieNodePackage2* result = binSearch(node, target_chain);

	return result;



}
////
// inserting
TrieNode* setTrieNode(TrieNode* b)
{
	TrieNode* a = malloc(sizeof(TrieNode));

	//char* word;
	a->word = malloc(sizeof(char) * (strlen(b->word) + 1));
	memcpy(a->word, b->word, sizeof(char) * (strlen(b->word)));
	a->word[strlen(b->word)] = '\0';

	struct TrieNode** neighbors = NULL;
	//a->neighbors = malloc(sizeof(TrieNode*) * b->size);
	//memcpy(a->neighbors, b->neighbors, sizeof(TrieNode*) * b->size);

	//int neighbors_count;
	a->neighbors_count = 0;//b->neighbors_count;
	a->size = 0;//b->size;

	//int size; // power of 2
	struct ContextState* object;
	if(b->object != NULL)
	{
		a->object = malloc(sizeof(ContextState));
		memcpy(a->object, b->object, sizeof(ContextState));
	}
	else
	{
		a->object = NULL;
	}
	return a;
}

TrieNode* copyTrieNode(TrieNode* b)
{
	TrieNode* a = malloc(sizeof(TrieNode));

	//char* word;
	a->word = malloc(sizeof(char) * (strlen(b->word) + 1));
	memcpy(a->word, b->word, sizeof(char) * (strlen(b->word)));
	a->word[strlen(b->word)] = '\0';

	struct TrieNode** neighbors;
	a->neighbors = malloc(sizeof(TrieNode*) * b->size);
	memcpy(a->neighbors, b->neighbors, sizeof(TrieNode*) * b->size);

	//int neighbors_count;
	a->neighbors_count = b->neighbors_count;
	a->size = b->size;

	//int size; // power of 2
	struct ContextState* object;
	if(b->object != NULL)
	{
		a->object = malloc(sizeof(ContextState));
		memcpy(a->object, b->object, sizeof(ContextState));
	}
	else
	{
		a->object = NULL;
	}
	return a;
}
int distance(int pos, int size)
{
	// memcpy memory scalar
	return size - pos;
}
TrieNode* newTrieNode()
{
	TrieNode* new_trie_node = malloc(sizeof(TrieNode));
	new_trie_node->word = NULL;
	new_trie_node->neighbors = NULL;
	new_trie_node->neighbors_count = 0;
	new_trie_node->size = 0;
	new_trie_node->object = NULL;
	return new_trie_node;
}
TrieNode** newTrieNodes(char* word, int location, int neighbor_count)
{
	if(neighbor_count > location)
	{
		TrieNode** new_neighbors = malloc(sizeof(TrieNode*) * neighbor_count);
		for(int i = 0; i < location; i++)
		{
			new_neighbors[i] = newTrieNode();
		}
		new_neighbors[location] = malloc(sizeof(TrieNode));
		new_neighbors[location]->word = malloc(sizeof(char) * (strlen(word) + 1) );
		new_neighbors[location]->neighbors = NULL;
		new_neighbors[location]->size = 0;
		new_neighbors[location]->neighbors_count = 0;
		new_neighbors[location]->object = NULL;
		for(int i = location + 1; i < neighbor_count; i++)
		{
			new_neighbors[i] = newTrieNode();
		}

		return new_neighbors;
	}
	return NULL;
	

}
TrieNode** insertItem(int pos, TrieNode* node, TrieNode* value)
{
	//printf("insert item nod's size %i\n", node->size);
	int size = node->size;
	TrieNode** new_neighbors = newTrieNodes(node->word, pos, size + 1);

	// need to actually add the word in
	// still doesn't copy the word in correctly
	//printf("word to add %s  %lu\n", value->word, strlen(value->word));

	//memcpy(new_neighbors[pos]->word,
		//		value->word,
		//		sizeof(char) * (strlen(value->word)));
	//new_neighbors[pos]->word[strlen(value->word)] = '\0';
	//printf("word added %s  %i\n", new_neighbors[pos]->word,
	//	strlen(new_neighbors[pos]->word));

	//printf("post %i, size %i\n",pos, size);
	// make new array
	// copy the below part from old array to new array
	// copy left and right halves

	int copy_left_size = 0;
	int copy_right_size = 0;
	if(pos < size)
	{

		if(size == 1)
		{
			// [0, size)
			copy_right_size = distance(0, size);

		}
		else if(size > 1)
		{
			// [0, pos), [pos, size)
			copy_left_size = distance(0, pos);
			copy_right_size = distance(pos, size);
		}
	}
	else if(pos == size)
	{
		if(size == 1)
		{
			//printf("base case\n");
			// [0, 0]
			copy_left_size = 1;//distance(0, 0);
		}
		else if(size > 1)
		{
			// [0, pos)
			copy_left_size = distance(0, pos);
		}
	}
	// may need to put more in here
	//printf("left %i, right %i pos %i\n", copy_left_size, copy_right_size, pos);
	// need separate cases for size== 1
	// can't have them in the combined choices part
	// adding in an extra item
	if(size == 1)
	{
		if(copy_left_size > 0)
		{
			//printf("base case left\n");
			// pos 1 was the insert location
			new_neighbors[0] = copyTrieNode(node->neighbors[0]);
			//memcpy(new_neighbors[0], node->neighbors[0], sizeof(TrieNode));

		}
		else if(copy_right_size > 0)
		{
			//printf("base case right\n");
			// pos 0 was the insert location
			new_neighbors[pos] = setTrieNode(value);

			new_neighbors[1] = copyTrieNode(node->neighbors[0]);
			//memcpy(new_neighbors[1], node->neighbors[0], sizeof(TrieNode));
			//printf("word after shift %s pos %i\n", new_neighbors[pos]->word, pos);


		}
		//memcpy(new_neighbors[pos]->word,
		//		value->word,
		//		sizeof(char) * (strlen(value->word)));
	//new_neighbors[pos]->word[strlen(value->word)] = '\0';

	}
	else
	{
		if(copy_left_size > 0)
		{
			//printf("copy left size %i\n", copy_left_size);
			
			for(int i = 0; i < copy_left_size; i++)
			{
				//printf("%i\n", i);
				//printf("%i th object %x\n", i, new_neighbors[i]);
				new_neighbors[i] = copyTrieNode(node->neighbors[i]);
				//memcpy(new_neighbors[i], node->neighbors[i], sizeof(TrieNode));
				//printf("%s\n", new_neighbors[i]->word);
			}

		}
		new_neighbors[pos] = setTrieNode(value);

		//memcpy(new_neighbors[pos]->word,
		//		value->word,
		//		sizeof(char) * (strlen(value->word)));
	//new_neighbors[pos]->word[strlen(value->word)] = '\0';
		if(copy_right_size > 0)
		{
			//printf("copy right size %i\n", copy_right_size);
			
			for(int i = copy_left_size; i < size; i++)
			{
				// + 1 needs to go somewhere else
				new_neighbors[i + 1] = copyTrieNode(node->neighbors[i]);
				//memcpy(new_neighbors[i + 1], node->neighbors[i], sizeof(TrieNode));
				//printf("%s\n", new_neighbors[i]->word);

			}
		
			
		}

	}
	
	return new_neighbors;
}



bool insert1Item(TrieNode* node, TrieNode* target_chain, int location)
{
	// insert a new word at node's neighbors
	//printf("here\n");
	if(node->neighbors == NULL)
	{
		
		node->neighbors = newTrieNodes(target_chain->word, 0, 1);
		/*malloc(sizeof(TrieNode*));
		node->neighbors[0] = malloc(sizeof(TrieNode));
		node->neighbors[0]->word = malloc(sizeof(char) * strlen(target_chain->word));
		node->neighbors[0]->neighbors = NULL;
		node->neighbors[0]->size = 0;
		node->neighbors[0]->neighbors_count = 0;
		node->neighbors[0]->object = NULL;
		node->size = 1;
		*/
		node->size = 1;
		
		memcpy(node->neighbors[0]->word,
				target_chain->word,
				sizeof(char) * strlen(target_chain->word));
		
		//printf("added %s\n", node->neighbors[0]->word);
		return true;
	

	}
	// call insert for all remaining sizes
	else
	{
		//printf("inserting items\n");
		//printf("1 insert item nod's size %i\n", node->size);

		TrieNode** new_neighbors = insertItem(location, node, target_chain);
		//printf("word saved %s\n", new_neighbors[location]->word);
		//printf("word saved %s\n", new_neighbors[1]->word);


		free(node->neighbors);
		node->neighbors = new_neighbors;
		node->size++;
		//printf("word saved %s\n", node->neighbors[0]->word);
		//printf("word saved %s\n", node->neighbors[1]->word);

		return true;
	}
	/*else if(node->size == 1)
	{
		printf("should add in here\n");
		// location == 1 or 0
	}
	else if(node->size == 2)
	{

	}*/
}
// will need to look out for this function as the visitor function is made
int insert2(TrieNode* node, TrieNode* target_chain, ContextState* target_state)
{
	printf("\ninserting name\n");
	printTrieNodes(target_chain);
	// only returns the deepest location, not all locations 
	TrieNodePackage2* result = searchForInsertId(node, target_chain, target_state);
	//printTrieNodes(result->target_pointer);
	if(result != NULL)
	{
		//printf("got here\n");
		if(result->state_there)
		{
			printf("already added\n");
			// don't add
		}
		else if(result->target_pointer == NULL)
		{
			// add in state
		}
		else
		{
			// adding same names
			//printf("null stuff\n");
			/*printf("printing tree before\n");

			printTrieNodeTree(node, 1);

			printf("%i\n", result->tree_pointer->size);
			*/
			int count = 0;
			int insert_location = result->location;
			while(result->target_pointer != NULL)
			{
				//printf("count %i\n", count);
				// save the names
				// insert1Item will run case null at the 2nd to nth iterations
				// result location is only meaningfull for the first round because all other inserts are increasing the size to 1
				insert1Item(result->tree_pointer, result->target_pointer, insert_location);
				/*printf("item has been added !!!!!\n");
				printf("printing tree\n");
				printTrieNodeTree(node, 1);
				printf("\n");
				*/

				if(result->tree_pointer->neighbors != NULL &&
					result->target_pointer->neighbors != NULL)
				{
					//printf("advance\n");
					result->tree_pointer = result->tree_pointer->neighbors[insert_location];
					result->target_pointer = result->target_pointer->neighbors[0];
					count++;

				}
				else
				{
					// save the object
					//printf("save object\n");
					result->tree_pointer->neighbors[insert_location]->object = target_state;
					break;
				}
				insert_location = 0;


			}
			// claims the state exists but can't find it
			//printf("done\n");
			TrieNodePackage2* result2 = searchForInsertId(node, target_chain, target_state);
			if(result2 != NULL)
			{
				if(result2->object_found)
				{
					printf("found name\n");
					printTrieNodeTreeFlat(result2->object_found->state_name);
					printf("\n\n");

					//printContextState(result2->object_found);
				}
				//printf("location: %i\n", result->location);

			}
			//printf("\nprinting tree\n");
			//printf("%i %x\n",result2->state_there,  result2->object_found);
			//printTrieNodeTree(node, 1);
			//printf("\n");
			
			// add chain in and state
			return 1;//insert1Item(result->tree_pointer, result->target_pointer, result->location);
			//return -1;
		}

	}

	
	return -1;
	
	/*
	is the state there?
		don't add
	else
		if chain is null
			add in state
		else

			add chain in and state
	*/
}
//////
