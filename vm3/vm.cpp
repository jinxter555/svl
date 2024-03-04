#include "vm.hh"

VM::VM() {
  R[Reg::fp].i = 0;
}
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

// load targetR, from addrR, from offset
void VM::load() { 
  us_int_t loc = R[instruction->operands[1].i].i + instruction->operands[2].i;
  if(loc > vmstack.size()-1) { std::cerr << "can't load from above the stack!\n"; return; }
  R[instruction->operands[0].i] = vmstack[loc];
}

void VM::store() { // store, from srcR, target addrR, target offset
  us_int_t loc = R[instruction->operands[1].i].i + instruction->operands[2].i;
  if(loc > vmstack.size()-1) { std::cerr << "can't store above the stack!\n"; return; }
  vmstack[loc] = R[instruction->operands[0].i];
}

void VM::call() {
  us_int_t sp = vmstack.size();
  vmframes.push(Frame(pc, R[Reg::fp].i, sp));
  R[Reg::fp].i = sp;
  pc = instruction->operands[0].adr;
}

void VM::ret() {
  us_int_t sp;
  if(vmframes.empty()) return; // might disable this with compiler defines for speed
  Frame sf = vmframes.top();
  vmframes.pop();
  R[Reg::fp].i = sf.fp;
  pc = sf.pc;
  sp = sf.sp;
  //std::cout << "ret sp: " << sp << "\n";
  vmstack.resize(sp);
}

// caller handles stack for returned values
void VM::ret_np() {  
  us_int_t sp;
  std::cout << "ret_np ..\n";
  if(vmframes.empty()) return; // might disable this with compiler defines for speed
  Frame sf = vmframes.top();
  vmframes.pop();
  R[Reg::fp].i = sf.fp;
  pc = sf.pc;
  sp = sf.sp;
  std::cout << "sp:" << sp << "+" << " np:" <<  instruction->operands[0].i << "\n";
  vmstack.resize(sp + instruction->operands[0].i);
  std::cout << "ret sp: " << sp << "\n";
  sp = vmstack.size();
}

// clear up calling stack including arguments
void VM::ret_n() {
  us_int_t sp;
  if(vmframes.empty()) return; // might disable this with compiler defines for speed
  Frame sf = vmframes.top();
  vmframes.pop();
  R[Reg::fp].i = sf.fp;
  pc = sf.pc;
  sp = sf.sp;
  vmstack.resize(sp - instruction->operands[0].i);
  sp = vmstack.size();
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
    case Opcode::STORE: store();  break;
    case Opcode::LOAD:  load();  break;
    case Opcode::CALL:   call();  break;
    case Opcode::RET:    ret();  break;
    case Opcode::RET_N:  ret_n();  break;
    case Opcode::RET_NP:  ret_np();  break;
    case Opcode::EXIT:   vmexit();  break;
    default: break;

  }
}

