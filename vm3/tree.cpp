#include "tree.hh"

void TreeNode::add_child(const std::string &key, std::shared_ptr<TreeNode> child) {
  if(children[key] == nullptr)
    // children[key] = move(child);
    children[key] = child;
}

std::shared_ptr<TreeNode> TreeNode::get_child(const std::string &key) const {
 // cout << "in get child\n";
  // return nullptr;
  //cout << "in get child after check empty\n";

  if(children.find(key) == children.end()) {
    //cout << "in get child if \n";
    return nullptr;
  }
    //cout << "out get child \n";
  return children.at(key);
}

std::vector<std::string> TreeNode::get_child_keys() const {
  std::vector<std::string> keys;
  for(auto const& [key, val] : children) {
    keys.push_back(key);
  }
  return keys;
}

std::any TreeNode::get_data() const {
  return data;
}
void TreeNode::set_data(const std::any d) {
  data = d;
}

//--------------------------------------------------------------


void Tree::add_node(std::vector<std::string> keys, const std::any data) {
  if(root == nullptr) {
    root = std::make_shared<TreeNode>();
  }

  auto curr = root;
  for(int i=0; i<keys.size() -1; i++) {
    if(curr->get_child(keys[i])==nullptr) {
      curr->add_child(keys[i], std::make_shared<TreeNode>());
    }
    curr = curr->get_child(keys[i]);
  }
  curr->add_child(keys.back(), std::make_shared<TreeNode>(data));
}

std::shared_ptr<TreeNode> Tree::get_node(std::vector<std::string> keys) const {
  auto curr = root;
  if(curr==nullptr) return nullptr;
  for(auto key : keys) {
    curr = curr->get_child(key);
    if(curr == nullptr) return nullptr;
  }
  return curr;
}


void Tree::set_node(std::vector<std::string> keys, const std::any data) const {
  auto curr = get_node(keys);
  curr->set_data(data);
}
