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
vector<string> LispExpr::get_local_vars(Node&process) {
  MYLOGGER(trace_function, "LispExpr::get_lcoal_vars(Node&process)", __func__, SLOG_FUNC_INFO);

  vector<string> name_list={};

  auto frame_ref_status = frame_current(process);
  if(!frame_ref_status.first) return {};
  auto scopes_ref_status = frame_ref_status.second[SCOPES];
  if(!scopes_ref_status.first) return {};
  Node::Integer s = scopes_ref_status.second.size_container() ;

  for(Node::Integer i=s-1; i>=0; i--) {
    //auto scope_ref_status = scope_current(process);
    //cout << "symbol lookup i: " << i << "\n";
    auto scope_ref_status = scopes_ref_status.second[i];
    if(!scope_ref_status.first) {
      cerr << "get_local_vars(): scope lookup failed!" <<  scope_ref_status.second._to_str() << "\n";
      return {};
    }
    auto scope_vars_ref_status = scope_ref_status.second.get_node(VAR);

    if(!scope_vars_ref_status.first) {
      cerr << "get_local_vars() var[] lookup failed!" <<  scope_vars_ref_status.second._to_str() << "\n";
      return {};
    }

    auto scope_immute_ref_status = scope_ref_status.second.get_node(IMMUTE);
    if(!scope_immute_ref_status.first) {
     cerr << "get_local_vars() immute[] lookup failed!" <<  scope_immute_ref_status.second._to_str() << "\n";
      return {};
    }

    auto scope_args_ref_status = scope_ref_status.second.get_node(ARGS);
    if(!scope_args_ref_status.first) {
      cerr << "get_local_vars() args[] lookup failed!" <<  scope_immute_ref_status.second._to_str() << "\n";
      return {};
    }

    //cout << "scope_vars_ref_status:  " << scope_vars_ref_status << "\n";

    auto l_vars =  scope_vars_ref_status.second.get_keys_vector();
    name_list.insert(name_list.end(), l_vars.begin(), l_vars.end());

    auto l_immutes =  scope_immute_ref_status.second.get_keys_vector();
    name_list.insert(name_list.end(), l_immutes.begin(), l_immutes.end());

    auto l_args =  scope_args_ref_status.second.get_keys_vector();
    name_list.insert(name_list.end(), l_args.begin(), l_args.end());
  }
  return name_list;


}