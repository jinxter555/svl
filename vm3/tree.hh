#include <iostream>
#include <map>
#include <any>
#include <vector>
#include <memory>


class TreeNode {
  friend class Tree;
private:
  std::map<std::string, std::shared_ptr<TreeNode>> children;
  std::any data;
public:

  TreeNode() {}
  TreeNode(std::any data) : data(data) {}

  void add_child(const std::string &key, std::shared_ptr<TreeNode> child);
  std::shared_ptr<TreeNode> get_child(const std::string& key) const;

  std::vector<std::string> get_child_keys() const;
  std::any get_data() const;
  void set_data(const std::any d);
};

class Tree {
private:
  std::shared_ptr<TreeNode> root;
public:
  Tree() : root(nullptr) {}
  Tree(std::any data) : root(std::make_shared<TreeNode>(data)) {}

  void add_node(std::vector<std::string> keys, const std::any data);

  std::shared_ptr<TreeNode> get_node(std::vector<std::string> keys) const;

  void set_node(std::vector<std::string> keys, const std::any data) const ;

};

