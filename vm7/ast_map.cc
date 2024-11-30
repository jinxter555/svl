#include <utility>
#include "ast_map.hh"
#include "operand.hh"

AstMap::AstMap() 
: AstExpr(OperandType::map_t)
//, myself(this) 
{}

astexpr_u_ptr AstMap::clone() const {
  map_u_ptr new_map = make_unique<AstMap>();

  for (auto const& [key, val] : map_) {
    new_map->map_[key] = val.clone();
  }
  return new_map;
}

Operand AstMap::clone_val() const {
  cerr << "I should NOT be here in  AstMap::clone_val()\n";
  auto v = clone();
  return Operand(move(v));
};

Operand AstMap::evaluate(astexpr_u_ptr& ast_ctxt) {
  return Operand();
}

Operand& AstMap::getv()  {
  cerr << "I should NOT be here in  AstMap::getv()\n";
  //myself.value_ = unique_ptr<AstMap>(this);
  //myself.type_ = OperandType::uptr_t;
  return nil_operand;
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

//--------------------------------------
AstExpr *AstMap::get_raw_ptr() const {
  return (AstExpr*)this;
}


AstExpr *AstMap::get_raw_ptr(const Operand &k) const {
  auto k_str = k._get_str();
  return get_raw_ptr(k_str);
}
AstExpr *AstMap::get_raw_ptr(const string &k) const {
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
  return add(k._get_str(), v, overwrite);
}
bool AstMap::add(const string &k, const AstExpr& v, bool overwrite) {
  //if(this==nullptr) {return false;}
  if(!overwrite && has_key(k)) return false;
  if(v.type_ == OperandType::map_t || v.type_ == OperandType::list_t)
    map_[k] = move(v.clone());
  else {
    map_[k] = v.clone_val();
  }
  return true;
}

bool AstMap::add(const Operand &k, astexpr_u_ptr&& vptr, bool overwrite) {
  return add(k._get_str(), move(vptr), overwrite);
}
bool AstMap::add(const string &k, astexpr_u_ptr&& vptr, bool overwrite) {
  //if(this==nullptr) {return false;}

  if(has_key(k) && !overwrite) return false;
  map_[k] = move(vptr);
  return true;
}
//------------------------------------- 
bool AstMap::add_branch(const vector<string> &keys, const Operand& operand, bool overwrite)  {
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
  int i=0, s = keys.size();  
  string k; AstMap *curr=this, *next;

  if(curr==nullptr || curr->type_ != OperandType::map_t)  return nil_operand;
  for(int i=0; i<s-1; i++) {
    k = keys[i];  //cout << "keys[" << i<< "]: " << keys[i] << "\n";
    next = (AstMap*) curr->get_raw_ptr(k);
    if(curr==nullptr || curr->type_ != OperandType::map_t)  return nil_operand;
    curr = next;
  }

  if(curr==nullptr) {
    //cerr << "curr is null!\n";
    return nil_operand;
  } else
    return curr->getv(keys.back());
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
