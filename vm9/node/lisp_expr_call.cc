#include <iostream>
#include "lisp_expr.hh"
#include "my_helpers.hh"
#include "defs.hh"

#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"



// (call (module function) (arg1 arg2 arg3))
//       (module function )
// (identifer (x y z ...))
//        (module, function) = identifier
// returns (module, function)
vector<string> LispExpr::extract_mf(Node& process, Node&node_mf) {
  MYLOGGER(trace_function, "LispExpr::extract_mf(Node&process, const Node& node_mf)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("node_mf: ") + node_mf._to_str(), SLOG_FUNC_INFO+30);

  switch(node_mf.type_) {
  case Node::Type::Identifier: {
    Node::Vector list;

    auto mf = node_mf._get_str();
    auto mf_full_name =  split_string(mf ,"."); // is it in form of module.fuction  with a dot?

    if(mf_full_name.size() == 1 ) { 
      list.push_back(Node::create(mf));
      return extract_mf(process, list);  // get module name from frame
    } else {
      return mf_full_name;
    }
  }

  case  Node::Type::Vector:{
    auto &list = node_mf._get_vector_ref();
    return extract_mf(process, list); }
  default: return {}; }
  return {};
}

vector<string> LispExpr::extract_mf(Node& process, Node::Vector &list) {
  MYLOGGER(trace_function, "LispExpr::extract_mf(Node&process, const Node& list)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("list: ") + Node::_to_str(list), SLOG_FUNC_INFO+30);

  // call (func)  no module specified use frame to get module info
  if(list.size() == 1 ) {
    //cout << "extract mf size 1\n";
    auto f = list[0]->_to_str();

    auto frames_status = process[FRAMES];
    if(!frames_status.first) { 
      cerr << " frames[] not found: " << frames_status.second._to_str() << "\n";
      return {};
    }
    auto last_frame_status = frames_status.second.back();
    if(!last_frame_status.first)  { 
      /*
      cout << "process: " << process << "\n";
      cout << "pid: " << process[PID] << "\n";
      cout << "frames: " << frames_status.second << "\n";
      */
      cerr << " last frame not found: " << last_frame_status.second._to_str() << "\n";
      return {};
    }

    auto current_module_status = last_frame_status.second[CURRENT_MODULE];
    if(!current_module_status.first) {return {};
      cerr << " current module not found in last frame: " << current_module_status.second._to_str() << "\n";
      return {};
    }

    auto m  = current_module_status.second._to_str();
   // cout << "m:"  << m  << ", f:" << f <<"\n";
    return {m, f};

  } else if(list.size() == 2 ) {
    auto m = list[0]->_to_str();
    auto f = list[1]->_to_str();
    return {m, f};
  }
  return {};
}


//------------------------------------------------------------------------
// call to lambda anonymous functions
//
Node::OpStatus LispExpr::attach_params_args_to_frame(unique_ptr<Node>& frame, const vector<string>& params, Node::Vector &&arg_list) {
  MYLOGGER(trace_function, "LispExpr::attach_params_args_to_frame(frame, param_path, arg_list)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("param_path: ") + _to_str_ext(params), SLOG_FUNC_INFO+30);
  MYLOGGER_MSG(trace_function, string("arg_list: ") + Node::_to_str(arg_list), SLOG_FUNC_INFO+30);

  if(arg_list.size() != params.size())
    return {false, Node::create_error(Error::Type::InvalidOperation,  
      "attach_params_args_to_frame() different size of params: "  
      + to_string( params.size()) 
      + " "  + _to_str_ext(params)
      + " and args: "  + to_string(arg_list.size())
      + " " + Node::_to_str(arg_list)
    )};
  size_t s =  params.size();

  Node::Map args;
  for(size_t i=0; i <s; i++) {
    args[params[i]] = move(arg_list[i]);
  }
  frame->set(ARGS, Node::create(move(args)));
  return {true, nullptr};
}

//------------------------------------------------------------------------

Node::OpStatus   LispExpr::frame_create_fun_args(Node& fun, Node::Vector &&arg_list) {
  MYLOGGER(trace_function, "LispExpr::frame_create_params_args(frame, param_path, arg_list)", __func__, SLOG_FUNC_INFO);
  //MYLOGGER_MSG(trace_function,  "params: " + _to_str_ext(params), SLOG_FUNC_INFO+30);
  MYLOGGER_MSG(trace_function, "arg_list: " + Node::_to_str(arg_list), SLOG_FUNC_INFO+30);


  auto const params = get_params(fun._get_map_ref());

  if(arg_list.size() != params.size())
    return {false, Node::create_error(Error::Type::InvalidOperation,  
      "frame_create_params_args() different size of params: "
      + to_string( params.size()) 
      + " "  + _to_str_ext(params)
      + " and args: "  + to_string(arg_list.size())
      + " " + Node::_to_str(arg_list)
    )};
  Node::Map args;
  size_t s =  params.size();
  for(size_t i=0; i <s; i++) {
    args[params[i]] = move(arg_list[i]);
  }
  auto frame = frame_create();
  frame->set(ARGS, Node::create(move(args)));


  // frame need to set current module ptr current 
  auto fun_name = fun.get_node_with_ptr(NAME).second._to_str();
  frame->set(CURRENT_FUNCTION, fun_name); 
  frame->set(CURRENT_FUNCTION_PTR, &fun); 

  if(fun.m_has_key(CLASS_PTR)) {
    auto &class_node = fun.get_node(CLASS_PTR).second;
    auto &module_node = class_node.get_node_with_ptr(MODULE_PTR).second;
    auto class_name = class_node.get_node_with_ptr(NAME).second._to_str();
    auto module_name = module_node.get_node_with_ptr(NAME).second._to_str();

    //cout << "fun parent class name :" << class_node.get_node_with_ptr(NAME) <<  "\n";
    //cout << "fun parent class :" << class_node <<  " is an object!";
    //cout << "module :" << module_node<<  "\n\n";


    frame->set(CURRENT_CLASS, class_name); 
    frame->set(CURRENT_CLASS_PTR, &class_node); 

    frame->set(CURRENT_MODULE, module_name); 
    frame->set(CURRENT_MODULE_PTR, &module_node); 

  } else if(fun.m_has_key(MODULE_PTR)) {
    auto &module_node = fun.get_node_with_ptr(MODULE_PTR).second;
    auto module_name = module_node.get_node_with_ptr(NAME).second._to_str();

    frame->set(CURRENT_MODULE, module_name); 
    frame->set(CURRENT_MODULE_PTR, &module_node); 

  }else {
    cerr << "fun has no class_ptr or module_ptr!\n";
    return {false, nullptr};
  }


  //return {true, move(frame)};
  return {true, move(frame)};
}

//------------------------------------------------------------------------
// call to closure blocks .. (for range(1..10) (do (i) ..))
//   ie. attach range value to var i with new scope
///
Node::OpStatus LispExpr::attach_params_args_to_scope_vars(Node& process, const vector<string>& params, Node::Vector &&arg_list) {
  MYLOGGER(trace_function, "LispExpr::attach_params_args_to_scope_vars(Node&process, Vector&params, Vector&arg_list)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("param_path: ") + _to_str_ext(params), SLOG_FUNC_INFO+30);
  MYLOGGER_MSG(trace_function, string("arg_list: ") + Node::_to_str(arg_list), SLOG_FUNC_INFO+30);

  auto frame_ref_status=frame_current(process);
  if(!frame_ref_status.first) {
    cerr << "attach_params_args_scope_vars() current frame not found in process!\n";
    return {false, Node::create_error(Error::Type::KeyNotFound,  
      "attach_params_args_scope_vars()  current_frame not found in process")};
  }

  auto scopes_ref_status = frame_ref_status.second.get_node(SCOPES);
  if(!scopes_ref_status.first) {
    cerr << "attach_params_args_scope_vars() [SCOPES] not found in frame!\n";
    return {false, Node::create_error(Error::Type::KeyNotFound,  
      "attach_params_args_scope_vars() [SCOPES] not found in frame")};
  }
  if(arg_list.size() != params.size())
    return {false, Node::create_error(Error::Type::InvalidOperation,  
      "attach_params_args_to_frame() different size of params and args")};
  
    
  size_t s =  params.size();
  auto scope = scope_create();
  auto var_ref_status = scope->get_node(VAR);
  auto &var_list = var_ref_status.second;
  for(size_t i=0; i <s; i++) {
    var_list.set(params[i],  move(arg_list[i]));
  }
  scope_push(process, move(scope));
  


  return {true, nullptr};
}

//------------------------------------------------------------------------
// (call (module function) (arg1 arg2 arg3))
Node::OpStatus LispExpr::call(Node& process, const Node& code_node) {
  MYLOGGER(trace_function, "LispExpr::call(Node&process, const Node& code_node)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("code_node: ") + code_node._to_str(), SLOG_FUNC_INFO+30);

  if(code_node.type_ != Node::Type::Vector)
    return {false, Node::create_error(Error::Type::InvalidOperation,  
      "Can't call module_function != (module function)\n")};

  const auto& code_list =get<Node::Vector>(code_node.value_);
  return call(process, code_list);

} 


// code_list = (call (module function) (arg1 arg2 arg3))
Node::OpStatus LispExpr::call(Node& process, const Node::Vector& code_list, size_t start) {
  MYLOGGER(trace_function, "LispExpr::call(Node&process, const Node::Vector& code_list, int start)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("code_node: ") + Node::_to_str( code_list) + " start:" + to_string(start), SLOG_FUNC_INFO+30);

  const auto &mf_list_pair =  code_list[start];
  auto mf_vector = extract_mf(process, *mf_list_pair); //cout << "mf_vector " << _to_str_ext(mf_vector) << "\n";

  // might need to fix this later on because it might be inconsistent but less parethesis
  // call object?
  auto object_ref = symbol_lookup(process, mf_vector[0]); // this might be an object call?
  if(object_ref.first) {
    try {
      const auto &argv_vector =  code_list[start+1]->_get_vector_ref();
      return call_object(process, object_ref.second, mf_vector[1], argv_vector);
    } catch(...) {}
    const auto &argv_vector =  list_clone_remainder(code_list, start + 1);
    return call_object(process, object_ref.second, mf_vector[1], argv_vector);
  }

  // module funtion call
  auto fun_path = lisp_path_module;
  fun_path.push_back(mf_vector[0]); // push module name

  auto mac_path = fun_path; // just copy to the macro
  mac_path.push_back(MACRO);

  fun_path.push_back(FUNCTION);    //  push module."function".
  fun_path.push_back(mf_vector[1]); // module."function".func_name

  mac_path.push_back(mf_vector[1]); // try macro 


  try { // mod.fun ( arg1 arg2 arg3 ...)
    const auto &argv_vector =  code_list[start+1]->_get_vector_ref();

    auto fun_exist = get_node(fun_path);
    if(fun_exist.first) {
      auto call_fun_status = call(process, fun_path, argv_vector);
      if(call_fun_status.first) return call_fun_status;

    }

    auto mac_exist = get_node(mac_path);
    if(mac_exist.first) {
      auto call_mac_status = call_macro(process, mac_path, argv_vector);
      if(call_mac_status.first) return call_mac_status;
    }
    

  } catch(...) {}

  // mod.fun arg1 arg2 arg3 ...
  const auto &argv_vector =  list_clone_remainder(code_list, start + 1);

  auto fun_exist = get_node(fun_path);
  if(fun_exist.first) {
    auto call_fun_status = call(process, fun_path, argv_vector);
    if(call_fun_status.first) return call_fun_status;
  }

    // try macro
  auto mac_exist = get_node(mac_path);
  if(mac_exist.first) {
    auto call_mac_status = call_macro(process, mac_path, argv_vector);
    if(call_mac_status.first) return call_mac_status;
  }

  //return call_fun_status; // return fun status for now


  return {false, Node::create_error(Error::Type::KeyNotFound, "Either function or macro symbol '" + mf_vector[1] + "' not found!\n")};
}

Node::OpStatus LispExpr::call_object(Node&process,  Node& object, const string method_name, const Node::Vector& argv_list) {
  MYLOGGER(trace_function, "LispExpr::call_object(Node&process, const Node& fun, Node::vector&&argv_list)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, "object: " + object._to_str(), SLOG_FUNC_INFO+30);
  MYLOGGER_MSG(trace_function, "argv_list: " + Node::_to_str(argv_list), SLOG_FUNC_INFO+30);

  try {
    auto fun_ref_status
    =object.get_node_with_ptr(OBJ_INFO)
    .second.get_node_with_ptr(CLASS_PTR)
    .second.get_node_with_ptr(FUNCTION);

//    cout << "fun ref status :" << fun_ref_status << "\n";
    auto  argvs_status = eval(process, argv_list, 0); // this returns a vector
    if(!argvs_status.first) {
      cerr << " call_object() error eval argv_list: " << Node::_to_str(argv_list) + argvs_status.second->_to_str() <<"\n";
      return argvs_status;
    }

    auto object_uptr = Node::ptr_USU(object); // this object
    argvs_status.second->push_front(move(object_uptr));
    auto method_fun_ref = fun_ref_status.second.get_node(method_name);

    if(!method_fun_ref.first) {
      string msg = "send object message() method '" + method_name +  "' not found!";
      cerr << msg << "\n";
      return {false, Node::create_error(Error::Type::FunctionNotFound, msg)};
    }

    return call(process, method_fun_ref.second, move(argvs_status.second->_get_vector_ref()));


  } catch(...) {
      string msg = "call_object() calling not Not class object!";
      cerr << msg << "\n";
      return {false, Node::create_error(Error::Type::SymbolNotFound,  msg)};

  }
  return {true, Node::create()};

}



// call process, vector [ full path name ] [params]
//Node::OpStatus LispExpr::call(Node& process, const Node::Vector& path, const Node::Vector& params) {
Node::OpStatus LispExpr::call(Node& process, const vector<string>& path, const Node::Vector& argv_list) {
  MYLOGGER(trace_function, "LispExpr::call(Node&process, const Node& path, const Node::vector&params)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("path: ") + _to_str_ext(path), SLOG_FUNC_INFO+30);


  auto fun_ref_status = get_node(path);
  if(!fun_ref_status.first) {
    cerr << "error looking up fun path: " << _to_str_ext( path ) + "," + fun_ref_status.second._to_str() <<"\n";
    return {false, fun_ref_status.second.clone()};
  }

  //auto  args_status = eval(process, argv_list); // this returns a vector
  auto  args_status = eval(process, argv_list, 0); // this returns a vector

  if(!args_status.first) {
    cerr << " call() error eval argv_list: " << _to_str_ext( path ) + ": " + Node::_to_str(argv_list) + args_status.second->_to_str() <<"\n";
    return args_status;
  }

  auto &argv = args_status.second->_get_vector_ref();

  return call(process, fun_ref_status.second, move(argv));

}
//------------------------------------------------------------------------
Node::OpStatus LispExpr::call_macro(Node& process, const vector<string>& path, const Node::Vector& argv_list) {
  MYLOGGER(trace_function, "LispExpr::call_macro(Node&process, const Node& fun, Node::vector&&argv_vector)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("path: ") + _to_str_ext(path), SLOG_FUNC_INFO+30);
  MYLOGGER_MSG(trace_function, "argv_vector: " + Node::_to_str(argv_list), SLOG_FUNC_INFO+30);

  cout <<  "call macro!";
  auto mac_ref_status = get_node(path);
  if(!mac_ref_status.first) {
    cerr << "error looking up macro path: " << _to_str_ext( path ) + "," + mac_ref_status.second._to_str() <<"\n";
    return {false, mac_ref_status.second.clone()};
  }
  auto frame_status = frame_create_fun_args(mac_ref_status.second, move(Node::clone(argv_list)->_get_vector_ref()));
  if(!frame_status.first) {
    cerr << "call_mac(process, path, argv list) can't do frame_create_params!"  +  frame_status.second->_to_str() +"\n";
    return frame_status;
  }
  frame_push(process, move(frame_status.second));
  auto scope = scope_create();
  auto scope_status =  scope_push(process, move(scope));

  auto code_list_status = mac_ref_status.second.get_node(CODE);
  if(!code_list_status.first) {
    cerr << "call_mac(process, path, argv_list) error!" +  code_list_status.second._to_str() +"\n";
    return {false, code_list_status.second.clone()};
  }
  auto evaled_status = eval(process, code_list_status.second);
  frame_pop(process);
  return evaled_status;
}

//------------------------------------------------------------------------
Node::OpStatus LispExpr::call(Node& process, Node& fun, Node::Vector&& argv_vector) {
  MYLOGGER(trace_function, "LispExpr::call(Node&process, const Node& fun, Node::vector&&argv_vector)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, "fun: " + fun._to_str(), SLOG_FUNC_INFO+30);
  MYLOGGER_MSG(trace_function, "argv_vector: " + Node::_to_str(argv_vector), SLOG_FUNC_INFO+30);

  auto frame_status = frame_create_fun_args(fun, move(argv_vector));
  if(!frame_status.first) {
    cerr << "call(process, fun, argv vector) can't do frame_create_params!"  +  frame_status.second->_to_str() +"\n";
    return frame_status;
  }
  frame_push(process, move(frame_status.second));
  auto scope = scope_create();
  auto scope_status =  scope_push(process, move(scope));

  auto code_list_status = fun.get_node(CODE);
  if(!code_list_status.first) {
    cerr << "call(process, fun, argv) error!" +  code_list_status.second._to_str() +"\n";
    return {false, code_list_status.second.clone()};
  }
  //return eval(process, code_list_status.second);
  auto evaled_status = eval(process, code_list_status.second);
  frame_pop(process);
  return evaled_status;
}


//------------------------------------------------------------------------ funcall var
// (funcall var (arglist))
//           start start+1
// var should be an lambda object from __object_info__
//
Node::OpStatus LispExpr::funcall(Node& process, const Node::Vector& code_list, size_t start) {
  MYLOGGER(trace_function, "LispExpr::funcall(Node&process, Node::Vector&list, int start)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, "node_list:" + Node::_to_str(code_list), SLOG_FUNC_INFO+30);
  MYLOGGER_MSG(trace_function, string("start: ") + to_string(start), SLOG_FUNC_INFO+30);

  auto &fun_var_ptr = code_list[start];

  if(fun_var_ptr->type_ != Node::Type::Identifier) {
    cerr << "funcall() fun_var is not an identifier:" << fun_var_ptr->_to_str() << "\n";
    return {false, Node::create_error(Error::Type::Parse, "funcall() fun_var is not an identifier! " + fun_var_ptr->_to_str())};
  }
  auto obj_ref_status = symbol_lookup(process, fun_var_ptr->_to_str());
  if(!obj_ref_status.first) {
    cerr << "funcall() fun_var lookup up failed :" << fun_var_ptr->_to_str() << "\n";
    return {false, Node::create_error(Error::Type::Parse, "funcall() fun_var identifier lookup failed! " + fun_var_ptr->_to_str())};
  }

  auto args = list_clone_remainder(code_list, start+1);

  switch(obj_ref_status.second.type_){
  case  Node::Type::Map: {
    auto &obj_lambda = get<Node::Map>(obj_ref_status.second.value_);
    return call_lambda(process, obj_lambda, move(args) );
  }
  case  Node::Type::Shared: {

    auto s_ptr = get<Node::ptr_S>(obj_ref_status.second.value_);
    if(s_ptr->type_!=Node::Type::Map) {
      cerr << "funcall() shared obj type: " << s_ptr->get_type() << "\n";
      return {false, Node::create_error(Error::Type::Parse, 
        "funcall() fun_var identifier lookup failed shareptr object ! " + s_ptr->_to_str())};
    }
    //cout << "shared obj type: " << Node::_to_str( s_ptr->_get_type()) << "\n";
    //cout << "shared obj : " << *s_ptr << "\n";
    //cout << "get params from obj : " << _to_str_ext( get_params(s_ptr->_get_map_ref()))  << "\n";

    return call_lambda(process, s_ptr->_get_map_ref(), move(args) );
  }
  default: 
    cerr << "funcall() fun_var lookup up failed " << fun_var_ptr->_to_str() << " is not a Node::Type::Map primitive\n";
    cout << "get type: " << obj_ref_status.second.get_type() << "\n";
    return {false, Node::create_error(Error::Type::Parse, "funcall() fun_var identifier lookup failed! " + fun_var_ptr->_to_str())};
  }
  cout << "fun call var!\n";
  return {true, nullptr};
}

//
// args must be a && that cloned from parent function
//
Node::OpStatus LispExpr::call_lambda(Node& process, const Node::Map & obj_lambda, Node::Vector&& args) {
  MYLOGGER(trace_function, "LispExpr::call_lambda(Node&process, Node::Map&obj_lambda, Node::Vector&& args)", __func__, SLOG_FUNC_INFO)
  MYLOGGER_MSG(trace_function, "args:" + Node::_to_str(args), SLOG_FUNC_INFO+30)


  // why frame is need because args to be stored in frame
  auto frame = frame_create();
  auto params = move(get_params(obj_lambda));

  //auto op_status = attach_params_args_to_frame(frame, move(params), move(args) );
  auto op_status = attach_params_args_to_frame(frame, params, move(args) );
  if(!op_status.first) {
    cerr 
    << "LispExpr::call_lambda(): error params and args " 
    << op_status.second->_to_str() << "\n";
    return op_status;
  }

  frame_push(process, move(frame));
  const auto &obj_info = obj_lambda.at(OBJ_INFO);
  auto type_ref_status = obj_info->get_node(TYPE);

  const auto &code = obj_lambda.at(CODE);
  if(!type_ref_status.first) {
    cerr << "obj type info error:" <<  type_ref_status.second._to_str() << "\n";
    return {false, type_ref_status.second.clone()};
  }
  //auto type = get<Node::Integer>(type_ref_status.second.value_);
  auto type = get<Lisp::Type>(type_ref_status.second.value_);
  if(type == Lisp::Type::lambda) {
    //cout << "call object type == lambda\n";
    return eval(process, *code);
  }
  cerr << "call __object_info__.type != lambda. but call_lambda()!\n";
  return {false, Node::create_error(Error::Type::Unknown,  "call __object_info__.type != lambda. but call_lambda()!")};

 }

//------------------------------------------------------------------------ call_closure
// call to closure blocks .. (for range(1..10) (do (i) ..))
//   ie. attach range value to var i with new scope
//
Node::OpStatus LispExpr::call_closure(Node& process, const Node::Map & obj_closure, Node::Vector&& args) {
  MYLOGGER(trace_function, "LispExpr::call_closure(Node&process, Node::Map&obj_closure, Node::Vector&& args)", __func__, SLOG_FUNC_INFO)
  MYLOGGER_MSG(trace_function, "args:" + Node::_to_str(args), SLOG_FUNC_INFO+30)

  /*
  auto scope_ref_status = scope_current(process);
  if(!scope_ref_status.first)  {
    cerr << "call_closure() scope current error!\n" ;
    return {false, Node::create_error(Error::Type::Unknown,  "call_closure() scope current error!" + scope_ref_status.second._to_str())};
  }*/
  auto params = move(get_params(obj_closure));
  attach_params_args_to_scope_vars(process, params, move(args));


  return {false, Node::create_error(Error::Type::Unknown,  "call __object_info__.type != closure. but call_closure()!")};

}

//------------------------------------------------------------------------
// code_list = (call_extern (module function) this_node_var& (arg1 arg2 arg3))
Node::OpStatus LispExpr::call_extern(Node& process, const Node::Vector& code_list, size_t start) {
  MYLOGGER(trace_function, "LispExpr::call_extern(Node&process, Node::Vector&list_kv, int start)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("list: ") + Node::_to_str(code_list), SLOG_FUNC_INFO+30);
  MYLOGGER_MSG(trace_function, string("start: ") + to_string(start), SLOG_FUNC_INFO+30);

  auto &modfun = code_list[start];
  auto mod_ref_status= modfun->get_node(0);
  auto fun_ref_status= modfun->get_node(1);
  auto &node_this = code_list[start+1];
  auto &node_arg = code_list[start+2];

  if(!mod_ref_status.first || !fun_ref_status.first)  {
    cerr << "LispExpr::call_extern() error getting module and function: !"  
    << mod_ref_status.second._to_str() 
    + " : "  
    + fun_ref_status.second._to_str() + "\n";
    return {false, fun_ref_status.second.clone()};
  }

  auto node_this_status = eval(process, *node_this);
  if(!node_this_status.first) {
    cerr << "3rd argument aka node this failed to eval!\n";
    return node_this_status;
  }
  auto node_arg_status = eval(process, *node_arg);
  if(!node_arg_status.first) {
    cerr << "call_extern() error, can't eval arg list!\n";
    cerr << "node_arg_status.second " <<  node_arg_status.second->_to_str() << "\n";
     return node_arg_status;
  }

  return call_extern(process, 
    mod_ref_status.second._to_str(), 
    fun_ref_status.second._to_str(), 
    *node_this_status.second, node_arg_status.second->_get_vector_ref());

}


//------------------------------------------------------------------------ call extern
Node::OpStatus LispExpr::call_extern(Node& process, const string&name_mod, const string&name_fun, Node& node_this, const Node::Vector& args) {
  MYLOGGER(trace_function, "LispExpr::call_extern(Node&process, Node& node_this, Node::Vector&args)", __func__, SLOG_FUNC_INFO);

  auto method_path = cc_path_module;
  method_path.push_back(name_mod);
  method_path.push_back(FUNCTION);
  method_path.push_back(name_fun);
  //cout << "method path: " << _to_str_ext(method_path) << "\n";
  auto fun_method_ref_status = get_node(method_path);
  if(!fun_method_ref_status.first) {
    cerr << "method function not found!" <<   name_fun;
    return{false, Node::create_error(Error::Type::FunctionNotFound, "method function not found") };
  }

  Node::Fun method_fun = get<Node::Fun>(fun_method_ref_status.second.value_);
  auto result_status = method_fun(process, node_this, args);
  //cout << "result status : " << result_status << "\n";
  return result_status;

}
