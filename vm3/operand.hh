#pragma once
#include <variant>
#include <string>
#include <stdexcept>
#include <iostream>
#include <any>
#include "lang.hh"
#include "number.hh"
#include "atom.hh"



class Operand {
private:
  OperandVariant value_;
  VarTypeEnum type_;
  std::vector<Operand> list_;
public:
  VarTypeEnum get_type() { return type_;};
  void print_type() const;
  // Constructors for each supported type
  Operand(int value) ;
  Operand(float value) ;
  Operand(bool value) ;
  Operand(const Number& value) ;
  Operand(const Atom& value) ;
  Operand(const std::string& value) ;
  Operand(std::vector<std::any>  l, VarTypeEnum t); // tuple

  // Get the stored value (use with caution)
  const OperandVariant& getValue() const ;

  // Overload addition operator

  Operand operator+(const Operand& other) const ;
  Operand operator-(const Operand& other) const ;
  Operand operator*(const Operand& other) const;
  Operand operator/(const Operand& other) const;
  Operand &operator[](int i) {
    return list_[i];
  };
  const Operand &operator[](int i) const{
    return list_[i];
  };

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
  //void push_back(std::vector<Operand> &, const Operand& other); // for list
  bool list_cmp(const Operand& other) const; // for list
  static void list_print(std::ostream& os, char b, char e, const Operand& ol) ;
  int list_size() const { 
    if(type_ == VarTypeEnum::list_t || type_ == VarTypeEnum::tuple_t) 
      return  list_.size(); 
    return 0;
  }

  friend std::ostream& operator<<(std::ostream& os, const Operand& operand);
  //friend std::ostream& operator<<(std::ostream& os, const std::vector<Operand> operand_vector) ;

};


