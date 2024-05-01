#pragma once
#include <memory>
#include <stack>
#include <iostream>
#include "tree.hh"
#include "ast.hh"
#include "universe.hh"
#include "lang.hh"

class SvlmLang {
  friend class SvlmInteractive;
  friend class SvlmLangContext;

public:
  std::shared_ptr<Tree> context_tree;

  SvlmLang(std::shared_ptr<Tree> tp);
  std::stack<std::shared_ptr<ListExprAst>> ast_current_contexts;
  std::shared_ptr<ListExprAst> ast_current_context;
private:

};

class SvlmLangContext  {
public:
  SvlmLang *svlm_lang;
  full_symbol_t current_context;

  SvlmLangContext(SvlmLang *s);
  void init(SvlmLang *s) { svlm_lang=s; } 
  void add_app_name(const std::string &app);
  void add_module_name(const std::string &m);
  void add_mvar_name(const std::string &mv);
  void run_evaluate();

  s_int_t get_sym_addr(const key_tok_t ktt,  const full_symbol_t &fst);
  std::vector<std::string> get_sym_key(const key_tok_t ktt,  const full_symbol_t &fst);

};
