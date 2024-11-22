#include <vector>
#include "../ast_list.hh"
#include "../ast_map.hh"


int main() {
  AstMap m1;

  vector<string> k1= {"hello", "one", "two1"};
  vector<string> k2= {"hello", "one", "two2", "three", "four", "Five"};
  vector<string> k2b= {"hello", "one", "two3", "three", "four", "Five"};
  vector<string> k3= {"hello", "one-one", "hello"};
  vector<string> k3b= {"hello", "one-one", "hello", "one", "two1"};

  m1.add_branch(k1, 123l, true);
  m1.add_branch(k2, 456l, true);
  m1.add_branch(k2b, make_unique<Operand>(5555l), false);

  m1.add_branch(k2b, make_unique<Operand>(5555l), false);

  cout << "m1: " << m1 << "\n";

  auto rptr = m1.get_raw_ptr(string("hello"));
  cout << "rptr " <<  rptr << "\n";
  rptr->print();
  cout << "\n";
  m1.add_branch(k3, unique_ptr<AstExpr>(rptr) );
  // rptr->print();
  auto &rv = m1.get_branch(k3b);
  cout << "rv: " <<  rv<< "\n";



  cout << "\n";


  return 0;
}