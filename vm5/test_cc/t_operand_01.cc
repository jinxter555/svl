#include "../operand.hh"

int main() {
  Operand i1(10);
  Operand i2(10);
  Operand s1(string("str1"));
  Operand s2(string("str2"));
  Operand s3("str3");
  Operand s4("str4");
  Operand nil;

  cout << i1 + i2 << "\n";
  cout << s1 + s2 << "\n";
  cout << s3 + s4 << "\n";
  cout << nil << "\n";
  cout << i1 + s4 << "\n";

  return 0;
}