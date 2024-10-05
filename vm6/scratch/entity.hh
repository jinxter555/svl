#ifndef _ENTITY_H_
#define _ENTITY_H_

#pragma once
#include "operand.hh"

class Entity : public Operand {
  friend class OperandEntity;
  friend class ListEntity;
  friend class MapEntity;
protected:
  //map<string, entity_u_ptr> children;
  unordered_map<string, entity_u_ptr> children;
  vector<entity_u_ptr> members;
  entity_u_ptr  parent;
public:
  Entity();
  Entity(const Operand&);
  Entity(const OperandType);
  Entity(const Entity &v) ;

  //-------------------------------------------
  friend ostream& operator<<(ostream& os, const Entity& e);
  friend ostream& operator<<(ostream& os, const entity_u_ptr& vptr) ;
  //-------------------------------------------
  virtual entity_u_ptr clone() const = 0;
  virtual void print() const =0;
  virtual OperandEntity to_str() const =0;
  virtual Operand _get_operand() const =0; 
};

class OperandEntity : public Entity {
public:
  static entity_u_ptr error;
  OperandEntity();
  OperandEntity(const Operand &v);
  void set(const OperandEntity &v);
  void print() const ;
  entity_u_ptr clone() const override;
  OperandEntity to_str() const override;
  const string _to_str() const;
  Operand _get_operand() const  override; 
  OperandEntity operator=(const OperandEntity &v);

};

class VEntity :  public Entity {
public:
  VEntity();
  //VEntity(const OperandType);
  VEntity(const Operand&);
  //-------------------------------------------
  //virtual const Entity& add(const Entity& v)=0;
  //virtual const entity_u_ptr& add(entity_u_ptr &vptr) =0;    // for list

  virtual const Entity& add(const Entity &k, entity_u_ptr& vptr)=0 ;  // for bison and ast to add 
  virtual const Entity& add(const Entity &k, const Entity& v)=0;   // for map

  virtual const Entity& get(const Entity &k) = 0;
  virtual const Entity& set(const Entity &k, const Entity &v) = 0;
  virtual const Entity& set(const Entity &k, entity_u_ptr &vptr) = 0;

};

class ListEntity : public VEntity {
protected:
public:
  static ListEntity undef_error; 
  static ListEntity mem_error;
  static ListEntity invalid_error;

  ListEntity();
  ListEntity(const ListEntity& l);
  ListEntity(const Operand &v);
  const Entity& add(const Entity &v) ;
  const entity_u_ptr& add(entity_u_ptr &vptr) ;
  const entity_u_ptr& add(entity_u_ptr &&vptr);

  const Entity& add(const Entity &k, const Entity& v) override ;
  const Entity& add(const Entity &k, entity_u_ptr& vptr) override ;

  const Entity&   get(const Entity &k) override ;
  const Entity&   get(int i) ;
  const Entity& set(const Entity &k, const Entity &v) override;
  const Entity& set(const Entity &k, entity_u_ptr &vptr) override;
  const ListEntity&  get_list(int i) ;

  s_integer size() const;


  OperandEntity to_str() const override ;
  Operand _get_operand() const override ;
  entity_u_ptr clone() const override;
  void print() const override;
};


class MapEntity : public VEntity {
public:
  MapEntity();
  //MapEntity(const MapEntity& m);

  entity_u_ptr clone() const override;

//  const Entity& add(const Entity &v) override ;
//  const entity_u_ptr& add(entity_u_ptr &vptr) override ;

  const Entity& add(const Entity &k, const Entity& v) override ; 
  const Entity& add(const Entity &k, entity_u_ptr& vptr) override; 
  const Entity& add(const string &k_str, const Entity& v) ;

  const Entity& get(const Entity &k) override ;
  const Entity& get(const string &k) ;

  const Entity& set(const Entity &k, const Entity &v) override;
  const Entity& set(const Entity &k, entity_u_ptr &vptr) override;


  inline bool has_key(const string &k) ;
  inline bool has_key(const Entity &k) ;

  OperandEntity to_str() const override;
  Operand _get_operand() const override;

  void print() const override;

  const ListEntity get_keys() const;
  vector<string> get_keys_vecstr() const;



};

#endif