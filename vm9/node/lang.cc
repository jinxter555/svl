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


const Node::Integer Lang::Atom::fun=str_to_atom("fun");
const Node::Integer Lang::Atom::server=str_to_atom("server");
const Node::Integer Lang::Atom::accept=str_to_atom("accept");
const Node::Integer Lang::Atom::connect=str_to_atom("connect");
const Node::Integer Lang::Atom::client=str_to_atom("client");
const Node::Integer Lang::Atom::run=str_to_atom("run");
const Node::Integer Lang::Atom::ok=str_to_atom("ok");
const Node::Integer Lang::Atom::error=str_to_atom("error");
const Node::Integer Lang::Atom::read=str_to_atom("read");
const Node::Integer Lang::Atom::write=str_to_atom("write");
const Node::Integer Lang::Atom::read_text=str_to_atom("read_text");
const Node::Integer Lang::Atom::write_text=str_to_atom("write_text");
const Node::Integer Lang::Atom::read_binary=str_to_atom("read_binary");
const Node::Integer Lang::Atom::write_binary=str_to_atom("write_binary");
const Node::Integer Lang::Atom::is_open=str_to_atom("is_open");
const Node::Integer Lang::Atom::got_text=str_to_atom("got_text");
const Node::Integer Lang::Atom::echo=str_to_atom("echo");
const Node::Integer Lang::Atom::initialize=str_to_atom("initialize");
const Node::Integer Lang::Atom::finalize=str_to_atom("finalize");
const Node::Integer Lang::Atom::extract=str_to_atom("extract");
const Node::Integer Lang::Atom::match=str_to_atom("match");
const Node::Integer Lang::Atom::icase=str_to_atom("icase");
const Node::Integer Lang::Atom::part=str_to_atom("part");
const Node::Integer Lang::Atom::full=str_to_atom("full");