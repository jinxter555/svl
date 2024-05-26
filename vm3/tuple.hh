#include <vector>
#include <iostream>
#include <any>

std::ostream& operator << (std::ostream& out, std::any& a) ;
class Tuple {
private:
  std::vector<std::any> tlist;
public:
  Tuple(std::vector<std::any>  l) : tlist(l){};
  void print() ;
  std::vector<std::any> get_data() const;
};