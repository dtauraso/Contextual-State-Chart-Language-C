#include "trie_node.h"
#include "jsmn/jsmn.h"

enum token_types {_primitive, _object, _array, _string};
enum data_types{is_list, is_string, is_empty_case};
/// state functions for testing visitor function
bool returnTrue(ContextState* current_state)
{
	printf("return true\n");
	return true;
}
bool returnFalse(ContextState* current_state)
{
	printf("return false\n");
	return false;
}

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
	//printf("b word %s\n", b->word);
	//int size = strlen(b->word);
	//printf("%i\n", size);
	a->word = copyString(b->word);
	//printf("%s\n", a->word);

	//a->word = malloc(sizeof(char) * (size));
	//memcpy(a->word, b->word, sizeof(char) * size);
	//a->word[size] = '\0';

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
	a->word = copyString(b->word);
	//printf("%s\n", a->word);
	//a->word = malloc(sizeof(char) * (strlen(b->word) + 1));
	//memcpy(a->word, b->word, sizeof(char) * (strlen(b->word)));
	//a->word[strlen(b->word)] = '\0';

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
		new_neighbors[location]->word = NULL;//malloc(sizeof(char) * (strlen(word) + 1) );
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
			new_neighbors[1] = setTrieNode(value);
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
		
		node->neighbors[0]->word = copyString(target_chain->word);

		/*memcpy(node->neighbors[0]->word,
				target_chain->word,
				sizeof(char) * strlen(target_chain->word));
		*/
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
void setFunction(ContextState* state)
{
	if(strcmp(state->function_pointer_name, "\"returnTrue\"") == 0)
	{
		state->function_pointer = returnTrue;
		//printf("testing function\n");
		//state->function_pointer(state);

	}
	else if(strcmp(state->function_pointer_name, "\"returnFalse\"") == 0)
	{
		state->function_pointer = returnFalse;
		//printf("testing function\n");
		//state->function_pointer(state);

	}
}
// will need to look out for this function as the visitor function is made
int insert2(TrieNode* node, TrieNode* target_chain, ContextState* target_state)
{
	printf("\ninserting name\n");
	printTrieNodes(target_state->state_name->neighbors[0]);
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
					printf("save object\n");
					result->tree_pointer->neighbors[insert_location]->object = target_state;
					//printTrieNodeTreeFlat(result->tree_pointer->neighbors[insert_location]->object->state_name->neighbors[0]);

					setFunction(result->tree_pointer->neighbors[insert_location]->object);
					result->tree_pointer->neighbors[insert_location]->object->function_pointer(target_state);
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
					printTrieNodeTreeFlat(result2->object_found->state_name->neighbors[0]);
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
Tokens* makeTokens(jsmntok_t tokens[], const char* input, int total_tokens)
{
	Tokens* my_tokens = malloc(sizeof(Tokens));
	my_tokens->i = 0;
	my_tokens->_tokens = malloc(sizeof(jsmntok_t));
	my_tokens->_tokens = tokens;
	my_tokens->input = malloc(sizeof(const char));
	my_tokens->input = input;
	my_tokens->current_token = tokens[0];
	my_tokens->total_tokens = total_tokens;
	return my_tokens;
	//int i;
	//const char* input;
	//jsmntok_t* _tokens;
}
jsmntok_t getToken(Tokens* my_tokens)
{
	return my_tokens->current_token;
}
jsmntok_t getIthToken(Tokens* my_tokens, int i)
{
	return my_tokens->_tokens[i];
}
const char* getInput(Tokens* my_tokens)
{
	return my_tokens->input;
}
int getI(Tokens* my_tokens)
{
	return my_tokens->i;
}
void advanceToken(Tokens* my_tokens)
{
	int i = my_tokens->i;
	i++;
	my_tokens->current_token = my_tokens->_tokens[i];
	my_tokens->i = i;
}
jsmntok_t lookAhead(Tokens* my_tokens)
{
	int i = my_tokens->i;
	return my_tokens->_tokens[i+1];
}
bool noTokensLeft(Tokens* my_tokens)
{
	return my_tokens->i >= my_tokens->total_tokens;
}

void addTrieNodeItem(Tokens* my_tokens, TrieNode* root)
{

	if(my_tokens != NULL && root != NULL)
	{
		char* current_string = collectChars(getToken(my_tokens), getInput(my_tokens));
		
		root->word = copyString(current_string);
		//int current_string_size = sizeof(char) * (strlen(current_string) + 1);
		//printf("here %i\n", j);
		//printf("here 2 %i\n", root->size);
		//printf("here 3 %x\n", root->neighbors[0]);

		//root->word = malloc(current_string_size);
		//memcpy(root->word, current_string, current_string_size);
		
		free(current_string);
	}
		


	

}
void stringFinger(Tokens* my_tokens,
				  int second_size, 
				  TrieNode* root,
				  int j)
{

	/*
	set root->neighbors[0]
	current = root->neighbors[0]


	loop: [0, # of strings - 1]
		add item to current
		make new slot
		set current->neighbors[0]
		set new slot to current->neighbors[0]
		current = current->neighbors[0]
	*/
	//printf("string finger\n");

	// [0, # of strings - 1]
	// 1 string finger
	root->neighbors[j] = initTrieNode();
	root->neighbors[j]->size = 1;
	root->object = NULL;
	TrieNode* current = root->neighbors[j];
	//printf("# of strings %i\n", second_size);
	for(int i = 0; i < second_size; i++)
	{
		/*
		add item to current
		advance token
		make new slot
		set current->neighbors[0]
		set new slot to current->neighbors[0]
		current = current->neighbors[0]
		*/
		//printf("%i\n", i);
		addTrieNodeItem(my_tokens, current);
		//printf("%s\n", root->neighbors[j]->word);

		//printf("here rr\n");
		//printf("token before: %s\n", collectChars(getToken(my_tokens), getInput(my_tokens)));
		//printf("saved %s\n", current->word);
		advanceToken(my_tokens);
		//		printf("here\n");
		if(i == second_size - 1)
		{
			//printf("done\n");
			current->neighbors = NULL;
			current->size = 0;

			current->neighbors_count = 0;
			break;
		}
		//printf("token after: %s\n", collectChars(getToken(my_tokens), getInput(my_tokens)));

		TrieNode* next = malloc(sizeof(TrieNode));
		next->size = 1;
		next->object = NULL;
		//printf("here 3\n");

		current->neighbors = malloc(sizeof(TrieNode*));
		current->neighbors[0] = next;
		//		printf("here 4\n");

		current = current->neighbors[0];



	}
	/*
	TrieNode* tracker = root;
	//printf("first one \n %x\n", root->neighbors[j]->word);

	int k = j;
	printf("printing finger|\n");
	for(int i = 0; i < second_size; i++)
	{
		//printf("j %i\n", k);
		printf("%s\n", tracker->neighbors[k]->word);
		if(i < second_size - 1)
		{
			k = 0;
			tracker = tracker->neighbors[k];

		}
	}
	printf("|\n");
	*/
	
}
TrieNode* makeTrieTree(Tokens* my_tokens)
{
	// check for array type first
	// make test cases for this function
	// first token should be the most outer list
	int size = getToken(my_tokens).size;
	// make dummy TrieNode with no neighbors
	TrieNode* root = initTrieNode();

	if(size == 0)
	{
		// []
		advanceToken(my_tokens);
		//printf("[]\n");
		return root;
	}
	else
	{
		// [stuff]
		/*
		at [names]_1 token
		make a chain out of stuff and the next token in caller is [names]_2

		*/
		jsmntok_t next_token = lookAhead(my_tokens);
		//advanceToken(my_tokens);  // going in from outer array
		//printf("scanning a finger\n");
		//printf("second size %i\n", second_size);
		advanceToken(my_tokens);
		root->neighbors = malloc(sizeof(TrieNode*) * size);
		root->size = size;

		if(next_token.type == _string)
		{
			// 1 string finger
			// stringFinger(my_tokens, current, next, second_size)
			stringFinger(my_tokens, size, root, 0);


		}
		else if(next_token.type == _array)
		{

			// current token is at the inner array

			// string fingers
			for(int i = 0; i < size; i++)
			{
				root->neighbors[i] = initTrieNode();
				root->neighbors[i]->size = 1;
				int second_size = getToken(my_tokens).size;
				//printf("string finger\n");
				advanceToken(my_tokens);

				//printf("%s\n", collectChars(getToken(my_tokens), getInput(my_tokens)));
				stringFinger(my_tokens, second_size, root, i);
			}
		}
		/*
		TrieNode* tracker = root;
		printf("root size %i\n", root->size);
		//printf("first one \n %x\n", root->neighbors[j]->word);
		for(int m = 0; m < root->size; m++)
		{
			TrieNode* finger_tracker = tracker->neighbors[m];
			printf("printing finger|\n");

			while(finger_tracker != NULL)
			{
				printf("%s\n", finger_tracker->word);
				if(finger_tracker->neighbors != NULL)
				{
					finger_tracker = finger_tracker->neighbors[0];

				}
				else
				{
					finger_tracker = NULL;
				}
			}
			printf("\n\n");
		}
		
		printf("|\n");
		*/
		return root;

		
	}
}
//////
void visitor(ContextState* start, ContextState* end)
{


}