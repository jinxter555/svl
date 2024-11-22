#include "../ast_list.hh"

int main() {
  AstList l1;

  Operand i1(1l);
  l1.add(Operand(123l));
  l1.add(Operand(456l));
  l1.add(Operand(789l));
  l1.add(Operand("hello"));

  cout << "l1[1]: " << l1[1l] << "\n";
  cout << "l1[3]: " << l1[3l] << "\n";
  //l1[1l] = Operand(5555l).clone();
  l1[1l] = make_unique<Operand>(5555l);
  cout << "l1[1]: " << l1[1l] << "\n";
  l1[3l] = Operand("world").clone();
  cout << "l1[3]: " << l1[3l] << "\n";
  cout << "l1[33]: " << l1[33l] << "\n";



  return 0;
}