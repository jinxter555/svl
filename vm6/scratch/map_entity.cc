#include "entity.hh"


MapEntity::MapEntity() {}

MapEntity nil_map;



entity_u_ptr MapEntity::clone() const {
  entity_u_ptr new_map = make_unique<MapEntity>();

  for (auto const& [key, val] : children) {
   new_map->children[key]=(val->clone()); 
  }

  return new_map;
}

const Entity& MapEntity::add(const Entity &k, const Entity& v) {
  auto k_str = k._get_operand()._get_str();
  auto k_o = k._get_operand();

  cout << "k_str: " << k_str << "\n";
  //if(children[k_str] != nullptr) { 
  if(has_key(k_str)) {
    cerr << "key: " << k_str << " already exist!";
    return nil_map;
  }
  children[k_str] = v.clone();
  return  *children[k_str];
}

const Entity& MapEntity::add(const Entity &k, entity_u_ptr& vptr) {
  auto k_str = k._get_operand()._get_str();
  children[k_str] = move(vptr);
  return  *children[k_str];

}
const Entity& MapEntity::add(const Entity &v) { return nil_map;};
const entity_u_ptr& MapEntity::add(entity_u_ptr &vptr) { return nullptr; };


const Entity&  MapEntity::get(const Entity &k) {
  auto k_str = k._get_operand()._get_str();
  return get(k_str);
}
//const Entity&  MapEntity::get(const entity_u_ptr &k) { }

const Entity&  MapEntity::get(const string &k) {
  if(!has_key(k)){
    cerr << "key: " << k << " does not exist!";
    return nil_map;
  }
  return  *children[k];
}



const Entity& MapEntity::set(const Entity &k, const Entity &v) {
  entity_u_ptr vptr  = v.clone();
  return set(k, vptr);
}

const Entity& MapEntity::set(const Entity &k, entity_u_ptr &vptr) {
  auto k_str = k._get_operand()._get_str();
  //if(children[k_str] == nullptr) {
  if(!has_key(k_str)){
    cerr << "key: " << k_str << " does not exist!";
    return nil_map;
  }
  children[k_str] = move(vptr);
  return  *children[k_str];
}

//------------------------------------- 
bool MapEntity::has_key(const Entity &k)  {
  string k_str = k._get_operand()._get_str();
  return has_key(k);
}
bool MapEntity::has_key(const string  &k)  {
  //if(children[k] == nullptr)
  if(!children[k])
    return false;
  return true;
}
//------------------------------------- 
Operand MapEntity::to_str() const {
  vector<Operand> kv_paires ;
  Operand colon(":");
  Operand q("\"");

  for (auto const& [key, val] : children) {
    Operand outstr = q + Operand(key) + q  + colon + " " + val->to_str();
    kv_paires.push_back(outstr);
  }

  int i, s = kv_paires.size();
  Operand outstr("{");
  for(i=0; i<s-1; i++) {
    outstr = outstr + kv_paires[i] + ", ";
  }
  outstr = outstr + kv_paires[i] + "}";
  return outstr;

}

const ListEntity MapEntity::get_keys() const {
  ListEntity key_list;
  for (auto const& [key, val] : children) {
    key_list.add(OperandEntity(key));
    Operand v = val->to_str();
  }
  return key_list;
}
vector<string> MapEntity::get_keys_vecstr() const {
  vector<string> key_list;
  for (auto const& [key, val] : children) {
    key_list.push_back(key);
  }
  return key_list;
}

Operand MapEntity::_get_operand() const { 
  return Operand();
}

void MapEntity::print() const {
  cout << to_str();
/*
  if(children.empty()) {cout << "{}"; return;}

  cout << "{";
  for (auto const& [key, val] : children) {
    std::cout << key << ':'  << val << ",";
  }
  cout << "}";
*/
}

/*
const map_u_ptr& MapEntity::get_map(const Entity &k) {
  auto k_str = k._get_operand()._get_str();
  if(!has_key(k_str)) return nullptr;

  return  *children[k_str];

} 
const ListEntity& MapEntity::get_list(const Entity &k) {
  return ListEntity::undef_error;

}
*/