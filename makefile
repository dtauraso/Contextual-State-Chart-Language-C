

include_and_c_files =  main.cpp vector.c vector.h trie_tree.h trie_tree.c standard_includes.h

object_files =  main.o vector.o trie_tree.o



%.o:%.c $(include_and_c_files)
	gcc $< -c


state_machine.x: $(object_files)

	gcc $(object_files) -o state_machine.x 

test:
	make clean

	-make state_machine.x
	#-./state_machine.x input.txt
	# -./state_machine.x parsing_tree_copy.json calculator_example.txt
	#-./state_machine.x insert_test_5.json calculator_example.txt
	#-./state_machine.x tokens_to_trie_tree_test.json calculator_example.txt

	-./state_machine.x parsing_tree.json calculator_example.txt
	#-./state_machine.x parsing_tree.json parallel_programming_example.txt
	# -./state_machine.x parsing_tree.json parallel_programming_example2.txt

	#-./state_machine.x parsing_tree.json start.txt

	#-./state_machine.x parallel_programming_example_json.json calculator_example.txt

	# -./state_machine.x parallel_programming_example.json parallel_programming_example.txt

	#-./state_machine.x parsing_tree.json little_sequence_hierarchy.txt
	#-./testing.x parsing_tree.json calculator_example.txt
run:
	-./state_machine.x parsing_tree.json calculator_example.txt

clean:
	-rm *.o *.x
