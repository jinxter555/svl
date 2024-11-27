#include "operand.hh"
#include "ast_list.hh"





AstList nil_list;

AstList::AstList() : AstExpr(OperandType::list_t) {}

AstList::AstList(const AstList& l) {
  for(auto &e : l.list_) {
    list_.push_back(e->clone()); 
  }
};

astexpr_u_ptr AstList::clone() const {
  list_u_ptr new_list = make_unique<AstList>();

  for(auto &e : list_) 
    new_list->list_.push_back(e->clone()); 
  return new_list;
}
Operand AstList::clone_val() const {
  return Operand();
}
//--------------------------------------
astexpr_u_ptr& AstList::operator[] (const Operand& k) {
  return const_cast<astexpr_u_ptr&>(as_const(*this)[k._get_int()]); 
}
const astexpr_u_ptr& AstList::operator[] (const Operand &k) const {
  int index = k._get_int();
  if(index > list_.size() || index < 0) return nil_ast_ptr;
  return list_[index]; 
}

//--------------------------------------
Operand& AstList::getv(const Operand &k)  {
  //cout << "1getv k(" << k << ")";
  return getv(k._get_int());
}
Operand& AstList::getv(int i)  {
  //cout << "1getv(" << i << ")\n";
  //return nil_operand;
  if(list_[i] == nil_ast_ptr) return nil_operand;
  //cout << "2getv(" << i << ")";
  return list_[i]->getv();
}
Operand& AstList::getv()  {
  cerr << "calling AstList::getv()!\n";
  return nil_operand;
}

vector<string> AstList::_get_keys() { return {}; }
//--------------------------------------

astexpr_u_ptr& AstList::get_u_ptr(const Operand &k) {
  return get_u_ptr(k._get_int());
}
astexpr_u_ptr& AstList::get_u_ptr(int i) {
  return list_[i];
}

AstExpr *AstList::get_raw_ptr(const Operand &k) {
  return get_raw_ptr(k._get_int());
}
AstExpr *AstList::get_raw_ptr(int i) {
   if(i > list_.size() || i < 0) return nullptr;
  return list_[i].get();

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
Operand AstList::opfunc(const Operand& other, AstOpCode op) {
  return  Operand();
}
//--------------------------------------
s_integer AstList::size() const { return list_.size(); }

//--------------------------------------
bool AstList::set(const Operand &key, const AstExpr &v ) {
  int i = key._get_int();
  if(i > size() || i < 0) return false;
  list_[i] = v.clone();
  return true;
}

bool AstList::set(const Operand &key, astexpr_u_ptr &&vptr ) {
  int i = key._get_int();
  if(i > size() || i < 0) return false;
  list_[i] = move(vptr);
  return true;
}
//--------------------------------------
Operand AstList::to_str() const {
  s_integer i, s = size();
  Operand outstr("[");
  if(s==0) {return Operand("[]");}

  for(i=0; i<s-1; i++) {
    outstr = outstr + list_[i]->to_str() + ",";
  }
  outstr = outstr + list_[i]->to_str() + "]";
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

astexpr_u_ptr AstList::evaluate(astexpr_u_ptr &ctxt) {
  int i, s = size();
  list_u_ptr result_list = make_unique<AstList>();
  cout << "in list eval!\n";
  for(i=0; i<s; i++) {
    result_list->add(list_[i]->evaluate(ctxt));
  }
  return result_list;
}