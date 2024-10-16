#include "../ast.hh"

int main() {
/*
  OperandEntity i1(101l);
  OperandEntity i2(102l);
  OperandEntity i3(103l);
  OperandEntity s1(string("str1"));
  OperandEntity s2(string("str2"));
  OperandEntity s3("str3");
  OperandEntity s4("str4");

  ListEntity l1;
  l1.add(i1);
  l1.add(i2);
  l1.add(i2);
*/

  AstOperand ex1;
  MapEntity node;

  operand_u_ptr vptr1 = make_unique<Operand>("hello123");
  entity_u_ptr vptr2 = make_unique<ListEntity>();
  entity_u_ptr vptr4 = make_unique<MapEntity>();



  Operand i1(123l);
  vptr2->add(Operand(1l));
  vptr2->add(string("what"));

  vptr4->add("three", "world3");
  vptr4->add("four", "world4");
  vptr4->print();
  cout << "\n\n";
  node.add(Operand("system22"), move(vptr2));
  node.add(Operand("system3"), move(vptr4));
  node.add(Operand("system3"), move(vptr4));

//  if(vptr2 == nullptr) { cout << "vptr2 listentity bombed!\n"; exit(1); }
//  if(vptr4 == nullptr) { cout << "vptr4 mapentity bombed!\n"; exit(1); }

  auto o3 = Operand(string("system3"));
  auto &e = node.get(o3);
  auto e_cv = node.get(o3).clone_val();
  cout << "e system3: " << e << "\n";
  cout << "e system3 cloned value: " << e_cv << "\n";

  cout << "after move vptr4";
  //vptr4->print();
  cout << "\n\n";

  node.add(Operand("system11"), Operand("world11"));
  node.add(Operand("system2"), Operand("world2"));
  //node.add(Operand("system3"), vptr4);
  node.print();
  cout << "\n\n";

  //vptr4->print();
  cout << "\n\n";


  node.add(Operand("system2"), move(vptr2));
  //node.add(string("hello1"), Operand("world1"));
  //node.add(string("hello2"), "world2");
  node.add(string("hello23"), move(vptr4));
  node.add(string("hello24"), move(vptr4));

  cout << "astnode1\n";
  cout << "map node\n";
  //node.print();
  cout << "\nex1--\n";

/*
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
*/

  return 0;
}