#pragma once
#include "operand.hh"


class Tree : public Primordial<Tree> {
protected:
  Operand root;
public:
  Tree(const OperandType&t) : Primordial(t), root(map_t{}) {};
  s_integer size() const override {return 0;};
  void print() const override;
};