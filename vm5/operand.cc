#include <variant>
#include <string>
#include <stdexcept>
#include <iostream>
#include "operand.hh"


//Operand operand_nil;
std::ostream& operator << (std::ostream& out, const any& a);

Operand::Operand() { type_ = OperandType::nil_t; }
Operand::Operand(bool v) : value_(v) { type_ = OperandType::bool_t; }
Operand::Operand(int v) : value_(Number(v)) { type_ = OperandType::num_t; }
Operand::Operand(float v) : value_(Number(v)) { type_ = OperandType::num_t; }
Operand::Operand(const Number& v) : value_(v) { type_ = OperandType::num_t; }
Operand::Operand(const string& v) : value_(v) { type_ = OperandType::str_t; }
Operand::Operand(const char* v) : value_(string(v)) { type_ = OperandType::str_t; }
/*
Operand::Operand(const char* v)  { 
  printf("operand init char*: %s ", v);
  value_ = move(string(v));
  type_ = OperandType::str_t; 
}
*/

const OperandVariant& Operand::getValue() const { return value_; }

Operand Operand::type_str(OperandType t) {
  string outstr;
  switch(t) {
  case OperandType::nil_t:  outstr ="nil_t"; break;
  case OperandType::type_t:  outstr ="type"; break;
  case OperandType::err_t:  outstr ="err_t"; break;
  case OperandType::bool_t: outstr ="bool"; break;
  case OperandType::num_t:  outstr ="num_t"; break;
  case OperandType::str_t:  outstr ="str_t"; break;
  case OperandType::atom_t: outstr ="atom_t"; break;
  case OperandType::list_t: outstr ="list_t"; break;
  case OperandType::map_t:  outstr ="map_t"; break;
  case OperandType::ast_op_t:  outstr ="ast_opt_t"; break;
  case OperandType::except_t:  outstr ="except_t"; break;
  case OperandType::any_t:  outstr ="any_t"; break;
  default: outstr ="type unknown"; break;
  }
  return Operand(outstr);
}
Operand Operand::ast_op_str(AstOp t_op) {
  std::string oc;

  switch(t_op) {
  case AstOp::noop:  oc="-noop-"; break;
  case AstOp::ast_default:  oc="default"; break;
  case AstOp::ast_else:  oc="else"; break;
  case AstOp::assign:  oc="="; break;
  case AstOp::plus:  oc="+"; break;
  case AstOp::minus: oc="-"; break;
  case AstOp::mul:   oc="*"; break;
  case AstOp::div:   oc="/"; break;
  case AstOp::eql:   oc="=="; break;
  case AstOp::neql:  oc="!="; break;
  case AstOp::gt:    oc=">"; break;
  case AstOp::lt:    oc="<"; break;
  case AstOp::lteq:  oc="<="; break;
  case AstOp::gteq:  oc=">="; break;
  case AstOp::and_:  oc="&&"; break;
  case AstOp::or_:  oc="||"; break;
  case AstOp::not_:  oc="!"; break;
  default: oc="not ast operator"; break;
  } 
  return Operand(oc);
}


Operand Operand::err_str(OperandErrorCode err) {
  string outstr;
  
  switch(err) {
  case OperandErrorCode::invalid_op_t:
    outstr = "invalid operand operation";
    break;
  case OperandErrorCode::unassigned_t:
    outstr = "operand has not been assigned value";
    break;
  case OperandErrorCode::undefined_t:
    outstr = "no such operand. it's undefined";
    break;
  default:
    outstr = "unknown error!";
    break;
  }
  return Operand(outstr);
}

//-----------------------------------------------------------------------
Operand Operand::type_str() const{
  return type_str(type_);
}

Operand Operand::err_str() const {
  if(type_ != OperandType::err_t) {
    return Operand(string(""));
  }
  OperandErrorCode err = get<OperandErrorCode>(value_);
  return err_str(err);
}

Operand Operand::ast_op_str() const {
  if(type_ != OperandType::ast_op_t) {
    return Operand(string(""));
  }
  AstOp op_t = get<AstOp>(value_);
  return ast_op_str(op_t);
}
//-----------------------------------------------------------------------

Operand Operand::whatami() const {
  Operand w = type_str(type_);
  if(type_ == OperandType::err_t) {
    OperandErrorCode err = get<OperandErrorCode>(value_);
    return w +  string(": ") + err_str(err);
  }
  return w;
}

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
  case OperandType::err_t: 
    return std::get<OperandErrorCode>(value_) == std::get<OperandErrorCode>(other.value_);
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

std::ostream& operator<<(std::ostream& os, const Operand& operand) {
  switch(operand.type_) {
  case OperandType::nil_t:   cout << "nil"; break;
  //case OperandType::err_t:   cout << "error operand!"; break;
  case OperandType::err_t:   cout << operand.whatami(); break;
  default: 
    std::visit([&os](const auto& value) { os << value; }, operand.value_);
  }
  return os;
}

std::ostream& operator<<(std::ostream& os, const OperandType& t) {
  cout << Operand::type_str(t);
  return os;
}

std::ostream& operator<<(std::ostream& os, const AstOp& t_op) {
  cout << Operand::ast_op_str(t_op);
  return os;
}
std::ostream& operator<<(std::ostream& os, const OperandErrorCode& err) {
  cout << Operand::err_str(err);
  return os;
}