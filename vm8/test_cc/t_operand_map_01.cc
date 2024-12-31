#include <cassert>
#include "operand.hh"

#include <catch2/catch_all.hpp>


TEST_CASE("check operand list 1") {
  Operand i1(123l);
  Operand f1(12.3450);

  Operand s1(string("str1"));
  Operand s2(string("str2"));

  map_t t1;
  t1["hello1"] = 111l;
  t1["hello2"] = 555l;
  t1["hello3"] = i1.clone();


  Operand m1(t1);
  cout << "t1:" << t1 << "\n";
  cout << "m1:" << m1 << "\n";
  m1["hello3"] = f1.clone();
  m1["hello4"] = 6666l;
  cout << "m1:" << m1 << "\n";


  
}
