#pragma once

#include "prompt.hh"
#include "assembler.hh"

class AssemblerInteractive : public Prompt {
private:
  VM *vm;
  Assembler *assembler;
public:

  AssemblerInteractive(const string &, const string &);

  void interact(const string&);
  void parse_prompt(const string&);
  void accept_prompt(const string&) override;

  void load(const string &filename);
  void set_vm(VM *vm);

  // printing
  // void print_line();
  void print_program();
  void run_program();
  void run_program2();
  void print_instruction(us_int_t pc);
  void print_vm_stack_int();
  void print_vm_registers(byte_code_t n=8);     //  print default r1..r8 registers

};