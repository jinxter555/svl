#include "entity.hh"

ListEntity ListEntity::undef_error=ListEntity(OperandErrorCode::undefined_t);
ListEntity ListEntity::mem_error=ListEntity(OperandErrorCode::mem_alloc_t);
ListEntity ListEntity::invalid_error=ListEntity(OperandErrorCode::invalid_op_t);

Operand list_type(OperandType::list_t, nil);

//ListEntity::ListEntity() : VEntity (OperandType::list_t) {
ListEntity::ListEntity() : VEntity(list_type) {
  type_ = OperandType::list_t;
}

ListEntity::ListEntity(const Operand& v) : VEntity(v) {}


/*
ListEntity::ListEntity(const ListEntity& l) {
  entity_u_ptr new_l = l.clone();
  //members = move(new_l->members);
};
*/
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
  return *add(vptr);
}

const Entity& ListEntity::add(const Entity &v) { 
  entity_u_ptr vptr = v.clone();
  return *add(vptr); 
}

const entity_u_ptr& ListEntity::add(entity_u_ptr &vptr) {
  members.push_back(move(vptr));
  return members.back();
}
const entity_u_ptr& ListEntity::add(entity_u_ptr &&vptr) {
  members.push_back(move(vptr));
  return members.back();
}
const Entity& ListEntity::add(const Entity &k, const Entity& v) 
{ return ListEntity::invalid_error; }; // this is for map not
const Entity& ListEntity::add(const Entity &k, entity_u_ptr& vptr) 
{ return ListEntity::invalid_error; }; // this is for map not


s_integer ListEntity::size() const { return members.size(); }

//--------------------------------------
const Entity& ListEntity::get(const Entity &key) {
  return get(key._get_int());
}
const Entity& ListEntity::get(int i) {
  if(i > members.size() || i < 0) return ListEntity::undef_error;
  return *members[i];
}

const ListEntity&  ListEntity::get_list(int i) {
  if(i > members.size() || i<0 ) return ListEntity::undef_error;

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
const Entity& ListEntity::set(const Entity &key, const Entity &v ) {
  entity_u_ptr vptr  = v.clone();
  return set(key, vptr );
}

const Entity& ListEntity::set(const Entity &key, entity_u_ptr &vptr ) {
  int i = key._get_int();
  if(i > members.size() || i < 0) return ListEntity::undef_error;
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


//Entity ListEntity::evaluate(Entity *ctxt) {return entity_undef_error; }

//void ListEntity::print() { cout << *this; }
//--------------------------------------