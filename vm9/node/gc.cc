#include "node.hh"
#include <iostream>

#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"


//------------------------------------------------------------------------ Garbage Collection
/*
GCObject::GCObject() {};
GCObject::~GCObject() {
  //cout << "deleting object id: " << id << "\n";
}*/
//------------------------------------------------------------------------
void Marker::visit(GCObject *obj) {
  if(obj && !obj->marked) {
    obj->marked = true;
    obj->accept(*this);
  }
}

void Node::accept(Visitor&v) {
  for(GCObject* neighbor : edges) {
    v.visit(neighbor);
  }


}

//Node::Integer ObjectStore::register_object(unique_ptr<GCObject> obj) {
Node::Integer ObjectStore::register_object(shared_ptr<GCObject> obj) {
  MYLOGGER(trace_function, "ObjectStore::register_object(shared_ptr<GCObject>obj)", __func__, SLOG_FUNC_INFO);

  obj->id  = current_id;
  registry[current_id] = obj;
  current_id++;
  return obj->id;
}



void ObjectStore::collect() {
  Marker marker;

  for(GCObject* root : roots) {
    marker.visit(root);
  }

  auto it = registry.begin();
  while(it != registry.end()) {
    if(!it->second->marked) {
      it = registry.erase(it);
    } else {
      it->second->marked = false;
      ++it;
    }
  }
}
void ObjectStore::print() {
  for(auto &obj : registry ) {
    cout << "obj.id: " << obj.first << ", " << obj.second->_to_str() << "\n";
  }
}