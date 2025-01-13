#include <cassert>
#include "operand.hh"

#include <catch2/catch_all.hpp>


TEST_CASE("check operand 1") {
  Operand i1(123l);
  //CHECK(i1._get_number() == 123l);

  Operand f1(12.3450);
  CHECK(f1._get_number() == Number(12.3450) );
  Operand u_f1(f1.clone());
  CHECK(f1._get_number() == u_f1._get_number());
  CHECK(u_f1._get_number() == 12.3450);

  Operand s1(string("str1"));
  CHECK(s1._to_str() == "str1");

  astnode_u_ptr ptr = make_unique<Operand>(555l);
  Operand u_i1(move(ptr));
  Operand u_i2(make_unique<Operand>(6666l));
  CHECK(u_i1._get_number() == 555l);

  Operand v1=123l;
  Operand v2=v1.clone();

  operand_variant_t ov1 = 123l;
  cout << "ov1 " << ov1 << "\n";
  cout << "ov1.getnu " << get<Number>(ov1) << "\n";


  //Operand op1(AstOpCode::plus);
  //CHECK(op1._get_opcode() == AstOpCode::plus);
  
}
