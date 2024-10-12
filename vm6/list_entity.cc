#include "entity.hh"


/*
ListEntity::ListEntity(const ListEntity& l) {
  entity_u_ptr new_l = l.clone();
  //members = move(new_l->members);
};
*/
ListEntity nil_list;

ListEntity::ListEntity() : Entity(OperandType::list_t) {}

ListEntity::ListEntity(const ListEntity& l) {
  for(auto &e : l.members) {
    auto v = visit(GetOperandValue(), e.value_); 
     members.push_back(v); 
  }
};

entity_u_ptr ListEntity::clone() const {
  list_u_ptr new_list = make_unique<ListEntity>();

  for(auto &e : members) {
    auto v = visit(GetOperandValue(), e.value_); 
    new_list->members.push_back(v); 
  }
  return new_list;
}
//--------------------------------------
const Entity& ListEntity::add(const Operand& v)  {
  auto nv = visit(GetOperandValue(), v.value_); 
  members.push_back(nv); 
  return *this;
}

const Entity& ListEntity::add(const Entity &v) { 
  entity_u_ptr vptr = v.clone();
  return add(move(vptr)); 
}

//const entity_u_ptr& ListEntity::add(entity_u_ptr &vptr) { members.push_back(move(vptr)); return members.back(); }

const Entity& ListEntity::add(entity_u_ptr &&vptr) {
  members.push_back(move(vptr));
  return *this;
}

const Entity& ListEntity::add(const Operand &k, const Entity& v) { return nil_list; };
const Entity& ListEntity::add(const Operand &k, const Operand& v) { return nil_list; };
const Entity& ListEntity::add(const Operand &k, entity_u_ptr&& vptr) { return nil_list; }; 


//--------------------------------------
const Operand& ListEntity::get(const Operand &key) {
  return get_nonconst(key._get_int());
}
const Operand& ListEntity::get(int i) {
  return get_nonconst(i);
}
Operand& ListEntity::get_nonconst(const Operand &key) {
  return get_nonconst(key._get_int());
}
Operand& ListEntity::get_nonconst(int i) {
  if(i > members.size() || i < 0) return nil_operand;
  return members[i];
}

Entity * ListEntity::get_raw_ptr(const Operand&k) {
  int i =  k._get_int();
  return  get_raw_ptr(i);
}

Entity*  ListEntity::get_raw_ptr(int i) {
  if(i > members.size() || i < 0) return nullptr;
  auto value = visit(GetOperandValue(), members[i].value_);
  return  std::get<entity_u_ptr>(value).get();
}

//--------------------------------------
s_integer ListEntity::size() const { return members.size(); }

/*
const ListEntity&  ListEntity::get_list(int i) {
  if(i > members.size() || i<0 ) return nil_list;

  entity_u_ptr &rptr =  members[i];
  ListEntity* lptr = dynamic_cast<ListEntity*>(rptr.get());
  cout << "\nin get_list--begin\n";
  lptr->print();
  cout << "in get_list--end\n";
  return *lptr;
}
*/

//--------------------------------------
const Entity& ListEntity::set(const Operand &key, const Operand &v ) {
  int i = key._get_int();
  if(i > members.size() || i < 0) return nil_list;
  members[i] = visit(GetOperandValue(), v.value_); 
  return *this;
}
const Entity& ListEntity::set(const Operand &key, const Entity &v ) {
  entity_u_ptr vptr  = v.clone();
  return set(key, move(vptr) );
}
const Entity& ListEntity::set(const Operand &key, entity_u_ptr &&vptr ) {
  int i = key._get_int();
  if(i > members.size() || i < 0) return nil_list;
  members[i] = move(vptr);
  return *this;
}
//--------------------------------------
Operand ListEntity::to_str() const {
  int i, s = members.size();
  Operand outstr("[");
  if(s==0) {return Operand("[]");}

  for(i=0; i<s-1; i++) {
    outstr = outstr + members[i].to_str() + ",";
  }
  outstr = outstr + members[i].to_str() + "]";
  return outstr;
}

void ListEntity::print() const {
  cout << to_str();
}

Operand ListEntity::get_type() const {
  return Operand(OperandType::list_t);
};

//Entity ListEntity::evaluate(Entity *ctxt) {return entity_undef_error; }

//void ListEntity::print() { cout << *this; }
//--------------------------------------