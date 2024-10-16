#include "../ast.hh"


int main() {
  Operand i1(1l);
  Operand i2(2l);
  Operand i3(3l);

  Operand one("one");
  Operand two("two");
  Operand three("three");
  Operand m1_s("m1");
  Operand m2_s("m2");

  ListEntity l1, l2;

  l1.add(i1);
  l1.add(i2);
  l1.add(i3);
  l2.add(l1);
  l2.add(l2);

  MapEntity m1, m2;
  
  cout << "m1: " << m1 << "\n";
  cout << "m2: " << m2 << "\n\n";


  m1.add(one, i1);
  m1.add(two, i2);
  m1.add(three, i3);
  m1.add(string("l1"), l1);
  m1.add(string("l2"), l2);
  Operand i4 = i3.opfunc(i1, AstOpCode::plus);
  //m1.add("four", i3+i1);
  m1.add(string("four"), i4);
  //m1.add("five", i3+i2);
  Operand i5 = i3.opfunc(i2, AstOpCode::plus);
  m1.add(string("five"), i5);

  auto mr = m2.add(m1_s, m1).get_type();

  m2.add(m2_s, m1);

  cout << "m1: " << m1 << "\n";
  cout << "m2: " << m2 << "\n\n";
  m2.set(m2_s, m2);
  cout << "m2: " << m2 << "\n";
  cout << "m2 type: " << m2.get_type() << "\n\n";

  auto m3=m1;
  m3.add(string("myworld"), "myhello");
  cout << "m1: " << m1 << "\n";
  cout << "m3: " << m3 << "\n";
  cout << "m3 type: " << m3.get_type() << "\n\n";



  return 0;
}