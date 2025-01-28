#include "lang.hh"
#include "operand.hh"
#include "operand_vars.hh"

#include "ast_node.hh"
#include "ast_list.hh"
#include "ast_map.hh"

#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"

//-----------------------------------------------------------------------
Operand Operand::operator+(const Operand& other) const {
  auto vrptr = _vrptr();
  auto other_vrptr = other._vrptr();

  if(vrptr->type_ != other_vrptr->type_) { 
    cout << "error! " << *this << " + '" << other << "'\n";
    return Operand(OperandErrorCode::invalid_op_t);
  }

  switch(vrptr->type_) {
  case OperandType::num_t:  {
    return  _get_number() + other._get_number();
    //cout << "operator: r" << r << "\n";
    //return r;
  }
  case OperandType::str_t: 
    return Operand(get<std::string>(value_) + get<std::string>(other.value_));
  case OperandType::uptr_t: 
    cout << "operator + uptr_t\n";
    return Operand();
  default: 
    std::cout << "type int: " << static_cast<int>(type_) << "\n";
    throw std::runtime_error("Unsupported operation"); 
  }
}

  // Overload subtraction operator (similar approach)
Operand Operand::operator-(const Operand& other) const {
  auto vrptr = _vrptr();
  auto other_vrptr = other._vrptr();

  if(vrptr->type_ != other_vrptr->type_) { 
    cout << "error! " << *this << " + '" << other << "'\n";
    return Operand(OperandErrorCode::invalid_op_t);
  }

  switch(vrptr->type_) {
  case OperandType::num_t: 
    return _get_number() - other._get_number();
  default: 
    throw std::runtime_error("Unsupported operation"); 
  }
}

Operand Operand::operator*(const Operand& other) const {
  auto vrptr = _vrptr();
  auto other_vrptr = other._vrptr();

  if(vrptr->type_ != other_vrptr->type_) { 
    throw std::runtime_error("Unsupported operation * for unequal types"); 
  }
  switch(vrptr->type_) {
  case OperandType::num_t: 
    return _get_number() * other._get_number();
  default: 
    throw std::runtime_error("Unsupported operation"); 
  }
}

Operand Operand::operator/(const Operand& other) const {
  auto vrptr = _vrptr();
  auto other_vrptr = other._vrptr();

  if(vrptr->type_ != other_vrptr->type_) { 
    throw std::runtime_error("Unsupported operation * for unequal types"); 
  }
  switch(vrptr->type_) {
  case OperandType::num_t:  {
    Number other_num = other._get_number();
    if(other_num==0l) return nil;
    return _get_number() / other_num; }
  default: 
    throw std::runtime_error("Unsupported operation"); 
  }
}
bool Operand::operator==(const AstNode& other) const {
  MYLOGGER(trace_function , "Operand::==(AstNode&)" ,__func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("this.type: ")+ get_type()._to_str()  + string(" -vs- other.type: ") + other.get_type()._to_str(), SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("this : ") + _to_str(), SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("other: ") + other.to_str()._to_str(), SLOG_FUNC_INFO);

  cout << "Operand::==(const AstNode&)\n";
  cout << "this: " << to_str()<<  "\nother: " << other << "\n";
  cout << "type: " << get_type() << ", other_type: " << other.get_type() << "\n\n";

  auto vrptr = _vrptr();
  auto other_vrptr = other._vrptr();

  switch(vrptr->_get_type()) {
  case OperandType::list_t: {
    return vrptr->get_list() == other_vrptr->get_list();
  }
  case OperandType::map_t: {
    return vrptr->get_map() == other_vrptr->get_map();
  }}

  return visit(CmpEql(), vrptr->_get_variant(), other_vrptr->_get_variant());

}

bool Operand::operator==(const Operand& other) const {
  MYLOGGER(trace_function , "Operand::==(operand&)" ,__func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("this.type: ")+ get_type()._to_str()  + string(" -vs- other.type: ") + other.get_type()._to_str(), SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("this : ") + _to_str(), SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("other: ") + other._to_str(), SLOG_FUNC_INFO);

/*
  cout << "Operand::==(const Operand&)\n";
  cout << "this: " << to_str()<<  ", other: " << other << "\n";
  cout << "type: " << get_type() << "other_type: " << other.get_type() << "\n";
*/
  auto result = visit(CmpEql(), value_, other.value_);

  if(result==true) return result;

  auto vrptr  = _vrptr(); auto other_vrptr =  other._vrptr();

//  if(vrptr==nullptr && other_vrptr!=nullptr) return false;
  if(vrptr==nullptr) return false;

  switch(vrptr->_get_type()) {
  case OperandType::list_t: { return vrptr->get_list() == other_vrptr->get_list(); }
  case OperandType::map_t: { return vrptr->get_map() == other_vrptr->get_map();}
  }

  if(other_vrptr==nullptr && vrptr->is_nil()) { return true;}
 // if(other_vrptr==nullptr && vrptr==nullptr) { return true;}
  if(other_vrptr==nullptr) { return false;} // can't compare anything 
  return visit(CmpEql(), vrptr->_get_variant(), other_vrptr->_get_variant());

}

