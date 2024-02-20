#pragma once
#include "vm.hh"

class Assembly {
protected:
  instr_t instruction = {Opcode(0), 0,0,0};
  instr_t code[1000];
  //Tree *context;
  us_int_t pc_load=0; // program counter at load program
public:
  //shared_ptr<TreeNode> resolve_symbol_node(const vector<std::string> &keys) const;
  void run(VM&);
};
