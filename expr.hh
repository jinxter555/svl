/*
 *
write a c++ Expr class. where it takes an infix vector string of numbers and operators. Then convert the infix vector string to postfix vector string. also write an evaluate function to evaluate the postfix vector. the carret ^ token should be implemented  with the math library pow function in the Evaluate method. modify the Expr class where it can handle Math functions like sin, cos at runtime and use dynamically loaded libraries.

* 
 * */

#include <cmath>
#include <iostream>
#include <stack>
#include <string>
#include <vector>

#include <dlfcn.h>
#include <gnu/lib-names.h>
#include "token.hh"
#include "readinputline.hh"

#pragma once


using namespace std;

class Expr {
 private:
  vector<Token> infix_;

  static int Precedence(const string& op);
  friend class Interpreter;
 public:
  Expr() {}
  Expr(const ReadInputLine& ril) {
    infix_ = move(ril.infix_tokens);
  }
  Expr(const vector<Token>& infix) : infix_(infix) {}

  vector<Token> ToPostfix();
  static vector<Token> ToPostfix(vector<Token>& infix);
  Token Evaluate();
  Token Evaluate(vector<Token>& postfix);
  void print();

  static bool IsFunction(const Token& t1, const Token& t2);
};
