
//MultiwayLinesNode* makeTree(Scanner* my_scanner, char* input)
//{
	// This function reinterprets the indented lines in the input as a multiway doubly linked tree.

	// needs the input to end on a newline after the last collectable text
	// there can't be any lines with only indents
	//printf("makeTree\n");
	/*
	setup
		next
			have_more_lines_to_read. (next_indent > current_indent | next_indent < current_indent | next_indent == current_indent)
	have_more_lines_to_read
		next
			(next_indent > current_indent | next_indent < current_indent | next_indent == current_indent)
	next_indent > current_indent
		next
			have_more_lines_to_read
	next_indent < current_indent
		next
			have_more_lines_to_read
	next_indent == current_indent
		next
			have_more_lines_to_read

	*/
			/*
	int current_indent = 0;
	int next_indent = 0;
	int i = 0;
	int num_lines = countLines(input);
	//printf("here\n");
	MultiwayLinesNode* dummy_dummy_root = initMultiwayLinesNode();
	// surroundByQuotes("dummy_dummy_root")
	dummy_dummy_root = setName(dummy_dummy_root, "\"dummy_dummy_root\"");


	MultiwayLinesNode* dummy_root = initMultiwayLinesNode();

	dummy_root = setName(dummy_dummy_root, "\"dummy_root\"");



	MultiwayLinesNode* root = initMultiwayLinesNode();

	root = setName(root, "\"root\"");


	MultiwayLinesNode* parent = root;

	MultiwayLinesNode* child;

	doubleLink(dummy_dummy_root, dummy_root);

	doubleLink(dummy_root, parent);

	char* word = getNextWord(input, i);

	parent = setName(parent, word);

	i += strlen(word) + 1;

	next_indent = countTabs(input, i);
	i += next_indent;
	free(word);

	// assuming there will be 1 state and 1 child
	if(next_indent > current_indent)
	{
		word = getNextWord(input, i);
		child = initMultiwayLinesNode();
		child = setName(child, word);

		doubleLink(parent, child);

		i += strlen(word) + 1;

		next_indent = countTabs(input, i);

		i += next_indent;


		swap(&current_indent, &next_indent);

		free(word);

	}
	//printf("got here\n");

	// input[i] should be first char of 3rd word
	int count = 0;
	while(count < num_lines)
	{
		//printf("count %i, num_lines %i, i %i, input len %lu\n", count+1, num_lines, i, strlen(input));

		char* word = getNextWord(input, i);

		MultiwayLinesNode* new_node = initMultiwayLinesNode();
		if(new_node == NULL) exit(1);

		new_node = setName(new_node, word);


		free(word);

		i += strlen(new_node->line) + 1;

		next_indent = countTabs(input, i);
		

		if(next_indent > current_indent)
		{
			// GOING DOWN

			doubleLink(child, new_node);


			parent = child;

			child = new_node;

		}
		else if(next_indent < current_indent)
		{
			// CLIMB UP
			doubleLink(child, new_node);
			if(next_indent <= 0)
			{
				return root;
			}
			int target_indent = current_indent;
			while(target_indent > next_indent)
			{

				// have parent go up 1 parent
				parent = parent->parents[parent->parents_size - 1]; // last path visited
				child = child->parents[child->parents_size - 1];

				// target_indent--
				target_indent--;
			}

		}
		else // next_indent == current_indent
		{
			// child must have gone up from the climb up case
			//  GOING ACROSS
			doubleLink(child, new_node);
			



		}
		i += next_indent;
		swap(&current_indent, &next_indent);

		//printf("tree -------------------------\n");
		//printTree(root, 0);
		//printf("-------------------------\n");



		count++;
	}
	//printf("done with file tree -------------------------\n");
	//printTree(root, 0);
	//printf("-------------------------\n");

	return 0;
}*/