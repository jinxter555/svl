#include <vector>
#include "../ast_list.hh"
#include "../ast_map.hh"


int main() {
  AstMap m1;

  vector<string> k1= {"hello", "one", "two"};
  vector<string> k2= {"hello", "one", "two", "three", "four", "Five"};
  vector<string> k2b= {"hello", "one", "two2", "three", "four", "Five"};

  m1.add_branch(k1, 123l, true);
  m1.print();
  auto& v1 = m1.get_branch(k1);
  cout << "\nv1: " << v1 <<  "\n";
  m1.add_branch(k2, 456l, false);
  m1.add_branch(k2b, 456l, false);
  auto& v2 = m1.get_branch(k2);
  v2.print();
  cout << "\nv2: " << v2 <<  "\n";
  cout << "v2 type: " << v2.get_type() << "\n";

  auto& v2b = m1.get_branch(k2b);
  cout << "\nv2b: " << v2b <<  "\n";

  cout << "m1: " << m1 << "\n";
  cout << "\n";


  return 0;
}