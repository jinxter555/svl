#include "../entity.hh"

ostream& operator<<(ostream& os, const OperandType& t);

int main() {
  Entity i1(10);
  Entity i2(20);
  Operand o1(11) ;
  Operand o2(21) ;

  Entity e1 = o1;


  cout << i1 + i2 << "\n";
  cout << o1 + i2 << "\n";
  cout << o1.get_type() << "\n";
  cout << e1 << "\n";
  cout << e1.e_type_<< "\n";

  return 0;
}