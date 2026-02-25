#include "gc.hh"

GCObject::GCObject(int id) : id(id) {}

GCObject::~GCObject() {
    cout << "delete object id " << id << "\n";
}



void Marker::visit(GCObject *obj) {
  if(obj && !obj->marked) {
    obj->marked = true;
    obj->accept(*this); // find all reachables
  }
}

void GarbageCollector::register_object(unique_ptr<GCObject> obj) {
  int id = obj->id;
  registry[id] = move(obj);
}

void GarbageCollector::add_root(int id) {
  if(registry.find(id) != registry.end()) {
    roots.push_back(registry[id].get());
  }
}

void GarbageCollector::collect() {
  cout << "start collection!\n";

  // phase 1 : mark
  Marker marker;
  for(GCObject* root : roots) {
    marker.visit(root);
  }

  // phase 2: sweep
  auto it = registry.begin();
  while( it != registry.end() ) {
    if(!it->second->marked) {
      it = registry.erase(it);
    } else {
      it->second->marked= false;
      ++it;
    }
  }
  cout << "collection finished!\n";

}

