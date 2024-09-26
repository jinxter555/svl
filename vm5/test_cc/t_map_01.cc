#include "../entity.hh"
#include "../ast.hh"

ostream& operator<<(ostream& os, const OperandType& t);

int main() {
  Entity list1(OperandType::list_t);
  Entity list2(OperandType::list_t);
  Operand i1(1);
  Operand i2(2);
  Operand i3(3);
  AstMap m1;
  m1.add("hello", i1);
  m1.add("world", i2);
  AstMap m2;
  m2.add("what", m1);
  m2.add("where", m1);

  cout << "m1: " << m1.whatami() << "\n";
  m1.print();
  cout << "m2: " << m1.whatami() << "\n";
  m2.print();
  m1.set("hello", Operand(555));
  m1.print();
  cout << "\n\n";
  m2.print();

  return 0;
}