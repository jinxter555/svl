#include <cassert>
#include "../operand.hh"
#include "../ast_list.hh"


int main() {
  //OperandEntity i1(12345l);
  Operand i1(1l);
  Operand i2(2l);
  Operand i3(3l);
  Operand i4 = i1.clone_val();

  AstList l1, l2;

  cout << "i1 : " << i1 << "\n";
  cout << "i1.clone() : " << i1.clone() << "\n";
  cout << "l1 type: " << l1.get_type() << "\n";
  cout << "l1: " << l1 << "\n";



  assert(l1.add(i1)==true);

  l1.add(i2);
  l1.add(i3);
  l2.add(l1);
  l2.add(l1);
  l2.add(l2);



  cout << "l1 type: " << l1.get_type() << "\n";
  cout << "l1: " << l1 << "\n";
  cout << "l1[1]: " << l1.getv(1) ;
  cout << "\n\n";
  cout << "l2 type: " << l2.get_type() << "\n";
  cout << "l2[1]: " << l2.getv(1) << "\n";
  cout << "l2: " << l2 << "\n\n";
  const Operand& ov2 = l2.getv(1);//.clone_val();
  const Operand& ov2b = l2[1];//.clone_val();
  cout << "ov2: " << ov2 << "\n";
  cout << "ov2b: " << ov2b << "\n";
  // auto i5 = i4 + i4 + i4; // pure function auto  won't compile
  cout << "l1: " << l1 << "\n";

  //cout << "l1: " << (Entity) l1 << "\n";
  //l1.print();

  return 0;
}