#include <cassert>
#include "../operand.hh"
#include "../ast_list.hh"

int main() {
  Operand i1(11l);
  Operand i2(12l);
  Operand i3(13l);
  AstList l1;
  l1.add(i1);
  l1.add(i2);
  l1.add(i3);

  Operand l1a_ptr(l1.clone_usu());
  Operand l1b_ptr(l1a_ptr.clone_usu());
  //Operand l1b_ptr(l1.clone_usu());
  l1b_ptr.set(0l, Operand(666l));
  l1a_ptr.set(1l, Operand(555l));



  cout << "i1: " << i1 << "\n";
  cout << "i1.clone_usu(): " << i1.clone_usu() << "\n";
  cout << "\n";
  cout << "l1: " << l1 << "\n";
  cout << "l1a_ptr: " << l1a_ptr << "\n";
  cout << "l1b_ptr: " << l1b_ptr << "\n";


  cout << "\n";
}