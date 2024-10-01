#ifndef LANG_HH
#define LANG_HH

#pragma once

#include <variant>
#include <vector>
#include <map>
#include <unordered_map>
#include <memory>
#include <string>
#include <iostream>

#ifdef __BOOST__
  #define variant_user boost::variant
  #define variant_get boost::get
  #define variant_visit boost::apply_visitor
#else
  #define variant_user std::variant
  #define variant_get get
  #define variant_visit visit
#endif


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

enum class OperandStatusCode {
  ok,
  error,
  divide_by_zero,
  overflow,
};

enum class OperandErrorCode {
  ok,
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
  s_int_t,
  s_float_t,
  str_t,
  atom_t,
  tuple_t,
  scalar_t,
  list_t,
  map_t,
  ast_op_t,
  except_t,
};

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


using s_integer = long;
using s_float = double;

#endif