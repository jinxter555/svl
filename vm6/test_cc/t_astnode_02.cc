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

  vector<string> keys1 = {"hello", "one", "two1", "three"};
  //vector<string> keys1 = {"hello", "one"};
  //vector<string> keys1 = {"hello", "one", "two"};


  vector<string> keys2 = {"hello", "one", "two2", "three", "four", "Five"};
  vector<string> keys3 = {"hello", "one-one", "two", "three", "four", "Five"};

  node.add_branch(keys1, 123l);
  node.print_m();
  node.add_branch(keys2, 456l);
  node.print_m();
  node.add_branch(keys3, 789l);
  node.print_m();




  return 0;
}