#pragma once
#include <iostream>
#include <variant>
#include <unordered_map>
//#include <map>
#include <vector>
#include "ast_node.hh"
#include "operand.hh"



class AstMap: public AstNode{
private:
  map <string, Operand> map_;
public:
  AstMap();
  AstMap(const map_t&);

  astnode_u_ptr clone() const override;
  Operand evaluate(astnode_u_ptr&) override;

  const AstNode& get_node() const override;
  const Operand& get_operand() const override;
  const AstList& get_list() const override;
  const AstMap& get_map() const override;
  vector<string> _get_keys() const override;

  const Operand* get_operand_ptr() const override;
  const AstList* get_list_ptr() const override;
  const AstMap* get_map_ptr() const override;

  Operand* get_operand_ptr_nc() override;
  AstList* get_list_ptr_nc() override;
  AstMap* get_map_ptr_nc() override;

  const astnode_u_ptr& get_u_ptr() const override ;
  astnode_u_ptr& get_u_ptr_nc() override ;
  operand_variant_t _get_variant() const override;

  const list_t& _get_list() const;

  astnode_ptr _vrptr() const override;
  Operand to_str() const override;
  //astnode_ptr get_raw_ptr() const ;
  Operand get_type() const override;
  OperandType _get_type() const override;

  void print() const override;
  s_integer size() const override;

  bool is_nil() const override;

  //-------------------------
  Operand& operator[] (const list_t& k) ;
  Operand& operator[] (const vec_str_t& k) ;

  Operand& operator[] (const AstList& k) override ;
  const Operand& operator[] (const AstList& k) const override final ;

  Operand& operator[] (const string& k) override ;
  const Operand& operator[] (const string& k) const override ;

  Operand& operator[] (const s_integer&k ) override final;
  const Operand& operator[] (const s_integer&k) const override final;

  //-------------------------
  //bool operator==(const AstNode& ) const override;
  bool operator==(const AstMap& ) const ;
  bool operator!=(const AstMap& ) const ;
  bool operator==(const astnode_ptr& ) const override;
  bool cmp_eql(const AstNode&) const override;
  bool cmp_eql(const AstMap *) const ;

  Operand opfunc(const AstNode&, AstOpCode op) override final;
  //-------------------------
  const Operand& back() const override;
  Operand& back_nc()  override;


  bool add(const AstList &k, astnode_u_ptr &&v, bool overwrite=false);
  bool add(const Operand &k, astnode_u_ptr &&v, bool overwrite=false);
  bool add(const vec_str_t &k, astnode_u_ptr &&v, bool overwrite=false);

  bool add(const string &k, astnode_u_ptr &&v, bool overwrite=false);
  bool add(const string &k, const AstNode& v, bool overwrite=false);

  bool add(const AstList &k, const operand_variant_t&v, bool overwrite=false);
  bool add(const vec_str_t &k, const operand_variant_t&v, bool overwrite=false);
  bool add(const string &k,  const operand_variant_t& v, bool overwrite=false);

  bool add(astnode_u_ptr &&vptr) override {return false; };  // for list

  //-------------------------

  bool has_key(const Operand &k) const;
  bool has_key(const string &k) const ;





/*
  void accept_nc(Visitor &visitor) override;
  bool isEqual(const AstNode& other) const override;
  void accept(Visitor &visitor) const override;
*/
  //bool operator==(const AstList& other) const { };

};

class AstExpr : public AstMap {
protected:
  OperandType type_;
  AstMap &node=*(AstMap*)this;
public:
  AstExpr(OperandType t)  :  type_(t) {}
  Operand get_type()  { return type_; }
  OperandType _get_type()  { return type_; }
//  virtual Operand evaluate(astnode_u_ptr&) =0;
};