#include "assembly.hh"


void Assembly::dispatch() {
  //cout << "in assembly::dispatch\n";
  // vm.dispatch(instruction);
}

shared_ptr<TreeNode> Assembly::resolve_symbol_node(const vector<string>& keys) const {
  auto curr = context->get_node(keys);
  return curr; 
}