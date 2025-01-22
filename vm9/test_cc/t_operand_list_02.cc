#include <cassert>
#include "operand.hh"
#include "ast_list.hh"

#include <catch2/catch_all.hpp>

#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"


TEST_CASE("check operand list 2") {
  trace_function.open("trace_svlm.log", std::ios::out);
  ScopeLogger::set_current_verbose_level(SLOG_FUNC_INFO + 1);


  //vector<Operand> l1 = {i1.clone_operand(), f1.clone_operand()};
  vector<Operand> l1, l2 ;
  l1.push_back(Operand(1l));
  l1.push_back(Operand(22l));
  l1.push_back(Operand("str3"));
  l1.push_back(Operand(44.44));
  l1.push_back(Operand(5.555));

  l2.push_back(Operand(1.2));
  l2.push_back(Operand(2.3));
  l2.push_back(Operand(3.4));

  AstList ol1(l1);
  ol1.add(l2);
  cout << "ol1: " << ol1 << "\n";
  ol1[2l] = "twotwo";
  cout << "ol1: " << ol1 << "\n";

  auto &v = ol1[AstList(vec_num_t{5l,2l})];
  CHECK(v._get_number() == 3.40);
  cout << "v: " << v << "\n";
  cout << "\n";

  AstList ol2(l2);
  ol2.add(ol1.clone());
  ol2.add(3.14159);

  auto l3=make_unique<AstList>();
  l3->add(123l);
  l3->add(456l);
  l3->add(789l);
  l3->add(3.14159);
  cout << "l3: " << *l3<< "\n";


  cout << "ol2: " << ol2 << "\n";
}
