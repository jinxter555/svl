#include "../entity.hh"


int main() {
  OperandEntity i1(1l);
  OperandEntity i2(2l);
  OperandEntity i3(3l);

  OperandEntity one("one");
  OperandEntity two("two");
  OperandEntity three("three");
  OperandEntity m1_s("m1");
  OperandEntity m2_s("m2");
  MapEntity m1, m2;
  m1.add(one,i1);
  m1.add(two, i2);
  m1.add(three, i3);
  OperandEntity i4 = i3 + i1;
  //m1.add("four", i3+i1);
  m1.add("four", i4);
  //m1.add("five", i3+i2);
  OperandEntity i5 = i3 + i2;
  m1.add("five", i5);

  m2.add(m1_s, m1);
  m2.add(m2_s, m1);

  cout << "m1: " << m1 << "\n\n";
  cout << "m2: " << m2 << "\n\n";
  m2.set(m2_s, m2);
  cout << "m2: " << m2 << "\n\n";
  cout << "m2 type: " << m2.get_type() << "\n\n";


  return 0;
}