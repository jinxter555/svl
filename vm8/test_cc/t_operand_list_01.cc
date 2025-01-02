#include <cassert>
#include "operand.hh"

#include <catch2/catch_all.hpp>


TEST_CASE("check operand list 1") {
  Operand i1(123l);
  CHECK(i1._get_number() == 123l);

  Operand f1(12.3450);
  CHECK(f1._get_number() == Number(12.3450) );

  Operand s1(string("str1"));
  CHECK(s1._to_str() == "str1");

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
  cout << "lc<-ol1: " << lc << "\n";
  ol1[1l]= 3.14159;
  ld[1l] = 555555l;
  cout << " lc: " << lc << "\n";
  cout << "ol1: " << ol1 << "\n";
  cout << " l1: " << l1 << "\n";
  cout << " ld<-clone(lc): " << ld << "\n";


  l1.push_back(Operand(3l));
  Operand ol2(l1);
  cout << "ol2: " << ol2 << "\n";
  Operand ol3(move(ol1.clone_list()));
  cout << "ol3: " << ol3 << "\n";
  Operand ol4(move(i1.clone_list()));
  cout << "ol4: " << ol4 << "\n";

  Operand ol5(move(ol3.clone_list()));
  ol5.add("hello");
  ol5.add(5555l);
  ol5.add(12.345);
  cout << "ol5<-ol3: " << ol5 << "\n";
  cout << "ol3: " << ol3 << "\n";

  Operand ol6;
  ol6.add(i1);
  ol6.add(ol1);
  ol6.add(ol5);
  cout << "ol6: " << ol6 << "\n";

  Operand ol7(123l);
  CHECK(ol7.add(ol5) == false);
  cout << "ol7: " << ol7 << "\n";

  ol1[1l] = 5555l;
  cout << "ol1: " << ol1 << "\n";
  cout << "l1: " << l1 << "\n";
  Operand ol8(move(l1));
  cout << "l1: " << l1 << "\n";
  cout << "ol8: " << ol8 << "\n";






  
}
