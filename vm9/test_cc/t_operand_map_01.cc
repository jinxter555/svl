#include <cassert>
#include <catch2/catch_all.hpp>

#include "operand.hh"
#include "ast_map.hh"

#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"


TEST_CASE("check operand map 1") {
  trace_function.open("trace_svlm.log", std::ios::out);
  ScopeLogger::set_current_verbose_level(SLOG_FUNC_INFO+29);

  MYLOGGER(trace_function, "TEST_CASE()", __func__, SLOG_FUNC_INFO);

  Operand i1(123l);
  Operand f1(12.3450);

  //Operand s1(string("str1"));
  //Operand s2(string("str2"));

  map_t t1;

  t1["hello1"] = 1l;
  t1["hello2"] = 22l;
  t1["hello3"] = i1.clone();
  t1["hello3"] = 333l;
  CHECK(t1["hello2"]._to_str() == "22");
  //cout << "t1:" << t1 << "\n";


  AstMap m1(t1);
  cout << "m1:" << m1 << "\n";
  m1[static_cast<string>("hello4")] = 4444l;
  m1["hello5"] = 5555l;
  cout << "m1:" << m1 << "\n";
  auto &v4 = m1["hello4"];
  cout << "m1[hello4]:" << v4 << "\n";
  auto &v5 = m1["hello5"];
  const auto &v6 = m1["hello6"];
  cout << "m1[hello5]:" << v5 << "\n";
  cout << "m1[hello6]:" << v6 << "\n";
  v5=51111l;
  cout << "m1:" << m1 << "\n";
  return ;



  CHECK(m1["hello4"]._to_str() == "6666");

  return ;


  cout << "m1:" << m1 << "\n";
  m1[123l] = 777l;
  Operand m2(m1.clone());

  cout << "m1[123]:" << m1[123l] << "\n\n";
  cout << "m1: " << m1 << "\n";
  cout << "m2: " << m2 << "\n";
  CHECK(m1 == m2);
  m2["hello4"] = 6665l;
  CHECK(m1 != m2);


  
}
