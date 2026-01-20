#include "lisp.hh"
#include "node.hh"


Lisp::Lisp(){}

string Lisp::_to_str(Lisp::Op op) {
  switch (op) {
    case Lisp::Op::kernel: return "kernel";
    case Lisp::Op::system: return "system";
    case Lisp::Op::root: return "root";
    case Lisp::Op::class_: return "class";
    case Lisp::Op::new_: return "new";
    case Lisp::Op::delete_: return "delete";
    case Lisp::Op::clone: return "clone";
    case Lisp::Op::error: return "error";
    case Lisp::Op::noop: return "noop";
    case Lisp::Op::identifier: return "identifier";
    case Lisp::Op::scalar: return "scalar";
    case Lisp::Op::literal: return "literal";
    case Lisp::Op::list: return "list";
    case Lisp::Op::deque: return "deque";
    case Lisp::Op::vector: return "vector";
    case Lisp::Op::map: return "map";
    case Lisp::Op::car: return "car";
    case Lisp::Op::cdr: return "cdr";
    case Lisp::Op::add: return "add";
    case Lisp::Op::sub: return "sub";
    case Lisp::Op::mul: return "mul";
    case Lisp::Op::div: return "div";
    case Lisp::Op::mod: return "mod";
    case Lisp::Op::var: return "var";
    case Lisp::Op::assign: return "assign";
    case Lisp::Op::def: return "def";
    case Lisp::Op::call: return "call";
    case Lisp::Op::funcall: return "funcall";
    case Lisp::Op::call_extern: return "call_extern";
    case Lisp::Op::send: return "send";
    case Lisp::Op::ret: return "ret";
    case Lisp::Op::cond: return "cond";
    case Lisp::Op::print: return "print";
    case Lisp::Op::module: return "module";
    case Lisp::Op::defun: return "defun";
    case Lisp::Op::defmacro: return "defmacro";
    case Lisp::Op::alias: return "alias";
    case Lisp::Op::lambda: return "lambda";
  }
  return "Unknown LispOp";
}