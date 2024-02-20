#include "vm.hh"


void VM::iadd_c() {
  R[instruction->operands[0].i].i 
    = R[instruction->operands[1].i].i
    + instruction->operands[2].i;
}

void VM::iadd_r() {
  R[instruction->operands[0].i].i 
    = R[instruction->operands[1].i].i
    + R[instruction->operands[2].i].i;
}
void VM::call() {
  vmframes.push(Frame(pc, fp));
  fp = vmstack.size();
  pc = instruction->operands[0].adr;

}
void VM::ret() {
  Frame sf = vmframes.top();
  vmframes.pop();
  fp = sf.fp;
  pc = sf.pc;
}
void VM::vmexit() {
  pc = 999999;
}


void VM::push_c() {
  vmstack.push_back(
    instruction->operands[0]
  );
}
void VM::push_r() {
  vmstack.push_back(
    R[instruction->operands[0].i]
  );
}
void VM::pop_r() {
  if(vmstack.empty()) { // might want to comment this out for speed optimization
    std::cerr << "stack emtpy poped out\n";
    return;
  }
  // R[instruction->operands[0].i] = vmstack.top();
  R[instruction->operands[0].i] = vmstack.back();
  // cout << "poped out " << R[instruction->operands[0].i].i << "\n";
  vmstack.pop_back();
  // cout << "in popr\n";  print_registers();
}

void VM::dispatch(instr_t &itt) {
  instruction = &itt;
  dispatch();
}
void VM::dispatch() {
  switch(instruction->opcode) {
    case Opcode::IADD_C: iadd_c(); break;
    default: break;

  }
}





