#include "assembly.hh"
/*
shared_ptr<TreeNode> Assembly::resolve_symbol_node(const vector<std::string>& keys) const {
  auto curr = context->get_node(keys);
  return curr; 
}
*/
void Assembly::run(VM &vm) {
  for(vm.pc=0; vm.pc < pc_load;) {
    //print_instruction(vm.pc);
    vm.dispatch(code[vm.pc++]); // note pc++ is here and not in for
  }
}