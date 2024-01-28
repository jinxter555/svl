#include "assembler_interactive.hh"

AssemblerInteractive::AssemblerInteractive(const string &hf, const string &ps) 
  : Prompt(hf, ps)  { 
  vm = new VM;
  assembler = new Assembler;
  vm->set_assembly((Assembly *) assembler);
};

  void interact(const string&);

void AssemblerInteractive::load(const string &filename) {
  assembler->load(filename);
}

void AssemblerInteractive::accept_prompt(const string &line) {
  parse_prompt(line);
  // print_line();
}

void AssemblerInteractive::parse_prompt(const string &line) {
  if(line[0] == '\\') { // command
    interact(line);
  } else { // assembly language
    if(!assembler->parse(line))
      cerr << "prompt error parsing!\n";
    if(!assembler->decode(true))
      cerr << "prompt error decoding!\n";
    else {
      // cout << "dispatching from prompt:\n";
      vm->dispatch(assembler->instruction);
    }
  }
}
void AssemblerInteractive::run_program() {
  //for(vm->pc=0; vm->pc < assembler->pc_load; vm->pc++) {
    //cout << "vm->pc: " << vm->pc << "\n";
    //print_instruction(vm->pc);
    //vm->dispatch(assembler->code[vm->pc]);

   for(vm->pc=0; vm->pc < assembler->pc_load;) {
    print_instruction(vm->pc);
    vm->dispatch(assembler->code[vm->pc++]); // note pc++ is here and not in for
  }
}

void AssemblerInteractive::interact(const string& line) {
  if(line == "\\print_register") print_vm_registers();
  if(line == "\\print_stack_int") print_vm_stack_int();
  if(line == "\\print_program") print_program();
  if(line == "\\run_program") run_program();
}

/*
void AssemblerInteractive::print_line() {
  if(opcode_str != "") cout << "op: " << opcode_str << " operands: ";
  for(int i=0; i<3; i++) {
    if(operands_str[i] == "") continue;
    cout << operands_str[i] << " ";
  }
  cout << "\n";
}
*/
void AssemblerInteractive::print_instruction(us_int_t pc) {
  auto instruction = assembler->code[pc];
  
  cout 
  << "code[" <<pc<< "]" 
  << ": " << int(instruction.opcode)  << " "
  << int(instruction.operands[0].i) << ","
  << int(instruction.operands[1].i) << ","
  << int(instruction.operands[2].i) << "\n";
}

/*
void AssemblerInteractive::print_vm_stack_int() {
  int i=0; reg_t  n ;
  std::stack<reg_t> temp_stack = vm->vmstack;
  cout << "print_stack_int\n";
  while(!temp_stack.empty()) {
    reg_t n = temp_stack.top();
    std::cout << i++ << ": " << n.i << "\n";
    temp_stack.pop();
    // if(i>20) break;
  }
  cout << "\n";
}
*/
void AssemblerInteractive::print_vm_stack_int() {
  int i=0;
  for (vector<reg_t>::iterator it = vm->vmstack.begin() ; it != vm->vmstack.end(); ++it) {
    cout << i++ << ": " << (*it).i << "\n";
  }
  std::cout << '\n';


}

void AssemblerInteractive::print_vm_registers(byte_code_t n) {
  for(byte_code_t i=0; i<n; i++) {
    cout << "R" << int(i) << ":" << vm->R[i].i << " ";
  }
  cout << "\n";
}

void AssemblerInteractive::print_program() {
  for(int i=0; i<assembler->pc_load; i++) {
    cout 
      << "code[" <<i<< "]" 
      <<  int(assembler->code[i].opcode) << " "  
      << "operands: "  
      <<  assembler->code[i].operands[0].i << ","  
      <<  assembler->code[i].operands[1].i << ","  
      <<  assembler->code[i].operands[2].i << "\n";
  }
}



