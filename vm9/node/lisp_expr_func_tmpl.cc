#ifndef LISP_EXPR_FUNC_TMPL_CC
#define LISP_EXPR_FUNC_TMPL_CC

#pragma once
#include <iostream>
#include "lisp_expr.hh"

#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"

//------------------------------------------------------------------------
/*
template <typename T>
Node::OpStatus LispExpr::builtin_print(Node& env, const T& list) {
  MYLOGGER(trace_function, "LispExpr::print(Node&env, T&list)", __func__, SLOG_FUNC_INFO);
  if constexpr (is_same_v<T, Node::Vector> || is_same_v<T, Node::DeQue>||  is_same_v<T, Node::List>) {

    cout << "builtin_print_list\n";

    for(auto& element : list) { 
      if(element.first) {
        auto& ev = element.second->eval(env);
        cout << *ev.second << "\n";
      }
    }
    //return {true, Node::create()};
    //return {true, nullptr};
    return {true, Node::create()};
  } else {
    cout << "builtin_print something\n";
    //cout << list << "\n";
  }
}
*/
template <typename T>
Node::OpStatus LispExpr::builtin_print_n(Node& process, const T& list, size_t start) {
  MYLOGGER(trace_function, "LispExpr::builtin_print_n(Node&env, const T&list, size_t)", __func__, SLOG_FUNC_INFO);
  //cout << "builtin print!\n";
  //return {true, Node::create(true)};
  if constexpr (is_same_v<T, Node::Vector> || is_same_v<T, Node::DeQue>||  is_same_v<T, Node::List>) {
    size_t s=list.size();
    for(size_t i = start;  i<s; i++) {
      auto &element = list[i];
      auto ee = eval(process, *element);
      if(!ee.first ) return ee;
      if(ee.second->type_ == Node::Type::Atom) {  // only works for print :atom, not for print map 
        auto atom_ref_status = atom_to_str(ee.second->_get_integer());
        if(!atom_ref_status.first) return {false, atom_ref_status.second.clone()};
        cout << atom_ref_status.second;
      } else {
        cout << *ee.second;
      }
    }
  } else {
    cout << "builtin_print_n unknown T list\n";

  }
  return {true, Node::create()};
}
#endif