#include <stdio.h>
#include "assembler_interactive.hh"
#include "my_helpers.hh"

std::vector<std::string> AssemblerInteractive::commands = {
  "!print_tree",
  "!print_register",
  "!print_register_int",
  "!print_register_float",
  "!print_stack_int",
  "!print_stack_float",
  "!print_ds_int",
  "!print_ds_float",
  "!print_program",
  "!print_src",
  "!print_src_break",
  "!print_program_float",
  "!print_current_function",
  "!run_program",
  "!call",
  "!break",
  "!step",
  "!run_break",
  ""
};

extern AssemblerInteractive ait;
static std::vector<std::string> AssemblerInteractive_cui_keys={};

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
   if(line[0] == '!') { // command
    interact(line);
  } else { // assembly language
    //if(line[0]== '%' && line[1]=='%') return; // ignore assembler directive
    parse(line);
  }
}

void AssemblerInteractive::loadsrc(std::ifstream &fs) {
  std::string line;
  while(std::getline(fs,  line))
    source[line_read_count++].line_str = line;
  fs.clear(); fs.seekg(0);
}

void AssemblerInteractive::load(const std::string &cfn) {
  std::vector<std::string> filenames = split_string(cfn, " ");

  for(auto filename : filenames) {
    std::ifstream infile(filename);
    if(infile.is_open()) {
      loadsrc(infile); // read to src and reset
      scanner.switch_streams(&infile, &std::cerr);
      parser.parse();
    } else {
      std::cerr << "Error opening assembly file: " << filename << "\n";
    }
    infile.close();
  }
  assembler.resolve_names();
  scanner.switch_streams(&std::cin, &std::cerr);
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
  std::string rest_break =  match(line, "!break");
  std::string rest_step =  match(line, "!step");
  std::string rest_psb =  match(line, "!print_src_break");
  std::string rest_plvar =  match(line, "!print_current_function");
  if(line == "!print_tree" || rest_tree != "" ) print_tree(rest_tree);
  if(line == "!print_register") print_vm_registers(12);
  if(line == "!print_register_int") print_vm_registers(12);
  if(line == "!print_register_float") print_vm_registers_float();
  if(line == "!print_stack_int") print_vm_stack_int();
  if(line == "!print_stack_float") print_vm_stack_float();
  if(line == "!print_src") print_src();
  if(line == "!print_src_break" ||  rest_psb != "") print_src_break(rest_psb);
  if(line == "!print_ds_int") assembler.print_ds_i();
  if(line == "!print_ds_float") assembler.print_ds_f();
  if(line == "!print_program") print_program();
  if(line == "!print_current_function" || rest_plvar != "") print_current_function(rest_plvar);
  if(line == "!print_program_float") print_program_f();
  if(line == "!run_program") run_program();
  if(line == "!run_break") run_break();
  if(line == "!break" || rest_break != "" ) set_breakpoint(rest_break);
  if(line == "!step" || rest_step != "" ) run_step(rest_step);
  if(line == "!call" || rest_call !="") call_func(rest_call); // setup up add end of code[] with call func , and exit
  AssemblerInteractive_cui_keys.clear();
}


void AssemblerInteractive::set_breakpoint(const std::string& bstr) {
  us_int_t bpt = std::strtoll(bstr.c_str(), nullptr, 10);
  assembler.set_breakpoint(bpt);
}
void AssemblerInteractive::run_step(const std::string& bstr) {
  us_int_t num = std::strtoll(bstr.c_str(), nullptr, 10);
  assembler.run_step(vm, num);
}
void AssemblerInteractive::run_break() {
  assembler.run_break(vm);
}

