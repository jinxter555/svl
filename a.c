#include <iostream>
class A {
  protected:
    int v;
};

class B : A {
public:
  void f1() { A::v=2; }
  int v() {return A::v; }
};

int main() {
  B b1;
  b1.f1();
  std::cout << b1.v() << "\n";

  return 0;
}
