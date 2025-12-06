SHELL := /bin/bash
CC=g++ -g -std=c++23 
# Define temporary directory
TMPDIR = /dev/shm
MAKE=make

objects = node.o node_map.o node_list.o node_math.o tree.o lang.o lisp.o lisp_expr.o lisp_reader.o scope_logger.o commandline.o
#objects = (wildcard: *.cc)
headers  := (wildcard: *.hh)

#all: test_cc_d $(objects) 
all: $(objects)   test_cc_d



$(objects): %.o: %.cc 
	$(CC) -c $^ -o $@

test_cc_d:
	$(MAKE) -C test_cc 


clean:
	rm -f out *.o *.gch *.out
	cd test_cc; make clean
