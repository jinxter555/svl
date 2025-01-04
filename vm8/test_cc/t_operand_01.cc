#include <cassert>
#include "operand.hh"

#include <catch2/catch_all.hpp>


TEST_CASE("check operand 1") {
  Operand i1(123l);
  CHECK(i1._get_number() == 123l);

  Operand f1(12.3450);
  CHECK(f1._get_number() == Number(12.3450) );

  Operand s1(string("str1"));
  CHECK(s1._to_str() == "str1");

  Operand u_i1(make_unique<Operand>(555l));
  CHECK(u_i1._get_number() == 555l);

  auto ctxt = i1.clone();
  cout << "s1.evaluate: " << s1.evaluate(ctxt) << "\n";
  CHECK(s1.evaluate(ctxt) == "str1");
  
}
