#include "list_entity.hh"

ListEntity ListEntity::undef_error=ListEntity(OperandErrorCode::undefined_t);
ListEntity ListEntity::mem_error=ListEntity(OperandErrorCode::mem_alloc_t);

ListEntity::ListEntity() { type_ = OperandType::list_t; }
ListEntity::ListEntity(const Operand& v) : Entity(v) { type_ = OperandType::err_t; }

const Entity& ListEntity::add(const Entity &v) { 
  entity_u_ptr vptr = v.clone();
  return *add(vptr); 
}

const entity_u_ptr& ListEntity::add(entity_u_ptr &vptr) {
  members.push_back(move(vptr));
  return members.back();
}


const Entity& ListEntity::get(const Entity &key) {
  return get(key._get_int());
}
const Entity& ListEntity::get(int i) {
  //if(i > members.size()) return entity_undef_error;
  return *members[i];
}

const ListEntity&  ListEntity::get_list(const Entity &key) {
  return get_list(key._get_int());
}
const ListEntity&  ListEntity::get_list(int i) {
//  if(i > members.size() || i<0 ) return Entity::entity_undef_error;
  entity_u_ptr &rptr =  members[i];
  //unique_ptr<Entity> &rptr =  members[i];
  //ListEntity* lptr = static_cast<ListEntity*>(rptr.get());
  ListEntity* lptr = dynamic_cast<ListEntity*>(rptr.get());
  //cout << "getlist\n";
  //return rptr;

  return *lptr;
}

const Entity& ListEntity::set(const Entity &key, const Entity &v ) {
  entity_u_ptr vptr  = v.clone();
  return set(key, vptr );
}

const Entity& ListEntity::set(const Entity &key, entity_u_ptr &vptr ) {
  int i = key._get_int();
  // if(i > members.size() || i < 0) return entity_undef_error;
  members[i] = move(vptr);
  return *members[i];
}

entity_u_ptr ListEntity::clone() const {
  entity_u_ptr new_list = make_unique<ListEntity>();

  for(auto &e : members) {
   new_list->members.push_back(e->clone()); 
  }
  return new_list;
}

//Entity ListEntity::evaluate(Entity *ctxt) {return entity_undef_error; }

//void ListEntity::print() { cout << *this; }
//--------------------------------------