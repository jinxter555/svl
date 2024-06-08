#pragma once
#include "vm_type.hh"
#include <variant>

#define TM std::map<std::string, std::shared_ptr<TreeNode>>
#define TMA std::map<std::string, std::any>

enum class key_tok_t {
  app=10, api, smodule, mvar, mvar_total_count,
  mfunction, fbody, lvar, larg, label
};

enum class ast_op {
  noop,
  ast_default,
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

typedef struct {
  std::string uni, app, api, smodule, mvar, mfunction, fbody, lvar, larg, label;
  key_tok_t type;     // app, api, smodule... do i know who i am?
} full_symbol_t;

typedef struct {
  s_int_t location;  // address location of code[] where symbol is referenced
  key_tok_t type;     // type for svl lang, module, function, var,
  full_symbol_t name; // std::string sapp, sapi, smodule, sfunction, svar;
  int operand_loc;
} unresolved_symbol_t;

enum class DeclOpcodeAST {
  MODULE,
  DEF,
  VAR
};

class Number; class Atom; class Tuple;
using OperandVariant = std::variant
  <bool, Number, Atom, Tuple, std::string>;

enum class VarTypeEnum {
  bool_t,
  num_t,
  str_t,
  atom_t,
  tuple_t,
  ptr_t, // pointer maybe
  user_t,
};


typedef std::variant<int, float>  num_d_t;

typedef struct {
  unsigned char pos; // argument postition from 0 - 255
  std::string name;
} arg_name_pos_t;

