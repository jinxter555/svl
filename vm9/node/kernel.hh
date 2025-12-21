#ifndef KERNEL_HH
#define KERNEL_HH

#pragma once
#include "node.hh"
#include "tree.hh"

#include <functional>
#define UNIVERSE "universe"
#define PID "pid"
#define CFS "control_flow_state"
#define FRAMES "frames"


class Kernel : public Tree {
protected:
  static const vector<string> path_to_processes; 
  std::hash<string> hasher;

  enum class ProcState { run, sleep, suspend, stop, wait };
  
public:
  Kernel();

  Node::OpStatusRef proc_create();
  string _to_str(ProcState state);

  virtual void bootstrap();
};

#endif