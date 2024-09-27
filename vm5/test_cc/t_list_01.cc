#include "../entity.hh"
#include "../ast.hh"

ostream& operator<<(ostream& os, const OperandType& t);

int main() {
  Entity list1(OperandType::list_t);
  Entity list2(OperandType::list_t);
  Operand i1(1);
  Operand i2(2);
  Operand i3(3);
  AstList l1, l2;
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


  //cout << "l1: " << (Entity) l1 << "\n";
  //l1.print();

  return 0;
}