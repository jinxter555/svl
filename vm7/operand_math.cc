#include "lang.hh"
#include "operand.hh"
//#include "entity.hh"
#include "ast.hh"
#include "ast_list.hh"
#include "ast_map.hh"

#define DEBUG_TRACE_FUNC
#include "scope_logger.hh"

//-----------------------------------------------------------------------
Operand Operand::operator+(const Operand& other) const {
  auto type_ = _get_type();
  auto other_type_ = other._get_type();

  if(type_ != other_type_) { 
    cout << "error! " << *this << " + '" << other << "'\n";
    return Operand(OperandErrorCode::invalid_op_t);
  }

  switch(type_) {
  case OperandType::num_t:  {
    return  _get_number() + other._get_number();
    //cout << "operator: r" << r << "\n";
    //return r;
  }
  case OperandType::str_t: 
    return Operand(get<std::string>(value_) + get<std::string>(other.value_));
  case OperandType::uptr_t: 
    cout << "operator+ uptr_t\n";
    return Operand();
  default: 
    std::cout << "type int: " << static_cast<int>(type_) << "\n";
    throw std::runtime_error("Unsupported operation"); 
  }
}

  // Overload subtraction operator (similar approach)
Operand Operand::operator-(const Operand& other) const {
  auto type_ = _get_type();
  auto other_type_ = other._get_type();

  if(type_ != other_type_) 
    throw std::runtime_error("Unsupported operation + for unequal types"); 

  switch(type_) {
  case OperandType::num_t: 
    return _get_number() - other._get_number();
  default: 
    throw std::runtime_error("Unsupported operation"); 
  }
}

Operand Operand::operator*(const Operand& other) const {
  auto type_ = _get_type();
  auto other_type_ = other._get_type();

  if(type_ != other_type_)  {
    //cout << "this get_type: " << get_type() << "\n"; cout << "other get_type: " << other.get_type() << "\n";
    throw std::runtime_error("Unsupported operation * for unequal types"); 
  }

  switch(type_) {
  case OperandType::num_t: 
    return _get_number() * other._get_number();
  default: 
    throw std::runtime_error("Unsupported operation"); 
  }
}

Operand Operand::operator/(const Operand& other) const {
  auto type_ = _get_type();
  auto other_type_ = other._get_type();
  if(type_ != other_type_) 
    throw std::runtime_error("Unsupported operation / for unequal types"); 

  switch(type_) {
  case OperandType::num_t:  {
    Number other_num = other._get_number();
    if(other_num==0l) return nil;
    return _get_number() / other_num;
  }
  default: 
    throw std::runtime_error("Unsupported operation"); 
  }
}
bool Operand::operator==(const AstExpr& other) const {
  MYLOGGER(trace_function , "Operand::==(AstExpr&)" ,__func__);
  MYLOGGER_MSG(trace_function, string("this.type: ")+ get_type()._to_str()  + string(" -vs- other.type: ") + other.get_type()._to_str());

/*
  cout << "Operand::==(const AstExpr&)\n";
  cout << "this: " << to_str()<<  ", other: " << other << "\n";
  cout << "type: " << get_type() << "other_type: " << other.get_type() << "\n";
*/

  return visit(OperandCmpEql(), value_, other._get_variant());

}

bool Operand::operator==(const Operand& other) const {
  MYLOGGER(trace_function , "Operand::==(operand&)" ,__func__);
  MYLOGGER_MSG(trace_function, string("this.type: ")+ get_type()._to_str()  + string(" -vs- other.type: ") + other.get_type()._to_str());

/*
  cout << "Operand::==(const Operand&)\n";
  cout << "this: " << to_str()<<  ", other: " << other << "\n";
  cout << "type: " << get_type() << "other_type: " << other.get_type() << "\n";
*/

  auto result = visit(OperandCmpEql(), value_, other.value_);

  if(result==true) return result;
  auto a = get_raw_ptr(); auto b =  other.get_raw_ptr();
  return *a == *b;



}