void AssemblerInteractive::print_vm_stack_int() {
  int i=0;
  Frame frame=vm.get_current_frame();
  // for (std::vector<reg_t>::iterator it = vm->vmstack.begin() ; it != vm->vmstack.end(); ++it) {
  for (std::vector<reg_t>::iterator it = vm.vmstack.begin() ; it != vm.vmstack.end(); ++it) {
    //std::cout  << "frame.fp: " << frame.fp << "\n";
    if(frame.fp == i) std::cout << "----cf----\n";
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

void AssemblerInteractive::print_current_function(const std::string& clvar){
  std::string lvar = trim(clvar);

  full_symbol_t fst = assembler.lookup_current_function(vm);
  std::cout << fst.smodule + ":" + fst.mfunction << "\n";
  if(clvar == "")  return;

  fst.lvar = lvar;
  s_int_t lvar_addr = assembler.get_sym_addr(key_tok_t::lvar, fst);
  Frame current_frame = vm.get_current_frame();
  s_int_t loc = current_frame.fp + lvar_addr;
  reg_t value = vm.vmstack[loc];
  std::cout 
    << fst.smodule + ":" + fst.mfunction + " " + lvar + "\n"
    << " addr: " << lvar_addr << "\n"
    << " ivalue: " << value.i << "\n"
    << " fvalue: " << value.f << "\n\n";
}

void AssemblerInteractive::print_src(){
  char istr[16];
  for(unsigned int i=0; i<line_read_count; i++) {
    snprintf(istr, 16, "code[%06d]: ", i);
    //sprintf(istr, "code[%06d]: ", i);
    std::cout << istr << source[i].line_str  << "\n";
  }
}
void AssemblerInteractive::print_src_break(const std::string &cnumstr){
  char istr[16];
  std::string numstr;
  int breakpoint = assembler.Assembly::breakpoint;
  if(cnumstr == "") numstr = std::string("10");
  us_int_t num = std::strtoll(numstr.c_str(), nullptr, 10);

  for(unsigned int i=breakpoint; i<breakpoint + num; i++) {
    snprintf(istr, 16, "code[%06d]: ", i);
    //sprintf(istr, "code[%06d]: ", i);
    std::cout << istr << source[i].line_str  << "\n";
  }
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
void AssemblerInteractive::set_ui_commands() {
  std::string command; int list_index=0;
  std::vector<std::string> keys;
  //std::cout << "set ui commandsize:" << commands.size() << "\n";

  for(auto command : AssemblerInteractive::commands) {
    if(command =="") continue;
    keys = {rlac_current_context_key, command};
    assembler.context->add_node({keys}, 1);
  }

  std::shared_ptr<TreeNode> ptree_node = assembler.context->get_node({rlac_current_context_key, "!print_tree"});
  if(ptree_node!=nullptr) {
    std::shared_ptr<TreeNode> uni_node = assembler.context->get_node({CONTEXT_UNIV});
    ptree_node->add_child({CONTEXT_UNIV}, uni_node);
  } else
    std::cerr << "Can't add the universe to !print_tree\n";
}
std::vector<std::string> AssemblerInteractive::get_ui_commands(const std::vector<std::string> &ptk) {
  std::vector<std::string> keys;
  std::vector<std::string> children;
  keys = {rlac_current_context_key};
  keys.insert(keys.end(), ptk.begin(), ptk.end());
  
  // std::cout << "keys: "; for(auto k: keys) { std::cout << k << ","; } std::cout << "\n";

  children = assembler.context->get_children(keys);
  children.push_back("");
  return children;
}


void convert_buff_to_keys() {
  std::string rlbuff=trim(rl_line_buffer);
  AssemblerInteractive_cui_keys.clear();
  if(rl_line_buffer!=NULL)
    AssemblerInteractive_cui_keys = split_string(rlbuff, " ");
}


char* AssemblerInteractive_command_generator(const char *text, int state) {
  std::vector<std::string> commands = move(ait.get_ui_commands(AssemblerInteractive_cui_keys));
  std::string textstr(text), command;
  static int list_index, len; 

  if(!state) {
    list_index = 0;
    len = strlen(text);
  }  
  
  // std::cout << " keys:" << AssemblerInteractive_cui_keys.size() << ":"; for(auto k: AssemblerInteractive_cui_keys) { std::cout << k << ","; } std::cout <<"\n";

  // while((command = AssemblerInteractive::commands[list_index++]) != "") {
  while((command = commands[list_index++]) != "") {
    if( command.compare(0, len, textstr) == 0) {
      return strdup(command.c_str());
    }
  }
  return nullptr;
}

char** AssemblerInteractive_command_completion(const char *text, int start, int end) {
  char **matches, *match;
  std::string matchstr, rematch;
  rl_attempted_completion_over = 1;

  if(std::string(rl_line_buffer)  == "") AssemblerInteractive_cui_keys.clear();
  if(rl_line_buffer[strlen(rl_line_buffer)-1] == ' ') {convert_buff_to_keys(); }

  matches = rl_completion_matches(text, AssemblerInteractive_command_generator);

  if(matches == nullptr && strlen(text) > 0) {     // if stuck from previous command didn't complete properly
    convert_buff_to_keys(); 
    if(!AssemblerInteractive_cui_keys.empty()) 
      rematch = AssemblerInteractive_cui_keys.back();
      AssemblerInteractive_cui_keys.pop_back();
      matches = rl_completion_matches(rematch.c_str(), AssemblerInteractive_command_generator);
  }

  return  matches;
}
