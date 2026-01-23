#ifndef LANG_HH
#define LANG_HH

#pragma once
#include <string>
#include <memory>


using namespace  std;

class Lisp {
public:
  enum class Op 
  { root, kernel, system
  , class_, private_, new_, delete_, clone
  , error, noop
  , identifier, scalar, literal, list, deque, vector, map, object
  , var, assign
  , car, cdr
  , add, sub, div, mul, mod
  , def, call, send, ret, call_extern, funcall
  , cond, print, loop, for_, do_, if_, case_, when
  , module, defun, defmacro, alias, lambda
  };
  using Type=Op;
  Lisp();
  static string _to_str(Lisp::Op op);
};

#endif
