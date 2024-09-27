#include "ast.hh"
//-------------------------------------- Ast Map
AstMap::AstMap() { type_ = OperandType::map_t; }

entity_ptr AstMap::add_ptr(const string &k, entity_ptr vptr) {
  children[k] = vptr;
  return vptr;
}

Entity AstMap::add(const string &k, const Entity &v) {
  entity_ptr vptr  = make_shared<Entity>(v);
  if(vptr == nullptr) return entity_mem_error;
  return *add_ptr(k, vptr);
}

Entity AstMap::add(const vector<string> &keys, const Entity &v) {
  shared_ptr<AstMap> current = nullptr;
  shared_ptr<AstMap> vptr  = nullptr;
  for(auto k: keys) {
    if(current==nullptr)  {
      current = dynamic_pointer_cast<AstMap>(get_new_ptr(k));
      continue;
    }
    current = dynamic_pointer_cast<AstMap>(current->get_new_ptr(k));
  }
  current->children[keys.back()] = make_shared<Entity>(v);
}


entity_ptr AstMap::get_ptr(const string &k) {
  if (children.find(k) != children.end())  
    return children[k];
  return nullptr;
}
entity_ptr AstMap::get_new_ptr(const string &k) {
  if (children.find(k) != children.end())  
    return children[k];
  children[k] = make_shared<Entity>();
  return children[k];
}

Entity AstMap::get(const string &k) {
  entity_ptr vptr = get_ptr(k);
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
//-------------------------------------- 

//-------------------------------------- Ast Root
AstRoot::AstRoot() { 
  root = get_ptr("root"); 
  if(root==nullptr) {
    auto vptr = make_shared<Entity>(OperandType::map_t);
    root = add_ptr("root", vptr); 
  }
}
AstRoot::AstRoot(AstMap m) { 
  root = m.get_ptr("root");
}

Entity AstRoot::add(const vector<string> &keys, const Entity &v) {
  shared_ptr<AstMap> current_root  = dynamic_pointer_cast<AstMap>(root);
  for(auto k: keys) {
    auto vptr= make_shared<AstMap>();
    if(vptr == nullptr) return entity_mem_error;
    current_root->add_ptr(k, vptr);
    current_root = vptr;
  }
}
*/