#include "../entity.hh"


int main() {
  OperandEntity n1(123l);
  cout << "i1:" << n1 << "\n";
  cout << "i1 whatami:" << n1._get_operand().whatami() << "\n";

  OperandEntity s1("hello");
  cout << "s1:" << s1 << "\n";
  cout << "s1:" << s1._get_operand().whatami() << "\n";


  OperandEntity s2(string("hello,world"));
  OperandEntity i1(Operand(11l)) ;
  OperandEntity i2(22l) ;
  OperandEntity i3(33l) ;
  OperandEntity f1(12.345) ;
  entity_u_ptr f1_c  = f1.clone();
  Operand f1_o = f1._get_operand();
  OperandEntity i5 ;
  OperandEntity i4 = i2.opfunc(i3, AstOpCode::plus);

  //i5.set( i4 + i1);
  i5 = i4.opfunc(i1, AstOpCode::plus);

  OperandEntity s3 = s2.to_str();


  cout << "s1:" << s1 << "\n";
  cout << "s1 geto:" << s1._get_operand() << "\n";
  cout << "s1 gettype:" << s1.get_type() << "\n";
  cout << "s2:" << s2 << "\n";
  cout << "s2 geto:" << s2._get_operand() << "\n";
  cout << "s3:" << s3 << "\n";

  cout << "i1:" << i1 << "\n";
  cout << "i2:" << i2 << "\n";
  cout << "f1:" << f1 << "\n";
  cout << "f1 gettype:" << f1.get_type() << "\n";
  cout << "f1_o:" << f1_o << "\n";
  cout << "f1_c:" << f1_c << "\n";
  cout << "i4:" << i4 << "\n";
  cout << "i5:" << i5 << "\n";

  return 0;
}