#include "ast_map.hh"
#include "operand.hh"

AstMap::AstMap() : AstExpr(OperandType::map_t) {}

astexpr_u_ptr AstMap::clone() const {
  map_u_ptr new_map = make_unique<AstMap>();

  for (auto const& [key, val] : map_) {
    new_map->map_[key] = val.clone();
  }
  return new_map;
}

astexpr_u_ptr AstMap::evaluate(astexpr_u_ptr& ast_ctxt) {
  return nullptr;
}

Operand& AstMap::getv()  {
  return nil_operand;
}

Operand& AstMap::getv(const Operand &k)  {
  return(getv(k._get_str()));
}
Operand& AstMap::getv(const string &k)  {
  if(this==nullptr || !has_key(k)){
    cerr << "getv key: " << k << " does not exist!\n";
    return nil_operand;
  }
  return  map_[k];

}

astexpr_u_ptr& AstMap::get_u_ptr(const Operand &k) {
  auto k_str = k._get_str();
  return get_u_ptr(k_str);
}
astexpr_u_ptr& AstMap::get_u_ptr(const string &k) {
  if(this == nullptr || !has_key(k)){
    return nil_ast_ptr;
  }
  return map_[k]._get_astexpr_u_ptr();
}

AstExpr *AstMap::get_raw_ptr(const Operand &k) {
  auto k_str = k._get_str();
  return get_raw_ptr(k_str);
}
AstExpr *AstMap::get_raw_ptr(const string &k) {
  if(this == nullptr || !has_key(k)){
    //cerr << "raw pointer key: " << k << " does not exist!\n";
    return nullptr;
  }
  //auto value = visit(GetOperand_eptr(), children[k].value_);
  return map_[k]._get_astexpr_raw_ptr();

}


//--------------------------------------
bool AstMap::add(const AstExpr& v)  { return false; }
bool AstMap::add(astexpr_u_ptr &&vptr) { return false; }
//--------------------------------------
bool AstMap::add(const Operand &k, const AstExpr& v, bool overwrite) {
  return add(k._get_str(), v, overwrite);
}
bool AstMap::add(const string &k, const AstExpr& v, bool overwrite) {
  if(this==nullptr) {return false;}
  if(!overwrite && has_key(k)) return false;
  map_[k] = move(v.clone());
  return true;
}

bool AstMap::add(const Operand &k, astexpr_u_ptr&& vptr, bool overwrite) {
  return add(k._get_str(), move(vptr), overwrite);
}
bool AstMap::add(const string &k, astexpr_u_ptr&& vptr, bool overwrite) {
  if(this==nullptr) {return false;}

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

//------------------------------------- 
Operand& AstMap::get_branch(const vector<string> &keys) {
  int i=0, s = keys.size();  
  string k; AstMap *curr=this, *next;

  if(curr==nullptr || curr->type_ != OperandType::map_t)  return nil_operand;
  for(int i=0; i<s-1; i++) {
    k = keys[i]; // cout << "keys[" << i<< "]: " << keys[i] << "\n";
    next = (AstMap*) curr->get_raw_ptr(k);
    if(curr==nullptr || curr->type_ != OperandType::map_t)  return nil_operand;
    curr = next;
  }

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
bool AstMap::has_key(const Operand &k)  {
  string k_str = k._get_str();
  return has_key(k_str);
}
bool AstMap::has_key(const string  &k)  {
  if(this==nullptr || type_ != OperandType::map_t) return false;
  if (map_.find(k) != map_.end())  {
    return true;
  }
  return false;
}
//------------------------------------- 
s_integer  AstMap::size() const { return map_.size(); }
void AstMap::print() const { cout << to_str(); }
Operand AstMap::get_type() const { return Operand(OperandType::map_t); }

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
