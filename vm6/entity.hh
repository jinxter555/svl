#ifndef _ENTITY_H_
#define _ENTITY_H_

#pragma once

#include "lang.hh"
#include "operand.hh"

class Entity; using entity_u_ptr = unique_ptr<Entity>;
class OperandEntity; using oe_u_ptr = unique_ptr<OperandEntity>;
class ListEntity; using le_u_ptr = unique_ptr<ListEntity>;
class MapEntity; using me_u_ptr = unique_ptr<MapEntity>;

//using EntityVariant = variant<entity_u_ptr, oe_u_ptr, le_u_ptr,  me_u_ptr>;
using EntityVariant = variant<entity_u_ptr, oe_u_ptr>;
//using EntityVariant = variant<entity_u_ptr, oe_u_ptr>;


class Entity : public Operand {
  friend class OperandEntity;
  friend class ListEntity;
protected:
  //vector<entity_u_ptr> members;
  vector<EntityVariant> members;
  //unordered_map<string, entity_u_ptr> children;
  //map<string, entity_u_ptr> children;
  entity_u_ptr  parent;
  Operand operation_status; // errors operating on members or children 
public:
  Entity();
  Entity(const Operand&);
  Entity(const Entity &v) ;
  //-------------------------------------------
  virtual entity_u_ptr clone() const = 0;
  virtual const Entity& add(const Entity& v)=0;
  virtual const entity_u_ptr& add(entity_u_ptr &vptr) =0;    // for list

  virtual const Entity& add(const Entity &k, entity_u_ptr& vptr)=0 ;  // for bison and ast to add 
  virtual const Entity& add(const Entity &k, const Entity& v)=0;   // for map

  virtual const Entity& get(const Entity &k) = 0;
  virtual const Entity& set(const Entity &k, const Entity &v) = 0;
  virtual const Entity& set(const Entity &k, entity_u_ptr &vptr) = 0;

  virtual Operand to_str() const = 0;
  virtual void print() const =0;
  //-------------------------------------------
  friend ostream& operator<<(ostream& os, const Entity& e);
  friend ostream& operator<<(ostream& os, const entity_u_ptr& vptr) ;
  //-------------------------------------------
};

class OperandEntity : public Entity {
public:
  static OperandEntity undef_error; 
  static OperandEntity mem_error;
  static entity_u_ptr error;
  OperandEntity();
  OperandEntity(const Operand &v);

  const Entity& add(const Entity &v) override { return undef_error; };

  const entity_u_ptr& add(entity_u_ptr &vptr) override { return error; };

  const Entity& add(const Entity &k, const Entity& v) override 
    { return OperandEntity::undef_error; }; // this is for map or list not here
  const Entity& add(const Entity &k, entity_u_ptr& vptr) override { return OperandEntity::undef_error;}; 

  inline const Entity&   get(const Entity &k) override {return undef_error; };
  const Entity&   get(int i) {return undef_error;};

  const Entity& set(const Entity &k, const Entity &v) override {return undef_error;};
  const Entity& set(const Entity &k, entity_u_ptr &vptr) override {return undef_error;};

  Operand to_str() const override;
  entity_u_ptr clone() const override;

  void print() const override;
};


#endif