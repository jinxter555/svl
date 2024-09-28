#pragma once
#include <variant>
#include <string>
#include <stdexcept>
#include <iostream>
#include <any>
#include <memory>
#include "lang.hh"

class Operand {
  friend class Entity;
protected:
  OperandVariant value_;
  OperandType type_;
public:
  // Constructors for each supported type
  Operand();
  Operand(OperandType t) : type_(t) {} //  just type
  Operand(OperandType t, const OperandType &tv) : type_(t), value_(tv) {} //  meta program type of types
  Operand(AstOp op) : type_(OperandType::ast_op_t), value_(op) {} //  just type
  Operand(OperandErrorCode c) : type_(OperandType::err_t), value_(c) {} //  just type
  Operand(int value) ;
  Operand(float value) ;
  Operand(bool value) ;
  Operand(const Number& value) ;
  Operand(const string& value) ;
  Operand(const char* value) ;


  static string nil_str;

  //--------------------------------------------------------- Overload primative operator
  void set_type(const OperandType &t) { type_=t;};

  const OperandVariant& _get_value() const ;
  inline Number _get_number() const ;

  s_integer _get_int() const ;
  s_float _get_float() const ;
  const string& _get_str() const ;
  const string& _to_str() const { return  _get_str();};
  OperandType _get_type() const { return type_;};

  //--------------------------------------------------------- Overload math operator
  Operand get_str() const {return to_str();}; 
  Operand to_str() const; 


/*
  static Operand to_str(OperandType t);
  static Operand to_str(OperandVariant v);
  static Operand to_str(OperandErrorCode err);
  static Operand to_str(AstOp op); 
*/


  Operand whatami() const;  // introspection type + value

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

  friend ostream& operator<<(ostream& os, const Operand& operand);

};
