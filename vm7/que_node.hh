#pragma once
#include "ast.hh"
#include "ast_list.hh"
#include "ast_map.hh"

class QueNode 
: public AstMap
, public AstList{
private:
  OperandType type_;

public:
  //void add(const ListEntity&);
  QueNode();

  void print_l() const;
  void print_m() const;

  using AstMap::add;
  using AstMap::set;
  using AstMap::getv;
  using AstMap::to_str;

  using AstMap::add_branch;
  using AstMap::get_branch;

  astexpr_u_ptr clone() ;
 // OperandEntity to_str() { return Operand("astnode123");}
  Operand get_type() { return Operand(OperandType::quenode_t);}
  OperandType _get_type() { return OperandType::quenode_t;}
  void print() const ;
  friend ostream& operator<<(ostream& os, const QueNode& e) ;

};

class Tree : public Primordial<Tree> {
protected:
  QueNode root;
public:
  Tree(const OperandType&t) : Primordial(t) {};
  s_integer size() const override {return 0;};

};
