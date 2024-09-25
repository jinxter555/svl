#include "../entity.hh"

ostream& operator<<(ostream& os, const OperandType& t);

int main() {
  Entity s1(string("hello")) ;
  Entity s2(string("world")) ;
  cout << "s1:" << s1 << "\n";
  Entity list1(OperandType::list_t);
  Entity list2(OperandType::list_t);

  return 0;
}