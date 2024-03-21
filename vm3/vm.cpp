#include "vm.hh"
#include <stdio.h>

VM::VM() {
  //R[Reg::fp].i = 0;
  R[Reg::flag].i = 0;
  data_seg = nullptr;
}

const Frame& VM::get_calling_frame() {
  return vmframes.top();
}
const Frame VM::get_current_frame() {
  s_int_t func=0;
  return Frame(pc, R[Reg::fp].i, vmstack.size(), func);

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
void VM::load_l() { 
  us_int_t loc = R[instruction->operands[1].i].i + instruction->operands[2].i;
  if(loc > vmstack.size()-1) { std::cerr << "can't load from above the stack!\n"; return; }
  R[instruction->operands[0].i] = vmstack[loc];
}

void VM::store_l() { // store, from srcR, target addrR, target offset
  us_int_t loc = R[instruction->operands[1].i].i + instruction->operands[2].i;
  if(loc > vmstack.size()-1) { std::cerr << "can't store above the stack!\n"; return; }
  vmstack[loc] = R[instruction->operands[0].i];
}

// load R_target, R_datasegment, addr_loc
void VM::load_g() { 
  us_int_t loc;
  if(data_seg == nullptr || data_seg->empty()) { std::cerr << "data segment have been not initalized!\n"; return; }

  if(instruction->operands[1].i == -1)  // hack if operand1 == -1, just operand2 addr realtive to datasegment
    loc = instruction->operands[2].i;
  else
    loc = R[instruction->operands[1].i].i + instruction->operands[2].i;

  if(loc > data_seg->size()-1) { std::cerr << "can't load from above the data segment!\n"; return; }
  R[instruction->operands[0].i] = (*data_seg)[loc];
}

// store R_from, R_datasegment, addr_loc_target
void VM::store_g() {
  us_int_t loc;
  if(data_seg == nullptr || data_seg->empty()) { std::cerr << "data segment have been not initalized!\n"; return; }

  if(instruction->operands[1].i == -1)  // hack if operand1 == -1, just operand2 addr realtive to datasegment
    loc = instruction->operands[2].i;
  else
    loc = R[instruction->operands[1].i].i + instruction->operands[2].i;

  if(loc > data_seg->size()-1) { std::cerr << "can't store above the data segment!\n"; return; }
  (*data_seg)[loc] = R[instruction->operands[0].i];
}

void VM::call() {
  us_int_t sp = vmstack.size();
  vmframes.push(Frame(pc, R[Reg::fp].i, sp, 
    instruction->operands[0].adr));
  R[Reg::fp].i = sp;
  pc = instruction->operands[0].adr;
}

void VM::call_r() {
  us_int_t sp = vmstack.size();
  vmframes.push(Frame(pc, R[Reg::fp].i, sp, 
    R[instruction->operands[0].i].adr));
  R[Reg::fp].i = sp;
  pc = R[instruction->operands[0].i].adr;
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
// n plus
void VM::ret_np() {  
  us_int_t sp;
  //std::cout << "ret_np ..\n";
  if(vmframes.empty()) return; // might disable this with compiler defines for speed
  Frame sf = vmframes.top();
  vmframes.pop();
  R[Reg::fp].i = sf.fp;
  pc = sf.pc;
  sp = sf.sp;
  //std::cout << "sp:" << sp << "+" << " np:" <<  instruction->operands[0].i << "\n";
  vmstack.resize(sp + instruction->operands[0].i);
  //std::cout << "ret sp: " << sp << "\n";
  sp = vmstack.size();
}

// clear up calling stack including arguments
// n minus
void VM::ret_nm() {
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

// if operand0 Reg== -1, use operand1 as addr 
// else branch operand1 addr
void VM::beq() {
  if(R[Reg::flag].flag.Z) {
    pc = instruction->operands[0].adr; 
  }
}
void VM::bgt() {
  if(R[Reg::flag].flag.C) {
    pc = instruction->operands[0].adr; 
  }
}
void VM::blt() {
  if(R[Reg::flag].flag.N) {
    pc = instruction->operands[0].adr; 
  }
}
void VM::ble() {
  if(R[Reg::flag].flag.N || R[Reg::flag].flag.Z) {
    pc = instruction->operands[0].adr; 
  }
}
void VM::bge() {
  if(R[Reg::flag].flag.C || R[Reg::flag].flag.Z) {
    pc = instruction->operands[0].adr; 
  }
}

void VM::cmpi() { // comparing registers integer
  reg_t difference; 
  difference.i 
    = R[instruction->operands[0].i].i 
    - R[instruction->operands[1].i].i;
  R[Reg::flag].flag.N = difference.i < 0;
  R[Reg::flag].flag.C = difference.i > 0;
  R[Reg::flag].flag.Z = difference.i == 0;
}

void VM::cmpf() { // comparing registers floating point
  reg_t difference; 
  difference.f 
    = R[instruction->operands[0].i].f 
    - R[instruction->operands[1].i].f;
  R[Reg::flag].flag.N = difference.f < 0;
  R[Reg::flag].flag.C = difference.f > 0;
  R[Reg::flag].flag.Z = difference.f == 0;
}


void VM::iprint() {
  std::cout << R[instruction->operands[0].i].i << "\n";
}
void VM::fprint() {
  std::cout << R[instruction->operands[0].i].f << "\n";
}
void VM::cprint() {
  int i, c=instruction->operands[1].i;
  if(c <= 0) c = sizeof(reg_t); 
  for(i=0; i<c; i++) 
    printf("%c", R[instruction->operands[0].i].c[i]);
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
void VM::stack_resize() {
  us_int_t sp=vmstack.size();
  vmstack.resize(sp + instruction->operands[0].i);
}
void VM::data_resize() {
  // std::cout << "data segment resize: " << instruction->operands[0].i << "\n";
  us_int_t dp=data_seg->size();
  data_seg->resize(dp + instruction->operands[0].i);
}
void VM::data_size() {
  R[instruction->operands[0].i].i = data_seg->size();
}

void VM::set_d_av() {
  if(data_seg == nullptr || data_seg->empty()) { std::cerr << "data segment have been not initalized!\n"; return; }

  us_int_t loc = instruction->operands[0].i;

  if(loc > data_seg->size()-1) { std::cerr << "can't store above the data segment!\n"; return; }
  (*data_seg)[loc] = instruction->operands[1];
}

void VM::set_s_av() {
}

// data_add Reg, 0, 0   # add value of reg
// data_add -1, int    # add number int instead
// data_add -1, float   # add number float instead
void VM::data_add() {
  if( instruction->operands[0].i==-1) 
    data_seg->push_back(instruction->operands[1]);
  else
    data_seg->push_back(R[instruction->operands[0].i]);
}


void VM::set_data_seg(std::vector<reg_t> *sds) {
  if(data_seg == nullptr)
    data_seg  = sds;
}
void VM::dispatch(instr_t &itt) {
  instruction = &itt;
  dispatch();
}
void VM::dispatch() {
  switch(instruction->opcode) {
    case Opcode::INVALID: std::cerr << "Invalid instruction !!!!\n"; break;
    case Opcode::MOV: mov(); break;
    case Opcode::IADD_C: iadd_c(); break;
    case Opcode::IADD_R: iadd_r(); break;
    case Opcode::ISUB_C: isub_c(); break;
    case Opcode::ISUB_R: isub_r(); break;
    case Opcode::POP_R:  pop_r();   break;
    case Opcode::PUSH_C: push_c();  break;
    case Opcode::PUSH_R: push_r();  break;
    case Opcode::STORE_L: store_l();  break;
    case Opcode::LOAD_L:  load_l();  break;
    case Opcode::STORE_G: store_g();  break;
    case Opcode::LOAD_G:  load_g();  break;
    case Opcode::DATA_ADD:   data_add();  break;
    case Opcode::IPRINT:  iprint();  break;
    case Opcode::FPRINT:  fprint();  break;
    case Opcode::CPRINT:  cprint();  break;
    case Opcode::CALL:   call();  break;
    case Opcode::CALL_R:   call_r();  break;
    case Opcode::RET:    ret();  break;
    case Opcode::RET_NM:  ret_nm();  break;
    case Opcode::RET_NP:  ret_np();  break;

    case Opcode::BEQ:   beq(); break; 
    case Opcode::BGT:   bgt(); break; 
    case Opcode::BLT:   blt(); break;
    case Opcode::BLE:   ble(); break;
    case Opcode::BGE:   bge(); break;
  
    case Opcode::CMPI:  cmpi(); break;
    case Opcode::CMPF:  cmpf(); break;


    case Opcode::STACK_RESIZE:   stack_resize();  break;
    case Opcode::DATA_RESIZE:   data_resize();  break;
    case Opcode::DATA_SIZE:   data_size();  break;
    case Opcode::SET_D_AV:   set_d_av();  break;
    case Opcode::EXIT:   vmexit();  break;
    case Opcode::NOOP:   break;
    default: std::cerr << "you've forgot to add case instruction: " <<  static_cast<int>(instruction->opcode) << "!!!!\n"; break;
  }
}

