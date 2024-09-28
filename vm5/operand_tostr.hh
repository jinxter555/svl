#pragma
#include "operand.hh"

struct OperandToStringVisitor {
  Operand operator()(bool b) const;
  Operand operator()(s_integer i) const;
  Operand operator()(s_float f) const ;
  Operand operator()(const std::string& s) const ;
  Operand operator()(const Number &n) const;
  Operand operator()(OperandType t) const;
  Operand operator()(OperandErrorCode err) const;
  Operand operator()(AstOp t_op) const;
};
