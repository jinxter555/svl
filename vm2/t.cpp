#include "vm.hh"

using namespace std;
int main() {
  std::stack<reg_t>  s;
  reg_t r0,r1 ;
  r0.i = 123;
  r1.i = 456;
  s.push(r0);
  s.push(r1);

  cout << s[0].i << "\n";

  return 0;
}


