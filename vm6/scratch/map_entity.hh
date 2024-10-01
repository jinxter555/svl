#pragma once
#include "entity.hh"
#include "list_entity.hh"
#include "operand_entity.hh"

class MapEntity : public Entity {
public:
  static MapEntity error;

  static MapEntity undef_error; 
  static MapEntity mem_error;
  static MapEntity invalid_error;

  MapEntity();
  //MapEntity(const MapEntity& m);
  MapEntity(const Operand &v);

  entity_u_ptr clone() const override;

  const Entity& add(const Entity &v) override { return MapEntity::undef_error;};

  const entity_u_ptr& add(entity_u_ptr &vptr) override { return *Entity::error ; };

  const Entity& add(const Entity &k, const Entity& v) override ; 
  const Entity& add(const Entity &k, entity_u_ptr& vptr) override; 

  const Entity& get(const string &k) ;
  const Entity&   get(const Entity &k) override ;

  const Entity& set(const Entity &k, const Entity &v) override;
  const Entity& set(const Entity &k, entity_u_ptr &vptr) override;

  //const map_u_ptr&   get_map(const Entity &k) override;
  //const ListEntity&  get_list(const Entity &k) override;

  inline bool has_key(const string &k) ;
  inline bool has_key(const Entity &k) ;

  using Operand::_get_type;  // for error handling to findout if err_t instead of map_t

  Operand to_str() const override;
  void print() const override;

  const ListEntity get_keys() const;
  vector<string> get_keys_vecstr() const;

};