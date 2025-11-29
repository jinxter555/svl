#include "node.hh"
#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"

Node::OpStatus Node::merge(unique_ptr<Node> n, bool override) {
  switch(n->type_) {
    case Type::Map: {
      auto &map = get<Map>(n->value_);
      return merge(map, override);
    }
    case Type::List: {
    }
  }
  return {false, Node::create(false)};
}

Node::OpStatus Node::merge(Map &mv, bool override){
  MYLOGGER(trace_function, "Node::merge(Map mv, bool)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("with mapv: ") + Node::_to_str(mv), SLOG_FUNC_INFO+30);

  if(type_ != Node::Type::Map) {
    return {false, create_error(Node::Error::Type::InvalidOperation, 
      "Node::Merge(), Can't for non map type: " + _to_str(type_) )};
  }
  auto &map = get<Map>(value_);
  for(auto &p : mv) {
    if(m_has_key(p.first) && !override) return {false, Node::create(false)}; 
    map[p.first] = move(p.second);
  }
  return {true, Node::create(true)}; // success
}

Node::OpStatus Node::has_key(const string&key) {
  if(type_ != Node::Type::Map) {
    return {false, create_error(Node::Error::Type::InvalidOperation, 
      "Can't lookup key '" + key + "' for non map type: type: " + _to_str(type_) )};
  }
  auto &map = get<Map>(value_);
  if (map.find(key) != map.end())  return {true, Node::create(true)};
  return {true, Node::create(false)};
}

bool Node::m_has_key(const string&key) {
  auto &map = get<Map>(value_);
  if (map.find(key) != map.end())  return true;
  return false;
}





bool Node::extend(const vector<string>&path, bool override) {
  MYLOGGER(trace_function, "Node::extend(vector& path)", __func__, SLOG_FUNC_INFO);

  Node* node_ptr=this;
  for(auto p : path) {
    cout << "p: " << p << "\n";
    auto &map = get<Map>(node_ptr->value_);
    node_ptr = extend_node_by_key(map, p, override);
    if(node_ptr==nullptr) return false;
  }

  return true;

}


// private has to be call from Map handling functions
// get and extend node by key
Node* Node::extend_node_by_key(Map& map,  const string&key, bool create) { 
  MYLOGGER(trace_function, "Node::get_node_by_key(string& key)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("key: ") + key, SLOG_FUNC_INFO+30);

  if (map.find(key) != map.end()) return map[key].get(); // key found
  if(!create) return nullptr; // don't create
  Map new_map={};
  map[key] = Node::create(move(new_map));
  return map[key].get();
}