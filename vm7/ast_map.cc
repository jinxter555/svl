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

const Operand& AstMap::getv()  {
  return nil_operand;
}

const Operand& AstMap::getv(const Operand &k)  {
  return(getv(k._get_str()));
}
const Operand& AstMap::getv(const string &k)  {
  if(!has_key(k)){
    cerr << "key: " << k << " does not exist!";
    return nil_operand;
  }
  return  map_[k];

}

const astexpr_u_ptr& AstMap::getptr(const Operand &k) {
  return nil_ast_ptr;
}
AstExpr *AstMap::get_raw_ptr(const Operand &k) {
  auto k_str = k._get_str();
  return get_raw_ptr(k_str);
}
AstExpr *AstMap::get_raw_ptr(const string &k) {
  if(!has_key(k)){
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
bool AstMap::add(const Operand &k, const AstExpr& v) {
  return add(k._get_str(), v);
}
bool AstMap::add(const string &k, const AstExpr& v) {
  if(has_key(k)) return false;
  map_[k] = move(v.clone());
  return true; 
}

bool AstMap::add(const Operand &k, astexpr_u_ptr&& vptr) {
  return add(k._get_str(), move(vptr));
}
bool AstMap::add(const string &k, astexpr_u_ptr&& vptr) {
  if(vptr==nullptr) return false;
  if(has_key(k)) return false;
  map_[k] = move(vptr);
  return true; 
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
  return has_key(k);
}
bool AstMap::has_key(const string  &k)  {
  if (map_.find(k) != map_.end())  return true;
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
