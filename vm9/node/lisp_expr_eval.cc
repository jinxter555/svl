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
Node::OpStatusRef LispExpr::symbol_lookup(Node&process, const string&name ) {
  MYLOGGER(trace_function, "LispExpr::symbol_lookup(Node&process, const string&)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, "name:" + name, SLOG_FUNC_INFO+30);
  auto frames_ref_status = process[FRAMES];
  if(!frames_ref_status.first) return frames_ref_status;
  auto frame_ref_back_status = frames_ref_status.second.back();
  if(!frame_ref_back_status.first) return frame_ref_back_status;
  auto arg_ref_status = frame_ref_back_status.second[ARGS];
  if(!arg_ref_status.first) return arg_ref_status;
  return arg_ref_status.second[name];
}
//------------------------------------------------------------------------
// eval node 
Node::OpStatus LispExpr::eval(Node& process, const Node& code_node) {
  MYLOGGER(trace_function, "LispExpr::eval(Node&process, Node&code_node)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("code_list: ") + code_node._to_str(), SLOG_FUNC_INFO+30);

  if(code_node.type_ != Node::Type::Vector) {
    /*
    cerr << "Can't eval unknown code vector type: " << Node::_to_str(code_node.type_) << "!\n";
    return {false, Node::create_error(Node::Error::Type::InvalidOperation,  
      "Can't eval unknown code vector type!\n")};
    */
   return {true, code_node.clone()};
  }
  //cout << "eval process: \n"; process.print();


  auto const &code_list = get<Node::Vector>(code_node.value_);
  return eval(process, code_list);

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
        return {false, Node::create_error(Node::Error::Type::KeyNotFound, 
          "Nested vector code error" + nested_status.second._to_str())};
      }
      return eval(process, nested_status.second);
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
      cout << "Identifier var! " << code_list[0]->_to_str() << " need to lookup\n";
      cout << "symbol lookup " << symbol_lookup(process, code_list[0]->_to_str()) << "\n";

    } else if(s > 1) {
      // need to push call lisp:op
 //     cout << "Identifier call!" << Node::_to_str(code_list) << "\n";
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
// (call (function) (arg1 arg2 arg3))  --- use process frame to get module name

// returns {module, function}
vector<string> LispExpr::node_to_mf(Node& process, Node&node_mf) {
  MYLOGGER(trace_function, "LispExpr::call(Node&process, const Node& code_list)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("node_mf: ") + node_mf._to_str(), SLOG_FUNC_INFO+30);


  if(node_mf.type_ != Node::Type::Vector)
    return {};
  
  // call (func)  no module specified
  if(node_mf.size_container() == 1 ) {
    auto f = node_mf[0].second._to_str();

    //.second._to_str();

    //auto frames_status = process.get_node(FRAMES);
    auto frames_status = process[FRAMES];
    if(!frames_status.first) return {};
    auto last_frame_status = frames_status.second.back();
    if(!last_frame_status.first) return {};

    auto current_module_status = last_frame_status.second[CURRENT_MODULE];
    if(!current_module_status.first) return {};
    auto m  = current_module_status.second._to_str();
    return {m, f};

  } else if(node_mf.size_container() == 2 ) {
    auto m = node_mf[0].second._to_str();
    auto f = node_mf[1].second._to_str();
    return {m, f};
  }
  return {};
}

//------------------------------------------------------------------------
Node::OpStatus LispExpr::attach_arguments_to_frame(unique_ptr<Node>& frame, const vector<string>& params_path, unique_ptr<Node> arg_list) {
  MYLOGGER(trace_function, "LispExpr::attach_argument_to_frame(...)", __func__, SLOG_FUNC_INFO);

  Node::OpStatusRef params_list_status = get_node(params_path);
  if(!params_list_status.first) {
    return {false, Node::create_error(Node::Error::Type::InvalidOperation,  
      "Can't create arguments list for" + _to_str_ext(params_path) + " \n")};
  }
  size_t s =  params_list_status.second.size_container();

  if(params_list_status.second.size_container() != arg_list->size_container()) {
    return {false, Node::create_error(Node::Error::Type::InvalidOperation,  
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
// code_list = (call (module function) (arg1 arg2 arg3))
Node::OpStatus LispExpr::call(Node& process, const Node::Vector& code_list, int start) {
  MYLOGGER(trace_function, "LispExpr::call(Node&process, const Node& code_list)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("code_node: ") + Node::_to_str( code_list), SLOG_FUNC_INFO+30);

  if(code_list.size() != 3)
    return {false, Node::create_error(Node::Error::Type::InvalidOperation,  
      "Can't call module_function != (call (module function)(...))\n")};

  const auto &mf_node_ptr=  code_list[start];

  auto mf_vector = node_to_mf(process, *mf_node_ptr);
  auto func_path = lisp_path_module;
 
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

  Node::OpStatusRef code_list_status = get_node(call_path);

  if(!code_list_status.first)  {
    cerr << _to_str_ext(call_path) << " path not found!\n";
    return  {false, Node::create_error(
      Node::Error::Type::KeyNotFound, 
      "LispExpr::call(Node& process, Node::Vector& code_list) path node not found: " + _to_str_ext(call_path))};
  }

  return eval(process, code_list_status.second);


  //vector<string> code_path_list =  LispExpr::lisp_path_module;
  //auto call_path = move(node_mf_to_path(mf.second, lisp_path_module));

  /*
  code_path_list.insert(code_path_list.end(), mf_list.begin(), mf_list.end());
  */
}

// (call (module function) (arg1 arg2 arg3))
Node::OpStatus LispExpr::call(Node& process, Node& code_node) {
  MYLOGGER(trace_function, "LispExpr::call(Node&process, const Node& code_node)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("code_node: ") + code_node._to_str(), SLOG_FUNC_INFO+30);

  if(code_node.type_ != Node::Type::Vector)
    return {false, Node::create_error(Node::Error::Type::InvalidOperation,  
      "Can't call module_function != (module function)\n")};

  const auto& code_list =get<Node::Vector>(code_node.value_);
  return call(process, code_list);

} 