#include "vm.hh"
#include "vm_num.hh"
#include "assembly.hh"

VM::VM() {
  assembly = nullptr;
  for(int i=0; i<MAXREG; ++i) {
    R[i].i = 0;
  }
}
void VM::set_assembly(Assembly *a) {
  assembly = a;
}

void VM::pushc() {
  //cout << "in pushc\n"; print_instruction();
  //cout << "\n"; //print_stack_int(); cout << "\n";
  vmstack.push_back(
    instruction->operands[0]
  );
  //print_stack_int(); cout << "\n";
}
void VM::pushr() {
  vmstack.push_back(
    R[instruction->operands[0].i]
  );
}

void VM::popr() {
  if(vmstack.empty()) { // might want to comment this out for speed optimization
    cerr << "stack emtpy poped out\n";
    return;
  }
  // R[instruction->operands[0].i] = vmstack.top();
  R[instruction->operands[0].i] = vmstack.back();
  // cout << "poped out " << R[instruction->operands[0].i].i << "\n";
  vmstack.pop_back();
  // cout << "in popr\n";  print_registers();
}

void VM::mov() {
  R[instruction->operands[0].i].i
    = instruction->operands[1].i;
}

void VM::load() { // load targetR, addrR, offset
  us_int_t loc = R[instruction->operands[1].i].i + instruction->operands[2].i;
  if(loc > vmstack.size()-1) { cerr << "can't load from above the stack!\n"; return; }
  R[instruction->operands[0].i] = vmstack[loc];
 
  //cout  << "load vmstack.size:" <<  vmstack.size() << "\n";
  //print_instruction();
  //cout << "load from addr: vmstack[" << loc <<  "]:" << vmstack[loc].i << "\n";  
}
void VM::store() { // store srcR, target addrR, offset
  us_int_t loc = R[instruction->operands[1].i].i + instruction->operands[2].i;
  if(loc > vmstack.size()-1) { cerr << "can't store above the stack!\n"; return; }
  vmstack[loc] = R[instruction->operands[0].i];
}

void VM::addi() {
  // print_instruction();
  R[instruction->operands[0].i].i 
    = R[instruction->operands[1].i].i
    + R[instruction->operands[2].i].i;
}
void VM::subi() {
  R[instruction->operands[0].i].i 
    = R[instruction->operands[1].i].i
    - R[instruction->operands[2].i].i;
}
void VM::muli() {
  R[instruction->operands[0].i].i 
    = R[instruction->operands[1].i].i
    * R[instruction->operands[2].i].i;
}
void VM::divi() {
  R[instruction->operands[0].i].i 
    = R[instruction->operands[1].i].i
    / R[instruction->operands[2].i].i;
}

void VM::call() {
  vmframes.push(Frame(pc, fp));
  fp = vmstack.size();
  pc = instruction->operands[0].adr;
  cout << "setting pc to: " << pc << "\n";
  //pc = instruction->operands[0].adr - 1;
}
void VM::ret() {
  Frame sf = vmframes.top();
  vmframes.pop();
  fp = sf.fp;
  pc = sf.pc;
  cout << "ret: pc= " << pc << "\n";
}

void VM::vmexit() {
  pc = 99999;
}
void VM::cmpi() { // comparing registers integer
  reg_t difference; 
  difference.i 
    = R[instruction->operands[0].i].i 
    - R[instruction->operands[1].i].i;
  flag.N = difference.i < 0;
  flag.C = difference.i > 0;
  flag.Z = difference.i == 0;
}

void VM::cmpf() { // comparing registers floating point
  reg_t difference; 
  difference.f 
    = R[instruction->operands[0].i].f 
    - R[instruction->operands[1].i].f;
  flag.N = difference.f < 0;
  flag.C = difference.f > 0;
  flag.Z = difference.f == 0;
}

void VM::beq() {
  if(flag.Z) {
  }
}
void VM::bgt() {
  if(flag.C) {
  }
}
void VM::blt() {
  if(flag.N) {
  }
}
void VM::ble() {
  if(flag.N || flag.Z) {
  }
}
void VM::bge() {
  if(flag.C || flag.Z) {
  }
}

void VM::dispatch() {
  //cout << "vm inline dispatch\n"; 
  switch(instruction->opcode)  {
    case VM_mov:    mov();    break;
    case VM_load:   load();    break;
    case VM_store:  store();    break;
    case VM_addi:   addi();   break;
    case VM_subi:   subi();   break;
    case VM_muli:   muli();   break;
    case VM_divi:   divi();   break;
    case VM_popr:   popr();   break;
    case VM_pushc:  pushc();  break;
    case VM_pushr:  pushr();  break;
    case VM_call:   call();  break;
    case VM_ret:    ret();  break;
    case VM_vmexit: vmexit();  break;
  }
}
void VM::dispatch(instr_t &itt) {
  //cout << "vm dispatch\n"; 
  instruction = &itt;
  dispatch();
}

void VM::print_instruction() {
  cout << "opcode: " << int(instruction->opcode) << "\n";
  cout << "operands0: " << int(instruction->operands[0].i) << "\n";
  cout << "operands1: " << int(instruction->operands[1].i) << "\n";
  cout << "operands2: " << int(instruction->operands[2].i) << "\n";
  cout << "\n";
}

/*
void VM::print_stack_int() {
  int i=0; reg_t  n ;
  std::stack<reg_t> temp_stack = stack;
  cout << "print_stack_int\n";
  while(!temp_stack.empty()) {
    reg_t n = temp_stack.top();
    std::cout << i++ << ": " << n.i << "\n";
    temp_stack.pop();
    // if(i>20) break;
  }
  cout << "\n";
}

void VM::print_registers(byte_code_t n) {
  for(byte_code_t i=0; i<n; i++) {
    cout << "R" << int(i) << ":" << R[i].i << " ";
  }
  cout << "\n";
}
*/
