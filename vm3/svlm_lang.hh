#pragma once
#include <memory>
#include <stack>
#include <iostream>
#include "tree.hh"
#include "ast.hh"
#include "universe.hh"
#include "lang.hh"
#include "frame_svlm.hh"

std::ostream& operator << (std::ostream& out, std::any& a) ;

class SvlmLang {
  friend class SvlmInteractive;
  friend class SvlmLangContext;

public:
  std::shared_ptr<Tree> context_tree;

  SvlmLang(std::shared_ptr<Tree> tp);
  std::stack<std::shared_ptr<ListExprAst>> ast_current_contexts;
  std::shared_ptr<ListExprAst> ast_current_context;
  
  std::vector<FrameSvlm> svlm_frames;
  std::vector<std::any> svlm_stack;
  FrameSvlm frame;
  bool ast_eval_continue = true;

  void fcall_args_setup(std::vector<std::any>);


  // parser functions
  std::shared_ptr<ListExprAst> new_ast_l_cc(std::string v="code_block") {
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
  bool interactive = false; // if this is going to be from file or prompt

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

  void fcall_stack_setup(std::vector<std::any> args, std::string callee) {
    // get the lvar from 
    full_symbol_t fst = current_context; 
    fst.mfunction=callee;
    std::string k;
    std::vector<std::string> keys, lvar_keys;
    keys = move(get_sym_key(key_tok_t::mfunction, fst)); // same as lva
    keys.push_back("lvars");
    std::shared_ptr<TreeNode> lvar_node  = svlm_lang->context_tree->get_node({keys});
    std::map<std::string, std::shared_ptr<TreeNode>> lvars = lvar_node->get_children();

    std::cout<< "keys: "; for(auto k: keys) {std::cout << k << " ";} std::cout << "\n";

    std::cout << "lvars:\n";
    for (const auto& [key, _] : lvars) {
      std::cout << "k: " << key << "\n";
    }
    std::cout << "\n";

    for(int i=0; i<args.size(); i++) {
      std::cout << "arg: " << std::any_cast<std::string>(lvar_node->get_member_data(i)) << "=" << args[i]<< "\n";
      k = std::any_cast<std::string>(lvar_node->get_member_data(i));
      lvars[k]->set_data(args[i]);
    }

    svlm_lang->svlm_stack.push_back(lvars);

  }
};
