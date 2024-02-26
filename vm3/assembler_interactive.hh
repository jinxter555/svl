#include <sstream>
#include <regex>
#include <FlexLexer.h>
#include "prompt.hh"
#include "assembler.hh"
#include "vm.hh"
#include "Parser2.hh"
#include "Scanner2.hh"


class AssemblerInteractive : public Prompt {
private:
  VM vm;
  Assembler assembler;
  vslasm::Scanner scanner{ std::cin, std::cerr };
  vslasm::Parser parser{ &scanner, &assembler};

  void interact(const std::string&);
  void parse_prompt(const std::string&);

  void print_tree(const std::string &line);  
  void print_vm_registers(int n=8);  
  void print_vm_registers_float(int n=8);  
  void print_vm_stack_int();
  void print_vm_stack_float();
  void print_program();
  void print_program_f();
  void call_func(const std::string &line);

  std::string match(const std::string& line, const std::string& pattern);
public:
  AssemblerInteractive(const std::string &, const std::string &);
  void accept_prompt(const std::string&) override;
  void load(const std::string &filename);
  void parse(const std::string &line);
  void run_program();
}; 

