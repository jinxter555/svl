#pragma once
#include "vm_type.hh"
#include <variant>

enum class key_tok_t {
  app=10, api, smodule, mvar, mvar_total_count,
  mfunction, fbody, lvar, larg, label
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

enum class BinOpcodeAST {
  INT_OP_INT,
  FLT_OP_FLT,
  INT_OP_FLT,
  FLT_OP_INT,
  ASSIGN_INT_L,
  ASSIGN_INT_G,
  ASSIGN_FLT_L,
  ASSIGN_FLT_G,
};

typedef struct {
  BinOpcodeAST op_type;
  char op;
} op_t;

enum class DeclOpcodeAST {
  MODULE,
  DEF,
  VAR
};

enum class VarTypeEnum {
  INT,
  FLT,
  STR,
  PTR=10, // pointer maybe
  USER_DEF=100
};

typedef struct {
  VarTypeEnum t;
  std::variant<int, float, std::string> v;
} vartype_t;

typedef std::variant<int, float>  num_d_t;

typedef struct {
  unsigned char pos; // argument postition from 0 - 255
  std::string name;
} arg_name_pos_t;

