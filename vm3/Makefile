CC=clang++ -std=c++17

main.out:  lexer2.l grammar2.y main.cpp  opcode.o assembler.o  assembly.o commandline.o \
	assembler_interactive.o vm.o prompt.o tree.o my_helpers.o
	bison -d grammar2.y 
	flex lexer2.l
	$(CC) -omain.out main.cpp Parser2.cpp Scanner2.cpp opcode.o my_helpers.o \
	assembler.o assembly.o commandline.o assembler_interactive.o  vm.o prompt.o tree.o -lreadline


opcode.o: opcode.cpp opcode.hh
	$(CC) -c opcode.cpp

assembly.o: assembly.cpp assembly.hh
	$(CC) -c assembly.cpp

vm.o: vm.cpp vm.hh
	$(CC) -c vm.cpp

commandline.o: commandline.cpp commandline.hh
	$(CC) -c commandline.cpp

prompt.o : prompt.cpp  prompt.hh
	$(CC) -c prompt.cpp

assembler.o : assembler.cpp  assembler.hh
	$(CC) -c assembler.cpp

assembler_interactive.o : assembler_interactive.cpp  assembler_interactive.hh
	$(CC) -c assembler_interactive.cpp

tree.o : tree.cpp  tree.hh
	$(CC) -c tree.cpp

my_helpers.o : my_helpers.cpp  my_helpers.hh
	$(CC) -c my_helpers.cpp

clean:
	rm -f main.out Parser2.cpp Scanner2.cpp *.o *.gch