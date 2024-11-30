#pragma once
#include "operand.hh"

struct OperandToStringVisitor {
  Operand operator()(const Nil&) const;
  Operand operator()(bool b) const;
  //Operand operator()(s_integer i) const;
  //Operand operator()(s_float f) const ;
  Operand operator()(const Number& n) const ;
  Operand operator()(const std::string& s) const ;
  Operand operator()(OperandType t) const;
  Operand operator()(OperandErrorCode err) const;
  Operand operator()(OperandStatusCode status) const;
  Operand operator()(ControlFlow cf) const;
  Operand operator()(AstOpCode t_op) const;
  Operand operator()(const astexpr_u_ptr&) const;
  Operand operator()(const operand_u_ptr&) const;
  Operand operator()(svlm_ast_ptr) const;
/*
  Operand operator()(const list_u_ptr&) const;
  Operand operator()(const map_u_ptr&) const;
  Operand operator()(const e_members_t&) const;
  Operand operator()(const e_children_t&) const;
*/
};
