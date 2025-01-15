#pragma once
#include <iostream>
#include <variant>
#include <unordered_map>
#include <vector>
#include "lang.hh"
#include "ast_node.hh"






class Operand : public AstNode {
private:
  operand_variant_t value_;
public:
  Operand();
  Operand(const Nil&);
  Operand(const s_integer);
  Operand(const s_float);
  Operand(const bool) ;
  Operand(const Number&) ;
  Operand(const char*) ;
  Operand(const string&) ;
  Operand(const OperandType&);
  Operand(const AstOpCode&);
  Operand(const OperandErrorCode&);
  Operand(const OperandStatusCode&);
  Operand(const ControlFlow&);
  Operand(astnode_u_ptr &&);
  //Operand(const astnode_u_ptr &);
  //Operand(const astnode_s_ptr &);
  Operand(const list_t &);
  Operand(const map_t &);
  Operand(const vec_num_t&);
  Operand(const vec_str_t&);
  Operand(const operand_variant_t& ) ;
  Operand(const astnode_ptr);
  Operand(const svlm_ast_ptr) ;

  bool add(astnode_u_ptr &&) ;  // for list
  bool add(const operand_variant_t&) ;  // for list

  bool add(const AstList &k, const operand_variant_t&, bool overwrite=false);
  bool add(const AstList &k, astnode_u_ptr&&, bool overwrite=false);



  operand_variant_t _get_variant() const override;



//------------------------------------
  astnode_u_ptr clone() const ;
  operand_u_ptr clone_operand() const ;

  Operand evaluate(unique_ptr<AstNode>& ctxt) override;
//------------------------------------
  Operand to_str() const override;
  string _to_str() const;

  Operand get_type() const override;
  OperandType _get_type() const override;

  void print() const override;
  s_integer size() const override;

  Number _get_number() const ;
  //inline s_integer _get_int() const ;
  inline s_integer _get_int() const  { return _get_number().get_int(); };
  inline s_integer _get_float() const  { return _get_number().get_float(); };


  astnode_ptr _vrptr() const override; 
  astnode_ptr get_raw_ptr() const ;

  const astnode_u_ptr& get_u_ptr() const override;
  astnode_u_ptr& get_u_ptr_nc() override;

  astnode_u_ptr _uptr() ; 

  bool has_key(const Operand &k)  const ;

  bool is_nil() const;

//------------------------------------
  const Operand& get_value() const;

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


//------------------------------------
  AstOpCode _get_opcode() const;
  Operand get_opcode() const;


  const Operand& operator[] (const Operand& k)const  ;
  Operand& operator[] (const Operand& k) override final;
  Operand& operator[] (const AstList& k) override final;
  
