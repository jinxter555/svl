#include <iostream>
#include <map>
#include <any>
#include <vector>
#include <memory>

#include "tree.hh"

using namespace std;


void TreeNode::add_child(string key, shared_ptr<TreeNode> child) {
    if(children[key] == nullptr)
      children[key] = move(child);
}

shared_ptr<TreeNode> TreeNode::get_child(string key) const {
    if(children.find(key) == children.end()) {
      return nullptr;
    }
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

void TreeNode::set_data(any d) {
    data = d;
}


  void Tree::add_node(vector<string> keys, any data) {
    if(root == nullptr) {
      root = make_shared<TreeNode>();
    }
    auto curr = root;
    for(int i=0; i<keys.size() - 1; i++) {
      if(curr->get_child(keys[i])==nullptr) {
        curr->add_child(keys[i], make_shared<TreeNode>());
      }
      curr = curr->get_child(keys[i]);
    }
    curr->add_child(keys.back(), make_shared<TreeNode>(data));
  }

  shared_ptr<TreeNode> Tree::get_node(vector<string> keys) const {
    auto curr = root;
    for(auto key : keys) {
      curr = curr->get_child(key);
      if(curr == nullptr) return nullptr;
    }
    return curr;
  }

  void Tree::set_node(vector<string> keys, any data) const {
    auto curr = get_node(keys);
    curr->set_data(data);
  }


#ifdef __MAIN__
#undef __MAIN__
int main() {
  auto my_tree = new Tree();
  my_tree->add_node({"key1"}, string("workjob"));
  my_tree->add_node({"key1", "key2"}, 1);
  my_tree->add_node({"key1", "key3"}, string("hello"));
  my_tree->add_node({"key4", "key5"}, 3.145);

  auto node1a = my_tree->get_node({"key1", "key2"});
  cout << "v at key1/key2: " << any_cast<int>(node1a->get_data()) << endl;
  my_tree->set_node({"key1", "key2"}, 2.1);
  auto node1b = my_tree->get_node({"key1", "key2"});
  auto node1c = my_tree->get_node({"key1", "key2"});
  cout << "v at key1/key2: " << any_cast<double>(node1b->get_data()) << endl;
  cout << "v at key1/key2: " << any_cast<double>(node1a->get_data()) << endl;
  cout << "&v " << node1a << "\n";
  cout << "&v " << node1b << "\n";
  cout << "&v " << node1c << "\n";
  cout << "\n";

  node1a = my_tree->get_node({"key1"});
  cout << "v at key1: " << 
    any_cast<string>(node1a->get_data()) << endl;

  auto node2 = my_tree->get_node({"key1", "key3"});
  cout << "v at key1/key3: " << any_cast<string>(node2->get_data()) << endl;

  auto node3 = my_tree->get_node({"key4", "key5"});
  cout << "v at key4/key5: " << any_cast<double>(node3->get_data()) << endl;
  cout << "\n";
}

#endif
