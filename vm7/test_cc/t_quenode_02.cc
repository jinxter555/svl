#include "../que_node.hh"

int main() {
  QueNode node;
  AstMap nil_map;

  cout << nil_map << "\n";


  vector<string> keys0 = {"bigbang"};

  vector<string> keys1 = {"hello", "one", "two"};
  vector<string> keys2 = {"hello", "one", "two", "three", "four", "Five"};

  vector<string> keys2b = {"hello", "one", "two"};
  vector<string> keys3 = {"hello", "one-one", "two", "three", "four", "Five"};
  vector<string> keys3b  = {"hello", "one-one", "two"};

  vector<string> d1 = {"world", "one-one", "two"};



  vector<string> vstr1 = {"svlvm", "readline", "commands", "svlm", "!!print_tree","svlvm","hello", "world"};
  vector<string> vstr1b = {"svlvm", "readline", "commands", "svlm", "!!print_tree","svlvm"};

  cout << "key blah: " << node.get_branch({"blah"}) << "\n\n";


  //node.add_branch(keys0, 55555l); node.print_m();
  node.add_branch(keys1, 123l); node.print_m(); cout << "\n\n";
  node.add_branch(keys2, 456l, true); node.print_m(); cout << "\n\n";

  auto &dv1 = node.get_branch({"hello"});
  cout << "dv1: " << dv1 << "\n";
  dv1.add(Operand("world"), 5555l);

  return 0;







  node.add_branch(vstr1, 8888l);
  //node.print_m();



  node.add_branch(keys3, 789l);
  node.print_m();

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