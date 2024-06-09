#pragma once
#include <variant>
#include <string>
#include <stdexcept>
#include <iostream>
#include "lang.hh"
#include "number.hh"
#include "atom.hh"
#include "tuple.hh"



class Operand {
private:
  OperandVariant value_;
  VarTypeEnum type_;
public:
  VarTypeEnum get_type() { return type_;};
  // Constructors for each supported type
  Operand(int value) ;
  Operand(float value) ;
  Operand(bool value) ;
  Operand(const Number& value) ;
  Operand(const Atom& value) ;
  Operand(const std::string& value) ;
  Operand(const Tuple& value) ;

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


  bool bin_op(const Operand& other, ast_op op) const;

  friend std::ostream& operator<<(std::ostream& os, const Operand& operand);

};


