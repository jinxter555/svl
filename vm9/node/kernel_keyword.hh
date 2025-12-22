#ifndef KERNEL_HH
#define KERNEL_HH

#pragma once
//#include "node.hh"
#include "tree.hh"

#include <functional>
#include <string>
#define UNIVERSE "universe"
#define PID "pid"
#define CFS "control_flow_state"
#define FRAMES "frames"


class KernelKW {
protected:
  static const vector<string> path_to_processes; 

  enum class ProcState { run, sleep, suspend, stop, wait };
  
public:
  //Kernel();

  Node::OpStatusRef proc_create();
  string _to_str(ProcState state);

  virtual void bootstrap();
};

#endif