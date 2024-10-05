#include "entity.hh"

const MapEntity nil_map;
entity_u_ptr nil_ptr = make_unique<OperandEntity>(); 

MapEntity::MapEntity() { parent = nullptr; }
MapEntity::MapEntity(const MapEntity& m) {
  map_u_ptr new_map = make_unique<MapEntity>();

  for (auto const& [key, val] : m.children) {
   new_map->children[key]=(val->clone()); 
  }
  children = move(new_map->children);
}

entity_u_ptr MapEntity::clone() const {
  map_u_ptr new_map = make_unique<MapEntity>();

  for (auto const& [key, val] : children) {
   new_map->children[key]=(val->clone()); 
  }
  return new_map;
}

//------------------------------------- 
const Entity& MapEntity::add(const OperandEntity &k, const Entity& v) {
  auto k_str = k._get_operand()._get_str();
  return  add(k_str, v);
}

const Entity& MapEntity::add(const string &k_str, const Entity& v) {
  if(has_key(k_str)) 
    return nil_map;
  children[k_str] = v.clone();
  return  *children[k_str];
}

const Entity& MapEntity::add(const OperandEntity &k, entity_u_ptr& vptr) {
  auto k_str = k._get_operand()._get_str();
  children[k_str] = move(vptr);
  return  *children[k_str];
}
//------------------------------------- 
bool MapEntity::has_key(const OperandEntity &k)  {
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
const Entity&  MapEntity::get(const OperandEntity &k) {
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



const Entity& MapEntity::set(const OperandEntity &k, const Entity &v) {
  entity_u_ptr vptr  = v.clone();
  return set(k, vptr);
}

const Entity& MapEntity::set(const OperandEntity &k, entity_u_ptr &vptr) {
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

//------------------------------------- 
OperandEntity MapEntity::to_str() const {
  //vector<OperandEntity> kv_paires ;
  if(children.empty()) return Operand();

  vector<Operand> kv_paires ;
  Operand colon(":");
  Operand q("\"");
  Operand outstr;

  for (auto const& [key, val] : children) {
    outstr = q + key + q  + colon + " " + val->to_str()._to_str();
    kv_paires.push_back(visit(GetOperandValue(), outstr.value_));
  }

  outstr=Operand("{");
  int i, s = kv_paires.size();
  for(i=0; i<s-1; i++) {
    outstr = outstr + kv_paires[i] + ", ";
  }
  outstr = outstr + kv_paires[i] + "}";
  return OperandEntity(outstr);
}


OperandEntity MapEntity::get_type() const { return Operand(OperandType::map_t); }

void MapEntity::print() const {
  cout << to_str();
}