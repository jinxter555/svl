#include <cassert>
#include <catch2/catch_all.hpp>

#include "operand.hh"

#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"


TEST_CASE("check operand map 3 with tree like structure ") {
  trace_function.open("trace_svlm.log", std::ios::out);
  ScopeLogger::set_current_verbose_level(SLOG_FUNC_INFO + 10);

  MYLOGGER(trace_function, "TEST_CASE()", __func__, SLOG_FUNC_INFO);

  Operand i1(123l);
  Operand f1(12.3450);

  Operand s1(string("str1"));
  Operand s2(string("str2"));

  map_t t1;
  t1["hello1"] = 111l;
  t1["hello2"] = 555l;
  t1["hello3"] = i1.clone();
  CHECK(t1["hello2"]._to_str() == "555");



  Operand m2(make_unique<Operand>(t1));
  //Operand m2(t1);
  m2["pi"] = 3.14159;
  m2["www1"] = "server1";


  cout << "m2: " << m2 << "\n";
  m2.add("e", 2.718, true);
  CHECK(m2["e"]._to_str() == "2.718000");
  cout << "m2: " << m2 << "\n";
  m2.add("e", "ebay", false);
  CHECK(m2["e"]._to_str() == "2.718000");
  cout << "m2: " << m2 << "\n";
  m2.add("e", "ebay", true);
  CHECK(m2["e"]._to_str() == "ebay");


  Operand tm1(map_t {});
  tm1.add("s1", t1 );
  tm1.add("s2", m2 );

  cout << "tm1: " << tm1 << "\n";
  Operand k1(list_t {});
  k1.add("s1");
  k1.add("hello2");
  cout << "tm1[" << k1 <<"]: " << tm1[k1] << "\n";
  Operand k2(list_t {});
  k2.add("s2");
  k2.add("e");
  cout << "tm1[" << k2 <<"]: " << tm1[k2] << "\n";
  CHECK(tm1[k2]._to_str() == "ebay");

  

  
}
