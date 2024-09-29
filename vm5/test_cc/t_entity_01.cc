#include "../entity.hh"

ostream& operator<<(ostream& os, const OperandType& t);

int main() {
  Operand nil;
  Operand b1(true) ;
  Operand b2(false) ;
  cout << "nil b1 b2: " << nil << " " << b1 << " " << b2 << "\n";
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