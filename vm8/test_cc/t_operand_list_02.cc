#include <cassert>
#include "operand.hh"

#include <catch2/catch_all.hpp>

#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"


TEST_CASE("check operand list 2") {
  trace_function.open("trace_svlm.log", std::ios::out);
  ScopeLogger::set_current_verbose_level(SLOG_FUNC_INFO + 20);


  //vector<Operand> l1 = {i1.clone(), f1.clone()};
  vector<Operand> l1, l2 ;
  l1.push_back(Operand(1l));
  l1.push_back(Operand(22l));
  l1.push_back(Operand("str3"));
  l1.push_back(Operand(44.44));
  l1.push_back(Operand(5.555));

  l2.push_back(Operand(1.2));
  l2.push_back(Operand(2.3));
  l2.push_back(Operand(3.4));

  Operand ol1(l1);
  ol1.add(l2);
  cout << "ol1: " << ol1 << "\n";
  Operand ol2(ol1.clone());
  cout << "ol2: " << ol2 << "\n\n";
  CHECK(ol1 == ol2);

  ol1[1l] = "twotwo";
  cout << "ol1: " << ol1 << "\n";
  cout << "ol2: " << ol2 << "\n\n";
  CHECK(ol1 != ol2);


  ol2[0l] = 111111l;
  ol2[1l] = "twotwo";
  cout << "ol1: " << ol1 << "\n";
  cout << "ol2: " << ol2 << "\n\n";

  //Operand k1(list_t{5l, 2l});
  Operand k1(list_t{});
  k1.add(1l);
  cout << "ol1[" << k1<< "]" << ol1[k1] << "\n";;
  CHECK(ol1[k1] == "twotwo");

  Operand k2(list_t{});
  k2.add(5l);
  k2.add(2l);
  cout << "ol1[" << k2<< "]" << ol1[k2] << "\n";;
  CHECK(ol1[k2] == 3.4);
  
}
