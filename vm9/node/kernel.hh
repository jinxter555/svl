#pragma once
#include "tree.hh"

#include <functional>
#define UNIVERSE "universe"
#define PID "pid"
#define CFS "control_flow_state"
#define FRAMES "frames"

class Kernel : public Tree {
protected:
  static const vector<string> path_to_atoms; 
  static const vector<string> path_to_processes; 
  std::hash<string> hasher;

  enum class ProcState { run, sleep, suspend, stop, wait };
  
public:
  Kernel();
  void bootstrap();
  Node::OpStatusRef proc_create();

  Node::Integer str_to_atom(const string& input);
  Node::OpStatus atom_to_str(Node::Integer v);
  virtual void bootstrap()=0;
};
