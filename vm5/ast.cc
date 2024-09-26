#include "ast.hh"

//-------------------------------------- Ast List
AstList::AstList() { type_ = OperandType::list_t; }


const Entity& AstList::add(const Entity &v) { 
  cout << "add: v " << v << "\n";
  auto vptr = make_unique<Entity>(v); 
  //Entity v_new(v);
  //cout << "add: v_new" << v_new<< "\n";
  cout << "add: v_ptr: " << *vptr<< "\n";
  cout << "\n";
  return *add(vptr); 
}

const entity_u_ptr& AstList::add(entity_u_ptr &vptr) {
  members.push_back(move(vptr));
  return members.back();
}


const Entity& AstList::get(const Entity &key) {
  int i = key._get_int();
  if(i > members.size())
    return entity_undef_error;
  return *members[i];
}

/*
AstList&  AstList::get_list(const Entity &key) {
  int i = key._get_int();
  //if(i > members.size() || i<0 ) return Entity::entity_undef_error;
  entity_u_ptr &rptr =  members[i];
  int i = key._get_int();
  //return *members[i];
  //return *members[i];
}
*/

const Entity& AstList::set(const Entity &key, const Entity &v ) {
  entity_u_ptr vptr  = make_unique<Entity>(v);
  return set(key, vptr );
}

const Entity& AstList::set(const Entity &key, entity_u_ptr &vptr ) {
  int i = key._get_int();
  if(i > members.size() || i < 0) 
    return entity_undef_error;
  members[i] = move(vptr);
  return *members[i];
}


//Entity AstList::evaluate(Entity *ctxt) {return entity_undef_error; }

void AstList::print() {
  cout << *this;
}
//--------------------------------------
/*
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