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

  auto ev_list_status = eval(process, list, start);
  if(!ev_list_status.first) {
    cerr << "Error encounter in lisp::car eval list" << ev_list_status << "\n";
    return ev_list_status;
  }


  auto &head = ev_list_status.second->front().second;
  // auto rv_status = eval(process, *head);
  auto rv_status = eval(process, head);
  if(!rv_status.first) {
    cerr << "Error encounter in lisp::car eval" << rv_status << "\n";
    return rv_status;
  }
  if(rv_status.second->type_==Node::Type::Vector) {
    auto &plist = get<Node::Vector>(rv_status.second->value_);
    if(plist.size()==0) return {true, Node::create()};
  cout << "car v rv_status: " << rv_status << "\n";
    return {true, move(plist[0])};
  }
  if(rv_status.second->type_==Node::Type::Shared) {
    auto s_ptr = get<Node::ptr_S>(rv_status.second->value_);
    return car(process, s_ptr->_get_vector_ref(), 0);
  }

  //return {true, Node::create()};
  //cout << "car rv_status: " << rv_status << "\n";
  return rv_status;
}


//------------------------------------------------------------------------
Node::OpStatus LispExpr::car_eval_head(Node&process, const Node::Vector &list, size_t start) {
  MYLOGGER(trace_function, "LispExpr::car(Node&process, Node::Vector&list)", __func__, SLOG_FUNC_INFO)
  MYLOGGER_MSG(trace_function, string("list: ") + Node::_to_str(list), SLOG_FUNC_INFO+30)
  MYLOGGER_MSG(trace_function, string("start: ") + to_string(start), SLOG_FUNC_INFO+30)

  if(list.empty()) return {true, Node::create()}; // return null


  auto &head = list[start];
  // auto rv_status = eval(process, *head);
  auto rv_status = eval(process, *head);
  if(!rv_status.first) {
    cerr << "Error encounter in lisp::car eval" << rv_status << "\n";
    return rv_status;
  }
  if(rv_status.second->type_==Node::Type::Vector) {
    auto &plist = get<Node::Vector>(rv_status.second->value_);
    if(plist.size()==0) return {true, Node::create()};
  cout << "car v rv_status: " << rv_status << "\n";
    return {true, move(plist[0])};
  }
  if(rv_status.second->type_==Node::Type::Shared) {
    auto s_ptr = get<Node::ptr_S>(rv_status.second->value_);
    return car(process, s_ptr->_get_vector_ref(), 0);
  }

  //return {true, Node::create()};
  //cout << "car rv_status: " << rv_status << "\n";
  return rv_status;
}

