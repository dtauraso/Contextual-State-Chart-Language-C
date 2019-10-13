#include "trie_node.h"
#include "jsmn/jsmn.h"

enum token_types {_primitive, _object, _array, _string};
enum data_types{is_list, is_string, is_empty_case};
/// state functions for testing visitor function
void deleteContextState(ContextState* state);
char* surroundByQuotes(char* word_from_input);

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
void deleteTrieNode(TrieNode* node)
{
	printf("deleteTrieNode %x\n", (unsigned int) node);
	// the node still has a presence but it's size is not accessible
	// it might not exist in the heap
	if(node != NULL)
	{
		printf("neighbors size\n");
		printf("%i\n", node->size);
		if(node->size > 0)
		{
			for(int i = 0; i < node->size; i++)
			{
				printf("%i\n", i);
				if(node->neighbors[i] != NULL)
				{
					deleteTrieNode(node->neighbors[i]);

				}
			}
		}
		if(node->neighbors != NULL)
		{
			// we are in trouble
			// size should correspond to the actual size of node->neighbors
		}
		if(node->word)
		{
			printf("about to delete name\n%s\n", node->word);
			free(node->word);
			node->word = NULL;

		}
		if(node->object)
		{
			deleteContextState(node->object);
			node->object = NULL;

		}
		free(node);
		node = NULL;
		printf("done deleting TrieNode\n");
	}
	else
	{
		printf("done deleting TrieNode\n");

	}

	
}
void printStateName(TrieNode* root)
{

	TrieNode* tracker = root;
	//printf("root size %i\n", root->size);
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
		printf("--------\n");
	}
	
	printf("|\n");
}

// each function consuming tokens advance the index
// to the token for the next function

// binary search
// find the midpoint after the search fails
// VectorAppend to the right
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
enum edgeCases{end_of_perfect_match, target_chain_has_more_words, can_keep_matching};
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
							 bool is_perfect_match)
{
	TrieNodePackage2* package = malloc(sizeof(TrieNodePackage2));
	package->tree_pointer = malloc(sizeof(TrieNode));
	package->target_pointer = malloc(sizeof(TrieNode));
	package->tree_pointer = tree_pointer;
	package->target_pointer = target_pointer;

	package->location = location;
	
	package->is_perfect_match = is_perfect_match;
	//printf("%i %i\n", state_there, object_found);

	return package;
}
TrieNodePackage2* mainBinSearch(TrieNode* node, TrieNode* target_chain)
{
	//printf("mainBinSearch\n");
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

		/* prevents the next midpoint from overaccessing*/
		while(low <= high && mid < node_tracker->size)
		{
			//key = mid_node->word;
			//value = target_chain_tracker->word;
			//printf("%i, %i\n", low, high);

			//printf("%i, %i\n", mid, node->size);

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
				// (tree_pointer, name_pointer, location, if_perfect_match)
				if(end_of_perfect_match == edge_case_result)
				{
					//printf("end_of_perfect_match\n");
					// only care about getting to the node with the final match
					// the contents of the state is not relevant 
					// (tree_pointer, null, mid, !state_there)
					// more accurate to what is going on but a problem(can add but can't find)
					return makePackage(node_tracker, NULL, mid, 1);
				}
				else if(target_chain_has_more_words == edge_case_result)
				{
					//printf("target_chain_has_more_words\n");
					//printf("mid %i\n", mid);
					// (tree_pointer, target_pointer, mid, !state_there)
					return makePackage(node_tracker, target_chain_tracker, mid, 0);
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
						return makePackage(node_tracker, target_chain_tracker, mid, 0);
					}

					
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
		// take to the last word that would match so the insert is ahead of all words less than the target
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
		return makePackage(node_tracker, target_chain_tracker, location_of_insert, 0);
		
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
		//printf("search word %s\n", target_chain->word);

		//printf("largest word %s\n", node->neighbors[largest_size - 1]->word);
		// target < first word
		if(strcmp(target_chain->word, node->neighbors[0]->word) < 0)
		{
			//printf("done 0\n");
			location_of_insert = 0;
			return makePackage(node,
							   target_chain,
							   location_of_insert,
							   0);
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
							   0);
		}
		//printf("got here\n");
		return mainBinSearch(node, target_chain);
		
	}
	else
	{
		return NULL;
	}
	
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
// f(TrieNode* node, TrieNode* target_chain, ContextState* target_state, int insert_location)
TrieNodePackage2* searchForInsertId(TrieNode* node,
								    TrieNode* target_chain)
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
		return makePackage(node, target_chain, 0, 0);
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
		new_neighbors[location]->word = NULL;// malloc(sizeof(char) * (strlen(word) + 1) ) will be used elsewhere
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
/*
delete
	size == 1
		erase element and object
	size > 1
		element is at left side
			shift remainder of array 1 to the left

		element is at right side
			make new array 1 shorter

		element is in middle
			shift remainder of array 1 to the left

*/
int intervaleDistance(int low, int high)
{
	if(low == 0)
		return high - low + 1;
	return high - low;
}

