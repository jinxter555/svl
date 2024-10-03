#include "entity.hh"


MapEntity::MapEntity() {}

MapEntity nil_map;
entity_u_ptr nil_ptr = make_unique<OperandEntity>(); 



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

const Entity& MapEntity::add(const Entity &k, entity_u_ptr& vptr) {
  auto k_str = k._get_operand()._get_str();
  children[k_str] = move(vptr);
  return  *children[k_str];
}

const Entity& MapEntity::add(const Entity &v) { return nil_map;};
const entity_u_ptr& MapEntity::add(entity_u_ptr &vptr) { 
  //entity_u_ptr nptr = make_unique<Entity>();
  //return nptr; 
  //return nullptr;
  return nil_ptr;
};


const Entity&  MapEntity::get(const Entity &k) {
  auto k_str = k._get_operand()._get_str();
  return get(k_str);
}

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

//------------------------------------- 
OperandEntity MapEntity::to_str() const {
  //vector<OperandEntity> kv_paires ;
  ListEntity kv_paires ;
  OperandEntity colon(":");
  OperandEntity q("\"");
  OperandEntity outstr;

  for (auto const& [key, val] : children) {
    outstr = q + OperandEntity(key) + q  + colon + " " + val->to_str();
    kv_paires.add( outstr);
  }

  outstr=OperandEntity("{");
  int i, s = kv_paires.size();
  for(i=0; i<s-1; i++) {
    outstr = outstr + kv_paires.get(i) + ", ";
  }
  outstr = outstr + kv_paires.get(i) + "}";
  return outstr._get_operand();

}
void MapEntity::print() const {
  cout << to_str();
}