#include "../operand.hh"

int main() {
  Operand i1(10l);
  Operand i2(12l);
  Operand s1(string("str1"));
  Operand s2(string("str2"));
  Operand s3("str3");
  Operand s4("str4");

  cout << "app: t_operand_01\n";
  cout <<  i1._to_str() << "\n";
  cout <<  s2._to_str() << "\n";
  cout <<  s3._to_str() << "\n";
  cout <<  s4._to_str() << "\n";

  return 0;
}