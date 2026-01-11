#include <iostream>
#include "lisp_expr.hh"

#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"



Node::OpStatus LispExpr::car(Node&process, const Node::Vector &list, int start) {
  MYLOGGER(trace_function, "LispExpr::car(Node&process, Node::Vector&list)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("list: ") + Node::_to_str(list), SLOG_FUNC_INFO+30);

  //if(list.empty()) return {false, Node::create_error(Error::Type::EmptyContainer, "Empty List front()!")};
  if(list.empty()) return {true, Node::create()}; // return null
  auto &head = list[start];
  switch(head->type_) {
  case Node::Type::Identifier: {
    auto name = get<string>(head->value_);

    auto rv_ref_status = symbol_lookup(process, name  );
    if(!rv_ref_status.first) {
      cerr << "Lisp::car error symbol '"  <<   name << "' lookup " << rv_ref_status.second << "\n";
      return {false, rv_ref_status.second.clone()};
    }
    if(rv_ref_status.second.type_==Node::Type::Vector){
      auto &rlist = get<Node::Vector>(rv_ref_status.second.value_);
      return {true, rlist[0]->clone()};
    }
    return {true, rv_ref_status.second.clone()};

  }
  case Node::Type::Vector: {
    auto &rlist = get<Node::Vector>(head->value_);
    auto rv_status = eval(process, rlist);
    if(!rv_status.first) {
      cerr << "Error encounter in lisp::car vector " << rv_status << "\n";
      return rv_status;
    }
    if(rv_status.second->type_== Node::Type::Vector) {
      if(rv_status.second->empty_container()) return {true, Node::create()};
      auto rv_front_status = rv_status.second->front();
      if(!rv_front_status.first) {
        cerr << "Error encounter in lisp::car vector front " << rv_status << "\n";
        return {false,  rv_front_status.second.clone()};
      }
      return {true, rv_front_status.second.clone()};
    }
    return rv_status;

  }
  default: {

  }}
  cout << "car last outside switch!\n";
  return {true, head->clone()};

}
Node::OpStatus LispExpr::cdr(Node&process, const Node::Vector &list, int start) {
    Node::Vector rlist;
    size_t s=list.size();
    rlist.reserve(s);
    for(size_t i=0; i<s; i++) {
      auto evaled_status =  eval(process, *list[i]);
      if(!evaled_status.first) return evaled_status;
      rlist.push_back(move(evaled_status.second));
    }
    return  {true, Node::create(move(rlist))};

}
