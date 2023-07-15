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
  context.locals[name] = vp;
  vp++;
}

void VMsvl::add_expr(Expr& expr) { // takes variable expr modify th
    auto ep = expr.ToPostfix();
    code.insert(code.end(), ep.begin(), ep.end());
}

void VMsvl::run() {
}


