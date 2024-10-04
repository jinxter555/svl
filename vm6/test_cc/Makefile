SHELL := /bin/bash
CC=g++ -std=c++17 -g
# Define temporary directory
TMPDIR = /dev/shm
ast_o := $(wildcard ../*.o)
core_o := $(wildcard ../../*.o)

# all: t_entity_01.out t_entity_02.out  t_list_01.out  t_list_02.out # t_map_01.out t_ast_operand_01.out  u_entity_ptr_01.out
all: t_entity_01.out t_entity_02.out  t_list_01.out  t_list_02.out  t_map_01.out t_astnode_01.out
#all: t_operand_01.out 
#all: $(objects)

t_operand_01.out: t_operand_01.o $(ast_o)
	$(CC)  $^  -o $@

t_entity_01.out: t_entity_01.o $(ast_o)
	$(CC)  $^  -o $@

t_entity_02.out: t_entity_02.o $(ast_o)
	$(CC)  $^ -o $@

t_list_01.out: t_list_01.o $(ast_o)
	$(CC)  $^ -o $@

t_list_02.out: t_list_02.o $(ast_o)
	$(CC)  $^ -o $@

t_map_01.out: t_map_01.o $(ast_o)
	$(CC)  $^ -o $@

t_ast_operand_01.out: t_ast_operand_01.o $(ast_o)
	$(CC)  $^  -o $@

t_astnode_01.out: t_astnode_01.o $(ast_o)
	$(CC)  $^  -o $@

u_entity_ptr_01.out: u_entity_ptr_01.o $(ast_o)
	$(CC)  $^  -o $@

#$(objects): %.o: %.cc
#	$(CC) -c $^ -o $@

clean:
	rm -f all out *.o *.gch *.out t_entity_01 t_entity_02
	rm -f all out *.o *.gch *.out 

remake:
	make clean
	make
