#pragma once
#include "vm.hh"
#include "tree.hh"

class Assembly {
protected:
  instr_t instruction = {Opcode(0), 0,0,0};
  instr_t code[1000];
  s_int_t pc_load=0; // program counter at load program
public:
  void run(VM&);
  void run_single_instruction(VM&);
  void run_call(VM&, s_int_t start_pc);
  void insert_instruction();
};
