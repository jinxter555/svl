#include "../ast_list.hh"

int main() {
  AstList l1;

  l1.add(Operand(123l));
  l1.add(Operand(456l));
  l1.add(Operand(789l));
  l1.add(Operand("hello"));

  cout << "l1[1]: " << l1[1] << "\n";
  cout << "l1[3]: " << l1[3] << "\n";
  l1[1] = 5555l;
  cout << "l1[1]: " << l1[1] << "\n";
  l1[3] = string("world");
  cout << "l1[3]: " << l1[3] << "\n";
  cout << "l1[33]: " << l1[33] << "\n";



  return 0;
}