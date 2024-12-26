#include <utility>
#include "ast_map.hh"
#include "operand.hh"

#define DEBUG_TRACE_FUNC
#include "scope_logger.hh"
#include "my_helpers.hh"

AstMap::AstMap() 
: AstExpr(OperandType::map_t)
//, myself(this) 
{}
//--------------------------------------

astexpr_u_ptr AstMap::clone() const {
  map_u_ptr new_map = make_unique<AstMap>();

  for (auto const& [key, val] : map_) {
    new_map->map_[key] = val.clone();
  }
  return new_map;
}

Operand AstMap::clone_val() const {
  cerr << "AstMap::clone_val(), I shouldn't be here!\n";
  //return Operand(clone());
  return clone();
};

astexpr_u_ptr AstMap::clone_usu() {
  return make_unique<Operand>(
    make_shared<Operand>(clone())
  );
}
//--------------------------------------

Operand AstMap::evaluate(astexpr_u_ptr& ast_ctxt) {
  return clone();
}
//--------------------------------------

const Operand& AstMap::_get_value() const {
  return *(Operand*)this;
}

Operand& AstMap::back() { return nil_operand;}
Operand& AstMap::front() { return nil_operand;}


Operand& AstMap::getv(const Operand &k)  {
  return(getv(k._get_str()));
}
Operand& AstMap::getv(const string &k)  {
  if(!has_key(k)){
    //cerr << "getv key: " << k << " does not exist!\n";
    return nil_operand;
  }
  return  map_[k];

}
//--------------------------------------
Operand& AstMap::operator[] (const Operand& k) {
  return const_cast<Operand&>(as_const(*this)[k._get_str()]); 
}
const Operand& AstMap::operator[] (const Operand &k) const {
  const string i = k._get_str();
  if(!has_key(i)) return nil_operand;
  return map_.at(i); 
}

//--------------------------------------
astexpr_u_ptr& AstMap::get_u_ptr_nc(const Operand&k) { 
  return const_cast<astexpr_u_ptr&>(as_const(this->get_u_ptr(k))); 
}

const astexpr_u_ptr& AstMap::get_u_ptr(const Operand &k) const {
  auto k_str = k._get_str();
  return get_u_ptr(k_str);
}
const astexpr_u_ptr& AstMap::get_u_ptr(const string &k) const {
  if(this == nullptr || !has_key(k)){
    return nil_ast_ptr;
  }
  return map_.at(k).get_u_ptr();
}
const astexpr_u_ptr& AstMap::get_u_ptr() const {
  cerr << "I should NOT be here in  AstMap::get_u_ptr()\n";
  return nil_ast_ptr;
}
astexpr_u_ptr& AstMap::get_u_ptr_nc() { 
  return const_cast<astexpr_u_ptr&>(as_const(this->get_u_ptr())); 
}

astexpr_s_ptr AstMap::get_s_ptr() { return nullptr; };
//astexpr_s_ptr  AstMap::get_s_ptr_nc() { return nullptr; };

//--------------------------------------
AstExpr *AstMap::get_raw_ptr() const {
  return (AstExpr*)this;
}


AstExpr *AstMap::get_raw_ptr(const Operand &k) const {
  auto k_str = k._get_str();
  return get_raw_ptr(k_str);
}
AstExpr *AstMap::get_raw_ptr(const string &k) const {
  //cout << "AstMap::get_raw_ptr: k_str " << k << "\n";
  if(this == nullptr || !has_key(k)){
    //cerr << "raw pointer key: " << k << " does not exist!\n";
    return nullptr;
  }
  //auto value = visit(GetOperand_eptr(), children[k].value_);
  return map_.at(k).get_raw_ptr();

}


//--------------------------------------
bool AstMap::add(const AstExpr& v)  { return false; }
bool AstMap::add(astexpr_u_ptr &&vptr) { return false; }
//--------------------------------------
bool AstMap::add(const Operand &k, const AstExpr& v, bool overwrite) {
  MYLOGGER(trace_function
  , "AstMap::add(const Operand &k, const AstExpr& v, bool overwrite): "
  ,string("AstMap::") + string(__func__));
  MYLOGGER_MSG(trace_function, k._to_str()  + string(": ")  + v.to_str()._to_str());

  return add(k._get_str(), v, overwrite);
}
bool AstMap::add(const string &k, const AstExpr& v, bool overwrite) {
  MYLOGGER(trace_function, "AstMap::add(string)", __func__);
  //if(this==nullptr) {return false;}
  if(!overwrite && has_key(k)) return false;

  switch(v.type_){
  case OperandType::map_t:
  case OperandType::list_t:
  case OperandType::uptr_t:
    map_[k] = move(v.clone());
    break;
/*
  case OperandType::sptr_t:
    //map_[k] = move(v.clone());
    map_[k] = move(v.clone());
    break;
*/
  default: {
    //map_[k] = v.clone_val();
    MYLOGGER_MSG(trace_function, string("before: ") + v.clone_val()._to_str());
    map_[k] = v._get_variant();
    MYLOGGER_MSG(trace_function, string("after: ") + v.clone_val()._to_str());
    break;
  }}
  return true;
}


