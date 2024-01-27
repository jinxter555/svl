#pragma once

#include <iostream>
#include "vm_svl.hh"
#include "expr.hh"


using namespace std;

class Interpreter {
private:
  VMsvl vmsvl;
  vector<Token> code; // postfix expressions
  int pc; // counter for adding expr to code
public:
  Interpreter() {};
  void add_expr(vector<Token>& infix);
  void add_expr(Expr& e);
  void vmsvl_print_code(Expr& e);
  void vmsvl_print_stack(Expr& e);
  void cml_action(const string &act);
  void print_code();
  void run();
};
