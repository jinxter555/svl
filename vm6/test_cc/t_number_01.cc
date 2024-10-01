#include "../number.hh"


int main() {
  Number n1(123);
  Number f1(123.3456);
  double f2= 123.3456;

  cout << "n1: " << n1.to_str() << "\n";
  cout << "f1: " << f1.to_str() << "\n";
  cout << "f2: " << f2 << "\n";
  cout << "f2 tostring: " << to_string(f2) << "\n";

  return 0;
}
