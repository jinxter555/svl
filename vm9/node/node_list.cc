#include "node.hh"
vector<string> Node::list_to_vector_string(const List &list) {
  vector<string> result;
  for(auto& e : list ) {
    result.push_back(e->_to_str());
  }
  return result;

}