#include "../operand.hh"

using namespace std;
int main() {
  Operand list({Operand(1), Operand(2), Operand(3), Operand(Atom("hello,world"))}, VarTypeEnum::tuple_t);
  //for(int i=0; i<10; i++) { list[i] = Operand(i*10); }

  cout << list[1] << "\n";
  list[1] = Operand(1.23f);
  cout << list[2] << "\n";
  cout << list << "\n";
  cout << list.list_size() << "\n";
}
