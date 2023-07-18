#pragma once

#include <iostream>
#include "vm_svl.hh"
#include "expr.hh"


using namespace std;

class Interpreter {
private:
  VMsvl vmsvl;
public:
  Interpreter() {};
  void vmsvl_add_expr(vector<Token>& infix);
  void vmsvl_add_expr(Expr& e);
  void vmsvl_print_code(Expr& e);
  void vmsvl_print_stack(Expr& e);
  void run();
};
