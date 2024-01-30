#pragma once
#include "assembly.hh"


typedef struct symbol_1 {
  string smodule, sfunction, svar;
} symbol_t;

typedef struct symbol_2 {
  reg_t  location;
  string smodule, sfunction, svar;
} unresolved_t;



class Assembler : public Assembly {
  friend class AssemblerInteractive;
protected:
  // vector<string> module_structure_names;
  int lvc=0;  // local variable count starting from %function
  string current_module="", current_function  = "", current_var="";
  string opcode_str="", operands_str[3] = {"", "", ""};

  vector<unresolved_t> unresolved_names;

public:
  Assembler();
  void run(VM &vm);
  void run1(VM &vm);

  void load(const string &filename);
  void reload();
  void reset();
  void load_bin(string &filename);
  void save_bin(string &filename);

  bool parse(const string &);  
  //elevel_t parse_assembly(const string &);  
  bool parse_instruction_string(const string &);  
  bool parse_directive(const string &);

  void clear_line();
  bool decode(bool from_prompt=false);
private:

  bool opcode2bin();           // opcode_str to bin 
  bool operands2bin(const string&, reg_t&);           // operands_str to bin. return 0 on success
  bool is_float(const string&); //
  bool is_integer(const string&); //

  bool decode_call();
  void add_unresolved_name(const string &m, const string &f, const string &v);
  void resolve_names();


};
