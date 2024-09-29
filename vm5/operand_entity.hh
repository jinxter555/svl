#pragma once
#include "entity.hh"
#include "list_entity.hh"


class OperandEntity : public Entity {
public:
  static OperandEntity undef_error; 
  static OperandEntity mem_error;
  static entity_u_ptr error;
  OperandEntity();
  OperandEntity(const Operand &v);

  const Entity& add(const Entity &v) override { return undef_error; };

  const entity_u_ptr& add(entity_u_ptr &vptr) override { 
    return error;
  };

  const Entity& add(const Entity &k, const Entity& v) override 
    { return OperandEntity::undef_error; }; // this is for map or list not here

  inline const Entity&   get(const Entity &k) override {return undef_error; };
  const Entity&   get(int i) {return undef_error;};

  const Entity& set(const Entity &k, const Entity &v) override {return undef_error;};
  const Entity& set(const Entity &k, entity_u_ptr &vptr) override {return undef_error;};
 const MapEntity&   get_map(const Entity &k) override {};
  const ListEntity&  get_list(const Entity &k) override {
    return ListEntity::undef_error;
  };
 // Entity& get_ref(int i) ;
  Operand to_str() const override;
  entity_u_ptr clone() const override;

  void print() const override;


  //-------------------------------------------
  using Entity::_get_operand;
  using Operand::operator+;
  using Operand::operator-;
  using Operand::operator*;
  using Operand::operator/;

  using Operand::operator==;
  using Operand::operator!=;
  using Operand::operator>=;
  using Operand::operator<=;
  using Operand::operator<;
  using Operand::operator>;

  using Operand::operator&&;
  using Operand::operator||;
  using Operand::operator!;
};