//------------------------------------------------------------------------

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
Node::OpStatus LispExpr::literal(const Node::Vector &list_cc_vec, size_t start) {
  MYLOGGER(trace_function, "LispExpr::literal(const Node::Vector&list, int start)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, "start: " + start, SLOG_FUNC_INFO+30);
  Node::Vector list_result;
  size_t s=list_cc_vec.size();
  for(size_t i=start; i<s; i++)  {
    auto op = keyword_to_op(list_cc_vec[i]->_to_str()); // Lisp::Op
    if(op != Lisp::Op::scalar)   // identifier or scalar
      list_result.push_back(Node::create(op));
    else
      list_result.push_back(list_cc_vec[i]->clone());
  }
  return {true, Node::create(move(list_result))};
}

//------------------------------------------------------------------------
// modifiy code list for unquotes
Node::OpStatus LispExpr::quote(Node&process, const Node::Vector &code_list, size_t start) {
  MYLOGGER(trace_function, "LispExpr::quote(const Node::Vector&list, int start)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("code_list: ") + Node::_to_str(code_list), SLOG_FUNC_INFO+30);
  MYLOGGER_MSG(trace_function, "start: " + start, SLOG_FUNC_INFO+30);

  size_t s=code_list.size();
  Node::Vector result_cc_vec;
  result_cc_vec.reserve(s);

  for(size_t i=start; i<s; i++) {
    switch(code_list[i]->type_) {
    case Node::Type::Vector: {
      //cout << "innner quote: " << code_list[i]->_to_str() << "\n\n";

      auto &inner_vec = code_list[i]->_get_vector_ref(); // skip the first element that's op_head
      auto inner_status= quote(process, inner_vec, 0);
      if(!inner_status.first) { return inner_status; }
      result_cc_vec.push_back(move(inner_status.second));

      break;
    }
    case Node::Type::LispOp: {

      Lisp::Op op_head = get<Lisp::Op>(code_list[i]->value_); // skip the first element that's op_head
      if(op_head == Lisp::Op::unquote) {
        //cout << "in quote( unquote() )\n";
        auto uq_status = unquote(process, code_list, i+1);
        i++; // skip to the next token 

        if(!uq_status.first) {
          cerr << "in quote( unquote(..) ) error:" << uq_status.second->_to_str() << "\n";
          return uq_status;
        }
        //result_cc_vec.push_back(move(uq_status.second));
        return uq_status;
      } else {
        result_cc_vec.push_back(code_list[i]->clone());
      }
      break;
    }
    case Node::Type::Identifier: { // check if it is 'identifier#'
      auto id_name = code_list[i]->_to_str();
      if(id_name.back() == '~') {
        auto unique_name = Lang::unqiue_name(id_name);
        result_cc_vec.push_back(Node::create(unique_name, Node::Type::Identifier));
        break;
      }
    }

    default: {
      result_cc_vec.push_back(code_list[i]->clone());
    }}
  }

    //list_result.push_back(list[i]->clone());

  return {true, Node::create(move(result_cc_vec))};
}
//------------------------------------------------------------------------
// (unquote symbol)
Node::OpStatus LispExpr::unquote(Node&process, const Node::Vector &list, size_t start) {
  MYLOGGER(trace_function, "LispExpr::unquote(const Node::Vector&list, int start)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, "start: " + start, SLOG_FUNC_INFO+30);


  auto name = list[start]->_to_str();
  auto rv_ref_status = symbol_lookup(process, name);

  //cout << "unquoting ' " << name << "'\n";
  //cout << "rv_ref_status: " << rv_ref_status << "\n";

  if(!rv_ref_status.first) {
    cerr << "unquote Identifier: '" << name << "' not found!" << rv_ref_status.second._to_str() << "\n";
    return {false, rv_ref_status.second.clone()};
  }
  if(rv_ref_status.second.type_ == Node::Type::Shared) 
    return {true, Node::ptr_USU(rv_ref_status.second)}; // clone a uniqu ptr to shared ptr without  recursive clone
  return {true, rv_ref_status.second.clone()};

}

//------------------------------------------------------------------------
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
    default: return {false, Node::create_error(Error::Type::Unknown, "attach class var to object() Unknown var error")}; }
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
  string current_module;
  auto class_full_name = list[start]->_to_str();

  auto object = Node::create(Node::Type::Map);
  auto obj_info = Node::create(Node::Type::Map);

  obj_info->set(TYPE, Lisp::Type::object );

  auto cfp = full_path_class(process, class_full_name); 
  auto class_ref_status  = get_node(cfp);

  if(!class_ref_status.first) {
    cerr << "Can't create an object for class:'"  << class_full_name <<"', error:"  << class_ref_status.second._to_str() << "\n";
    return {false, class_ref_status.second.clone()};
  }
  obj_info->set(_CLASS, class_full_name);

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

  vector<string> constructor_name = {FUNCTION, INITIALIZE};

  try {
    auto constructor_ref_status = class_ref_status.second.get_node(constructor_name);
  
    auto argv_status = eval(process, list, start + 1, 1); // get all the argv and create a spot at vector[0] for 'this' object
    if(!argv_status.first) {
      cerr  << "Object construct parameters errors: " <<  argv_status.second->_to_str() << "\n";
      return argv_status;
    }
    auto &argv_list_vector = argv_status.second->_get_vector_ref();
  
    //argv_list_vector.insert(argv_list_vector.begin(), Node::ptr_US( move(shared_object_call)));
    //argv_list_vector[0] = Node::ptr_US( move(shared_object_call));
    argv_list_vector[0] = move(shared_object_call);
  
    call(process, constructor_ref_status.second, move(argv_list_vector));
    return {true, move(shared_object_ret)};

  } catch(...) {
    auto msg = "constructor method: initialize() doesn't exist!";
    return {false, Node::create_error(Error::Type::Parse, msg)};
  }

}

// call finalize() and node.delete
Node::OpStatus LispExpr::object_delete(Node&process, const Node::Vector &list, size_t start) {
  MYLOGGER(trace_function, "LispExpr::object_create(Node&process, Node::Vector&list, int start)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("list: ") + Node::_to_str(list), SLOG_FUNC_INFO+30);
  MYLOGGER_MSG(trace_function, string("start: ") + to_string(start), SLOG_FUNC_INFO+30);

  auto frame_ref_status = frame_current(process);
  auto scopes_ref_status = frame_ref_status.second[SCOPES];
  Node::Integer s = scopes_ref_status.second.size_container() ;

  for(Node::Integer i=s-1; i>=0; i--) {
    //auto scope_ref_status = scope_current(process);
    //cout << "symbol lookup i: " << i << "\n";
    auto scope_ref_status = scopes_ref_status.second[i];
    if(!scope_ref_status.first) {
      cerr << "scope lookup failed!" <<  scope_ref_status.second._to_str() << "\n";
      return {false, Node::create_error(Error::Type::InvalidOperation, "Object_delete(): Unknown error looking up scope")};
    }

    size_t s2 = list.size();
    for(size_t j=start; j<s2; j++) {
      string name = list[j]->_to_str();
      // cout << "deleting " << name << "\n";
  
      auto var_ref = var_lookup(scope_ref_status.second, name);
      if(var_ref.first)  {
        cout << "found var " << name<< "\n";
        if(Lisp::type(var_ref.second)==Lisp::Type::object) {
          cout << "It's an object var " << var_ref << "\n\n";
          object_finalize(process, var_ref.second);
          var_ref.second.delete_();
        }
        continue;

      }
      auto immute_ref = immute_lookup(scope_ref_status.second, name);
      if(immute_ref.first)  {
        cout << "found immute" << immute_ref << "\n";
        if(Lisp::type(immute_ref.second)==Lisp::Type::object) {
          cout << "It's an object immute" << immute_ref << "\n\n";
          object_finalize(process, immute_ref.second);
          var_ref.second.delete_();
        }
        continue;
      }
      cerr << "var '" << name <<"' not found!\n";
    }
  }

  return {true, Node::create(atom_ok, Node::Type::Atom)};
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
    =object.get_node(OBJ_INFO)
    .second.get_node(CLASS_PTR)
    .second.get_node(FUNCTION);

  auto object_uptr = Node::ptr_USU(object);

  if(!fun_ref_status.first) {
    cerr << "in send_object_Message(...) error looking up methods fun_ref_status: "  << fun_ref_status.second << "\n";
    return {false, fun_ref_status.second.clone()};
  }


  auto method_eval_status = eval(process, *list[start+1]);
  if(!method_eval_status.first) {
    cerr << "send object message() error with method name!\n";
    return {false, Node::create_error(Error::Type::Parse, "send object message() error with method name")};
  }

  auto method_name = atom_to_str(method_eval_status.second->_get_integer());
  auto argv_list = eval(process, list, start+1); // start+1 gets replace with this pointer. this returns a vector
  if(!argv_list.first){
    cerr << "send object message() argument eval failed !\n";
    return {false, Node::create_error(Error::Type::Parse, "send object message() argument eval failed !")};
  }

  argv_list.second->set(0, move(object_uptr)); // 0, was the :method name, and change it to object ptr 

  auto method_fun_ref = fun_ref_status.second.get_node(method_name);
  if(!method_fun_ref.first) {
    string msg = "send object message() method '" + method_name +  "' not found!";
    cerr << msg << "\n";
    return {false, Node::create_error(Error::Type::FunctionNotFound, msg)};
  }

  return call(process, method_fun_ref.second, move(argv_list.second->_get_vector_ref()));

}



//------------------------------------------------------------------------
// 2 parmas module.class
// 3 parmas module.class // to be worked on

/*
Node::OpStatusRef LispExpr::get_class(deque<string> mc) {
  MYLOGGER(trace_function, "LispExpr::get_class(list<string>mfc)", __func__, SLOG_FUNC_INFO);
  string mc_str = _to_str_ext(mc);
  MYLOGGER_MSG(trace_function, "mfc: " + mc_str  , SLOG_FUNC_INFO+30);
  //auto path = lisp_path_module;
  auto path = namespace_module_path();


  // class name string
  auto class_name = mc.back();
  mc.pop_back();

  path.push_back(join_str(mc, "."));
  path.push_back(_CLASS);

  path.push_back(class_name); 
  //cout << "getclass: path " << _to_str_ext(path) << "\n";



  auto node_ref_status = get_node(path);
  if(!node_ref_status.first)  {
    cerr << "Looking up class '"  << mc_str <<"' not found: "  << node_ref_status.second._to_str() << "\n";
    return node_ref_status;
  }
  return node_ref_status;


}
*/

//------------------------------------------------------------------------
// create a map object
// (map ( (k1 v1) (k2 v2) )) //creates a new map object
Node::OpStatus LispExpr::hash_create(Node&process, const Node::Vector &list_kv, size_t start) {
  MYLOGGER(trace_function, "LispExpr::hash_create(Node&process, Node::Vector&list_kv, int start)", __func__, SLOG_FUNC_INFO);
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
      cerr << "hash create, key,  error! "  <<  key_ref_status.second << "\n";
      return {false, key_ref_status.second.clone()};
    }

    auto const &value_ref_status = kv_pair->get_node(1);
    if(!value_ref_status.first) {
      cerr << "hash create, value, error! "  <<  value_ref_status.second << "\n";
      return {false, value_ref_status.second.clone()};
    }
    auto value_status = eval(process, value_ref_status.second);
    if(!value_status.first) {
      cerr << "hash create key,value eval pair error! "  <<  value_status << "\n";
      return value_status;
    }
    map[key_ref_status.second._to_str()] = move(value_status.second);

  }
  
  obj_info->set("type", Lisp::Type::hash );
  map[OBJ_INFO] = move(obj_info);

  return {true, Node::create(move(map))};
}

