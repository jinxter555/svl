#include <iostream>
#include "lisp_expr.hh"
#include "my_helpers.hh"
#include "interactive.hh"

#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"

//------------------------------------------------------------------------
Node::OpStatus LispExpr::car(Node&process, const Node::Vector &list, size_t start) {
  MYLOGGER(trace_function, "LispExpr::car(Node&process, Node::Vector&list)", __func__, SLOG_FUNC_INFO)
  MYLOGGER_MSG(trace_function, string("list: ") + Node::_to_str(list), SLOG_FUNC_INFO+30)
  MYLOGGER_MSG(trace_function, string("start: ") + to_string(start), SLOG_FUNC_INFO+30)

  if(list.empty()) return {true, Node::create()}; // return null

  auto &head = list[start];
  auto rv_status = eval(process, *head);
  if(!rv_status.first) {
    cerr << "Error encounter in lisp::car eval" << rv_status << "\n";
    return rv_status;
  }
  if(rv_status.second->type_==Node::Type::Vector) {
    auto &plist = get<Node::Vector>(rv_status.second->value_);
    if(plist.size()==0) return {true, Node::create()};
    return {true, move(plist[0])};
  }
  return {true, Node::create()};
}

Node::OpStatus LispExpr::cdr(Node&process, const Node::Vector &list, size_t start) {
  MYLOGGER(trace_function, "LispExpr::cdr(Node&process, Node::Vector&list)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("list: ") + Node::_to_str(list), SLOG_FUNC_INFO+30);
  MYLOGGER_MSG(trace_function, string("start: ") + to_string(start), SLOG_FUNC_INFO+30);

  if(list.empty()) return {true, Node::create()}; // return null

  auto &head = list[start];
  auto rv_status = eval(process, *head);
  if(!rv_status.first) {
    cerr << "Error encounter in lisp::cdr eval" << rv_status << "\n";
    return rv_status;
  }
  if(rv_status.second->type_==Node::Type::Vector) {
    Node::Vector rlist;
    auto &plist = get<Node::Vector>(rv_status.second->value_);
    size_t  s= plist.size(); 
    if(s==0) return {true, Node::create()};
    for(size_t i=1; i<s; i++) {
      rlist.push_back(move(plist[i]));
    }
    return {true, Node::create(move(rlist))};
  }
  // from scalar
  return {true, Node::create()};
}

//------------------------------------------------------------------------
Node::OpStatus LispExpr::literal(const Node::Vector &list, size_t start) {
  MYLOGGER(trace_function, "LispExpr::literal(const Node::Vector&list, int start)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, "start: " + start, SLOG_FUNC_INFO+30);
  Node::Vector list_result;
  size_t s=list.size();
  for(size_t i=start; i<s; i++) 
    list_result.push_back(list[i]->clone());
  return {true, Node::create(move(list_result))};
}
Node::OpStatus LispExpr::attach_class_vars_to_object(Node&process, Node&object, Node::Vector& var_list){
  size_t s = var_list.size();
  for(size_t i=1; i<s; i++) { // skip i = 0, (var ..) 
    auto const &ele = var_list[i];
    switch(ele->type_) {
    case Node::Type::Identifier: {
      if(ele->_to_str() =="this") {cerr << "you can't do that with 'this' in class\n"; break;}
      object.set(ele->_to_str(),  make_unique<Node>());
      break; }
    case Node::Type::Vector: {
      auto v_name_ref_1 = (*ele)[0];
      auto v_var_ref_1 = (*ele)[1];
      auto v = eval(process, v_var_ref_1.second);
      if(!v.first) return v;
      object.set(v_name_ref_1.second._to_str(),  move(v.second));
      break; }
    default: return {false, Node::create_error(Error::Type::Unknown, "Unknown var error")}; }
  }
  return {true, Node::create(true)};
}

//------------------------------------------------------------------------
// create a map object
// (new ClassName (param1 param2 ... ) ) //creates a new map object
//
Node::OpStatus LispExpr::object_create(Node&process, const Node::Vector &list, size_t start) {
  MYLOGGER(trace_function, "LispExpr::object_create(Node&process, Node::Vector&list, int start)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("list: ") + Node::_to_str(list), SLOG_FUNC_INFO+30);
  MYLOGGER_MSG(trace_function, string("start: ") + to_string(start), SLOG_FUNC_INFO+30);
  auto class_full_name = list[start]->_to_str();
  auto cfnv = split_string_deque(class_full_name, "."); // class full name vector module.class or name space. mdoule . class

  auto object = Node::create(Node::Type::Map);
  auto obj_info = Node::create(Node::Type::Map);

  obj_info->set(TYPE, Lisp::Type::object );


  if(cfnv.size() == 1) {
    auto current_module = frame_current(process).second[CURRENT_MODULE].second._to_str();
    cfnv.push_front(current_module);
  }

  auto class_ref_status  = get_class(cfnv);
  if(!class_ref_status.first) {
    cerr << "Can't create an object for class:'"  << _to_str_ext(cfnv) <<"', error:"  << class_ref_status.second._to_str() << "\n";
    return {false, class_ref_status.second.clone()};
  }
  obj_info->set(_CLASS, _to_str_ext(cfnv));

//  cout << "class ref status: " << class_ref_status << "\n";
 //cout << "need to call class constructor: " << cfnv.back()  << "\n";
 //vector<string> constructor_path = {FUNCTION, cfnv.back()};

 //cout << "need to call class constructor: " <<  class_ptr->get_node(constructor_path)  << "\n";

  obj_info->set(CLASS_PTR, &class_ref_status.second);
  object->set(OBJ_INFO, move(obj_info));


  auto var_ref_status = class_ref_status.second.get_node(VAR); // get class variables  
  if(!var_ref_status.first) {
    cerr << "no class var found: " << var_ref_status << "\n";
    return {false, var_ref_status.second.clone()};
  }
  attach_class_vars_to_object(process, *object, var_ref_status.second._get_vector_ref());
  // inject vars into contructor 


  auto shared_object_call = Node::container_obj_to_US(move(object));
  auto shared_object_ret = Node::ptr_USU(shared_object_call);

  //auto constructor_ref_status = class_ref_status.second.get_node(constructor_path);

  auto constructor_ref_status = class_ref_status.second.get_node({FUNCTION, cfnv.back()});



  //cout << "constructor: " << constructor_ref_status.second << "\n\n";

  auto argv_status = eval(process, list, start + 1); // get all the argv
  if(!argv_status.first) {
    cerr  << "Ojbect construct parameters errors: " <<  argv_status.second->_to_str() << "\n";
    return argv_status;
  }

  auto &argv_list_vector = argv_status.second->_get_vector_ref();

  argv_list_vector.insert(argv_list_vector.begin(), Node::ptr_US( move(shared_object_call)));

  // cout << "argv_status : " << argv_status << "\n";

  call(process, constructor_ref_status.second, move(argv_list_vector));
  return {true, move(shared_object_ret)};
}



//------------------------------------------------------------------------
// create a map object
// (send object_variable (method arg1 arg2... ) ) //creates a new map object
// (send object_variable method (arg1 arg2...  ) //creates a new map object
//
Node::OpStatus LispExpr::send_object_message(Node&process, const Node::Vector &list, size_t start) {
  MYLOGGER(trace_function, "LispExpr::send_object_message(Node&process, Node::Vector&list, int start)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("list: ") + Node::_to_str(list), SLOG_FUNC_INFO+30);
  MYLOGGER_MSG(trace_function, string("start: ") + to_string(start), SLOG_FUNC_INFO+30);

  auto object_name = list[start]->_to_str();
  auto object_ref_status = symbol_lookup(process, object_name);

  if(!object_ref_status.first) {
    cerr << "Can't lookup object '"  << object_name <<"', error:"  << object_ref_status.second._to_str() << "\n";
    return {false, object_ref_status.second.clone()};

  }

  auto &object = object_ref_status.second;
  auto fun_ref_status
    =object.get_node_with_ptr(OBJ_INFO)
    .second.get_node_with_ptr(CLASS_PTR)
    .second.get_node_with_ptr(FUNCTION);

  auto object_uptr = Node::ptr_USU(object);

  if(!fun_ref_status.first) {
    cerr << "in send_object_Message(...) error looking up methods fun_ref_status: "  << fun_ref_status.second << "\n";
    return {false, fun_ref_status.second.clone()};
  }

  //cout << "object : type" << Node::_to_str( object.type_) << "\n";
  //cout << "object_ptr : type" << Node::_to_str( object_ptr->type_) << "\n";
  //cout << "class_ptr " << class_ptr << "\n";

  //auto method_name = atom_to_str(list[start+1]->_get_integer()).second._to_str();
  auto method_name = atom_to_str(list[start+1]->_get_integer());
  auto argv_list = eval(process, list, start+1); // this returns a vector

 // cout << "method_name: " <<  method_name << "\n";
 // cout << "1 argv_list: " <<  argv_list<< "\n";

  argv_list.second->set(0, move(object_uptr)); // 0, was the :method name, and change it to object ptr 



  auto method_fun = fun_ref_status.second.get_node(method_name);

  return call(process, method_fun.second, move(argv_list.second->_get_vector_ref()));

}



//------------------------------------------------------------------------
// 2 parmas module.class
// 3 parmas namespace.module.class // to be worked on

Node::OpStatusRef LispExpr::get_class(deque<string> mc) {
  MYLOGGER(trace_function, "LispExpr::get_class(list<string>mfc)", __func__, SLOG_FUNC_INFO);
  string mc_str = _to_str_ext(mc);
  MYLOGGER_MSG(trace_function, "mfc: " + mc_str  , SLOG_FUNC_INFO+30);
  auto path = lisp_path_module;
  path.push_back(mc[0]);
  path.push_back(_CLASS);
  path.push_back(mc[1]); //cout << "getclass: path " << _to_str_ext(path) << "\n";
  auto node_ref_status = get_node(path);
  if(!node_ref_status.first)  {
    cerr << "Looking up class '"  << mc_str <<"' not found: "  << node_ref_status.second._to_str() << "\n";
    return node_ref_status;
  }
  return node_ref_status;


}


//------------------------------------------------------------------------
// create a map object
// (map ( (k1 v1) (k2 v2) )) //creates a new map object
Node::OpStatus LispExpr::map_create(Node&process, const Node::Vector &list_kv, size_t start) {
  MYLOGGER(trace_function, "LispExpr::map_create(Node&process, Node::Vector&list_kv, int start)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("list_kv: ") + Node::_to_str(list_kv), SLOG_FUNC_INFO+30);
  MYLOGGER_MSG(trace_function, string("start: ") + to_string(start), SLOG_FUNC_INFO+30);
  Node::Map map;
  auto obj_info = make_unique<Node>(Node::Type::Map);

  if(list_kv.empty()) return {true, Node::create(Node::Type::Map)}; // empty map

  size_t  s = list_kv.size();
  for(size_t i=start; i<s; i++) {
    auto &kv_pair = list_kv[i];
    auto const &key_ref_status  = kv_pair->get_node(0);
    if(!key_ref_status.first) {
      cerr << "map create, key,  error! "  <<  key_ref_status.second << "\n";
      return {false, key_ref_status.second.clone()};
    }

    auto const &value_ref_status = kv_pair->get_node(1);
    if(!value_ref_status.first) {
      cerr << "map create, value, error! "  <<  value_ref_status.second << "\n";
      return {false, value_ref_status.second.clone()};
    }
    auto value_status = eval(process, value_ref_status.second);
    if(!value_status.first) {
      cerr << "map create key,value eval pair error! "  <<  value_status << "\n";
      return value_status;
    }
    map[key_ref_status.second._to_str()] = move(value_status.second);

  }
  
  //auto type_atom_ptr = make_unique<Node>();
  //type_atom_ptr->set_atom(str_to_atom("map"));
  //obj_info->set("type",  move(type_atom_ptr));
  obj_info->set("type", Lisp::Type::map );
  map[OBJ_INFO] = move(obj_info);


  //cout << "map " << Node::_to_str( map) << "\n";
  return {true, Node::create(move(map))};
}

//------------------------------------------------------------------------
// process, node this object, and args pass to this object
Node::OpStatus LispExpr::map_get_keys(Node&process, Node &node, const Node::Vector& args) {
  MYLOGGER(trace_function, "LispExpr::map_get_keys(Node&process, const Node& node, const Vector& args)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("node: ") + node._to_str(), SLOG_FUNC_INFO+30);
  MYLOGGER_MSG(trace_function, string("node: ") + Node::_to_str(args), SLOG_FUNC_INFO+30);

  switch(node.type_) {
  case Node::Type::Map: {
    Node::Vector list_key; 
    auto &map = get<Node::Map>(node.value_);
    for(const auto& kv : map) {
      if(kv.first == OBJ_INFO) continue;
      list_key.push_back(Node::create(kv.first));} 

    return {true, Node::create(move(list_key))};}

  case Node::Type::Shared: {
    Node::Vector list_key; 
    auto &map_ptr = get<Node::ptr_S>(node.value_);
    auto &map= get<Node::Map>(map_ptr->value_);
    for(const auto& kv : map)  {
      if(kv.first == OBJ_INFO) continue;
      list_key.push_back(Node::create(kv.first)); }
    return {true, Node::create(move(list_key))}; }
  default: 
    return {false, Node::create_error(
    Error::Type::IndexWrongType, 
    "map get keys and but type is not map, type: "+  Node::_to_str(node.type_))};
  }

}
//------------------------------------------------------------------------
// index by key
Node::OpStatus LispExpr::map_get_value(Node&process, Node &node, const Node::Vector& args) {
  MYLOGGER(trace_function, "LispExpr::map_get_value(Node&process, const Node& node, const Vector& args)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("node: ") + node._to_str(), SLOG_FUNC_INFO+30);
  MYLOGGER_MSG(trace_function, string("args: ") + Node::_to_str(args), SLOG_FUNC_INFO+30);

  auto &key_ptr = args[0];

  if(key_ptr->type_ != Node::Type::String) 
    return {false, Node::create_error(Error::Type::IndexWrongType, "key is not a string!")};
  string key_str = key_ptr->_to_str();


  switch(node.type_) {
  case Node::Type::Map: {
    auto &map = get<Node::Map>(node.value_);
    for(const auto& kv : map) 
      if(kv.first == key_str) return {true, Node::create(kv.second->clone())};
    return {false, Node::create_error(Error::Type::KeyNotFound, "Key : '"  + key_str +"' not found!")};
  }
  case Node::Type::Shared: {
    auto &map_ptr = get<Node::ptr_S>(node.value_);
    if(map_ptr->type_!= Node::Type::Map)  
      return {false, Node::create_error(Error::Type::IndexWrongType, 
        "map_set_value() shared pointer not pointing to map !")};
    auto &map= get<Node::Map>(map_ptr->value_);
    for(const auto& kv : map)  
      if(kv.first == key_str) return {true, Node::create(kv.second->clone())};
    return {false, Node::create_error(Error::Type::KeyNotFound, "Key : '"  + key_str +"' not found!")};
  }
  default: 
    return {false, Node::create_error(
    Error::Type::IndexWrongType, 
    "map get keys and but type is not map, type: "+  Node::_to_str(node.type_))};
  }
}

//------------------------------------------------------------------------
// no need to eval  args !!!! because ars have already beend evaled by call_extern
Node::OpStatus LispExpr::map_set_value(Node&process, Node &node, const Node::Vector& args) {
  MYLOGGER(trace_function, "LispExpr::map_set_value(Node&process, const Node& node, const Vector& args)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("node: ") + node._to_str(), SLOG_FUNC_INFO+30);
  MYLOGGER_MSG(trace_function, string("args: ") + Node::_to_str(args), SLOG_FUNC_INFO+30);

  auto &key_ptr = args[0];
  auto &value_ptr = args[1];

  if(key_ptr->type_ != Node::Type::String) 
    return {false, Node::create_error(Error::Type::IndexWrongType, "key is not a string!")};
  string key_str = key_ptr->_to_str();


  switch(node.type_) {
  case Node::Type::Map: {
    auto &map = get<Node::Map>(node.value_);
    map[key_str] = value_ptr->clone();
    return {true, Node::create(true)};
  }
  case Node::Type::Shared: {
    auto &map_ptr = get<Node::ptr_S>(node.value_);
    if(map_ptr->type_!= Node::Type::Map)
      return {false, Node::create_error(Error::Type::IndexWrongType, 
        "map_set_value() shared pointer not pointing to map !")};

    auto &map= get<Node::Map>(map_ptr->value_);
    map[key_str] = value_ptr->clone();
    return {true, Node::create(true)};
  }
  default: 
    return {false, Node::create_error(
    Error::Type::IndexWrongType, 
    "map get keys and but type is not map, type: "+  Node::_to_str(node.type_))};
  }
}
//------------------------------------------------------------------------
Node::OpStatus LispExpr::map_del_key(Node&process, Node &node, const Node::Vector& args) {
  MYLOGGER(trace_function, "LispExpr::map_del_key(Node&process, const Node& node, const Vector& args)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, "node: " + node._to_str(), SLOG_FUNC_INFO+30)
  MYLOGGER_MSG(trace_function, "args: " + Node::_to_str(args), SLOG_FUNC_INFO+30)

  auto &key_ptr = args[0];

  if(key_ptr->type_ != Node::Type::String) 
    return {false, Node::create_error(Error::Type::IndexWrongType, "key is not a string!")};
  string key_str = key_ptr->_to_str();

  switch(node.type_) {
  case Node::Type::Map: {
    auto &map = get<Node::Map>(node.value_);
    Node::Integer s = map.erase(key_str);
    return {true, Node::create(s)};
  }
  case Node::Type::Shared: {
    auto &map_ptr = get<Node::ptr_S>(node.value_);
    if(map_ptr->type_!= Node::Type::Map)
      return {false, Node::create_error(Error::Type::IndexWrongType, 
        "map_set_value() shared pointer not pointing to map !")};

    auto &map= get<Node::Map>(map_ptr->value_);
    Node::Integer s = map.erase(key_str);
    return {true, Node::create(s)};
  }
  default: {}}

  return {false, Node::create_error(
    Error::Type::IndexWrongType, 
    "map get keys and but type is not map, type: "+  Node::_to_str(node.type_))};
}

Node::OpStatus LispExpr::map_has_key(Node&process, Node &node, const Node::Vector& args) {
  MYLOGGER(trace_function, "LispExpr::map_has_key(Node&process, const Node& node, const Vector& args)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, "node: " + node._to_str(), SLOG_FUNC_INFO+30)
  MYLOGGER_MSG(trace_function, "args: " + Node::_to_str(args), SLOG_FUNC_INFO+30)

  auto &key_ptr = args[0];

  if(key_ptr->type_ != Node::Type::String) 
    return {false, Node::create_error(Error::Type::IndexWrongType, "key is not a string!")};
  string key_str = key_ptr->_to_str();

  switch(node.type_) {
  case Node::Type::Map: {
    //auto &map = get<Node::Map>(node.value_);
    //Node::Integer s = map.erase(key_str);
    return node.has_key(key_str);
  }
  case Node::Type::Shared: {
    auto &map_ptr = get<Node::ptr_S>(node.value_);
    if(map_ptr->type_!= Node::Type::Map)
      return {false, Node::create_error(Error::Type::IndexWrongType, 
        "map_set_value() shared pointer not pointing to map !")};
    return map_ptr->has_key(key_str);
  }
  default: {}}

  return {false, Node::create_error(
    Error::Type::IndexWrongType, 
    "map get keys and but type is not map, type: "+  Node::_to_str(node.type_))};
}

//
// (lambda (param_list) (description) (code list))
// (lambda (param_list) (code list))
Node::OpStatus LispExpr::lambda_create(Node&process, const Node::Vector &list, size_t start){

  MYLOGGER(trace_function, "LispExpr::lambda(Node::List& list)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("list: ") + Node::_to_str(list), SLOG_FUNC_INFO+30);

  size_t s = list.size();

  if(list.size()<3) return {false, Node::create_error(Error::Type::Parse, "lambda requires atleast 2 parameters! " + Node::_to_str(list))};

  Node::Map map={}; 
  auto obj_info = make_unique<Node>(Node::Type::Map);

  map[_PARAMS] = list[start]->clone();

  if(s==4){ // both description and code
    map[DESC] = list[start+1]->clone();
    map[CODE] = list[start+2]->clone();
  } else if(s==3) { // just code
    map[CODE] = list[start+1]->clone();
  }
  obj_info->set("type",  Lisp::Type::lambda);
  map[OBJ_INFO] = move(obj_info);
  
  return {true, Node::create(move(map))};

}

// (do (param_list) (code list))
Node::OpStatus LispExpr::closure_create(Node&process, const Node::Vector &list, size_t start){
  MYLOGGER(trace_function, "LispExpr::closure_create(Node::List& list)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("list: ") + Node::_to_str(list), SLOG_FUNC_INFO+30);

  size_t s = list.size();

  if(list.size()<2) return {false, Node::create_error(Error::Type::Parse, "closure do() blcok requires atleast 2 parameters! " + Node::_to_str(list))};

  Node::Map map={}; 
  auto obj_info = make_unique<Node>(Node::Type::Map);

  map[_PARAMS] = list[start]->clone();
  map[CODE] =  Node::create(list_clone_remainder(list, start+1));
  obj_info->set("type",  Lisp::Type::do_);
  map[OBJ_INFO] = move(obj_info);
  
  return {true, Node::create(move(map))};

}



Node::Vector LispExpr::list_clone_remainder(const Node::Vector &list, size_t start) {
  Node::Vector result_list;
  size_t s = list.size();
  for(size_t i=start; i<s; i++) 
    result_list.push_back(list[i]->clone());
  //return move(result_list);
  return result_list;
}


bool LispExpr::forever = true;

Node::OpStatus LispExpr::loop_forever(Node& process, const Node::Vector& list, size_t start) {
  MYLOGGER(trace_function, "LispExpr::loop_forever(Node& process, const Vector, start)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("list: ") + Node::_to_str(list), SLOG_FUNC_INFO+30)
  MYLOGGER_MSG(trace_function, string("start: ") + to_string(start), SLOG_FUNC_INFO+30)
  size_t s= list.size();
  while(forever) {
    //cout << "forever loop:\n";
    for(size_t i=start; i < s; i++) {
      auto &node = list[i];
      eval(process, *node);
    }
  }
  forever=true;
  return {true, Node::create()};
  //return {true, Node::create(false)};
  //return {true, nullptr};
}
Node::OpStatus LispExpr::read_input() {
  MYLOGGER(trace_function, "LispExpr::read_input()", __func__, SLOG_FUNC_INFO);
  string input;

  try { input = interface->read(); } catch(...) { forever=false; return {true, Node::create()}; }
  
  //cout << "> "; getline(cin , input);

  if(input == "exit") { 
    forever = false; 
    return {true, Node::create() };
  }

  if(input=="") return { true, Node::create()};

  auto token_list = reader.tokenize( reader.tokenize_preprocess( input)); // list<Token> 
  auto parsed_tokens_status =  reader.parse(token_list); // parse 
  if(!parsed_tokens_status.first) {
    cerr << "error parsing string token: !"  << parsed_tokens_status.second->_to_str() <<" \n";
    return parsed_tokens_status;
  }

  auto tokens = Node::create(move(parsed_tokens_status.second->_get_list_ref())); // this extra step maybe uncessary in future
  auto input_code_status = parse(*tokens);

  //cout <<"from 'read' after tokenizing, input_code_status: " << input_code_status << "\n";
  return input_code_status;
}

Node::Vector LispExpr::list_2_vector(Node::List &&list) {
  Node::Vector new_list;
  new_list.reserve(list.size());
  for(auto &ele : list) {
    new_list.push_back(move(ele));
  }
  return new_list;
}

// (root (..))
Node::OpStatus LispExpr::root_manifest(Node& process, const Node::Vector& code_list, size_t start) {
  MYLOGGER(trace_function, "LispExpr::root_manifest(Node&process, Node::Vector& code_list, size_t start)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, "code_list: " + Node::_to_str(code_list), SLOG_FUNC_INFO+30);
  MYLOGGER_MSG(trace_function, "start: " + to_string(start), SLOG_FUNC_INFO+30);
  cout << "root mani!\n";
  vector<string> path;
  size_t i, s =code_list.size();
  for(size_t i=start; i<s; i++) {
    path.push_back(code_list[i]->_to_str());
  }
   cout  << "root path '" << _to_str_ext( path) << "' \n";
  auto node_status_ref = get_node(path);
   cout  << "node status1 '" << node_status_ref << "' \n\n";

  if(!node_status_ref.first) {
    cerr << "root path '" << _to_str_ext( path) << "' not found\n";
    return {false, Node::create_error(Error::Type::KeyNotFound, "Path: '"  + _to_str_ext( path) + "' not found")};
  }
   cout  << "node status2 '" << node_status_ref << "' \n\n";
  return {true, node_status_ref.second.clone() };

  return {true, Node::create()};
}