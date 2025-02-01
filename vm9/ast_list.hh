#pragma once
#include <iostream>
#include <variant>
#include <unordered_map>
#include <vector>
#include "ast_node.hh"
#include "operand.hh"



class AstList : public AstNode {
  friend class Tuple;
protected:
  vector<Operand> list_;
public:
  //QueList() : AstNode(OperandType::list_t) { list_ = {};}
  AstList() ;
  AstList(const list_t &);
  AstList(const vec_num_t&);
  AstList(const vec_str_t&);

  astnode_u_ptr clone() const override;
  Operand evaluate(unique_ptr<AstNode>&) override;


//-------------------------------------- 
  const AstNode& get_node() const override;
  const Operand& get_operand() const override;
  const AstList& get_list() const override;
  const AstMap& get_map() const override;
  vector<string> _get_keys() const override;
  bool has_key(const string &k)  const override;

//-------------------------------------- 
  const Operand* get_operand_ptr() const override;
  const AstList* get_list_ptr() const override;
  const AstMap* get_map_ptr() const override;

//-------------------------------------- 
  Operand* get_operand_ptr_nc() override;
  AstList* get_list_ptr_nc() override;
  AstMap* get_map_ptr_nc() override;

//-------------------------------------- 
  const astnode_u_ptr& get_u_ptr() const override;
  astnode_u_ptr& get_u_ptr_nc() override;
  operand_variant_t _get_variant() const override;

//-------------------------------------- 
  Operand& operator[] (const s_integer&k ) override final;
  const Operand& operator[] (const s_integer&k) const override final;

  const Operand& operator[] (const string& k) const override final ;
  Operand& operator[] (const string& k) override ;

  const Operand& operator[] (const AstList& k) const ;
  Operand& operator[] (const AstList& k) override;

  Operand& operator[] (const vec_num_t& k) ;

//-------------------------------------- 

  //bool operator==(const AstNode& ) const override;
  bool operator==(const AstList& ) const ;
  bool operator!=(const AstList& ) const ;
  bool operator==(const astnode_ptr& ) const override;
  bool cmp_eql(const AstNode&) const override;
  bool cmp_eql(const AstList *) const ;
  Operand opfunc(const AstNode&, AstOpCode op) override ;

  const Operand& back() const override;
  Operand& back_nc()  override;
//  const Operand& operator[] (const AstList &k) const ;

  bool add(const operand_variant_t&) ;  // for list
  bool add(astnode_u_ptr &&vptr) override;  // for list
  bool add(const list_t &);
  Operand& remove();


  const list_t& _get_list() const;
  list_t& _get_list_nc() ;

  astnode_ptr _vrptr() const override;
  Operand to_str() const override;
  //astnode_ptr get_raw_ptr() const ;
  Operand get_type() const override;
  OperandType _get_type() const override;

  void print() const override;
  s_integer size() const override;

  bool is_nil() const override;

//  qnode_u_ptr clone() const override;
  //AstNode& operator[] (const AstNode& k) override ;
  //const AstNode& operator[] (const AstNode&k) const override;
  //void accept_nc(Visitor &visitor) override;
  //bool isEqual(const AstNode& other) const override;
  //void accept(Visitor &visitor) const override;

  //bool operator==(const QueList& other) const ;

};


//
// tuple {nil}=={nil} return false problem
//
class Tuple : public AstList{
private:
  OperandType type_;
public:
  Tuple() {};
  Tuple(astnode_u_ptr) ;
//  bool operator==(const Tuple& other) const;
//  bool operator!=(const Tuple& other) const;
//  bool cmp_eql(const AstNode &) const override;
//  Operand opfunc(const AstNode&, AstOpCode op) override final;

  using AstList::operator==;
  using AstList::operator!=;
  using AstList::opfunc;
  using AstList::cmp_eql;

  Operand evaluate(astnode_u_ptr& ast_ctxt) override ;

  astnode_u_ptr clone() const override; 
  astnode_ptr _vrptr() const override;

  Operand to_str() const override ;
  Operand get_type() const override;
  OperandType _get_type() const override;

  //using AstList::evaluate;
  using AstList::size;

  void print() const override;
};