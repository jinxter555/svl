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
  cout << "AstList::operator[" <<  index << "]\n" ;
  return const_cast<Operand&>(as_const(*this)[index]); 
}
const Operand& AstList::operator[] (int index) const { 
  cout << "AstList::operator[" <<  index << "]const \n" ;
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
  if(list_[i] == nil_ast_ptr) return nil_operand;
  //return list_[i].getv();
  return list_[i];
}
Operand& AstList::getv()  {
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

astexpr_u_ptr AstList::evaluate(astexpr_u_ptr &ctxt) {
  int i, s = size();
  //list_u_ptr result_list = make_unique<AstList>();
  astexpr_u_ptr result_list = make_unique<AstList>();
  //cout << "in list eval!\n";
  for(i=0; i<s; i++) {
    result_list->add(list_[i].evaluate(ctxt));
  }
  return result_list;
}

astexpr_u_ptr AstList::opfunc(astexpr_u_ptr other, AstOpCode op) {
  cerr << "AstList::opfunc, I shouldn't be here!\n";
  return nullptr;
}
