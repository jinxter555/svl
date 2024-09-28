#pragma once
#include "entity.hh"
#include "list_entity.hh"

class MapEntity : public Entity {
public:

  static MapEntity undef_error; 
  static MapEntity mem_error;
  static MapEntity invalid_error;

  MapEntity();
  MapEntity(const MapEntity& m);
  MapEntity(const Operand &v);

  const Entity& add(const Entity &v) override { return MapEntity::undef_error;};
  const entity_u_ptr& add(entity_u_ptr &vptr) override {return nullptr;};

  const Entity& add(const Entity &k, const Entity& v) override ; 
  //const Entity& add(const Entity &k, entity_u_ptr& vptr) ; 

  inline const Entity&   get(const Entity &k) override ;


  const Entity& set(const Entity &k, const Entity &v) override;
  const Entity& set(const Entity &k, entity_u_ptr &vptr) override;

  const MapEntity&   get_map(const Entity &k) override;
  const ListEntity&  get_list(const Entity &k) override;
  Entity& to_str() const override {};
  entity_u_ptr clone() const override;
  void print() const override;
  void print_list() { cout << "hello mr list!\n"; this->print();}
 // Entity& get_ref(int i) ;

};