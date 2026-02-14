#include "node.hh"
#include "lang.hh"
#include <iostream>

const vector<string> Lang::atoms_key = {UNIVERSE, "Lang", "Atoms"};

unordered_map<Node::Integer , string> Lang::Atoms;
std::hash<string> Lang::hasher;

Lang::Lang() : Kernel() {
  //Node::Map map;
  //set_branch(atoms_key, Node::create(move(map)));
}

//------------------------------------------------------------------------
Node::Integer Lang::str_to_atom(const string& input) {
  Node::Integer hash_value = hasher(input);
  Atoms[hash_value] = input;
  return hash_value;
}

string Lang::atom_to_str(Node::Integer v) {
  return Atoms[v];
}
string Lang::atom_to_str_imap(Node::Integer v) {
  if (auto it = Atoms.find(v); it != Atoms.end()) 
    return Atoms[v];
  return  to_string(v)+"i";
}

string Lang::unqiue_name(const string& input) {
  unsigned long hash_value = hasher(input);
  return input + to_string(hash_value);
}

void Lang::bootstrap() {}