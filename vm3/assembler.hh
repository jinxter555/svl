#pragma once
#include "opcode.hh"
#include "assembly.hh"
#include "vm.hh"

#define CONTEXT_UNIV "svlvm"
typedef struct {
  std::string uni, sapp, sapi, smodule, mvar, sfunction, lvar;
  // type for svl lang
} full_symbol_t;

enum class unresolved_t{
  app=10, api, module, mvar,
  function, lvar, label
};
typedef struct {
  reg_t  location;
  // std::string sapp, sapi, smodule, sfunction, svar;
  unresolved_t type;
  // type for svl lang
  full_symbol_t name;
} unresolved_symbol_t;

class Assembler : public Assembly {
  friend class AssemblerInteractive;
private:
  Tree *context;

  //std::string 
  //  context_uni = CONTEXT_UNIV, current_app="myprog", current_api="myapi_0.00", 
  //  current_module="", current_function  = "", current_var="";
  full_symbol_t current_context;
  std::vector<unresolved_symbol_t> unresolved_syms;
  int lvc=0;  // local variable count starting from %function

  std::shared_ptr<TreeNode> resolve_symbol_node(const std::vector<std::string> &keys) const;

public:  
  Assembler();
  Opcode lookup_opcode(const std::string& opname);
  void set_instruction(const instr_t &t);
  void insert_instruction();
  void run(VM& vm);
  void run_single_instruction(VM &vm); // this is for user command prompt eval

  void super_opfun_set_instruction(Opcode op, const full_symbol_t &fst);
  void print_program();

  // add names to the symbol tree for later address lookup
  void add_app_name(const std::string &app);
  void add_api_name(const std::string &api);
  void add_module_name(const std::string &m);
  void add_function_name(const std::string &f);
  void add_label_name(const std::string &l);
  void add_lvar_name(const std::string &v);

  void add_unresolved_function(const full_symbol_t &fst);
  void add_unresolved_var(const std::string &m, const std::string &f, const std::string &v);
  full_symbol_t get_current_context() { return current_context; };
  void resolve_names();


};