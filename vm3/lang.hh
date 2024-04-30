#pragma once
enum class key_tok_t {
  app=10, api, smodule, mvar, mvar_total_count,
  mfunction, lvar, larg, label
};

typedef struct {
  std::string uni, app, api, smodule, mvar, mfunction, lvar, larg, label;
  key_tok_t type;     // app, api, smodule... do i know who i am?
} full_symbol_t;

typedef struct {
  s_int_t location;  // address location of code[] where symbol is referenced
  key_tok_t type;     // type for svl lang, module, function, var,
  full_symbol_t name; // std::string sapp, sapi, smodule, sfunction, svar;
  int operand_loc;
} unresolved_symbol_t;