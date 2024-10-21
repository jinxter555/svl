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
  QueNode() {}

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
  const Operand& add_branch(const vector<string> &keys, const Operand& operand=nil_operand);
  const Operand& add_branch(const vector<string> &keys, const Operand& e);
  const Operand& add_branch(const vector<string> &keys, astexpr_u_ptr&& e);
};

class Tree : public Primordial<Tree> {
protected:
  QueNode node;
public:
  Tree(const OperandType&t) : Primordial(t) {};


};

class SvlmAst : Tree {
public:
  SvlmAst(const OperandType&t) : Tree(t) {};

  void add_module();
  void add_class();
  void add_function();
  void add_mvar();
  void add_ovar();
  void add_lvar();

  unique_ptr<Tree> clone() const override {return nullptr;};
  Operand to_str() const override { return "";};
  Operand get_type() const override { return OperandType::nil_t;};
  void print() const override {};

};