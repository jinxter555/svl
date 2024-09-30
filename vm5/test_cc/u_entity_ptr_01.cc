#include "../entity.hh"
#include "../operand_entity.hh"

ostream& operator<<(ostream& os, const OperandType& t);

int main() {
  OperandEntity n1(123);
  OperandEntity i1(Operand(11)) ;
  OperandEntity i2(22) ;
  OperandEntity i3(33) ;

  OperandEntity s1("hello");
  OperandEntity s2(string("world"));

  entity_u_ptr o_ptr1 = make_unique<OperandEntity>(s1);
  entity_u_ptr l_ptr1 = make_unique<ListEntity>();
  cout << "*o_ptr1: "  << *o_ptr1 << "\n";
  l_ptr1->add(n1);
  l_ptr1->add(i1);
  l_ptr1->add(s1);
  l_ptr1->add(s2);
  cout << "\n";
  cout << "*l_ptr1: "  << *l_ptr1 << "\n";







  return 0;
}