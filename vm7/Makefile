SHELL := /bin/bash
CC=g++ -std=c++17  -ggdb
# Define temporary directory
TMPDIR = /dev/shm
MAKE=make

#objects = atom.o operand.o number.o printer_any.o entity.o list_entity.o map_entity.o operand_entity.o 
objects = operand.o operand_tostr.o operand_math.o number.o ast.o ast_list.o ast_map.o operand_visitors.o 
headers  := (wildcard: *.hh)

all: $(objects)  test_cc_d
#all: $(objects) 



$(objects): %.o: %.cc 
	$(CC) -g -c $^ -o $@

test_cc_d:
	$(MAKE) -C test_cc 


clean:
	rm -f out *.o *.gch *.out
	cd test_cc; make clean