TrieNode** grabBlockOfNeighbors(TrieNode** neighbors, int offset, int interval_distance)
{
	int size_to_grab = sizeof(TrieNode*) * interval_distance;
	//printf("size %i\n", size_to_grab/sizeof(TrieNode*));
	TrieNode** new_neighbors = malloc(size_to_grab);
	memcpy(new_neighbors, neighbors + offset, size_to_grab);
	return new_neighbors;
}
void deleteNeighbors(TrieNode* node)
{
	for(int i = 0; i < node->neighbors_count; i++)
	{
		deleteTrieNode(node->neighbors[i]);
	}
	free(node->neighbors);
	node->neighbors = NULL;
}
void deleteElement(TrieNode* node, int pos)
{

	// deletes node->neighbors[pos]
	TrieNode* element = node->neighbors[pos];

	int number_of_elements = node->size;
	if(number_of_elements == 1)
	{
		// erase element
		deleteTrieNode(element);
		free(node->neighbors);
		node->neighbors = NULL;
		node->size = 0;
		node->neighbors_count = 0;
	}
	else
	{
		int end = number_of_elements - 1;
		// need to delete the object too(need a delete for context state)
		// call delete(object)
		// element is at pos == 0
		if(pos == 0)
		{
			int sizeof_A = intervaleDistance(1, end + 1);
			//printf("%i %i, %i\n", 1, end, sizeof_A);
			TrieNode** new_neighbors = grabBlockOfNeighbors(node->neighbors, 1, sizeof_A);
			/*
			printf("neighbors A left\n");
			for(int i = 0; i < sizeof_A; i++)
			{
				printf("%s\n", new_neighbors[i]->word);
			}
			*/
			deleteNeighbors(node);
			node->neighbors = NULL;
			node->neighbors = malloc(sizeof(TrieNode*) * (number_of_elements - 1));
			for(int i = 0; i < sizeof_A; i++)
			{
				node->neighbors[i] = new_neighbors[i];
			}
			node->size -= 1;
			node->neighbors_count -= 1;
			//node->neighbors = new_neighbors;
		}
		/*
			make copy of neighbors 1 length shorter(pos 1 to end)
			erase current neighbors
		*/
		// element is at pos == end
		else if(pos == end)
		{
			int sizeof_A = intervaleDistance(pos, end - 1);

			TrieNode** new_neighbors = grabBlockOfNeighbors(node->neighbors, pos, sizeof_A);
			deleteNeighbors(node);
			node->neighbors = NULL;
			node->neighbors = malloc(sizeof(TrieNode*) * (number_of_elements - 1));
			for(int i = 0; i < sizeof_A; i++)
			{
				node->neighbors[i] = new_neighbors[i];
			}
			node->size -= 1;
			node->neighbors_count -= 1;

		}
		/*
			make copy of neighbors 1 length shorter(start to end - 1)
			erase current neighbors

		*/
		// else
		else
		{
			// it actually erased something but it was not the name picked to erase
			// ranges appear to be wrong
			// first slice appears to be right
			int sizeof_A = intervaleDistance(0, pos - 1);

			//printf("%i %i, %i\n", 0, pos - 1, sizeof_A);
			int sizeof_B = intervaleDistance(pos + 1, end + 1);

			//printf("%i %i, %i\n", pos + 1, end, sizeof_B);
			TrieNode* test_node = initTrieNode();
			TrieNode** new_neighbors_A = grabBlockOfNeighbors(node->neighbors, 0, sizeof_A);
			/*
			printf("neighbors A\n");
			for(int i = 0; i < sizeof_A; i++)
			{
				printf("%s\n", new_neighbors_A[i]->word);
			}
			*/
			//printf("%s\n", new_neighbors_A[9]->word);

			test_node->neighbors = new_neighbors_A;



			TrieNode** new_neighbors_B = grabBlockOfNeighbors(node->neighbors, pos + 1, sizeof_B);
			/*
			printf("neighbors B\n");
			for(int i = 0; i < sizeof_B; i++)
			{
				printf("%s\n", new_neighbors_B[i]->word);
			}
			*/
			deleteNeighbors(node);
			node->neighbors = NULL;
			//printf("neighbors left %i\n", node->neighbors);
			node->neighbors = malloc(sizeof(TrieNode*) * (number_of_elements - 1));
			for(int i = 0; i < sizeof_A; i++)
			{
				node->neighbors[i] = new_neighbors_A[i];
			}
			//memcpy(node->neighbors, new_neighbors_A, sizeof_A);
			
			/*
			printf("neighbors A left\n");
			for(int i = 0; i < sizeof_A; i++)
			{
				printf("%s\n", new_neighbors_A[i]->word);
			}
			

			printf("neighbors B left\n");

			for(int i = 0; i < sizeof_B; i++)
			{

				printf("%i%s\n", i, new_neighbors_B[i]->word);
			}
			*/
			for(int i = 0; i < sizeof_B; i++)
			{
				node->neighbors[i + sizeof_A] = new_neighbors_B[i];
			}

			//memcpy(node->neighbors + sizeof_A, new_neighbors_B, sizeof(TrieNode*) * sizeof_B);
			/*
			printf("%i\n", number_of_elements - 1);
			for(int i = 0; i < number_of_elements - 1; i++)
			{
				printf("%s\n", node->neighbors[i]->word);

			}
			*/
			node->size -= 1;
			node->neighbors_count -= 1;
			//printf("test_node\n");
			//printTrieNodes(test_node);

			//printf("\n\n");
		}
		/*
			make copy of neighbors from pos + 1 to end(B)(save size)
			make copy of neighbors from start to pos - 1(A)(save size)
			erase current neighbors

			merge A and B with new neighbors of size = old size - 1
		*/

	}
	
}

