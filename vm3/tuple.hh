#ifndef TUPLE_H
#define TUPLE_H

#include <vector>
#include <iostream>
#include <any>
#include "lang.hh"

class Tuple {
private:
  std::vector<std::any> tlist;
public:
  Tuple(std::vector<std::any>  l) : tlist(l){};
  void print() ;
  std::vector<std::any> get_data() const;
  bool operator==(const Tuple& other) const;
  bool operator!=(const Tuple& other) const;
  bool bin_op(const Tuple& other, ast_op op) const;
};

#endif