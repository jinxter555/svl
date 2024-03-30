#CC=clang++ -std=c++17 -g
CC=g++ -std=c++17 -g

main.out:  asm_lexer.l asm_grammar.y main.cpp  opcode.o assembler.o  assembly.o commandline.o \
	assembler_interactive.o vm.o prompt.o tree.o my_helpers.o ast_grammar.y ast_lexer.l  \
	asm_parser.cpp asm_scanner.cpp ast_parser.cpp ast_scanner.cpp
#	bison -d asm_grammar.y 
#	bison -d ast_grammar.y 
#	flex asm_lexer.l
#	flex ast_lexer.l
	$(CC) -omain.out main.cpp asm_parser.cpp asm_scanner.cpp opcode.o my_helpers.o \
	assembler.o assembly.o commandline.o assembler_interactive.o  vm.o prompt.o  \
	ast_scanner.cpp ast_parser.cpp tree.o -lreadline

asm_parser.cpp: assembler.hh asm_scanner.hh assembler.cpp asm_grammar.y
	bison -d asm_grammar.y 

ast_parser.cpp: ast_grammar.y
	bison -d ast_grammar.y 

asm_scanner.cpp: assembler.hh asm_scanner.hh assembler.cpp asm_lexer.l
	flex asm_lexer.l

ast_scanner.cpp: ast_lexer.l
	flex -i ast_lexer.l




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
	rm -f main.out asm_parser.cpp asm_scanner.cpp *.o *.gch ast_scanner.cpp ast_parser.cpp