//delete2(dict, state->state_name->neighbors[0], state)
int delete2(TrieNode* node, TrieNode* target_chain, ContextState* target_state)
{
	// ContextState* target_state only used to set to the state after being found or made
	printf("deleting name\n");
	printTrieNodes(target_state->state_name->neighbors[0]);
	TrieNodePackage2* result = searchForInsertId(node, target_chain);
	//printTrieNodes(result->target_pointer);
	if(result != NULL)
	{

		//printf("got here\n");
		if(result->is_perfect_match)
		{
			if(result->tree_pointer != NULL)
			{
				TrieNode* node1 = result->tree_pointer;
				int mid = result->location;
				TrieNode* neighbor = node1->neighbors[mid];
				if(neighbor != NULL)
				{
					// delete neighbor
					deleteElement(node1, mid);
					return 1;
				}
				else
				{
					// can't do anything
				}
				//printf("already added\n");
				// don't add
			}
			
		}
	}
	
	return 0;
	
}




// cases for slicing operations
//enum slicing_cases{};
// do I need separate cases for insert vs delete?
// perhaps a enum state machine?

bool posLessThanSizeAndSizeIs1(int pos, int size)
{
	return pos < size && size == 1;
}
bool posLessThanSizeAndSizeGreaterThan1(int pos, int size)
{
	return pos < size && size > 1;
}
bool posEqualToSizeAndSizeIsOne(int pos, int size)
{
	return pos == size && size == 1;
}
bool posEqualToSizeAndSizeGreaterThanOne(int pos, int size)
{
	return pos == size && size > 1;
}
bool sizeIs1AndCopyLeftSizeGreaterThan0(int size, int copy_left_size)
{
	return size == 1 && copy_left_size > 0;
}
bool sizeIs1AndCopyRightSizeGreaterThan0(int size, int copy_right_size)
{
	return size == 1 && copy_right_size > 0;
}

bool sizeGreaterThan1AndCopyLeftSizeGreaterThan0(int size, int copy_left_size)
{
	return size > 1 && copy_left_size > 0;
}
bool sizeGreaterThan1AndCopyRightSizeGreaterThan0(int size, int copy_right_size)
{
	return size > 1 && copy_right_size > 0;
}

