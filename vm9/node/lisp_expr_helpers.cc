#include <iostream>
#include "lisp_expr.hh"

#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"

#include "lisp_expr_func_tmpl.cc"


//------------------------------------------------------------------------
vector<string> LispExpr::get_params(const Node::Map&closure) {
  MYLOGGER(trace_function, "LispExpr::get_params(Node::Map&closure)", __func__, SLOG_FUNC_INFO);
  vector<string> result_list;

  const auto &params_ptr= closure.at(_PARAMS);
  auto &params = params_ptr->_get_vector_ref();

  for(const auto&ele : params ) 
    result_list.push_back(ele->_to_str());
  
  return move(result_list);
}