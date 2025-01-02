#include <cassert>
#include "number.hh"
#include "operand.hh"

#include <catch2/catch_all.hpp>

#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"


TEST_CASE("check operand value 1") {

  trace_function.open("trace_svlm.log", std::ios::out);
  ScopeLogger::set_current_verbose_level(SLOG_FUNC_INFO + 20);

  MYLOGGER(trace_function, "TEST_CASE()", __func__, SLOG_FUNC_INFO);

  Operand i1(123l);
  CHECK(i1._get_number() == 123l);

  //auto &i1_v =  i1.get_value();
  //CHECK(i1_v._get_number() == 123l);

  Operand f1(12.3450);
  CHECK(f1._get_number() == Number(12.3450) );

  Operand s1(string("str1"));
  CHECK(s1._to_str() == "str1");

  Operand u_i1(make_unique<Operand>(555l));
  CHECK(u_i1._get_number() == 555l);

  //Operand ptr1(make_unique<Operand>(123l));
  Operand ptr1(make_unique<Operand>(
    make_shared<Operand>( 123l)
  ));
  auto &i1_pv =  ptr1.get_value();
  //cout << "i1_pv.gettype():" << i1_pv.get_type() << "\n";
  CHECK(i1_pv._get_number() == Number(123l));
  CHECK(i1_pv._get_number() == i1._get_number());
  CHECK(ptr1._get_number() == Number(123l));
  CHECK(ptr1.get_value() == i1.get_value());

  auto vrptr = ptr1._vrptr();
  cout << "ptr1: " << &ptr1 << "\n";
  cout << "vrptr: " << vrptr << "\n";
  cout << "*vptr: " << *vrptr << "\n";
  cout << "*vptr.getypte(): " << (*vrptr).get_type() << "\n";

  
}
