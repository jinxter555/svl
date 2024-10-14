#ifndef _OPERAND_HH_
#define _OPERAND_HH_
#pragma once
#include "lang.hh"
#include "number.hh"



//--------------------------------------------------------- 

class Operand : public Primordial<Operand> {
  friend class Entity;
  friend class ListEntity;
  friend class MapEntity;
  friend class QueNode;
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
  entity_u_ptr& _get_entity_u_ptr() ;
  Entity* _get_entity_raw_ptr();
  const string _get_str() const ;
  const string _to_str() const ;
  OperandType _get_type() const;
  //--------------------------------------------------------- Overload entity ..
  //e_members_t& _get_members(); e_children_t& _get_children();
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

struct GetOperandNode_by_key{
string k;
template <typename T>
const Operand& operator()(T value) const;
const Operand& operator()(const entity_u_ptr& v) const  ;
};

struct GetOperand_eptr{
template <typename T>
Entity* operator()(T value) const;
Entity* operator()(const entity_u_ptr& v) const  ;


/*
Entity* operator()(const bool v) const ;
Entity* operator()(const Nil& v) const ;
Entity* operator()(const Number& v) const ;
Entity* operator()(const string& v) const ;
Entity* operator()(const AstOpCode& v) const ;
Entity* operator()(const OperandType& v) const ;
Entity* operator()(const OperandStatusCode& v) const ;
Entity* operator()(const OperandErrorCode& v) const ;
*/
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