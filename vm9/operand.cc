#include <iostream>
#include <stdexcept>
#include "operand.hh"
#include "ast_list.hh"
#include "ast_map.hh"

//#include "operand_vars.hh"
//#define TO_STR(m) ((Operand::ToString *) this)->Operand::ToString::operator()(m);

#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"



extern const Nil nil={};
extern const Operand nil_operand=Operand();
//extern const list_t nil_list = {};
extern const AstList nil_list = AstList();
extern const AstMap nil_map = AstMap();
extern const int i_var =123;
extern const astnode_u_ptr nil_ast_ptr=nullptr;
extern const operand_u_ptr nil_operand_ptr=nullptr;
operand_u_ptr nil_operand_ptr_nc=nullptr;
Operand nil_operand_nc=Operand();



ostream& operator<<(ostream& os, const Operand& v);

Operand::Operand()                  : AstNode(OperandType::nil_t),  value_(nil) {}
Operand::Operand(const Nil&n)       : AstNode(OperandType::nil_t), value_(nil) {}
Operand::Operand(const s_float v)   : AstNode(OperandType::num_t),  value_(v) {}
Operand::Operand(const s_integer v) : AstNode(OperandType::num_t), value_(v) {}
Operand::Operand(const Number& v)   : AstNode(OperandType::num_t), value_(v) {}
Operand::Operand(const char*v)      : AstNode(OperandType::str_t), value_(string(v)) {}
Operand::Operand(const string& v)   : AstNode(OperandType::str_t), value_(v) {}
Operand::Operand(const bool v)      : AstNode(OperandType::bool_t), value_(v) {}
Operand::Operand(const OperandType &v)        : AstNode(OperandType::type_t), value_(v){}
Operand::Operand(const AstOpCode& v)          : AstNode(OperandType::ast_op_t), value_(v) {}
Operand::Operand(const OperandErrorCode &v)   : AstNode(OperandType::err_t),    value_(v) {}
Operand::Operand(const OperandStatusCode &v)  : AstNode(OperandType::status_t), value_(v) {}
Operand::Operand(const ControlFlow &v )       : AstNode(OperandType::control_t), value_(v) {}
Operand::Operand(astnode_u_ptr&&v )           : AstNode(OperandType::uptr_t), value_(move(v)) {}
//Operand::Operand(const astnode_s_ptr&v )      : AstNode(OperandType::sptr_t), value_(v) {}
Operand::Operand(const astnode_ptr  v)      : AstNode(OperandType::ptr_t), value_(v) {}

//Operand::Operand(const astnode_u_ptr&v )      : AstNode(OperandType::ast_uptr_t), value_(move(v->clone())) {}
//------------------------------------ vec 
Operand::Operand(const vec_num_t& l) {
  type_ = OperandType::uptr_t;
  auto  new_list = make_unique<AstList>();
  for(auto e: l) new_list->add(make_unique<Operand>(e));
  astnode_u_ptr ptr = move(new_list);
  value_ = move(ptr);
}
Operand::Operand(const vec_str_t& l) {
  type_ = OperandType::uptr_t;
  auto  new_list = make_unique<AstList>();
  for(auto e: l) new_list->add( make_unique<Operand>(e));
  astnode_u_ptr ptr = move(new_list);
  value_ = move(ptr);
}
Operand::Operand(const list_t& l) {
  type_ = OperandType::uptr_t;
  auto  new_list = make_unique<AstList>();
  for(auto &e: l) new_list->add( e.clone());
  astnode_u_ptr ptr = move(new_list);
  value_ = move(ptr);
}
Operand::Operand(const map_t& m) {
  type_ = OperandType::uptr_t;
  auto  new_map= make_unique<AstMap>();
   for (auto const& [key, val] : m) {                                                                                                                                        
    (*new_map)[key] = val.clone();                                                                                                                                          
   }                                                                                                                                                                            
  astnode_u_ptr ptr = move(new_map);
  value_ = move(ptr);
}

Operand::Operand(const operand_variant_t& v ) {
  //type_ = visit(Type(), v);
  //value_ = visit(Variant(), v); 
} 

Operand Operand::evaluate(unique_ptr<AstNode>&ctxt) { 
  MYLOGGER(trace_function , "Operand::evaluate()" , __func__, SLOG_FUNC_INFO);
  return _get_variant();
}
//------------------------------------ add() s
bool Operand::add(astnode_u_ptr &&vptr) {
  return false;
}

//------------------------------------ Clone() s
astnode_u_ptr Operand::_uptr() { 
  MYLOGGER(trace_function , "Operand::_uptr()" , __func__, SLOG_FUNC_INFO);
  if(holds_alternative<astnode_u_ptr>(value_))  {
    auto vptr = move(get<astnode_u_ptr>(value_));
    value_ = nil;
    type_ = OperandType::nil_t;
    return move(vptr); 
  }
  return nullptr;
}

//------------------------------------ Clone() s
astnode_u_ptr Operand::clone() const { return visit(Clone{}, value_); }
//unique_ptr<Operand> Operand::clone_operand() const { return visit(Clone{}, value_); }

