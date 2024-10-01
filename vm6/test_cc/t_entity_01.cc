#include "../entity.hh"

ostream& operator<<(ostream& os, const OperandType& t);

int main() {
  Operand nil;
  Operand b1(true) ;
  Operand b2(false) ;
  Operand i1(Number(123l)) ;
  Operand i2(123l) ;
  Operand f1(1.23) ;
  cout << "nil b1 b2: " << nil << " " << b1 << " " << b2 << "\n";

  Operand s1(move(string("hello"))) ;

  cout << "i1: " << i1 << "\n";
  cout << "i2: " << i2 << "\n";
  cout << "f1: " << f1 << "\n";
  cout << "s1: " << s1 << "\n";

  //cout << o1 << "\n";
  return 0;
}