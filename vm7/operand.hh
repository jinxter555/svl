#ifndef _OPERAND_HH_
#define _OPERAND_HH_
#pragma once
#include "lang.hh"
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
  Operand(astexpr_s_ptr &);
  Operand(AstExpr *);
  Operand(svlm_ast_ptr);


  //Operand operator=(const Operand &v);

  //--------------------------------------------------------- Overload primative operator
  Operand clone_val() const;
  astexpr_u_ptr clone() const override; 

  Operand evaluate(astexpr_u_ptr& ast_ctxt) override final;
  //--------------------------------------------------------- Overload primative operator
  OperandVariant _get_value() const override;
  Number _get_number() const ;
  s_integer _get_int() const override final ;
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
  astexpr_s_ptr get_s_ptr() override final;
  astexpr_u_ptr clone_usu() ;
  //astexpr_s_ptr get_s_ptr_nc() override final;
  //--------------------------------------------------------- 
  AstExpr *get_raw_ptr(const Operand &k) const override final;
  AstExpr *get_raw_ptr() const override final;

  AstExpr *get_raw_ptr(const string &k) const ;
  AstExpr *get_raw_ptr(const s_integer i) const ;

  const astexpr_u_ptr& get_u_ptr(const Operand &k) const override final;
  astexpr_u_ptr& get_u_ptr_nc(const Operand &k) override final;

  const astexpr_u_ptr& get_u_ptr() const override;
  astexpr_u_ptr& get_u_ptr_nc() override final; // non constant
  const astexpr_u_ptr& get_u_ptr_node() const ; // get  last uptr node 

  svlm_ast_ptr get_svlm_ptr();




  //--------------------------------------------------------- 
  friend ostream& operator<<(ostream& os, const Operand& operand);
  //--------------------------------------------------------- Overload math operator
  Operand operator+(const Operand& other) const ;
  Operand operator-(const Operand& other) const ;
  Operand operator*(const Operand& other) const;
  Operand operator/(const Operand& other) const;
  //--------------------------------------------------------- Overload math equality operator
  bool operator==(const Operand& other) const;
  //bool operator==(const Nil& other) const;
  bool operator!=(const Operand& other) const;
  bool operator>=(const Operand& other) const;
  bool operator<=(const Operand& other) const;
  bool operator<(const Operand& other) const;
  bool operator>(const Operand& other) const;

  Operand operator&&(const Operand& other) const;
  Operand operator||(const Operand& other) const;

  bool operator==(const AstExpr&) const override;
  bool operator!=(const AstExpr&) const override;
  bool cmp_eql(const AstExpr&) const override;
  //bool cmp_eql(const OperandVariant&) const override;
  //--------------------------------------------------------- Overload math logic operator
  Operand operator!() const;
  //--------------------------------------------------------- 
  Operand opfunc(const AstExpr&, AstOpCode op) override final;
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

  const Operand& getv() const override final ;
  //Operand& getv_nc() override final ;
  Operand& getv(const Operand &k)  override final ;

  Operand& back()  override final ;
  Operand& front()  override final ;
  
  Operand& operator[] (const Operand& k) override final;
  const Operand& operator[] (const Operand &k) const override final;



};

//--------------------------------------------------------- 
struct OperandValue{
template <typename T> 
OperandVariant operator()(T value) const;
OperandVariant operator()(const astexpr_u_ptr& v) const  ;
OperandVariant operator()(const astexpr_s_ptr& v) const  ;
};

struct OperandClone{
template <typename T> 
operand_u_ptr operator()(T value) const;
operand_u_ptr operator()(const astexpr_u_ptr& v) const  ;
operand_u_ptr operator()(const astexpr_s_ptr& v) const  ;
};

