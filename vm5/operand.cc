#include <variant>
#include <string>
#include <stdexcept>
#include <iostream>
#include "operand.hh"

Operand operand_nil;

Operand::Operand() { type_ = OperandType::nil_t; }
Operand::Operand(bool v) : value_(v) { type_ = OperandType::bool_t; }
Operand::Operand(int v) : value_(Number(v)) { type_ = OperandType::num_t; }
Operand::Operand(float v) : value_(Number(v)) { type_ = OperandType::num_t; }
Operand::Operand(const Number& v) : value_(v) { type_ = OperandType::num_t; }
Operand::Operand(const string& v) : value_(v) { type_ = OperandType::str_t; }
Operand::Operand(const char* v) : value_(string(v)) { type_ = OperandType::str_t; }

const OperandVariant& Operand::getValue() const { return value_; }




Operand Operand::operator+(const Operand& other) const {
  if(type_ != other.type_) { 
    cout << "error! " << *this << " + " << other << "\n";
    throw std::runtime_error("Unsupported operation + for unequal types"); 
    return Operand(OperandType::invalid_op_t);
  }

  switch(type_) {
  case OperandType::num_t: 
    return Operand(std::get<Number>(value_) + std::get<Number>(other.value_));
  case OperandType::str_t: 
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
  case OperandType::num_t: 
    return Operand(std::get<Number>(value_) - std::get<Number>(other.value_));
  default: 
    throw std::runtime_error("Unsupported operation"); 
  }
}

Operand Operand::operator*(const Operand& other) const {
  if(type_ != other.type_) 
    throw std::runtime_error("Unsupported operation * for unequal types"); 

  switch(type_) {
  case OperandType::num_t: 
    return Operand(std::get<Number>(value_) * std::get<Number>(other.value_));
  default: 
    throw std::runtime_error("Unsupported operation"); 
  }
}

Operand Operand::operator/(const Operand& other) const {
  if(type_ != other.type_) 
    throw std::runtime_error("Unsupported operation / for unequal types"); 

  switch(type_) {
  case OperandType::num_t: 
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
  case OperandType::bool_t: 
    return std::get<bool>(value_) == std::get<bool>(other.value_);
  case OperandType::num_t: 
    return std::get<Number>(value_) == std::get<Number>(other.value_);
  case OperandType::str_t: 
    return std::get<std::string>(value_) == std::get<std::string>(other.value_);
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
  case OperandType::bool_t: 
    return std::get<bool>(value_) != std::get<bool>(other.value_);
  case OperandType::num_t: 
    return std::get<Number>(value_) != std::get<Number>(other.value_);
  case OperandType::str_t: 
    return std::get<std::string>(value_) != std::get<std::string>(other.value_);
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
  case OperandType::num_t: 
    return std::get<Number>(value_) >= std::get<Number>(other.value_);
  case OperandType::str_t: 
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
  case OperandType::num_t: 
    return std::get<Number>(value_) <= std::get<Number>(other.value_);
  case OperandType::str_t: 
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
  case OperandType::num_t: 
    return std::get<Number>(value_) < std::get<Number>(other.value_);
  case OperandType::str_t: 
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
  case OperandType::num_t: 
    return std::get<Number>(value_) > std::get<Number>(other.value_);
  case OperandType::str_t: 
    return std::get<std::string>(value_) > std::get<std::string>(other.value_);
  default: 
    throw std::runtime_error("Unsupported operation"); 
  }
}

Operand Operand::operator!() const {
  switch(type_) {
  case OperandType::bool_t: 
    return !std::get<bool>(value_);
  case OperandType::num_t: 
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
  case OperandType::bool_t: 
    return std::get<bool>(value_) && std::get<bool>(other.value_);
  case OperandType::num_t: 
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
  case OperandType::bool_t: 
    return std::get<bool>(value_) || std::get<bool>(other.value_);
  case OperandType::num_t: 
    return std::get<Number>(value_) || std::get<Number>(other.value_);
  default: 
    throw std::runtime_error("Unsupported operation"); 
  }
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
  switch(operand.type_) {
  case OperandType::nil_t:          cout << "nil"; break;
  case OperandType::invalid_op_t:   cout << "invalid operation on operand!"; break;
  case OperandType::unassigned_t:   cout << "operand unassigned!"; break;
  default: 
    std::visit([&os](const auto& value) { os << value; }, operand.value_);
  }
  return os;
}

std::ostream& operator<<(std::ostream& os, const OperandType& t) {
  switch(t) {
  case OperandType::nil_t:          cout << "nil"; break;
  case OperandType::invalid_op_t:   cout << "invalid operation on operand!"; break;
  case OperandType::unassigned_t:   cout << "operand unassigned!"; break;
  case OperandType::num_t:   cout << "num_t"; break;
  case OperandType::str_t:   cout << "str_t"; break;
  case OperandType::bool_t:   cout << "bool_t"; break;
  default: cout << "unknown operand type!"; break; 
  }
  return os;
}

std::ostream& operator<<(std::ostream& os, const ast_op& t_op) {
  std::string oc;
  switch(t_op) {
  case ast_op::noop:  oc="-noop-"; break;
  case ast_op::ast_default:  oc="default"; break;
  case ast_op::ast_else:  oc="else"; break;
  case ast_op::assign:  oc="="; break;
  case ast_op::plus:  oc="+"; break;
  case ast_op::minus: oc="-"; break;
  case ast_op::mul:   oc="*"; break;
  case ast_op::div:   oc="/"; break;
  case ast_op::eql:   oc="=="; break;
  case ast_op::neql:  oc="!="; break;
  case ast_op::gt:    oc=">"; break;
  case ast_op::lt:    oc="<"; break;
  case ast_op::lteq:  oc="<="; break;
  case ast_op::gteq:  oc=">="; break;
  case ast_op::and_:  oc="&&"; break;
  case ast_op::or_:  oc="||"; break;
  case ast_op::not_:  oc="!"; break;
  default: oc="out wrong type"; break; } 
  std::cout << oc ; 
  return os;

}

void Operand::print_type()  const{
  std::string outstr;

  switch(type_) {
  case OperandType::bool_t: outstr ="type bool"; break;
  case OperandType::num_t: outstr ="type num_t"; break;
  case OperandType::str_t: outstr ="type str_t"; break;
  case OperandType::atom_t: outstr ="type atom_t"; break;
  case OperandType::list_t: outstr ="type list_t"; break;
  case OperandType::map_t: outstr ="type map_t"; break;
  case OperandType::ptr_t: outstr ="type ptr_t"; break;
  case OperandType::user_t: outstr ="type user_t"; break;
  default: outstr ="type unknown"; break;
  }
  std::cout << outstr << "\n";
}