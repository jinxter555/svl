#include "node.hh"
#include "lang.hh"
#include <iostream>

const vector<string> Lang::atoms_key = {UNIVERSE, "Lang", "Atoms"};

unordered_map<Node::Integer , string> Lang::Atoms;

Lang::Lang() : Kernel() {
  //Node::Map map;
  //set_branch(atoms_key, Node::create(move(map)));
}

//------------------------------------------------------------------------
Node::Integer Lang::str_to_atom(const string& input) {
  Node::Integer hash_value = hasher(input);
  //auto atoms = get_branch(atoms_key);

  //if(atoms==nullptr) throw std::runtime_error("Lang: atoms map is nullptr\n");
  
  //cout << "hash is " <<  hash_value << "  \n";
  //cout << "atoms map \n";
  //cout << "atoms map \n"<< *atoms << "\n";
  //atoms->set(to_string(hash_value), input);
  Atoms[hash_value] = input;

  //atoms->print(); cout << *atoms << "\n\n";

  return hash_value;
}
//Node::OpStatusRef Lang::atom_to_str(Node::Integer v) {
string Lang::atom_to_str(Node::Integer v) {
  //auto atoms = get_branch(atoms_key);
  return Atoms[v];
  // return (*atoms)[to_string(v)];
}


void Lang::bootstrap() {}