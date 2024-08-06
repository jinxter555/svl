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
Operand::Operand(const Tuple &value) : value_(value) { type_ = VarTypeEnum::tuple_t; }
Operand::Operand(const std::string& value) : value_(value) { type_ = VarTypeEnum::str_t; }

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
  case VarTypeEnum::tuple_t: 
    //return std::get<Tuple>(value_) == std::get<Tuple>(other.value_);
    std::cout << "operand tuple cmp ==\n";
    return false;
  default: 
    throw std::runtime_error("Unsupported operation"); 
  }
}
bool Operand::operator!=(const Operand& other) const {
  if(type_ != other.type_) 
    throw std::runtime_error("Unsupported operation != for unequal types"); 
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
    //return std::get<Tuple>(value_) != std::get<Tuple>(other.value_);
    return false;
  default: 
    throw std::runtime_error("Unsupported operation"); 
  }
}

bool Operand::operator>=(const Operand& other) const {
  if(type_ != other.type_) 
    throw std::runtime_error("Unsupported operation >= for unequal types"); 
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
  if(type_ != other.type_) 
    throw std::runtime_error("Unsupported operation <= for unequal types"); 
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
  if(type_ != other.type_) 
    throw std::runtime_error("Unsupported operation < for unequal types"); 
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
  if(type_ != other.type_) 
    throw std::runtime_error("Unsupported operation > for unequal types"); 
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
  if(type_ != other.type_) 
    throw std::runtime_error("Unsupported operation && for unequal types"); 

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
    std::cout << "self type: "; print_type(); 
    std::cout << ",other type: "; other.print_type();

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


bool Operand::bin_op(const Operand& other, ast_op op) const {
  
  if(type_ != other.type_) 
    throw std::runtime_error("Unsupported operation > for unequal types"); 

  switch(op){
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
  default: 
    return false;
  }
  return false;
}


std::ostream& operator<<(std::ostream& os, const Operand& operand) {
  std::visit([&os](const auto& value) { os << value; }, operand.value_);
  return os;
}

void Operand::print_type()  const{
  std::string outstr;
  switch(type_) {
  case VarTypeEnum::bool_t: outstr ="type bool"; break;
  case VarTypeEnum::num_t: outstr ="type num_t"; break;
  case VarTypeEnum::str_t: outstr ="type str_t"; break;
  case VarTypeEnum::atom_t: outstr ="type atom_t"; break;
  case VarTypeEnum::tuple_t: outstr ="type tuple_t"; break;
  case VarTypeEnum::ptr_t: outstr ="type ptr_t"; break;
  case VarTypeEnum::user_t: outstr ="type user_t"; break;
  default: outstr ="type unknown"; break;
  }
  std::cout << outstr << "\n";
}