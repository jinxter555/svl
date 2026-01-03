#ifndef LANG_HH
#define LANG_HH

#pragma once
#include <string>
#include <memory>


using namespace  std;

class Node;
class Lisp {
public:
  enum class Op 
  { kernel, system, root
  , not_found, error, noop
  , identifier, scalar, list, deque, vector
  , var, assign
  , add, sub, div, mul, mod
  , def, call, send, ret
  , loop, cond, print
  , module, defun
  };
  Lisp();
  static string _to_str(Lisp::Op op);
};

#endif
