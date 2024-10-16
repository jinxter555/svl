#pragma once
#include "operand.hh"

extern Operand nil_operand;

class Entity : public Primordial<Entity> {
  friend class OperandEntity;
  friend class ListEntity;
  friend class MapEntity;
  friend class QueNode;
protected:
  virtual Entity *get_raw_ptr(const Operand &k)=0;
public:
  Entity();
  Entity(const OperandType &t);

  virtual entity_u_ptr clone() const = 0;

  //-------------------------------------------
  virtual const Entity& add(const Operand &v) =0;  // for list
  virtual const Entity& add(const Entity &v) =0;  // for list
  virtual const Entity& add(entity_u_ptr &&vptr) =0;  // for list
  //-------------------------------------------
  virtual const Entity& add(const Operand &k, const Entity& v)=0;
  virtual const Entity& add(const Operand &k, const Operand& v)=0;
  virtual const Entity& add(const Operand &k, entity_u_ptr&& vptr)=0;

  virtual const Entity& set(const Operand &k, const Entity& v) = 0;
  virtual const Entity& set(const Operand &k, const Operand& v) = 0;
  virtual const Entity& set(const Operand &k, entity_u_ptr&& vptr) = 0;

  virtual const Operand& get(const Operand &k) = 0;
  virtual Operand&  get_nonconst(const Operand &k) =0;
  //-------------------------------------------
  friend ostream& operator<<(ostream& os, const Entity& e);
  friend ostream& operator<<(ostream& os, const entity_u_ptr& vptr) ;
  //-------------------------------------------

};

class ListEntity : public Entity {
protected:
public:
/*
  static ListEntity undef_error; 
  static ListEntity mem_error;
  static ListEntity invalid_error;
*/
  e_members_t members;
  //vector<unique_ptr<Entity>> members;

  ListEntity();
  ListEntity(const ListEntity& l);


  entity_u_ptr clone() const override;

  const Entity& add(const Operand &v) ;
  const Entity& add(const Entity &v) ;
//  const entity_u_ptr& add(entity_u_ptr &vptr) ;
  const Entity& add(entity_u_ptr &&vptr);

  const Entity& add(const Operand &k, const Entity& v) override final;
  const Entity& add(const Operand &k, const Operand& v) override final;
  const Entity& add(const Operand &k, entity_u_ptr&& vptr) override final;

  const Operand&   get(const Operand &k) override final;
  Operand&  get_nonconst(const Operand &k) override final;
  const Operand&   get(int i) ;
  Operand&   get_nonconst(int i) ;

  Entity *get_raw_ptr(const Operand &k) override final;
  Entity *get_raw_ptr(int i) ;

  const Entity& set(const Operand &k, const Entity &v) override final;
  const Entity& set(const Operand &k, const Operand &v) override final;
  const Entity& set(const Operand &k, entity_u_ptr &&vptr) override final;
  //const ListEntity&  get_list(int i) ;

  s_integer size() const;

  Operand to_str() const override ;
  Operand get_type() const override;

  void print() const override;
};


class MapEntity : public Entity {
friend class QueNode;
public:
  entity_u_ptr parent;
  e_children_t children;

  MapEntity();
  MapEntity(const MapEntity& m);

  entity_u_ptr clone() const override;

//  const Entity& add(const Entity &v) override ;
//  const entity_u_ptr& add(entity_u_ptr &vptr) override ;
  const Entity& add(const Operand &v) override ;
  const Entity& add(const Entity &v) override;
  const Entity& add(entity_u_ptr &&vptr) override;

  const Entity& add(const Operand&k, const Entity& v) override final;
  const Entity& add(const Operand&k, const Operand& v) override final;
  const Entity& add(const Operand &k, entity_u_ptr&& vptr) override final; 

  const Entity& add(const string&k, entity_u_ptr&& vptr) ; 
  const Entity& add(const string &k_str, const Entity& v) ;
  const Entity& add(const string &k_str, const Operand& v) ;

  const Operand& get(const Operand &k) override final;
  const Operand& get(const string &k) ;
  Operand&  get_nonconst(const Operand &k) override final;
  Operand&  get_nonconst(const string &k) ;

  const Entity& set(const Operand &k, const Entity &v) override final;
  const Entity& set(const Operand &k, const Operand& v) override final;
  const Entity& set(const Operand &k, entity_u_ptr &&vptr) override final;

  Entity *get_raw_ptr(const Operand &k) override final;
  Entity *get_raw_ptr(const string &k);


  inline bool has_key(const string &k) ;
  inline bool has_key(const Operand &k) ;

  Operand to_str() const override;
  Operand get_type() const;

  void print() const override;

  const ListEntity get_keys() const;
  vector<string> get_keys_vecstr() const;


};

/*
class OperandEntity : public Entity {
protected:
  Operand value_;
  OperandType type_;
public:
  static entity_u_ptr error;
  OperandEntity();
  OperandEntity(const Operand &v);
  void print() const ;
  entity_u_ptr clone() const override;
  OperandEntity to_str() const override;
  const string _to_str() const;

  s_integer _get_int() const;
  s_float _get_float() const;

  Operand _get_operand() const override final; 
  OperandEntity operator=(const OperandEntity &v);
  OperandEntity opfunc(const OperandEntity& other, AstOpCode op);
  OperandEntity get_type() const;
};
*/