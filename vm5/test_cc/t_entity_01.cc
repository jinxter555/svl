#include "../entity.hh"

ostream& operator<<(ostream& os, const OperandType& t);

int main() {
  Operand o1(11) ;
  Operand o2(2222) ;
  Operand o4(3322) ;
  Operand s1(move(string("hello"))) ;


  cout << "e1 = o1, o1: " << o1 << "\n";
  cout << "e3 = s1, s1: " << s1 << "\n";


  cout << o1.type_str() << "\n";




  return 0;
}