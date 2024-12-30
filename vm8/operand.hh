#pragma once
#include <iostream>
#include <variant>
#include "number.hh"

using namespace std;

class Operand;
using operand_ptr = Operand *;
using operand_u_ptr = unique_ptr<Operand>;
using operand_s_ptr = shared_ptr<Operand>;


//using map_t = map<string, operand_u_ptr>;
using map_t = map<string, Operand>; 
//using list_t = vector<operand_u_ptr>;
using list_t = vector<Operand>; 

using operand_variant_t = variant
< Nil
, bool, string, Number
, ControlFlow
, AstOpCode
, OperandErrorCode
, OperandStatusCode
, OperandType
, list_t
, map_t
, operand_ptr
, operand_s_ptr
, operand_u_ptr
>;

class Operand {
private:
  OperandType type_;
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
  Operand(operand_u_ptr &&);
  Operand(const operand_u_ptr &);
  Operand(const operand_ptr);
  Operand(const operand_s_ptr& );
  Operand(const list_t &);
  Operand(const map_t &);
  //Operand(const initializer_list<Operand> &v);
  
//------------------------------------
  Operand get_type() const ;
  OperandType _get_type() const ;
  Number _get_number() const ;

  Operand to_str() const ;
  string _to_str() const;
//------------------------------------
  const Operand& get_value() const;
  operand_variant_t _get_variant() const;
  operand_variant_t _deref() const;
//------------------------------------
  operand_u_ptr clone() const ;
//------------------------------------

  s_integer size() const ;
  void print() const ;

//------------------------------------
  Operand operator+(const Operand& other) const ;
  Operand operator-(const Operand& other) const ;
  Operand operator*(const Operand& other) const;
  Operand operator/(const Operand& other) const;

  bool operator==(const Operand& other) const;
  bool operator!=(const Operand& other) const;
  bool operator>=(const Operand& other) const;
  bool operator<=(const Operand& other) const;
  bool operator<(const Operand& other) const;
  bool operator>(const Operand& other) const;

  Operand operator&&(const Operand& other) const;
  Operand operator||(const Operand& other) const;

  Operand operator!() const;

  Operand opfunc(const Operand&, AstOpCode op) ;

//------------------------------------
struct Clone{
template <typename T> 
operand_u_ptr operator()(const T& value) const;
operand_u_ptr operator()(const Nil) const;
operand_u_ptr operator()(const operand_ptr& v) const  ;
operand_u_ptr operator()(const operand_u_ptr& v) const  ;
operand_u_ptr operator()(const operand_s_ptr& v) const  ;
};

struct Value{
template <typename T> 
const Operand& operator()(T &v) const ;
const Operand& operator()(const Nil) const;
const Operand& operator()(operand_ptr& v) const ;
const Operand& operator()(operand_u_ptr& v) const ;
const Operand& operator()(operand_s_ptr& v) const ;
};

struct Variant{
template <typename T> 
operand_variant_t operator()(const T& value) const;
operand_variant_t operator()(const Nil) const;
operand_variant_t operator()(const operand_ptr& v) const  ;
operand_variant_t operator()(const operand_s_ptr& v) const  ;
operand_variant_t operator()(const operand_u_ptr& v) const  ;
operand_variant_t operator()(const list_t& v) const  ;
operand_variant_t operator()(const map_t& v) const  ;
};

struct DeRef{
template <typename T> 
operand_variant_t operator()(const T& value) const;
operand_variant_t operator()(const Nil) const;
operand_variant_t operator()(const operand_ptr& v) const  ;
operand_variant_t operator()(const operand_s_ptr& v) const  ;
operand_variant_t operator()(const operand_u_ptr& v) const  ;
operand_variant_t operator()(const list_t& v) const  ;
operand_variant_t operator()(const map_t& v) const  ;
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
  Operand operator()(const operand_s_ptr&) const;
  Operand operator()(const operand_u_ptr&) const;
  Operand operator()(const operand_ptr&) const;
  Operand operator()(const list_t &) const;
  Operand operator()(const map_t &) const;
  //Operand operator()(s_integer i) const;
  //Operand operator()(s_float f) const ;
};



};

//------------------------------------
ostream& operator<<(ostream& os, const Operand& v);
ostream& operator<<(ostream& os, const operand_u_ptr& ptr);
ostream& operator<<(ostream& os, const operand_s_ptr& ptr);
ostream& operator<<(ostream& os, const operand_ptr& ptr);



extern Nil nil;