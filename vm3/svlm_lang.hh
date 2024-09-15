#pragma once
#include <memory>
#include <stack>
#include <iostream>
#include "tree.hh"
#include "ast.hh"
#include "universe.hh"
#include "lang.hh"



std::ostream& operator << (std::ostream& out, std::any& a) ;

class SvlmLang {
  friend class SvlmInteractive;
  friend class SvlmLangContext;

public:
  std::shared_ptr<Tree> context_tree;

  SvlmLang(std::shared_ptr<Tree> tp);
  std::stack<std::shared_ptr<ListExprAst>> ast_current_contexts;
  std::shared_ptr<ListExprAst> ast_current_context;
  
  //std::vector<FrameSvlm> svlm_frames;
  // std::vector<std::any> svlm_stack;
  //std::vector<std::shared_ptr<TMA>> svlm_stack;
  std::vector<FrameSvlm> svlm_stack;
  //FrameSvlm frame;
  ControlFlow control_flow = ControlFlow::run;
  std::shared_ptr<ExprAst> fc_exp; // flow control expression
  std::stack<ControlFlow> control_flow_stack;

  ControlFlow pop_control_flow();
  void push_control_flow();
  void reset() {
    control_flow = ControlFlow::run;
    while(!control_flow_stack.empty()) 
      control_flow_stack.pop();
  }
private:

};

class SvlmLangContext  {
public:
  SvlmLang *svlm_lang;
  full_symbol_t current_context;
  bool interactive = false; // if this is going to be from file or prompt
  bool last_line = false; // command prompt last line
  bool defining_func = false;

  SvlmLangContext(SvlmLang *s);
  void init(SvlmLang *s) { svlm_lang=s; } 
  void add_app_name(const std::string &app);
  void add_module_name(const std::string &m);
  void add_mvar_name(const std::string &mv);

  void add_function_name(const std::string &n);
  void add_function_params(std::vector<std::string> param_list);
  void add_function_lvars(const std::vector<std::string> lvars);
  void add_function_fbody(std::shared_ptr<ExprAst> code);

  void run_evaluate();
  std::any evaluate_last_line();

  s_int_t get_sym_addr(const key_tok_t ktt,  const full_symbol_t &fst);
  std::vector<std::string> get_sym_key(const key_tok_t ktt,  const full_symbol_t &fst);

  void fcall_stack_setup(std::vector<std::any> args, std::string callee);
};