bool Operand::operator==(const astnode_ptr& other) const { 
  cout << "Operand::==(const astnode_ptr)\n";
//  cout << "this: " << to_str()<<  " type: " << get_type() << "\n";
//  cout << "other: " << other << " other type: " << other->get_type() << "\n";
  return visit(CmpEql(), _get_variant(), other->_get_variant());
}

bool Operand::operator!=(const Operand& other) const {
//  cout << "Operand::!=(Operand&)\n";
//  cout << "this: " << to_str()<<  " type: " << get_type() << "\n";
//  cout << "other: " << other << " other type: " << other.get_type() << "\n";
  return !(*this==other);
}


bool Operand::cmp_eql(const AstNode&other) const { 
  MYLOGGER(trace_function , "Operand::cmp_eql(astexpr_u_ptr)", __func__, SLOG_FUNC_INFO);
  cout << "Operand::cmp_eql(astexpr_u_ptr)\n";
  return this->get_operand() == other.get_operand();
}



bool Operand::operator>=(const Operand& other) const {
  auto vrptr = (Operand*) _vrptr();
  auto other_vrptr =(Operand*) other._vrptr();

  if(vrptr->type_ != other_vrptr->type_) { 
    //throw std::runtime_error("Unsupported operation > for unequal types"); 
    return false;
  }

  switch(vrptr->type_) {
  case OperandType::num_t: 
    return vrptr->_get_number() >= other_vrptr->_get_number();
  case OperandType::str_t: 
    return get<std::string>(value_) >= get<std::string>(other.value_);
  default: 
    throw std::runtime_error("Unsupported operation"); 
  }
}

bool Operand::operator<=(const Operand& other) const {
  auto vrptr = (Operand*) _vrptr();
  auto other_vrptr =(Operand*) other._vrptr();

  if(vrptr->type_ != other_vrptr->type_) { 
    //throw std::runtime_error("Unsupported operation > for unequal types"); 
    return false;
  }

  switch(vrptr->type_) {
  case OperandType::num_t: 
    return vrptr->_get_number() <= other_vrptr->_get_number();
  case OperandType::str_t: 
    return get<std::string>(value_) <= get<std::string>(other.value_);
  default: 
    throw std::runtime_error("Unsupported operation"); 
  }
}

bool Operand::operator<(const Operand& other) const {
  auto vrptr = (Operand*) _vrptr();
  auto other_vrptr =(Operand*) other._vrptr();

  if(vrptr->type_ != other_vrptr->type_) { 
    //throw std::runtime_error("Unsupported operation > for unequal types"); 
    return false;
  }

  switch(vrptr->type_) {
  case OperandType::num_t: 
    //return get<Number>(value_) < get<Number>(other.value_);
    return vrptr->_get_number() < other_vrptr->_get_number();
  case OperandType::str_t: 
    return get<std::string>(value_) < get<std::string>(other.value_);
  default: 
    throw std::runtime_error("Unsupported operation"); 
  }
}

bool Operand::operator>(const Operand& other) const {
  //auto type_ = _get_type();
  auto vrptr = (Operand*) _vrptr();
  auto other_vrptr =(Operand*) other._vrptr();

  if(vrptr->type_ != other_vrptr->type_) { 
    //throw std::runtime_error("Unsupported operation > for unequal types"); 
    return false;
  }

  switch(vrptr->type_) {
  case OperandType::num_t: 
    //return get<Number>(value_) > get<Number>(other.value_);
    return vrptr->_get_number() > other_vrptr->_get_number();
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

Operand Operand::opfunc(const AstNode& v, AstOpCode op) {
  MYLOGGER(trace_function, string("Operand::opfunc(") + 
    v.to_str()._to_str()+ string(")") + Operand(op)._to_str() , __func__, SLOG_FUNC_INFO);

  //cout << "Operand::opfunc()\n";
  //cout << "Opcode: " << Operand(op)<< "\n";

  Operand other(v.clone());
  
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


//--------------
template <typename T, typename U> bool Operand::CmpEql::operator()(const T &a, const U &b) {
  MYLOGGER(trace_function , "Operand::CmpEql::()(T, U)" , __func__, SLOG_FUNC_INFO);
//  cout << "T == U?\n";
  return false; 
};
template <typename T> bool Operand::CmpEql::operator()(const T &a, const T &b) { 
  MYLOGGER(trace_function , "Operand::CmpEql::()(T, T)" ,__func__, SLOG_FUNC_INFO);
//  cout << "T == T?\n";
  return a==b; 
};
bool Operand::CmpEql::operator()(const Nil a, const Nil b){ 
  MYLOGGER(trace_function , "Operand::CmpEql::()(Nil, Nil)" ,__func__, SLOG_FUNC_INFO);
//  cout << "nil == nil\n"; 
  return true; 
}
bool Operand::CmpEql::operator()(const AstNode *a, const AstNode *b) {
  cout << "Operand::CmpEql::()(AstNode*, AstNode*)\n"; 
  return visit(CmpEql(), a->_get_variant(), b->_get_variant());
}