TrieNode** VectorInsertItem(int pos, TrieNode* node, TrieNode* value)
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

	if(posLessThanSizeAndSizeIs1(pos, size))
	{
		// [0, size)
		copy_right_size = distance(0, size);
	}
	else if(posLessThanSizeAndSizeGreaterThan1(pos, size))
	{
		// [0, pos), [pos, size)
		copy_left_size = distance(0, pos);
		copy_right_size = distance(pos, size);
	}
	else if(posEqualToSizeAndSizeIsOne(pos, size))
	{
		// [0, 0]
		copy_left_size = 1;

	}
	else if(posEqualToSizeAndSizeGreaterThanOne(pos, size))
	{
		// [0, pos)
		copy_left_size = distance(0, pos);

	}
	
	// may need to put more in here
	//printf("left %i, right %i pos %i\n", copy_left_size, copy_right_size, pos);
	// need separate cases for size== 1
	// can't have them in the combined choices part
	// adding in an extra item
	if(sizeIs1AndCopyLeftSizeGreaterThan0(size, copy_left_size))
	{
		new_neighbors[0] = copyTrieNode(node->neighbors[0]);
		new_neighbors[1] = setTrieNode(value);
		//memcpy(new_neighbors[0], node->neighbors[0], sizeof(TrieNode));
		return new_neighbors;
	}
	else if(sizeIs1AndCopyRightSizeGreaterThan0(size, copy_right_size))
	{
		new_neighbors[pos] = setTrieNode(value);
		new_neighbors[1] = copyTrieNode(node->neighbors[0]);
		//memcpy(new_neighbors[1], node->neighbors[0], sizeof(TrieNode));
		//printf("word after shift %s pos %i\n", new_neighbors[pos]->word, pos);

		return new_neighbors;
	}
	
	if(sizeGreaterThan1AndCopyLeftSizeGreaterThan0(size, copy_left_size))
	{
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
	if(sizeGreaterThan1AndCopyRightSizeGreaterThan0(size, copy_right_size))
	{
		for(int i = copy_left_size; i < size; i++)
		{
			// + 1 needs to go somewhere else
			new_neighbors[i + 1] = copyTrieNode(node->neighbors[i]);
			//memcpy(new_neighbors[i + 1], node->neighbors[i], sizeof(TrieNode));
			//printf("%s\n", new_neighbors[i]->word);

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

		TrieNode** new_neighbors = VectorInsertItem(location, node, target_chain);
		//printf("word saved %s\n", new_neighbors[location]->word);
		//printf("word saved %s\n", new_neighbors[1]->word);

		for(int i = 0; i < node->size; i++)
		{
			free(node->neighbors[i]);

		}
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
	// ContextState* target_state only used to set to the state after being found or made
	printf("\ninserting name\n");
	printTrieNodes(target_state->state_name->neighbors[0]);
	TrieNodePackage2* result = searchForInsertId(node, target_chain);
	//printTrieNodes(result->target_pointer);
	if(result != NULL)
	{

		//printf("got here\n");
		if(result->is_perfect_match)
		{
			TrieNode* node = result->tree_pointer;
			int mid = result->location;
			TrieNode* neighbor = node->neighbors[mid];
			if(neighbor != NULL)
			{
				if(neighbor->object != NULL)
				{
					//printf("already added\n");

				}
				else
				{
					// add in state
				}
			}
			else
			{
				// can't do anything
			}
			//printf("already added\n");
			// don't add
		}
		else
		{
			// add in the names remaining
			printf("adding name\n");
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
					//printTrieNodeTreeFlat(result->tree_pointer->neighbors[insert_location]->object->state_name->neighbors[0]);
					setFunction(result->tree_pointer->neighbors[insert_location]->object);
					//printf("saved object\n");

					//result->tree_pointer->neighbors[insert_location]->object->function_pointer(target_state);
					break;
				}
				insert_location = 0;


			}
			// claims the state exists but can't find it
			//printf("done\n");
			
			TrieNodePackage2* result2 = searchForInsertId(node, target_chain);
			/*
			if(result2 != NULL)
			{
				if(result2->object_found)
				{
					printf("found name\n");
					printStateName(result2->object_found->state_name);

					//printTrieNodeTreeFlat(result2->object_found->state_name->neighbors[0]);
					//printf("\n\n");

					//printContextState(result2->object_found);
				}
				//printf("location: %i\n", result->location);

			}*/
			
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
	root->neighbors[j]->neighbors_count = 1;
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
		next->neighbors_count = 1;
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
				root->neighbors[i]->neighbors_count = 1;
				root->neighbors_count += 1;

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
/*
char** makeName1(char* name)
{

}
*/
/*
new syntax plan
      P --> ( P ) | P P | epsilon
	p
		next paths
			(. p. )
			-------	
			p. p
			-------
			epsilon

	state
		another name
			next paths
				------------------------------------------
				a name. another name. a secondary name
				an overflowing name. another name. a secondary name
				-------	
				calculator context. a different name
				-------
				null
				------------------------------------------
*/
/*
typedef StateName
{
	char** names;
	int size;
}StateName;*/
/// preprocessing for the visitor function
// all strings saved into trie tree have double quotes around them
StateName* makeStateName1(char* name)
{
	StateName* full_state_name = malloc(sizeof(StateName));
	full_state_name->names = malloc(sizeof(char*));
	full_state_name->names[0] = surroundByQuotes(copyString(name));

	full_state_name->size = 1;
	return full_state_name;
}
StateName* makeStateName2(char* name_1, char* name_2)
{
	StateName* full_state_name = malloc(sizeof(StateName));
	full_state_name->names = malloc(sizeof(char*) * 2);
	
	full_state_name->names[0] = surroundByQuotes(copyString(name_1));

	full_state_name->names[1] = surroundByQuotes(copyString(name_2));


	full_state_name->size = 2;

	return full_state_name;
}

StateName* makeStateName3(char* name_1, char* name_2, char* name_3)
{
	StateName* full_state_name = malloc(sizeof(StateName));
	full_state_name->names = malloc(sizeof(char*) * 3);
	
	full_state_name->names[0] = surroundByQuotes(copyString(name_1));


	full_state_name->names[1] = surroundByQuotes(copyString(name_2));

	full_state_name->names[2] = surroundByQuotes(copyString(name_3));


	full_state_name->size = 3;

	return full_state_name;

}
TrieNode* makeFullStateName(StateName* name)
{
	// doesn't make any dummy nodes
	int size = name->size;
	//printf("%i\n", size);
	// make finger
	//printf("%s\n", name->names[0]);
	TrieNode* root = malloc(sizeof(TrieNode));
	// init neighbors
	root->neighbors = malloc(sizeof(TrieNode*));
	root->neighbors[0] = initTrieNode();
	root->neighbors[0]->size = 1;
	root->neighbors[0]->neighbors_count = 1;

	root->object = NULL;
	root->size = 1;
	root->neighbors_count = 1;


	TrieNode* current = root->neighbors[0];
	//printf("# of strings %i\n", size);
	for(int i = 0; i < size; i++)
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

		// addItem(name->names[i], current)
		current->word = copyString(name->names[i]);

		//addTrieNodeItem(my_tokens, current);
		//printf("%s\n", root->neighbors[j]->word);
		//printf("%s\n", current->word);
		//printf("here rr\n");
		//printf("token before: %s\n", collectChars(getToken(my_tokens), getInput(my_tokens)));
		//printf("saved %s\n", current->word);
		//advanceToken(my_tokens);
		//		printf("here\n");
		if(i == size - 1)
		{
			//printf("done\n");
			current->neighbors = NULL;
			current->size = 0;

			current->neighbors_count = 0;
			break;
		}
		//printf("should not be here\n");
		//printf("token after: %s\n", collectChars(getToken(my_tokens), getInput(my_tokens)));

		TrieNode* next = malloc(sizeof(TrieNode));
		next->size = 1;
		next->object = NULL;
		next->neighbors_count = 1;
		//printf("here 3\n");

		current->neighbors = malloc(sizeof(TrieNode*));
		current->neighbors[0] = next;
		//		printf("here 4\n");

		current = current->neighbors[0];
	}
	return root;
}
ContextState* makeVariable(StateName* name, Data* value)
{
	TrieNode* full_state_name = makeFullStateName(name);
	printStateName(full_state_name);
	ContextState* state = makeFullContextState2(
		full_state_name,
		NULL,
		NULL,
		NULL,
		"\"returnTrue\"",
		value,
		NULL,
		returnTrue,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL);
	return state;

}
bool addVariableToDict(TrieNode* dict, ContextState* state)
{

	//printf("data value %i\n", state->var_data->_int);	
	// insert2(root, state->state_name->neighbors[0], state);
	insert2(dict, state->state_name->neighbors[0], state);
	return true;
	// return success
}

/*
bool addToDict2(TrieNode* dict, char* name1, char* name2)
{
	// make finger

	// add to dict
	// return success
}

bool addToDict3(TrieNode* dict, char* name1, char* name2, char* name3)
{
	// make finger

	// add to dict
	// return success
}
*/
TrieNode* makeSearchName(StateName* name)
{
	// when searching need to start with the first node that has a name
	// the TrieNode* names stored in the dict have a dummy node first
	return makeFullStateName(name)->neighbors[0];
	// makeSearchName("name", "another name", "a third name")
}

ContextState* obtainState(TrieNodePackage2* result)
{
	//printf("%i\n", result->is_perfect_match);
	if(result->is_perfect_match)
	{
		TrieNode* node = result->tree_pointer;
		int mid = result->location;
		//printf("%i\n", mid);
		TrieNode* neighbor = node->neighbors[mid];
		if(neighbor != NULL)
		{
			if(neighbor->object != NULL)
			{
				//printf("already added\n");
				return neighbor->object;
			}
		}
	}
	return NULL;
}
//////
/// methods for visitor function
///
void visitor(TrieNode* dict, ContextState* start, ContextState* end)
{

	/*
	need a dict holding the bottom state trackers and the tree they trace out
	loop while end is not in the set of next states
		do the following for each state in the bottom state trackers

			if the next states are parallel
				run each next state
				add the successfull ones to the bottom state trackers
				each passing state in [2, n] are assumed to be branches
				if last state failed set dead state flag
			else
				run each next state
				add the first successfull one to the bottom state trackers
				save the index of the first passing state into the bottom state trackers
				if last state failed set dead state flag
		after loop
		scan the bottom state trackers
			if the state is an end state
				go up the state tracker tree till we get to the top or next set of next states
			if the state is a dead state
				go up the state tracker tree till we get to the top or the next set of next states starting from where that level last stoped(submaching was false, but the parent state was true, therefore the parent state is false)

	*/

	TrieNode* bottom_tracker = initTrieNode();
	// each state is a start attribute
	/*
		trees
			bottom tracker
				(var_name, level_number, current_branch)
			main graph
				control flow

			system tree
				each child
					(level_number, max_branch value)

	*/

	//ContextState* var = makeVariable(makeStateName3("name", "another name", "a third name"), makeDataInt(3456));
	//addVariableToDict(bottom_tracker, var);
	//printf("printing tree\n");
	//printTrieNodeTree(bottom_tracker, 1);
	//printf("\n");
	/*
TrieNodePackage2* searchForInsertId(TrieNode* node,
								    TrieNode* target_chain,
								    ContextState* target_state)

	*/
	//TrieNodePackage2* result = searchForInsertId(bottom_tracker, makeSearchName(makeStateName3("name", "another name", "a third name")));
	//ContextState* x = obtainState(result);
	// need a way to enumerate all states
	//printf("%x\n", result->object_found);
	//printf("%i\n", x->var_data->_int);
	// what's next?
	// delete(dict, state)
	// delete(dict, state, attribute_name, (state_namme))
	/*
	just a little part of the plan

	*/
	//if(result->object_found)
	//{
		//printf("%x\n", result->object_found);	
		//int var = 
	//}
	TrieNode* user_control_flow = initTrieNode();
	TrieNode* bottom_tracker_tracker = initTrieNode();
	TrieNode* history = initTrieNode();  // add the last passing state to the tree
	printf("deleting prev_word\n");
	//delete2(dict, state->state_name->neighbors[0], state)
	//printf("%s\n", makeStateName1("prev_word")->names[0]);
	//printf("%s\n", makeFullStateName(makeStateName1("prev_word"))->neighbors[0]->word);
	//makeStateName1("prev_word");

	//printf("%s\n", makeSearchName(makeStateName1("prev_word"))->word);
	ContextState* item_to_erase = obtainState(searchForInsertId(dict, makeSearchName(makeStateName1("prev_word"))));
	//printf("%s\n", item_to_erase->state_name->neighbors[0]->word);
	//printf("about to delete\n");
	//printf("%x\n", item_to_erase);
	delete2(dict, item_to_erase->state_name->neighbors[0], item_to_erase);
	printTrieNodeTree(dict, 1);
	//printf("\n");
	ContextState* item_to_erase2 = obtainState(searchForInsertId(dict, makeSearchName(makeStateName1("current_word"))));

	delete2(dict, item_to_erase2->state_name->neighbors[0], item_to_erase2);
	printTrieNodeTree(dict, 1);


	// erase 1 in the middle with 2 names
	ContextState* item_to_erase3 = obtainState(searchForInsertId(dict, makeSearchName(makeStateName2("level_number", "0"))));

	delete2(dict, item_to_erase3->state_name->neighbors[0], item_to_erase3);
	printTrieNodeTree(dict, 1);

	// erase 1 at the end with 2 names




}