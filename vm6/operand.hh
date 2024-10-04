#ifndef _OPERAND_HH_
#define _OPERAND_HH_
#pragma once
#include "lang.hh"

class Nil{};
extern Nil nil;
class Entity; class OperandEntity; class ListEntity; 
class AstNode;

using entity_u_ptr = unique_ptr<Entity>;
using e_members_t = vector<entity_u_ptr>;

using list_u_ptr = unique_ptr<ListEntity>;
using operand_u_ptr=unique_ptr<OperandEntity>;

using OperandVariant=std::variant
< Nil
, bool, string, Number
, AstOpCode, OperandErrorCode
, OperandStatusCode, OperandType
, entity_u_ptr , list_u_ptr
, e_members_t
//, AstNode
>;

class Operand {
  friend class Entity;
  friend class OperandEntity;
  friend class ListEntity;
  friend class MapEntity;
protected:
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

  Operand(const Number& value) ;
  Operand(const string&);
  Operand(const char* value);
  Operand(const OperandVariant&);

  Operand(entity_u_ptr);
  Operand(list_u_ptr);
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
  //--------------------------------------------------------- Overload math operator
  Operand get_str() const;
  Operand get_type() const;

  Operand to_str() const; 
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
template <typename T> OperandVariant operator()(T value) const;                                                                                                                                   
OperandVariant operator()(const entity_u_ptr& v) const  ;                                                                                                           
OperandVariant operator()(const list_u_ptr& v) const  ;                                                                                                           
OperandVariant operator()(Entity *v) const ;
OperandVariant operator()(const e_members_t& v) const  ;                                                                                                           
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
OperandType operator()(const list_u_ptr& v) const  ;                                                                                                           
OperandType operator()(Entity *v) const ;
OperandType operator()(const e_members_t& v) const  ;                                                                                                           
};


#endif