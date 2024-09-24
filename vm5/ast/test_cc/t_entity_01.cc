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

  Entity e1 = o1;
  Operand o3 = e1;


  cout << i1 + i2 << "\n";
  cout << o1 + i2 << "\n";
  cout << o1.type_str() << "\n";
  cout << e1 << "\n";
   cout << e1.type_str() << "\n";
  cout  << o3 + e1 << "\n";


  if(o3 == e1) { cout << "o3 == e1\n"; }
  if(o3 == i1) { cout << "o3 == i1\n"; }
  else {cout << "o3 != i1\n";}

  Entity list1(OperandType::list_t);
  Entity list2(OperandType::list_t);
  list1.list_add(i1);
  list1.list_add(i2);
  list1.list_add(i3);
  list1.list_add(i4); list1.list_add(i5); list1.list_add(o1); list1.list_add(o2); list1.list_add(o4);
  cout << "list1: " << list1 << "\n";
  list2.list_add(list1);
  list2.list_add(list1);
  cout << "list2: " << list2 << "\n";

  return 0;
}