#include "que_node.hh"
class SvlmAst : Tree {
protected:
  //Operand control_flow = ControlFlow::run;
public:
  SvlmAst(const OperandType&t) : Tree(t) {};

  void add_module();
  void add_class();
  void add_function();
  void add_mvar();
  void add_ovar();
  void add_lvar();

  unique_ptr<Tree> clone() const override {return nullptr;};
  Operand to_str() const override { return "";};
  Operand get_type() const override { return OperandType::nil_t;};
  void print() const override {};
};