#include "vm.hh"

void VM::mov() {
  //R[instruction->operands[0].i].i
  //  = instruction->operands[1].i;
  R[instruction->operands[0].i]
    = instruction->operands[1];
}

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
void VM::isub_c() {
  R[instruction->operands[0].i].i 
    = R[instruction->operands[1].i].i
    - instruction->operands[2].i;
}
void VM::isub_r() {
  R[instruction->operands[0].i].i 
    = R[instruction->operands[1].i].i
    - R[instruction->operands[2].i].i;
}

// load targetR, addrR, offset
void VM::load_l() { 
  us_int_t loc = R[instruction->operands[1].i].i + instruction->operands[2].i;
  if(loc > vmstack.size()-1) { std::cerr << "can't load from above the stack!\n"; return; }
  R[instruction->operands[0].i] = vmstack[loc];
 
  //cout  << "load vmstack.size:" <<  vmstack.size() << "\n";
  //print_instruction();
  //cout << "load from addr: vmstack[" << loc <<  "]:" << vmstack[loc].i << "\n";  
}
void VM::store_l() { // store srcR, target addrR, offset
  us_int_t loc = R[instruction->operands[1].i].i + instruction->operands[2].i;
  if(loc > vmstack.size()-1) { std::cerr << "can't store above the stack!\n"; return; }
  vmstack[loc] = R[instruction->operands[0].i];
}



void VM::call() {
  us_int_t sp = vmstack.size();
  vmframes.push(Frame(pc, fp, sp));
  fp = sp;
  pc = instruction->operands[0].adr;

}
void VM::ret() {
  us_int_t sp;
  Frame sf = vmframes.top();
  vmframes.pop();
  fp = sf.fp;
  pc = sf.pc;
  sp = sf.sp;
  vmstack.resize(sp);
}
void VM::vmexit() {
  pc = exit_max_pc;
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
    case Opcode::MOV: mov(); break;
    case Opcode::IADD_C: iadd_c(); break;
    case Opcode::IADD_R: iadd_r(); break;
    case Opcode::ISUB_C: isub_c(); break;
    case Opcode::ISUB_R: isub_r(); break;
    case Opcode::POP_R:  pop_r();   break;
    case Opcode::PUSH_C: push_c();  break;
    case Opcode::PUSH_R: push_r();  break;
    case Opcode::CALL:   call();  break;
    case Opcode::RET:    ret();  break;
    case Opcode::EXIT:   vmexit();  break;

    default: break;

  }
}

