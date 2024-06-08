#include <variant>
#include "operand.hh"

using namespace std;
int main() {
  int i42=42;
  int i10=10;

  Operand op1(42);
  Operand op1f(12.345f);
  Operand op1n(Number(42));
  Operand op2n(Number(42.123f));
  Operand b1(true);

  //Operand op2(std::string("hello"));
  Operand op2(std::string("hello"));
  Operand op3(10);

  Operand result1 = op1 + op1; // Throws runtime_error (unsupported)
  Operand result2 = op1n + op2n; // Throws runtime_error (unsupported)
  Operand result2s = op2 + op2; // Throws runtime_error (unsupported)
  //Operand result2 = op1 + op3; // Creates Operand(52)
  //Operand result1n = op1 + op1n; // Creates Operand(52)
  //Operand result3 = op2 - op1; // Throws runtime_error (unsupported)
  //Operand result4 = op3 - op1; // Creates Operand(-32)
  //Operand rs = op2   + op2;

  std::cout << result1 << "\n";
  std::cout << result2 << "\n";
  std::cout << result2s << "\n";
  std::cout << op1f + op1f << "\n";
  std::cout << b1 << "\n";
  Operand tt = (b1==b1);
  if(b1==b1 && b1==tt) {
    std::cout << "b1=eql" << "\n";
    std::cout << tt;
  }
  //std::cout << result2 << "\n";
  //std::cout << result1n << "\n";
  //std::cout << rs << "\n";

  return 0;
}

