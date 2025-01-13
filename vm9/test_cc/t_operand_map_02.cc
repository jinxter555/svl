#include <cassert>
#include <catch2/catch_all.hpp>

#include "operand.hh"
#include "ast_map.hh"
#include "ast_list.hh"

#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"


TEST_CASE("check operand map 2") {
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



  //Operand m2(make_unique<Operand>(t1));
  //Operand m2(t1);
  AstMap m2;
  m2["pi"] = 3.14159;
  m2["www1"] = "server1";
  cout << "m2: " << m2 << "\n";

  m2.add(string("e"), Operand(2.718), true);
  //CHECK(m2["e"]._to_str() == "2.718000");
  m2.add(AstList(vec_str_t{"hola", "mundo"}), Operand(3.14159).clone(), false);
  cout << "m2: " << m2 << "\n";
  auto &v1 = m2[AstList(vec_str_t{"hola", "mundo"})];

  cout << "v1: " << v1 << "\n";
  CHECK(v1._get_number() == 3.14159);

  m2.add(AstList(vec_str_t{"hola", "mundo"}), Operand("pi!").clone(), false);
  auto &v1b = m2[AstList(vec_str_t{"hola", "mundo"})];
  cout << "v1b: " << v1b << "\n";
  CHECK(v1._get_number() == 3.14159);


  m2.add(AstList(vec_str_t{"hola", "mundo"}), Operand("pi!").clone(), true);
  cout << "m2: " << m2 << "\n";
  auto &v2 = m2[AstList(vec_str_t{"hola", "mundo"})];
  cout << "v2: " << v2 << "\n";
  CHECK(v2._to_str() == "pi!");



/*
  m2.add("e", "ebay", true);
  CHECK(m2["e"]._to_str() == "2.718000");
  cout << "m2: " << m2 << "\n";

  m2.add("e", "ebay", true);
  CHECK(m2["e"]._to_str() == "ebay");
  cout << "m2: " << m2 << "\n";
*/




  
}
