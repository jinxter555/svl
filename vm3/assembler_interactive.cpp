#include "assembler_interactive.hh"
#include "my_helpers.hh"

std::vector<std::string> AssemblerInteractive::commands = {
  "!print_tree",
  "!print_register",
  "!print_register_int",
  "!print_register_float",
  "!print_stack_int",
  "!print_stack_float",
  "!print_program",
  "!print_program_float",
  "!run_program",
  "!call",
  ""
};

AssemblerInteractive::AssemblerInteractive(const std::string &hf, const std::string &ps) 
  : Prompt(hf, ps) {
    //vm = new VM;
    //assembler = new Assembler;
  setup_ui_commands();

}

void AssemblerInteractive::accept_prompt(const std::string &line) {
  parse_prompt(line);
  // print_line();
}
void AssemblerInteractive::parse_prompt(const std::string &line) {
   if(line[0] == '!') { // command
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
  assembler.resolve_names();
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

void AssemblerInteractive::interact(const std::string& cline) {
  std::string line = cline;
  line.erase(line.find_last_not_of(" ")+1);
  std::string rest_tree =  match(line, "!print_tree");
  std::string rest_call =  match(line, "!call ");
  if(line == "!print_tree" || rest_tree != "" ) print_tree(rest_tree);
  if(line == "!print_register") print_vm_registers(12);
  if(line == "!print_register_int") print_vm_registers(12);
  if(line == "!print_register_float") print_vm_registers_float();
  if(line == "!print_stack_int") print_vm_stack_int();
  if(line == "!print_stack_float") print_vm_stack_float();
  if(line == "!print_program") print_program();
  if(line == "!print_program_float") print_program_f();
  if(line == "!run_program") run_program();
  if(line == "!call" || rest_call !="") call_func(rest_call); // setup up add end of code[] with call func , and exit
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
void AssemblerInteractive::print_program_f(){
  assembler.print_program_f();
}

void AssemblerInteractive::print_tree(const std::string &cline){
  std::string line = cline;
  line.erase(line.find_last_not_of(" ")+1);


  std::vector<std::string> vstr = split_string(line, " ");
  vstr.erase(vstr.begin()); // erase empty element

//  for(auto s : vstr) { std::cout << "s: '" << s << "'\n"; }

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
void AssemblerInteractive::call_func(const std::string &line) {
  std::cout << "calling function: '" << line  << "'\n";
  std::vector<std::string> vstr = split_string(line, ":");
  if(vstr.size() == 1) {std::cerr << "you have to specify module\n";return;}
  assembler.run_call(vm, vstr[0], vstr[1]);

}
void AssemblerInteractive::setup_ui_commands() {
  std::string command; int list_index=0;
  std::vector<std::string> key;
  //std::cout << "set ui commandsize:" << commands.size() << "\n";

  // while((command = commands[list_index++]) != "") {
  for(auto command : AssemblerInteractive::commands) {
    if(command =="") continue;
    std::cout << "adding command " << command << "\n";
    key = {rlac_current_context_key, command};
    assembler.context->add_node({key}, 1);
  }
}

extern AssemblerInteractive ait;
char* AssemblerInteractive_command_generator(const char *text, int state) {
  std::string textstr(text), command;
  static int list_index, len;

  if(!state) {
    list_index = 0;
    len = strlen(text);
  }

  while((command = AssemblerInteractive::commands[list_index++]) != "") {
  // for(auto command : AssemblerInteractive::commands) {
    if( command.compare(0, len, textstr) == 0) {
      return strdup(command.c_str());
    }
  }
  return nullptr;
}

char** AssemblerInteractive_command_completion(const char *text, int start, int end) {
  char **matches, *match;
  std::string matchstr;
  rl_attempted_completion_over = 1;

  return  rl_completion_matches(text, AssemblerInteractive_command_generator);
  //matches = rl_completion_matches(text, AssemblerInteractive_command_generator);
  //return matches;

}