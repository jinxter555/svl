#include <iostream>
#include "lisp_expr.hh"

#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"

#include "lisp_expr_func_tmpl.cc"


//------------------------------------------------------------------------
// get parameters of caller, as in fun, lambda, macro, closure
//
vector<string> LispExpr::get_params(const Node::Map&caller) {
  MYLOGGER(trace_function, "LispExpr::get_params(Node::Map&closure)", __func__, SLOG_FUNC_INFO);
  vector<string> result_list;

  try {
    const auto &params_ptr= caller.at(_PARAMS);
    auto &params = params_ptr->_get_vector_ref();
    for(const auto&ele : params ) 
      result_list.push_back(ele->_to_str());
    return result_list;
  }catch(...) {
    return {};
  }

}
Node::OpStatus LispExpr::builtin_print_r(Node& process, const Node::Vector& cc_vec, size_t start) {
  MYLOGGER(trace_function, "LispExpr::builtin_print_r(Node&process, const Node::Vector& cc_vec, start)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, "cc_vector: " + Node::_to_str(cc_vec), SLOG_FUNC_INFO+30);
  MYLOGGER_MSG(trace_function, "start: " + start, SLOG_FUNC_INFO+30);
  size_t s=cc_vec.size();
  for(size_t i = start;  i<s; i++) {
    //Node::print_value_recursive(*cc_vec[i]);

    auto ee_status = eval(process, *cc_vec[i]);
    if(!ee_status.first)
      return ee_status;
   // Node::print_value_recursive(*ee_status.second);
   ee_status.second->print();
  }
  return {true, Node::create()};
}