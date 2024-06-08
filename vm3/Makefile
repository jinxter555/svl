#CC=clang++ -std=c++17 -g
CC=g++ -std=c++17 -g
#CC=g++ -std=c++17 

main.out:  asm_lexer.l asm_grammar.y main.cc  opcode.o assembler.o  assembly.o commandline.o \
	assembler_interactive.o vm.o prompt.o tree.o my_helpers.o svlm_grammar.y svlm_lexer.l  \
	asm_parser.cc asm_scanner.cc svlm_parser.cc svlm_scanner.cc \
	svlm_interactive.o svlm_lang.o ast.o printer_any.o number.o operand.o tuple.o atom.o
	$(CC) -o /dev/shm/main.out main.cc asm_parser.cc asm_scanner.cc opcode.o my_helpers.o \
	assembler.o assembly.o commandline.o assembler_interactive.o  vm.o prompt.o  \
	svlm_scanner.cc svlm_parser.cc tree.o  svlm_interactive.o svlm_lang.o \
	printer_any.o number.o operand.o tuple.o atom.o ast.o \
	-lreadline


asm_parser.cc: assembler.hh asm_scanner.hh assembler.cc asm_grammar.y
	bison -d asm_grammar.y 

asm_parser.hh: 
	bison -d asm_grammar.y 

svlm_parser.cc: svlm_grammar.y
	bison -d svlm_grammar.y 

svlm_parser.hh: svlm_grammar.y
	bison -d svlm_grammar.y 

asm_scanner.cc: assembler.hh asm_scanner.hh assembler.cc asm_lexer.l
	flex asm_lexer.l

svlm_scanner.cc: svlm_lexer.l
	flex -i svlm_lexer.l



printer_any.o: printer_any.cc
	$(CC) -c printer_any.cc

tuple.o: tuple.cc tuple.hh
	$(CC) -c tuple.cc

number.o: number.cc number.hh
	$(CC) -c number.cc

operand.o: operand.cc operand.hh
	$(CC) -c operand.cc

atom.o: atom.cc atom.hh
	$(CC) -c atom.cc

ast.o: ast.cc ast.hh
	$(CC) -c ast.cc

opcode.o: opcode.cc opcode.hh
	$(CC) -c opcode.cc

assembly.o: assembly.cc assembly.hh
	$(CC) -c assembly.cc

vm.o: vm.cc vm.hh
	$(CC) -c vm.cc

commandline.o: commandline.cc commandline.hh
	$(CC) -c commandline.cc

prompt.o : prompt.cc  prompt.hh
	$(CC) -c prompt.cc

assembler.o : assembler.cc  assembler.hh
	$(CC) -c assembler.cc

assembler_interactive.o : assembler_interactive.cc  assembler_interactive.hh asm_parser.hh asm_scanner.hh asm_parser.cc asm_scanner.cc
	$(CC) -c assembler_interactive.cc

svlm_lang.o: svlm_lang.cc svlm_lang.hh
	$(CC) -c svlm_lang.cc

svlm_interactive.o: svlm_interactive.cc svlm_interactive.hh svlm_parser.hh svlm_scanner.hh svlm_parser.cc svlm_scanner.cc
	$(CC) -c svlm_interactive.cc

tree.o : tree.cc  tree.hh
	$(CC) -c tree.cc

ast.o : ast.cc  ast.hh
	$(CC) -c ast.cc

my_helpers.o : my_helpers.cc  my_helpers.hh
	$(CC) -c my_helpers.cc

clean:
	rm -f asm_parser.cc asm_scanner.cc *.o *.gch svlm_scanner.cc svlm_parser.cc svlm_parser.hh asm_parser.hh

