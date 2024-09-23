SHELL := /bin/bash
CC=g++ -std=c++17 -g
# Define temporary directory
TMPDIR = /dev/shm
ast_o := $(wildcard ../*.o)
core_o := $(wildcard ../../*.o)

objects = t_entity_01.o

a.out: $(objects)
	$(CC)  $^ $(ast_o) $(core_o) -o a.out

$(objects): %.o: %.cc
	$(CC) -c $^ -o $@

clean:
	rm -f all out *.o *.gch *.out
