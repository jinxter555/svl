#ifndef LANG_HH
#define LANG_HH

#pragma once
#include <string>
#include <memory>


using namespace  std;

class Lisp {
public:
  enum class Op 
  { kernel, system, root, class_, new_, delete_, clone
  , error, noop
  , identifier, scalar, literal, list, deque, vector, map
  , var, assign
  , car, cdr
  , add, sub, div, mul, mod
  , def, call, send, ret, extern_
  , loop, cond, print
  , module, defun, defmacro, alias, lambda
  };
  Lisp();
  static string _to_str(Lisp::Op op);
};

#endif