bool AstMap::add(const Operand &k, astexpr_u_ptr&& vptr, bool overwrite) {
  MYLOGGER( trace_function
    , "AstMap::add(const Operand &k, astexpr_u_ptr&& vptr, bool overwrite)"
  ,__func__)
  MYLOGGER_MSG(trace_function, k._to_str() + string(": ") + vptr->to_str()._to_str());

  return add(k._get_str(), move(vptr), overwrite);
}
bool AstMap::add(const string &k, astexpr_u_ptr&& vptr, bool overwrite) {
  //if(this==nullptr) {return false;}

  if(has_key(k) && !overwrite) return false;
  map_[k] = move(vptr);
  //map_[k] = vptr;
  return true;
}
//------------------------------------- 
bool AstMap::add_branch(const vector<string> &keys, const Operand& operand, bool overwrite)  {
  MYLOGGER( trace_function
    , "AstMap::add_branch(const vector<string> &keys, op)"
    ,__func__)
  MYLOGGER_MSG( trace_function, string("keys: ")+add_vector_string(keys, ", ") + string(":") +  operand._to_str());

  //return add_branch(keys, operand.clone(), overwrite);
  int i=0, s = keys.size();  
  string k;
  AstMap *curr=this, *next;
  for(int i=0; i<s-1; i++) {
    k = keys[i]; //cout << "keys[" << i<< "]: " << keys[i] << "\n";
    next =(AstMap*) curr->get_raw_ptr(k);
    if(next==nullptr || next->type_ != OperandType::map_t) {
      if(!curr->add(keys[i], make_unique<AstMap>(), overwrite)) {
        return false;
      }
    }
    curr =(AstMap*) curr->get_raw_ptr(k);
  }
  curr->add(keys.back(), operand, overwrite);
  return true;
}

bool AstMap::add_branch(const vector<string> &keys, astexpr_u_ptr&& vvptr , bool overwrite) {
  MYLOGGER( trace_function
    , "AstMap::add_branch(const vector<string> &keys, vvptr)"
    ,__func__)
  MYLOGGER_MSG( trace_function, string("keys: ")+add_vector_string(keys, ", ") + string(":") +  vvptr->to_str()._to_str());

  int i=0, s = keys.size();  
  string k;
  AstMap *curr=this, *next;
  for(int i=0; i<s-1; i++) {
    k = keys[i]; //cout << "keys[" << i<< "]: " << keys[i] << "\n";
    next =(AstMap*) curr->get_raw_ptr(k);
    if(next==nullptr || next->type_ != OperandType::map_t) {
      if(!curr->add(keys[i], make_unique<AstMap>(), overwrite)) {
        return false;
      }
    }
    curr =(AstMap*) curr->get_raw_ptr(k);
  }
  curr->add(keys.back(), move(vvptr), overwrite);
  return true;
}





//------------------------------------- 
Operand& AstMap::get_branch(const vector<string> &keys) {
  // MYLOGGER( trace_function, __func__, __func__)
  MYLOGGER( trace_function
    , "AstMap::get_branch(const vector<string> &keys)"
    ,__func__)
  MYLOGGER_MSG( trace_function, string("keys: ")+add_vector_string(keys, ", "));
  int i=0, s = keys.size();  
  string k; AstExpr *curr=this, *next;

  //if(curr==nullptr )  return nil_operand;
  for(int i=0; i<s-1; i++) {
    k = keys[i];  //cout << "keys[" << i<< "]: " << keys[i] << "\n";
    if(curr==nullptr) { 
      cerr << "AstMap::get_branch, curr nullptr bomb!\n";
      return nil_operand;
    } else { //cout  << "curr type: " << curr->get_type() << "\n"; 
    }
    next = (AstExpr*) curr->get_raw_ptr(k);
    if(curr==nullptr)  return nil_operand;
    curr = next;
  }

  if(curr==nullptr) {
    //cerr << "curr is null!\n";
    return nil_operand;
  } else {
    return curr->getv(Operand(keys.back()));
  }
  return nil_operand;
}






//------------------------------------- 
bool AstMap::set(const Operand &k, const AstExpr& v) {
  return set(k._get_str(), v);
}
bool AstMap::set(const string &k, const AstExpr& v) { 
  if(!has_key(k)){
    cerr << "map set operand and key: " << k << " does not exist!\n";
    return false;
  }
  map_[k] = v.clone();
  return  true;
}

