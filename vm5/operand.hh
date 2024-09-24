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
  Operand* operand_error=nullptr;

/*
  vector<Operand> members;
  map<string, Operand> children;
  shared_ptr<Operand>  parent;
*/

public:
  // Constructors for each supported type
  Operand();
  Operand(OperandType t) : type_(t) {} //  just type
  Operand(AstOp op) : value_(op) {} //  just type
  Operand(OperandErrorCode c) : value_(c), type_(OperandType::err_t) {} //  just type
  Operand(int value) ;
  Operand(float value) ;
  Operand(bool value) ;
  Operand(const Number& value) ;
  Operand(const string& value) ;
  Operand(const char* value) ;

  //
  OperandType type_get() const { return type_;};
  void type_print() const;

  // Get the stored value (use with caution)
  const OperandVariant& getValue() const ;

  static Operand type_str(OperandType t);
  static Operand err_str(OperandErrorCode err);
  static Operand ast_op_str(AstOp op); 

  Operand type_str() const;
  Operand err_str() const;
  Operand ast_op_str() const; 

  Operand whatami() const;  // introspection type + value

  // Overload math operator
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


  Operand opfunc(const Operand& other, AstOp op) ;

  friend ostream& operator<<(ostream& os, const Operand& operand);
  friend ostream& operator<<(ostream& os, const OperandType& t);

};

std::ostream& operator << (std::ostream& out, std::any& a);