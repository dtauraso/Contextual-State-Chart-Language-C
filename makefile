


#include_files = data.h name.h point.h  visit_functions.h hash_table.h state.h states.h standard_headers.h  data.c name.c point.c hash_table.c state.c states.c visit_functions.c state_machine.c
#object_files = data.o name.o point.o state.o states.o hash_table.o visit_functions.o state_machine.o


include_and_c_files2 = state3.c state3.h main.c jsmn.c jsmn.h

object_files2 = state3.o main.o jsmn.o


include_and_c_files3 = testing.c state3.c state3.h
object_files3 = state3.o testing.o

%.o:%.c $(include_and_c_files2)
	gcc $< -c

%.o:%.c $(include_and_c_files3)
	gcc $< -c

#state2.o: state2.c state2.h
#	gcc state2.c -c

#main.o: main.c state2.o
#	gcc main.c state2.c -c

state_machine.x: $(object_files2)

	gcc $(object_files2) -o state_machine.x
testing.x: $(object_files3)

	gcc $(object_files3) -o testing.x

run:
	-make clean
	#g++ main.c -o state_machine.x
	-make state_machine.x
	#-make testing.x
	#-./state_machine.x input.txt
	-./state_machine.x parsing_tree.json calculator_example.txt
	#-./testing.x parsing_tree.json calculator_example.txt
clean:
	-rm *.o *.x
