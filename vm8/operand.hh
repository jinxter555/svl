#pragma once
#include <iostream>
#include <variant>
#include "number.hh"

using namespace std;

#define TO_STR(m) ((Operand::ToString *) this)->Operand::ToString::operator()(m);

class Operand;
using operand_ptr = Operand *;
using operand_u_ptr = unique_ptr<Operand>;
using operand_s_ptr = shared_ptr<Operand>;


//using map_t = map<string, operand_u_ptr>;
using map_t = map<string, Operand>; 
//using list_t = vector<operand_u_ptr>;
using list_t = vector<Operand>; 
using vec_num_t = vector<Number>;
using vec_str_t = vector<string>;

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
  Operand(list_t &&);
  Operand(const map_t &);
  Operand(const vec_num_t&);
  Operand(const vec_str_t&);
  //Operand(const initializer_list<Operand> &v);
  
//------------------------------------
  operand_u_ptr clone() const ;
  list_t clone_list();
  map_t clone_map();
  static list_t clone_list(const list_t&);
  static map_t clone_map(const map_t&);
//------------------------------------
  bool is_nil() const;
  bool has_key(const Operand &k)  const ;


  s_integer size() const ;
  void print() const ;
//------------------------------------
  bool add(const Operand&);
  bool add(const Operand&, const Operand&, bool overwrite=false);
  bool addk(const Operand&k, const Operand&v, bool overwrite=false);
//------------------------------------
  Operand get_type() const ;
  OperandType _get_type() const ;
  Number _get_number() const ;
  //inline s_integer _get_int() const ;
  inline s_integer _get_int() const  { return _get_number().get_int(); };

  Operand to_str() const ;
  string _to_str() const;
//------------------------------------
  const Operand& get_value() const;
  Operand& get_value_nc() ;

  const list_t& _get_list() const;
  s_integer _get_list_size() const;
  list_t& _get_list_nc() ;



  const map_t& _get_map() const;
  s_integer _get_map_size() const;
  map_t& _get_map_nc();

  operand_variant_t _get_variant() const;
  operand_variant_t _deref() const;

  operand_ptr _vrptr() const; 
  //operand_ptr get_raw_ptr() const;
  Operand* get_raw_ptr() const;

//------------------------------------
  Operand& operator[] (const Operand& k) ;
  const Operand& operator[] (const Operand &k) const ;

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
operand_u_ptr operator()(const list_t& v) const  ;
operand_u_ptr operator()(const map_t& v) const  ;
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

struct Map {
const map_t& operator()(const map_t& v) const ;
template <typename T> const map_t& operator()(const T &v) const ;
const map_t& operator()(const Nil) const;
const map_t& operator()(const operand_ptr& v) const ;
const map_t& operator()(const operand_u_ptr& v) const ;
const map_t& operator()(const operand_s_ptr& v) const ;
};

struct List {
const list_t& operator()(const list_t& v) const ;
template <typename T> const list_t& operator()(const T &v) const ;
const list_t& operator()(const Nil) const;
const list_t& operator()(const operand_ptr& v) const ;
const list_t& operator()(const operand_u_ptr& v) const ;
const list_t& operator()(const operand_s_ptr& v) const ;
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

struct Vrptr {
//const operand_ptr &parent_ptr;
//Vrptr(const Operand&);
template <typename T> 
operand_ptr operator()(const T& value) const;
operand_ptr operator()(const Nil) const;
operand_ptr operator()(const operand_ptr& v) const  ;
operand_ptr operator()(const operand_s_ptr& v) const  ;
operand_ptr operator()(const operand_u_ptr& v) const  ;
};


struct Rptr {
template <typename T> 
const operand_ptr operator()(const T& v) const;
const operand_ptr operator()(const Nil) const;
const operand_ptr operator()(const operand_ptr&) const;
const operand_ptr operator()(const operand_s_ptr&) const;
const operand_ptr operator()(const operand_u_ptr&) const;
};

struct Add{
list_t &l_;
Add(list_t &);
template <typename T> 
bool operator()(const T& ) ;
bool operator()(const Nil) ;
bool operator()(const operand_ptr& v) ;
bool operator()(const operand_s_ptr& v) ;
bool operator()(const operand_u_ptr& v) ;
bool operator()(const list_t& v) ;
bool operator()(const map_t& v) ;
};

struct AddK{
map_t &map_;
bool overwrite;
AddK(map_t &, bool);
template <typename T, typename U> 
  bool operator()(const T&k, const U& v ) ;
template <typename T> 
  bool operator()(const list_t& k, const T& v) ;
template <typename T> 
  bool operator()(const string& k, const T& v) ;
  bool operator()(const Nil, const Nil) ;

  bool has_key(const Operand &k)  const ;
  bool has_key(const string &k)  const ;
};

struct GetK{
template <typename T, typename U> const Operand& operator()(const T&, const U& ) const;

template <typename T> const Operand& operator()(const list_t&, const T& ) const;
const Operand& operator()(const list_t&, const Number&) const;
const Operand& operator()(const list_t&, const Nil) const;
const Operand& operator()(const list_t&,const operand_ptr& ) const;
const Operand& operator()(const list_t&,const operand_s_ptr& ) const;
const Operand& operator()(const list_t&,const operand_u_ptr& ) const;
const Operand& operator()(const list_t&,const list_t&) const;

template <typename T> const Operand& operator()(const map_t&, const T& ) const;
const Operand& operator()(const map_t&, const string&) const;
const Operand& operator()(const map_t&, const list_t&) const;
const Operand& operator()(const map_t&, const Nil) const;
const Operand& operator()(const map_t&,const operand_ptr& ) const;
const Operand& operator()(const map_t&,const operand_s_ptr& ) const;
const Operand& operator()(const map_t&,const operand_u_ptr& ) const ;
const Operand& operator()(const map_t&,const map_t&) const ;

template <typename T> const Operand& operator()(const operand_ptr& m, const T&k )const;
template <typename T> const Operand& operator()(const operand_s_ptr& m, const T&k )const;
template <typename T> const Operand& operator()(const operand_u_ptr& m, const T&k )const;
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


  //Operand operator()(const map_t &) const;
  //Operand operator()(s_integer i) const;
  //Operand operator()(s_float f) const ;
};



struct CmpEql{
template <typename T, typename U> 
  bool operator()(const T &a, const U &b) const ;
template <typename T> 
  bool operator()(const T &a, const T &b) const ;
  bool operator()(const list_t&a, const list_t &b) const ;
  bool operator()(const Nil, const Nil b) const;
};



};

//------------------------------------
ostream& operator<<(ostream& os, const Operand& v);
