#pragma once
#include "vm_type.hh"
#include <variant>
#include <memory>
#include <any>
#include <map>

#define TMN std::map<std::string, std::shared_ptr<TreeNode>>
#define TMA std::map<std::string, std::any>

#define LIST_PTR std::shared_ptr<std::vector<Operand>>
#define LIST_T std::vector<Operand>

enum class key_tok_t {
  app=10, api, smodule, mvar, mvar_total_count,
  mfunction, fbody, lvar, larg, label
};

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

class Number; class Atom; 
class Operand;
using OperandVariant = std::variant
  //<bool, Number, Atom, std::string, std::vector<Operand>>;
  <bool, Number, Atom, std::string, LIST_T>;

enum class VarTypeEnum {
  nil_t,
  undefined_t,
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


class FrameSvlm {
public:
  //std::shared_ptr<ExprAst> program_pointer; // point to the current ast tree
  //s_int_t sp=0;  // current stack pointer
  //s_int_t fp=0;  // frame pointer to in stack
  std::shared_ptr<TMA> lvars;
  std::any ret_val;
};


typedef std::variant<int, float>  num_d_t;
