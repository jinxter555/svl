#include "atom.hh"
#include <iostream>

Atom::Atom(std::string s) : data(s) {}

std::string Atom::get_data() const {
  return data;
}
void Atom::print() const {
    std::cout <<  ":" << data;
}
bool Atom::operator==(const Atom& other) const{
  return data == other.data;
};
bool Atom::operator!=(const Atom& other) const{
  return data != other.data;
};


