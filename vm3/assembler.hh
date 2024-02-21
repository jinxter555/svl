#pragma once
#include "opcode.hh"
#include "assembly.hh"
#include "vm.hh"

class Assembler : public Assembly {
  friend class AssemblerInteractive;
private:
public:
  Opcode lookup_opcode(const std::string& opname);
  // void decoder ( std::string opname="" , reg_t operand1=0l , reg_t operand2 , reg_t operand3);
  void set_instruction(const instr_t &t);
  void insert_instruction();
  void run(VM& vm);
  void run_single_instruction(VM &vm);

  void print_program();
};

