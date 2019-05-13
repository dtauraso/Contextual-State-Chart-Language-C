


#include_files = data.h name.h point.h  visit_functions.h hash_table.h state.h states.h standard_headers.h  data.c name.c point.c hash_table.c state.c states.c visit_functions.c state_machine.c
#object_files = data.o name.o point.o state.o states.o hash_table.o visit_functions.o state_machine.o


include_and_c_files2 = state2.h state2.c main.c

object_files2 = state2.o main.o



%.o:%.c $(include_and_c_files2)
	gcc $< -c




state_machine.x: $(object_files2)

	gcc $(object_files2) -o state_machine.x

run:
	-make clean
	-make state_machine.x
	#-./state_machine.x input.txt
	-./state_machine.x calculator_example.txt
clean:
	-rm *.o *.x
