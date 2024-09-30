#include "../ast.hh"

int main() {
  Operand i1(101);
  Operand i2(102);
  Operand s1(string("str1"));
  Operand s2(string("str2"));
  Operand s3("str3");
  Operand s4("str4");
  Operand nil;

  AstOperand ao1(i1);
  AstOperand ao2(123);
  OperandEntity oe1(i1);
  ao1.print();
  ao2.print();
  cout << "\n";
  cout << oe1 << "\n";

  return 0;
}