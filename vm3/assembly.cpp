#include "assembly.hh"

void Assembly::set_data_seg(VM &vm) {
  vm.set_data_seg(&data_seg);
}
void Assembly::run(VM &vm) {
  vm.set_data_seg(&data_seg);
  for(vm.pc=0; vm.pc < pc_load;) {
    vm.dispatch(code[vm.pc++]); // note pc++ is here and not in for
  }
}
void Assembly::run_call(VM &vm, s_int_t start_pc) {
  for(vm.pc=start_pc; vm.pc < pc_load;) {
    vm.dispatch(code[vm.pc++]); // note pc++ is here and not in for
  }
}
void Assembly::run_single_instruction(VM &vm) {
    vm.dispatch(instruction); // note pc++ is here and not in for
}

void Assembly::insert_instruction(us_int_t lno) {
  code[pc_load] = instruction;
  line_no[pc_load] = lno;
  pc_load++;
}