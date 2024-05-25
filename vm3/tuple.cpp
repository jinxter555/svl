#include "tuple.hh"

std::vector<std::any> Tuple::get_data() const {
  return tlist;
}
void Tuple::print() {
    int i;
    std::cout << "{";
    for(i=0; i<tlist.size()-1; i++) {
      std::cout <<  tlist[i] << ", ";
    }
    std::cout <<  tlist[i] << "}";
}


