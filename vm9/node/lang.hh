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
  class Atom {
  public: 
    static  const Node::Integer fun;
    /*
    static  const Node::Integer module_, fun, def, class_, atom_get, atom_set, atom_index, atom_size, atom_ok, atom_error, atom_unknown,
    atom_lambda, atom_closure, atom_else,
    atom_atom, atom_integer, atom_float, atom_string, atom_cc_vec, atom_cc_list, atom_cc_deque, atom_cc_map, atom_cc_imap, atom_object, atom_namespace,
    atom_pid, atom_ppid;
*/
  };

  Lang();

  static Node::Integer str_to_atom(const string& input);
  static string unqiue_name(const string& input);
  //Node::OpStatusRef atom_to_str(Node::Integer v);
  static string atom_to_str(Node::Integer v);
  static string atom_to_str_imap(Node::Integer v);
  void bootstrap() override;
};
