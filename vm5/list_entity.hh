#pragma once
#include "entity.hh"
#include "map_entity.hh"

class ListEntity : public Entity {
public:
  static ListEntity undef_error; 
  static ListEntity mem_error;
  static ListEntity invalid_error;

  ListEntity();
  ListEntity(const ListEntity& l);
  ListEntity(const Operand &v);
  const Entity& add(const Entity &v) override ;
  const entity_u_ptr& add(entity_u_ptr &vptr) override;

  const Entity& add(const Entity &k, const Entity& v) 
    override { return ListEntity::invalid_error; }; // this is for map not
  const Entity& add(const Entity &k, entity_u_ptr& vptr) 
    override { return ListEntity::invalid_error; }; // this is for map not


  const Entity&   get(const Entity &k) override ;
  const Entity&   get(int i) ;


  const Entity& set(const Entity &k, const Entity &v) override;
  const Entity& set(const Entity &k, entity_u_ptr &vptr) override;


  //const MapEntity&   get_map(const Entity &k) override;
  //const ListEntity&  get_list(const Entity &k) override;
  const ListEntity&  get_list(int i) ;

  using Operand::_get_type;  // for error handling to findout if err_t instead of map_t

  Operand to_str() const override ;
  entity_u_ptr clone() const override;
  void print() const override;
  void print_list() { cout << "hello mr list!\n"; this->print();}
 // Entity& get_ref(int i) ;

};