#include "map_entity.hh"


MapEntity MapEntity::undef_error=MapEntity(OperandErrorCode::undefined_t);
MapEntity MapEntity::mem_error=MapEntity(OperandErrorCode::mem_alloc_t);
MapEntity MapEntity::invalid_error=MapEntity(OperandErrorCode::invalid_op_t);

MapEntity::MapEntity() { type_ = OperandType::map_t; }
MapEntity::MapEntity(const Operand& v) : Entity(v) { type_ = OperandType::err_t; }


void MapEntity::print() const {
  if(children.empty()) {cout << "{}"; return;}

  cout << "{";
  for (auto const& [key, val] : children) {
    std::cout << key << ':'  << val << ",";
  }
  cout << "}";
}

entity_u_ptr MapEntity::clone() const {
  entity_u_ptr new_map = make_unique<MapEntity>();

  for (auto const& [key, val] : children) {
   new_map->children[key]=(val->clone()); 
  }

  return new_map;
}

const Entity& MapEntity::add(const Entity &k, const Entity& v) {
  auto k_str = k._get_operand()._get_str();
  if(children[k_str] != nullptr) {
    cerr << "key: " << k_str << " already exist!";
    return MapEntity::invalid_error;
  }
  children[k_str] = v.clone();
  return  *children[k_str];
}

const Entity& MapEntity::add(const Entity &k, entity_u_ptr& vptr) {
  auto k_str = k._get_operand()._get_str();
  children[k_str] = move(vptr);
  return  *children[k_str];

}


const Entity&   MapEntity::get(const Entity &k) {
  auto k_str = k._get_operand()._get_str();
  if(children[k_str] == nullptr) {
    cerr << "key: " << k_str << " does not exist!";
    return MapEntity::undef_error;
  }
  return  *children[k_str];
}
const Entity& MapEntity::set(const Entity &k, const Entity &v) {
  entity_u_ptr vptr  = v.clone();
  return set(k, vptr);
}

const Entity& MapEntity::set(const Entity &k, entity_u_ptr &vptr) {
  auto k_str = k._get_operand()._get_str();
  if(children[k_str] == nullptr) {
    cerr << "key: " << k_str << " does not exist!";
    return MapEntity::undef_error;
  }
  children[k_str] = move(vptr);
  return  *children[k_str];
}

//------------------------------------- entity 
bool MapEntity::has_key(const Entity &k)  {
  auto k_str = k._get_operand()._get_str();
  return has_key(k);
}
bool MapEntity::has_key(const string  &k)  {
  if(children[k] == nullptr)
    return false;
  return true;
}
//------------------------------------- entity : list

const MapEntity& MapEntity::get_map(const Entity &k) {

} 
const ListEntity& MapEntity::get_list(const Entity &k) {

}
Operand MapEntity::to_str() const {
  return Operand("{}");
}