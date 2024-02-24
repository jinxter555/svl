#include <iostream>
#include "assembler.hh"


Assembler::Assembler() {
  context = new Tree();
  context->add_node({"key1"}, std::string("workjob"));
  context->add_node({"key1", "key2"}, 1);
  context->add_node({"key1", "key2", "key3b"}, 123);
  context->add_node({"key1", "key3"}, std::string("hello"));
  context->add_node({"key4", "key5"}, 3.145);

  context->add_node({"key1"}, std::string("workjob3"));
  std::cout << "context init" <<"\n";

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
  current_app = app;
  context->add_node({context_uni, current_app, "addr"}, pc_load);
}
void Assembler::add_api_name(const std::string &api) {
  current_api = api;
  context->add_node({
    context_uni, current_app,
    current_api, "addr"}, pc_load);
}
void Assembler::add_module_name(const std::string &m) {
  current_module = m;
  context->add_node({
    context_uni, current_app,
    current_api, current_module, "addr"}, pc_load);
}
void Assembler::add_function_name(const std::string &f) {
  current_function = f; 
  // current_var = ""; // clear out var so, %call fun1 won't return variable
  lvc = 0; // init lvc local variable counter, it should be similar to vp variable pointer
  context->add_node({
    context_uni, current_app, current_api, 
    current_module, current_function, "addr"}, pc_load);
}
void Assembler::add_label_name(const std::string &l) {
  context->add_node({
    context_uni, current_app, current_api, 
    current_module, current_function, l, "addr"}, pc_load);
}

// the address location will be point to the stack realtive from fp,fp+vp
void Assembler::add_var_name(const std::string &v) {
  current_var = v;
  context->add_node({context_uni, current_app, current_api, 
  current_module, current_function, current_var, "addr"}, lvc++);
}

void Assembler::super_op(Opcode op, const std::string operand1,
  std::string operand2, std::string operand3) {
  switch(op) {
  case Opcode::CALL: 
    add_unresolved_function(current_module, operand1);
    break;
  default: break;
  }
}

std::shared_ptr<TreeNode> Assembler::resolve_symbol_node(const std::vector<std::string>& keys) const {
  auto curr = context->get_node(keys);
  return curr; 
}



void Assembler::add_unresolved_function(const std::string &m, const std::string &f) {
  unresolved_symbol_t  notfound_name;
  std::cerr << "adding to not found to unresolved vector\n";
  notfound_name.location.adr = pc_load;
  notfound_name.smodule=m; //tokens_s[1], ""};
  notfound_name.sfunction=f; //tokens_s[1], ""};
  unresolved_names.push_back(notfound_name);
}


void Assembler::super_op_fun(Opcode op, const full_symbol_t &fst) {

}