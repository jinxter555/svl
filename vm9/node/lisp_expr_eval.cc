#include <iostream>
#include "lisp_expr.hh"
#include "my_helpers.hh"

#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"

#include "lisp_expr_func_tmpl.cc"



//------------------------------------------------------------------------
// symbol lookup 
Node::OpStatusRef LispExpr::arg_lookup(Node&process, const string&name ) {
  MYLOGGER(trace_function, "LispExpr::arg_lookup(Node&process, const string&)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, "name:" + name, SLOG_FUNC_INFO+30);

  auto frame_ref_back_status = frame_current(process);
  if(!frame_ref_back_status.first) return frame_ref_back_status;
  auto arg_ref_status = frame_ref_back_status.second[ARGS];
  if(!arg_ref_status.first) return arg_ref_status;
  return arg_ref_status.second[name];
}

//------------------------------------------------------------------------
Node::OpStatusRef LispExpr::var_lookup(Node&scope, const string&name ) {
  MYLOGGER(trace_function, "LispExpr::var_lookup(Node&scope, const string&)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, "name:" + name, SLOG_FUNC_INFO+30);

  auto scope_vars_ref_status = scope.get_node(VAR);
  if(!scope_vars_ref_status.first) {
    cerr << "var[] lookup failed!" <<  scope_vars_ref_status.second._to_str() << "\n";
    return scope_vars_ref_status;
  }

  auto nested_name = split_string(name, ".");

  if(nested_name.size()==1)
    return scope_vars_ref_status.second[name];

  // this returns a shared ptr to a map
  auto shared_ptr_ref_status = scope_vars_ref_status.second[nested_name[0]];

  if(!shared_ptr_ref_status.first) {
    cerr << "varlookup() error sptr_ref_status : " << shared_ptr_ref_status.second._to_str() << "\n";
    return shared_ptr_ref_status;
  }
  nested_name.erase(nested_name.begin());
  return shared_ptr_ref_status.second._get_ptr_s()->get_node(nested_name);

}

Node::OpStatusRef LispExpr::immute_lookup(Node&scope, const string&name ) {
  MYLOGGER(trace_function, "LispExpr::immute_lookup(Node&scope, const string&)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, "name:" + name, SLOG_FUNC_INFO+30);

  auto scope_immute_ref_status = scope.get_node(IMMUTE);
  if(!scope_immute_ref_status.first) {
    cerr << "immute[] lookup failed!" <<  scope_immute_ref_status.second._to_str() << "\n";
    return scope_immute_ref_status;
  }

  auto nested_name = split_string(name, ".");


  auto immute_ref_value = scope_immute_ref_status.second[name];
  if(nested_name.size()==1)
    return immute_ref_value;
  
  return scope_immute_ref_status.second[name];
}




//------------------------------------------------------------------------
// lookup both var, immute and then argument list in current frame
Node::OpStatusRef LispExpr::symbol_lookup(Node&process, const string&name ) {
  MYLOGGER(trace_function, "LispExpr::symbol_lookup(Node&process, const string&)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, "name:" + name, SLOG_FUNC_INFO+30);


  auto frame_ref_status = frame_current(process);
  if(!frame_ref_status.first) return frame_ref_status;

  auto scopes_ref_status = frame_ref_status.second[SCOPES];

  if(!scopes_ref_status.first) return scopes_ref_status;
  Node::Integer s = scopes_ref_status.second.size_container() ;

  //cout << "symbol lookup size: " << s << "\n";

  for(Node::Integer i=s-1; i>=0; i--) {
    //auto scope_ref_status = scope_current(process);
    //cout << "symbol lookup i: " << i << "\n";
    auto scope_ref_status = scopes_ref_status.second[i];
    if(!scope_ref_status.first) {
      cerr << "scope lookup failed!" <<  scope_ref_status.second._to_str() << "\n";
      return scope_ref_status;
    }
  
    auto var_ref = var_lookup(scope_ref_status.second, name);
    if(var_ref.first) return var_ref;
  
    auto immute_ref = immute_lookup(scope_ref_status.second, name);
    if(immute_ref.first) return immute_ref;

  }



  auto arg_ref = arg_lookup(process, name);
  if(arg_ref.first) return arg_ref;

  return {false, Error::ref(Error::Type::SymbolNotFound)};
}


//------------------------------------------------------------------------
// eval node 
Node::OpStatus LispExpr::eval(Node& process, const Node& code_node) {
  MYLOGGER(trace_function, "LispExpr::eval(Node&process, Node&code_node)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("code_node: ") + code_node._to_str(), SLOG_FUNC_INFO+30);

  if(code_node.empty_container())  return{true, Node::create(Node::Type::Vector)}; 

  switch(code_node.type_) {
  case Node::Type::Vector: {
    auto const &code_list = get<Node::Vector>(code_node.value_);
    return eval(process, code_list); }

  case Node::Type::Identifier: { // just identifier as a variable
    auto name = get<string>(code_node.value_);
    auto rv_ref_status = symbol_lookup(process, name  );
    if(!rv_ref_status.first) {
      cerr << "Identifier: " << name << " not found!" << rv_ref_status.second._to_str() << "\n";
      return {false, rv_ref_status.second.clone()};
    }
    if(rv_ref_status.second.type_ == Node::Type::Shared) 
      return {true, Node::ptr_USU(rv_ref_status.second)}; // clone a uniqu ptr to shared ptr without  recursive clone

    return {true, rv_ref_status.second.clone()};
  }
  case Node::Type::Map: { // object, lambda, 
    cout << "eval node map!\n";
    return {true, code_node.clone()};
  }
    

  //case Node::Type::Shared: { cout << "shared ptr!\n"; }
  default: {}}
  return {true, code_node.clone()};

  //return {true, Node::create_error(Error::Type::Unknown, "Unknown error should not reach!")};

}

//------------------------------------------------------------------------
// lisp op head
Node::OpStatus LispExpr::eval(Node& process, const Lisp::Op op_head, const Node::Vector& code_list, size_t start) {
  MYLOGGER(trace_function, "LispExpr::eval(Node&process, Lisp::Op, Node::Vector& code_list)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("lisp::op: ") + Lisp::_to_str(op_head), SLOG_FUNC_INFO+30);
  MYLOGGER_MSG(trace_function, string("code_list: ") + Node::_to_str(code_list), SLOG_FUNC_INFO+30);

  switch(op_head){
  case Lisp::Op::vector:  {
    //cout << "lisp::op:  nested vector code! start: " << start <<"\n";
    size_t s=code_list.size()-1, i; 

    for(i=start; i<s; i++) {
      auto evaled_status =  eval(process, *code_list[i]);
      if(!evaled_status.first) return evaled_status;
    }
    return  eval(process, *code_list[i]);

  }
  case Lisp::Op::print: return builtin_print_n(process, code_list, start);
  case Lisp::Op::literal: return literal(code_list, start);
  case Lisp::Op::var:     return var_attach(process, code_list, start); 
  case Lisp::Op::assign:  return assign_attach(process, code_list, start); 
  case Lisp::Op::funcall:   return funcall(process, code_list, start); 
  case Lisp::Op::call:   return call(process, code_list, start); 
  case Lisp::Op::car:   return car(process, code_list, start);
  case Lisp::Op::cdr:   return cdr(process, code_list, start);
  case Lisp::Op::lambda:    return lambda_create(process, code_list, start);
  case Lisp::Op::map:   return map_create(process, code_list, start);
  case Lisp::Op::send:   {
    cout << "sendng message in eval!\n"; //return map_messages(process, code_list, start );
    return {true, nullptr};
  }
  case Lisp::Op::class_:   {
    cout << "class in eval!\n"; //return map_messages(process, code_list, start );
    return {true, nullptr};
  }
  case Lisp::Op::private_:   {
    cout << "class in eval!\n"; //return map_messages(process, code_list, start );
    return {true, nullptr};
  }


  case Lisp::Op::call_extern: { return call_extern(process, code_list, start ); }
  case Lisp::Op::defun:   {
    cout << "defun in eval!\n";
    return {true, nullptr};
  }
  default:{}}
  cerr << "unknown command()!: " + Lisp::_to_str(op_head) + "\n"; 
  return {false, Node::create_error(Error::Type::Unknown, "Unknown Lisp::Op command")};
}

//------------------------------------------------------------------------
Node::OpStatus LispExpr::eval(Node& process, const Node::Vector& code_list) {
  MYLOGGER(trace_function, "LispExpr::eval(Node&process, Node::Vector& code_list)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("code_list: ") + Node::_to_str(code_list), SLOG_FUNC_INFO+30);

  //cout << "code_list size " << code_list.size() << "\n"; cout << "code_list str " << Node::_to_str(code_list) << "\n";
  if(code_list.empty()) return{true, Node::create(Node::Type::Vector)};

  switch(code_list[0]->type_) {

  case Node::Type::LispOp: {
    Lisp::Op op_head = get<Lisp::Op>(code_list[0]->value_);
    // skip the first element that's op_head
    return eval(process, op_head, code_list, 1); }

  case Node::Type::Identifier: { //    cerr << "code_list.size : " <<  code_list.size() << "\n";
    auto s = code_list.size() ;
    if(s == 1) { // signle element: identifier, var, immut, arg lookup //cout << "vector 1 identifier lookup : " << Node::_to_str(code_list) << "\n";
      return eval(process, *code_list[0]);
    } else if(s > 1) { // function lookup // cout << "identifier s>1!\n";
      return call(process, code_list);
    }
    return {false, Node::create_error(Error::Type::Unknown, "Unknown error in Identifier")};
  }

  case Node::Type::Vector: { // normally this is the code list block and return last element
    size_t i;
    for(i=0; i<code_list.size()-1; i++) {
      auto value_status = eval(process, *code_list[i]);
      if(!value_status.first) {
        cerr << "eval failed! " << *value_status.second << "\n";
        return value_status;
      }
      if(value_status.second->type_ == Node::Type::Map) { // need to figure if need to call lambda closure
        cout << "returned map or object need to check if t needs to call lambda or closure!\n";
      }
    }
    return eval(process, *code_list[i]);
  }

  // scalars here int, float string, etc
  default: { //cout << "eval default! type: " << Node::_to_str(code_list[0]->type_) << "\n";
    Node::Vector rlist;
    size_t s=code_list.size();
    rlist.reserve(s);
    for(size_t i=0; i<s; i++) {
      auto evaled_status =  eval(process, *code_list[i]);
      if(!evaled_status.first) return evaled_status;
      rlist.push_back(move(evaled_status.second));
    }
    return  {true, Node::create(move(rlist))};
  }}

  // code should not reach here
  cerr << "code should not reach here!\n";
  return {true, Node::create()};
}
