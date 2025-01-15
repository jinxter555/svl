#include <cassert>
#include "operand.hh"
#include "ast_list.hh"

#include <catch2/catch_all.hpp>

#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"

#include "operand_vars.hh"



TEST_CASE("check operand list 1") {
  trace_function.open("trace_svlm.log", std::ios::out);
  ScopeLogger::set_current_verbose_level(SLOG_FUNC_INFO + 20);

  Operand i1(123l);
  CHECK(i1._get_number() == 123l);

  Operand f1(12.3450);
  CHECK(f1._get_number() == Number(12.3450) );


  Operand u_i1(make_unique<Operand>(555l));
  CHECK(u_i1._get_number() == 555l);

  //if(nil_operand == nil_operand) { cout << "nil operand=";}
  Operand a(nil);

  //vector<Operand> l1 = {i1.clone_operand(), f1.clone()};
  vector<Operand> l1 ;
  l1.push_back(Operand(1l));
  l1.push_back(Operand(22l));
  l1.push_back(Operand(333l));

  if(i_var == 123) { cout << "ivar123\n"; }
  Operand ol1(l1);
  cout << "ol1: " << ol1 << "\n";
  cout << "ol1[0]: " << ol1[0l] << "\n";
  cout << "ol1[1]: " << ol1[1l] << "\n";
  cout << "ol1[2]: " << ol1[2l] << "\n";
  auto &L1 = ol1.get_list();
  auto &l1b = L1._get_list();
  cout << "ol1.get_list(): " << L1 << "\n\n";
  auto rb = (L1==ol1);
  auto rb2 = L1.cmp_eql(ol1);
  if(rb) {cout << "rb, L1==ol1\n"; }
  if(rb2) {cout << "rb2, L1==ol1\n"; }
  //CHECK(L1== ol1);

  Operand ol2(ol1.clone());
  auto ol2_ptr = ol2.get_list_ptr();
  cout << "*ol2_ptr: " << *ol2_ptr << "\n";
  cout << "ol2_ptr.gettype: " << ol2_ptr->get_type() << "\n";
  CHECK(ol2_ptr->_get_type()== OperandType::list_t);


/*
  cout << "ol1[2]: " << ol1[make_unique<Operand>(2l)] << "\n";

  auto &lc = ol1._get_list();
  auto ld = Operand(lc);
  cout << "ld<-clone_operand()<-lc<-ol1: " << ld << "\n";
  CHECK(ld == ol1);
  if(ld == ol1) { cout << "ld == ol1\n"; }
  else cout << "ld != ol1\n\n";


  cout << "lc<-ol1: " << lc << "\n";
  ol1[1l]= f1.clone_operand();
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

  Operand ol2(ol1.clone_operand());
  cout << "ol1: " << ol1 << "\n";
  cout << "ol2: " << ol2 << "\n";
  cout << "ol2.getype(): " << ol2.get_type() << "\n";
  ol2[1l] = 55555l;
  cout << "ol2: " << ol2 << "\n";
  CHECK(ol1!= ol2);


  vec_num_t num_list_1 = {1l,2l,3l};
  //vec_num_t num_list_2 = {1l, 2.2f, 3.1415f};
  Operand num_list_ov1(num_list_1);
  Operand num_list_ov2(vec_num_t{1l, 2.2f, 3.1415f});
  cout << "num_list_ov1: " <<  num_list_ov1 << "\n";
  cout << "num_list_ov2: " <<  num_list_ov2 << "\n";

  vec_str_t str_list_1 = {"str1", "hello1", "www1"};
  Operand str_list_ov1(str_list_1);
  Operand str_list_ov2(vec_str_t{"peppa", "pig", "language", "exchange"});
  cout << "str_list_ov1: " <<  str_list_ov1 << "\n";
  cout << "str_list_ov2: " <<  str_list_ov2 << "\n";
*/
}