Node::OpStatus LispExpr::ihash_create(Node&process, const Node::Vector &list_kv, size_t start) {
  MYLOGGER(trace_function, "LispExpr::hash_create(Node&process, Node::Vector&list_kv, int start)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("list_kv: ") + Node::_to_str(list_kv), SLOG_FUNC_INFO+30);
  MYLOGGER_MSG(trace_function, string("start: ") + to_string(start), SLOG_FUNC_INFO+30);
  Node::IMap map;
  auto obj_info = make_unique<Node>(Node::Type::Map);

  if(list_kv.empty()) return {true, Node::create(Node::Type::Map)}; // empty map

  size_t  s = list_kv.size();
  for(size_t i=start; i<s; i++) {
    auto &kv_pair = list_kv[i];
    auto const &key_ref_status  = kv_pair->get_node(0);
    if(!key_ref_status.first) {
      cerr << "hash create, key,  error! "  <<  key_ref_status.second << "\n";
      return {false, key_ref_status.second.clone()};
    }

    auto const &value_ref_status = kv_pair->get_node(1);
    if(!value_ref_status.first) {
      cerr << "hash create, value, error! "  <<  value_ref_status.second << "\n";
      return {false, value_ref_status.second.clone()};
    }
    auto value_status = eval(process, value_ref_status.second);
    if(!value_status.first) {
      cerr << "hash create key,value eval pair error! "  <<  value_status << "\n";
      return value_status;
    }
    try {
    map[key_ref_status.second._get_integer()] = move(value_status.second);
    } catch(...) {
      cerr << "hash key error! "  <<  key_ref_status.second._to_str() << "\n";
      return {false, key_ref_status.second.clone()};
    }

  }
  
  obj_info->set("type", Lisp::Type::ihash );
  map[Lang::str_to_atom( OBJ_INFO)] = move(obj_info);
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

//------------------------------------------------------------------------
// (do (param_list) (code list))
Node::OpStatus LispExpr::closure_create(Node&process, const Node::Vector &list, size_t start){
  MYLOGGER(trace_function, "LispExpr::closure_create(Node::List& list)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("list: ") + Node::_to_str(list), SLOG_FUNC_INFO+30);

  size_t s = list.size();

  if(s<2) return {false, Node::create_error(Error::Type::Parse, "closure do() blcok requires atleast 2 parameters! " + Node::_to_str(list))};

  Node::Map map={}; 
  auto obj_info = make_unique<Node>(Node::Type::Map);

  map[_PARAMS] = list[start]->clone();
  map[CODE] =  Node::create(list_clone_remainder(list, start+1));
  obj_info->set("type",  Lisp::Type::do_);
  map[OBJ_INFO] = move(obj_info);
  
  return {true, Node::create(move(map))};

}


//------------------------------------------------------------------------
Node::Vector LispExpr::list_clone_remainder(const Node::Vector &list, size_t start) {
  Node::Vector result_list;
  size_t s = list.size();
  for(size_t i=start; i<s; i++) 
    result_list.push_back(list[i]->clone());
  return result_list;
}


//------------------------------------------------------------------------
bool LispExpr::forever = true;
Node::OpStatus LispExpr::loop_forever(Node& process, const Node::Vector& list, size_t start) {
  MYLOGGER(trace_function, "LispExpr::loop_forever(Node& process, const Vector, start)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("list: ") + Node::_to_str(list), SLOG_FUNC_INFO+30)
  MYLOGGER_MSG(trace_function, string("start: ") + to_string(start), SLOG_FUNC_INFO+30)
  size_t s= list.size();
  while(forever) {
    for(size_t i=start; i < s; i++) {
      auto &node = list[i];
      eval(process, *node);
    }
  }
  forever=true;
  return {true, Node::create()};
}

//------------------------------------------------------------------------
// (while (condition) (...))
//    (condition) with '()' prefix returns a vector
//    [condition] with '[]' infix returns a scalar
//        need to check if it's scalar or vector 

Node::OpStatus LispExpr::while_(Node& process, const Node::Vector& code_list, size_t start) {
  MYLOGGER(trace_function, "LispExpr::while_(Node& process, const Vector, start)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("code_list: ") + Node::_to_str(code_list), SLOG_FUNC_INFO+30)
  MYLOGGER_MSG(trace_function, string("start: ") + to_string(start), SLOG_FUNC_INFO+30)
  size_t s= code_list.size();
  bool condition;

  auto condition_status =  eval(process, *code_list[start]);

  if(!condition_status.first) {
    return {false, Node::create_error(Error::Type::Unknown, 
      "Unknown error in while loop!" + condition_status.second->_to_str())};
  }
  if(condition_status.second->type_ == Node::Type::Vector) {
    auto condition_status_inner = car(process, condition_status.second->_get_vector_ref(), 0);
    condition=condition_status_inner.second->_get_bool();
  } else
    condition=condition_status.second->_get_bool();

  while(condition) {

    for(size_t i=start+1; i < s; i++) {
      auto &node = code_list[i];
      auto value_status = eval(process, *node);
      // return is an object 
      if(value_status.second->type_ == Node::Type::Map) { // need to figure if need to call lambda closure
        switch(handle_cf_object(process, value_status.second->_get_map_ref())) {
        case Node::ControlFlow::cf_run: { break;}
        case Node::ControlFlow::cf_return:{ 
          //return  {true, Node::create(move(result_list))}; 
          //cout << "return value_status " << *value_status.second<< "\n";
          return  {true, move(value_status.second)};
        }
        default: {}
        }
      }
    }

    auto condition_status =  eval(process, *code_list[start]);

    //cout << "in while condition_status " <<  condition_status << "\n";

    if(!condition_status.first) {
      return {false, Node::create_error(Error::Type::Unknown, 
        "Unknown error in while loop!" + condition_status.second->_to_str())};
    }
    if(condition_status.second->type_ == Node::Type::Vector) {
      auto condition_status_inner = car(process, condition_status.second->_get_vector_ref(), 0);
      condition=condition_status_inner.second->_get_bool();
    } else
      condition=condition_status.second->_get_bool();

  }

  return {true, Node::create()};
}

//------------------------------------------------------------------------
//   0   1           2                  3
// (if (condition) (first_block...) (else_block...))
Node::OpStatus LispExpr::if_(Node& process, const Node::Vector& list, size_t start) {
  MYLOGGER(trace_function, "LispExpr::if_(Node& process, const Vector, start)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, "list: "+ Node::_to_str(list), SLOG_FUNC_INFO+30)
  MYLOGGER_MSG(trace_function, "start: " + to_string(start), SLOG_FUNC_INFO+30)
  MYLOGGER_MSG(trace_function, "num of blocks: " + to_string(list.size()),  SLOG_FUNC_INFO+30)

  size_t s= list.size(); bool condition;
  auto condition_status =  eval(process, *list[start]);

  //cout << "condition status: " << condition_status << "\n";


  if(!condition_status.first) {
    return {false, Node::create_error(Error::Type::Unknown, 
      "Unknown error in while loop!" + condition_status.second->_to_str())};
  }

  try { condition=condition_status.second->_get_bool(); } catch(...) {
    //cerr << "Error: if condition eval.  something went wrong maybe ()";
    //return{false, Node::create_error(Error::Type::Parse, "Error: if condition eval.  something went wrong maybe ()")};

    auto condition_status_inner = car(process, condition_status.second->_get_vector_ref(), 0);
    try {
      condition=condition_status_inner.second->_get_bool();
    } catch(...) {
      cerr << "Error: if condition eval.  something went wrong maybe ()";
      return{false, Node::create_error(Error::Type::Parse, "Error: if condition eval.  something went wrong maybe ()")};
    }
  }

  if(condition) {
    if(s>=3) {
      auto &first_block = list[start+1];
      if(first_block->type_ != Node::Type::Vector) {
        cerr << "something is up for the first if block ";
        return {false, Node::create_error(Error::Type::Parse, "If eval first block error!")};
      }
      return eval(process, *first_block);
      }
  } else {
    if(s==4) {
      auto &else_block = list[start+2];
      if(else_block->type_ != Node::Type::Vector) {
        cerr << "something is up for the first if block ";
        return {false, Node::create_error(Error::Type::Parse, "If eval else block error!")};
      }
      return eval(process, *else_block);
    }
  }
  return {true, Node::create()};

}



//------------------------------------------------------------------------



Node::OpStatus LispExpr::read_input() {
  MYLOGGER(trace_function, "LispExpr::read_input()", __func__, SLOG_FUNC_INFO);
  string input;

  try { input = interface->read(); } catch(...) { forever=false; return {true, Node::create()}; }
  
  //cout << "> "; getline(cin , input);

  //if(input == "exit") { forever = false; return {true, Node::create() }; }

  if(input=="") return { true, Node::create()};

  auto token_list = reader.tokenize( reader.tokenize_preprocess( input)); // list<Token> 
  auto parsed_tokens_status =  reader.parse(token_list); // parse 
  if(!parsed_tokens_status.first) {
    cerr << "error parsing string token: !"  << parsed_tokens_status.second->_to_str() <<" \n";
    return parsed_tokens_status;
  }

  auto tokens = Node::create(move(parsed_tokens_status.second->_get_list_ref())); // this extra step maybe uncessary in future
  auto input_code_status = parse_build(*tokens);

  //cout <<"from 'read' after tokenizing, input_code_status: " << input_code_status << "\n";
  return input_code_status;
}


Node::Vector LispExpr::list_to_vector(Node::List &&list) {
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
  size_t s =code_list.size();

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

Node::OpStatus LispExpr::lisp_object_return(Node&process, const Node::Vector &code_list, size_t start) {
  MYLOGGER(trace_function, "LispExpr::lisp_object_return(Node&process, Node::Vector& code_list, size_t start)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, "code_list: " + Node::_to_str(code_list), SLOG_FUNC_INFO+30)
  MYLOGGER_MSG(trace_function, "start: " + to_string(start), SLOG_FUNC_INFO+30)


  //cout << "return!\n";
  if(code_list.size() < 2) {
    auto msg = "return requires something to return. try return :ok!";
    cerr << msg << "\n";
    return {false, Node::create_error(Error::Type::Parse, msg) };
  }

  Node::Map map={}; 
  auto ret_status = eval(process, *code_list[start]);
  if(!ret_status.first) {
    cout << "Can't eval return value!\n";
    return ret_status;
  }
  map[RET_VALUE] = move(ret_status.second);

  auto obj_info = make_unique<Node>(Node::Type::Map);
  obj_info->set(TYPE,  Lisp::Type::return_);
  map[OBJ_INFO] = move(obj_info);
  
  return {true, Node::create(move(map))};

}

Node::ControlFlow LispExpr::handle_cf_object(Node&process, Node::Vector&result_list, const Node::Map& object) {
  MYLOGGER(trace_function, "LispExpr::handle_cf_object(Node&process, Node::Vector& result_list, Node::Map& object)", __func__, SLOG_FUNC_INFO);

   //cout << "returned map or object need to check if t needs to call lambda or closure!\n";
   //cout << "return object : " <<  Node::_to_str(object) << "\n";

   try {
    auto &object_info = object.at(OBJ_INFO);
    auto type = object_info->get_node(TYPE).second._get_lisp_op();

    switch(type) {
    case Lisp::Op::return_: {
      auto &return_value = object.at(RET_VALUE);
      //cout << "return value " << *return_value << "\n";
      result_list.push_back(return_value->clone());
      return Node::ControlFlow::cf_return;
    }
    default: {}
    }

   } catch(...) {
    // not an object just a map
    return Node::ControlFlow::cf_run;

   }
  return Node::ControlFlow::cf_run;

 }

Node::ControlFlow LispExpr::handle_cf_object(Node&process, const Node::Map& object) {
  MYLOGGER(trace_function, "LispExpr::handle_cf_object(Node&process, Node::Map& object)", __func__, SLOG_FUNC_INFO);
   try {
    auto &object_info = object.at(OBJ_INFO);
    auto type = object_info->get_node(TYPE).second._get_lisp_op();

    switch(type) {
    case Lisp::Op::return_: {
      //auto &return_value = object.at(RET_VALUE);
      //cout << "return value " << *return_value << "\n";
      return Node::ControlFlow::cf_return;
    }
    default: {}
    }

   } catch(...) {
    // not an cf object just a map
    return Node::ControlFlow::cf_run;
   }
   return Node::ControlFlow::cf_run;
}


Node::OpStatus LispExpr::cf_object_to_OpStatus(Node&process, unique_ptr<Node>object_ptr) {
  MYLOGGER(trace_function, "LispExpr::cf_object_to_OpStatus(Node&process, Node::Map& object)", __func__, SLOG_FUNC_INFO);
  if(object_ptr->type_ == Node::Type::Map) { // need to figure if need to call lambda closure
   try {
    //cout << "object_ptr " << *object_ptr << "\n";
    auto object_info_ref = object_ptr->get_node(OBJ_INFO);
     if(!object_info_ref.first) {
      cerr << "Cf_Object_to_opstatus () object error ";

      return {false, object_info_ref.second.clone() };
     }


    auto type = object_info_ref.second.get_node(TYPE).second._get_lisp_op();

    switch(type) {
    case Lisp::Op::return_: {
      auto return_value_ref = object_ptr->get_node(RET_VALUE);
      //cout << "return value " << *return_value << "\n";
      return {true, return_value_ref.second.clone()};
    }
    default: {}
    }

   } catch(...) {
    // not an cf object just a map
   return {true, object_ptr->back().second.clone()};
   }
  }
   return {true, object_ptr->back().second.clone()};
}

Node::ControlFlow LispExpr::handle_cf_object_return(Node&process, Node::Vector&result_list, const Node::Map& object) {
  return Node::ControlFlow::cf_return;
}

//------------------------------------------------------------------------
Node::OpStatus LispExpr::cond(Node& process, const Node::Vector& list, size_t start) {
  MYLOGGER(trace_function, "LispExpr::cond(Node& process, const Vector, start)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, "list: "+ Node::_to_str(list), SLOG_FUNC_INFO+30)
  MYLOGGER_MSG(trace_function, "start: " + to_string(start), SLOG_FUNC_INFO+30)

  size_t s=list.size(); bool condition;
  for(size_t i=start; i<s; i+=2) {
    
    auto &cond = list[i];
    auto &block = list[i+1];

    auto condition_status =  eval(process, *cond);

    try { condition=condition_status.second->_get_bool(); } catch(...) {
      //cerr << "Error: if condition eval.  something went wrong maybe ()";
      //return{false, Node::create_error(Error::Type::Parse, "Error: if condition eval.  something went wrong maybe ()")};
      try {
        auto condition_status_inner = car(process, condition_status.second->_get_vector_ref(), 0);
        condition=condition_status_inner.second->_get_bool();
        
      } catch(...) {
        cerr << "Error: if condition eval.  something went wrong maybe ()";
        return{false, Node::create_error(Error::Type::Parse, "Error: if condition eval.  something went wrong maybe ()")};
      }
    }

    if(condition) {
      return eval(process, *block);
    }

  }

  return  {true, Node::create()};
}

//------------------------------------------------------------------------
Node::OpStatus LispExpr::match(Node& process, const Node::Vector& list, size_t start) {
  MYLOGGER(trace_function, "LispExpr::cond(Node& process, const Vector, start)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, "list: "+ Node::_to_str(list), SLOG_FUNC_INFO+30)
  MYLOGGER_MSG(trace_function, "start: " + to_string(start), SLOG_FUNC_INFO+30)

  size_t s=list.size(); bool condition;
  auto &rhs  = list[start];

  for(size_t i=start+1; i<s; i+=2) {
    Node::Vector assign_code_list;
    assign_code_list.reserve(s);
    string head_str="";

    auto &lhs = list[i];
    auto &block = list[i+1];
    assign_code_list.push_back(Node::create(Lisp::Op::assign));
    assign_code_list.push_back(lhs->clone());
    assign_code_list.push_back(rhs->clone());
    //cout << "= " << *lhs << " "  << *rhs << "-->" << *block << "\n";
    try {
      auto  &lhs_head = lhs->_get_vector_ref()[0];
      head_str = lhs_head->_to_str();
    } catch(...) {}

    if(head_str == "_"){
      condition = true;
    } else {
      auto  condition_status =  assign_attach(process, assign_code_list, 1);

      try { condition=condition_status.second->_get_bool(); } catch(...) {
        try {
          auto condition_status_inner = car(process, condition_status.second->_get_vector_ref(), 0);
          condition=condition_status_inner.second->_get_bool();
          
        } catch(...) {
          cerr << "Error: if condition eval.  something went wrong maybe ()";
          return{false, Node::create_error(Error::Type::Parse, "Error: if condition eval.  something went wrong maybe ()")};
        }
      }
    }

    if(condition) {
      return eval(process, *block);
    }
  }
  return  {true, Node::create()};
}

//------------------------------------------------------------------------
Node::OpStatus LispExpr::case_(Node& process, const Node::Vector& list, size_t start) {
  MYLOGGER(trace_function, "LispExpr::case(Node& process, const Vector, start)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, "list: "+ Node::_to_str(list), SLOG_FUNC_INFO+30)
  MYLOGGER_MSG(trace_function, "start: " + to_string(start), SLOG_FUNC_INFO+30)

  size_t s=list.size(); bool condition;
  // auto &rhs  = list[start];
  auto rhs_status  = eval(process, *list[start]);

  if(!rhs_status.first) {
    auto msg = "case (x): x evaled to error";
    cerr << msg  << "\n";
    return {false, Node::create_error(Error::Type::Parse, msg)};
  }

  auto &rhs = rhs_status.second;


  for(size_t i=start+1; i<s; i+=2) {
    Node::Vector case_code_list;
    case_code_list.reserve(s);

    string head_str="";


    auto &lhs= list[i]->_get_vector_ref()[0];

    auto &block = list[i+1];

    case_code_list.push_back(Node::create(Lisp::Op::eq));
    case_code_list.push_back(lhs->clone());
    case_code_list.push_back(rhs->clone());

    head_str = lhs->_to_str();

    if(head_str == "_"){
      condition = true;
    } else {
      auto  condition_status =  eval(process, Lisp::Op::eq,  case_code_list, 1);

      try { condition=condition_status.second->_get_bool(); } catch(...) {
        try {
          auto condition_status_inner = car(process, condition_status.second->_get_vector_ref(), 0);
          condition=condition_status_inner.second->_get_bool();
          
        } catch(...) {
          cerr << "Error: if condition eval.  something went wrong maybe ()";
          return{false, Node::create_error(Error::Type::Parse, "Error: if condition eval.  something went wrong maybe ()")};
        }
      }
    }

    if(condition) {
      return eval(process, *block);
    }
  }
  return  {true, Node::create()};
}