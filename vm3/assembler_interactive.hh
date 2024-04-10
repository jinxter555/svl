#include <sstream>
#include <regex>
#include "prompt.hh"
#include "assembler.hh"
#include "vm.hh"
#include "asm_parser.hh"
#include "asm_scanner.hh"

#define rlac_current_context_key   CONTEXT_UNIV, "ac_commands"

typedef struct {
  us_int_t line_no;
  std::string  line_str;
} src_t;

//class AssemblerInteractive : public Prompt {
class AssemblerInteractive : public LangPrompt {
private:
  VM vm;
  Assembler assembler;
  us_int_t line_read_count=0; 

  src_t source[MAX_CODE_SIZE];

  vslasm::AsmScanner asm_scanner{ std::cin, std::cerr };
  vslasm::AsmParser asm_parser{ &asm_scanner, &assembler};

  void interact(const std::string&);
  void parse_prompt(const std::string&);

  void print_tree(const std::string &line);  
  void print_vm_registers(int n=8);  
  void print_vm_registers_float(int n=8);  
  void print_vm_stack_int();
  void print_vm_stack_float();
  void print_src();
  void print_src_break(const std::string& numstr="10");
  void print_ds();
  void print_program();
  void print_program_f();
  void call_func(const std::string &line);

  std::string match(const std::string& line, const std::string& pattern);
public:
  AssemblerInteractive(const std::string &, const std::string &);
  void accept_prompt(const std::string&) override;
  void loadsrc(std::ifstream &fs);
  void load(const std::string &filename);
  void parse(const std::string &line);
  void run_program();

  void set_ui_commands();
  std::vector<std::string> get_ui_commands(const std::vector<std::string> &ptk={});

  void set_breakpoint(const std::string& bstr);
  void run_break(); // stop at location return to prompt
  void run_step(const std::string& bstr ); // step num of steps from bkpt

  void print_current_function(const std::string& lvstr);

  Assembler* getAssembler() { return &assembler;}

  static std::vector<std::string> commands;
  static std::vector<std::string> cui_keys;

  static char** command_completion(const char *text, int start, int end);
  static char* command_generator(const char *text, int state);
  static void convert_buff_to_keys();

}; 