struct OperandEvaluate {
astexpr_u_ptr &ctxt;
OperandEvaluate(astexpr_u_ptr&c);
template <typename T> 
Operand operator()(T v) const ;
Operand operator()(astexpr_ptr v) ;
Operand operator()(astexpr_u_ptr& v) ;
Operand operator()(astexpr_s_ptr& v) ;
};


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
OperandType operator()(const astexpr_ptr v) const  ;
OperandType operator()(const astexpr_s_ptr& v) const  ;
OperandType operator()(const astexpr_u_ptr& v) const  ;
};

struct GetOperandAstOpCode{
template <typename T>
AstOpCode operator()(T value) const;
AstOpCode operator()(const AstOpCode &v) const  ;
};


struct OperandSPtr {
template <typename T> 
astexpr_s_ptr operator()(T& v);
astexpr_s_ptr operator()(astexpr_ptr& v);
astexpr_s_ptr operator()(astexpr_u_ptr& v);
astexpr_s_ptr operator()(astexpr_s_ptr& v);
};

struct OperandUPtr {
const astexpr_u_ptr nil_ast_ptr=nullptr;
template <typename T> 
const astexpr_u_ptr& operator()(const T& v) const;
const astexpr_u_ptr& operator()(const astexpr_ptr& v) const;
const astexpr_u_ptr& operator()(const astexpr_u_ptr& v) const;
const astexpr_u_ptr& operator()(const astexpr_s_ptr& v) const;
};




// for AstList
struct OperandAdd{
const AstExpr &value_;
OperandAdd(const AstExpr&v);
template <typename T> 
bool operator()(T& v) ;
bool operator()(astexpr_ptr& v) ;
bool operator()(astexpr_u_ptr& v) ;
bool operator()(astexpr_s_ptr& v) ;
};

// for AstMap
struct OperandAddK{
const Operand &key_;
const AstExpr &value_;
bool overwrite;
OperandAddK(const Operand& k, const AstExpr& v, bool overwrite=false);
template <typename T> 
bool operator()(T& v) ;
bool operator()(astexpr_ptr& v) ;
bool operator()(astexpr_u_ptr& v) ;
bool operator()(astexpr_s_ptr& v) ;
};

// for AstMap
struct OperandSet{
const Operand &key_;
astexpr_u_ptr vptr;
OperandSet(const Operand& k, astexpr_u_ptr vptr);
template <typename T> 
bool operator()(T& v) ;
bool operator()(astexpr_ptr& v) ;
bool operator()(astexpr_u_ptr& v) ;
bool operator()(astexpr_s_ptr& v) ;
};


// get value
struct OperandGetv {
const Operand &value_;
OperandGetv(const Operand&v);
template <typename T> 
const Operand& operator()(T &v) const ;
const Operand& operator()(astexpr_ptr& v) const ;
const Operand& operator()(astexpr_u_ptr& v) const ;
const Operand& operator()(astexpr_s_ptr& v) const ;
};

// for AstMap
struct OperandGetv_k{
const Operand &key_;
OperandGetv_k(const Operand& k);
template <typename T> 
Operand& operator()(T& v) ;
Operand& operator()(astexpr_ptr& v) ;
Operand& operator()(astexpr_u_ptr& v) ;
Operand& operator()(astexpr_s_ptr& v) ;
};

struct OperandUsu{
template <typename T> 
operand_u_ptr operator()(T value) ;
operand_u_ptr operator()(const astexpr_u_ptr& v) ;
operand_u_ptr operator()(const astexpr_s_ptr& v) ;
};

struct OperandCmpEql{
template <typename T, typename U> bool operator()(const T &a, const U &b) ;
template <typename T> bool operator()(const T &a, const T &b) ;
bool operator()(const Nil, const Nil b);
bool operator()(const astexpr_ptr& a, const astexpr_ptr& b);

template <typename T> bool operator()(const astexpr_u_ptr& a, const T& b);
bool operator()(const astexpr_u_ptr& a, const Number& b);
bool operator()(const astexpr_u_ptr& a, const astexpr_u_ptr& b);
bool operator()(const astexpr_s_ptr& a, const astexpr_s_ptr& b);

};





extern Operand nil_operand;

#endif