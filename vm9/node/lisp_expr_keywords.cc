#include "lisp_expr.hh"

#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"

//------------------------------------------------------------------------ Lisp Expr Keywords
void LispExpr::set_keywords() {
  auto map_ = make_unique<Node>(Node::Type::Map);
  map_->set("kernel", Op::kernel);
  map_->set("system", Op::system);
  map_->set("root",   Op::root);
  map_->set("new",   Op::new_);
  map_->set("delete",   Op::delete_);
  map_->set("class",   Op::class_);
  map_->set("private",   Op::private_);
  map_->set("new",   Op::new_);
  map_->set("clone",   Op::clone);
  map_->set("error",Op::error);
  map_->set("noop", Op::noop);
  map_->set("identifier", Op::identifier);
  map_->set("scalar", Op::scalar);
  map_->set("literal", Op::literal);
  map_->set("list", Op::list);
  map_->set("vector", Op::vector);
  map_->set("deque", Op::deque);
  map_->set("map", Op::map);
  map_->set("var", Op::var);
  map_->set("assign", Op::assign);
  map_->set("car", Op::car);
  map_->set("cdr", Op::cdr);
  map_->set("add", Op::add);
  map_->set("sub", Op::sub); 
  map_->set("mul", Op::mul);
  map_->set("div", Op::div);
  map_->set("mod", Op::mod); 
  map_->set("def", Op::def); 
  map_->set("call", Op::call);
  map_->set("funcall", Op::funcall);
  map_->set("curry", Op::curry);
  map_->set("pipe", Op::pipe);
  map_->set("eval", Op::eval);
  map_->set("call_extern", Op::call_extern);
  map_->set("send", Op::send);
  map_->set("ret", Op::ret);
  map_->set("cond", Op::cond);
  map_->set("loop", Op::loop);
  map_->set("while", Op::while_);
  map_->set("repeat", Op::repeat);
  map_->set("for", Op::for_);
  map_->set("do", Op::do_);
  map_->set("print",Op::print);
  map_->set("module",Op::module);
  map_->set("defun", Op::defun);
  map_->set("defmacro", Op::defmacro);
  map_->set("alias", Op::alias);
  map_->set("lambda", Op::lambda);
  map_->set("read", Op::read);
  map_->set("readline", Op::readline);

  map_->set("+", Op::add);
  map_->set("-", Op::sub);
  map_->set("*", Op::mul);
  map_->set("/", Op::div);
  map_->set("%", Op::mod);

  map_->set("<", Op::lt);
  map_->set(">", Op::gt);
  map_->set("<=", Op::lteq);
  map_->set(">=", Op::gteq);
  map_->set("==", Op::eq);
  map_->set("=", Op::assign);

  set_branch(lisp_path_keyword, move(map_));
}

Lisp::Op LispExpr::keyword_to_op(const string &input) {
  MYLOGGER(trace_function, "LispExpr::keyword_to_op()", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("lookup input: ") + input, SLOG_FUNC_INFO+30);

  auto map_ = get_branch(lisp_path_keyword);
  //auto &map_ = Lisp::map_;

  if(map_ == nullptr || map_->type_ != Node::Type::Map) {
    cout << "lisp keyworld map_ type != map\n";
    return Lisp::Op::error;
  }
  auto status = (*map_)[input];
  if(!status.first) {
    MYLOGGER_MSG(trace_function, "Lisp keyword: " + input + " not found , return as scalar", SLOG_FUNC_INFO+30);
    return Lisp::Op::scalar;
  }
  auto op = get<Lisp::Op>(status.second.value_);
  return op;
}