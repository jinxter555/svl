#include "../ast_list.hh"
#include "../ast_map.hh"


int main() {
  Operand i1(1l);
  Operand i2(2l);
  Operand i3(3l);

  Operand one("one");
  Operand two("two");
  Operand three("three");
  Operand opstr("op");
  Operand op(AstOpCode::plus);
  Operand l("left");
  Operand r("right");

  AstMap m1, m2, mr;
  
  m1.add(one, i1);
  m1.add(two, i2);
  m1.add(three, i3);
  m1.add(l, i1);
  m1.add(r, i2);
  m1.add(opstr, op);

  auto &v1 = m1[one];
  cout << "v1: " << v1 << "\n";

  m1[one] = Operand("world555l");
  //m1.set(one, one);
  cout << "v1: " << v1 << "\n";
  m1[one] = 555l;
  cout << "m1[one] " << m1[one] << "\n";
  const Operand &v2 = m1[two];
  cout << "v2: " << v2 << "\n";
  cout << "m1[two]: " << m1[two]<< "\n";
  cout << "op: " << op << "\n";
  cout << "op: getopcode: " << op.get_opcode() << "\n";
  cout << "m1[opstr]: " << m1[opstr]<< "\n";
  cout << "m1[opstr]:get_Opcode " << m1[opstr].get_opcode() << "\n";





  return 0;
}