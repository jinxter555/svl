#include <iostream>
#include <variant>
#include <unordered_map>
#include <vector>
#include "que_node.hh"


//---------------------------------------------------------------------------
CompareVisitor::CompareVisitor(const Operand& v) 
  : operand_(&v) 
  , list_(nullptr) 
  , map_(nullptr) 
  {}

CompareVisitor::CompareVisitor(const QueList& l) 
  : operand_(nullptr) 
  , list_(&l) 
  , map_(nullptr) 
  {}

CompareVisitor::CompareVisitor(const QueMap& m) 
  : operand_(nullptr) 
  , list_(nullptr) 
  , map_(&m) 
  {}

void CompareVisitor::visit(Operand &other) { isEqual = (this->operand_ != nullptr); }
void CompareVisitor::visit(QueList &other) { isEqual = (this->list_!= nullptr); }
void CompareVisitor::visit(QueMap &other) { isEqual = (this->map_!= nullptr); }
bool CompareVisitor::isEqualResult() const{ return isEqual; }