#include "entity.hh"

class ListEntity : public Entity {
public:
  static ListEntity undef_error; 
  static ListEntity mem_error;

  ListEntity();
  ListEntity(const Operand &v);
  const Entity& add(const Entity &v) override ;
  const entity_u_ptr& add(entity_u_ptr &vptr) override;
  entity_u_ptr add(const Entity &k, const Entity& v) override { return nullptr; }; // this is for map not
  inline const Entity&   get(const Entity &k) override ;
  const Entity&   get(int i) ;

  const Entity& set(const Entity &k, const Entity &v) override;
  const Entity& set(const Entity &k, entity_u_ptr &vptr) override;


 // const MapEntity&   get_map(const Entity &k) override;
  const ListEntity&  get_list(const Entity &k) override;
  const ListEntity&  get_list(int i) ;
  entity_u_ptr clone() const override;
 // Entity& get_ref(int i) ;

};