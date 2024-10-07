#include "../entity.hh"


int main() {
  //OperandEntity i1(12345l);
  Operand i1(1l);
  Operand i2(2l);
  Operand i3(3l);
  //OperandEntity i4=i1.opfunc(i2.opfunc(i3, AstOpCode::plus), AstOpCode::plus);
  Operand i4=i1.opfunc(i2.opfunc(i3, AstOpCode::plus), AstOpCode::plus);

  ListEntity l1, l2;

  cout << "i1 : " << i1 << "\n";
  cout << "l1 type: " << l1.get_type() << "\n";
  cout << "l1: " << l1 << "\n";

  l1.add(i1);
  l1.add(i2);
  l1.add(i3);
  l2.add(l1);
  l2.add(l1);
  l2.add(l2);



  cout << "l1 type: " << l1.get_type() << "\n";
  cout << "l1: " << l1 << "\n";
  cout << "l1[1]: " << l1.get(1) ;
  cout << "\n\n";
  cout << "l2 type: " << l2.get_type() << "\n";
  cout << "l2[1]: " << l2.get(1) << "\n";
  cout << "l2: " << l2 << "\n\n";
  //const Entity &l3 = l2.get(1).clone_val();
  //cout << "l3: " << l3 << "\n";
  l1.set(i1, i4);
  // auto i5 = i4 + i4 + i4; // pure function auto  won't compile
  Operand i5 = i4.opfunc(i4, AstOpCode::mul);
  l1.set(i2, i5);
  cout << "l1: " << l1 << "\n";

  //cout << "l1: " << (Entity) l1 << "\n";
  //l1.print();

  return 0;
}