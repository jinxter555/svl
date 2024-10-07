#ifndef _OPERAND_HH_
#define _OPERAND_HH_
#pragma once
#include "lang.hh"

class Nil{};
extern Nil nil;
class Entity; class ListEntity;  class MapEntity;


class AstNode; class AstExpr;
class Operand;
using operand_u_ptr=unique_ptr<Operand>;

using entity_u_ptr = unique_ptr<Entity>;
//using e_members_t = vector<entity_u_ptr>;
using e_members_t = vector<Operand>;
using e_children_t = unordered_map<string, Operand>;

using list_u_ptr = unique_ptr<ListEntity>;
using map_u_ptr = unique_ptr<MapEntity>;


using astexpr_u_ptr = unique_ptr<AstExpr>;

using OperandVariant=std::variant
< Nil
, bool, string, Number
, AstOpCode, OperandErrorCode
, OperandStatusCode, OperandType
, entity_u_ptr
// , list_u_ptr
//, e_members_t , e_children_t
>;

template <typename T>
class Primordial {
protected:
  OperandType type_;
public:
 // Primordial(OperandType);
  Primordial(OperandType t) : type_(t) {};
  virtual unique_ptr<T> clone() const=0;
  virtual Operand to_str() const =0;
  virtual Operand get_type() const=0;
  virtual void print() const =0;
};

class Operand : public Primordial<Operand> {
  friend class Entity;
  friend class ListEntity;
  friend class MapEntity;
protected:
  //OperandType type_;
  OperandVariant value_;
public:
  const static string nil_str;
  // Constructors for each supported type
  // Operand(int value) ; //Operand(float value) 
  //--------
  Operand();
  Operand(bool) ;
  Operand(s_integer);
  Operand(s_float);

  Operand(OperandType);
  Operand(AstOpCode);
  Operand(OperandErrorCode);
  Operand(OperandStatusCode);

  Operand(const Number&) ;
  Operand(const string&);
  Operand(const char* );
  Operand(const OperandVariant&);
  Operand(const OperandType, const OperandVariant&);
  //Operand(const Operand&);
  Operand(entity_u_ptr &);
  Operand(entity_u_ptr &&);

  //Operand operator=(const Operand &v);

  //--------------------------------------------------------- Overload primative operator
  Operand clone_val() const;
  unique_ptr<Operand> clone() const override ;
  //--------------------------------------------------------- Overload primative operator
  OperandVariant _get_value() const;
  inline Number _get_number() const ;
  s_integer _get_int() const ;
  s_float _get_float() const ;
  const string _get_str() const ;
  const string _to_str() const ;
  OperandType _get_type() const;
  //--------------------------------------------------------- Overload entity ..
  e_members_t& _get_members();
  e_children_t& _get_children();
  //--------------------------------------------------------- Overload math operator
  Operand get_str() const;
  Operand get_type() const override;

  Operand to_str() const override; 
  void  print() const override; 
  Operand whatami() const;  // introspection type + value
  //--------------------------------------------------------- Overload math operator
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
  //--------------------------------------------------------- Overload math logic operator
  Operand opfunc(const Operand& other, AstOpCode op) ;
  //--------------------------------------------------------- 
};

struct GetOperandValue{
template <typename T> 
OperandVariant operator()(T value) const;                                                                                                                                   
OperandVariant operator()(const entity_u_ptr& v) const  ;                                                                                                           
/*
OperandVariant operator()(const list_u_ptr& v) const  ;                                                                                                           
OperandVariant operator()(Entity *v) const ;
OperandVariant operator()(const e_members_t& v) const  ;                                                                                                           
OperandVariant operator()(const e_children_t& v) const  ;                                                                                                           
*/
};

struct GetOperandClone{
template <typename T> 
operand_u_ptr operator()(T value) const;                                                                                                                                   
operand_u_ptr operator()(const entity_u_ptr& v) const  ;                                                                                                           
};



struct GetOperandType{
OperandType operator()(const bool v) const ;
OperandType operator()(const Nil& v) const ;
OperandType operator()(const Number& v) const ;
OperandType operator()(const string& v) const ;
OperandType operator()(const AstOpCode& v) const ;
OperandType operator()(const OperandType& v) const ;
OperandType operator()(const OperandStatusCode& v) const ;
OperandType operator()(const OperandErrorCode& v) const ;
OperandType operator()(const entity_u_ptr& v) const  ;                                                                                                           
/*
OperandType operator()(const list_u_ptr& v) const  ;                                                                                                           
OperandType operator()(Entity *v) const ;
OperandType operator()(const e_members_t& v) const  ;                                                                                                           
OperandType operator()(const e_children_t& v) const  ;                                                                                                           
*/
};


#endif