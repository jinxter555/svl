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
void Marker::visit(GCObject &obj) {
  if(!obj.marked) {
    cout << "marking object: " << obj._to_str() << "\n";
    obj.marked = true;
    obj.accept(*this);
  }
}

void Node::accept(Visitor&v) {
  for(GCObject& neighbor : edges) {
    v.visit(neighbor);
  }

  if(is_container()) { cout << "container type: " << _to_str(type_) << ",  object: " << _to_str() << "\n"; }
  switch(type_) {
  case Type::Vector: {
    for(auto &ele : _get_vector_ref() ) {
      cout << "ele: " << *ele << "\n";
    }
  }
  case Type::Map: {
    for(auto &ele : _get_map_ref() ) {
      cout << "ele-key : " << ele.first << ", ele-value: " << ele.second->_to_str() << "\n";
    }
  }
  default: {}}

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

  for(GCObject& root : roots) {
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
    cout << "obj.id: " << obj.first << " marked: " << obj.second->marked  <<  " , " << obj.second->_to_str() << "\n";
  }
}