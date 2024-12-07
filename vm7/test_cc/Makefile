SHELL := /bin/bash
CC=g++ -std=c++17 -g
# Define temporary directory
TMPDIR = /dev/shm
core_o := $(wildcard ../ast_list.o ../ast_map.o ../ast.o ../my_helpers.o ../number.o ../operand_math.o ../operand.o ../operand_tostr.o ../operand_visitors.o ../que_node.o ../scope_logger.o )
#core_o := $(wildcard ../ast_list.o ../ast_map.o ../ast.o ../commandline.o ../my_helpers.o ../number.o ../operand_math.o ../operand.o ../operand_tostr.o ../operand_visitors.o ../prompt.o ../que_node.o ../scope_logger.o ../svlm_ast.o ../svlm_interactive.o ../svlm_parser.o ../svlm_scanner.o)


# all: t_operand_01.out t_list_01.out  t_list_02.out  t_map_01.out t_map_02.out t_map_03.out  t_map_04.out t_quenode_01.out t_quenode_02.out
all: t_operand_01.out   t_list_01.out   # t_list_02.out  t_list_03.out   t_map_01.out t_map_02.out t_map_03.out  t_map_04.out t_quenode_01.out t_quenode_02.out
#all: $(objects)
CCFLAG = -lreadline

t_operand_01.out: t_operand_01.o $(core_o)
	$(CC)  $^ $(CCFLAG) -o $@

t_list_01.out: t_list_01.o $(core_o)
	$(CC)  $^ $(CCFLAG) -o $@

t_list_02.out: t_list_02.o $(core_o)
	$(CC)  $^ $(CCFLAG) -o $@

t_list_03.out: t_list_03.o $(core_o)
	$(CC)  $^ $(CCFLAG) -o $@

t_list_02.out: t_list_02.o $(core_o)
	$(CC)  $^ $(CCFLAG) -o $@

t_map_01.out: t_map_01.o $(core_o)
	$(CC)  $^ $(CCFLAG) -o $@

t_map_02.out: t_map_02.o $(core_o)
	$(CC)  $^ $(CCFLAG) -o $@

t_map_03.out: t_map_03.o $(core_o)
	$(CC)  $^ $(CCFLAG) -o $@

t_map_04.out: t_map_04.o $(core_o)
	$(CC)  $^ $(CCFLAG) -o $@

t_quenode_01.out: t_quenode_01.o $(core_o)
	$(CC)  $^  $(CCFLAG) -g -o $@

t_quenode_02.out: t_quenode_02.o $(core_o)
	$(CC)  $^  $(CCFLAG) -g -o $@


#$(objects): %.o: %.cc
#	$(CC) -c $^ -o $@

clean:
	rm -f all out *.o *.gch *.out t_entity_01 t_entity_02
	rm -f all out *.o *.gch *.out 

remake:
	make clean
	make
