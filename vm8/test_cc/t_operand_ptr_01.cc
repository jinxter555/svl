#include <cassert>
#include "../operand.hh"

int main() {
  Operand i_nil_a(nil);
  Operand i_nil_b( make_unique<Operand>(nil));

  Operand i1_a( 123l);
  Operand i1_b( make_unique<Operand>(123l));

  Operand i3_a( 333l);
  Operand i3_b( make_unique<Operand>(333l));

  cout << "i1_a: " << i1_a << "\n";
  cout << "i1_a.getv(): " << i1_a.getv() << "\n";
  cout << "i1_a.Operand(_get_value()): " << Operand(i1_a._get_value()) << "\n\n";

  cout << "i1_b: " << i1_b << "\n";
  cout << "i1_b.getv(): " << i1_b.getv() << "\n";
  cout << "i1_b.Operand(_get_value()): " << Operand(i1_b._get_value()) << "\n\n";

  cout << "i1_a==i1_b: " << Operand(i1_a == i1_b) << "\n\n";

  cout << "i3_a: " << i3_a << "\n";
  cout << "i1_a==i3_a: " << Operand(i1_a == i3_a) << "\n\n";
  cout << Operand(i1_a == i3_a) << "\n";

  cout << "i3_b: " << i3_a << "\n";
  cout << "i1_a==i3_b: " << Operand(i1_a == i3_b) << "\n\n";
  cout << Operand(i1_a == i3_b) << "\n";
  auto bv = i1_a == i3_b;
  cout << "i_nil_a: " << i_nil_a << "\n";
  cout << "i_nil_a==i_nil_a: " << Operand(i_nil_a== i_nil_a) << "\n\n";
  cout << Operand(i_nil_a == i_nil_a) << "\n";

  cout << "\n";
}