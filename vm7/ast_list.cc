#include "operand.hh"
#include "ast_list.hh"


#define DEBUG_TRACE_FUNC
#include "scope_logger.hh"



AstList nil_list;

AstList::AstList() 
: AstExpr(OperandType::list_t) 
//, myself(this) 
{}

AstList::AstList(const AstList& l) {
  for(auto &e : l.list_) {
    list_.push_back(e.clone()); 
  }
};

//--------------------------------------
astexpr_u_ptr AstList::clone() const {
  MYLOGGER(trace_function , "AstList::clone()" ,__func__);

  list_u_ptr new_list = make_unique<AstList>();
  for(auto &e : list_)  {
    new_list->list_.push_back(e.clone()); 
  }
  return move(new_list);
}

Operand AstList::clone_val() const {
  cerr << "AstList::clone_val(), I shouldn't be here!\n";
  MYLOGGER(trace_function , "AstList::clone_val()" ,__func__);

  return clone();
}
astexpr_u_ptr AstList::clone_usu() {
  return make_unique<Operand>(
    make_shared<Operand>(clone())
  );
}

//--------------------------------------
Operand& AstList::operator[] (const Operand& k) {
  return const_cast<Operand&>(as_const(*this)[k._get_int()]); 
}
const Operand& AstList::operator[] (const Operand &k) const {
  int index = k._get_int();
  if(index >= list_.size() || index < 0) return nil_operand;
  return list_[index]; 
}

Operand& AstList::operator[] (int index) { 
  //cout << "AstList::operator[" <<  index << "]\n" ;
  return const_cast<Operand&>(as_const(*this)[index]); 
}
const Operand& AstList::operator[] (int index) const { 
  //cout << "AstList::operator[" <<  index << "]const \n" ;
  if(index >= list_.size() || index < 0) return nil_operand;
  return list_[index]; 
}

//--------------------------------------
Operand& AstList::getv(const Operand &k)  {
  //cout << "AstList::getv k(" << k << ")";
  return getv(k._get_int());
}
Operand& AstList::getv(const string &k)  {
  //cout << "AstList::getv k(" << k << ")";
  return getv(stoi(k, nullptr, 10));
}
Operand& AstList::getv(int i)  {
  if(i >= list_.size() || i < 0) return nil_operand;
  //if(list_[i] == nil_ast_ptr) return nil_operand;
  //return list_[i].getv();
  return list_[i];
}
const Operand& AstList::getv()  const {
  cerr << "AstList::getv() I shouldn't be here\n";
  return nil_operand;
}
Operand& AstList::back() { return list_.back(); }
Operand& AstList::front() { return list_.front(); }

vector<string> AstList::_get_keys() const {return {}; }
//--------------------------------------
astexpr_u_ptr& AstList::get_u_ptr_nc() { 
  return const_cast<astexpr_u_ptr&>(as_const(this->get_u_ptr())); 
}
const astexpr_u_ptr& AstList::get_u_ptr() const {
  cerr << "I should NOT be here in  AstList::get_u_ptr()\n";
  return nil_ast_ptr;
}
astexpr_s_ptr AstList::get_s_ptr() { return nullptr; };
//astexpr_s_ptr  AstList::get_s_ptr_nc() { return nullptr; };
//--------------------------------------

astexpr_u_ptr& AstList::get_u_ptr_nc(const Operand&k) { 
  return const_cast<astexpr_u_ptr&>(as_const(this->get_u_ptr(k))); 
}

const astexpr_u_ptr& AstList::get_u_ptr(const Operand &k) const {
  return get_u_ptr(k._get_int());
}
const astexpr_u_ptr& AstList::get_u_ptr(int i) const {
  return list_[i].get_u_ptr();
}


//--------------------------------------
AstExpr *AstList::get_raw_ptr() const {
  return (AstList*)this;
}

AstExpr *AstList::get_raw_ptr(const Operand &k) const {
  return get_raw_ptr(k._get_int());
}
AstExpr *AstList::get_raw_ptr(const string &k) const {
  cout << "astlist:get_raw_ptr k_str to int\n";
  return get_raw_ptr(stoi(k, nullptr, 10));
}

