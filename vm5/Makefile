SHELL := /bin/bash
CC=g++ -std=c++17  -g
# Define temporary directory
TMPDIR = /dev/shm
MAKE=make

objects = atom.o operand.o number.o printer_any.o entity.o list_entity.o map_entity.o operand_entity.o operand_tostr.o
#objects = (wildcard: *.cc)
headers  := (wildcard: *.hh)

#all: test_cc_d $(objects) 
all: $(objects)  test_cc_d



$(objects): %.o: %.cc 
	$(CC) -c $^ -o $@

test_cc_d:
	$(MAKE) -C test_cc 


clean:
	rm -f out *.o *.gch *.out
	cd test_cc; make clean
