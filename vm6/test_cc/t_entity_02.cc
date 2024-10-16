#include "../ast.hh"


int main() {
  Operand n1(123l);
  Operand i1(Operand(11l)) ;
  cout << "n1:" << n1 << "\n";
  cout << "n1 whatami:" << n1.whatami() << "\n";

  Operand s1("hello");
  cout << "s1: " << s1 << "\n";
  cout << "s1: whatami() " << s1.whatami() << "\n";
  cout << "s1: gettype() " << s1.get_type() << "\n";


  Operand s2(string("hello,world"));
  Operand i2(22l) ;
  Operand i3(33l) ;
  Operand f1(12.345) ;
  Operand f1_c  = f1.clone_val();
  Operand f1_o = f1.clone_val();
  Operand i5 ;
  Operand i4 = i2.opfunc(i3, AstOpCode::plus);

  //i5.set( i4 + i1);
  i5 = i4.opfunc(i1, AstOpCode::plus);
  //i5 = Operand(555l);

  Operand s3 = s2.to_str();


  cout << "s1:" << s1 << "\n";
  cout << "s1 geto:" << s1.clone_val() << "\n";
  cout << "s1 gettype:" << s1.get_type() << "\n";
  cout << "s2:" << s2 << "\n";
  cout << "s2 geto:" << s2.clone_val() << "\n";
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