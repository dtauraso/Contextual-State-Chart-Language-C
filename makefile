

include_and_c_files = state.c state.h main.c jsmn.c jsmn.h lisp_node.c lisp_node.h trie_node.c trie_node.h

object_files = jsmn.o state.o lisp_node.o trie_node.o main.o



%.o:%.c $(include_and_c_files)
	gcc $< -c


state_machine.x: $(object_files)

	gcc $(object_files) -o state_machine.x

test:
	-make clean

	-make state_machine.x
	#-./state_machine.x input.txt
	#-./state_machine.x parsing_tree.json calculator_example.txt
	-./state_machine.x parallel_programming_example.json parallel_programming_example.txt

	#-./state_machine.x parsing_tree.json little_sequence_hierarchy.txt
	#-./testing.x parsing_tree.json calculator_example.txt
run:
	-./state_machine.x parsing_tree.json calculator_example.txt

clean:
	-rm *.o *.x
