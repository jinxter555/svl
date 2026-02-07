#include "lisp.hh"
#include "node.hh"
#include "defs.hh"
#include <iostream>


Lisp::Lisp(){}

string Lisp::_to_str(Lisp::Op op) {
  switch (op) {
    case Lisp::Op::root: return "root";
    case Lisp::Op::nil: return "nil";
    case Lisp::Op::kernel: return "kernel";
    case Lisp::Op::system: return "system";
    case Lisp::Op::class_: return "class";
    case Lisp::Op::private_: return "private";
    case Lisp::Op::new_: return "new";
    case Lisp::Op::delete_: return "delete";
    case Lisp::Op::clone: return "clone";
    case Lisp::Op::error: return "error";
    case Lisp::Op::noop: return "noop";
    case Lisp::Op::identifier: return "identifier";
    case Lisp::Op::scalar: return "scalar";
    case Lisp::Op::literal: return "literal";
    case Lisp::Op::quote: return "quote";
    case Lisp::Op::unquote: return "unquote";
    case Lisp::Op::list: return "list";
    case Lisp::Op::deque: return "deque";
    case Lisp::Op::vector: return "vector";
    case Lisp::Op::map: return "map";
    case Lisp::Op::object: return "object";
    case Lisp::Op::car: return "car";
    case Lisp::Op::cdr: return "cdr";

    case Lisp::Op::add: return "add";
    case Lisp::Op::sub: return "sub";
    case Lisp::Op::mul: return "mul";
    case Lisp::Op::div: return "div";
    case Lisp::Op::mod: return "mod";

    case Lisp::Op::eq: return "eq";
    case Lisp::Op::lt: return "lt";
    case Lisp::Op::gt: return "gt";
    case Lisp::Op::gteq: return "gteq";
    case Lisp::Op::lteq: return "lteq";
    case Lisp::Op::and_: return "and";
    case Lisp::Op::or_: return "or";
    case Lisp::Op::not_: return "not";

    case Lisp::Op::var: return "var";
    case Lisp::Op::assign: return "assign";
    case Lisp::Op::def: return "def";
    case Lisp::Op::call: return "call";
    case Lisp::Op::funcall: return "funcall";
    case Lisp::Op::curry: return "curry";
    case Lisp::Op::pipe: return "pipe";
    case Lisp::Op::eval: return "eval";
    case Lisp::Op::call_extern: return "call_extern";
    case Lisp::Op::send: return "send";
    case Lisp::Op::ret: return "ret";
    case Lisp::Op::cond: return "cond";
    case Lisp::Op::loop: return "loop";
    case Lisp::Op::while_: return "while";
    case Lisp::Op::repeat: return "repeat";
    case Lisp::Op::for_: return "for";
    case Lisp::Op::do_: return "do";
    case Lisp::Op::if_: return "if";
    case Lisp::Op::case_: return "case";
    case Lisp::Op::when: return "when";
    case Lisp::Op::print: return "print";
    case Lisp::Op::module: return "module";
    case Lisp::Op::defun: return "defun";
    case Lisp::Op::defmacro: return "defmacro";
    case Lisp::Op::alias: return "alias";
    case Lisp::Op::lambda: return "lambda";
    case Lisp::Op::read: return "read";
    case Lisp::Op::readline: return "readline";
    default: {}
  }
  return "Unknown LispOp";
}


Lisp::Type Lisp::type(const Node& node) {
  try {
   auto &m= get<Node::Map>(node.value_);
   return type(m);
  } catch(...){
    return Lisp::Type::nil;
  }

}
Lisp::Type Lisp::type(const Node::Map& map_) {
  try {
    auto &obj_info = map_.at(OBJ_INFO);
    auto type_ref_status = obj_info->get_node(TYPE);
    if(!type_ref_status.first) return Lisp::Type::nil;
    auto t = get<Lisp::Type>(type_ref_status.second.value_);
    return t;
  } catch(...) {
    return Lisp::Type::nil;
  }
}