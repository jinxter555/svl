#include "../operand_entity.hh"
#include "../list_entity.hh"

ostream& operator<<(ostream& os, const OperandType& t);

int main() {
  OperandEntity i1(1);
  OperandEntity i2(2);
  OperandEntity i3(3);
  OperandEntity i4=i1+i2+i3;
  ListEntity l1, l2;
  l1.add(i1);
  l1.add(i2);
  l1.add(i3);
  l2.add(l1);
  l2.add(l1);
  l2.add(l2);



  cout << "l1 type: " << l1.type_str() << "\n";
  cout << "l1: " << l1 << "\n";
  cout << "l1[1]: " << l1.get(1) ;
  cout << "\n\n";
  cout << "l2 type: " << l2.type_str() << "\n";
  cout << "l2[1]: " << l2.get(1) << "\n";
  cout << "l2: " << l2 << "\n\n";
  const Entity &l3 = l2.get(1);
  cout << "l3: " << l3 << "\n";
  l1.set(i1, i4);
  // auto i5 = i4 + i4 + i4; // pure function auto  won't compile
  OperandEntity i5 = i4 + i4 + i4;
  l1.set(i2, i5);
  cout << "l1: " << l1 << "\n";


  //cout << "l1: " << (Entity) l1 << "\n";
  //l1.print();

  return 0;
}