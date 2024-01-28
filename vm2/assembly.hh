#pragma once
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include "vm.hh"
#include "tree.hh"

using namespace std;

typedef unsigned char elevel_t;

class Assembly {
  // friend class VM; 
  friend class Assembler;
protected:
  instr_t instruction = {0, 0, 0, 0};
  instr_t code[1000];
  Tree *context;

  // mdoule , function, global variable, symbol tree lookup
  us_int_t pc_load=0;    // program counter at load

public:
  void dispatch();
  shared_ptr<TreeNode> resolve_symbol_node(const vector<string> &keys) const ;
  
  
  // Assembly(const string &hf, const string &ps) : Prompt(hf, ps) {};
  // void accept(const string &) override;

  static map<string, byte_code_t> asm_str_lookup ;
};