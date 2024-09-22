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

  vector<Operand> members;
  map<string, Operand> children;
  shared_ptr<Operand>  parent;

public:
  // Constructors for each supported type
  Operand();
  Operand(OperandType t) : type_(t) {} //  just type
  Operand(int value) ;
  Operand(float value) ;
  Operand(bool value) ;
  Operand(const Number& value) ;
  Operand(const string& value) ;
  Operand(const char* value) ;

  //
  OperandType get_type() { return type_;};
  void print_type() const;
  // Get the stored value (use with caution)
  const OperandVariant& getValue() const ;

  // Overload addition operator

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


  Operand opfunc(const Operand& other, ast_op op) ;

  friend ostream& operator<<(ostream& os, const Operand& operand);
  friend ostream& operator<<(ostream& os, const OperandType& t);

};


