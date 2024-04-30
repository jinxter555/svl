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

private:
  std::shared_ptr<Tree> context_tree;
public:
  SvlmLang(std::shared_ptr<Tree> tp);
  std::stack<std::shared_ptr<ListExprAst>> ast_current_contexts;
  std::shared_ptr<ListExprAst> ast_current_context;

};

class SvlmLangContext  {
  SvlmLang *svl_lang;
  full_symbol_t current_context;
public:
  SvlmLangContext();
  void init(SvlmLang *s) {
    std::cout << "init svlang: " << s << "\n";
    svl_lang=s;
  } 
  void add_app_name(const std::string &app);
  void add_module_name(const std::string &m);
  void add_mvar_name(const std::string &mv);
  s_int_t get_sym_addr(const key_tok_t ktt,  const full_symbol_t &fst);
  std::vector<std::string> get_sym_key(const key_tok_t ktt,  const full_symbol_t &fst);
};
