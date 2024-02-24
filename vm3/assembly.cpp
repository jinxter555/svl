#include "assembly.hh"

void Assembly::run(VM &vm) {
  for(vm.pc=0; vm.pc < pc_load;) {
    //print_instruction(vm.pc);
    vm.dispatch(code[vm.pc++]); // note pc++ is here and not in for
  }
}
void Assembly::run_single_instruction(VM &vm) {
    vm.dispatch(instruction); // note pc++ is here and not in for
}

void Assembly::insert_instruction() {
  code[pc_load++] = instruction;
}