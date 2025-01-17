#pragma once
#include "lang.hh"
#include "number.hh"

class Operand;
class AstList;
class AstMap;



class Visitor {
public:
  virtual void visit(Operand&)=0;
  virtual void visit(AstList&)=0;
  virtual void visit(AstMap&)=0;

};

class AstNode : public Primordial<AstNode> {
public:
  AstNode() : Primordial(OperandType::nil_t) {};
  AstNode(OperandType t) : Primordial(t) {};

  virtual Operand evaluate(unique_ptr<AstNode>&) =0 ;
  virtual Operand opfunc(const AstNode&, AstOpCode op) =0;


  virtual astnode_ptr _vrptr() const =0;
  //virtual astnode_ptr get_raw_ptr() const =0;

  virtual const AstNode& get_node() const=0;
  virtual const Operand& get_operand() const=0;
  virtual const AstList& get_list() const=0;
  virtual const AstMap& get_map() const=0;

  virtual const Operand* get_operand_ptr() const=0;
  virtual const AstList* get_list_ptr() const=0;
  virtual const AstMap* get_map_ptr() const=0;

  virtual Operand* get_operand_ptr_nc() =0;
  virtual AstList* get_list_ptr_nc() =0;
  virtual AstMap* get_map_ptr_nc() =0;

  virtual const astnode_u_ptr& get_u_ptr() const =0;
  virtual astnode_u_ptr& get_u_ptr_nc() =0;
  virtual operand_variant_t _get_variant() const=0 ;

  virtual bool is_nil() const=0;


  virtual const Operand& operator[] (const string &k) const =0 ;
  virtual Operand& operator[] (const string& k) = 0;

  virtual const Operand& operator[] (const s_integer &k) const =0 ;
  virtual Operand& operator[] (const s_integer& k) = 0;

  virtual const Operand& operator[] (const AstList& k) const = 0;
  virtual Operand& operator[] (const AstList& k) = 0;

  virtual const Operand& back() const = 0;
  virtual Operand& back_nc() = 0;
  virtual bool add(astnode_u_ptr &&vptr) =0;  // for list
  



  //virtual bool operator==(const AstNode& ) const=0;
  virtual bool operator==(const astnode_ptr& ) const=0;
  virtual bool cmp_eql(const AstNode&) const=0;

  /*
  virtual bool operator!=(const AstNode& other) const=0;

  virtual bool add(const AstNode& v) = 0;
*/
  //virtual void accept(Visitor &visitor) const=0;
  //virtual void accept_nc(Visitor &)=0;
  //virtual bool isEqual(const AstNode& other) const=0;
};

/*
class CompareVisitor : public Visitor {
private:
  const Operand *operand_;
  const AstList *list_;
  const AstMap *map_;
  bool isEqual;
public:
  CompareVisitor(const Operand&);
  CompareVisitor(const AstList&);
  CompareVisitor(const AstMap&);

  void visit(Operand &) override;
  void visit(AstList &) override;
  void visit(AstMap&) override;

  bool isEqualResult() const;

};


*/

ostream& operator<<(ostream& os, const astnode_u_ptr& ptr) ;
ostream& operator<<(ostream& os, const AstNode& e) ;