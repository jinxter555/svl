#include "vm_type.hh"
class FrameSvlm {
  //std::shared_ptr<ExprAst> program_pointer; // point to the current ast tree
  s_int_t sp=0;  // current stack pointer
  s_int_t fp=0;  // frame pointer to in stack
};