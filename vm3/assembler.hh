#pragma once
#include "opcode.hh"
#include "assembly.hh"
#include "vm.hh"

#include "universe.hh"
#include "lang.hh"


class Assembler : public Assembly {
  friend class AssemblerInteractive;
  friend class Parser;
private:
  std::shared_ptr<Tree> context;
  //std::string 
  //  context_uni = CONTEXT_UNIV, current_app="myprog", current_api="myapi_0.00", 
  //  current_module="", current_function  = "", current_var="";
  
  full_symbol_t current_context;
  std::vector<unresolved_symbol_t> unresolved_syms;
  std::unordered_map<s_int_t, full_symbol_t> addr2sym_map;
//----
  s_int_t lvc=0;  // local variable count starting from %function
  s_int_t lac=-1; // local argument count starting from fp-1 backward toward calling stack.
  
  bool warning_print = false;

public:  
  s_int_t mvc=0;  // module variable count, aka GLOBAL variable to be accessed by parser as well.

  Assembler(std::shared_ptr<Tree> tp);
  Opcode lookup_opcode(const std::string& opname);
  void set_instruction(const instr_t &t);
  void insert_instruction();
  void run(VM& vm);
  void run_single_instruction(VM &vm); // this is for user command prompt eval
  void run_call(VM &vm, const std::string& m, const std::string& f); // this is for user command prompt eval

  void set_breakpoint(us_int_t bpt=0);
  void run_break(VM&); // stop at location return to prompt
  void run_step(VM&, s_int_t num=1); // step num of steps from bkpt

  void super_opfun_set_instruction(Opcode op, const full_symbol_t &fst);
  void super_op_branch(const std::string &labelstr);
  void print_program();
  void print_program_f();
  void print_ds_i();
  void print_ds_f();

  // add names to the symbol tree for later address lookup
  s_int_t add_app_name(const std::string &app);
  s_int_t add_api_name(const std::string &api);
  s_int_t add_module_name(const std::string &m);
  s_int_t add_mvar_name(const std::string &mv, int offset=1 ); // offset, [n] elements of an array 1 is
  s_int_t add_function_name(const std::string &f);
  s_int_t add_label_name(const std::string &l);
  s_int_t add_larg_name(const std::string &a);
  s_int_t add_lvar_name(const std::string &v, int n=1);


  void set_dataseg_adr_value(s_int_t madr, reg_t v);  

  void resolve_names();
  void add_unresolved_sym(const key_tok_t ktt, const full_symbol_t &fst, int oploc=-1);
  full_symbol_t lookup_current_function(VM& vm); // who and where am i function lookup

  full_symbol_t get_current_context() { return current_context; };
  std::vector<std::string> get_sym_key(const key_tok_t ktt,  const full_symbol_t &fst);
  s_int_t get_sym_addr(const key_tok_t ktt,  const full_symbol_t &fst);



  full_symbol_t dotstr2fst(key_tok_t ktt, const std::string& vs);
  full_symbol_t dotstr2modfun(const std::string& s);
  full_symbol_t dotstr2modvar(const std::string& s);
  full_symbol_t dotstr2mod(const std::string& s);

  us_int_t line_total_read=0; // to be used by Parser

};
