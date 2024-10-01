#include "../entity.hh"

ostream& operator<<(ostream& os, const OperandType& t);

int main() {
  Operand nil;
  Operand b1(true) ;
  Operand b2(false) ;
  Operand i1(123l) ;
  cout << "nil b1 b2: " << nil << " " << b1 << " " << b2 << "\n";

  Operand s1(move(string("hello"))) ;

  cout << "s1: " << s1 << "\n";

  //cout << o1 << "\n";
  return 0;
}