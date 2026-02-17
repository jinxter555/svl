#ifndef LANG_HH
#define LANG_HH

#pragma once
#include <string>
#include <memory>
#include <unordered_map>


using namespace  std;

class Node;
using Map = unordered_map<string, unique_ptr<Node>>;



class Lisp {
public:
  enum class Op 
  { root, nil, kernel, system, branch, namespace_
  , class_, private_, new_, delete_, clone
  , error, noop
  , identifier, scalar, literal, quote, unquote, list, deque, vector, hash, ihash, object
  , var, assign
  , car, cdr, map
  , add, sub, div, mul, mod, lt, gt, lteq, gteq, eq, neq, and_, or_, not_
  , read, readline
  , call, send, ret, call_extern, funcall, curry, pipe
  , cond, print, printr, loop, eval, while_, return_, exit_, continue_, break_, repeat, for_, do_, if_, iif, case_, match, when
  , module, def, defun, defmacro, alias, lambda, faz
  };
  using Type=Op;
  Lisp();
  static string _to_str(Lisp::Op op);
  static Type type(const Node& node);
  static Type type(const Map& m);
};

#endif
