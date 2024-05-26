#CC=clang++ -std=c++17 -g
CC=g++ -std=c++17 -g
#CC=g++ -std=c++17 

main.out:  asm_lexer.l asm_grammar.y main.cpp  opcode.o assembler.o  assembly.o commandline.o \
	assembler_interactive.o vm.o prompt.o tree.o my_helpers.o svlm_grammar.y svlm_lexer.l  \
	asm_parser.cpp asm_scanner.cpp svlm_parser.cpp svlm_scanner.cpp \
	svlm_interactive.o svlm_lang.o ast.o printer_any.o number.o tuple.o atom.o
	$(CC) -o main.out main.cpp asm_parser.cpp asm_scanner.cpp opcode.o my_helpers.o \
	assembler.o assembly.o commandline.o assembler_interactive.o  vm.o prompt.o  \
	svlm_scanner.cpp svlm_parser.cpp tree.o  svlm_interactive.o svlm_lang.o \
	printer_any.o number.o tuple.o atom.o ast.o \
	-lreadline


asm_parser.cpp: assembler.hh asm_scanner.hh assembler.cpp asm_grammar.y
	bison -d asm_grammar.y 

asm_parser.hh: 
	bison -d asm_grammar.y 

svlm_parser.cpp: svlm_grammar.y
	bison -d svlm_grammar.y 

svlm_parser.hh: svlm_grammar.y
	bison -d svlm_grammar.y 

asm_scanner.cpp: assembler.hh asm_scanner.hh assembler.cpp asm_lexer.l
	flex asm_lexer.l

svlm_scanner.cpp: svlm_lexer.l
	flex -i svlm_lexer.l



printer_any.o: printer_any.cpp
	$(CC) -c printer_any.cpp

tuple.o: tuple.cpp tuple.hh
	$(CC) -c tuple.cpp

number.o: number.cpp number.hh
	$(CC) -c number.cpp

atom.o: atom.cpp atom.hh
	$(CC) -c atom.cpp

ast.o: ast.cpp ast.hh
	$(CC) -c ast.cpp

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

assembler_interactive.o : assembler_interactive.cpp  assembler_interactive.hh asm_parser.hh asm_scanner.hh asm_parser.cpp asm_scanner.cpp
	$(CC) -c assembler_interactive.cpp

svlm_lang.o: svlm_lang.cpp svlm_lang.hh
	$(CC) -c svlm_lang.cpp

svlm_interactive.o: svlm_interactive.cpp svlm_interactive.hh svlm_parser.hh svlm_scanner.hh svlm_parser.cpp svlm_scanner.cpp
	$(CC) -c svlm_interactive.cpp

tree.o : tree.cpp  tree.hh
	$(CC) -c tree.cpp

ast.o : ast.cpp  ast.hh
	$(CC) -c ast.cpp

my_helpers.o : my_helpers.cpp  my_helpers.hh
	$(CC) -c my_helpers.cpp

clean:
	rm -f main.out asm_parser.cpp asm_scanner.cpp *.o *.gch svlm_scanner.cpp svlm_parser.cpp svlm_parser.hh asm_parser.hh

