// assembly opcode string to byte code
#include "assembly.hh"
#include "vm_num.hh"


map<string, byte_code_t> Assembly::asm_str_lookup = {
  {"mov",   VM_mov},
  {"load",   VM_load},
  {"store",   VM_store},
  {"addi",  VM_addi},
  {"subi",  VM_subi},
  {"muli",  VM_muli},
  {"divi",  VM_divi},
  {"pushc", VM_pushc},
  {"pushr", VM_pushr},
  {"popr",  VM_popr},
  {"call",  VM_call},
  {"ret",  VM_ret},
  {"vmexit",  VM_vmexit},
};
