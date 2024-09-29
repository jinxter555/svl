#include "../operand_entity.hh"
#include "../map_entity.hh"


int main() {
  OperandEntity i1(1);
  OperandEntity i2(2);
  OperandEntity i3(3);

  OperandEntity one("one");
  OperandEntity two("two");
  OperandEntity three("three");
  OperandEntity m1_s("m1");
  OperandEntity m2_s("m2");
  MapEntity m1, m2;
  m1.add(one,i1);
  m1.add(two, i2);
  m1.add(three, i3);

  m2.add(m1_s, m1);
  m2.add(m2_s, m1);

  cout << "m1: " << m1 << "\n\n";
  cout << "m2: " << m2 << "\n\n";
  m2.set(m2_s, m2);
  cout << "m2: " << m2 << "\n\n";


  return 0;
}