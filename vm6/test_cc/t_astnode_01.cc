#include "../ast.hh"

int main() {
  OperandEntity i1(101l);
  OperandEntity i2(102l);
  OperandEntity i3(103l);
  OperandEntity s1(string("str1"));
  OperandEntity s2(string("str2"));
  OperandEntity s3("str3");
  OperandEntity s4("str4");

/*
  ListEntity l1;
  l1.add(i1);
  l1.add(i2);
  l1.add(i2);
*/

  AstNode an1;

  an1.add(i1);
  an1.add(i2);
  an1.add(i3);

  i3 = i3 * i2;
  an1.ListEntity::add(i3.clone());

  i3 = i3 + i2;
  entity_u_ptr i4ptr = i3.clone();
  an1.ListEntity::add(i4ptr);

  OperandEntity n1(1l);
  OperandEntity f1(12.345);

  an1.print_l();

  cout << "an[1]: " << an1[1] << "\n";

  //an1[1] = 123.456;
  an1.ListEntity::set(n1, s1);
  an1.print_l();
  an1.MapEntity::add(s1, i1);
  cout << "an[s1]: " << an1[s1._to_str()] << "\n";
  an1.print_m();



  cout << "\n";
//  cout << "l1: " <<  l1 << "\n";

  return 0;
}