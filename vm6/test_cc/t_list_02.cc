#include "../entity.hh"

int main() {
  long z=0;
  Operand i0(z);
  Operand i1(1l);
  Operand i2(2l);
  Operand i3(3l);
  Operand o_i4=i1+i2+i3;
  OperandEntity i4(o_i4);


  ListEntity l1, l2;
  l1.add(i1);
  l1.add(i2);
  l1.add(i3);

  l2.add(l1);
  l2.add(l1);
  l2.add(l2);






  cout << "l1: " << l1 << "\n";
  cout << "l1 type: " << l1.get_type() << "\n";
  cout << "l1[1]: " << l1.get(1) ;
  cout << "\n\n";

  cout << "l2 type: " << l2.get_type() << "\n";
  cout << "l2[1]: " << l2.get(1) << "\n";
  cout << "l2: " << l2 << "\n\n";
  const Entity &l3 = l2.get(1);
  cout << "l3: " << l3 << "\n\n";

  l1.set(OperandEntity(i1), i4);
  // auto i5 = i4 + i4 + i4; // pure function auto  won't compile
  OperandEntity i5 =i4.opfunc(i4, AstOpCode::mul );
  l1.set(OperandEntity(i2), i5);
  cout << "l1: " << l1 << "\n";

  //const ListEntity& mylist = l2.get_list(1);
  auto &mylist = l2.get_list(1);
  //mylist.print_list();
  cout << "mylist: " << mylist << "\n";
  cout << "l2: " << l2 << "\n\n";

  ListEntity l4 = l1;
  cout << "l4: " << l4 << "\n";
  ListEntity l5(l1);
  cout << "l1: " << l1 << "\n";
  cout << "l5: " << l5 << "\n";




  return 0;
}