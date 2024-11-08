#include <vector>
#include "../ast_list.hh"
#include "../ast_map.hh"


int main() {
  AstMap m1;

  vector<string> k1= {"hello", "one", "two"};
  vector<string> k2= {"hello", "one", "two", "three", "four", "Five"};
  vector<string> k2b= {"hello", "one", "two2", "three", "four", "Five"};

  m1.add_branch(k1, 123l);
  m1.print();
  m1.add_branch(k2, 456l, false);
  m1.add_branch(k2b, 456l, false);
  m1.print();
  cout << "\n";


  return 0;
}