//------------------------------------
Operand Operand::get_type() const { return _get_type(); }
//Operand     Operand::get_opcode()     const { return _get_opcode(); }
//---------------------------  
OperandType Operand::_get_type() const { return type_; };
//AstOpCode   Operand::_get_opcode()    const { return visit(OpCode{}, value_); }
//------------------------------------
const Operand& Operand::get_value() const {
  return get_operand();
}

const Operand& Operand::get_operand() const {
  switch(type_) {
  case OperandType::ptr_t:
  case OperandType::uptr_t:
  case OperandType::sptr_t:{
    auto vptr =(Operand*) _vrptr();
    return vptr->get_operand();
  }}
  return *this;
}

const AstNode& Operand::get_node() const { return get_operand(); }
const AstList& Operand::get_list() const {
  auto vptr = _vrptr();
  if(vptr->_get_type() != OperandType::list_t) return nil_list;
  return _vrptr()->get_list();
};

const AstMap& Operand::get_map() const {
  auto vptr = _vrptr();
  //if(vptr->_get_type() != OperandType::map_t) return nil_map;
  return _vrptr()->get_map();
};

const Operand* Operand::get_operand_ptr() const {
  return (Operand*)_vrptr();
}
const AstList* Operand::get_list_ptr() const {
  auto vptr = _vrptr();
  if(vptr->_get_type()== OperandType::list_t)
    return (AstList*)vptr;
  return nullptr;
}

const AstMap* Operand::get_map_ptr() const {
  auto vptr = _vrptr();
  if(vptr->_get_type()== OperandType::map_t)
    return (AstMap*)vptr;
  return nullptr;
}

Operand* Operand::get_operand_ptr_nc() {
  MYLOGGER(trace_function, "AstList::get_operand_ptr_nc()", __func__, SLOG_FUNC_INFO);
  return (Operand*)this;
}
AstList* Operand::get_list_ptr_nc() {
  MYLOGGER(trace_function, "AstList::get_list_ptr_nc()", __func__, SLOG_FUNC_INFO);
  auto vptr = _vrptr();
  if(vptr->_get_type()== OperandType::list_t)
    return (AstList*)vptr;
  return nullptr;
}

AstMap* Operand::get_map_ptr_nc() {
  MYLOGGER(trace_function, "AstList::get_map_ptr_nc()", __func__, SLOG_FUNC_INFO);
  auto vptr = _vrptr();
  if(vptr->_get_type()== OperandType::map_t)
    return (AstMap*)vptr;
  return nullptr;
}


//------------------------------------
Operand& Operand::operator[] (const Operand& k) {
  MYLOGGER(trace_function, "Operand::operator[](Operand&)", __func__, SLOG_FUNC_INFO);
  //return const_cast<Operand&>(as_const(*this)[k]); 
  auto vptr =(AstList*) _vrptr();
  if(vptr==nullptr) return nil_operand_nc;
  return (*vptr)[k];
};
const Operand& Operand::operator[] (const Operand &k) const {
  MYLOGGER(trace_function, "Operand::operator[](Operand&) const", __func__, SLOG_FUNC_INFO);
  auto vptr =(AstList*) _vrptr();
  if(vptr==nullptr) return nil_operand;
  return (*vptr)[k];
};

//------------------------------------
Number Operand::_get_number() const { 
  if(holds_alternative<Number>(value_)) {
    return get<Number>(value_); 
  } else if(holds_alternative<string>(value_)) {
    auto strnum = get<string>(value_);
    if(strnum.find('.')!= string::npos) return Number(stod(strnum)); 
    else return Number(stol(strnum)); 
  }
  //return get<Number>(_get_variant());
  auto vptr =(Operand*) _vrptr();
  return vptr->_get_number();
}

//s_integer Operand::_get_int() const { return _get_number().get_int(); }

bool Operand::is_nil() const {
  if(type_ == OperandType::nil_t) return true; 
  return false; 
}
//------------------------------------
Operand Operand::to_str() const { 
  return visit(ToString{}, value_); 
}

string Operand::_to_str() const { 
  //OperandType type = visit(GetOperandType(), value_);
   if (holds_alternative<string>(value_))
    return get<string>(value_); 
  return to_str()._to_str();
}


//------------------------------------

void Operand::print() const { cout << *this; }
s_integer Operand::size() const {return 0l;}

//------------------------------------ DeRef

//------------------------------------------------------------------------------------------------------------------ 
ostream& operator<<(ostream& os, const Operand& v) {
  MYLOGGER(trace_function, "OS<<(Operand&)", __func__, SLOG_FUNC_INFO+20);
  cout << v._to_str();
  return os;
}

//------------------------------------ Clone
template <typename T> 
astnode_u_ptr Operand::Clone::operator()(const T& v) const { return make_unique<Operand>(v); }
astnode_u_ptr Operand::Clone::operator()(const Nil v) const { return nullptr; }
astnode_u_ptr Operand::Clone::operator()(const astnode_ptr& v) const { return v->clone(); }
astnode_u_ptr Operand::Clone::operator()(const astnode_u_ptr& v) const {return v->clone(); } 
astnode_u_ptr Operand::Clone::operator()(const astnode_s_ptr& v) const { return v->clone(); }


