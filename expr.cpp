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
#include "readinputline.hh"
#include "expr.hh"
#include "token.hh"


using namespace std;

bool Expr::IsFunction(const Token& t1, const Token& t2) const {
    return t1.type == INDENTIFIER && t2.op() == "(";
}

int Expr::Precedence(const string& op) const {
    if (op == "=") return 1;
    if (op == "+" || op == "-") return 10;
    if (op == "*" || op == "/") return 20;
    if (op == "^") return 30;
    return 0;
}

void Expr::print() {
    cout << "Expr infix print()\n";
    for(auto token : infix_) {
      token.print();
      // token.print_t();
    }
    cout << "\n\nExpr postfix print()\n";
    for(auto token : ToPostfix()) {
      token.print();
      // token.print_t();
    }
    cout << "\n";
}

vector<Token> Expr::ToPostfix() {
  return ToPostfix(infix_);
}

vector<Token> Expr::ToPostfix(vector<Token>& infix) {
    stack<Token> s;
    vector<Token> postfix;

    // for (const auto& token : infix_) {
    for (int i=0; i < infix.size(); i++) {
      const auto& token = infix[i];
      const auto& next_token = infix[i+1];

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
      } else if (IsFunction(token, next_token)) {
        cout << "token function handling: " << token.funcname() << "\n";
        s.push(token);
      } else { // push anything for now, might want to check if it's identifer later
        s.push(token);
      }
    }

    while (!s.empty()) {
      postfix.push_back(s.top());
      s.pop();
    }

    return postfix;
  }

Token Expr::Evaluate() {
    stack<Token> s;
    vector<Token> postfix_= ToPostfix();

    //for (const auto& token : ToPostfix()) {
    for (int i=0; i < postfix_.size(); i++) {
      const auto& token = postfix_[i];
      const auto& next_token = postfix_[i+1];
      if (token.is_number()) {
        s.push(token);
      } else if (token.is_op_bin()) { // this should be bin op

        Token num2 = s.top();
        s.pop();
        Token num1 = s.top();
        s.pop();

        s.push(Token::calc(token.op(), num1, num2));
      } else if(token.op() == "=") { // this should be uni op, ++, -- etc
          Token id1 = next_token;
          Token result = s.top();

          // cout << "tok identifier = " <<  id1.identifer() << "\n";
          cout << "tok identifier = " << id1.identifer() << "\n";
          cout << "result = "; result.print();
      } else if (IsFunction(token, next_token)) {
        cout << "in eval function handling: " << "\n";
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


#ifdef __MAIN__
#undef __MAIN__

int main() {
  vector<string> infix2 = {"3", "+", "4", "*", "2", "/", "(", "1", "-", "5", ")", "^", "2"};
  vector<Token> infix1 = {
    Token(10, INTEGER),
    Token("+", OPERATOR),
    Token(20, INTEGER),
    Token("*", OPERATOR),
    Token(50.123f, FLOAT)
   };
  vector<Token> infix = {
    Token("sin", INDENTIFIER),
    Token("(", PAIRS),
    Token(50.123f, FLOAT),
    Token("+", OPERATOR),
    Token(20.323f, FLOAT),
    Token(")", PAIRS),
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
#endif
