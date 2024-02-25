#include <iostream>
#include "assembler.hh"


Assembler::Assembler() {
  context = new Tree();
  current_context = {
    CONTEXT_UNIV, 
    "myprog", 
    "myapi_0.00",
    "", // mod
    "", // fun
    "", // var
  };
};

Opcode Assembler::lookup_opcode(const std::string& opname) {
  auto it = opcode_table.find(opname);
  if(it != opcode_table.end()) {
    return it->second;
  } else {
    return Opcode::INVALID;
  }
}

void Assembler::run(VM& vm) {
  Assembly::run(vm);
}
void Assembler::run_single_instruction(VM& vm) {
  Assembly::run_single_instruction(vm);
}
void Assembler::set_instruction(const instr_t &t) {
  Assembly::instruction = t;
}

void Assembler::insert_instruction() {
  Assembly::insert_instruction();
}
void Assembler::print_program() {
  for(int i=0; i<pc_load; i++) {
    std::cout 
      << "code[" <<i<< "]" 
      <<  int(code[i].opcode) << " "  
      << "operands: "  
      <<  code[i].operands[0].i << ","  
      <<  code[i].operands[1].i << ","  
      <<  code[i].operands[2].i << "\n";
  }
}
void Assembler::add_app_name(const std::string &app) {
  current_context.sapp = app;
  context->add_node({
    current_context.uni, 
    current_context.sapp,
    "addr"}, pc_load);
}
void Assembler::add_api_name(const std::string &api) {
  current_context.sapi = api;
  context->add_node({
    current_context.uni, 
    current_context.sapp,
    current_context.sapi, 
    "addr"}, pc_load);
}
void Assembler::add_module_name(const std::string &m) {
  current_context.smodule = m;
  context->add_node({
    current_context.uni, 
    current_context.sapp,
    current_context.sapi, 
    current_context.smodule,
    "addr"}, pc_load);
}
void Assembler::add_function_name(const std::string &f) {
  current_context.sfunction = f; 
  // current_var = ""; // clear out var so, %call fun1 won't return variable
  lvc = 0; // init lvc local variable counter, it should be similar to vp variable pointer
  context->add_node({
    current_context.uni, 
    current_context.sapp,
    current_context.sapi, 
    current_context.smodule,
    current_context.sfunction,
    "addr"}, pc_load);
}
void Assembler::add_label_name(const std::string &l) {
  context->add_node({
    current_context.uni, 
    current_context.sapp,
    current_context.sapi, 
    current_context.smodule,
    current_context.sfunction,
    l, "addr"}, pc_load);
}

// the address location will be point to the stack realtive from fp,fp+vp
void Assembler::add_lvar_name(const std::string &v) {
  current_context.lvar = v;
  context->add_node({
  current_context.uni, 
  current_context.sapp,
  current_context.sapi, 
  current_context.smodule,
  current_context.sfunction,
  current_context.lvar, 
  "addr"}, lvc++);
}

/*
void Assembler::super_op(Opcode op, const std::string operand1, std::string operand2, std::string operand3) {
  switch(op) {
  case Opcode::CALL: 
    //add_unresolved_function(current_module, operand1);
    break;
  default: break;
  }
}*/

std::shared_ptr<TreeNode> Assembler::resolve_symbol_node(const std::vector<std::string>& keys) const {
  auto curr = context->get_node(keys);
  return curr; 
}



void Assembler::add_unresolved_function(const full_symbol_t &fst) {
  unresolved_symbol_t  notfound;
  notfound.name = current_context;
  notfound.name.smodule = fst.smodule;
  notfound.name.sfunction = fst.sfunction;
  notfound.type = unresolved_t::function ;
  notfound.location.adr = pc_load;
  unresolved_syms.push_back(notfound);
  std::cerr << "adding to not found: '" << fst.smodule << ":" << fst.sfunction << "' to unresolved vector\n";

}


void Assembler::super_opfun_set_instruction(Opcode op, const full_symbol_t &fst) {
  s_int_t adr = -1;
  std::shared_ptr<TreeNode> sym_node = context->get_node({
    current_context.uni, 
    current_context.sapp,
    current_context.sapi, 
    fst.smodule, 
    fst.sfunction, 
    "addr"});

  if(sym_node == nullptr) {
    std::cout << "function '" << fst.sfunction << "' not found\n";
    add_unresolved_function(fst);
  } else {
    adr = std::any_cast<s_int_t>(sym_node->get_data());
  }
  instr_t asm_instr = {op, adr,0,0};
  set_instruction(asm_instr); 
}

#define __fkeys__ {us.name.uni, us.name.sapp, us.name.sapi, us.name.smodule, us.name.sfunction, "addr"}
void Assembler::resolve_names() {
  // gothru all vector unresolvednames
  std::vector<std::string> keys;
  std::shared_ptr<TreeNode> sym_node;
  // std::cout << "trying unresolved symbols\n";

  for(auto us  : unresolved_syms) {
    // std::cout << "unresolved sym:'" << us.name.sfunction << "'\n";
    switch(us.type) {
    case unresolved_t::mvar:  break;
    case unresolved_t::function:  
      sym_node = context->get_node(__fkeys__);
      if(sym_node != nullptr) {
        std::cout << "resolving function: '" << us.name.sfunction << "'\n";
        code[us.location.adr].operands[0].adr
          = std::any_cast<s_int_t>(sym_node->get_data());
      } else { 
        std::cerr << "can't resolve symbol: nullptr\n"; 
      }

      break;
    case unresolved_t::lvar:  break;
    default: break;
    }
  }
}
