#include <cassert>
#include "../operand.hh"



int main() {
  Operand i1(11l);
  Operand i2(12l);
  Operand s1(string("str1"));
  Operand s2(string("str2"));
  Operand s3("str3");
  Operand s4("str4");
  Operand sh_i1(
    make_shared<Operand>(123456789l)
  );
  Operand nil;

  Operand v1 = 111l;

  Operand v2 = "hello";
  Operand v3;


  const Operand &r_v1 = v1.getv();
  Operand v1_b = v1.clone();
  cout << "v1: " << v1 << "\n";
  cout << "reference r_v1: " << r_v1 << "\n";
  cout << "v1 + 2: " << v1 + 2l<< "\n";
  cout << "reference r_v1: " << r_v1 + 2l << "\n";
  cout << "r_v1=555 \n"; //r_v1 = 555l;
  cout << "v1: " << v1 << "\n";
  cout << "reference r_v1: " << r_v1 << "\n";
  cout << "v1 + 2: " << v1 + 2l<< "\n";
  cout << "reference r_v1: " << r_v1 + 2l << "\n\n";

  auto u_p1 = make_unique<Operand>(111l);
  cout << "u_p1: " << *u_p1 << "\n";
  cout << "before getv() u_p1: " << *u_p1 << "\n";
  {
    auto &r_p1  = u_p1->getv();
    //r_p1 = 222l;
  }
  cout << "after getv() u_p1: " << *u_p1 << "\n";
  cout << "\n";

  cout << i1 + i2 << "\n";
  cout << s1 + s2 << "\n";
  cout << s3 + s4 << "\n";
  cout << nil << "\n";
  cout << i1 + s4 << "\n";

  cout << "i1: " << i1 << "\n";
  cout << "i1.getv(): " << i1.getv() << "\n";

  Operand oc1(AstOpCode::mul);
  cout << "oc1: " <<  oc1  << "\n";
  cout << "oc1: " <<  oc1.get_opcode()  << "\n";

  cout << "shared sh_i1: " <<  sh_i1 << "\n";
  cout << "shared sh_i1 + i1: " <<  sh_i1 + i1 << "\n";
  cout << "shared sh_i1.getv() + i1: " <<  sh_i1.getv() + i1 << "\n";


  return 0;
}
