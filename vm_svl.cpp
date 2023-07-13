#include "token.hh"
#include "vm_svl.hh"

using namespace std;
void VMsvl::push(Token tv) {
  stack.push(tv);
}