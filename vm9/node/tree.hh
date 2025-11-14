#pragma once
#include "node.hh"

class Tree {
protected:
  unique_ptr<Node> root;
public:
  Tree();
  Tree(unique_ptr<Node> root_node);
  const Node* get_root() const ;
  Node::OpStatus set_branch(const vector<string>&path, unique_ptr<Node>child);
  Node::OpStatus delete_branch(const vector<string>&path);
  Node* get_branch(const vector<string>&path) const ;


};
