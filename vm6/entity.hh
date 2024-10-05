
#include "operand.hh"

class Entity {
  friend class OperandEntity;
  friend class ListEntity;
  friend class MapEntity;
protected:
  Operand value_;
  OperandType type_;
public:
  Entity();
  Entity(const Operand&);
  Entity(const OperandType);
  Entity(const Entity &v) ;

  s_integer _get_int() const;
  s_float _get_float() const;
  string  _to_str() const;

  Operand _get_operand() const;
  OperandEntity get_type() const;
  //-------------------------------------------
  virtual entity_u_ptr clone() const = 0;
  virtual void print() const =0;
  virtual OperandEntity to_str() const =0;
  //-------------------------------------------
  friend ostream& operator<<(ostream& os, const Entity& e);
  friend ostream& operator<<(ostream& os, const entity_u_ptr& vptr) ;
};

class VEntity : public Entity {
public:
  VEntity();
  VEntity(const Operand& v);

  //-------------------------------------------
  virtual const Entity& add(const Entity &k, entity_u_ptr& vptr)=0 ;  // for bison and ast to add 
  virtual const Entity& add(const Entity &k, const Entity& v)=0;   // for map
  virtual const Entity& set(const Entity &k, entity_u_ptr &vptr) = 0;
  virtual const Entity& set(const Entity &k, const Entity &v) = 0;
  virtual const Entity& get(const Entity &k) = 0;
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
  ListEntity(const Operand &v);

  entity_u_ptr clone() const override;

  const Entity& add(const Operand &v) ;
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


  OperandEntity  to_str() const override ;
  void print() const override;
  using Entity::get_type;
};


class MapEntity : public VEntity {
public:
  entity_u_ptr parent;
  e_children_t children;

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

  void print() const override;

  const ListEntity get_keys() const;
  vector<string> get_keys_vecstr() const;

  using Entity::get_type;

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
  Operand _get_operand() const; 
  OperandEntity operator=(const OperandEntity &v);
  OperandEntity opfunc(const OperandEntity& other, AstOpCode op);
  using Entity::get_type;
};