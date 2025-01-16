#include <utility>
#include "ast_list.hh"
#include "operand_vars.hh"


#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"


/*
void AstList::accept_nc(Visitor& visitor) { visitor.visit(*this); }
void AstList::accept(Visitor& visitor) const { visitor.visit(*const_cast<QueList*>(this)); }

bool AstList::isEqual(const QueNode &other) const {
  CompareVisitor compare_visitor(*this);
  other.accept(compare_visitor);
  return compare_visitor.isEqualResult();
}
*/
//------------------------------------------------------------------------------------------------------------------ 
AstList::AstList() : AstNode(OperandType::list_t) {}

AstList::AstList(const list_t & l) : AstNode(OperandType::list_t) {
  for(auto &e: l) list_.push_back( e.clone()); }

AstList::AstList(const vec_num_t& l) : AstNode(OperandType::list_t) {
  for(auto &e: l) list_.push_back(e); }

AstList::AstList(const vec_str_t& l) : AstNode(OperandType::list_t) {
  for(auto &e: l) list_.push_back(e); }

//--------------------------------------
Operand AstList::evaluate(unique_ptr<AstNode>&ctxt) { 
  MYLOGGER(trace_function , "AstList::evaluate()" , string("AstList::") + string(__func__), SLOG_FUNC_INFO);
  //cout << "AstList::evaluate()\n";
  int i, s = size();
  astnode_u_ptr result_list = make_unique<AstList>();
  //cout << "in list eval!\n";
  //cout << "size: " << size() << "\n";
  for(i=0; i<s; i++) {
    //cout  << "list[" << i << "]" << list_[i] << "\n";
    result_list->add(list_[i].evaluate(ctxt).clone());
  }
  return result_list;
}
//--------------------------------------
astnode_u_ptr AstList::clone() const {
  MYLOGGER(trace_function, "AstList::clone_list(list_t&)", __func__, SLOG_FUNC_INFO);

  auto new_list = make_unique<AstList>();
  for(auto &e : list_)  {
    new_list->list_.push_back(e.clone()); 
  }
  return new_list;
}

