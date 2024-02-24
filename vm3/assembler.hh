#pragma once
#include "opcode.hh"
#include "assembly.hh"
#include "vm.hh"

#define CONTEXT_UNIV "svlvm"
typedef struct full_symbol_s {
  std::string sapp, sapi, smodule, sfunction, svar;
} full_symbol_t;

typedef struct symbol_2 {
  reg_t  location;
  std::string sapp, sapi, smodule, sfunction, svar;
} unresolved_symbol_t;

class Assembler : public Assembly {
  friend class AssemblerInteractive;
private:
  Tree *context;

  std::string 
    context_uni = CONTEXT_UNIV, current_app="myprog", current_api="myapi_0.00", 
    current_module="", current_function  = "", current_var="";
  std::vector<unresolved_symbol_t> unresolved_names;
  int lvc=0;  // local variable count starting from %function

  
  // add names to the symbol tree for later address lookup
  void add_app_name(const std::string &app);
  void add_api_name(const std::string &api);
  void add_module_name(const std::string &m);
  void add_function_name(const std::string &f);
  void add_label_name(const std::string &l);
  void add_var_name(const std::string &v);

  void add_unresolved_function(const std::string &m, const std::string &f);
  void add_unresolved_var(const std::string &m, const std::string &f, const std::string &v);

  std::shared_ptr<TreeNode> resolve_symbol_node(const std::vector<std::string> &keys) const;
public:  
  Assembler();
  Opcode lookup_opcode(const std::string& opname);
  void set_instruction(const instr_t &t);
  void insert_instruction();
  void run(VM& vm);
  void run_single_instruction(VM &vm);

  void super_op(Opcode op, const std::string operand1, const std::string operand2="", const std::string operand3="");
  void super_op_fun(Opcode op, const full_symbol_t &fst);
  void print_program();
};