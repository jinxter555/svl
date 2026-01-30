#include "node.hh"

#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"

vector<string> Node::list_to_vector_string(const List &list) {
  vector<string> result;
  for(auto& e : list ) {
    result.push_back(e->_to_str());
  }
  return result;

}

// 
Node::OpStatusRef Node::get_node(size_t index) {
  MYLOGGER(trace_function, "Node::get_node(size_t& index)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("index: ") + to_string(index), SLOG_FUNC_INFO+30);

  //cout << "get_node value:  " << _to_str() << "\n";
  //cout << "get_node type: " << _to_str(type_) << "\n";

  if(type_ != Type::Vector) return {false, null_node};

  //cout << "get_node index value: " << _to_str() << "\n";
  auto &v = get<Vector>(value_);
  auto &rv = v[index];
  //return {true, *rv};
  return {true, *v[index]};
}

//------------------------------------------------------------------------
Node::OpStatusRef Node::get_node_with_ptr(size_t index) {
  MYLOGGER(trace_function, "Node::get_node_with_ptr(string& key)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, "index: " + to_string(index), SLOG_FUNC_INFO+30);

  switch(type_) {
  case Type::Shared: {
    auto sptr = get<ptr_S>(value_);
    return sptr->get_node(index); }
  case Type::Raw: {
    auto sptr = get<ptr_R>(value_);
    return sptr->get_node(index); }
  case Type::Unique:  {
    auto &sptr = get<ptr_U>(value_);
    return sptr->get_node(index); }
  default: {}
  }
  return get_node(index);

}