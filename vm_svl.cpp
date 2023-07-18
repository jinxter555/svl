#include "expr.hh"
#include "token.hh"
#include "vm_svl.hh"

using namespace std;
void VMsvl::push(Token tv) {
  stack.push(tv);
}
Token VMsvl::pop() {
  Token v = stack.top();
  stack.pop();
  return v;
}

void VMsvl::call(int address) {
  frames.push_back(Frame(pc, fp));
  fp = stack.size();
  pc = address;
}

void VMsvl::decl(const string& name) {
  context.locals[name] = context.vp++;
  push(Token()); // empty token 
}

void VMsvl::print_code() {
  for(auto token: code) {
    token.print();
  }
}
void VMsvl::print_stack() {
  //for(auto token: stack) {
  //  token.print();
  //}
  auto token  = stack.top();
  token.print();

}
void VMsvl::clear_code() {
  code.clear();
}
void VMsvl::add_expr(vector<Token>& expr) { // takes variable expr modify th
    // auto ep = expr.ToPostfix();
    code.insert(code.end(), expr.begin(), expr.end());
}

void VMsvl::run() {
  for(;pc < code.size(); pc++) {
    auto& token = code[pc];
    auto& next_token = code[pc+1];

    if(token.is_number()) {
      stack.push(token);
    } else if(token.is_op_bin()) {
      Token num2 = stack.top();
      stack.pop();
      Token num1 = stack.top();
      stack.pop();

      stack.push(Token::calc(token.op(), num1, num2));
    } else if(token.op() == "=") { // assignment like the uni op, ++, -- etc
      Token id1 = next_token; pc++; // eat the next token
      Token result = stack.top();

      cout << "token identifier = " << id1.identifer() << "\n";
      cout << "result = "; result.print();
      continue;
    } else if(Expr::IsFunction(token, next_token)) {
      cout << "in eval function handling:\n";
    }
  }
}


