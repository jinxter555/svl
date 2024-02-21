#pragma once
#include "vm.hh"
#include "tree.hh"

class Assembly {
protected:
  instr_t instruction = {Opcode(0), 0,0,0};
  instr_t code[1000];
  Tree *context;
  us_int_t pc_load=0; // program counter at load program
public:
  std::shared_ptr<TreeNode> resolve_symbol_node(const std::vector<std::string> &keys) const;
  void run(VM&);
  void run_single_instruction(VM&);
  void insert_instruction();
};
