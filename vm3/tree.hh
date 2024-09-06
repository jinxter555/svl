#pragma once
#include <iostream>
#include <map>
#include <any>
#include <vector>
#include <memory>
#include "operand.hh"


class TreeNode {
  friend class Tree;
private:
  std::map<std::string, std::shared_ptr<TreeNode>> children;
  std::vector<std::shared_ptr<TreeNode>> members;
  std::shared_ptr<TreeNode> parent; // not yet implemented
  std::any data;
public:

  virtual ~TreeNode() {};
  TreeNode() {}
  TreeNode(std::any data) : data(data) {}

  void add_child(const std::string &key, std::shared_ptr<TreeNode> child);
  void add_child_data(const std::string &key, std::any data);
  void add_member(std::shared_ptr<TreeNode> m);

  std::shared_ptr<TreeNode> get_child(const std::string& key) const;

  std::map<std::string, std::shared_ptr<TreeNode>> get_children() const;
  //std::vector<std::shared_ptr<TreeNode>> get_members() const;

  std::shared_ptr<TreeNode> get_member(int index) const;
  std::any get_member_data(int index) const;
  int get_member_size() const;

  std::vector<std::string> get_child_keys() const;
  std::any get_data() const;
  std::any& get_data_r() ;
  std::any get_child_data(const std::string &key) const;
  void set_data(const std::any d);
  void set_child_data(const std::string& key, const std::any d);
  void print_data();
};

class Tree {
private:
  std::shared_ptr<TreeNode> root;
public:
  Tree() : root(nullptr) {}
  Tree(std::any data) : root(std::make_shared<TreeNode>(data)) {}

  void add_node(std::vector<std::string> keys, const std::any data);

  void add_tree_node(std::vector<std::string> keys, std::shared_ptr<TreeNode> tn);

  std::shared_ptr<TreeNode> get_node(std::vector<std::string> keys) const;
  std::vector<std::string> get_children(std::vector<std::string> keys) const;

  void set_node(std::vector<std::string> keys, const std::any data) const ;

};

