#include <iostream>
#include "lisp_expr.hh"

#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"



/*
Node::OpStatus LispExpr::car(Node&process, const Node::Vector &list, int start) {
  MYLOGGER(trace_function, "LispExpr::car(Node&process, Node::Vector&list)", __func__, SLOG_FUNC_INFO)
  MYLOGGER_MSG(trace_function, string("list: ") + Node::_to_str(list), SLOG_FUNC_INFO+30)
  MYLOGGER_MSG(trace_function, string("start: ") + to_string(start), SLOG_FUNC_INFO+30)

  //if(list.empty()) return {false, Node::create_error(Error::Type::EmptyContainer, "Empty List front()!")};
  if(list.empty()) return {true, Node::create()}; // return null
  auto &head = list[start];
  switch(head->type_) {
  case Node::Type::Identifier: {
    auto name = get<string>(head->value_);

    auto rv_ref_status = symbol_lookup(process, name  );
    if(!rv_ref_status.first) {
      cerr << "Lisp::car error symbol '"  <<   name << "' lookup " << rv_ref_status.second << "\n";
      return {false, rv_ref_status.second.clone()};
    }
    if(rv_ref_status.second.type_==Node::Type::Vector){
      auto &rlist = get<Node::Vector>(rv_ref_status.second.value_);
      return {true, rlist[0]->clone()};
    }
    return {true, rv_ref_status.second.clone()};

  }
  case Node::Type::Vector: {
    auto &rlist = get<Node::Vector>(head->value_);
    auto rv_status = eval(process, rlist);
    if(!rv_status.first) {
      cerr << "Error encounter in lisp::car vector " << rv_status << "\n";
      return rv_status;
    }
    if(rv_status.second->type_== Node::Type::Vector) {
      if(rv_status.second->empty_container()) return {true, Node::create()};
      auto rv_front_status = rv_status.second->front();
      if(!rv_front_status.first) {
        cerr << "Error encounter in lisp::car vector front " << rv_status << "\n";
        return {false,  rv_front_status.second.clone()};
      }
      return {true, rv_front_status.second.clone()};
    }
    return rv_status;

  }
  default: {

  }}
  cout << "car last outside switch!\n";
  return {true, head->clone()};

}
*/

