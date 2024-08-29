#include <variant>
#include <string>
#include <stdexcept>
#include <iostream>
#include "operand.hh"


Operand::Operand(bool value) : value_(value) { type_ = VarTypeEnum::bool_t; }
Operand::Operand(int value) : value_(Number(value)) { type_ = VarTypeEnum::num_t; }
Operand::Operand(float value) : value_(Number(value)) { type_ = VarTypeEnum::num_t; }
Operand::Operand(const Number &value) : value_(value) { type_ = VarTypeEnum::num_t; }
Operand::Operand(const Atom &value) : value_(value) { type_ = VarTypeEnum::atom_t; }
Operand::Operand(const std::string& value) : value_(value) { type_ = VarTypeEnum::str_t; }

Operand::Operand(std::vector<std::any>  l, VarTypeEnum t) : type_(t) { 
  for(auto a: l) {
    list_.push_back(std::any_cast<Operand>(a));
  }
}

const OperandVariant& Operand::getValue() const { return value_; }

Operand Operand::operator+(const Operand& other) const {
  if(type_ != other.type_) 
    throw std::runtime_error("Unsupported operation + for unequal types"); 

  switch(type_) {
  case VarTypeEnum::num_t: 
    return Operand(std::get<Number>(value_) + std::get<Number>(other.value_));
  case VarTypeEnum::str_t: 
    std::cout << "adding two strings\n";
    return Operand(std::get<std::string>(value_) + std::get<std::string>(other.value_));
  default: 
    std::cout << "type int: " << static_cast<int>(type_) << "\n";
    throw std::runtime_error("Unsupported operation"); 
  }
}



  // Overload subtraction operator (similar approach)
Operand Operand::operator-(const Operand& other) const {
  if(type_ != other.type_) 
    throw std::runtime_error("Unsupported operation + for unequal types"); 

  switch(type_) {
  case VarTypeEnum::num_t: 
    return Operand(std::get<Number>(value_) - std::get<Number>(other.value_));
  default: 
    throw std::runtime_error("Unsupported operation"); 
  }
}

Operand Operand::operator*(const Operand& other) const {
  if(type_ != other.type_) 
    throw std::runtime_error("Unsupported operation * for unequal types"); 

  switch(type_) {
  case VarTypeEnum::num_t: 
    return Operand(std::get<Number>(value_) * std::get<Number>(other.value_));
  default: 
    throw std::runtime_error("Unsupported operation"); 
  }
}

Operand Operand::operator/(const Operand& other) const {
  if(type_ != other.type_) 
    throw std::runtime_error("Unsupported operation / for unequal types"); 

  switch(type_) {
  case VarTypeEnum::num_t: 
    return Operand(std::get<Number>(value_) / std::get<Number>(other.value_));
  default: 
    throw std::runtime_error("Unsupported operation"); 
  }
}

bool Operand::operator==(const Operand& other) const {
  if(type_ != other.type_) {
    //throw std::runtime_error("Unsupported operation == for unequal types"); 
    return false;
  }
  
  //std::cout << "operand cmp==\n";
  switch(type_) {
  case VarTypeEnum::bool_t: 
    return std::get<bool>(value_) == std::get<bool>(other.value_);
  case VarTypeEnum::num_t: 
    return std::get<Number>(value_) == std::get<Number>(other.value_);
  case VarTypeEnum::str_t: 
    return std::get<std::string>(value_) == std::get<std::string>(other.value_);
  case VarTypeEnum::atom_t: 
    return std::get<Atom>(value_) == std::get<Atom>(other.value_);
  case VarTypeEnum::list_t: 
    return list_cmp(other);
  case VarTypeEnum::tuple_t: 
    return list_cmp(other);
  default: 
    throw std::runtime_error("Unsupported operation"); 
  }
}
bool Operand::operator!=(const Operand& other) const {
  if(type_ != other.type_) {
    //throw std::runtime_error("Unsupported operation != for unequal types"); 
    return false;
  }

  switch(type_) {
  case VarTypeEnum::bool_t: 
    return std::get<bool>(value_) != std::get<bool>(other.value_);
  case VarTypeEnum::num_t: 
    return std::get<Number>(value_) != std::get<Number>(other.value_);
  case VarTypeEnum::str_t: 
    return std::get<std::string>(value_) != std::get<std::string>(other.value_);
  case VarTypeEnum::atom_t: 
    return std::get<Atom>(value_) != std::get<Atom>(other.value_);
  case VarTypeEnum::tuple_t: 
    return !list_cmp(other);
  case VarTypeEnum::list_t: 
    return !list_cmp(other);
  default: 
    throw std::runtime_error("Unsupported operation"); 
  }
}

bool Operand::operator>=(const Operand& other) const {
  if(type_ != other.type_) {
    //throw std::runtime_error("Unsupported operation >= for unequal types"); 
    return false;
  }

  switch(type_) {
  case VarTypeEnum::num_t: 
    return std::get<Number>(value_) >= std::get<Number>(other.value_);
  case VarTypeEnum::str_t: 
    return std::get<std::string>(value_) >= std::get<std::string>(other.value_);
  default: 
    throw std::runtime_error("Unsupported operation"); 
  }
}

bool Operand::operator<=(const Operand& other) const {
  if(type_ != other.type_) {
    //throw std::runtime_error("Unsupported operation <= for unequal types"); 
    return false;
  }
  switch(type_) {
  case VarTypeEnum::num_t: 
    return std::get<Number>(value_) <= std::get<Number>(other.value_);
  case VarTypeEnum::str_t: 
    return std::get<std::string>(value_) <= std::get<std::string>(other.value_);
  default: 
    throw std::runtime_error("Unsupported operation"); 
  }
}

