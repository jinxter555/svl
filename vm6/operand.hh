#ifndef _OPERAND_HH_
#define _OPERAND_HH_
#pragma once
#include "lang.hh"

class Operand; 
class Entity;
using entity_u_ptr = unique_ptr<Entity>;

using OperandVariant=std::variant
< bool, AstOp
, string, OperandErrorCode
, OperandStatusCode, OperandType
, Number
, entity_u_ptr
>;

using o_u_ptr=unique_ptr<Operand>;

class Operand {
  friend class Entity;
  friend class OperandEntity;
  friend class ListEntity;
  friend class MapEntity;
protected:
  OperandType type_;
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
  Operand(const Number& value) ;
  Operand(const string&);
  Operand(const char* value);
  Operand(OperandType);
  Operand(OperandType, const OperandVariant&);
  Operand(AstOp);
  Operand(OperandErrorCode);
  Operand(OperandStatusCode);
  Operand(entity_u_ptr);
  //--------------------------------------------------------- Overload primative operator
  inline Number _get_number() const ;
  s_integer _get_int() const ;
  s_float _get_float() const ;
  const string _get_str() const ;
  const string _to_str() const ;
  void set_type(const OperandType &t);
  OperandType _get_type() const;
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
  Operand opfunc(const Operand& other, AstOp op) ;
  //--------------------------------------------------------- 
/*
  struct GetValue {
    template <typename T> OperandVariant operator()(T value) const;                                                                                                                                   
    OperandVariant operator()(const entity_u_ptr& v) const  ;                                                                                                           
    OperandVariant operator()(Entity *v) const ;
    OperandVariant operator()(const string &s) const ;
    OperandVariant operator()(const Number &n) const ;
    OperandVariant operator()(const OperandStatusCode ) const ;
    OperandVariant operator()(const OperandErrorCode) const ;
    OperandVariant operator()(const OperandType ) const ;
    OperandVariant operator()(bool) const ;
    OperandVariant operator()(AstOp) const ;

  };                            
  */
};

struct GetOperandValue{
template <typename T> OperandVariant operator()(T value) const;                                                                                                                                   
OperandVariant operator()(const entity_u_ptr& v) const  ;                                                                                                           
OperandVariant operator()(Entity *v) const ;
};


#endif