AstExpr *AstList::get_raw_ptr(int i) const {
  //cout << "AstList::get_raw_ptr:i " << i << "\n";
  if(i >= list_.size() || i < 0) return nullptr;
  return list_[i].get_raw_ptr();
  //auto ptr = list_[i].get_raw_ptr();
  //cout << "*ptr: " << *ptr << "\n";
  //return ptr;

}
//--------------------------------------
bool AstList::add(const AstExpr& v)  {
  list_.push_back(v.clone()); 
  return true;
}

bool AstList::add(astexpr_u_ptr &&vptr) {
  if(vptr==nullptr) return false;
  list_.push_back(move(vptr));
  return true;
}

bool AstList::add(const Operand &k, const AstExpr& v, bool overwrite) { return false; }
bool AstList::add(const Operand &k, astexpr_u_ptr&& vptr, bool overwrite) { return false; }

bool AstList::add_branch(const vector<string> &keys, const Operand& operand, bool overwrite)  {return false;}
bool AstList::add_branch(const vector<string> &keys, astexpr_u_ptr&& vvptr , bool overwrite) {return false;}
Operand& AstList::get_branch(const vector<string> &keys) {return nil_operand;}

//--------------------------------------
s_integer AstList::size() const { return list_.size(); }

//--------------------------------------
bool AstList::set(const Operand &key, const AstExpr &v ) {
  /*
  int i = key._get_int();
  if(i >= size() || i < 0) return false;
  list_[i] = v.clone();
  return true;
  */
  return set(key, v.clone());
}

bool AstList::set(const Operand &key, astexpr_u_ptr &&vptr ) {
  int i = key._get_int();
  if(i >= size() || i < 0) return false;
  list_[i] = move(vptr);
  return true;
}
//--------------------------------------

/*
Operand AstList::to_str() const {
  int i, s = size();
  Operand outstr("[\n");
  if(s==0) {return Operand("[]");}

  for(i=0; i<s-1; i++) {
    outstr = outstr + to_string(i) + string(": ") + list_[i].to_str() + ",\n";
  }
  outstr = outstr +  to_string(i)  + string(": ") + list_[i].to_str() + "\n]";
  return outstr;
}
*/

Operand AstList::to_str() const {
  int i, s = size();
  Operand outstr("[");
  if(s==0) {return Operand("[]");}

  for(i=0; i<s-1; i++) {
    outstr = outstr + list_[i].to_str() + ",";
  }
  outstr = outstr + list_[i].to_str() + "]";
  return outstr;
}
void AstList::print() const {
  //if(this==nullptr) return;
  cout << to_str();
}

Operand AstList::get_type() const {
  return type_;
  return Operand(OperandType::list_t);
};
OperandType AstList::_get_type() const {
  return OperandType::list_t;
};

Operand AstList::evaluate(astexpr_u_ptr &ctxt) {
  MYLOGGER(trace_function , "AstList::evaluate()" ,__func__);
  int i, s = size();
  astexpr_u_ptr result_list = make_unique<AstList>();
  //cout << "in list eval!\n";
  for(i=0; i<s; i++) {
    result_list->add(list_[i].evaluate(ctxt));
  }
  return result_list;
}

Operand AstList::opfunc(const AstExpr& other, AstOpCode op) {
  cout << "AstList::opfunc()!\n";
  print(); cout << " " << Operand(op) << " " <<  other <<"\n";
  //return make_unique<Operand>( eql_cmp(move(other)));
  switch(op) {
  //case AstOpCode::eql:    return make_unique<Operand>( *this == move(other));
  case AstOpCode::eql:    return  cmp_eql(other);
  case AstOpCode::neql:   return  !cmp_eql(other);
  default:
    cerr << "AstList::opfunc, default error!\n";
    return Operand();
  }
}


//--------------------------------------
bool AstList::operator==(const AstExpr &other) const { 
  cout << "AstList::==()\n";
  return cmp_eql(other);
}

