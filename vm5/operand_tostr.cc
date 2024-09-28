#include "operand_tostr.hh"

Operand OperandToStringVisitor::operator()(bool b) const {
 if(b==true) return string("true");
 return string("false");
}

Operand OperandToStringVisitor::operator()(s_integer i) const {
 return to_string(i);
}
Operand OperandToStringVisitor::operator()(s_float f) const {
  return to_string(f);
}
Operand OperandToStringVisitor::operator()(const Number &n) const {
  return n.to_str();
}
Operand OperandToStringVisitor::operator()(const std::string& s) const {
  return s;
}
Operand OperandToStringVisitor::operator()(OperandType t) const {
  string outstr;
  switch(t) {
  case OperandType::nil_t:  outstr ="nil_t"; break;
  case OperandType::type_t:  outstr ="type"; break;
  case OperandType::err_t:  outstr ="err_t"; break;
  case OperandType::bool_t: outstr ="bool"; break;
  case OperandType::num_t:  outstr ="num_t"; break;
  case OperandType::str_t:  outstr ="str_t"; break;
  case OperandType::atom_t: outstr ="atom_t"; break;
  case OperandType::list_t: outstr ="list_t"; break;
  case OperandType::map_t:  outstr ="map_t"; break;
  case OperandType::ast_op_t:  outstr ="ast_opt_t"; break;
  case OperandType::except_t:  outstr ="except_t"; break;
  //case OperandType::any_t:  outstr ="any_t"; break;
  default: outstr ="type unknown"; break;
  }
  return outstr;
}

Operand OperandToStringVisitor::operator()(OperandErrorCode err) const {
  string outstr;
  
  switch(err) {
  case OperandErrorCode::invalid_op_t:
    outstr = "invalid operand operation";
    break;
  case OperandErrorCode::unassigned_t:
    outstr = "operand has not been assigned value";
    break;
  case OperandErrorCode::undefined_t:
    outstr = "no such operand. it's undefined";
    break;
  default:
    outstr = "unknown error!";
    break;
  }
  return outstr;
}

Operand OperandToStringVisitor::operator()(AstOp t_op) const {
  std::string oc;


  switch(t_op) {
  case AstOp::noop:  oc="-noop-"; break;
  case AstOp::ast_default:  oc="default"; break;
  case AstOp::ast_else:  oc="else"; break;
  case AstOp::assign:  oc="="; break;
  case AstOp::plus:  oc="+"; break;
  case AstOp::minus: oc="-"; break;
  case AstOp::mul:   oc="*"; break;
  case AstOp::div:   oc="/"; break;
  case AstOp::eql:   oc="=="; break;
  case AstOp::neql:  oc="!="; break;
  case AstOp::gt:    oc=">"; break;
  case AstOp::lt:    oc="<"; break;
  case AstOp::lteq:  oc="<="; break;
  case AstOp::gteq:  oc=">="; break;
  case AstOp::and_:  oc="&&"; break;
  case AstOp::or_:   oc="||"; break;
  case AstOp::not_:  oc="!"; break;
  default: oc="not ast operator"; break;
  } 
  return Operand(oc);
}