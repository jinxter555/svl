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


using namespace  std;


enum class AstOpCode {
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
  status_t,
  s_int_t,
  s_float_t,
  str_t,
  atom_t,
  tuple_t,
  scalar_t,     // operand  entity
  list_t,
  map_t,
  ast_op_t,
  ptr_t,
  uptr_t,
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

//--------------------------------------------------------- 
class Nil{};
extern Nil nil;

class Operand; class Number;
using operand_u_ptr=unique_ptr<Operand>;
//--------------------------------------------------------- 
class Entity; class ListEntity;  class MapEntity;
class AstNode; class AstExpr;
//--------------------------------------------------------- 
using entity_u_ptr = unique_ptr<Entity>;
using e_members_t = vector<Operand>;
using e_children_t = unordered_map<string, Operand>;
using list_u_ptr = unique_ptr<ListEntity>;
using map_u_ptr = unique_ptr<MapEntity>;
using astexpr_u_ptr = unique_ptr<AstExpr>;
//--------------------------------------------------------- 
using OperandVariant=std::variant
< Nil
, bool, string, Number
, AstOpCode, OperandErrorCode
, OperandStatusCode, OperandType
, entity_u_ptr
>;
//--------------------------------------------------------- 
template <typename T>
class Primordial {
protected:
  OperandType type_;
public:
 // Primordial(OperandType);
  Primordial(OperandType t) : type_(t) {};
  virtual unique_ptr<T> clone() const=0;
  virtual Operand to_str() const =0;
  virtual Operand get_type() const=0;
  virtual void print() const =0;
};

#endif