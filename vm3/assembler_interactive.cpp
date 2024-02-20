#include "assembler_interactive.hh"

AssemblerInteractive::AssemblerInteractive(const std::string &hf, const std::string &ps) 
  : Prompt(hf, ps) {
    //vm = new VM;
    //assembler = new Assembler;

}

void AssemblerInteractive::accept_prompt(const std::string &line) {
  parse_prompt(line);
  // print_line();
}
void AssemblerInteractive::parse_prompt(const std::string &line) {
   if(line[0] == '\\') { // command
    interact(line);
  } else { // assembly language
    parse(line);
  }
}

void AssemblerInteractive::load(const std::string &filename) {
  std::ifstream infile(filename);
  if(infile.is_open()) {
    scanner.switch_streams(&infile, &std::cerr);
    parser.parse();
  } else {
    std::cerr << "Error from assembly file: " << filename << "\n";
  }
  scanner.switch_streams(&std::cin, &std::cerr);
  infile.close();
}

void AssemblerInteractive::parse(const std::string &line) {
  std::istringstream input_buffer(line);
  scanner.switch_streams(&input_buffer, &std::cerr);
  parser.parse();
}

void AssemblerInteractive::run_program() {
  //assembler.run(vm);
}

void AssemblerInteractive::interact(const std::string& line) {
  if(line == "\\print_register") print_vm_registers();
  if(line == "\\print_stack_int") print_vm_stack_int();
  if(line == "\\print_program") print_program();
  if(line == "\\run_program") run_program();
}

void AssemblerInteractive::print_vm_stack_int() {
  int i=0;
  // for (std::vector<reg_t>::iterator it = vm->vmstack.begin() ; it != vm->vmstack.end(); ++it) {
  for (std::vector<reg_t>::iterator it = vm.vmstack.begin() ; it != vm.vmstack.end(); ++it) {
    std::cout << i++ << ": " << (*it).i << "\n";
  }
  std::cout << '\n';
}

void AssemblerInteractive::print_vm_registers(){};
void AssemblerInteractive::print_program(){};

