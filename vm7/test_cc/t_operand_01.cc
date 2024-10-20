#include "../operand.hh"

int main() {
  Operand i1(11l);
  Operand i2(12l);
  Operand s1(string("str1"));
  Operand s2(string("str2"));
  Operand s3("str3");
  Operand s4("str4");
  Operand nil;

  const Operand &oref= i1.getv();
  auto oref1 = oref.clone_val();


  cout << i1 + i2 << "\n";
  cout << s1 + s2 << "\n";
  cout << s3 + s4 << "\n";
  cout << nil << "\n";
  cout << i1 + s4 << "\n";

  oref1 = oref1 + 12345l;
  cout << "i1: " << i1 << "\n";
  cout << "i1.getv(): " << i1.getv() << "\n";
  cout << "oref1: " << oref1<< "\n";

  return 0;
}