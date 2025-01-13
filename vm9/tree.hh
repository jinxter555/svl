#pragma once
#include "lang.hh"
#include "operand.hh"
class Tree : public Primordial<Tree> {
protected:
  Operand root;
public:
  Tree(const OperandType&t) : Primordial(t), root() {};
  s_integer size() const override {return 0;};
  void print() const override;
};