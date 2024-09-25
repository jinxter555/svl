#include "ast.hh"

AstExpr::AstExpr() {}
AstExpr::~AstExpr() {}

//-------------------------------------- Ast List
AstList::AstList() { type_ = OperandType::list_t; }

void AstList::add(const Entity &v) {
  members.push_back(v);
}
Entity AstList::get(int i) const {
  if(i > members.size()) 
    return entity_undef_error;
  return members[i];
}
Entity& AstList::get_ref(int i) {
  if(i > members.size()) 
    return entity_undef_error;
  return members[i];
}
Entity AstList::set(int i, const Entity &v ) {
  if(i > members.size()) 
    return entity_undef_error;
  members[i] = v ;
  return v;
}
Entity AstList::evaluate(Entity *ctxt) {return entity_undef_error; }
void AstList::print() {
  cout << *this;
}
//--------------------------------------
//-------------------------------------- Ast Map
AstMap::AstMap() { type_ = OperandType::map_t; }

void AstMap::add_ptr(const string &k, entity_ptr vptr) {
  children[k] = vptr;
}
void AstMap::add(const string &k, const Entity &v) {
  entity_ptr vptr  = make_shared<Entity>(v);
  add_ptr(k, vptr);
}

entity_ptr AstMap::get_node_ptr(const string &k) {
  if (children.find(k) != children.end())  
    return children[k];
  return nullptr;
}

Entity AstMap::get(const string &k) {
  entity_ptr vptr = get_node_ptr(k);
  if(vptr==nullptr) return entity_undef_error;
  return *vptr;
}

Entity AstMap::set(const string &k, const Entity &v) {
  if (children.find(k) != children.end()) {
    children[k] = make_shared<Entity>(v);
    return *children[k];
  }
  return entity_undef_error;
}

Entity AstMap::evaluate(Entity *ctxt) { return entity_undef_error; }

void AstMap::print() {
  cout << *this;
}