#include "../entity.hh"

ostream& operator<<(ostream& os, const OperandType& t);

int main() {
  Operand nil;
  Operand b1(true) ;
  Operand b2(false) ;
  cout << "nil b1 b2: " << nil << " " << b1 << " " << b2 << "\n";


  Operand i1(Number(123l)) ;
  cout << "i1: " << i1 << "\n";
  cout << "i1 gettype: " << i1.get_type() << "\n";
  OperandVariant si_1 = i1._get_value(); // cout << "si_1: " << si_1 << "\n"; // no ostream overload won't work with si_1 
  Operand i2(125l) ;

  Number n1(123l);
  Number n2(456l);
  Number n3 = n1 + n2;
  cout << "n3: " << n3 << "\n";


  Operand i3 = i1 * i2;
  cout << "i3: " << i3 << "\n";
  i3 = i1 + i2;
  Operand i4(i3._get_value());
  cout << "i3: " << i3 << " gettype:" << i3.get_type()<< "\n";
  cout << "i4: " << i4 << " gettype:" << i4.get_type()<< "\n";
  Operand f1(1.23) ;
  cout << "nil b1 b2: " << nil << " " << b1 << " " << b2 << "\n";

  Operand s1(move(string("hello"))) ;

  cout << "i1: " << i1 << "\n";
  cout << "i2: " << i2 << "\n";
  cout << "f1: " << f1 << "\n";
  cout << "f1 gettype: " << f1.get_type() << "\n";
  cout << "s1: " << s1 << "\n";
  cout << "s1 gettype: " << s1.get_type() << "\n";
  cout << "i1 + f1: " << i1+f1 << "\n";


  cout << "i1.get_type(): " << i1.get_type() << "\n";
  cout << "s1.get_type(): " << s1.get_type() << "\n";
  cout << "f1.get_type(): " << f1.get_type() << "\n";

  //cout << o1 << "\n";
  return 0;
}