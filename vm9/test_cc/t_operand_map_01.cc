#include <cassert>
#include <catch2/catch_all.hpp>

#include "operand.hh"
#include "ast_map.hh"

#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"


TEST_CASE("check operand map 1") {
  trace_function.open("trace_svlm.log", std::ios::out);
  ScopeLogger::set_current_verbose_level(SLOG_FUNC_INFO+9);

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


  MYLOGGER_MSG(trace_function,  string("step 1") ,  SLOG_FUNC_INFO);
  AstMap m1(t1);
  MYLOGGER_MSG(trace_function,  string("step 2") ,  SLOG_FUNC_INFO);
  cout << "m1:" << m1 << "\n";

  MYLOGGER_MSG(trace_function,  string("step 3") ,  SLOG_FUNC_INFO);
  m1["hello4"] = 6666l;

  CHECK(m1["hello4"]._to_str() == "6666");

  cout << "m1:" << m1 << "\n";
  m1[123l] = 777l;

  cout << "m1[123]:" << m1[123l] << "\n\n";
  cout << "m1:" << m1 << "\n";


  
}
