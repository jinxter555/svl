CC=clang++ -std=c++20

main.out:  lexer2.l grammar2.y main.cpp  opcode.o assembler.o  assembly.o commandline.o assembler_interactive.o vm.o prompt.o
	bison -d grammar2.y
	flex lexer2.l
	clang++ -omain.out main.cpp Parser2.cpp Scanner2.cpp opcode.o assembler.o assembly.o commandline.o assembler_interactive.o  vm.o prompt.o -lreadline


opcode.o: opcode.cpp opcode.hh
	clang++ -c opcode.cpp

assembly.o: assembly.cpp assembly.hh
	clang++ -c assembly.cpp

vm.o: vm.cpp vm.hh
	clang++ -c vm.cpp

commandline.o: commandline.cpp commandline.hh
	$(CC) -c commandline.cpp

prompt.o : prompt.cpp  prompt.hh
	$(CC) -c prompt.cpp

assembler.o : assembler.cpp  assembler.hh
	$(CC) -c assembler.cpp

assembler_interactive.o : assembler_interactive.cpp  assembler_interactive.hh
	$(CC) -c assembler_interactive.cpp

clean:
	rm -f main.out Parser2.cpp Scanner2.cpp *.o *.gch