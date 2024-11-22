#include <cassert>
#include <vector>
#include "../ast_list.hh"
#include "../ast_map.hh"


int main() {
  AstMap m1;

  vector<string> k1= {"hello", "one", "two"};
  vector<string> k2= {"hello", "one", "two", "three", "four", "Five"};
  vector<string> k2b= {"hello", "one", "two2", "three", "four", "Five"};

  m1.add_branch(k1, 123l, true);
  m1.print(); cout << "\n\n";

  auto& v1 = m1.get_branch(k1);
  cout << "v1: " << v1 <<  " " << v1.get_type() << "\n";

  m1.add_branch(k2, 456l, true);
  m1.add_branch(k2b, make_unique<Operand>(5555l), false);


  auto& v2 = m1.get_branch(k2);
  v2.print();
  cout << "\nv2: " << v2 <<  "\n";
  cout << "v2 type: " << v2.get_type() << "\n";
  assert(v2 == 456l);


  auto& v2b = m1.get_branch(k2b);
  cout << "\nv2b: " << v2b <<  "\n";

  auto& v3 = m1.get_branch({"hello", "one"});
  cout << "\nv3: " << v3.get_type() << ":" << v3 <<  "\n";



  auto& v1b = m1.get_branch(k1);
  cout << "\nv1b: " << v1b <<  " " << v1b.get_type() << "\n";
//  v1b.add(Operand("three3"), Operand(333l));
  v1b.add_branch({"three-three", "four", "five"}, Operand(333l));

  cout << "\n";
  cout << "m1: " << m1.get_type() << " " << m1 << "\n";
  cout << "\n";



  return 0;
}