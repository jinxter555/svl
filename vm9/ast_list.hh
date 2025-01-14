#pragma once
#include <iostream>
#include <variant>
#include <unordered_map>
#include <vector>
#include "ast_node.hh"
#include "operand.hh"



class AstList : public AstNode {
private:
  vector<Operand> list_;
public:
  //QueList() : AstNode(OperandType::list_t) { list_ = {};}
  AstList() ;
  AstList(const list_t &);
  AstList(const vec_num_t&);
  AstList(const vec_str_t&);

  astnode_u_ptr clone() const override;
  Operand evaluate(unique_ptr<AstNode>&) override;


  const AstNode& get_node() const override;
  const Operand& get_operand() const override;
  const AstList& get_list() const override;
  const AstMap& get_map() const override;

  const Operand* get_operand_ptr() const override;
  const AstList* get_list_ptr() const override;
  const AstMap* get_map_ptr() const override;

  Operand* get_operand_ptr_nc() override;
  AstList* get_list_ptr_nc() override;
  AstMap* get_map_ptr_nc() override;

  Operand& operator[] (const Operand& k) override ;
  Operand& operator[] (const AstList& k) override;

  Operand& operator[] (const s_integer ) ;
  const Operand& operator[] (const s_integer) const ;

//  const Operand& operator[] (const AstList &k) const ;

  bool add(astnode_u_ptr &&vptr) override;  // for list
  bool add(const operand_variant_t&) ;  // for list
  bool add(const list_t &);


  const list_t& _get_list() const;

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