
hash_table.o: hash_table.h
	gcc -c hash_table.c

state_machine.x: hash_table.h forward_declarators.h hash_table.o
	gcc state_machine.c hash_table.o -o state_machine.x

#state_machine.x: hash.o state_machine.o
#	gcc hash.o state_machine.o

run:
	- make clean
	- make state_machine.x
	./state_machine.x
clean:
	rm *.o *.x
