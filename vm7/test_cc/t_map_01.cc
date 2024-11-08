#include "../ast_list.hh"
#include "../ast_map.hh"


int main() {
  Operand i1(1l);
  Operand i2(2l);
  Operand i3(3l);

  Operand one("one");
  Operand two("two");
  Operand three("three");
  Operand m1_s("m1");
  Operand m2_s("m2");

  AstList l1, l2;

  l1.add(i1);
  l1.add(i2);
  l1.add(i3);
  l2.add(l1);
  l2.add(l2);

  AstMap m1, m2;
  
  cout << "m1: " << m1 << "\n";
  cout << "m2: " << m2 << "\n\n";

  m1.add(two, Operand(123l));
  cout << "m1: " << m1 << "\n";
  cout << "m1 has key two: " <<  m1.has_key(two) << "\n";



  return 0;


  auto &one1b = m1.add(one, make_unique<AstMap>());
  cout <<  "one1b add : " << one1b.add("two", i2) << "\n";;

  cout << m1 << "\n";
  auto rptr  = m1.get_raw_ptr(one);
  cout << rptr << "\n";
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

  auto &mr = m2.add(m1_s, m1);
  mr.add("m1", m1);

  m2.add(m2_s, m1);

  cout << "m1: " << m1 << "\n";
  cout << "m2: " << m2 << "\n\n";
  cout << "mr: " << mr << "\n\n";



  return 0;
}