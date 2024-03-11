#pragma once
#include "vm.hh"
#include "tree.hh"

#define MAX_CODE_SIZE 5000

class Assembly {
protected:
  instr_t instruction = {Opcode(0), 0,0,0};

  instr_t code[MAX_CODE_SIZE];    
  // instruction pointing to actual src line no. macro expansion
  // and so on this is used for debugging break line and so on
  us_int_t line_no[MAX_CODE_SIZE]; 

  std::vector<reg_t> data_seg;
  s_int_t pc_load=0; // program counter at load program
public:
  void run(VM&);
  void run_single_instruction(VM&);
  void run_call(VM&, s_int_t start_pc);
  void insert_instruction(us_int_t lno=0);
  void set_data_seg(VM&);
};
