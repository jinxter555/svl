#pragma once
#include <memory>
#include <stack>
#include <iostream>
#include "tree.hh"
#include "ast.hh"
#include "universe.hh"
#include "lang.hh"
#include "frame.hh"

class SvlmLang {
  friend class SvlmInteractive;
  friend class SvlmLangContext;

public:
  std::shared_ptr<Tree> context_tree;

  SvlmLang(std::shared_ptr<Tree> tp);
  std::stack<std::shared_ptr<ListExprAst>> ast_current_contexts;
  std::shared_ptr<ListExprAst> ast_current_context;
  
  std::stack<Frame> svlm_frames;
  std::stack<vartype_t> svlm_stack;

  std::shared_ptr<ListExprAst> new_ast_l_cc(std::string v="block") {
    ast_current_contexts.push(ast_current_context);
    ast_current_context = std::make_shared<ListExprAst>(v);
    return ast_current_context;
  }
  std::shared_ptr<ListExprAst> done_ast_l_cc() {
    ast_current_context = ast_current_contexts.top();
    ast_current_contexts.pop();
    return ast_current_context;
  }

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

  void add_function_name(const std::string &n);
  void add_function_args(std::vector<std::string> param_list);
  void add_function_body(std::shared_ptr<ExprAst> code);

  void run_evaluate();
  std::any evaluate_last_line();

  s_int_t get_sym_addr(const key_tok_t ktt,  const full_symbol_t &fst);
  std::vector<std::string> get_sym_key(const key_tok_t ktt,  const full_symbol_t &fst);

};
