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
  case OperandType::num_t: 
    return _get_number() / other._get_number();
  default: 
    throw std::runtime_error("Unsupported operation"); 
  }
}
bool Operand::operator==(const Operand& other) const {
  MYLOGGER(trace_function , "Operand::==(operand&)" ,__func__);
  MYLOGGER_MSG(trace_function, string("this.type: ")+ get_type()._to_str()  + string(" -vs- other.type: ") + other.get_type()._to_str());



/*
  cout << "\nOperand::==(operand&)\n" ;
  cout << "value: " << *this << ", other: " << other << "\n";
  cout << "type: " << get_type() << ", other_type: " << other.get_type() << "\n";
*/

  bool result_b;

  result_b = visit(OperandCmpEql{}, value_, other.value_);
  if(result_b == true) { cout << "result_b is true!\n"; return true; }

  //auto a_ptr = _get_operand_ptr();
  //auto b_ptr = other._get_operand_ptr();
  auto a_ptr = get_raw_ptr();
  auto b_ptr = other.get_raw_ptr();



/*

  cout << "*a_ptr: " << *a_ptr << "\n";
  cout << "*b_ptr: " << *b_ptr << "\n";
  cout << "a_ptr->gettype(): " << a_ptr->get_type() << "\n";
  cout << "b_ptr->gettype(): " << b_ptr->get_type() << "\n";
*/
//  cout << "a_ptr->value(): " << a_ptr->getv() << "\n";
  // cout << "b_ptr->value(): " << b_ptr->getv() << "\n";
  switch(type_) {
  case OperandType::ptr_t:
  case OperandType::uptr_t:
  case OperandType::sptr_t:{
    switch(other.type_) {
    case OperandType::ptr_t:
    case OperandType::uptr_t:
    case OperandType::sptr_t:
      cout << "*a_ptr == *b_ptr?\n";
      result_b = *a_ptr == *b_ptr;
      if(result_b == true) { cout << "result_b is true!\n"; return true; }
      cout << "false!\n";
      return false;

      //return visit(OperandCmpEql{}, a_ptr->value_, b_ptr->value_);
    case OperandType::nil_t:
      if(a_ptr->is_nil()) return true;
    default:
      cout << "*a_ptr == other?\n";
      result_b = *a_ptr == other;
      if(result_b == true) { cout << "result_b is true!\n"; return true; }
      cout << "false!\n";
      return false;

      //return visit(OperandCmpEql{}, a_ptr->value_, other.value_ );
    }}
  case OperandType::nil_t:
    if(b_ptr->is_nil()) return true;
  default:
    //cout << "this->value= = b_ptr->variant() ?\n";
    cout << "revisit a  == b\n";
    result_b = visit(OperandCmpEql{}, value_, other.value_);
    if(result_b == true) { cout << "result_b is true!\n"; return true; }
    cout << "false!\n";
    return false;
    //return visit(OperandCmpEql{}, this->value_, other.value_);
  }

  if(a_ptr == nullptr || b_ptr==nullptr) return false;
  if(a_ptr->is_nil() || b_ptr->is_nil()) return false;

  result_b = *a_ptr == *b_ptr;
  if(result_b == true) { cout << "result_b is true!\n"; return true; }
  cout << "false!\n";
  return false;


//  return false;
  //auto rb = visit(OperandCmpEql{}, *_get_list_ptr(), *other._get_list_ptr());
  //return visit(OperandCmpEql{}, _get_value(), other._get_value());
}

/*
bool Operand::operator==(const Operand& other) const {
  MYLOGGER(trace_function , "Operand::==(operand&)" ,__func__);
  std::cout << "operand==(operand&)\n";
  cout << "*this: " << *this <<  " type: " << get_type() << "\n";
  cout << "other: " << other << " other type: " << other.get_type() << "\n";
  cout << "getv(): " << getv() << "\n";
  cout << "other.getv(): " << other.getv() << "\n";

  auto other_type = other._get_type();

  if(type_ != other_type) {
    if(other_type == OperandType::nil_t) return visit(OperandCmpEql{}, _get_value(), other.value_);
    if(type_ == OperandType::nil_t) return visit(OperandCmpEql{}, value_,  other._get_value() );
    //if(other_type == OperandType::nil_t) return false;
    //if(type_ == OperandType::nil_t) return false;
    return visit(OperandCmpEql{}, _get_value(), other._get_value());
  }
  return visit(OperandCmpEql{}, value_, other.value_);
  
  switch(type_) {
  case OperandType::bool_t: 
    return get<bool>(value_) == get<bool>(other.value_);
  case OperandType::num_t: 
    return get<Number>(value_) == get<Number>(other.value_);
  case OperandType::type_t: 
    return get<OperandType>(value_) == get<OperandType>(other.value_);
  case OperandType::str_t: 
    return get<std::string>(value_) == get<std::string>(other.value_);
  case OperandType::nil_t: {
    if(other.type_ == OperandType::nil_t) return true;
    return false;
  }
  case OperandType::list_t: {
    cout << "OperandType::list ==\n";
  }
  case OperandType::err_t: 
    return get<OperandErrorCode>(value_) == get<OperandErrorCode>(other.value_);
  default: 
    throw std::runtime_error("Unsupported operation"); 
  }

}
*/

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



bool Operand::operator==(const AstExpr &other) const { 
  cout << "Operand::==(AstExpr&)\n";
  //return cmp_eql(other);
  auto a_ptr = _get_operand_ptr();
  auto b_ptr = other._get_operand_ptr();
  if(a_ptr==nullptr){
    if(b_ptr==nullptr) return true;
    return false;
  }
  //return *_get_operand_ptr() == *other._get_operand_ptr();
  return *a_ptr == *b_ptr;
}
bool Operand::operator!=(const AstExpr &other) const { 
  cout << "Operand::!=(astexpr_u_ptr)\n";
  return !cmp_eql(other);
}

bool Operand::cmp_eql(const AstExpr&other) const { 
  MYLOGGER(trace_function , "Operand::cmp_eql(astexpr_u_ptr)", __func__);
  cout << "Operand::cmp_eql(astexpr_u_ptr)\n";
  return this->getv() == other.getv();
}

//--------------
template <typename T, typename U> bool OperandCmpEql::operator()(const T &a, const U &b) {
  MYLOGGER(trace_function , "OperandCmpEql::()(T, U)" , __func__);
//  cout << "T == U?\n";
  return false; 
};
template <typename T> bool OperandCmpEql::operator()(const T &a, const T &b) { 
  MYLOGGER(trace_function , "OperandCmpEql::()(T, T)" ,__func__);
//  cout << "T == T?\n";
  return a==b; 
};
bool OperandCmpEql::operator()(const Nil a, const Nil b){ 
  MYLOGGER(trace_function , "OperandCmpEql::()(Nil, Nil)" ,__func__);
//  cout << "nil == nil\n"; 
  return true; 
}