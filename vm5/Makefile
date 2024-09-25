SHELL := /bin/bash
CC=g++ -std=c++17 -g
# Define temporary directory
TMPDIR = /dev/shm

objects = atom.o operand.o number.o printer_any.o entity.o ast.o
#objects = (wildcard: *.cc)

all: $(objects)
#	$(CC)  $^ -o all

$(objects): %.o: %.cc
	$(CC) -c $^ -o $@

clean:
	rm -f out *.o *.gch *.out
