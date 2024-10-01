#include "operand.hh"
#include "entity.hh"

//-----------------------------------------------------------------------
Operand Operand::operator+(const Operand& other) const {
  if(type_ != other.type_) { 
    cout << "error! " << *this << " + '" << other << "'\n";
    return Operand(OperandErrorCode::invalid_op_t);
    /*
    throw std::runtime_error("Unsupported operation + for unequal types"); 
    return Operand(OperandType::err_t);
    */
  }

  switch(type_) {
  case OperandType::num_t: 
    return Operand(get<Number>(value_) + get<Number>(other.value_));
  case OperandType::str_t: 
    return Operand(get<std::string>(value_) + get<std::string>(other.value_));
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
    return Operand(get<Number>(value_) - get<Number>(other.value_));
  default: 
    throw std::runtime_error("Unsupported operation"); 
  }
}

Operand Operand::operator*(const Operand& other) const {
  if(type_ != other.type_) 
    throw std::runtime_error("Unsupported operation * for unequal types"); 

  switch(type_) {
  case OperandType::num_t: 
    return Operand(get<Number>(value_) * get<Number>(other.value_));
  default: 
    throw std::runtime_error("Unsupported operation"); 
  }
}

Operand Operand::operator/(const Operand& other) const {
  if(type_ != other.type_) 
    throw std::runtime_error("Unsupported operation / for unequal types"); 

  switch(type_) {
  case OperandType::num_t: 
    return Operand(get<Number>(value_) / get<Number>(other.value_));
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
    return get<bool>(value_) == get<bool>(other.value_);
  case OperandType::num_t: 
    return get<Number>(value_) == get<Number>(other.value_);
  case OperandType::str_t: 
    return get<std::string>(value_) == get<std::string>(other.value_);
  case OperandType::err_t: 
    return get<OperandErrorCode>(value_) == get<OperandErrorCode>(other.value_);
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
    return get<bool>(value_) != get<bool>(other.value_);
  case OperandType::num_t: 
    return get<Number>(value_) != get<Number>(other.value_);
  case OperandType::str_t: 
    return get<std::string>(value_) != get<std::string>(other.value_);
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
    return get<Number>(value_) >= get<Number>(other.value_);
  case OperandType::str_t: 
    return get<std::string>(value_) >= get<std::string>(other.value_);
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
    return get<Number>(value_) <= get<Number>(other.value_);
  case OperandType::str_t: 
    return get<std::string>(value_) <= get<std::string>(other.value_);
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
    return get<Number>(value_) < get<Number>(other.value_);
  case OperandType::str_t: 
    return get<std::string>(value_) < get<std::string>(other.value_);
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
    return get<Number>(value_) > get<Number>(other.value_);
  case OperandType::str_t: 
    return get<std::string>(value_) > get<std::string>(other.value_);
  default: 
    throw std::runtime_error("Unsupported operation"); 
  }
}

Operand Operand::operator!() const {
  switch(type_) {
  case OperandType::bool_t: 
    return !get<bool>(value_);
  case OperandType::num_t: 
    return !get<Number>(value_);
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
    return get<bool>(value_) && get<bool>(other.value_);
  case OperandType::num_t: 
    return get<Number>(value_) && get<Number>(other.value_);
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
    return get<bool>(value_) || get<bool>(other.value_);
  case OperandType::num_t: 
    return get<Number>(value_) || get<Number>(other.value_);
  default: 
    throw std::runtime_error("Unsupported operation"); 
  }
}

Operand Operand::opfunc(const Operand& other, AstOp op) {
  
  // if(type_ != other.type_) throw std::runtime_error("Unsupported operation > for unequal types"); 

  switch(op){
  case AstOp::plus:  return *this + other;
  case AstOp::minus: return *this - other; 
  case AstOp::mul:   return *this * other; 
  case AstOp::div:   return *this / other;
  case AstOp::eql:
    return *this == other;
  case AstOp::neql:
    return *this != other;
  case AstOp::gt:
    return *this > other;
  case AstOp::lt:
    return *this < other;
  case AstOp::lteq:
    return *this <= other;
  case AstOp::gteq:
    return *this >= other;
  case AstOp::and_:  return *this && other;
  case AstOp::or_:   return *this && other;
  case AstOp::not_:  return *this && other;
  default: 
    return false;
  }
  return false;
}