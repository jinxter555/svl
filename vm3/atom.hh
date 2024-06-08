#pragma once
#include <variant>
#include <string>
#include <iostream>

class Atom {
private:
  std::string data;
public:
  Atom(std::string);
  std::string get_data() const;
  void print() const;
  bool operator==(const Atom& other) const;
  bool operator!=(const Atom& other) const;
friend std::ostream& operator<<(std::ostream& os, const Atom& a) ;
};
