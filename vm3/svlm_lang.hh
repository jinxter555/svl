#pragma once
#include <memory>
#include <stack>
#include <iostream>
#include "tree.hh"
#include "ast.hh"
#include "universe.hh"

class SvlmLang {
  friend class SvlmInteractive;
private:
  std::shared_ptr<Tree> context_tree;
public:
  SvlmLang(std::shared_ptr<Tree> tp);
  std::stack<std::shared_ptr<ListExprAst>> current_contexts;
  std::shared_ptr<ListExprAst> current_context;

};

