#pragma once
#include "tree.hh"

#include <functional>
class Lang : public Tree {
protected:
  static const vector<string> atoms_key ; 
  std::hash<string> hasher;
public:
  Lang();

  Node::Integer str_to_atom(const string& input);
  Node::OpStatus atom_to_str(Node::Integer v);
  virtual void bootstrap()=0;
};
