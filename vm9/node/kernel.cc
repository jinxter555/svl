#include "kernel.hh"
#include <iostream>

#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"

const vector<string> Kernel::path_to_atoms= {UNIVERSE, "Lang", "Atoms"};
const vector<string> Kernel::path_to_processes = {UNIVERSE, "Process"};

extern Node null_node;

Kernel::Kernel() : Tree() {
  Node::Map map;
  set_branch(path_to_atoms, Node::create(move(map)));
}

void Kernel::bootstrap() {
  string boot_str = "(root set_branch (list Lang Lisp))";
  // create environemtn
  // create kernel
  // create some pre modules and functions
}

//------------------------------------------------------------------------
Node::Integer Kernel::str_to_atom(const string& input) {
  Node::Integer hash_value = hasher(input);
  auto atoms = get_branch(path_to_atoms);

  if(atoms==nullptr) throw std::runtime_error("Lang: atoms map is nullptr\n");
  
  atoms->set(to_string(hash_value), input);
  return hash_value;
}
Node::OpStatus Kernel::atom_to_str(Node::Integer v) {
  auto atoms = get_branch(path_to_atoms);
  return (*atoms)[to_string(v)];
}

Node::OpStatusRef Kernel::proc_create() {
  MYLOGGER(trace_function, "LispExpr::proc_create()", __func__, SLOG_FUNC_INFO);
  //MYLOGGER_MSG(trace_function, string("pid: ") + to_string(pid), SLOG_FUNC_INFO+30);

  auto proc_node = get_branch(path_to_processes);
  cout << "proc type: " << Node::_to_str(proc_node->type_) << "\n";

  if(proc_node->type_ != Node::Type::Vector)
    return {false, *Node::create_error(Node::Error::Type::System,
      "lisp_process not a vector: " + _to_str_ext(path_to_processes)) };
  
  auto pid = proc_node->size_container();
  Node::Map map={}; 

  map[PID] = Node::create(pid);
  map[CFS]= Node::create(pid);
  map[FRAMES] = Node::create(Node::Map());

  proc_node->push_back( Node::create(move(map))  );


  return proc_node->get_node(pid);

}