bool Operand::operator<(const Operand& other) const {
  if(type_ != other.type_) {
    //throw std::runtime_error("Unsupported operation < for unequal types"); 
    return false;
  }
  switch(type_) {
  case VarTypeEnum::num_t: 
    return std::get<Number>(value_) < std::get<Number>(other.value_);
  case VarTypeEnum::str_t: 
    return std::get<std::string>(value_) < std::get<std::string>(other.value_);
  default: 
    throw std::runtime_error("Unsupported operation"); 
  }
}

bool Operand::operator>(const Operand& other) const {
  if(type_ != other.type_) {
    //throw std::runtime_error("Unsupported operation > for unequal types"); 
    return false;
  }
  switch(type_) {
  case VarTypeEnum::num_t: 
    return std::get<Number>(value_) > std::get<Number>(other.value_);
  case VarTypeEnum::str_t: 
    return std::get<std::string>(value_) > std::get<std::string>(other.value_);
  default: 
    throw std::runtime_error("Unsupported operation"); 
  }
}

Operand Operand::operator!() const {
  switch(type_) {
  case VarTypeEnum::bool_t: 
    return !std::get<bool>(value_);
  case VarTypeEnum::num_t: 
    return !std::get<Number>(value_);
  default: 
    throw std::runtime_error("Unsupported operation"); 
  }
}

Operand Operand::operator&&(const Operand& other) const {
  if(type_ != other.type_) {
    throw std::runtime_error("Unsupported operation && for unequal types"); 
  }

  switch(type_) {
  case VarTypeEnum::bool_t: 
    return std::get<bool>(value_) && std::get<bool>(other.value_);
  case VarTypeEnum::num_t: 
    return std::get<Number>(value_) && std::get<Number>(other.value_);
  default: 
    throw std::runtime_error("Unsupported operation"); 
  }
}

Operand Operand::operator||(const Operand& other) const {
  if(type_ != other.type_)  {
    throw std::runtime_error("Unsupported operation || for unequal types"); 
  }

  switch(type_) {
  case VarTypeEnum::bool_t: 
    return std::get<bool>(value_) || std::get<bool>(other.value_);
  case VarTypeEnum::num_t: 
    return std::get<Number>(value_) || std::get<Number>(other.value_);
  default: 
    throw std::runtime_error("Unsupported operation"); 
  }
}


bool Operand::list_cmp(const Operand& other) const{
  int i, l;
  l = list_.size();
  if(l != other.list_.size()) return false;
  for(i=0; i<l; i++) {
    if(list_[i]!=other.list_[i]) return false; 
  }
  return true;
}


Operand Operand::opfunc(const Operand& other, ast_op op) {
  
  // if(type_ != other.type_) throw std::runtime_error("Unsupported operation > for unequal types"); 

  switch(op){
  case ast_op::plus:  return *this + other;
  case ast_op::minus: return *this - other; 
  case ast_op::mul:   return *this * other; 
  case ast_op::div:   return *this / other;
  case ast_op::eql:
    return *this == other;
  case ast_op::neql:
    return *this != other;
  case ast_op::gt:
    return *this > other;
  case ast_op::lt:
    return *this < other;
  case ast_op::lteq:
    return *this <= other;
  case ast_op::gteq:
    return *this >= other;
  case ast_op::and_:  return *this && other;
  case ast_op::or_:   return *this && other;
  case ast_op::not_:  return *this && other;
  default: 
    return false;
  }
  return false;
}


std::ostream& operator<<(std::ostream& os, const Operand& operand) {
  if(operand.type_ == VarTypeEnum::list_t) {
    Operand::list_print(os, '[', ']', operand);
  } else if(operand.type_ == VarTypeEnum::tuple_t) {
    Operand::list_print(os, '{', '}', operand);
  } else {
    std::visit([&os](const auto& value) { os << value; }, operand.value_);
  }
  return os;
}

void Operand::list_print(std::ostream& os, char b, char e, const Operand& ol) {
  int i;
  os << b;
  for(i=0; i<ol.list_.size()-1; i++) {
    os << ol.list_[i] << ","; 
  }
  os << ol.list_[i] << e;
}

/*
std::ostream& operator<<(std::ostream& os, const std::vector<Operand> operand_vector) {
  std::cout << "operand list: ";
  std::cout << "sizd: " << operand_vector.size() << "\n";

  for(auto operand: operand_vector) {
    std::cout << "operand ele: ";
    std::visit([&os](const auto& value) { os << value; }, operand.value_);
    std::cout << "\n";
  }
  return os;
}*/


void Operand::print_type()  const{
  std::string outstr;
  switch(type_) {
  case VarTypeEnum::bool_t: outstr ="type bool"; break;
  case VarTypeEnum::num_t: outstr ="type num_t"; break;
  case VarTypeEnum::str_t: outstr ="type str_t"; break;
  case VarTypeEnum::atom_t: outstr ="type atom_t"; break;
  case VarTypeEnum::list_t: outstr ="type list_t"; break;
  case VarTypeEnum::ptr_t: outstr ="type ptr_t"; break;
  case VarTypeEnum::user_t: outstr ="type user_t"; break;
  default: outstr ="type unknown"; break;
  }
  std::cout << outstr << "\n";
}