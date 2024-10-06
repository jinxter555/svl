#include "entity.hh"


/*
ListEntity::ListEntity(const ListEntity& l) {
  entity_u_ptr new_l = l.clone();
  //members = move(new_l->members);
};
*/
ListEntity nil_list;

ListEntity::ListEntity()  {}
ListEntity::ListEntity(const ListEntity& l) {
  for(auto &e : l.members) {
     members.push_back(e->clone()); 
  }
};

entity_u_ptr ListEntity::clone() const {
  list_u_ptr new_list = make_unique<ListEntity>();

  for(auto &e : members) {
   new_list->members.push_back(e->clone()); 
  }
  return new_list;
}
//--------------------------------------
const Entity& ListEntity::add(const Operand& v)  {
  entity_u_ptr vptr = make_unique<OperandEntity>(v);
  return *add(move(vptr));
}

const Entity& ListEntity::add(const Entity &v) { 
  entity_u_ptr vptr = v.clone();
  return *add(move(vptr)); 
}

//const entity_u_ptr& ListEntity::add(entity_u_ptr &vptr) { members.push_back(move(vptr)); return members.back(); }

const entity_u_ptr& ListEntity::add(entity_u_ptr &&vptr) {
  members.push_back(move(vptr));
  return members.back();
}
const Entity& ListEntity::add(const OperandEntity &k, const Entity& v) 
{ return nil_entity; }; // this is for map not
const Entity& ListEntity::add(const OperandEntity &k, entity_u_ptr&& vptr) 
{ return nil_entity; }; // this is for map not


s_integer ListEntity::size() const { return members.size(); }

//--------------------------------------
const Entity& ListEntity::get(const OperandEntity &key) {
  return get(key._get_int());
}
const Entity& ListEntity::get(int i) {
  if(i > members.size() || i < 0) return nil_entity;
  return *members[i];
}

const ListEntity&  ListEntity::get_list(int i) {
  if(i > members.size() || i<0 ) return nil_list;

  entity_u_ptr &rptr =  members[i];
  //unique_ptr<Entity> &rptr =  members[i];
  //ListEntity* lptr = static_cast<ListEntity*>(rptr.get());
  ListEntity* lptr = dynamic_cast<ListEntity*>(rptr.get());
  //cout << "getlist\n";
  //return rptr;
  cout << "\nin get_list--begin\n";
  lptr->print();
  cout << "in get_list--end\n";
  return *lptr;
}

//--------------------------------------
const Entity& ListEntity::set(const OperandEntity &key, const Entity &v ) {
  entity_u_ptr vptr  = v.clone();
  return set(key, move(vptr) );
}

const Entity& ListEntity::set(const OperandEntity &key, entity_u_ptr &&vptr ) {
  int i = key._get_int();
  if(i > members.size() || i < 0) return nil_entity;
  members[i] = move(vptr);
  return *members[i];
}
//--------------------------------------
OperandEntity ListEntity::to_str() const {
  int i, s = members.size();
  Operand outstr("[");
  if(s==0) {return Operand("[]");}

  for(i=0; i<s-1; i++) {
    outstr = outstr + members[i]->to_str()._to_str() + ",";
  }
  outstr = outstr + members[i]->to_str()._to_str() + "]";
  return outstr;
}

void ListEntity::print() const {
  cout << to_str();
}

OperandEntity ListEntity::get_type() const {
  return Operand(OperandType::list_t);
};

//Entity ListEntity::evaluate(Entity *ctxt) {return entity_undef_error; }

//void ListEntity::print() { cout << *this; }
//--------------------------------------