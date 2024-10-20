#include "ast_list.hh"
#include "operand.hh"
AstList::AstList() : AstExpr(OperandType::list_t) {}



AstList nil_list;


AstList::AstList(const AstList& l) {
  for(auto &e : l.list_) {
     list_.push_back(e.clone()); 
  }
};

astexpr_u_ptr AstList::clone() const {
  list_u_ptr new_list = make_unique<AstList>();

  for(auto &e : list_) 
    new_list->list_.push_back(e.clone()); 
  return new_list;
}
//--------------------------------------
const Operand& AstList::getv(const Operand &k)  {
  //cout << "1getv k(" << k << ")";
  return getv(k._get_int());
}
const Operand& AstList::getv(int i)  {
  //cout << "1getv(" << i << ")\n";
  //return nil_operand;
  if(list_[i] == nil_ast_ptr) return nil_operand;
  //cout << "2getv(" << i << ")";
  return list_[i].getv();
}
const Operand& AstList::getv()  {
  cerr << "calling AstList::getv()!\n";
  return nil_operand;
}
//--------------------------------------

const astexpr_u_ptr& AstList::getptr(const Operand &k) {
  return getptr(k._get_int());
}
const astexpr_u_ptr& AstList::getptr(int i) {
  return list_[i]._get_astexpr_u_ptr();
}

//--------------------------------------
bool AstList::add(const AstExpr& v)  {
  list_.push_back(v.clone()); 
  return true;
}

bool AstList::add(astexpr_u_ptr &&vptr) {
  list_.push_back(move(vptr));
  return true;
}

bool AstList::add(const Operand &k, const AstExpr& v) { return false; }
bool AstList::add(const Operand &k, astexpr_u_ptr&& vptr) { return false; }


//--------------------------------------
s_integer AstList::size() const { return list_.size(); }

//--------------------------------------
bool AstList::set(const Operand &key, const Operand &v ) {
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
  cout << to_str();
}

Operand AstList::get_type() const {
  return Operand(OperandType::list_t);
};

astexpr_u_ptr AstList::evaluate(astexpr_u_ptr &ctxt) {
  return nullptr;
}
