#include <any>
#include <iostream>
#include <vector>
#include "../tuple.hh"
#include "../operand.hh"


using namespace std;
 
int main()
{
    cout << boolalpha;
    cout << "\n";

    any a = 1;

  Operand ov1(11);
  Operand ov2(12);
  Operand ov3(13);
  std::vector ovv = {ov1, ov2, ov3};
  Tuple t1(ovv);
  t1.print();
  std::cout << "tuple assign any\n"; 
  std::any  el = std::any(t1);
  std::cout << "tuple fin any\n"; 
  Tuple t2 = any_cast<Tuple>(el);
  Tuple t3(t1);
  t2.print();
  t3.print();




    any a2 = t1;
    Tuple t1a = any_cast<Tuple>(a2);
    t1a.print();
    cout << a.type().name() << ": " << any_cast<int>(a) << "\n";
    a = 3.14;
    cout << a.type().name() << ": " << any_cast<double>(a) << "\n";
    a = true;
    cout << a.type().name() << ": " << any_cast<bool>(a) << "\n";
    cout << "\n";

    try {
      a = 1;
      cout << std::any_cast<float>(a) << '\n';
    } catch(const bad_any_cast &e) {
      cout << e.what() << "\n";
    }
    a =2 ;
    if(a.has_value()) {
      cout << a.type().name() << ": " << any_cast<int>(a) << "\n";
    }

    a.reset();
    if (!a.has_value()) {
        std::cout << "no value\n";
    }

    a = 3;
    int *i = any_cast<int>(&a);
    cout << *i << "\n";
    cout << "\n";

}
