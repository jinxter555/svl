#include <cassert>
#include "operand.hh"

#include <catch2/catch_all.hpp>

#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"


TEST_CASE("check operand list 1") {
  trace_function.open("trace_svlm.log", std::ios::out);
  ScopeLogger::set_current_verbose_level(SLOG_FUNC_INFO + 20);

  Operand i1(123l);
  CHECK(i1._get_number() == 123l);

  Operand f1(12.3450);
  CHECK(f1._get_number() == Number(12.3450) );


  Operand u_i1(make_unique<Operand>(555l));
  CHECK(u_i1._get_number() == 555l);

  //vector<Operand> l1 = {i1.clone(), f1.clone()};
  vector<Operand> l1 ;
  l1.push_back(Operand(1l));
  l1.push_back(Operand(22l));
  l1.push_back(Operand(333l));

  Operand ol1(l1);
  cout << "ol1: " << ol1 << "\n";
  cout << "ol1[0]: " << ol1[0l] << "\n";
  cout << "ol1[1]: " << ol1[1l] << "\n";
  cout << "ol1[2]: " << ol1[2l] << "\n";
  cout << "ol1[2]: " << ol1[make_unique<Operand>(2l)] << "\n";

  auto &lc = ol1._get_list();
  auto ld = Operand(lc);
  cout << "ld<-clone()<-lc<-ol1: " << ld << "\n";
  CHECK(ld == ol1);
  if(ld == ol1) { cout << "ld == ol1\n"; }
  else cout << "ld != ol1\n\n";


  cout << "lc<-ol1: " << lc << "\n";
  ol1[1l]= f1.clone();
  ld[1l] = 555555l;
  cout << " lc: " << lc << "\n";
  cout << "ol1: " << ol1 << "\n";
  cout << " ld: " << ld << "\n";
  CHECK(ld != ol1);
  if(ld == ol1) { cout << "ld == ol1\n"; }
  else cout << "ld != ol1\n";

  Operand le(ld.clone_list());
  cout << " le<-ld.clone_list():\n";
  CHECK(le == ld);
  if(le == ld) { cout << "le == ld\n"; }
  else { cout << "le != ld\n"; }




  return ;






  
}
