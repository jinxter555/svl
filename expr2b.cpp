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


using namespace std;

class Expr {
 private:
  bool IsFunction(const string& token) const {
    return token == "sin" || token == "cos";
  }

  int Precedence(const string& op) const {
    if (op == "+" || op == "-") return 1;
    if (op == "*" || op == "/") return 2;
    if (op == "^") return 3;
    return 0;
  }

  vector<Token> infix_;
 public:
  Expr(const vector<Token>& infix) : infix_(infix) {}

  vector<Token> ToPostfix() {
    stack<Token> s;
    vector<Token> postfix;

    for (const auto& token : infix_) {
      if (token.is_number()) {
        postfix.push_back(token);
      } else if (token.is_operator()) {
        while(
          !s.empty() && 
          s.top().is_operator() && 
          Precedence(s.top().op()) >= 
          Precedence(token.op()) 
        ) {
          postfix.push_back(s.top());
          s.pop();
        }
        s.push(token);
      } else if (token.op() == "(") {
        s.push(token);
      } else if (token.op() == ")") {
        while (!s.empty() && s.top().op() != "(") {
          postfix.push_back(s.top());
          s.pop();
        }
        s.pop();
      } else if (IsFunction(token.op())) {
        cout << "token function handling: " << "\n";
        s.push(token);
      }
    }

    while (!s.empty()) {
      postfix.push_back(s.top());
      s.pop();
    }

    return postfix;
  }

  Token Evaluate() {
    stack<Token> s;

    for (const auto& token : ToPostfix()) {
      if (token.is_number()) {
        s.push(token);
      } else if (token.is_operator()) {
        Token num2 = s.top();
        s.pop();
        Token num1 = s.top();
        s.pop();

        s.push(Token::calc(token.op(), num1, num2));
      } else if (IsFunction(token.funcname())) {
        cout << "in function handling: " << "\n";
        void *handle = dlopen(LIBM_SO, RTLD_LAZY);


        if (!handle) {
          cerr << "Error: " << dlerror() << endl;
          exit(1);
        }

        typedef double (*MathFunc)(double);

        MathFunc func = 
          reinterpret_cast<MathFunc>(
            dlsym(handle, token.funcname().c_str())
          ); // op should be function

        if (!func) {
          cerr << "Error: " << dlerror() << endl;
          exit(1);
        }

        Token arg = s.top();
        s.pop();

        double arg_value = (double) get<float>(arg.value);
        cout << "arg_value: " << arg_value << "\n";

        Token result = Token((float) func(arg_value), FLOAT);

        dlclose(handle);

        s.push(result);
      }
    }

    return s.top();
  }

};

int main() {
  vector<string> infix2 = {"3", "+", "4", "*", "2", "/", "(", "1", "-", "5", ")", "^", "2"};
  vector<Token> infix3 = {
    Token(10, INTEGER),
    Token("+", OPERATOR),
    Token(20, INTEGER),
    Token("*", OPERATOR),
    Token(50.123f, FLOAT)
   };
  vector<Token> infix = {
    Token("sin", OPERATOR),
    Token("(", OPERATOR),
    Token(50.123f, FLOAT),
    Token(")", OPERATOR),
  };

  
  Expr expr(infix);

  cout << "Infix: ";
  for (auto& token : infix)
    token.print();
  
  cout << endl;
  
  cout << "Postfix: ";
  for (auto& token : expr.ToPostfix()) 
    token.print();
  
  cout << endl;
  
  cout << "Result: " ;
  expr.Evaluate().print();

  cout << endl;

  return 0;
}
