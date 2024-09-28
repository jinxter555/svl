#include "../entity.hh"

ostream& operator<<(ostream& os, const OperandType& t);

int main() {
  Operand o1(11) ;
  cout << "o1: " << o1 << "\n";
  Operand o2("hello") ;
  cout << "str o2: " << o2 << "\n";

  Operand o4(3322) ;
  Operand s1(move(string("hello"))) ;


  cout << "e1 = o1, o1: " << o1 << "\n";
  cout << "e3 = s1, s1: " << s1 << "\n";

  //cout << o1 << "\n";
  return 0;
}