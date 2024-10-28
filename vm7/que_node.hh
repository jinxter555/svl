#pragma once
#include "ast.hh"
#include "ast_list.hh"
#include "ast_map.hh"

class QueNode 
: public AstMap
, public AstList{
private:

public:
  //void add(const ListEntity&);
  QueNode();

  void print_l() const;
  void print_m() const;

  using AstMap::add;
  using AstMap::set;
  using AstMap::getv;
  using AstMap::to_str;

  astexpr_u_ptr clone() ;
 // OperandEntity to_str() { return Operand("astnode123");}
  Operand get_type() { return Operand(OperandType::str_t);}
  void print() {};


  const Operand& get_branch(const vector<string> &keys);
  bool add_branch(const vector<string> &keys, const Operand& operand=nil_operand, bool overwrite=false);
  bool add_branch(const vector<string> &keys, const AstExpr& e, bool overwrite=false);
  bool add_branch(const vector<string> &keys, astexpr_u_ptr&& e, bool overwrite=false);
};

class Tree : public Primordial<Tree> {
protected:
  QueNode root;
public:
  Tree(const OperandType&t) : Primordial(t) {};
  s_integer size() const override {return 0;};

};
