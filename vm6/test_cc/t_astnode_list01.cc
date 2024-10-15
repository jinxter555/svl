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
  ListEntity l1;
  l1.add(3.1415);
  l1.add(42l);
  l1.add(123567l);
  //vector<string> keys1 = {"hello", "one"};
  //vector<string> keys1 = {"hello", "one", "two"};


  vector<string> keys2 = {"hello", "one", "two2", "three", "four", "Five"};
  vector<string> keys3 = {"hello", "one-one", "two", "three", "four", "Five"};
  vector<string> keys3b  = {"hello", "one-one", "two"};
  vector<string> keys4 = {"hello", "one-one", "two", "three", "four1", "Five"};

  node.add_branch(keys1, 123l);
  node.print_m();
  node.add_branch(keys2, 456l);
  node.print_m();
  node.add_branch(keys3, 789l);
  node.print_m();
  node.add_branch(keys4, l1);
  node.print_m();

  auto &ov0 = node.get_branch(keys0);
  cout << "ov0: " << ov0 << "\n";

  auto &ov1 = node.get_branch(keys1);
  cout << "ov1: " << ov1 << "\n";

  auto &ov1b = node.get_branch(keys1b);
  cout << "ov1b: " << ov1b << "\n";

  auto &ov3 = node.get_branch(keys3);
  cout << "ov3: " << ov3 << "\n";

  auto &ov3b = node.get_branch(keys3b);
  cout << "ov3b: " << ov3b << "\n";

  auto &ov4 = node.get_branch(keys4);
  cout << "ov4: " << ov4 << "\n";








  return 0;
}