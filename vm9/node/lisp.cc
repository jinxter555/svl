#include "lisp.hh"
#include "node.hh"

bool Lisp::initialized=false;
unique_ptr<Node> Lisp::map_=nullptr;

string Lisp::_to_str(Lisp::Op op) {
  switch (op) {
    case Lisp::Op::kernel: return "kernel";
    case Lisp::Op::system: return "system";
    case Lisp::Op::root: return "root";
    case Lisp::Op::error: return "error";
    case Lisp::Op::noop: return "noop";
    case Lisp::Op::list: return "list";
    case Lisp::Op::deque: return "deque";
    case Lisp::Op::vector: return "vector";
    case Lisp::Op::add: return "add";
    case Lisp::Op::sub: return "sub";
    case Lisp::Op::mul: return "mul";
    case Lisp::Op::div: return "div";
    case Lisp::Op::mod: return "mod";
    case Lisp::Op::def: return "def";
    case Lisp::Op::call: return "call";
    case Lisp::Op::send: return "send";
    case Lisp::Op::ret: return "ret";
    case Lisp::Op::cond: return "cond";
    case Lisp::Op::print: return "print";
    case Lisp::Op::module: return "module";
    case Lisp::Op::defun: return "defun";
  }
  return "Unknown LispOp";
}
void Lisp::init() {
  if(initialized) return;
  map_ = make_unique<Node>(Node::Type::Map);
  map_->set("kernel", Op::kernel);
  map_->set("system", Op::system);
  map_->set("root",   Op::root);
  map_->set("error",Op::error);
  map_->set("noop", Op::noop);
  map_->set("list", Op::list);
  map_->set("vector", Op::vector);
  map_->set("deque", Op::deque);
  map_->set("add", Op::add);
  map_->set("sub", Op::sub); 
  map_->set("mul", Op::mul);
  map_->set("div", Op::div);
  map_->set("mod", Op::mod); 
  map_->set("def", Op::def); 
  map_->set("call", Op::call);
  map_->set("send", Op::send);
  map_->set("ret", Op::ret);
  map_->set("cond", Op::cond);
  map_->set("print",Op::print);
  map_->set("module",Op::module);
  map_->set("defun",Op::defun);

  map_->set("+", Op::add);
  map_->set("-", Op::sub);
  map_->set("*", Op::mul);
  map_->set("/", Op::div);
  map_->set("%", Op::mod);
  initialized=true;
}