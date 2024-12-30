#include <cassert>
#include "operand.hh"

#include <catch2/catch_all.hpp>


TEST_CASE("check operand list 1") {
  Operand i1(123l);
  CHECK(i1._get_number() == 123l);

  Operand f1(12.3450);
  CHECK(f1._get_number() == Number(12.3450) );

  Operand s1(string("str1"));
  CHECK(s1._to_str() == "str1");

  Operand u_i1(make_unique<Operand>(555l));
  CHECK(u_i1._get_number() == 555l);

  //vector<Operand> l1 = {i1.clone(), f1.clone()};
  vector<Operand> l1 ;
  l1.push_back(Operand(1l));
  l1.push_back(Operand(2l));

  Operand ol1(l1);
  cout << "ol1: " << ol1 << "\n";
  l1.push_back(Operand(3l));
  Operand ol2(l1);
  cout << "ol2: " << ol2 << "\n";
  cout << "ol1: " << ol1 << "\n";

  
}
