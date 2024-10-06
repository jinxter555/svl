
#include "operand.hh"

class OperandEntity;
extern OperandEntity nil_entity;

class Entity {
  friend class OperandEntity;
  friend class ListEntity;
  friend class MapEntity;
public:
  virtual entity_u_ptr clone() const = 0;
  virtual OperandEntity to_str() const =0;
  virtual OperandEntity get_type() const=0;
  virtual void print() const =0;
  //-------------------------------------------
  friend ostream& operator<<(ostream& os, const Entity& e);
  friend ostream& operator<<(ostream& os, const entity_u_ptr& vptr) ;
};

class VEntity : public Entity {
public:
  VEntity();

  //-------------------------------------------
  virtual const Entity& add(const OperandEntity &k, entity_u_ptr&& vptr)=0 ;  // for bison and ast to add 

  virtual const Entity& add(const OperandEntity &k, const Entity& v)=0;   // for map
  virtual const Entity& set(const OperandEntity &k, entity_u_ptr&& vptr) = 0;

  virtual const Entity& set(const OperandEntity &k, const Entity &v) = 0;
  virtual const Entity& get(const OperandEntity &k) = 0;
};

class ListEntity : public VEntity {
protected:
public:
  static ListEntity undef_error; 
  static ListEntity mem_error;
  static ListEntity invalid_error;

  e_members_t members;
  //vector<unique_ptr<Entity>> members;

  ListEntity();
  ListEntity(const ListEntity& l);

  entity_u_ptr clone() const override;

  const Entity& add(const Operand &v) ;
  const Entity& add(const Entity &v) ;
//  const entity_u_ptr& add(entity_u_ptr &vptr) ;
  const entity_u_ptr& add(entity_u_ptr &&vptr);

  const Entity& add(const OperandEntity &k, const Entity& v) override final;
  const Entity& add(const OperandEntity &k, entity_u_ptr&& vptr) override final;

  const Entity&   get(const OperandEntity &k) override final;
  const Entity&   get(int i) ;
  const Entity& set(const OperandEntity &k, const Entity &v) override final;
  const Entity& set(const OperandEntity &k, entity_u_ptr &&vptr) override final;
  const ListEntity&  get_list(int i) ;

  s_integer size() const;

  OperandEntity  to_str() const override ;
  OperandEntity get_type() const override;

  void print() const override;
};


class MapEntity : public VEntity {
public:
  entity_u_ptr parent;
  e_children_t children;

  MapEntity();
  MapEntity(const MapEntity& m);

  entity_u_ptr clone() const override;

//  const Entity& add(const Entity &v) override ;
//  const entity_u_ptr& add(entity_u_ptr &vptr) override ;

  const Entity& add(const OperandEntity &k, const Entity& v) override final;

  // have to use && to allow only move operator here. &&vptr to prevent segfault
  const Entity& add(const OperandEntity &k, entity_u_ptr&& vptr) override final; 
  //const Entity& add(const Operand&k, entity_u_ptr& vptr) ;  // no need
  const Entity& add(const string&k, entity_u_ptr&& vptr) ; 

  const Entity& add(const string &k_str, const Entity& v) ;
  const Entity& add(const string &k_str, const Operand& v) ;

  const Entity& get(const OperandEntity &k) override final;
  const Entity& get(const string &k) ;

  const Entity& set(const OperandEntity &k, const Entity &v) override final;
  const Entity& set(const OperandEntity &k, entity_u_ptr &&vptr) override final;


  inline bool has_key(const string &k) ;
  inline bool has_key(const OperandEntity &k) ;

  OperandEntity to_str() const override;

  void print() const override;

  const ListEntity get_keys() const;
  vector<string> get_keys_vecstr() const;
  OperandEntity get_type() const;


};

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

  Operand _get_operand() const; 
  OperandEntity operator=(const OperandEntity &v);
  OperandEntity opfunc(const OperandEntity& other, AstOpCode op);
  OperandEntity get_type() const;
};