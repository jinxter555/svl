#ifndef _OPERAND_HH_
#define _OPERAND_HH_
#pragma once
#include "ast.hh"
#include "number.hh"



//--------------------------------------------------------- 

class Operand : public AstExpr {
friend class AstMap;
friend class AstList;
protected:
  OperandVariant value_;
public:
  const static string nil_str;
  // Constructors for each supported type
  // Operand(int value) ; //Operand(float value) 
  //--------
  Operand();
  Operand(const Nil&);
  Operand(bool) ;
  Operand(s_integer);
  Operand(s_float);

  Operand(OperandType);
  Operand(AstOpCode);
  Operand(OperandErrorCode);
  Operand(OperandStatusCode);
  Operand(ControlFlow);

  Operand(const Number&) ;
  Operand(const string&);
  Operand(const char* );
  Operand(const OperandVariant&);
  Operand(const OperandType, const OperandVariant&);
  //Operand(const Operand&);
  Operand(astexpr_u_ptr &);
  Operand(astexpr_u_ptr &&);
  Operand(AstExpr *);


  //Operand operator=(const Operand &v);

  //--------------------------------------------------------- Overload primative operator
  Operand clone_val() const;
  astexpr_u_ptr clone() const override; 

  Operand evaluate(astexpr_u_ptr& ast_ctxt) override final;
  //--------------------------------------------------------- Overload primative operator
  OperandVariant _get_value() const;
  Number _get_number() const ;
  s_integer _get_int() const ;
  s_float _get_float() const ;
  string _get_str() const ;
  string _to_str() const ;
  OperandType _get_type() const override ;
  AstOpCode _get_opcode() const;
  vector<string> _get_keys() const override final;
  //-------
  Operand get_opcode() const;
  Operand get_str() const;
  Operand get_type() const override;
  s_integer size() const override;

  Operand to_str() const override; 
  Operand whatami() const;  // introspection type + value

  void  print() const override; 
  //--------------------------------------------------------- 
  AstExpr *get_raw_ptr(const Operand &k) const override final;
  AstExpr *get_raw_ptr() const override final;

  AstExpr *get_raw_ptr(const string &k) const ;
  AstExpr *get_raw_ptr(const s_integer i) const ;

  const astexpr_u_ptr& get_u_ptr(const Operand &k) const override final;
  astexpr_u_ptr& get_u_ptr_nc(const Operand &k) override final;

  const astexpr_u_ptr& get_u_ptr() const override;
  astexpr_u_ptr& get_u_ptr_nc() override final; // non constant


  //--------------------------------------------------------- 
  friend ostream& operator<<(ostream& os, const Operand& operand);
  //--------------------------------------------------------- Overload math operator
  Operand operator+(const Operand& other) const ;
  Operand operator-(const Operand& other) const ;
  Operand operator*(const Operand& other) const;
  Operand operator/(const Operand& other) const;
  //--------------------------------------------------------- Overload math equality operator
  bool operator==(const Operand& other) const;
  bool operator!=(const Operand& other) const;
  bool operator>=(const Operand& other) const;
  bool operator<=(const Operand& other) const;
  bool operator<(const Operand& other) const;
  bool operator>(const Operand& other) const;

  Operand operator&&(const Operand& other) const;
  Operand operator||(const Operand& other) const;
  //--------------------------------------------------------- Overload math logic operator
  Operand operator!() const;
  //--------------------------------------------------------- 
  Operand opfunc(const Operand& other, AstOpCode op) ;
  //--------------------------------------------------------- 

  //-------------------------------------------
  bool add(const AstExpr &v) override final ;  // for list
  bool add(astexpr_u_ptr &&vptr) override final  ;  // for list
  //-------------------------------------------
  bool add(const Operand &k, const AstExpr& v, bool overwrite=false) override final ;
  bool add(const Operand &k, astexpr_u_ptr&& vptr, bool overwrite=false) override final ;
  //-------------------------------------------
  bool add_branch(const vector<string> &keys, const Operand& operand, bool overwrite=false) override final;
  bool add_branch(const vector<string> &keys, astexpr_u_ptr&& vvptr , bool overwrite=false) override final;
  Operand& get_branch(const vector<string> &keys) override final;
  //-------------------------------------------
  bool set(const Operand &k, const AstExpr& v) override final ;
  bool set(const Operand &k, astexpr_u_ptr&& vptr) override final ;

  Operand& getv()  override final ;
  Operand& getv(const Operand &k)  override final ;
  
  Operand& operator[] (const Operand& k) override final;
  const Operand& operator[] (const Operand &k) const override final;



};

//--------------------------------------------------------- 
struct GetOperandValue{
template <typename T> 
OperandVariant operator()(T value) const;
OperandVariant operator()(const astexpr_u_ptr& v) const  ;
};

struct GetOperandClone{
template <typename T> 
operand_u_ptr operator()(T value) const;
operand_u_ptr operator()(const astexpr_u_ptr& v) const  ;
};

struct OperandEvaluate {
astexpr_u_ptr &ctxt;
OperandEvaluate(astexpr_u_ptr&c);
template <typename T> 
Operand operator()(T v) ;
Operand operator()(astexpr_u_ptr& v) ;
};

/*
struct GetOperand_astexpr_ptr {
template <typename T>
AstExpr* operator()(T value) const;
AstExpr* operator()(const astexpr_u_ptr& v) const  ;
};
struct GetOperand_u_ptr {
template <typename T>
const astexpr_u_ptr& operator()(T value) const;
const astexpr_u_ptr& operator()(const astexpr_u_ptr& v) const  ;
};
*/

struct GetOperandType{
OperandType operator()(const bool v) const ;
OperandType operator()(const Nil& v) const ;
OperandType operator()(const Number& v) const ;
OperandType operator()(const string& v) const ;
OperandType operator()(const AstOpCode& v) const ;
OperandType operator()(const OperandType& v) const ;
OperandType operator()(const ControlFlow& v) const ;
OperandType operator()(const OperandStatusCode& v) const ;
OperandType operator()(const OperandErrorCode& v) const ;
OperandType operator()(const astexpr_u_ptr& v) const  ;
};

struct GetOperandAstOpCode{
template <typename T>
AstOpCode operator()(T value) const;
AstOpCode operator()(const AstOpCode &v) const  ;
};


extern Operand nil_operand;

#endif