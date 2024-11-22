#include <cassert>
#include "../operand.hh"

int main() {
  Operand i1(11l);
  Operand i1c(i1.clone());
  Operand i1d(Operand().clone());
  Operand i2(12l);
  Operand s1(string("str1"));
  Operand s2(string("str2"));
  Operand s3("str3");
  Operand s4("str4");
  Operand nil;

  const Operand &oref= i1.getv();
  auto oref1 = oref.clone_val();
  auto oref1b = oref.clone();


  cout << i1 + i2 << "\n";
  cout << s1 + s2 << "\n";
  cout << s3 + s4 << "\n";
  cout << nil << "\n";
  cout << i1 + s4 << "\n";

  oref1 = oref1 + 12345l;
  cout << "i1: " << i1 << "\n";
  cout << "i1.getv(): " << i1.getv() << "\n";
  cout << "i1c: " << i1c << "\n";
  cout << "i1c.getv(): " << i1c.getv() << "\n";
  assert(i1c.getv() == 11l);
  cout << "i1d.getv() is nil: " << i1d.getv() << "\n";
  assert(i1d.getv() == nil_operand);
  cout << "oref1: " << oref1<< "\n";
  cout << "oref1 type: " << oref1.get_type()<< "\n";
  cout << "oref1b : " << oref1b<< "\n";
  cout << "oref1b type : " << oref1b->get_type() << "\n";

  Operand oc1(AstOpCode::mul);
  cout << "oc1: " <<  oc1  << "\n";
  cout << "oc1: " <<  oc1.get_opcode()  << "\n";
  //Operand oc2() = oc1._get_opcode();


  return 0;
}