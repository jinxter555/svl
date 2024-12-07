#include "../ast_list.hh"

int main() {
  AstList l1;

  l1.add(Operand(123l));
  l1.add(Operand(456l));
  l1.add(Operand(789l));
  l1.add(Operand("hello"));

  cout << "l1: " <<  l1 << "\n";
  auto &l2 =  l1;
  cout << "l2: " <<  l2 << "\n";
  l2[1l] = 55555l;
  cout << "l1: " <<  l1 << "\n";
  cout << "l2: " <<  l2 << "\n";
  l1[1l] = 6666l;
  cout << "l1: " <<  l1 << "\n";
  cout << "l2: " <<  l2 << "\n";
  //exit(1);



  return 0;
}