  const Operand& back() const override;
  Operand& back_nc()  override;
 // const Operand& operator[] (const Operand &k) const override final;
/*
//------------------------------------
  void accept_nc(Visitor &visitor) override;
  void accept(Visitor &visitor) const override;
  bool isEqual(const AstNode& other) const override;
//------------------------------------
*/



struct Variant{
template <typename T> operand_variant_t operator()(const T& value) const;
operand_variant_t operator()(const Nil) const;
//operand_variant_t operator()(const astnode_ptr& v) const  ;
//operand_variant_t operator()(const astnode_s_ptr& v) const  ;
operand_variant_t operator()(const astnode_u_ptr& v) const  ;
};


//------------------------------------
struct Clone{
template <typename T> 
astnode_u_ptr operator()(const T& value) const;
astnode_u_ptr operator()(const Nil) const;
astnode_u_ptr operator()(const astnode_ptr& v) const  ;
astnode_u_ptr operator()(const astnode_u_ptr& v) const  ;
astnode_u_ptr operator()(const astnode_s_ptr& v) const  ;
};


//------------------------------------
struct Vrptr {
template <typename T> 
astnode_ptr operator()(const T& value) const;
astnode_ptr operator()(const Nil) const;
astnode_ptr operator()(const astnode_ptr& v) const  ;
astnode_ptr operator()(const astnode_s_ptr& v) const  ;
astnode_ptr operator()(const astnode_u_ptr& v) const  ;
};

//------------------------------------
struct Rptr {
template <typename T> 
const astnode_ptr operator()(const T& v) const;
const astnode_ptr operator()(const Nil) const;
const astnode_ptr operator()(const astnode_ptr&) const;
const astnode_ptr operator()(const astnode_s_ptr&) const;
const astnode_ptr operator()(const astnode_u_ptr&) const;
};

//------------------------------------
struct Uptr {
template <typename T> 
const astnode_u_ptr& operator()(const T& v) const;
const astnode_u_ptr& operator()(const Nil) const;
const astnode_u_ptr& operator()(const astnode_ptr& v) const;
const astnode_u_ptr& operator()(const astnode_u_ptr& v) const;
const astnode_u_ptr& operator()(const astnode_s_ptr& v) const;
};

//------------------------------------
struct Type{
OperandType operator()(const bool v) const ;
OperandType operator()(const Nil& v) const ;
OperandType operator()(const Number& v) const ;
OperandType operator()(const string& v) const ;
OperandType operator()(const AstOpCode& v) const ;
OperandType operator()(const OperandType& v) const ;
OperandType operator()(const ControlFlow& v) const ;
OperandType operator()(const OperandStatusCode& v) const ;
OperandType operator()(const OperandErrorCode& v) const ;
OperandType operator()(const astnode_u_ptr& v) const  ;
OperandType operator()(const astnode_s_ptr& v) const  ;
OperandType operator()(const astnode_ptr& v) const  ;
OperandType operator()(const svlm_ast_ptr&) const;
};

//------------------------------------
struct OpCode{
template <typename T> 
AstOpCode operator()(T& v) const ;
AstOpCode operator()(const AstOpCode v) const ;
AstOpCode operator()(const Nil) const ;
};

struct ToString {
  Operand operator()(const Nil) const;
  Operand operator()(bool b) const;
  Operand operator()(const Number& n) const ;
  Operand operator()(const string& s) const ;
  Operand operator()(OperandType) const;
  Operand operator()(OperandErrorCode err) const;
  Operand operator()(OperandStatusCode status) const;
  Operand operator()(ControlFlow cf) const;
  Operand operator()(AstOpCode t_op) const;
//  Operand operator()(const svlm_ast_ptr&) const ;
  //Operand operator()(const operand_s_ptr&) const;
  //Operand operator()(const operand_u_ptr&) const;
  //Operand operator()(const operand_ptr&) const;
  //Operand operator()(const list_t &) const;
  //Operand operator()(const map_t &) const;
  Operand operator()(const astnode_u_ptr&) const;
  Operand operator()(const astnode_s_ptr&) const;
  Operand operator()(const svlm_ast_ptr&) const;


  //Operand operator()(const map_t &) const;
  //Operand operator()(s_integer i) const;
  //Operand operator()(s_float f) const ;
};

  //--------------------------------------------------------- Overload math operator
  Operand operator+(const Operand& other) const ;
  Operand operator-(const Operand& other) const ;
  Operand operator*(const Operand& other) const;
  Operand operator/(const Operand& other) const;
  //--------------------------------------------------------- Overload math equality operator
  //bool operator==(const Nil& other) const;

  bool operator==(const Operand& other) const;
  bool operator!=(const Operand& other) const;
  bool operator>=(const Operand& other) const;
  bool operator<=(const Operand& other) const;
  bool operator<(const Operand& other) const;
  bool operator>(const Operand& other) const;

  Operand operator&&(const Operand& other) const;
  Operand operator||(const Operand& other) const;

  //bool operator==(const AstNode& ) const override;
  bool operator==(const AstNode& ) const ;
  bool operator==(const astnode_ptr& ) const override;
  bool cmp_eql(const AstNode&) const override;


struct CmpEql{
template <typename T, typename U> bool operator()(const T &a, const U &b) ;
template <typename T> bool operator()(const T &a, const T &b) ;
bool operator()(const AstNode*, const AstNode*) ;
bool operator()(const Nil, const Nil b);
};


  //bool operator!=(const AstNode&) const override;
  //bool cmp_eql(const AstExpr&) const override;
  //bool cmp_eql(const OperandVariant&) const override;
  //--------------------------------------------------------- Overload math logic operator
  Operand operator!() const;
  //--------------------------------------------------------- 
  Operand opfunc(const AstNode&, AstOpCode op) override final;





friend ostream& operator<<(ostream& os, const Operand& operand);
};

ostream& operator<<(ostream& os, const Operand& operand);
