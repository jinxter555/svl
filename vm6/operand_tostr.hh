#pragma once
#include "operand.hh"

struct OperandToStringVisitor {
  Operand operator()(bool b) const;
  Operand operator()(s_integer i) const;
  Operand operator()(s_float f) const ;
  Operand operator()(const std::string& s) const ;
  Operand operator()(OperandType t) const;
  Operand operator()(OperandErrorCode err) const;
  Operand operator()(OperandStatusCode status) const;
  Operand operator()(AstOp t_op) const;
  //Operand operator()(const entity_u_ptr&) const;
};