//------------------------------------------------------------------------------------------------------------------ 
Operand& AstList::operator[] (const Operand& k) {
  MYLOGGER(trace_function, "AstList::operator[](Operand& k)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("k: ") + k._to_str(), SLOG_FUNC_INFO);
  //return const_cast<Operand&>(as_const(*this)[k._get_int()]); 
  auto vrptr = k._vrptr();

  switch (vrptr->_get_type()) {
  case OperandType::num_t: {
    auto i = k._get_int();
    return list_[i]; } //return const_cast<Operand&>(as_const(*this)[kstr]); }
  case OperandType::list_t: {
    auto &l= vrptr->get_list();
    return (*this)[l]; //return const_cast<Operand&>(as_const(*this)[l]); 
  }}
  return nil_operand_nc;
}

//--------------------------------------
Operand& AstList::operator[] (s_integer index) { 
  MYLOGGER(trace_function, "AstList::operator[](int&)", __func__, SLOG_FUNC_INFO);
  //cout << "AstList::operator[" <<  index << "]\n" ;
  return const_cast<Operand&>(as_const(*this)[index]); 
  /*
  if(index >= list_.size() || index < 0) return nil_operand_nc;
  return list_[index]; 
  */
}

const Operand& AstList::operator[] (s_integer index) const { 
  MYLOGGER(trace_function, "AstList::operator[](int&) const", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("k: ") + Number(index)._to_str(), SLOG_FUNC_INFO);
//  cout << "AstList::operator[" <<  index << "]const \n" ;
  if(index >= list_.size() || index < 0) return nil_operand;
  return list_[index]; 
}
//--------------------------------------
Operand& AstList::operator[] (const vec_num_t& index_keys) {
  MYLOGGER(trace_function, "AstList::operator[](const vec_num_t&) const", __func__, SLOG_FUNC_INFO+10);
  return (*this)[AstList(index_keys)];
}

Operand& AstList::operator[] (const AstList& index_keys) {
  MYLOGGER(trace_function, "AstList::operator[](const AstList&) const", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("k: ") + index_keys.to_str()._to_str(), SLOG_FUNC_INFO);
  cout << "AstList::operator[" <<  index_keys << "] \n" ;

  auto Lptr= _vrptr();
  s_integer i, s = index_keys.size();
  for(i=0; i<s; i++) {
    //auto &k= index_keys.list_[i];
    auto &k= index_keys[i];
    auto &v = (*Lptr)[k];

    if(v.is_nil()) { return nil_operand_nc; }
    //if(i==s-1)  return const_cast<Operand&>(as_const(*Lptr)[k]); 
    if(i==s-1) return v;

    Lptr = v._vrptr();
  }
  return nil_operand_nc;
}

const Operand& AstList::back() const { return list_.back(); }
Operand& AstList::back_nc()  { return list_.back(); }

//------------------------------------------------------------------------------------------------------------------ 
bool AstList::is_nil() const {
  if(list_.size() <= 0) return true;
  return false;
}

//--------------------------------------
const list_t& AstList::_get_list() const { return list_; }

//------------------------------------------------------------------------------------------------------------------ 

astnode_ptr AstList::_vrptr() const {
  MYLOGGER(trace_function, "AstList::_vptr()", __func__, SLOG_FUNC_INFO);
  return (AstNode*) this; 
}

const astnode_u_ptr& AstList::get_u_ptr() const { return nil_ast_ptr; }
astnode_u_ptr& AstList::get_u_ptr_nc() { return nil_ast_ptr_nc; }

bool AstList::add(astnode_u_ptr &&vptr) {
  if(vptr==nullptr) return false;
  list_.push_back(move(vptr));
  return true;
}
bool AstList::add(const list_t & l) {
  MYLOGGER(trace_function , "AstList::add(list_t)" , __func__, SLOG_FUNC_INFO+9);
  auto new_list = make_unique<AstList>();
  for(auto &e: l) new_list->add( e.clone()); 
  add(move(new_list));
  return true;
}

/* bool AstList::add(const Operand& v) { list_.push_back(v.clone()); return true; }*/
bool AstList::add(const operand_variant_t& ovv) {
  MYLOGGER(trace_function , "AstList::add(operand_variant)" , __func__, SLOG_FUNC_INFO+9);
  list_.push_back(ovv);
  return true;
}





Operand AstList::to_str() const {
  int i, s = size();
  string outstr("[");
  if(s==0) {return Operand("[]");}

  for(i=0; i<s-1; i++) {
    outstr = outstr + list_[i]._to_str() + ",";
  }
  outstr = outstr + list_[i]._to_str() + "]";
  return outstr;
}

void AstList::print() const {
  //if(this==nullptr) return;
  cout << to_str();
}

Operand AstList::get_type() const {
  return type_;
};
OperandType AstList::_get_type() const { return OperandType::list_t; };

s_integer AstList::size() const { return list_.size(); }

const AstNode& AstList::get_node() const { return *this; }
const AstList& AstList::get_list() const { return *this; }
const Operand& AstList::get_operand() const { return nil_operand; }
const AstMap& AstList::get_map() const { return nil_map; }


const Operand* AstList::get_operand_ptr() const {
  MYLOGGER(trace_function, "AstList::get_operand_ptr()", __func__, SLOG_FUNC_INFO);
  return (Operand*)this;
}
const AstList* AstList::get_list_ptr() const {
  MYLOGGER(trace_function, "AstList::get_list_ptr()", __func__, SLOG_FUNC_INFO);
  return this;
}

const AstMap* AstList::get_map_ptr() const {
  MYLOGGER(trace_function, "AstList::get_map_ptr()", __func__, SLOG_FUNC_INFO);
  return nullptr;
}

Operand* AstList::get_operand_ptr_nc() {
  MYLOGGER(trace_function, "AstList::get_operand_ptr_nc()", __func__, SLOG_FUNC_INFO);
  return (Operand*)this;
}
AstList* AstList::get_list_ptr_nc() {
  MYLOGGER(trace_function, "AstList::get_list_ptr_nc()", __func__, SLOG_FUNC_INFO);
  return this;
}

AstMap* AstList::get_map_ptr_nc() {
  MYLOGGER(trace_function, "AstList::get_map_ptr_nc()", __func__, SLOG_FUNC_INFO);
  return nullptr;
}
operand_variant_t AstList::_get_variant() const { return nil; }

bool AstList::operator==(const AstList& other) const {
  MYLOGGER(trace_function, "AstList::==(AstList&)", __func__, SLOG_FUNC_INFO+9);
  cout << "AstList::==(const AstList&)\n";
  return cmp_eql(other);
}
bool AstList::operator!=(const AstList &other) const { 
  MYLOGGER(trace_function, "AstList::!=(const AstList&)", __func__, SLOG_FUNC_INFO);
  cout << "AstList::!=(const AstList&)\n";
  return !cmp_eql(other);
}

bool AstList::operator==(const astnode_ptr& vptr ) const {
  MYLOGGER(trace_function, "AstList::==(astnode_ptr&)", __func__, SLOG_FUNC_INFO+9);
  cout << "AstList::==(const astnode_ptr&)\n";
  return cmp_eql(*vptr);
}

bool AstList::cmp_eql(const AstNode  &other) const { 
  MYLOGGER(trace_function, "AstList::cmp_eql(AstNode&)", __func__, SLOG_FUNC_INFO+9);
  cout << "AstList::cmp_eql(const AstNode&)\n";
  return cmp_eql(other.get_list_ptr());
}

bool AstList::cmp_eql(const AstList* other_ptr) const { 
  MYLOGGER(trace_function, "AstList::cmp_eql(AstList*)", __func__, SLOG_FUNC_INFO+9);
  cout << "AstList::cmp_eql(AstList*)\n";
  cout << "*this: " << *this <<  " type: " << get_type() << "\n";

  s_integer s=size();
  if(other_ptr==nullptr ){
    if(s==0) return true;
    cout << "other_ptr is null!\n";
    return false;
  }
  cout << "*other: " << *other_ptr << " other type: " << other_ptr->get_type() << "\n\n";

  if(other_ptr->_get_type()!= OperandType::list_t) return false;
  if(s != other_ptr->size()) return false;


  for(s_integer i=0; i < s; i++ ) {
    cout << list_[i] << "==" << (*other_ptr)[i] << "\n";
    if(list_[i] == (*other_ptr)[i]) continue;
    else {
      cout << "AstList != AstList false\n";
      return false;
    }
  }
  cout << "AstList == AstList true\n";
  return true;
}

Operand AstList::opfunc(const AstNode& other, AstOpCode op) {
  MYLOGGER(trace_function , "AstList::opfunc()" ,__func__, SLOG_FUNC_INFO+9);
  cout << "AstList::opfunc()!\n";
  cout << "op: " << Operand(op) << "\n";
  
  print(); cout << " " << Operand(op) << " " <<  other <<"\n";
  //return make_unique<Operand>( eql_cmp(move(other)));
  switch(op) {
  //case AstOpCode::eql:    return make_unique<Operand>( *this == move(other));
  case AstOpCode::eql:    return  cmp_eql(other);
  case AstOpCode::neql:   return  !cmp_eql(other);
  default:
    cerr << "AstList::opfunc, default error!\n";
    return nil;
  }
}
