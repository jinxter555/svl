#include <cassert>
#include "../que_node.hh"

int main() {
  QueNode node;
  AstMap nil_map, m1;


  vector<string> keys0 = {"bigbang"};

  node.add_branch(keys0, 55555l);
  auto &n0 = node.get_branch(keys0);
  assert(n0 == 55555l);
  n0.print(); cout <<"\n\n";



  //vector<string> keys1 = {"hello"};
  vector<string> keys1 =  {"hello", "one", "two", "three"};
  vector<string> keys1b = {"hello", "one", "two", "three", "four", "Five"};
  node.add_branch(keys1b, 123l);
  auto &n1 = node.get_branch(keys1);
  n1.print(); cout <<"\n\n";

  auto &n1b = node.get_branch(keys1b);
  n1b.print(); cout <<"\n\n";

  return 0;

  vector<string> keys2 = {"hello", "one", "two", "three", "four", "Five"};
  vector<string> keys2b = {"hello", "one", "two"};
  vector<string> keys3 = {"hello", "one-one", "two", "three", "four", "Five"};
  vector<string> keys3b  = {"hello", "one-one", "two"};

  vector<string> vstr1 = {"svlvm", "readline", "commands", "svlm", "!!print_tree","svlvm","hello", "world"};
  vector<string> vstr1b = {"svlvm", "readline", "commands", "svlm", "!!print_tree","svlvm"};

  cout << "key blah: " << node.get_branch({"blah"}) << "\n\n";


  m1.add_branch(keys0, 55555l);

  cout << "node : " << node << "\n";
  cout << "m1 : " << m1 << "\n";
  cout << "\n";

  node.AstList::add(Operand("hello1111"));
  node.AstList::add(Operand("world1111"));
  m1.add_branch(keys1, 123l);

  cout << "node : " << node << "\n";
  cout << "m1 : " << m1 << "\n";
  cout << "\n";
  return 0;

  node.print_m();
  node.add_branch(keys2, 666l);
  m1.add_branch(keys2, 666l);
  node.print();
  m1.print();
  cout << "\n";

  node.add_branch(keys2, 456l, true);
  node.add_branch(vstr1, 8888l);
  //node.print_m();



  node.add_branch(keys3, 789l);
  node.print_m();
  cout << "\n";

  auto &ov0 = node.get_branch(keys0);
  cout << "ov0: " << ov0 << "\n";

  auto &ov1 = node.get_branch(keys1);
  cout << "ov1: " << ov1 << "\n";

  auto &ov2 = node.get_branch(keys2);
  cout << "ov2: " << ov2 << "\n";

  auto &ov2b = node.get_branch(keys2b);
  cout << "ov2b: " << ov2b << "\n";


  auto &ov3 = node.get_branch(keys3);
  cout << "ov3: " << ov3 << "\n";

  auto &ov3b = node.get_branch(keys3b);
  cout << "ov3b: " << ov3b << "\n";

  auto &ov4 = node.get_branch(vstr1);
  cout << "ov4: " << ov4 << "\n";

  auto &ov5 = node.get_branch(vstr1b);
  cout << "ov5: " << ov5 << "\n";
  cout << "ov5 getkeys: ";
  auto keys = ov5._get_keys() ;
  std::cout << "one keys: "; for(auto k: keys) { std::cout << k << ","; } std::cout << "\n\n";






  return 0;
}