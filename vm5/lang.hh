#ifndef LANG_HH
#define LANG_HH

#pragma once
#include <variant>
#include <vector>
#include <map>
#include <memory>
#include <any>
#include <string>
#include "number.hh"

using namespace  std;


enum class ast_op {
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


class Operand; class Number;
using OperandVariant = variant<bool, ast_op, Number, string>;

enum class OperandType {
  nil_t,            // assigned unknown value
  unassigned_t,     // defined but hasn't been assigned a value
  undefined_t,      // not such variable exist
  invalid_op_t,     // invalid operation has been applied to operand
  bool_t,
  num_t,
  str_t,
  atom_t,
  tuple_t,
  scalar_t,
  list_t,
  map_t,
  ptr_t, // pointer maybe
  user_t,
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



#endif