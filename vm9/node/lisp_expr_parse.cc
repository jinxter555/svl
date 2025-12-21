#include <iostream>
#include "lisp_expr.hh"

#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"


//------------------------------------------------------------------------ build and parse interpreter 

// tokens: double linked list of tokens
Node::OpStatus LispExpr::parse(Node& tokens) {
  MYLOGGER(trace_function, "LispExpr::parse(Node&tokens)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("tokens: ") + tokens._to_str(), SLOG_FUNC_INFO+30);
  //cout << "parse tokens: " <<  tokens << "\n\n";

  if(tokens.type_ != Node::Type::List) 
    return {true, tokens.clone()};

  //cout << "tokens: " <<  tokens<< "\n";
  auto head_status = tokens.pop_front(); 
  //cout << "parse(token): head_status: " <<  head_status << "\n";
  //cout << "head_status.second value: " <<  *head_status.second << "\n";
  //cout << "tokens: " <<  tokens<< "\n";


  if(!head_status.first) {
    cerr << "head_status error from front(): " <<  head_status << "\n";
    return head_status;
  }
  // have to check type_
  auto &list = get<Node::List>(tokens.value_);


  if(head_status.second->type_ == Node::Type::LispOp) {

    Lisp::Op op_head = get<Lisp::Op>(head_status.second->value_);
    MYLOGGER_MSG(trace_function, string("LispOp: ") + Lisp::_to_str(op_head), SLOG_FUNC_INFO+30);

    switch(op_head) {
    case Lisp::Op::print:  { //cout << "print: " <<  tokens << "\n";
      return {true, Node::create()};}
    case Lisp::Op::deque:  { 
      return build_parsed_deque(list); }
    case Lisp::Op::list:  { //cout << "parsing list: " <<  tokens << "\n";
      return build_parsed_list(list); }
    case Lisp::Op::vector:  { //cout << "parsing vector: " <<  tokens << "\n";
      return build_parsed_vector(list);}
    case Lisp::Op::def: {// cout << "case parse def\n";
      return build_parsed_def(list); }
    case Lisp::Op::defun: {
      return build_parsed_fun(list); }
    case Lisp::Op::module: {
      return build_parsed_module(list); }
    case Lisp::Op::root: { return build_parsed_root(list); }

    default: {
      cerr << "Parser build interpreter: Lisp Op not permitted  : " <<  Lisp::_to_str(op_head) << ", " << tokens << "\n";
      return {false, Node::create()}; 
    }}

    //cout << "lisp op head: " << Lisp::_to_str(op_head) << "\n";
  } else  {  // identifiers starts as (head ...)
    // convert it to a vector and return it
    // if(head_status.second->type_ == Node::Type::Identifier) { cout << "head_status "  << *head_status.second << " is identifier!\n"; }

    list.push_front(move(head_status.second));
    return build_parsed_vector( list);

  }

  return {true, Node::create()};
}

//-------------------------------- parse fun
// (fun_name (param_list) (description) (code list))
// return map as function
//
Node::OpStatus LispExpr::build_parsed_fun(Node::List& list) {
  MYLOGGER(trace_function, "LispExpr::build_parsed_fun(Node::List& list)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("list: ") + Node::_to_str(list), SLOG_FUNC_INFO+30);

  Node::Map map_n={}, map={}; 
  string name = get<string>(list.front()->value_); list.pop_front(); // function name

  // set func
  {// turn params List to params Vector for speed performance
  auto status=  build_parsed_vector(*list.front()); 
  if(!status.first) return status;
  map["params"] = move(status.second); list.pop_front();
  }

  map["description"] = move(list.front()); list.pop_front();
  
  {// turn code List to code Vector for speed performance
  auto status=  build_parsed_vector(*list.front()); 
  if(!status.first) return status;
  map["code"] = move(status.second); list.pop_front();
  //cout << "code: list after pop!" << Node::_to_str(list) << "\n";
  }

  map_n[name]  = Node::create(move(map));

  return {true, Node::create(move(map_n))};

}
//-------------------------------- parse module
// (module Main (defun main ) (defun f1 ) (defun f2))
Node::OpStatus LispExpr::build_parsed_module(Node::List& list) {
  MYLOGGER(trace_function, "LispExpr::build_parsed_module(Node::List& list)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("list: ") + Node::_to_str(list), SLOG_FUNC_INFO+30);

  vector<string> keys={};

  auto node_functions=make_unique<Node>(Node::Type::Map);
  auto node_module=make_unique<Node>(Node::Type::Map);

  string name = get<string>(list.front()->value_); list.pop_front(); // module name

  keys.push_back(name);
  keys.push_back("function");

  for(auto& ele: list) {  
    auto status_fun = parse(*ele); // parse (defun ...)
    if(!status_fun.first) return status_fun;
    node_functions->merge(move(status_fun.second));
  }
  node_module->set(keys, move(node_functions), true);

  return {true, move(node_module)};

 }

//-------------------------------- parse root
// (root :set (path,..) value )
// (root :get () )
Node::OpStatus LispExpr::build_parsed_root(Node::List& list) {
  MYLOGGER(trace_function, "LispExpr::build_parsed_root(Node::List& list)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("list: ") + Node::_to_str(list), SLOG_FUNC_INFO+30);

  try {
    auto root_sym_op = get<Node::Integer>(list.front()->value_); list.pop_front(); // root op symbol 
    if(root_sym_op == sym_set) {
      auto path_list = move(get<Node::List>(list.front()->value_));  list.pop_front();
      auto value = move(list.front());  list.pop_front();

      auto path_vec_str = Node::list_to_vector_string(path_list);
      return set(path_vec_str, move(value), true);
      //return {true, Node::create(true)};

    } else if(root_sym_op== sym_get){
      auto path_list = move(get<Node::List>(list.front()->value_));  list.pop_front();
      auto path_vec_str = Node::list_to_vector_string(path_list);
      auto node_ref = get_node(path_vec_str);
      if(node_ref.first) return {true, node_ref.second.clone()};
    }
  } catch(...) { 
    return {false, Node::create_error(Node::Error::Type::InvalidOperation, 
        "error: parsed root get symbol") };
  }
  return {true, Node::create()};

}

//------------------------------------------------------------------------
//Node::OpStatus LispExpr::builtin_add(Node &env, const Node::List& list, size_t start) {
template <typename T>
Node::OpStatus LispExpr::builtin_add(Node& env, const T& list) {
  unique_ptr<Node> result = make_unique<Node>(0);
  if constexpr (is_same_v<T, Node::Vector> || is_same_v<T, Node::DeQue>||  is_same_v<T, Node::List>) {
    for(auto& element : list) { 
      if(element.first) {
        auto& ev = element.second->eval(env);
        if(ev.first) *result = *result + *ev.second;
      }
    }
    return {false, move(result)};
  } else {
    return {false, Node::create()};
  }
}


//-------------------------------- parse def
Node::OpStatus LispExpr::build_parsed_def(Node::List& list) {
  MYLOGGER(trace_function, "LispExpr::build_parsed_def(Node::List& list)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("list: ") + Node::_to_str(list), SLOG_FUNC_INFO+30);

  auto def_type_ptr = move(list.front()); //cout << "head_status: " <<  head_status << "\n";
  list.pop_front();
  auto def_type = get<Node::Integer>(def_type_ptr->value_);

  if(def_type ==  sym_module) {
    cout << "def module\n";

  } else if(def_type == sym_fun) {
    cout << "def fun\n";

  }
  return {true, Node::create(1)};
}

//------------------------------------------------------------------------
Node::OpStatus LispExpr::attach_module(unique_ptr<Node> module) {
  MYLOGGER(trace_function, "LispExpr::attach_module(unique_ptr<Node>module)", __func__, SLOG_FUNC_INFO);
  auto mod_loc = get_branch(lisp_path_module);
  return mod_loc->merge(move(module));
  //cout << "mod_loc: " << *mod_loc << "\n\n";
  //return {false, Node::create(true)};
}


//------------------------------------------------------------------------ build parse
// asssumes Node.value_ contains a Node::List of nodes

//-------------------------------- vector

Node::OpStatus LispExpr::build_parsed_vector(Node& node) {
  MYLOGGER(trace_function, "LispExpr::build_parsed_vector(Node&)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("node: ") + node._to_str(), SLOG_FUNC_INFO+30);
  if(node.type_ != Node::Type::List) {
  }
  auto &list = get<Node::List>(node.value_);
  return build_parsed_vector(list);
}

Node::OpStatus LispExpr::build_parsed_vector(Node::List& list) {
  MYLOGGER(trace_function, "LispExpr::build_parsed_vector(Node::List&list)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("list: ") + Node::_to_str(list), SLOG_FUNC_INFO+30);

  Node::Vector vl;
  vl.reserve(list.size());
  for(auto& ele: list) {
    if(ele->type_ == Node::Type::List) { // nested parsing
      MYLOGGER_MSG(trace_function, string("build nested list: ") + ele->_to_str(), SLOG_FUNC_INFO+30);
      auto status_parsed = parse(*ele);
      if(!status_parsed.first) return status_parsed;
      MYLOGGER_MSG(trace_function, string("returned list type: ") + Node::_to_str(status_parsed.second->type_), SLOG_FUNC_INFO+30);
      vl.push_back(move(status_parsed.second));
    } else 
    //vl.push_back(move(ele->clone()));
    vl.push_back(move(ele));
  }
  return {true, Node::create(move(vl))};
}

//-------------------------------- list
Node::OpStatus LispExpr::build_parsed_list(Node& node) {
  MYLOGGER(trace_function, "LispExpr::build_parsed_list(Node& node)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("node: ") + node._to_str(), SLOG_FUNC_INFO+30);
  auto &list = get<Node::List>(node.value_);
  return build_parsed_list(list);
}

Node::OpStatus LispExpr::build_parsed_list(Node::List& list) {
  MYLOGGER(trace_function, "LispExpr::build_parsed_list(Node::List&list)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("list: ") + Node::_to_str(list), SLOG_FUNC_INFO+30);
  Node::List dl;
  for(auto& ele: list) {
    if(ele->type_ == Node::Type::List) { // nested parsing
      MYLOGGER_MSG(trace_function, string("build nested list: ") + ele->_to_str(), SLOG_FUNC_INFO+30);
      auto status_parsed = parse(*ele);
      if(!status_parsed.first) return status_parsed;
      MYLOGGER_MSG(trace_function, string("returned list type: ") + Node::_to_str(status_parsed.second->type_), SLOG_FUNC_INFO+30);
      dl.push_back(move(status_parsed.second));
    } else {
      //dl.push_back(move(ele->clone()));
      dl.push_back(move(ele));
    }
  }
  return {true, Node::create(move(dl))};

}

//-------------------------------- deque

Node::OpStatus LispExpr::build_parsed_deque(Node::List& list) {
  Node::DeQue dl;
  for(auto& e : list) dl.push_back(e->clone());
  return {true, Node::create(move(dl))};
}

Node::OpStatus LispExpr::build_parsed_deque(Node& node) {
  MYLOGGER(trace_function, "LispExpr::build_parsed_deque(Node& node)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("node: ") + node._to_str(), SLOG_FUNC_INFO+30);
  auto &list = get<Node::List>(node.value_);
  return build_parsed_deque(list);
  //return {true, Node::clone(node)};
}

//-------------------------------- map
Node::OpStatus LispExpr::build_parsed_map(Node::List& list) {
  Node::Map map;
  for(auto& e : list) {

  }
  return {true, Node::create(move(map))};
}
//Node::OpStatus LispExpr::build_parsed_map(Node& node) { }

