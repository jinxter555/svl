#include <iostream>
#include <map>
#include <any>
#include <vector>
#include <memory>

using namespace std;

class TreeNode {
  friend class Tree;
private:
  map<string, shared_ptr<TreeNode>> children;
  any data;
public:

  TreeNode() {}
  TreeNode(any data) : data(data) {}

  void add_child(const string &key, shared_ptr<TreeNode> child);
  shared_ptr<TreeNode> get_child(const string& key) const;

  vector<string> get_child_keys() const;
  any get_data() const;
  void set_data(const any d);
};

class Tree {
private:
  shared_ptr<TreeNode> root;
public:
  Tree() : root(nullptr) {}
  Tree(any data) : root(make_shared<TreeNode>(data)) {}

  void add_node(vector<string> keys, const any data);

  shared_ptr<TreeNode> get_node(vector<string> keys) const;

  void set_node(vector<string> keys, const any data) const ;

};

