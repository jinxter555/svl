SHELL := /bin/bash
CC=g++ -g -std=c++23 -Wall
# Define temporary directory
TMPDIR = /dev/shm
MAKE=make

objects = interactive.o prompt.o node.o node_str.o node_map.o node_list.o node_math.o tree.o \
kernel.o lang.o lisp.o  error.o \
lisp_expr.o lisp_expr_parse.o  lisp_expr_eval.o lisp_expr_func.o lisp_expr_call.o \
lisp_expr_helpers.o \
lisp_reader.o lisp_reader_infix.o scope_logger.o commandline.o my_helpers.o lisp_expr_keywords.o \
io_file.o

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
