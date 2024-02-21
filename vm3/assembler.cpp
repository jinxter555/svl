#include <iostream>
#include "assembler.hh"

Opcode Assembler::lookup_opcode(const std::string& opname) {
  auto it = opcode_table.find(opname);
  if(it != opcode_table.end()) {
    return it->second;
  } else {
    return Opcode::INVALID;
  }
}

void Assembler::run(VM& vm) {
  Assembly::run(vm);
}
void Assembler::run_single_instruction(VM& vm) {
  Assembly::run_single_instruction(vm);
}
void Assembler::set_instruction(const instr_t &t) {
  Assembly::instruction = t;
}

void Assembler::insert_instruction() {
  Assembly::insert_instruction();
}
void Assembler::print_program() {
  for(int i=0; i<pc_load; i++) {
    std::cout 
      << "code[" <<i<< "]" 
      <<  int(code[i].opcode) << " "  
      << "operands: "  
      <<  code[i].operands[0].i << ","  
      <<  code[i].operands[1].i << ","  
      <<  code[i].operands[2].i << "\n";
  }
}