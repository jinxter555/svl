CC=clang++ -std=c++17
main: main.o prompt.o assembly.o vm.o assembly_sbc.o commandline.o assembler.o assembler_interactive.o tree.o my_helpers.o
	$(CC) -g -o main.out  main.o prompt.o  assembler_interactive.o tree.o my_helpers.o \
	assembly.o vm.o assembly_sbc.o commandline.o assembler.o -lreadline

clean: 
	rm *.o main.out

main.o : main.cpp
	$(CC) -c main.cpp

prompt.o : prompt.cpp prompt.hh
	$(CC) -c prompt.cpp

asembly.o : assembly.cpp assembly.hh
	$(CC) -c assembly.cpp

vm.o : vm.cpp vm.hh
	$(CC) -c vm.cpp

assembly_sbc.o : assembly_sbc.cpp  
	$(CC) -c assembly_sbc.cpp

commandline.o: commandline.cpp commandline.hh
	$(CC) -c commandline.cpp

assembler.o : assembler.cpp  assembler.hh
	$(CC) -c assembler.cpp

assembler_interactive.o : assembler_interactive.cpp  assembler_interactive.hh
	$(CC) -c assembler_interactive.cpp

tree.o : tree.cpp  tree.hh
	$(CC) -c tree.cpp

my_helpers.o : my_helpers.cpp  my_helpers.hh
	$(CC) -c my_helpers.cpp

