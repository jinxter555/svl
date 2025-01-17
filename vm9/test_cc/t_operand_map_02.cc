#include <cassert>
#include <catch2/catch_all.hpp>

#include "operand.hh"
#include "ast_map.hh"
#include "ast_list.hh"

#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"


TEST_CASE("check operand map 2") {
  trace_function.open("trace_svlm.log", std::ios::out);
  ScopeLogger::set_current_verbose_level(SLOG_FUNC_INFO + 21);

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
  AstMap m1, m2;

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

  m2.add("mundo2", 88888l, true);
  m2.add(AstList(vec_str_t{"hola3", "mundo3"}), 456l, true);
  cout << "m2: " << m2 << "\n";
  auto &v3 = m2[AstList(vec_str_t{"hola3", "mundo3"})];
  CHECK(v3._get_number() == 456l);

  m2.add("e", "ebay", true);
  CHECK(m2["e"]._to_str() == "ebay");
  cout << "m2: " << m2 << "\n";

  Operand m3(m2.clone());
  cout << "m3: " << m3 << "\n";
  CHECK(m3 == m2);
  //m3[AstList(vec_str_t{"hola3", "mundo3"})] = 5555l;
  m3[vec_str_t{"hola3", "mundo3"}] = 5555l;
  cout << "m2: " << m2 << "\n";
  cout << "m3: " << m3 << "\n";
  CHECK(m3 != m2);

  list_t lt1;
  lt1.push_back("hola4");
  lt1.push_back("mundo4");
  //m3[lt1] = 16668l;
  m3.add(lt1, 168l, true);
  cout << "m3: " << m3 << "\n";
  cout << "m3[lt1]: " <<  m3[lt1] << "\n";
  m3[lt1] = 16668l;
  cout << "m3: " << m3 << "\n";
  cout << "m3[lt1]: " <<  m3[lt1] << "\n";





  
}
