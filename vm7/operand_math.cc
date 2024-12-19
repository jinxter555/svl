#include "operand.hh"
//#include "entity.hh"
#include "ast.hh"


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
  std::cout << "operand==(operand&)\n";
  cout << "*this: " << *this <<  " type: " << get_type() << "\n";
  cout << "other: " << other << " other type: " << other.get_type() << "\n";

  //auto type_ = _get_type(); auto other_type_ = other._get_type();
  if(type_ != other._get_type()) {
    //throw std::runtime_error("Unsupported operation == for unequal types"); 
    return false;
  }
  
  switch(type_) {
  case OperandType::bool_t: 
    return get<bool>(value_) == get<bool>(other.value_);
  case OperandType::num_t: 
    return get<Number>(value_) == get<Number>(other.value_);
  case OperandType::type_t: 
    return get<OperandType>(value_) == get<OperandType>(other.value_);
  case OperandType::str_t: 
    return get<std::string>(value_) == get<std::string>(other.value_);
  case OperandType::nil_t: 
    //if( holds_alternative<Nil>(value_) && holds_alternative<Nil>(other.value_)) return true;
    if(other.type_ == OperandType::nil_t) return true;
    return false;
  case OperandType::uptr_t:  {
    cout << "\ntype_ :uptr_t, ==\n";
    auto &lv = get_u_ptr();
    auto &rv = other.get_u_ptr();
    cout << "lv->gettype: " << lv->get_type() << " rv->gettype: " << rv->get_type() << "\n";
    cout << lv << "==" << rv << "\n";

    if(rv->_get_type() == OperandType::uptr_t
    || rv->_get_type() == OperandType::list_t 
    || rv->_get_type() == OperandType::map_t)  {
//      lv->print();
//      rv->print();
      cout << "lv==rv\n";
      return lv->cmp_eql(rv);
    }
    return lv->getv() ==  rv->getv();
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

Operand Operand::opfunc(const Operand& other, AstOpCode op) {
  
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



struct OperandCmpEql {
   template <typename T, typename U> bool operator()(const T a, T b) const { return a == b; };
  template <typename T, typename U> bool operator()(const T a, U b) const { return false; }
  bool operator()(const astexpr_u_ptr &a, astexpr_u_ptr &b) { 
    return true;

  };
};

bool Operand::operator==(const astexpr_u_ptr &other_vptr) const { 
  //visit(OperandCmpEql(), value_, other_vptr->value_);
  cout << "Operand::==(astexpr_u_ptr)\n";
  return true;
}
bool Operand::operator!=(const astexpr_u_ptr &other_vptr) const { 
  cout << "Operand::!=(astexpr_u_ptr)\n";
  return false; 
}
bool Operand::cmp_eql(const astexpr_u_ptr &other_vptr) const { 
  cout << "Operand::cmp_eql(astexpr_u_ptr)\n";
  return true; 
}