#include "assembler_interactive.hh"
#include "my_helpers.hh"

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
  assembler.run_single_instruction(vm);

}

void AssemblerInteractive::run_program() {
  assembler.run(vm);
}

void AssemblerInteractive::interact(const std::string& line) {
  std::string rest;
  
  rest =  match(line, "\\print_tree");
  if(line == "\\print_tree" || rest != "" ) print_tree(rest);
  if(line == "\\print_register") print_vm_registers();
  if(line == "\\print_register_int") print_vm_registers();
  if(line == "\\print_register_float") print_vm_registers_float();
  if(line == "\\print_stack_int") print_vm_stack_int();
  if(line == "\\print_stack_float") print_vm_stack_float();
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

void AssemblerInteractive::print_vm_stack_float() {
  int i=0;
  // for (std::vector<reg_t>::iterator it = vm->vmstack.begin() ; it != vm->vmstack.end(); ++it) {
  for (std::vector<reg_t>::iterator it = vm.vmstack.begin() ; it != vm.vmstack.end(); ++it) {
    std::cout << i++ << ": " << (*it).f << "\n";
  }
  std::cout << '\n';
}

void AssemblerInteractive::print_vm_registers(int n) {
  for(int i=0; i<n; i++) {
    std::cout << "R" << int(i) << ":" << vm.R[i].i << " ";
  }
  std::cout << "\n";
}
void AssemblerInteractive::print_vm_registers_float(int n) {
  for(int i=0; i<n; i++) {
    std::cout << "R" << int(i) << ":" << vm.R[i].f << " ";
  }
  std::cout << "\n";
}

void AssemblerInteractive::print_program(){
  assembler.print_program();
}

void AssemblerInteractive::print_tree(const std::string &line){
  std::vector<std::string> vstr = split_string(line, " ");
  vstr.erase(vstr.begin()); // erase empty element

  // for(auto s : vstr) { std::cout << "s: '" << s << "'\n"; }
  auto children = assembler.context->get_children(vstr);
  for(auto c : children) { std::cout << "child: " << c << "\n"; }
  auto node = assembler.context->get_node(vstr);
  if(node) {std::cout << "value: "; node->print_data(); std::cout << "\n";}



};


std::string AssemblerInteractive::match(const std::string& line, const std::string& pattern) {
  std::smatch match;
  std::regex regex(pattern);

  if (std::regex_search(line, match, regex)) {
    // Match found, return the rest of the line after the match
    return line.substr(match.position() + match.str(0).size());
  } else {
    // No match found, return an empty string
    return "";
  }
}