#include <iostream>
#include "lisp_expr.hh"

#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"


//------------------------------------------------------------------------ build and parse interpreter 

// tokens: double linked list of tokens
Node::OpStatus LispExpr::parse_build(Node& tokens) {
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
    case Lisp::Op::use:  { return use_at_parse_build(list); }
    case Lisp::Op::deque:  { return build_parsed_deque(list); }
    case Lisp::Op::list:  { return build_parsed_list(list); }
    case Lisp::Op::vector:  { return build_parsed_vector(list);}
    case Lisp::Op::def: { return build_parsed_def(list); }
    case Lisp::Op::if_: { return build_parsed_if(list); }
    case Lisp::Op::defmacro: { return build_parsed_macro(list); }
    case Lisp::Op::module_: { return build_parsed_module(list); }
    case Lisp::Op::class_: { return build_parsed_class(list); }
 // case Lisp::Op::root: { return build_parsed_root(list); }
 // case Lisp::Op::defun: { return build_parsed_fun(list); }
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
// return -> fun_name -> {code,params,object_info}
Node::OpStatus LispExpr::build_parsed_fun(Node::List& list) {
  MYLOGGER(trace_function, "LispExpr::build_parsed_fun(Node::List& list)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("list: ") + Node::_to_str(list), SLOG_FUNC_INFO+30);

  if(list.size()<3) return {false, Node::create_error(Error::Type::Parse, "defun requires atleast 3 parameters! " + Node::_to_str(list))};
  if(list.size()>4) return {false, Node::create_error(Error::Type::Parse, "defun greater than 4 parameters! " + Node::_to_str(list))};

  string name;

  Node::Map fun={}; 
  name = list.front()->_to_str();
  //try { name = get<string>(list.front()->value_); } catch(...) { return {false, Node::create_error(Error::Type::Parse, "(defun) name string error.")}; }
  
  list.pop_front(); // function name

  // set func
  {// turn params List to params Vector for speed performance
  auto status =  build_parsed_vector(*list.front()); 
  if(!status.first) return status;
  fun[_PARAMS] = move(status.second); list.pop_front();
  }

  //cout << "fun size:" <<  list.size() << "\n";
  if(list.size() == 2) {fun[DESC] = move(list.front()); list.pop_front();}
  else fun[DESC] = Node::create();
  
  {// turn code List to code Vector for speed performance
  auto status=  build_parsed_vector(*list.front()); 
  if(!status.first) return status;
  fun[CODE] = move(status.second); list.pop_front();
  //cout << "code: list after pop!" << Node::_to_str(list) << "\n";
  }

  auto obj_info = make_unique<Node>(Node::Type::Map);
  obj_info->set(TYPE,  Node::create(Lisp::Type::defun));

  fun[OBJ_INFO] = move(obj_info);
  fun["name"] = Node::create(name);

  return {true, Node::create(move(fun))};

}


//-------------------------------- parse fun
// (def name (param_list) (code list))
// def fun (x,y) ... end.def
// return map as function
// return -> fun_name -> {code,params,object_info}
Node::OpStatus LispExpr::build_parsed_def(Node::List& list) {
  MYLOGGER(trace_function, "LispExpr::build_parsed_def(Node::List& list)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("list: ") + Node::_to_str(list), SLOG_FUNC_INFO+30);

  string name;
  Node::Map fun={}; 
  if(list.empty()) return {false, Node::create_error(Error::Type::Parse, "def empty list to get fun name.")};

  name = list.front()->_to_str();
  //try { name = get<string>(list.front()->value_); } catch(...) { return {false, Node::create_error(Error::Type::Parse, "(defun) name string error.")}; }
  
  list.pop_front(); // function name

  // set func
  {// turn params List to params Vector for speed performance
  auto status =  build_parsed_vector(*list.front()); 
  if(!status.first) return status;
  fun[_PARAMS] = move(status.second); list.pop_front();
  }

  {// turn code List to code Vector for speed performance
  //auto status=  build_parsed_vector(*list.front()); 
  auto status=  build_parsed_vector(list); 
  if(!status.first) return status;
  fun[CODE] = move(status.second); 
  if(!list.empty()) list.pop_front();
  //cout << "code: list after pop!" << Node::_to_str(list) << "\n";
  }

  auto obj_info = make_unique<Node>(Node::Type::Map);
  obj_info->set(TYPE,  Node::create(Lisp::Type::def));

  fun[OBJ_INFO] = move(obj_info);
  fun[NAME] = Node::create(name);
  fun[NAMESPACE] = Node::create(build_namespace);

  return {true, Node::create(move(fun))};
}

//-------------------------------- parse macro
// (defmacro (param_list) (code list))
// def fun (x,y) ... end.def
// return map as function
// return -> fun_name -> {code,params,object_info}

Node::OpStatus LispExpr::build_parsed_macro(Node::List& cclist) {
  MYLOGGER(trace_function, "LispExpr::build_parsed_macro(Node::List& cclist)", __func__, SLOG_FUNC_INFO)
  MYLOGGER_MSG(trace_function, "list: " + Node::_to_str(cclist), SLOG_FUNC_INFO+30)

  string name;

  Node::Map macro={}; 
  if(cclist.empty()) return {false, Node::create_error(Error::Type::Parse, "defmacro empty cclist to get macro name.")};
  name = cclist.front()->_to_str();

  cclist.pop_front(); // function name

  {// Parameter block
  auto status =  build_parsed_vector(*cclist.front()); 
  if(!status.first) return status;
  macro[_PARAMS] = move(status.second); cclist.pop_front();
  }

  {
  auto status=  build_parsed_vector(cclist); 
  if(!status.first) return status;
  macro[CODE] = move(status.second); 
  if(!cclist.empty()) cclist.pop_front();
  }

  auto obj_info = make_unique<Node>(Node::Type::Map);
  obj_info->set(TYPE,  Node::create(Lisp::Type::defmacro));
  macro[OBJ_INFO] = move(obj_info);
  macro[NAME] = Node::create(name);
  macro[NAMESPACE] = Node::create(build_namespace);
  return {true, Node::create(move(macro))};
}




//-------------------------------- parse module
// (module Main (defun main ) (defun f1 ) (defun f2) (class end.class)) 
Node::OpStatus LispExpr::build_parsed_module(Node::List& list) {
  MYLOGGER(trace_function, "LispExpr::build_parsed_module(Node::List& list)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("list: ") + Node::_to_str(list), SLOG_FUNC_INFO+30);

  vector<string> keys={};

  auto module_functions=make_unique<Node>(Node::Type::Map);
  auto module_classes=make_unique<Node>(Node::Type::Map);
  auto module_macros=make_unique<Node>(Node::Type::Map);
  auto module_node=make_unique<Node>(Node::Type::Map);

  auto obj_info = make_unique<Node>(Node::Type::Map);
  obj_info->set(TYPE,  Node::create(Lisp::Type::module_));

  string module_name = get<string>(list.front()->value_); list.pop_front(); // module name

  for(auto& ele: list) {  
    auto status = parse_build(*ele); // parse (defun ...) (class ...)
    if(!status.first) return status;
    status.second->set(MODULE_PTR, module_node.get()); // causes recursive segault when print recursive// get raw pointer from 

    switch(Lisp::type(*status.second)){
    case Lisp::Type::def: {
      auto fun_name = (*status.second)["name"].second._to_str();
      //status.second->set(MODULE_PTR, module_node.get()); // causes recursive segault when print recursive// get raw pointer from 
      module_functions->set(fun_name, move(status.second));
      continue;
    }
    case Lisp::Type::defmacro: {
      auto mac_name = (*status.second)["name"].second._to_str();
      //status.second->set(MODULE_PTR, module_node.get()); // causes recursive segault when print recursive// get raw pointer from 
      module_macros->set(mac_name, move(status.second));
      continue;
    }

    case Lisp::Type::class_: {
      auto class_name = (*status.second)["name"].second._to_str();
      //cout << "class name: " << class_name << "\n";
      module_classes->set(class_name, move(status.second));
      break;
    }
    default: { }}
  }
  module_node->set(FUNCTION, move(module_functions));
  module_node->set(MACRO, move(module_macros));
  module_node->set(_CLASS, move(module_classes));
  module_node->set(OBJ_INFO, move(obj_info));
  module_node->set(NAME, module_name);
  module_node->set(NAMESPACE,  Node::create(build_namespace));

  return {true, move(module_node)};
}

//-------------------------------- attach 'this'  var to class method
Node::OpStatus LispExpr::attach_this_to_arguments(Node::Vector& list){
   list.insert(list.begin(), Node::create("this", Node::Type::Identifier)); 
   return {true, nullptr};
}

//-------------------------------- parse class
// (class Car (defun start) (defun drive) (defun f2) ) 
Node::OpStatus LispExpr::build_parsed_class(Node::List& list) {
  MYLOGGER(trace_function, "LispExpr::build_parsed_class(Node::List& list)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("list: ") + Node::_to_str(list), SLOG_FUNC_INFO+30);

  vector<string> keys={};

  auto class_functions=make_unique<Node>(Node::Type::Map);
  auto class_node=make_unique<Node>(Node::Type::Map);

  auto obj_info = make_unique<Node>(Node::Type::Map);
  obj_info->set(TYPE,  Node::create(Lisp::Type::class_));

  string class_name = get<string>(list.front()->value_); list.pop_front(); // class name

  for(auto& ele: list) {  
    auto status = parse_build(*ele); // parse (defun ...) (class ...)

    if(!status.first) return status;
    status.second->set(CLASS_PTR, class_node.get()); // recursive will segfault, check to_str and print recursive

    switch(Lisp::type(*status.second)){
    case Lisp::Type::def: {
      auto fun_name = (*status.second)[NAME].second._to_str();
    //  auto &code_list = (*status.second)[CODE].second._get_vector_ref();
      //cout << "defun code list:" << code_list << "\n";
      attach_this_to_arguments((*status.second)[_PARAMS].second._get_vector_ref());
   //   attach_this_to_var(code_list); // pre-prend (var this) to a class method, hopeflly only private in future
      class_functions->set(fun_name, move(status.second));
      continue;
    }
    case Lisp::Type::class_: {
    }
    default: { // assign class attributes here like  (var )
      if(status.second->type_==Node::Type::Vector) {
        auto head = status.second->front().second._to_str();
        auto v2o_status = vector_to_object(status.second->_get_vector_ref()); // vector 2 object
        class_node->set(head,  move(v2o_status.second) );

      } else {
        cerr << "unknown class attribute not vector!\n";
        return {false, Node::create_error(Error::Type::Parse, "unknown class attribute:" )};
      }
    }}
  }
  class_node->set(FUNCTION, move(class_functions));
  class_node->set(OBJ_INFO, move(obj_info));
  class_node->set(NAME, class_name);
  class_node->set(NAMESPACE,  Node::create(build_namespace));

  //cout << "module_node:" << *module_node << "\n";
  return {true, move(class_node)};
}



//-------------------------------- parse root
// (root :set (path,..) value )
// (root :get () )
Node::OpStatus LispExpr::build_parsed_root(Node::List& list) {
  MYLOGGER(trace_function, "LispExpr::build_parsed_root(Node::List& list)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("list: ") + Node::_to_str(list), SLOG_FUNC_INFO+30);

  try {
    auto root_sym_op = get<Node::Integer>(list.front()->value_); list.pop_front(); // root op symbol 
    if(root_sym_op == atom_set) {
      auto path_list = move(get<Node::List>(list.front()->value_));  list.pop_front();
      auto value = move(list.front());  list.pop_front();

      auto path_vec_str = Node::list_to_vector_string(path_list);
      return set(path_vec_str, move(value), true);
      //return {true, Node::create(true)};

    } else if(root_sym_op== atom_get){
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
// attach module to 'Lisp' Language tree
//
Node::OpStatus LispExpr::attach_module(unique_ptr<Node> mod_ptr) {
  MYLOGGER(trace_function, "LispExpr::attach_module(unique_ptr<Node>module)", __func__, SLOG_FUNC_INFO);
  //auto mod_loc = get_branch(lisp_path_module);
  auto mod_loc = get_branch(namespace_module_path());
  auto name_ref_status  = mod_ptr->get_node(NAME);

  if(!name_ref_status.first) {
    cerr << "error getting module name!\n";
    return {false, name_ref_status.second.clone()};
  }
  auto module_name = name_ref_status.second._to_str();
  //cout << "module name: " << module_name << "\n";


  //return mod_loc->merge(move(module));
  return mod_loc->set(module_name, move(mod_ptr));
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
    cerr << "build_parsed_vector() error with '"<<  node << "',type: " << Node::_to_str(node.type_) << "\n";
    return {false, Node::create_error(Error::Type::Parse, "build_parsed_vector()! not vector type:Can't build vector!")};
  }

  try {
  auto &list = get<Node::List>(node.value_);
  return build_parsed_vector(list);
  } catch(...) { 
    cerr << "build_parsed_vector() error with list '" <<  node << "'\n";
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
      auto status_parsed = parse_build(*ele);
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
      auto status_parsed = parse_build(*ele);
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

Node::OpStatus LispExpr::vector_to_object(const Node::Vector&list) {
  MYLOGGER(trace_function, "LispExpr::vector_to_object(const Node::Vector& list)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, "list: " + Node::_to_str( list), SLOG_FUNC_INFO+30);

  auto object = make_unique<Node>(Node::Type::Map);
  auto object_info = make_unique<Node>(Node::Type::Map);

  auto& head = list[0];
  try {
    auto lisp_type = get<Lisp::Type>(head->value_);
    if(lisp_type==Lisp::Type::var) {
      //cout << "need to assign vars differently because  in a class init object value (var (length 3.14159))!\n";
      //object->set(OBJ_INFO, move(object_info));
      //object->set(VECTOR, Node::clone(list));
      return {true, Node::clone(list)};

    }
    object_info->set(TYPE, lisp_type);
  } catch (...) {
    object_info->set(TYPE, Lisp::Type::nil);
  }
/*
  size_t s = list.size();
  for(size_t i=1;  i <s; i++  ) {
    object->set(list[i]->_to_str(), Node::create());
  }
*/
  object->set(OBJ_INFO, move(object_info));
  object->set(VECTOR, Node::clone(list));
  return {true, move(object)};
}


//-------------------------------- iif
Node::OpStatus LispExpr::build_parsed_if(Node::List& list) {
  MYLOGGER(trace_function, "LispExpr::build_parsed_iif(Node::List& list)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, "Node::List& list : " + Node::_to_str(list), SLOG_FUNC_INFO+30);
  Node::Vector if_vl, block_vl;

  if_vl.reserve(list.size());
  block_vl.reserve(list.size());

  // first block
  if(list.empty()) {
    return {false, Node::create_error(Error::Type::Parse, "parse: if error!")};
  }

  { // condition block
    auto status_parsed = parse_build(*list.front());
    if(!status_parsed.first) return status_parsed;
    if_vl.push_back(Node::create(Lisp::Op::if_));
//    cout << "condition: status_parsed" << status_parsed << "\n";
    if_vl.push_back(move(status_parsed.second));
    list.pop_front();
  }


  for(auto& ele: list) {
    auto status_parsed = parse_build(*ele);
    if(!status_parsed.first) return status_parsed;

    auto back_status_ref = status_parsed.second->back();
    if(back_status_ref.second.type_ == Node::Type::Atom &&
       back_status_ref.second._get_integer() == atom_else) {

      //cout << "build iif, block:  " << Node::_to_str(block_vl) << "\n";
      if_vl.push_back(Node::create(move(block_vl))); // push the first block
      block_vl.clear();
      continue;
    }
    block_vl.push_back(move(status_parsed.second));
  }
  if_vl.push_back(Node::create(move(block_vl)));

  //cout << "if_vl:  " << Node::_to_str(if_vl) << "\n\n";



  return {true, Node::create(move(if_vl))};
}

Node::OpStatus LispExpr::use_at_parse_build(Node::List& cc_list) {
  MYLOGGER(trace_function, "LispExpr::use(Node::List& list)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, "Node::List& list : " + Node::_to_str(cc_list), SLOG_FUNC_INFO+30);

  //cout << "namespace: " << Node::_to_str( cc_list) << "\n";
  auto cmd_option = move(cc_list.front()); cc_list.pop_front();

  //return {true, Node::create()};
  if(cmd_option->_get_integer() == atom_namespace) {
    auto ns = move(cc_list.front()); 
    build_namespace = ns->_to_str();
    set_branch(namespace_module_path(), Node::create(Node::Type::Map));
    //cout << "namespace: " << build_namespace << "\n";

  }


  return {true, Node::create(true)};
}