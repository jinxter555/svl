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
  if(tokens.empty_container())
    return {true, Node::create(Node::Type::Vector) };

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
    //case Lisp::Op::print:  { return {true, Node::create(Lisp::Op::print)};}
    case Lisp::Op::deque:  { return build_parsed_deque(list); }
    case Lisp::Op::list:  { 
      return build_parsed_list(list); }
    case Lisp::Op::vector:  { //cout << "parsing vector: " <<  tokens << "\n";
      return build_parsed_vector(list);}
    case Lisp::Op::def: {// cout << "case parse def\n";
      return build_parsed_def(list); }
    case Lisp::Op::defun: {
      return build_parsed_fun(list); }
    case Lisp::Op::module: {
      return build_parsed_module(list); }
    case Lisp::Op::class_: {
      cout << "class build!\n";
      //return build_parsed_module(list); 
      break;
    }
    case Lisp::Op::root: { return build_parsed_root(list); }
    default: {}
    }
  } 
  // convert it to a vector and return it
  // if(head_status.second->type_ == Node::Type::Identifier) 

  list.push_front(move(head_status.second));
  return build_parsed_vector(list);

}

//-------------------------------- parse fun
// (fun_name (param_list) (description) (code list))
// return map as function
//
Node::OpStatus LispExpr::build_parsed_fun(Node::List& list) {
  MYLOGGER(trace_function, "LispExpr::build_parsed_fun(Node::List& list)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("list: ") + Node::_to_str(list), SLOG_FUNC_INFO+30);

  if(list.size()<3) return {false, Node::create_error(Error::Type::Parse, "defun requires atleast 3 parameters! " + Node::_to_str(list))};
  if(list.size()>4) return {false, Node::create_error(Error::Type::Parse, "defun greater than 4 parameters! " + Node::_to_str(list))};

  string name;
  Node::Map map_n={}, map={}; 
  try { name = get<string>(list.front()->value_); 
  } catch(...) { 
    return {false, Node::create_error(Error::Type::Parse, "(defun) name string error.")};
  }
  
  list.pop_front(); // function name

  // set func
  {// turn params List to params Vector for speed performance
  auto status =  build_parsed_vector(*list.front()); 
  if(!status.first) return status;
  map[_PARAMS] = move(status.second); list.pop_front();
  }

  //cout << "fun size:" <<  list.size() << "\n";
  if(list.size() == 2) {map[DESC] = move(list.front()); list.pop_front();}
  else map[DESC] = Node::create();
  
  {// turn code List to code Vector for speed performance
  auto status=  build_parsed_vector(*list.front()); 
  if(!status.first) return status;
  map[CODE] = move(status.second); list.pop_front();
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
    return {false, Node::create_error(Error::Type::InvalidOperation, 
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
// attach module to 'Lisp' Language tree
//
Node::OpStatus LispExpr::attach_module(unique_ptr<Node> module) {
  MYLOGGER(trace_function, "LispExpr::attach_module(unique_ptr<Node>module)", __func__, SLOG_FUNC_INFO);
  auto mod_loc = get_branch(lisp_path_module);
  return mod_loc->merge(move(module));
  //cout << "mod_loc: " << *mod_loc << "\n\n";
  //return {false, Node::create(true)};
}
//--------------------------------  attach c++ static function
Node::OpStatus LispExpr::attach_cc_fun(const string&name, const Node::Fun& f) {
  MYLOGGER(trace_function, "LispExpr::attach_cc_fun(const string&name, const Node::Fun&f)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("name: ") + name, SLOG_FUNC_INFO+30);

  auto mod_loc = get_branch(cc_path_module);
  if(mod_loc==nullptr) {
    cerr << "attach_cc_fun(): mod_loc is nullptr!\n";
    return {false, Node::create_error(Error::Type::Unknown, "attach_cc_fun(): mod loc is nullptr!")};
  }

  Node::Map nm = {};
  nm[name] = Node::clone(f);
  return mod_loc->merge(Node::create(move(nm)));
}
Node::OpStatus LispExpr::attach_cc_fun(const string&name_mod, const string&name_fun, const Node::Fun& f) {
  MYLOGGER(trace_function, "LispExpr::attach_cc_fun(const string&name_mod, const string&name_fun, const Node::Fun&f)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, "name_mod: " + name_mod + ", name_fun: " + name_fun, SLOG_FUNC_INFO+30);
  auto location  = cc_path_module;
  location.push_back(name_mod);
  auto mod_loc_ref = get_node(location );
  if(!mod_loc_ref.first) { // module location does not exist
    //cerr << "CC_path_module returned false! !" << mod_loc_ref.second._to_str() << ", create new module\n";
    //return {false, mod_loc_ref.second.clone()};
    set_branch(location , Node::create(Node::Type::Map));
  }
  location.push_back(FUNCTION); // add 'function' sub branch as well
  auto modfun_loc = get_branch(location );

  if(modfun_loc==nullptr) 
    set_branch(location , Node::create(Node::Type::Map));

  modfun_loc = get_branch(location );
  Node::Map nm = {};
  nm[name_fun] = Node::clone(f);
  return modfun_loc->merge(Node::create(move(nm)));


}


//------------------------------------------------------------------------ build parse
// assumes Node.value_ contains a Node::List of nodes

//-------------------------------- vector

Node::OpStatus LispExpr::build_parsed_vector(Node& node) {
  MYLOGGER(trace_function, "LispExpr::build_parsed_vector(Node&)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("node: ") + node._to_str(), SLOG_FUNC_INFO+30);
  if(node.type_ != Node::Type::List) {
    cerr << "build_parsed_vector() error with :"<<  node << ",type: " << Node::_to_str(node.type_) << "\n";
    return {false, Node::create_error(Error::Type::Parse, "build_parsed_vector()! not vector type:Can't build vector!")};
  }

  try {
  auto &list = get<Node::List>(node.value_);
  return build_parsed_vector(list);
  } catch(...) { 
    cerr << "build_parsed_vector() error with list:" <<  node << "\n";
  }
  return {false, Node::create_error(Error::Type::Parse, "build_parsed_vector()! not vector type:Can't build vector!")};

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
  //for(auto& e : list) { }
  return {true, Node::create(move(map))};
}
//Node::OpStatus LispExpr::build_parsed_map(Node& node) { }


//------------------------------------------------------------------------ Lisp Expr Keywords
void LispExpr::set_keywords() {
  auto map_ = make_unique<Node>(Node::Type::Map);
  map_->set("kernel", Op::kernel);
  map_->set("system", Op::system);
  map_->set("root",   Op::root);
  map_->set("new",   Op::new_);
  map_->set("delete",   Op::delete_);
  map_->set("class",   Op::class_);
  map_->set("clone",   Op::clone);
  map_->set("error",Op::error);
  map_->set("noop", Op::noop);
  map_->set("identifier", Op::identifier);
  map_->set("scalar", Op::scalar);
  map_->set("literal", Op::literal);
  map_->set("list", Op::list);
  map_->set("vector", Op::vector);
  map_->set("deque", Op::deque);
  map_->set("map", Op::map);
  map_->set("var", Op::var);
  map_->set("assign", Op::assign);
  map_->set("car", Op::car);
  map_->set("cdr", Op::cdr);
  map_->set("add", Op::add);
  map_->set("sub", Op::sub); 
  map_->set("mul", Op::mul);
  map_->set("div", Op::div);
  map_->set("mod", Op::mod); 
  map_->set("def", Op::def); 
  map_->set("call", Op::call);
  map_->set("funcall", Op::funcall);
  map_->set("call_extern", Op::call_extern);
  map_->set("send", Op::send);
  map_->set("ret", Op::ret);
  map_->set("cond", Op::cond);
  map_->set("loop", Op::loop);
  map_->set("for", Op::for_);
  map_->set("do", Op::do_);
  map_->set("print",Op::print);
  map_->set("module",Op::module);
  map_->set("defun", Op::defun);
  map_->set("defmacro", Op::defmacro);
  map_->set("alias", Op::alias);
  map_->set("lambda", Op::lambda);

  map_->set("+", Op::add);
  map_->set("-", Op::sub);
  map_->set("*", Op::mul);
  map_->set("/", Op::div);
  map_->set("%", Op::mod);
  set_branch(lisp_path_keyword, move(map_));
}

Lisp::Op LispExpr::keyword_to_op(const string &input) {
  MYLOGGER(trace_function, "LispExpr::keyword_to_op()", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("lookup input: ") + input, SLOG_FUNC_INFO+30);

  auto map_ = get_branch(lisp_path_keyword);
  //auto &map_ = Lisp::map_;

  if(map_ == nullptr || map_->type_ != Node::Type::Map) {
    cout << "lisp keyworld map_ type != map\n";
    return Lisp::Op::error;
  }
  auto status = (*map_)[input];
  if(!status.first) {
    MYLOGGER_MSG(trace_function, "Lisp keyword: " + input + " not found , return as scalar", SLOG_FUNC_INFO+30);
    return Lisp::Op::scalar;
  }
  auto op = get<Lisp::Op>(status.second.value_);
  return op;
}