Node::OpStatus LispExpr::car(Node&process, const Node::Vector &list, int start) {
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

Node::OpStatus LispExpr::cdr(Node&process, const Node::Vector &list, int start) {
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
Node::OpStatus LispExpr::literal(const Node::Vector &list, int start) {
  MYLOGGER(trace_function, "LispExpr::literal(const Node::Vector&list, int start)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, "start: " + start, SLOG_FUNC_INFO+30);
  Node::Vector list_result;
  size_t s=list.size();
  for(size_t i=start; i<s; i++) 
    list_result.push_back(list[i]->clone());
  return {true, Node::create(move(list_result))};
}

//------------------------------------------------------------------------
// create a map object
// (map ( (k1 v1) (k2 v2) )) //creates a new map object
Node::OpStatus LispExpr::map_create(Node&process, const Node::Vector &list_kv, int start) {
  MYLOGGER(trace_function, "LispExpr::map_create(Node&process, Node::Vector&list_kv, int start)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("list_kv: ") + Node::_to_str(list_kv), SLOG_FUNC_INFO+30);
  MYLOGGER_MSG(trace_function, string("start: ") + to_string(start), SLOG_FUNC_INFO+30);
  Node::Map map;
  auto map_ = make_unique<Node>(Node::Type::Map);

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
  map[OBJ_INFO] = make_unique<Node>(Node::Type::Map);


  //cout << "map " << Node::_to_str( map) << "\n";
  return {true, Node::create(move(map))};
}

// handling messages for map
/*
Node::OpStatus LispExpr::map_messages(Node&process, const Node::Vector &list, int start) {
  MYLOGGER(trace_function, "LispExpr::map_messages(Node&process, Node::Vector&list_kv, int start)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("list: ") + Node::_to_str(list), SLOG_FUNC_INFO+30);
  MYLOGGER_MSG(trace_function, string("start: ") + to_string(start), SLOG_FUNC_INFO+30);
  auto &head = list[start];
  auto &args = list[start+1];
  switch(head->type_) {
  case Node::Type::Identifier: {
    auto name_var = head->_to_str();
    auto const &fun_name_ref_status = args->get_node(0);

    auto value_ref_status = symbol_lookup(process, head->_to_str());
    if(!value_ref_status.first) {
      cerr << "error sending message to object" + name_var + "  lookup up failed";
      return{false, Node::create_error(Error::Type::SymbolNotFound, "error sending message to object" + name_var + "  lookup up failed")};
    }
    if(!fun_name_ref_status.first) {
      cerr << "args.. error sending message: " 
      +  fun_name_ref_status.second._to_str() 
      + " to object" + name_var + "  lookup up failed";
      return{false, Node::create_error(Error::Type::SymbolNotFound, "error sending message: "
      +  fun_name_ref_status.second._to_str() 
      + " to object" + name_var + "  lookup up failed:")};
    }
    auto method_path = cc_path_module;
    method_path.push_back(fun_name_ref_status.second._to_str());
    auto fun_method_ref_status = get_node(method_path);
    if(!fun_method_ref_status.first) {
      cerr << "method function not found!" <<   fun_name_ref_status.second._to_str();
      return{false, Node::create_error(Error::Type::FunctionNotFound, "method function not found") };
    }

    Node::Fun method_fun = get<Node::Fun>(fun_method_ref_status.second.value_);
    auto result_status = method_fun(process, value_ref_status.second, {});



    cout << "Identerier: " <<  head->_to_str() << "\n";
    cout << "value : " <<  value_ref_status << "\n";
    cout << "args : " <<  *args << "\n";
    cout << "funrefstatus: " <<  fun_name_ref_status<< "\n";
    cout << "resultstat: " <<  result_status <<  "\n";

  }
  default: {}

  }
  return {true, nullptr};

}
  */
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
Node::OpStatus LispExpr::map_get_value(Node&process, Node &node, const Node::Vector& args) {
  MYLOGGER(trace_function, "LispExpr::map_get_value(Node&process, const Node& node, const Vector& args)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("node: ") + node._to_str(), SLOG_FUNC_INFO+30);
  MYLOGGER_MSG(trace_function, string("args: ") + Node::_to_str(args), SLOG_FUNC_INFO+30);

  auto &key = args[0];

  if(key->type_ != Node::Type::String) 
    return {false, Node::create_error(Error::Type::IndexWrongType, "key is not a string!")};
  string key_str = key->_to_str();


  switch(node.type_) {
  case Node::Type::Map: {
    auto &map = get<Node::Map>(node.value_);
    for(const auto& kv : map) 
      if(kv.first == key_str) return {true, Node::create(kv.second->clone())};
    return {false, Node::create_error(Error::Type::KeyNotFound, "Key : '"  + key_str +"' not found!")};
  }
  case Node::Type::Shared: {
    auto &map_ptr = get<Node::ptr_S>(node.value_);
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
  MYLOGGER(trace_function, "LispExpr::map_get_value(Node&process, const Node& node, const Vector& args)", __func__, SLOG_FUNC_INFO);
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
    return {true, nullptr};
  }
  case Node::Type::Shared: {
    auto &map_ptr = get<Node::ptr_S>(node.value_);
    auto &map= get<Node::Map>(map_ptr->value_);
    map[key_str] = value_ptr->clone();
    return {true, nullptr};
  }
  default: 
    return {false, Node::create_error(
    Error::Type::IndexWrongType, 
    "map get keys and but type is not map, type: "+  Node::_to_str(node.type_))};
  }
}
//------------------------------------------------------------------------


