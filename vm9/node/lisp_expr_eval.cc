#include <iostream>
#include "lisp_expr.hh"

#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"


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
      //cout << *element;
      cout << *ee.second;
    }
  } else {
    cout << "builtin_print_n unknown T list\n";

  }
  return {true, Node::create()};
}

//------------------------------------------------------------------------
// symbol lookup 
Node::OpStatusRef LispExpr::arg_lookup(Node&process, const string&name ) {
  MYLOGGER(trace_function, "LispExpr::arg_lookup(Node&process, const string&)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, "name:" + name, SLOG_FUNC_INFO+30);

  /*
  auto frames_ref_status = process[FRAMES];
  if(!frames_ref_status.first) return frames_ref_status;
  auto frame_ref_back_status = frames_ref_status.second.back();
*/
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
  //cout  <<"scope var: " << scope_vars_ref_status << "\n";
  return scope_vars_ref_status.second[name];
}

Node::OpStatusRef LispExpr::immute_lookup(Node&scope, const string&name ) {
  MYLOGGER(trace_function, "LispExpr::immute_lookup(Node&scope, const string&)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, "name:" + name, SLOG_FUNC_INFO+30);

  auto scope_immute_ref_status = scope.get_node(IMMUTE);
  if(!scope_immute_ref_status.first) {
    cerr << "immute[] lookup failed!" <<  scope_immute_ref_status.second._to_str() << "\n";
    return scope_immute_ref_status;
  }
  //cout  <<"scope immute: " << scope_immute_ref_status << "\n";
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
  MYLOGGER_MSG(trace_function, string("code_list: ") + code_node._to_str(), SLOG_FUNC_INFO+30);

  switch(code_node.type_) {
  case Node::Type::Vector: {
    auto const &code_list = get<Node::Vector>(code_node.value_);
    return eval(process, code_list); }

  case Node::Type::Identifier: {
    auto name = get<string>(code_node.value_);
    auto rv_ref_status = symbol_lookup(process, name  );
    if(!rv_ref_status.first) {
      cerr << "Identifier: " << name << " not found!" << rv_ref_status.second._to_str() << "\n";
      return {false, rv_ref_status.second.clone()};
    }
    return {true, rv_ref_status.second.clone()};
  }
  default: return {true, code_node.clone()};
  }

  return {true, code_node.clone()};
  //cout << "eval process: \n"; process.print();
  //cout << "what is going on3: " << Node::_to_str(code_list)<< "\n";


}

Node::OpStatus LispExpr::eval(Node& process, const Node::Vector& code_list) {
  MYLOGGER(trace_function, "LispExpr::eval(Node&process, Node::Vector& code_list)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("code_list: ") + Node::_to_str(code_list), SLOG_FUNC_INFO+30);

  switch(code_list[0]->type_) {
  case Node::Type::LispOp: {

    Lisp::Op op_head = get<Lisp::Op>(code_list[0]->value_);
    switch(op_head){
    case Lisp::Op::print: 
      return builtin_print_n(process, code_list, 1);
    //case Lisp::Op::call: return call(process, code_list);

    case Lisp::Op::vector:  {
      //cout << "lisp::op:  nested vector code!\n";
      auto nested_status = code_list[0]->get_node(0);
      if(!nested_status.first)  {
        cerr << "error getting node!\n";
        return {false, Node::create_error(Error::Type::KeyNotFound, 
          "Nested vector code error" + nested_status.second._to_str())};
      }
      return eval(process, nested_status.second);
    }

    case Lisp::Op::var: {
      //cout << "lisp::op::var !" << Node::_to_str( code_list) <<"\n";
      //cout << "scope_current: " << scope_current(process) << "\n";
      return var_attach(process, code_list, 1);
    }
    case Lisp::Op::assign: {
      //cout << "lisp::op::assign !" << Node::_to_str( code_list) <<"\n";
      return assign_attach(process, code_list, 1);
      break;
    }

    case Lisp::Op::call:  {
      //cout << "lisp::op:call vector code!\n";
      return call(process, code_list, 1);
    }

    default: { 
      cout << "unknown command()!: " + Lisp::_to_str(op_head) + "\n"; }
    }

    break;
  }
  case Node::Type::Identifier: {
//    cerr << "unknown command or function call: type is : " <<  Node::_to_str(code_list[0]->type_) << "\n";
//    cerr << "value is : " <<  code_list[0]->_to_str() << "\n";
//    cerr << "code_list.size : " <<  code_list.size() << "\n";
    auto s = code_list.size() ;

    if(s == 1) {
      //cout << "Identifier var! " << code_list[0]->_to_str() << " need to lookup\n";
      //cout << "symbol lookup " << symbol_lookup(process, code_list[0]->_to_str()) << "\n";
      auto rv_ref_status = symbol_lookup(process, code_list[0]->_to_str());
      if(!rv_ref_status.first) {
        cerr << "symbol lookup failed!\n";
        return { false, rv_ref_status.second.clone() };
      }
      return {true, rv_ref_status.second.clone()};

    } else if(s > 1) {
      // need to push call lisp:op
     //cout << "Identifier call!" << Node::_to_str(code_list) << "\n";
      return call(process, code_list);

    }
    return {false, Node::create(false)};
  }
  case Node::Type::Vector: {
    //cout << "nested vector code: code_list: " << Node::_to_str(code_list) << "\n";
    auto &nested_code_list = get<Node::Vector>(code_list[0]->value_);
    eval(process, nested_code_list);
    for(size_t i=1; i<code_list.size(); i++) {
      auto &code_node = code_list[i];
      eval(process, *code_node);
    }
    return {true, nullptr};
    //for(auto &nested_code : nested_code_list) { }
  }
  default: {
    Node::Vector rlist;
    size_t s=code_list.size();
    rlist.reserve(s);
    for(size_t i=0; i<s; i++) {
      auto &code_node = code_list[i];
      auto evaled_status =  eval(process, *code_node);
      if(!evaled_status.first) return evaled_status;
      rlist.push_back(move(evaled_status.second));
    }
    return  {true, Node::create(move(rlist))};
  }}


  //cout << "outside of swithc code_list: " <<  Node::_to_str( code_list) << "\n";
  
  //if(code_list.size() > 1) { }
  
  //return {true, nullptr};
  return {true, Node::create()};
}

//------------------------------------------------------------------------
// helper function 
// (call (module function) (arg1 arg2 arg3))
// returns a full path of [universe prefix, ..., module function,  code]
vector<string> LispExpr::node_mf_to_path(Node&node_mf,  const vector<string> prefix) {
  MYLOGGER(trace_function, "LispExpr::node_mf_to_path(Node&process, const Node& code_list)", __func__, SLOG_FUNC_INFO);
  //MYLOGGER_MSG(trace_function, string("code_node: ") + code_node._to_str(), SLOG_FUNC_INFO+30);

  vector<string> path = prefix;
  if(node_mf.type_ != Node::Type::Vector)
    return {};
  
  auto m = node_mf[0].second._to_str();
  path.push_back(m);
  path.push_back(FUNCTION);
  auto f = node_mf[1].second._to_str();
  path.push_back(f);
  return path;

}


// (call (module function) (arg1 arg2 arg3))
//       (module function )
// (identifer (x y z ...))
//        (module, function) = identifier
// returns {module, function}
vector<string> LispExpr::extract_mf(Node& process, Node&node_mf) {
  MYLOGGER(trace_function, "LispExpr::extract_mf(Node&process, const Node& node_mf)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("node_mf: ") + node_mf._to_str(), SLOG_FUNC_INFO+30);

  switch(node_mf.type_) {
  case Node::Type::Identifier: {
    Node::Vector list;
    auto mf = node_mf._get_str();
    list.push_back(Node::create(mf));
    //cout << "identifier mf: "  << mf << " \n";
    return extract_mf(process, list); }
  case  Node::Type::Vector:{
    auto &list = node_mf._get_vector_ref();
    return extract_mf(process, list); }
  default: return {}; }
  return {};
}

vector<string> LispExpr::extract_mf(Node& process, Node::Vector &list) {
  MYLOGGER(trace_function, "LispExpr::extract_mf(Node&process, const Node& list)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("list: ") + Node::_to_str(list), SLOG_FUNC_INFO+30);


  
  // call (func)  no module specified
  if(list.size() == 1 ) {
    //cout << "extract mf size 1\n";
    auto f = list[0]->_to_str();

    //.second._to_str();

    //auto frames_status = process.get_node(FRAMES);
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
Node::OpStatus LispExpr::attach_arguments_to_frame(unique_ptr<Node>& frame, const vector<string>& params_path, unique_ptr<Node> arg_list) {
  MYLOGGER(trace_function, "LispExpr::attach_argument_to_frame(...)", __func__, SLOG_FUNC_INFO);

  Node::OpStatusRef params_list_status = get_node(params_path);
  if(!params_list_status.first) {
    return {false, Node::create_error(Error::Type::InvalidOperation,  
      "Can't create arguments list for" + _to_str_ext(params_path) + " \n")};
  }
  size_t s =  params_list_status.second.size_container();

  if(params_list_status.second.size_container() != arg_list->size_container()) {
    return {false, Node::create_error(Error::Type::InvalidOperation,  
      "Can't create arguments list for " + _to_str_ext(params_path) + " size() are different  \n")};
  }

  Node::Map args;
  auto &params_vector = params_list_status.second._get_vector_ref();
  auto &arg_vector = arg_list->_get_vector_ref();
  for(size_t i=0; i <s; i++) {
    auto param_name = params_vector[i]->_to_str();

    args[param_name] = move(arg_vector[i]);
  }
  frame->set(ARGS, Node::create(move(args)));
  return {true, nullptr};

}

//------------------------------------------------------------------------
// (call (module function) (arg1 arg2 arg3))
Node::OpStatus LispExpr::call(Node& process, Node& code_node) {
  MYLOGGER(trace_function, "LispExpr::call(Node&process, const Node& code_node)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("code_node: ") + code_node._to_str(), SLOG_FUNC_INFO+30);

  if(code_node.type_ != Node::Type::Vector)
    return {false, Node::create_error(Error::Type::InvalidOperation,  
      "Can't call module_function != (module function)\n")};

  const auto& code_list =get<Node::Vector>(code_node.value_);
  return call(process, code_list);

} 


// code_list = (call (module function) (arg1 arg2 arg3))
Node::OpStatus LispExpr::call(Node& process, const Node::Vector& code_list, int start) {
  MYLOGGER(trace_function, "LispExpr::call(Node&process, const Node::Vector& code_list, int start)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("code_node: ") + Node::_to_str( code_list) + " start:" + to_string(start), SLOG_FUNC_INFO+30);

/*
  if(code_list.size() != 3 && start !=0) {
    cerr << "code list size! 3\n";
    return {false, Node::create_error(Error::Type::InvalidOperation,  
      "Can't call module_function != (call (module function)(...))\n")};

  }
 */ 
 const auto &mf_node_ptr=  code_list[start];

  auto mf_vector = extract_mf(process, *mf_node_ptr);
  //cout << "mf_vector " << _to_str_ext(mf_vector) << "\n";
  auto func_path = lisp_path_module;

  //return {true, nullptr};
 
  // need to extract module func with just identifier call
  // function path 

  func_path.push_back(mf_vector[0]);
  func_path.push_back(FUNCTION);

  func_path.push_back(mf_vector[1]);
  auto call_path = func_path;
  auto params_path = func_path;
  call_path.push_back(CODE);
  params_path.push_back(_PARAMS);
  

  auto frame = frame_create();
  frame->set(CURRENT_MODULE, mf_vector[0]);
  frame->set(CURRENT_FUNCTION, mf_vector[1]);

  // argument set up
  const auto &argv_node_ptr=  code_list[start+1];
  //cout << "*argv_node_ptr : " << *argv_node_ptr<< "\n";
  auto argv_list  = eval(process, *argv_node_ptr);
  if(!argv_list.first) return argv_list;
  //cout << "argv_list status: " << argv_list << "\n";
  //frame->set(LVAR, move(argv_list.second));
  auto aatf_status =  attach_arguments_to_frame(frame, params_path, move(argv_list.second));
  if(!aatf_status.first) return aatf_status;



  //
  frame_push(process, move(frame));
  auto scope = scope_create();
  auto scope_status =  scope_push(process, move(scope));
  if(!scope_status.first) {
    cerr << "scope status is false: scope push failed " << *scope_status.second << "\n";
    
  }




  Node::OpStatusRef code_list_status = get_node(call_path);

  if(!code_list_status.first)  {
    cerr << _to_str_ext(call_path) << " path not found!\n";
    return  {false, Node::create_error(
      Error::Type::KeyNotFound, 
      "LispExpr::call(Node& process, Node::Vector& code_list) path node not found: " + _to_str_ext(call_path))};
  }

  return eval(process, code_list_status.second);


  //vector<string> code_path_list =  LispExpr::lisp_path_module;
  //auto call_path = move(node_mf_to_path(mf.second, lisp_path_module));

  /*
  code_path_list.insert(code_path_list.end(), mf_list.begin(), mf_list.end());
  */
}
