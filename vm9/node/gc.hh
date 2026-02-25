#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include <memory>

class GCObject;

using namespace std;


class Visitor {
public:
  virtual void visit(GCObject* obj) = 0;
};

class GCObject {
public:
  int id;
  bool marked = false;
  GCObject(int id);
  virtual ~GCObject();
  virtual void accept(Visitor&v) = 0;
};

class Marker  : public Visitor {
public:
  void visit(GCObject* obj) override;

};

class GarbageCollector {
public:
  void register_object(unique_ptr<GCObject> obj);
  void add_root(int id);
  void collect();

private:
  unordered_map<int, unique_ptr<GCObject>> registry;
  vector<GCObject*> roots;
};