#include "../entity.hh"


int main() {
  OperandEntity n1(123l);
  cout << "i1:" << n1 << "\n";
  cout << "i1 whatami:" << n1._get_operand().whatami() << "\n";

  OperandEntity s1("hello");
  cout << "s1:" << s1 << "\n";
  cout << "s1:" << s1._get_operand().whatami() << "\n";


  OperandEntity s2(string("hello,world"));
  OperandEntity i1(Operand(11l)) ;
  OperandEntity i2(22l) ;
  OperandEntity i3(33l) ;
  OperandEntity f1(12.345) ;
  Operand f1_o = f1._get_operand();
  OperandEntity i4 = i2 + i3;
  cout << "s1:" << s1 << "\n";
  cout << "s1 geto:" << s1._get_operand() << "\n";
  cout << "s2:" << s2 << "\n";
  cout << "s2 geto:" << s2._get_operand() << "\n";

  cout << "i1:" << i1 << "\n";
  cout << "i2:" << i2 << "\n";
  cout << "f1:" << f1 << "\n";
  cout << "f1_o:" << f1_o << "\n";
  cout << "i4:" << i4 << "\n";

  return 0;
}