bool AstList::cmp_eql(const AstExpr &other) const { 
  cout << "AstList::cmp_eql(astexpr_u_ptr)\n";
  //cout << "*this: " << *this <<  " type: " << get_type() << "\n";
  //cout << "other: " << other_vptr << " other type: " << other_vptr->get_type() << "\n\n";

  if(other._get_type()!= OperandType::list_t) return false;
  s_integer s=size();
  if(s != other.size()) return false;

  for(s_integer i=0; i < s; i++ ) {
    //cout << list_[i] << "==" << (*other_vptr)[i] << "\n";
    if(list_[i] == other[i]) continue;
    else return false;
  }
  return true;
}

bool AstList::operator!=(const AstExpr &other) const { 
  cout << "AstList::!=()\n";
  return !cmp_eql(other);

}
//bool AstList::cmp_eql(const OperandVariant&ov) const { return false; }
OperandVariant AstList::_get_value() const { return nil; }



//-----------------------------------------------------------------------------------------------------------
Tuple::Tuple(astexpr_u_ptr l) : type_(OperandType::tuple_t) {
  s_integer i, s= l->size();
  for(i=0; i<s; i++) {
    list_.push_back(move(l->getv(i))); 
  }
}

Operand Tuple::to_str() const {
  s_integer i, s = list_.size();
  Operand outstr("{");
  if(s==0) {return Operand("{}");}

  for(i=0; i<s-1; i++) {
    outstr = outstr + list_[i].to_str() + ",";
  }
  outstr = outstr + list_[i].to_str() + "}";
  return outstr;
}

Operand Tuple::get_type() const {
  return OperandType::tuple_t;
};
OperandType Tuple::_get_type() const {
  return OperandType::tuple_t;
};

void Tuple::print() const {
  cout <<  to_str();
}
Operand Tuple::evaluate(astexpr_u_ptr &ctxt) {
  MYLOGGER(trace_function , "Tuple::evalaute()" ,__func__);

  int i, s = size();
  astexpr_u_ptr result_tuple = make_unique<Tuple>();
  for(i=0; i<s; i++) {
    result_tuple->add(list_[i].evaluate(ctxt));
  }
  return result_tuple;

}

//--------------------------------------
astexpr_u_ptr Tuple::clone() const {
  MYLOGGER(trace_function , "Tuple::clone()" ,__func__);

  list_u_ptr new_list = make_unique<Tuple>();
  for(auto &e : list_)  {
    new_list->list_.push_back(e.clone()); 
  }
  return move(new_list);
}

astexpr_u_ptr Tuple::clone_usu() {
  return make_unique<Operand>(
    make_shared<Operand>(clone())
  );
}
//--------------------------------------
bool Tuple::operator==(const Tuple&other) const { 
  MYLOGGER(trace_function , "Tuple::==(Tuple&)" , __func__);
  cout << "Tuple::==()\n";
  Operand other_tuple = other.clone();
  return cmp_eql(other_tuple);
}

bool Tuple::cmp_eql(const AstExpr &v) const {
  MYLOGGER(trace_function , "Tuple::cmp_eql(Operand&)" ,__func__);
  cout << "Tuple::cmp_eql(astexpr_u_ptr)\n";

  Operand other = v.clone();

  cout << "*this: " << *this <<  " type: " << get_type() << "\n";
  cout << "other: " << other<< " other type: " << other.get_type() << "\n\n";

  if(other._get_type()!= OperandType::tuple_t) return false;
  s_integer s=size();
  if(s != other.size()) return false;

  for(s_integer i=0; i < s; i++ ) {
    cout << list_[i] << "==" << other[i] << "\n";
    cout << list_[i].get_type() << "==" << other[i].get_type() << "\n";
    if(list_[i] == other[i]) continue;
    else return false;
  }
  return true;
}

Operand Tuple::opfunc(const AstExpr& other, AstOpCode op) {
  MYLOGGER(trace_function , "Tuple::opfunc()" ,__func__);

  cout << "Tuple::opfunc()!\n";
  print(); cout << " " << Operand(op) << " " <<  other <<"\n";
  switch(op) {
  case AstOpCode::eql:    return cmp_eql(other);
  case AstOpCode::neql:   return !cmp_eql(other);
  default:
    cerr << "AstList::opfunc, default error!\n";
    return Operand();
  }
}