bool AstMap::set(const Operand &k, astexpr_u_ptr&& vptr) {
  return set(k._get_str(), move(vptr));
}
bool AstMap::set(const string &k, astexpr_u_ptr&& vptr) {
  if(!has_key(k)){
    cerr << "map set vptr and key: " << k << " does not exist!\n";
    return false;
  }
  map_[k] = move(vptr);
  return  true;
}
//------------------------------------- 
bool AstMap::has_key(const Operand &k)  const {
  string k_str = k._get_str();
  return has_key(k_str);
}
bool AstMap::has_key(const string  &k)  const {
 // if(this==nullptr || type_ != OperandType::map_t) return false;
  if(type_ != OperandType::map_t) return false;
  if (map_.find(k) != map_.end())  {
    return true;
  }
  return false;
}

//------------------------------------- 
s_integer  AstMap::size() const { return map_.size(); }
void AstMap::print() const { 
  // if(this==nullptr) return;
  cout << to_str(); 
}
Operand AstMap::get_type() const { 
  return type_;
  return Operand(OperandType::map_t); 
}
OperandType AstMap::_get_type() const { 
  return OperandType::map_t; 
}

Operand AstMap::to_str() const {

  if(map_.empty()) return Operand();

  vector<string> kv_paires ;
  string colon(":");
  string q("\"");
  string outstr;

  for (auto const& [key, val] : map_) {
    outstr = q + key + q  + colon + " " + val.to_str()._to_str();
    kv_paires.push_back(outstr);
  }

  outstr="{";
  int i, s = kv_paires.size();
  for(i=0; i<s-1; i++) {
    outstr = outstr + kv_paires[i] + ", ";
  }
  outstr = outstr + kv_paires[i] + "}";
  return (outstr);
}

vector<string> AstMap::_get_keys() const {
  vector<string> key_list;
  for (auto const& [key, val] : map_) {
    key_list.push_back(key);
  }
  return key_list;
}

Operand AstMap::opfunc(const AstExpr &other, AstOpCode op) {
  MYLOGGER(trace_function , "AstMap::opfunc()" ,__func__);
  cout << "AstMap::opfunc()!\n";

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
  return nil;
}

bool AstMap::operator==(const astexpr_ptr vptr) const { 
  MYLOGGER(trace_function, "AstMap::==(const astexpr_ptr)", __func__);
  cout << "AstMap::==(const astexpr_ptr*)\n";
  cout << "what am i doing here!\n";
  return cmp_eql(vptr->_get_map_ptr());
}

bool AstMap::operator==(const AstExpr &other) const { 
  MYLOGGER(trace_function, "AstMap::==(const AstExpr&)", __func__);
  cout << "AstMap::==(const AstExpr&)\n";
  cout << "this: " <<  to_str() << ", other: " <<  other << "\n";
  return cmp_eql(other._get_map_ptr());
}

bool AstMap::operator!=(const AstExpr &other) const { 
  MYLOGGER(trace_function, "AstMap::!=(const AstExpr&)", __func__);
  cout << "AstMap::!=(const AstExpr&)\n";
  return !cmp_eql(other);
}

bool AstMap::cmp_eql(const AstExpr &other) const { 
  return cmp_eql(other._get_map_ptr());
}
bool AstMap::cmp_eql(const AstMap *other_ptr) const { 
  MYLOGGER(trace_function, "AstMap::cmp_eql(const AstExpr&)", __func__);
  cout << "AstMap::cmp_eql(const AstExpr&)\n";

  cout << "*this: " << *this <<  " type: " << get_type() << "\n";
  s_integer s=size();

  if(other_ptr==nullptr ){
    if(s==0) return true;
    cout << "other_ptr is null!\n";
    return false;
  }
  cout << "*other: " << *other_ptr << " other type: " << other_ptr->get_type() << "\n\n";

  if(other_ptr->_get_type()!= OperandType::map_t) return false;
  if(s != other_ptr->size()) return false;

  for (auto const& [key, val] : map_) {
    auto& other_val = (*other_ptr)[key];
    if(val != other_val) {
      cout << key << ":" << val << " != " << key << ":" << other_val << "\n";
      return false;
    }
  }

  return true; 
}

operand_variant_t AstMap::_get_variant() const { 
  //cout << "AstMap::_get_variant() I shouldn't be here\n";
  return nil; 
}

bool AstMap::is_current_nil() const {
  if(size()==0) return true;
  return false;
};
bool  AstMap::is_nil() const {
  if(size()==0) return true;
  return false;
}

const Operand* AstMap::_get_operand_ptr() const {
  //cout << "AstMap::_get_operand_ptr() I shouldn't be here\n";
  cout << "AstMap::_get_operand_ptr()\n";
  return nullptr;
}
const AstList* AstMap::_get_list_ptr() const {
  cout << "AstMap::_get_list_ptr()\n";
  return nullptr;
}
const AstMap* AstMap::_get_map_ptr() const {
  //cout << "AstMap::_get_map_ptr() I shouldn't be here\n";
  cout << "AstMap::_get_map_ptr()\n";
  return this;
}