#pragma once
#include "kernel.hh"

#include <functional>
#define UNIVERSE "universe"
class Lang : public Kernel {
protected:
  static const vector<string> atoms_key ; 
  std::hash<string> hasher;
public:
  Lang();

  Node::Integer str_to_atom(const string& input);
  //Node::OpStatusRef atom_to_str(Node::Integer v);
  static string atom_to_str(Node::Integer v);
  void bootstrap() override;
};
