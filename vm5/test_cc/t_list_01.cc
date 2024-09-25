#include "../entity.hh"
#include "../ast.hh"

ostream& operator<<(ostream& os, const OperandType& t);

int main() {
  Entity list1(OperandType::list_t);
  Entity list2(OperandType::list_t);
  Operand i1(1);
  Operand i2(2);
  Operand i3(3);
  AstList l1;
  l1.add(i1);
  l1.add(i2);
  l1.add(i3);


  cout << "list1: " << list1 << "\n";
  //cout << "l1: " << (Entity) l1 << "\n";
  l1.print();

  return 0;
}