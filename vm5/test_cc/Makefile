SHELL := /bin/bash
CC=g++ -std=c++17 -g
# Define temporary directory
TMPDIR = /dev/shm
ast_o := $(wildcard ../*.o)
core_o := $(wildcard ../../*.o)

all: a.out b.out c.out map.out
#all: $(objects)

objects := t_entity_01 t_entity_02


a.out: t_entity_01.o
	$(CC)  $^ $(ast_o) $(core_o) -o $@

b.out: t_entity_02.o
	$(CC)  $^ $(ast_o) $(core_o) -o $@

c.out: t_list_01.o
	$(CC)  $^ $(ast_o) $(core_o) -o $@
map.out: t_map_01.o
	$(CC)  $^ $(ast_o) $(core_o) -o $@


#$(objects): %.o: %.cc
#	$(CC) -c $^ -o $@

clean:
	rm -f all out *.o *.gch *.out
