#include "../operand_entity.hh"

ostream& operator<<(ostream& os, const OperandType& t);

int main() {
  OperandEntity n1(123);
  cout << "i1:" << n1 << "\n";
  return 0;

  OperandEntity s1("hello");
  cout << "s1:" << s1 << "\n";


  return 0;
  OperandEntity s2(string("hello"));
  OperandEntity i1(Operand(11)) ;
  OperandEntity i2(22) ;
  OperandEntity i3(33) ;
  auto i4 = i2 + i3;
  cout << "s1:" << s1 << "\n";
  cout << "s2:" << s2 << "\n";
  return 0;
  cout << "i1:" << i1 << "\n";
  cout << "i2:" << i2 << "\n";
  cout << "i4:" << i4 << "\n";

  return 0;
}