#include "tree.hh"
using namespace std;

void TreeNode::add_child(const string &key, shared_ptr<TreeNode> child) {
  if(children[key] == nullptr)
    // children[key] = move(child);
    children[key] = child;
}

shared_ptr<TreeNode> TreeNode::get_child(const string &key) const {
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

vector<string> TreeNode::get_child_keys() const {
  vector<string> keys;
  for(auto const& [key, val] : children) {
    keys.push_back(key);
  }
  return keys;
}

any TreeNode::get_data() const {
  return data;
}
void TreeNode::set_data(const any d) {
  data = d;
}

//--------------------------------------------------------------


void Tree::add_node(vector<string> keys, const any data) {
  if(root == nullptr) {
    root = make_shared<TreeNode>();
  }

  auto curr = root;
  for(int i=0; i<keys.size() -1; i++) {
    if(curr->get_child(keys[i])==nullptr) {
      curr->add_child(keys[i], make_shared<TreeNode>());
    }
    curr = curr->get_child(keys[i]);
  }
  curr->add_child(keys.back(), make_shared<TreeNode>(data));
}

shared_ptr<TreeNode> Tree::get_node(vector<string> keys) const {
  auto curr = root;
  if(curr==nullptr) return nullptr;
  for(auto key : keys) {
    curr = curr->get_child(key);
    if(curr == nullptr) return nullptr;
  }
  return curr;
}


void Tree::set_node(vector<string> keys, const any data) const {
  auto curr = get_node(keys);
  curr->set_data(data);
}
