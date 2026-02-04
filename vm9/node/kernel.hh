#ifndef KERNEL_HH
#define KERNEL_HH

#pragma once
//#include "node.hh"
#include "defs.hh"
#include "tree.hh"

#include <functional>
#include <string>


class Kernel : public Tree {
protected:
  static const vector<string> path_to_processes; 

  
public:
  Kernel();

  Node::OpStatusRef process_create();
  Node::OpStatusRef process_get(Node::Integer pid);
  //string _to_str(ProcState state);
  static Node::Integer pid(Node&process);
  virtual void bootstrap();
};

#endif