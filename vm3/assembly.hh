#pragma once
#include "vm.hh"
#include "tree.hh"

#define MAX_CODE_SIZE 5000

class Assembly {
protected:
  instr_t instruction = {Opcode(0), 0,0,0};

  s_int_t pc_load=0; // program counter at load program
  instr_t code[MAX_CODE_SIZE];    
  // instruction pointing to actual src line no. macro expansion
  // and so on this is used for debugging break line and so on
  us_int_t line_no[MAX_CODE_SIZE]; 

  std::vector<reg_t> data_seg;

  us_int_t breakpoint=0;
public:
  void run(VM&);
  void run_normal(VM&);
  void run_single_instruction(VM&);
  void run_call(VM&, s_int_t start_pc); // call function
  void run_break(VM&); // stop at location return to prompt
  void run_step(VM&, s_int_t num=1); // step num of steps from bkpt
  void insert_instruction(us_int_t lno=0);
  void set_data_seg(VM&);
  void set_breakpoint(us_int_t bpt=0);
};
