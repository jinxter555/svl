#pragma once
#include "kernel.hh"

#include <functional>
#define UNIVERSE "universe"
class Lang : public Kernel {
protected:
  static const vector<string> atoms_key ; 
  static std::hash<string> hasher;
  static unordered_map<Node::Integer , string> Atoms;
public:
  Lang();

  static Node::Integer str_to_atom(const string& input);
  static string unqiue_name(const string& input);
  //Node::OpStatusRef atom_to_str(Node::Integer v);
  static string atom_to_str(Node::Integer v);
  static string atom_to_str_imap(Node::Integer v);
  void bootstrap() override;
};
