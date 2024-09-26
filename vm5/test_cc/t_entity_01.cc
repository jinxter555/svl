#include "../entity.hh"

ostream& operator<<(ostream& os, const OperandType& t);

int main() {
  Entity i1(10);
  Entity i2(22);
  Entity i3(33);
  Entity i4(44);
  Entity i5(55);
  Operand o1(11) ;
  Operand o2(2222) ;
  Operand o4(3322) ;
  Operand s1(move(string("hello"))) ;

  Entity e1 = o1;
  Entity e3 = s1;

  cout << "e1 = o1, e1: " << e1 << "\n";
  cout << "e1 = o1, o1: " << o1 << "\n";
  cout << "e3 = s1, s1: " << s1 << "\n";
  cout << "e3 = s1, s1: " << e3 << "\n";

  Operand o3 = e1;

  cout << i1 + i2 << "\n";
  cout << o1 + i2 << "\n";
  cout << o1 * i2 << "\n";
  cout << o1.type_str() << "\n";
  cout << e1 << "\n";
   cout << e1.type_str() << "\n";
  cout  << o3 + e1 << "\n";


  if(o3 == e1) { cout << "o3 == e1\n"; }
  if(o3 == i1) { cout << "o3 == i1\n"; }
  else {cout << "o3 != i1\n";}

  Operand err1 =  i1 + s1;
  cout << "err: " << err1 << "\n";
  cout << "err whatami: " << err1.whatami() << "\n";

  return 0;
}