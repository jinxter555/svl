#include "svlm_operand.hh"
#include <vector>
#include <iostream>

std::ostream& operator << (std::ostream& out, std::any& a) ;
class Tuple : Operand {
private:
  std::vector<std::any> tlist;
public:
  Tuple(std::vector<std::any>  l) : tlist(l){};
  OperandType   whoami() override { return OperandType::Tuple; }
  void print() ;
  std::vector<std::any> get_data() const;
};