bool Operand::operator==(const astexpr_ptr other) const { 
  cout << "Operand::==(const astexpr_ptr)\n";

/*
  cout << "this: " << to_str()<<  " type: " << get_type() << "\n";
  cout << "other: " << other << " other type: " << other->get_type() << "\n";
*/
  return visit(OperandCmpEql(), _get_variant(), other->_get_variant());

}

bool Operand::operator!=(const Operand& other) const {
  cout << "Operand::!=(Operand&)\n";
  return !(*this==other);
}

bool Operand::operator>=(const Operand& other) const {
  auto type_ = _get_type();
  auto other_type_ = other._get_type();
  if(type_ != other_type_) {
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
  auto type_ = _get_type();
  auto other_type_ = other._get_type();
  if(type_ != other_type_) {
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
  auto type_ = _get_type();
  auto other_type_ = other._get_type();
  if(type_ != other_type_) {
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
  auto type_ = _get_type();
  auto other_type_ = other._get_type();
  if(type_ != other_type_) {
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
  auto type_ = _get_type();
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
  auto type_ = _get_type();
  auto other_type_ = other._get_type();

  if(type_ != other_type_) {
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
  auto type_ = _get_type();
  auto other_type_ = other._get_type();

  if(type_ != other_type_)  {
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

Operand Operand::opfunc(const AstExpr& v, AstOpCode op) {
  cout << "Operand::opfunc()\n";
  cout << "Opcode: " << Operand(op)<< "\n";
  Operand other(v.clone_val());
  
  // if(type_ != other.type_) throw std::runtime_error("Unsupported operation > for unequal types"); 

  switch(op){
  case AstOpCode::plus:   return *this + other;
  case AstOpCode::minus:  return *this - other; 
  case AstOpCode::mul:    return *this * other; 
  case AstOpCode::div:    return *this / other;
  case AstOpCode::eql:    return *this == other;
  case AstOpCode::neql:   return *this != other;
  case AstOpCode::gt:     return *this > other;
  case AstOpCode::lt:     return *this < other;
  case AstOpCode::lteq:   return *this <= other;
  case AstOpCode::gteq:   return *this >= other;
  case AstOpCode::and_:   return *this && other;
  case AstOpCode::or_:    return *this && other;
  case AstOpCode::not_:   return *this && other;
  default:                return false;
  }
  return false;
}





bool Operand::operator!=(const AstExpr &other) const { 
  cout << "Operand::!=(astexpr_u_ptr)\n";
  return !cmp_eql(other);
}

bool Operand::cmp_eql(const AstExpr&other) const { 
  MYLOGGER(trace_function , "Operand::cmp_eql(astexpr_u_ptr)", __func__);
  cout << "Operand::cmp_eql(astexpr_u_ptr)\n";
  return this->_get_value() == other._get_value();
}

//--------------
template <typename T, typename U> bool OperandCmpEql::operator()(const T &a, const U &b) {
  MYLOGGER(trace_function , "OperandCmpEql::()(T, U)" , __func__);
  //cout << "T == U?\n";
  return false; 
};
template <typename T> bool OperandCmpEql::operator()(const T &a, const T &b) { 
  MYLOGGER(trace_function , "OperandCmpEql::()(T, T)" ,__func__);
  //cout << "T == T?\n";
  return a==b; 
};
bool OperandCmpEql::operator()(const Nil a, const Nil b){ 
  MYLOGGER(trace_function , "OperandCmpEql::()(Nil, Nil)" ,__func__);
  //cout << "nil == nil\n"; 
  return true; 
}
bool OperandCmpEql::operator()(const AstExpr *a, const AstExpr *b) {
  cout << "OperandCmpEql::()(AstExpr*, AstExpr*)\n"; 
  return visit(OperandCmpEql(), a->_get_variant(), b->_get_variant());
}