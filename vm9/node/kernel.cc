#include "kernel.hh"
#include "tree.hh"
#include "my_helpers.hh"
#include <iostream>

#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"

//const vector<string> Kernel::path_to_atoms= {UNIVERSE, "Lang", "Atoms"};
const vector<string> Kernel::path_to_processes = {UNIVERSE, "Process"};

extern Node null_node;

Kernel::Kernel() : Tree() {
  bootstrap();
}

void Kernel::bootstrap() {
  Node::Vector vector_proc;
  vector_proc.reserve(10);
  set_branch(path_to_processes, Node::create(move(vector_proc)));
}

Node::Integer Kernel::pid(Node&process) {
  auto pid_status = process[PID];
  if(!pid_status.first) return -1;
  if(pid_status.second.type_!=Node::Type::Integer) return -1;
  return get<Node::Integer>(pid_status.second.value_);
}

//------------------------------------------------------------------------
Node::OpStatusRef Kernel::process_create() {
  MYLOGGER(trace_function, "LispExpr::proc_create()", __func__, SLOG_FUNC_INFO);
  //MYLOGGER_MSG(trace_function, string("pid: ") + to_string(pid), SLOG_FUNC_INFO+30);

  auto proc_vector_node = get_branch(path_to_processes);
  //cout << "proc type: " << Node::_to_str(proc_node->type_) << "\n";

  if(proc_vector_node->type_ != Node::Type::Vector)
    return {false, *Node::create_error(Error::Type::System,
      "lisp_process not a vector: " + _to_str_ext(path_to_processes)) };
  
  auto pid = proc_vector_node->size_container();
  Node::Map map={}; 
  Node::Vector frames;
  frames.reserve(20);

  map[PID] = Node::create(pid);
  //map[CFS]= Node::create(pid);
  map[FRAMES] = Node::create(move(frames));
  map[STATE] = Node::create(Node::ProcState::init);

  proc_vector_node->push_back( Node::create(move(map))  );


  return proc_vector_node->get_node(pid);

}

Node::OpStatusRef Kernel::process_get(Node::Integer pid) {
  auto proc_vector_node = get_branch(path_to_processes);
  //cout << "proc type: " << Node::_to_str(proc_node->type_) << "\n";

  if(proc_vector_node->type_ != Node::Type::Vector)
    return {false, *Node::create_error(Error::Type::System,
      "lisp_process not a vector: " + _to_str_ext(path_to_processes)) };
  return proc_vector_node->get_node(pid);
}