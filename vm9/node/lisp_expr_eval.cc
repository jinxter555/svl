#include <iostream>
#include "lisp_expr.hh"
#include "my_helpers.hh"

#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"

#include "lisp_expr_func_tmpl.cc"



//------------------------------------------------------------------------
// symbol lookup 
Node::OpStatusRef LispExpr::arg_lookup(Node&scope, const string&name ) {
  MYLOGGER(trace_function, "LispExpr::arg_lookup(Node&scope, const string&)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, "name:" + name, SLOG_FUNC_INFO+30);

//  cout << "scope:" << scope << "\n";
//  cout << "arg_lookup !" << name<< "\n\n";

//  auto frame_ref_back_status = frame_current(process);

//  if(!frame_ref_back_status.first) return frame_ref_back_status;
  auto arg_ref_status  = scope.get_node(ARGS);
  if(!arg_ref_status.first) return arg_ref_status;

//  cout << "arg_ref_status !"  << arg_ref_status <<"\n";

  auto nested_name = split_string(name, ".");

  if(nested_name.size()==1) {
    return arg_ref_status.second[name];
  }

  auto shared_ptr_ref_status = arg_ref_status.second[nested_name[0]];

  if(!shared_ptr_ref_status.first) {
    //cerr << "var_lookup() error sptr_ref_status : " << shared_ptr_ref_status.second._to_str() << "\n";
    return shared_ptr_ref_status;
  }

  nested_name.erase(nested_name.begin());
  return shared_ptr_ref_status.second._get_ptr_s()->get_node(nested_name);

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

  if(nested_name.size()==1) {
    return scope_vars_ref_status.second[name];
  }

  // this returns a shared ptr to a map
  auto shared_ptr_ref_status = scope_vars_ref_status.second[nested_name[0]];

  if(!shared_ptr_ref_status.first) {
    //cerr << "var_lookup() error sptr_ref_status : " << shared_ptr_ref_status.second._to_str() << "\n";
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


  //auto immute_ref_value = scope_immute_ref_status.second[name];
  if(nested_name.size()==1)
    return scope_immute_ref_status.second[name];
   // return immute_ref_value;

  auto shared_ptr_ref_status = scope_immute_ref_status.second[nested_name[0]];

  if(!shared_ptr_ref_status.first) {
    //cerr << "immute_lookup() error sptr_ref_status : " << shared_ptr_ref_status.second._to_str() << "\n";
    return shared_ptr_ref_status;
  }
  nested_name.erase(nested_name.begin());
  return shared_ptr_ref_status.second._get_ptr_s()->get_node(nested_name);
  //return scope_immute_ref_status.second[name];
}




//------------------------------------------------------------------------
// lookup both var, immute and then argument list in current frame
Node::OpStatusRef LispExpr::symbol_lookup(Node&process, const string&name ) {
  MYLOGGER(trace_function, "LispExpr::symbol_lookup(Node&process, const string&)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, "name:" + name, SLOG_FUNC_INFO+30);

  if(name=="nil") return {true, null_node};

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

    auto arg_ref = arg_lookup(scope_ref_status.second, name);
    if(arg_ref.first) return arg_ref;

  }




  return {false, Error::ref(Error::Type::SymbolNotFound)};
}


//------------------------------------------------------------------------

// eval node 
Node::OpStatus LispExpr::eval(Node& process, const Node& code_node) {
  MYLOGGER(trace_function, "LispExpr::eval(Node&process, Node&code_node)", __func__, SLOG_FUNC_INFO);
  //MYLOGGER_MSG(trace_function, "code_node: " + code_node._to_str(), SLOG_FUNC_INFO+30);

//  if(code_node.empty_container())  return{true, Node::create(Node::Type::Vector)}; 

  switch(code_node.type_) {
  case Node::Type::Vector: {
    auto const &code_list = get<Node::Vector>(code_node.value_);
    return eval(process, code_list); }

  case Node::Type::Identifier: { // just identifier as a variable
    auto name = get<string>(code_node.value_);
    auto rv_ref_status = symbol_lookup(process, name  );
    if(!rv_ref_status.first) {
      cerr << "Identifier: '" << name << "' not found!" << rv_ref_status.second._to_str() << "\n";
      return {false, rv_ref_status.second.clone()};
    }
    if(rv_ref_status.second.type_ == Node::Type::Shared) 
      return {true, Node::ptr_USU(rv_ref_status.second)}; // clone a uniqu ptr to shared ptr without  recursive clone

    return {true, rv_ref_status.second.clone()};
  }
  case Node::Type::ObjectId: { // object
    cout << "eval node object_id!\n";
    auto object_ref = object_get(process, code_node);
    return {object_ref.first, object_ref.second.clone()};
    break;
  }
  case Node::Type::Map: { // object, lambda, 
    cout << "eval node map!\n";
    return {true, code_node.clone()};
  }
    
  case Node::Type::List: { // object, lambda, 
    cout << "code node list: " << code_node._to_str()  << "\n";
    break;
  }


  case Node::Type::Shared: { // object, lambda, 
    MYLOGGER_MSG(trace_function, string("Shared code_node: ") + code_node._to_str(), SLOG_FUNC_INFO+30);
    //cout << "code node Shared\n";
    auto s_ptr = get<Node::ptr_S>(code_node.value_);
    return eval(process, *s_ptr);
  }

  default: {
  }}

  return {true, code_node.clone()};

}

//------------------------------------------------------------------------
// lisp op head
Node::OpStatus LispExpr::eval(Node& process, const Lisp::Op op_head, const Node::Vector& code_list, size_t start) {
  MYLOGGER(trace_function, "LispExpr::eval(Node&process, Lisp::Op op_head, Node::Vector& code_list)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("Lisp::Op:: ") + Lisp::_to_str(op_head), SLOG_FUNC_INFO+30);

//  if(op_head == Lisp::Op::error) { return {false, Node::create_error(Error::Type::Eval, "Got an evail error") };}

  MYLOGGER_MSG(trace_function, string("code_list: ") + Node::_to_str(code_list), SLOG_FUNC_INFO+30);
  MYLOGGER_MSG(trace_function, "start: " + to_string(start), SLOG_FUNC_INFO+30);

  switch(op_head){
  case Lisp::Op::nil:     return {true, Node::create()};
  case Lisp::Op::noop:     return {true, Node::create(Lisp::Op::noop)};
  case Lisp::Op::root:  return root_manifest(process, code_list, start); 
  case Lisp::Op::vector:  return eval(process, code_list, start); 
  case Lisp::Op::print: return builtin_print_n(process, code_list, start);
  case Lisp::Op::printr: return builtin_print_r(process, code_list, start);
  case Lisp::Op::literal: return literal(code_list, start);
  case Lisp::Op::unquote: return unquote(process, code_list, start);
  case Lisp::Op::var:     return var_attach(process, code_list, start); 
  case Lisp::Op::assign:  return assign_attach(process, code_list, start); 
  case Lisp::Op::eval:     return eval_eval(process, code_list, start);
  case Lisp::Op::read:   return read_input();
  case Lisp::Op::loop:   return loop_forever(process,code_list,start );

  case Lisp::Op::while_:   return while_(process, code_list, start );
  case Lisp::Op::return_:   return lisp_object_return(process, code_list, start );
  case Lisp::Op::exit_:   {forever=false; return {true, Node::create() };};

  case Lisp::Op::funcall:   return funcall(process, code_list, start); 
  case Lisp::Op::call:   return call(process, code_list, start); 
  case Lisp::Op::car:   return car(process, code_list, start);
  case Lisp::Op::cdr:   return cdr(process, code_list, start);
  case Lisp::Op::lambda:    return lambda_create(process, code_list, start);
  case Lisp::Op::do_:    return closure_create(process, code_list, start);
  case Lisp::Op::faz:    return faz(process, code_list, start);

  case Lisp::Op::hash:   return hash_create(process, code_list, start);
  case Lisp::Op::ihash:   return ihash_create(process, code_list, start);
  case Lisp::Op::new_:  return object_create(process, code_list, start);
  case Lisp::Op::delete_:  return object_delete(process, code_list, start);
  //case Lisp::Op::clone:  return clone(process, code_list, start);
  case Lisp::Op::send:    return send_object_message(process, code_list, start); 
  case Lisp::Op::if_:    { return if_(process, code_list, start ); }
  case Lisp::Op::iif:    { return if_(process, code_list, start ); }
  case Lisp::Op::cond:    { return cond(process, code_list, start ); }
  case Lisp::Op::match:    { return match(process, code_list, start ); }
  case Lisp::Op::case_:    { return case_(process, code_list, start ); }
  case Lisp::Op::quote: { return quote(process, code_list, start); }
  case Lisp::Op::error: { 
    return {false, Node::create_error(Error::Type::Eval, "Got an (error)") };
  }



  case Lisp::Op::class_:   {
    cout << "class in eval!\n"; //return map_messages(process, code_list, start );
    return {true, Node::create()};
  }
  case Lisp::Op::private_:   {
    cout << "private in eval!\n"; //return map_messages(process, code_list, start );
    return {true, Node::create()};
  }

  case Lisp::Op::call_extern: { return call_extern(process, code_list, start ); }
  case Lisp::Op::defun:   {
    cout << "defun in eval!\n";
    return {true, Node::create()};
  }
  default:{ return  eval_math(process, op_head, code_list, start); }
  } 
  cerr << "unknown op()!: " + Lisp::_to_str(op_head) + "\n"; 
  return {false, Node::create_error(Error::Type::Unknown, "Unknown Lisp::Op command")};
}

#include "lisp_expr_eval_math.hh"

//------------------------------------------------------------------------
// usally init eval with vector [lisp:op arg1 arg2.. ]
//
Node::OpStatus LispExpr::eval(Node& process, const Node::Vector& code_list) {
  MYLOGGER(trace_function, "LispExpr::eval(Node&process, Node::Vector& code_list)", __func__, SLOG_FUNC_INFO);
 // if(code_list.empty()) return{true, Node::create(Node::Type::Vector)};
  if(code_list.empty()) return{true, Node::create()};
  MYLOGGER_MSG(trace_function, string("code_list: ") + Node::_to_str(code_list), SLOG_FUNC_INFO+30);
 // MYLOGGER_MSG(trace_function, "code_list[0]->type_: " + Node::_to_str(code_list[5]->type_) + ", code_list[0]->value_: " + code_list[0]->_to_str(), SLOG_FUNC_INFO+30)

  //cout << "code_list size " << code_list.size() << "\n"; cout << "code_list str " << Node::_to_str(code_list) << "\n";
 // if(code_list.empty()) return{true, Node::create(Node::Type::Vector)};
//  if(code_list.empty()) return{true, Node::create()};

  switch(code_list[0]->type_) {

  case Node::Type::LispOp: {
    Lisp::Op op_head = get<Lisp::Op>(code_list[0]->value_); // skip the first element that's op_head
    return eval(process, op_head, code_list, 1); }


  case Node::Type::Identifier: { //    cerr << "code_list.size : " <<  code_list.size() << "\n";
    auto s = code_list.size() ;
    if(s == 1) { // signle element: identifier, var, immut, arg lookup //cout << "vector 1 identifier lookup : " << Node::_to_str(code_list) << "\n";
      return eval(process, *code_list[0]);
    } else if(s > 1) { // function lookup // cout << "identifier s>1!\n";
      return call(process, code_list);
    }
    return {false, Node::create_error(Error::Type::Unknown, "Unknown error in Identifier :'" + code_list[0]->_to_str() + "'")};
  }

  case Node::Type::Vector: 
    return eval(process, code_list, 0);

  // scalars here int, float string, etc
  default: { 
    MYLOGGER_MSG(trace_function, string("code_list type ") + Node::_to_str(code_list[0]->type_), SLOG_FUNC_INFO+30);

    return eval(process, code_list, 0);

  }}

  // code should not reach here
  cerr << "code should not reach here!\n";
  return {true, Node::create()};
}


//------------------------------------------------------------------------
Node::OpStatus LispExpr::eval(Node& process, const Node::Vector& code_list, size_t start, size_t front_insert_count) {
  MYLOGGER(trace_function, "LispExpr::eval(Node&process, Node::Vector& code_list, size_t start)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, "code_list: " + Node::_to_str(code_list), SLOG_FUNC_INFO+30);
  MYLOGGER_MSG(trace_function, "start: " + to_string(start), SLOG_FUNC_INFO+30);

  //if(code_list.empty()) return {true, Node::create()};

  Node::Vector result_list; //, result_list2;
  size_t s=code_list.size();
  result_list.reserve(s+front_insert_count);

  // create a list of prepend object for front replacement
  for(size_t i=0; i<front_insert_count; i++) { result_list.push_back(Node::create()); }


  for(size_t i=start; i<s; i++) { // return last eval,  size -1 
    auto value_status = eval(process, *code_list[i]);
    if(!value_status.first) {
      auto frame_ref_status = frame_current(process);
      if(frame_ref_status.first) { // get frame and find out where eval failed.
        auto current_module = frame_ref_status.second[CURRENT_MODULE].second._to_str();
        auto current_class = frame_ref_status.second[CURRENT_CLASS].second._to_str();
        auto current_function = frame_ref_status.second[CURRENT_FUNCTION].second._to_str();
        cout << "In Module:" << current_module << ", Class "<<   current_class<<  "\n";
        cout << "Function or method: " << current_function <<"\n";
      }
      cerr << "eval failed! " << *value_status.second << "\n" << *code_list[i] <<"\n";
      return value_status;
    }

    // return is an object 
    if(value_status.second->type_ == Node::Type::Map) { // need to figure if need to call lambda closure
      switch(handle_cf_object(process, result_list, value_status.second->_get_map_ref())) {
      case Node::ControlFlow::cf_run: { break;}
      case Node::ControlFlow::cf_return:{ 
        //return  {true, Node::create(move(result_list))}; 
        //cout << "return value_status " << *value_status.second<< "\n";
        return  {true, move(value_status.second)};
      }
      default: {}
      }
    }


    result_list.push_back(move(value_status.second));
  }
  return  {true, Node::create(move(result_list))};
}

Node::OpStatus LispExpr::eval_eval(Node& process, const Node::Vector& code_list, size_t start) {
  MYLOGGER(trace_function, "LispExpr::eval_eval(Node&process, Node::Vector& code_list, size_t start)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, "code_list: " + Node::_to_str(code_list), SLOG_FUNC_INFO+30);
  MYLOGGER_MSG(trace_function, "Lisp::Op::eval: start " + to_string(start) + ", code_list " + Node::_to_str(code_list), SLOG_FUNC_INFO+30);

  // if(code_list.empty()) return {true, Node::create()};
//  cout << "\nLisp::Op::eval: code_list:" + Node::_to_str(code_list) << "\n";
  auto evaled_stat1 = eval(process, code_list, start); 
  if(!evaled_stat1.first) {
    cerr << "something is wrong with eval('code...') :" << Node::_to_str(code_list) << "\n";
    return evaled_stat1;
  }
  auto inner_ref_status = evaled_stat1.second->get_node(0);
  auto evaled_stat2 = eval(process, inner_ref_status.second); 
  if(!evaled_stat2.first) {
    cerr << "something is wrong with code returned by  eval('code...') :" << evaled_stat2.second->_to_str() << "\n";
    cerr << "inner  :" << inner_ref_status << "\n";


  }
  //cout << "evaluated stat2: " <<  evaled_stat2<< "\n";
  return evaled_stat2;
}