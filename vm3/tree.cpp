#include "tree.hh"
#include "vm_type.hh"
#include "lang.hh"

void TreeNode::add_child(const std::string &key, std::shared_ptr<TreeNode> child) {
  if(children[key] == nullptr)
    // children[key] = move(child);
    children[key] = child;
}

void TreeNode::add_member(std::shared_ptr<TreeNode> member) {
  members.push_back(member);
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

std::shared_ptr<TreeNode> TreeNode::get_member(int index) const {
  return members[index];
}
int TreeNode::get_member_size() const {
  return members.size();
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

std::ostream& operator << (std::ostream& out, std::any& a) {
  if(a.type()  == typeid(char))
    out << std::any_cast<char>(a);
  else if(a.type()  == typeid(int))
    out << std::any_cast<int>(a);
  else if(a.type()  == typeid(double))
    out << std::any_cast<double>(a);
  else if(a.type()  == typeid(float))
    out << std::any_cast<float>(a);
  else if(a.type()  == typeid(long int))
    out << std::any_cast<long int>(a);
  else if(a.type()  == typeid(unsigned long int))
    out << std::any_cast<unsigned long int>(a);
  else if(a.type()  == typeid(long long))
    out << std::any_cast<long long>(a);
  else if(a.type()  == typeid(long double))
    out << std::any_cast<long double>(a);
  else if(a.type()  == typeid(std::string))
    out << std::any_cast<std::string>(a);
  else if(a.type()  == typeid(op_t)) {
    op_t ao = std::any_cast<op_t>(a);
    out << ao.op;
  }
  else
    out << "unknown value type!";
  return out;
}

void TreeNode::print_data() {
  std::cout << data;
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

void Tree::add_tree_node(std::vector<std::string> keys, std::shared_ptr<TreeNode> tn) {
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
  curr->add_child(keys.back(), tn);
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

std::vector<std::string> Tree::get_children(std::vector<std::string> keys) const {
  auto cnode = get_node(keys);
  if(cnode)
    return cnode->get_child_keys();
  else 
    return {};
}


void Tree::set_node(std::vector<std::string> keys, const std::any data) const {
  auto curr = get_node(keys);
  curr->set_data(data);
}
