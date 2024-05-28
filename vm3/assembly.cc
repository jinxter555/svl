#include "assembly.hh"

void Assembly::set_data_seg(VM &vm) {
  vm.set_data_seg(&data_seg);
}
void Assembly::set_breakpoint(us_int_t bpt) {
  breakpoint = bpt;
}
void Assembly::run(VM &vm) {
  if(breakpoint == 0) {
    run_normal(vm);
    return;
  }
  run_break(vm);
}

void Assembly::run_normal(VM &vm) {
  vm.set_data_seg(&data_seg);
  for(vm.pc=0; vm.pc < pc_load;) {
    vm.dispatch(code[vm.pc++]); // note pc++ is here and not in for
  }
}
void Assembly::run_break(VM &vm) {
  vm.set_data_seg(&data_seg);
  for(vm.pc=0; vm.pc < pc_load;) {
    vm.dispatch(code[vm.pc++]); // note pc++ is here and not in for
    if(line_no[vm.pc] >= breakpoint) break;
  }
}
void Assembly::run_step(VM &vm, s_int_t num) {
  vm.set_data_seg(&data_seg);
  if(vm.pc > pc_load || vm.pc == 0 || breakpoint == 0) {
    std::cerr << "maybe you didn't set break point properly or program have already exited!\n";
    return;
  }
  for(s_int_t current_line = line_no[vm.pc]; vm.pc < pc_load ;) {
    vm.dispatch(code[vm.pc++]); // note pc++ is here and not in for
    if(vm.pc > pc_load) break; // program have exited
    if(line_no[vm.pc] >= current_line + num) break;
  }
}

void Assembly::run_call(VM &vm, s_int_t start_pc) {
  vm.set_data_seg(&data_seg);
  for(vm.pc=start_pc; vm.pc < pc_load;) {
    vm.dispatch(code[vm.pc++]); // note pc++ is here and not in for
  }
}
void Assembly::run_single_instruction(VM &vm) {
  vm.set_data_seg(&data_seg);
  vm.dispatch(instruction); // note pc++ is here and not in for
}

void Assembly::insert_instruction(us_int_t lno) {
  code[pc_load] = instruction;
  line_no[pc_load] = lno;
  pc_load++;
}