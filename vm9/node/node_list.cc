#include "node.hh"

#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"
extern Node null_node;

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

  cout << "get_node value:  " << _to_str() << "\n";
  cout << "get_node type: " << _to_str(type_) << "\n";

  if(type_ != Type::Vector) return {false, null_node};

  cout << "get_node index value: " << _to_str() << "\n";
  auto &v = get<Vector>(value_);
  auto &rv = v[index];
  return {true, *rv};
}