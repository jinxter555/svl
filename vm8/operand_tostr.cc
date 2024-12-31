#include "operand.hh"
//#include "svlm_ast.hh"

#define DEBUG_TRACE_FUNC
#include "scope_logger.hh"

Operand Operand::ToString::operator()(const Nil n) const {
  return string("nil");
}
Operand Operand::ToString::operator()(bool b) const {
 if(b==true) return string("true");
 return string("false");
}

Operand Operand::ToString::operator()(const Number &n) const {
  return n.to_str();
}
Operand Operand::ToString::operator()(const string& s) const {
  return s;
}

Operand Operand::ToString::operator()(OperandType t) const {
  string outstr;
  switch(t) {
  case OperandType::nil_t:  outstr ="nil_t"; break;
  case OperandType::type_t:  outstr ="type_t"; break;
  case OperandType::err_t:  outstr ="err_t"; break;
  case OperandType::bool_t: outstr ="bool"; break;
  case OperandType::num_t:  outstr ="num_t"; break;
  case OperandType::str_t:  outstr ="str_t"; break;
  case OperandType::atom_t: outstr ="atom_t"; break;
  case OperandType::tuple_t: outstr ="tuple_t"; break;
  case OperandType::scalar_t: outstr ="scalar_t"; break;
  case OperandType::array_t: outstr ="array_t"; break;
  case OperandType::list_t: outstr ="list_t"; break;
  case OperandType::map_t:  outstr ="map_t"; break;
  case OperandType::ptr_t:  outstr ="ptr_t"; break;
  case OperandType::uptr_t:  outstr ="uptr_t"; break;
  case OperandType::sptr_t:  outstr ="sptr_t"; break;
  case OperandType::ast_op_t:  outstr ="ast_op_t"; break;
  case OperandType::ast_mod_t:  outstr ="ast_mod_t"; break;
  case OperandType::ast_binop_t:  outstr ="ast_binop_t"; break;
  case OperandType::ast_func_t:  outstr ="ast_func_t"; break;
  case OperandType::ast_class_t:  outstr ="ast_class_t"; break;
  case OperandType::ast_mvar_t:  outstr ="ast_mvar_t"; break;
  case OperandType::ast_lvar_t:  outstr ="ast_lvar_t"; break;
  case OperandType::ast_ovar_t:  outstr ="ast_ovar_t"; break;
  case OperandType::ast_print_t:  outstr ="ast_print_t"; break;
  case OperandType::ast_caller_t:  outstr ="ast_caller_t"; break;
  case OperandType::svlm_ast_ptr_t:  outstr ="svlm_ast_ptr_t"; break;
  case OperandType::except_t:  outstr ="except_t"; break;
  //case OperandType::any_t:  outstr ="any_t"; break;
  default: outstr ="i have forgotten to add. type unknown"; break;
  }
  return outstr;
}

Operand Operand::ToString::operator()(OperandStatusCode s) const { 
  string outstr;
  switch(s) {
  case OperandStatusCode::ok: 
    outstr = "ok"; break;
  case OperandStatusCode::error: 
    outstr = "error"; break;
  case OperandStatusCode::divide_by_zero: 
    outstr = "divided by zero"; break;
  case OperandStatusCode::overflow: 
    outstr = "overflow"; break;
  default: outstr = "default"; break;
  }
  return outstr;
}
Operand Operand::ToString::operator()(ControlFlow cf) const { 
  string outstr;
  switch(cf) {
  case ControlFlow::run: 
    outstr = "run"; break;
  case ControlFlow::ast_break:
    outstr = "break"; break;
  case ControlFlow:: ast_continue:
    outstr = "continue"; break;
  case  ControlFlow::ast_return:
    outstr = "return"; break;
  default:
    outstr = "ast run state unknown"; break;
  }
  return outstr;
}

Operand Operand::ToString::operator()(OperandErrorCode err) const {
  MYLOGGER(trace_function , "OperandToStringVisitor::operator(OperandErrorCode )" , __func__);

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
  MYLOGGER_MSG(trace_function, outstr);
  return outstr;
}

Operand Operand::ToString::operator()(AstOpCode t_op) const {
  std::string oc;


  switch(t_op) {
  case AstOpCode::noop:  oc="-noop-"; break;
  case AstOpCode::ast_default:  oc="default"; break;
  case AstOpCode::ast_else:  oc="else"; break;
  case AstOpCode::assign:  oc="="; break;
  case AstOpCode::assign_clone:  oc=":="; break;
  case AstOpCode::plus:  oc="+"; break;
  case AstOpCode::minus: oc="-"; break;
  case AstOpCode::mul:   oc="*"; break;
  case AstOpCode::div:   oc="/"; break;
  case AstOpCode::eql:   oc="=="; break;
  case AstOpCode::neql:  oc="!="; break;
  case AstOpCode::gt:    oc=">"; break;
  case AstOpCode::lt:    oc="<"; break;
  case AstOpCode::lteq:  oc="<="; break;
  case AstOpCode::gteq:  oc=">="; break;
  case AstOpCode::and_:  oc="&&"; break;
  case AstOpCode::or_:   oc="||"; break;
  case AstOpCode::not_:  oc="!"; break;
  default: oc="not ast operator"; break;
  } 
  return Operand(oc);
}

Operand Operand::ToString::operator()(const operand_s_ptr &vptr) const { 
  return vptr->to_str();
}
Operand Operand::ToString::operator()(const operand_u_ptr &vptr) const { 
  return vptr->to_str();
}
Operand Operand::ToString::operator()(const operand_ptr &vptr) const { 
  //return Operand("operand ptr: ") + vptr->to_str();
  return vptr->to_str();
}

Operand Operand::ToString::operator()(const list_t &l) const { 
  int i, s = l.size();
  string outstr("[");
  if(s==0) {return Operand("[]");}

  for(i=0; i<s-1; i++) {
    outstr = outstr + l[i]._to_str() + ",";
  }
  outstr = outstr + l[i]._to_str() + "]";

  return outstr;
}

Operand Operand::ToString::operator()(const map_t &map_) const { 
  if(map_.empty()) return "{}";

  vector<string> kv_paires ;
  string colon(":");
  string q("\"");
  string outstr;

  for (auto const& [key, val] : map_) {
    outstr = q + key + q  + colon + " " + val.to_str()._to_str();
    kv_paires.push_back(outstr);
  }

  outstr="{";
  int i, s = kv_paires.size();
  for(i=0; i<s-1; i++) {
    outstr = outstr + kv_paires[i] + ", ";
  }
  outstr = outstr + kv_paires[i] + "}";
  return (outstr);
}



//Operand Operand::ToString::operator()(const svlm_ast_ptr& v) const { return v->to_str(); }
/*
Operand OperandToStringVisitor::operator()(const list_u_ptr &vptr) const { 
  return Operand("list entity ptr: ") + vptr->_to_str(); 
}
Operand OperandToStringVisitor::operator()(const e_members_t &vptr) const { 
  return Operand("list members: ");
}
Operand OperandToStringVisitor::operator()(const e_children_t &vptr) const { 
  return Operand("children: ");
}
*/
//Operand OperandToStringVisitor::operator()(s_integer i) const { return to_string(i); }
//Operand OperandToStringVisitor::operator()(s_float f) const { return to_string(f); }