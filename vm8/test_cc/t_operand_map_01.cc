#include <cassert>
#include <catch2/catch_all.hpp>

#include "operand.hh"

#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"


TEST_CASE("check operand list 1") {
  trace_function.open("trace_svlm.log", std::ios::out);
  ScopeLogger::set_current_verbose_level(SLOG_FUNC_INFO);

  MYLOGGER(trace_function, "TEST_CASE()", __func__, SLOG_FUNC_INFO);

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
  m1.add("hello4", 44l);
  m1.add("hello5", 7777l);
  m1.add("hello4", 888l, true);
  cout << "m1:" << m1 << "\n";
  cout << "m1[hello4]:" << m1[make_unique<Operand>("hello4")] << "\n";
  cout << "m1[123]:" << m1[make_unique<Operand>(123l)] << "\n";


  
}
