#pragma once
//#include "lang.hh"
#include <string>
#include <memory>


using namespace  std;

class Node;
class Lisp {
public:
  enum class Op 
  { kernel, system, root
  , error, noop
  , list, deque, vector
  , add, sub, div, mul, mod
  , def, call, send, ret
  , loop, cond, print
  , module, defun
  };

  static bool initialized;
  static unique_ptr<Node> map_;
  static string _to_str(Lisp::Op op);
  static void init();
};