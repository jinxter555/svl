#include "../ast.hh"

int main() {
  QueNode node;
  MapEntity nil_map;

  //vector<string> keys = {"hello"};
  //node.add_branch(keys, 123l);
  //node.print_m();
  //return 0;
/*
  cout << nil_map << "\n";
  cout << nil_map.to_str() << "\n";
  cout << e->to_str() << "\n";
*/

  vector<string> keys0 = {"null"};
  vector<string> keys1 = {"hello", "one", "two1", "three"};
  vector<string> keys1b = {"hello", "one", "two1"};
  auto l1=make_unique<ListEntity>();
  l1->add(3.1415);
  l1->add(42l);
  l1->add(123567l);


  vector<string> keys2 = {"hello", "one", "two2", "three", "four", "Five"};
  vector<string> keys3 = {"hello", "one-one", "two", "three", "four", "Five"};
  vector<string> keys3b  = {"hello", "one-one", "two"};
  vector<string> keys4 = {"hello", "one-one", "two", "three", "four1", "Five"};

  AstOperand o1(Operand(123l));
  o1.print(); cout << "\n";
  //node.add_branch(keys4, move(l1));
  node.add_branch(keys4, o1.clone());
  node.print_m();




  return 0;
}