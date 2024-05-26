#ifndef ATOM_H
#define ATOM_H

#include <string>
class Atom {
private:
  std::string data;
public:
  Atom(std::string);
  std::string get_data() const;
  void print() const;
  bool operator==(const Atom& other) const;
  bool operator!=(const Atom& other) const;
};

#endif