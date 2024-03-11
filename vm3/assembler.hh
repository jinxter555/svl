#pragma once
#include "opcode.hh"
#include "assembly.hh"
#include "vm.hh"

#define CONTEXT_UNIV "svlvm"
typedef struct {
  std::string uni, app, api, smodule, mvar, mfunction, lvar, larg, label;

} full_symbol_t;


//extern Instruction bytecode;
// enum class unresolved_t{
enum class key_tok_t {
  app=10, api, smodule, mvar, mvar_total_count,
  mfunction, lvar, larg, label
};
typedef struct {
  reg_t  location;  // address location of code[] where symbol is referenced
  key_tok_t type;     // type for svl lang, module, function, var,
  full_symbol_t name; // std::string sapp, sapi, smodule, sfunction, svar;
  int operand_loc;
} unresolved_symbol_t;

class Assembler : public Assembly {
  friend class AssemblerInteractive;
  friend class Parser;
private:
  Tree *context;

  //std::string 
  //  context_uni = CONTEXT_UNIV, current_app="myprog", current_api="myapi_0.00", 
  //  current_module="", current_function  = "", current_var="";
  full_symbol_t current_context;
  std::vector<unresolved_symbol_t> unresolved_syms;
  s_int_t lvc=0;  // local variable count starting from %function
  s_int_t lac=-1; // local argument count starting from fp-1 backward toward calling stack.
  s_int_t mvc=0;  // module variable count, aka GLOBAL variable
  
  bool warning_print = false;

public:  
  Assembler();
  Opcode lookup_opcode(const std::string& opname);
  void set_instruction(const instr_t &t);
  void insert_instruction();
  void run(VM& vm);
  void run_single_instruction(VM &vm); // this is for user command prompt eval
  void run_call(VM &vm, const std::string& m, const std::string& f); // this is for user command prompt eval

  void super_opfun_set_instruction(Opcode op, const full_symbol_t &fst);
  void print_program();
  void print_program_f();

  // add names to the symbol tree for later address lookup
  void add_app_name(const std::string &app);
  void add_api_name(const std::string &api);
  void add_module_name(const std::string &m);
  void add_mvar_name(const std::string &mv, int offset=1 ); // offset, [n] elements of an array 1 is
  void add_function_name(const std::string &f);
  void add_label_name(const std::string &l);
  void add_larg_name(const std::string &a);
  void add_lvar_name(const std::string &v, int n=1);

  void resolve_names();

  void add_unresolved_sym(const key_tok_t ktt, const full_symbol_t &fst);

  full_symbol_t get_current_context() { return current_context; };
  std::vector<std::string> get_sym_key(const key_tok_t ktt,  const full_symbol_t &fst);
  s_int_t get_sym_addr(const key_tok_t ktt,  const full_symbol_t &fst);

  full_symbol_t dotstr2fst(key_tok_t ktt, const std::string& vs);
  full_symbol_t dotstr2modfun(const std::string& s);
  full_symbol_t dotstr2modvar(const std::string& s);
  full_symbol_t dotstr2mod(const std::string& s);

  us_int_t line_total_read=0; // to be used by Parser

};