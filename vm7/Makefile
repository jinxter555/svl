SHELL := /bin/bash
CC=g++ -std=c++17  -ggdb
# Define temporary directory
TMPDIR = /dev/shm
MAKE=make

#objects = atom.o operand.o number.o printer_any.o entity.o list_entity.o map_entity.o operand_entity.o 
objects = operand.o operand_tostr.o operand_math.o number.o ast.o ast_list.o ast_map.o operand_visitors.o  que_node.o  svlm_ast.o prompt.o \
my_helpers.o commandline.o svlm_interactive.o main.o svlm_parser.o svlm_scanner.o 
headers  := (wildcard: *.hh)

all: $(objects)  test_cc_d  main.out
#all: $(objects) 

svlm_scanner.cc: svlm_lexer.l
	flex -i svlm_lexer.l

svlm_parser.cc: svlm_grammar.y
	bison -d svlm_grammar.y

main.out: $(objects) 
	$(CC) $^ -o /dev/shm/main.out -lreadline

$(objects): %.o: %.cc 
	$(CC) -g -c $^ -o $@

test_cc_d:
	$(MAKE) -C test_cc 


clean:
	rm -f out *.o *.gch 
	rm -f svlm_scanner.cc
	rm -f svlm_parser.cc
	cd test_cc; make clean
