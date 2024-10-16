#include "entity.hh"
#include "ast.hh"

const MapEntity nil_map;

MapEntity::MapEntity() : Entity(OperandType::map_t) { parent = nullptr; type_= OperandType::map_t; }

MapEntity::MapEntity(const MapEntity& m) {
  map_u_ptr new_map = make_unique<MapEntity>();

  for (auto const& [key, val] : m.children) {
    new_map->children[key] = visit(GetOperandValue(), val.value_); 
  }
  children = move(new_map->children);
}

entity_u_ptr MapEntity::clone() const {
  map_u_ptr new_map = make_unique<MapEntity>();

  for (auto const& [key, val] : children) {
    new_map->children[key] = visit(GetOperandValue(), val.value_); 
  }
  return new_map;
}

//------------------------------------- 
const Entity& MapEntity::add(const Operand &v) {return nil_map;}
const Entity& MapEntity::add(const Entity &v) {return nil_map;}
const Entity& MapEntity::add(entity_u_ptr&&v) {return nil_map;}
//------------------------------------- 
const Entity& MapEntity::add(const Operand &k, const Entity& v) {
  auto k_str = k._get_str();
  return  add(k_str, v);
}

const Entity& MapEntity::add(const string &k_str, const Entity& v) {
  if(has_key(k_str)) 
    return nil_map;
  //cout << "map adding k: " << k_str << " ev " << v <<"\n";
  children[k_str] = v.clone();
  return  *this;
}
const Entity& MapEntity::add(const Operand &k, const Operand& v) {
  auto k_str = k._get_str();
  return  add(k_str, v);
}
//template <typename T>
//Entity* GetOperand_eptr::operator()(T value) const { return nullptr; }

const Entity& MapEntity::add(const string &k_str, const Operand& v) {
  if(has_key(k_str)) 
    return nil_map;
  children[k_str] = visit(GetOperandValue(), v.value_); 
  //cout << "map adding k: " << k_str << " ov " << v <<"\n";
  return  *this;
}

const Entity& MapEntity::add(const Operand &k, entity_u_ptr&& vptr) {
  auto k_str = k._get_str();
  return add(k_str, move(vptr));
}
const Entity& MapEntity::add(const string &k_str, entity_u_ptr&& vptr) {
  if(vptr==nullptr) return nil_map;
  if(has_key(k_str)) return nil_map;
  children[k_str] = move(vptr);
  return  *this;
}
//------------------------------------- 
bool MapEntity::has_key(const Operand &k)  {
  string k_str = k._get_str();
  return has_key(k);
}
bool MapEntity::has_key(const string  &k)  {
  if (children.find(k) != children.end())  return true;
   return false;
}
//------------------------------------- 
const Operand&  MapEntity::get(const Operand &k) {
  auto k_str = k._get_str();
  return get(k_str);
}

/*
const Operand&  MapEntity::get(const string &k) {
  if(!has_key(k)){
    cerr << "key: " << k << " does not exist!";
    return nil_operand;
  }
  return  children[k];
}
*/

const Operand&  MapEntity::get(const string &k) {
  return get_nonconst(k);
}

Operand&  MapEntity::get_nonconst(const Operand &k) {
  auto k_str = k._get_str();
  return get_nonconst(k_str);
}


Operand&  MapEntity::get_nonconst(const string &k) {
  if(!has_key(k)){
    cerr << "get_nonconst key: " << k << " does not exist!\n";
    return nil_operand;
  }
  return  children[k];
}

Entity*  MapEntity::get_raw_ptr(const Operand &k) {
  auto k_str = k._get_str();
  return get_raw_ptr(k_str);
}

Entity*  MapEntity::get_raw_ptr(const string &k) {
  if(!has_key(k)){
    //cerr << "raw pointer key: " << k << " does not exist!\n";
    return nullptr;
  }
  //auto value = visit(GetOperand_eptr(), children[k].value_);
  auto value = children[k]._get_entity_raw_ptr();
  return  value;
}





const Entity& MapEntity::set(const Operand &k, const Entity &v) {
  entity_u_ptr vptr  = v.clone();
  return set(k, move(vptr));
}

const Entity& MapEntity::set(const Operand &k, const Operand&v) {
  auto k_str = k._get_str();
  if(!has_key(k_str)){
    cerr << "entity setting operand-value key: " << k_str << " does not exist!\n";
    return nil_map;
  }
  children[k_str] = visit(GetOperandValue(), v.value_); 
  return *this;
}


const Entity& MapEntity::set(const Operand &k, entity_u_ptr &&vptr) {
  auto k_str = k._get_str();
  if(!has_key(k_str)){
    cerr << "entity set vptr key: " << k_str << " does not exist!\n";
    return nil_map;
  }
  children[k_str] = move(vptr);
  return  *this;
}

//------------------------------------- 

const ListEntity MapEntity::get_keys() const {
  ListEntity key_list;
  for (auto const& [key, val] : children) {
    key_list.add(Operand(key));
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
Operand MapEntity::to_str() const {
  //vector<Entity> kv_paires ;
  if(children.empty()) return Operand();

  vector<string> kv_paires ;
  string colon(":");
  string q("\"");
  string outstr;

  for (auto const& [key, val] : children) {
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


Operand MapEntity::get_type() const { return Operand(OperandType::map_t); }

void MapEntity::print() const {
  cout << to_str();
}