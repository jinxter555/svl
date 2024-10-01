#ifndef LANG_HH
#define LANG_HH

#pragma once
#include <variant>
#include <vector>
#include <map>
#include <unordered_map>
#include <memory>
#include <string>
#include "number.hh"

using namespace  std;


enum class AstOp {
  noop,
  ast_default,
  ast_else,
  plus,
  minus,
  mul,
  div,
  gt,
  lt,
  gteq,
  lteq,
  eql,
  neql,
  and_,
  not_,
  or_,
  assign,
};

enum class OperandErrorCode {
  no_error_t,         // has not encountered any errors
  dvide_zero_t,       // divided by zero
  unassigned_t,       // defined but hasn't been assigned a value
  undefined_t,        // not such variable exist
  invalid_op_t,       // invalid operation has been applied to operand
  mem_alloc_t,        // invalid operation has been applied to operand
};

enum class EntityStatusCode {
  ok,
  entity_already_exist,
  entity_not_found,
  key_not_found,
};


enum class OperandType {
  nil_t,            // assigned unknown value
  type_t,           // recursive type
  err_t,            // error code
  bool_t,
  num_t,
  str_t,
  atom_t,
  tuple_t,
  scalar_t,
  list_t,
  map_t,
  ast_op_t,
  except_t,
};

class Entity; 
using entity_u_ptr = unique_ptr<Entity>;
using entity_s_ptr = shared_ptr<Entity>;
using entity_ptr = Entity *;

class AstExpr; 
using astexpr_u_ptr = unique_ptr<AstExpr>;

class Operand; class Number;
using OperandVariant = variant<bool, AstOp, Number, string, OperandErrorCode, OperandType>;
using operand_ptr = Operand *;


enum class ControlFlow {
  run,
  ast_break, 
  ast_continue,
  ast_return,
  ast_wait,
  sleep,
  stop,
  ast_exit,
  error,
};

#endif