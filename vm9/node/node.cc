#include <iostream>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <type_traits>
#include "node.hh"
#include "defs.hh"
#include "lisp.hh"

#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"

Node null_node(Node::Type::Null);
Node node_null(Node::Type::Null);
Node node_error;
//unordered_map<Node::Integer , string> Atoms;


unique_ptr<Node> Node::create() { return make_unique<Node>(); }
unique_ptr<Node> Node::create(Value v) { return make_unique<Node>(move(v)); }
unique_ptr<Node> Node::create(Value v, Type t) { return make_unique<Node>(move(v), t); }
unique_ptr<Node> Node::create(Type t) { 
  switch(t) {
  case Type::IMap: {
    Node::IMap im;
    return make_unique<Node>(move(im));
  }
  case Type::Map: {
    Node::Map m;
    return make_unique<Node>(move(m));
  }
  case Type::List: {
    Node::List l;
    return make_unique<Node>(move(l));
  }
  case Type::Vector: {
    Node::Vector v;
    v.reserve(10);
    return make_unique<Node>(move(v));
  }
  case Type::DeQue: {
    Node::DeQue q;
    return make_unique<Node>(move(q));
  }
  default: return make_unique<Node>();}
//  throw std::runtime_error("Unsupported Node::create() type" + _to_str(t)); 

  return make_unique<Node>();

}

Node::Node() 
  : value_(std::monostate{})
  , type_(Type::Null)
  {}

bool Node::is_nil() {
  return type_ == Type::Null ? true : false;
}

Node::Node(ptr_S ptr) {value_ = ptr; type_ = Type::Shared;}
Node::Node(ptr_R ptr) {value_ = ptr; type_ = Type::Raw;}
Node::Node(ptr_U ptr) {value_ = move(ptr); type_ = Type::Unique;}
Node::Node(Fun f) {value_ = move(f); type_ = Type::Fun;}

Node::Node(Value v , Type t) : value_(move(v)), type_(t) {}

Node::Node(Value v)
  : value_(move(v)) {

  type_ = visit([](auto&& inner_arg) -> Type {
    using U = decay_t<decltype(inner_arg)>;
    if constexpr (is_same_v<U, monostate>) return Type::Null;
    else if constexpr (is_same_v<U, bool>) return Type::Bool;
    else if constexpr (is_same_v<U, Error>) return Type::Error;
    else if constexpr (is_same_v<U, Integer>) return Type::Integer;
    else if constexpr (is_same_v<U, Float>) return Type::Float;
    else if constexpr (is_same_v<U, Lisp::Op>) return Type::LispOp;
    else if constexpr (is_same_v<U, ProcState>) return Type::ProcState;
    else if constexpr (is_same_v<U, ControlFlow>) return Type::ControlFlow;
    else if constexpr (is_same_v<U, string>) return Type::String;
    else if constexpr (is_same_v<U, List>) return Type::List;
    else if constexpr (is_same_v<U, Vector>) return Type::Vector;
    else if constexpr (is_same_v<U, DeQue>) return Type::DeQue;
    else if constexpr (is_same_v<U, Map>) return Type::Map;
    else if constexpr (is_same_v<U, IMap>) return Type::IMap;
    else if constexpr (is_same_v<U, ptr_R>) return Type::Raw;
    else if constexpr (is_same_v<U, ptr_S>) return Type::Shared;
    else if constexpr (is_same_v<U, ptr_U>) return Type::Unique;
    else if constexpr (is_same_v<U, Fun>) return Type::Fun;
    return Type::Null;
  //}, get<Value>(this->value));
  }, value_);
}
Node::Node(Type t)
  : type_(t) {
  switch(t) {
  case Type::Null: value_= {}; break;
  case Type::Bool: value_=true; break;
  case Type::Integer: value_=0; break;
  case Type::Float: value_=0.0; break;
  case Type::String: value_=""; break;
  //case Type::Error: value_ = {} ; break;
  case Type::Error: value_ = Error{Error::Type::Unknown, "Unknown Init"} ; break;
  case Type::Map: { 
    Map nm={};
    value_ = move(nm);
    break;}
  case Type::IMap: { 
    IMap nm={};
    value_ = move(nm);
    break;}

  case Type::List: { 
    List l={};
    value_ = move(l);
    break;}
  case Type::Vector: { 
    Vector l={};
    value_ = move(l);
    break;}
  case Type::DeQue: { 
    DeQue l={};
    value_ = move(l);
    break;}
  default: {
    value_ = monostate{};
    type_ = Type::Null;

  }}
}


unique_ptr<Node> Node::create_error(Error::Type t, const string& msg) {
  return make_unique<Node>(Value(Error{t, msg}));
}

unique_ptr<Node> Node::clone(const List& list) {
  MYLOGGER(trace_function, "Node::clone(const List&)", __func__, SLOG_NODE_OP);
  List cloned_list;
  for(const auto& child_ptr :list ) 
    cloned_list.push_back(child_ptr->clone());
  return create(move(cloned_list));
}

unique_ptr<Node> Node::clone(const DeQue& list) {
  MYLOGGER(trace_function, "Node::clone(const DeQue&)", __func__, SLOG_NODE_OP);
  DeQue cloned_list;
  for(const auto& child_ptr :list ) 
    cloned_list.push_back(child_ptr->clone());
  return create(move(cloned_list));
}
unique_ptr<Node> Node::clone(const Vector& list) {
  MYLOGGER(trace_function, "Node::clone(const Vector&)", __func__, SLOG_NODE_OP);
  Vector cloned_list;
  for(const auto& child_ptr :list ) 
    cloned_list.push_back(child_ptr->clone());
  return create(move(cloned_list));
}
unique_ptr<Node> Node::clone(const Fun& f) {
  //return create(make_shared<Node>(f));
  return make_unique<Node>(f);
}




unique_ptr<Node> Node::clone(const Map& map) {
  MYLOGGER(trace_function, "Node::clone(const Map&map)", __func__, SLOG_NODE_OP);

  Map cloned_map;
  for(const auto& [key, child_ptr] : map) {
    if(key == CLASS_PTR) continue;      // prevent recursive cloning since class function contain  ptr to class itself
    if(key == MODULE_PTR) continue;
    cloned_map.try_emplace(key, child_ptr->clone());
  }
  return create(move(cloned_map));
}

unique_ptr<Node> Node::clone(const IMap& map) {
  MYLOGGER(trace_function, "Node::clone(const IMap&map)", __func__, SLOG_NODE_OP);

  IMap cloned_map;
  for(const auto& [key, child_ptr] : map) {
    cloned_map.try_emplace(key, child_ptr->clone());
  }
  return create(move(cloned_map));
}


unique_ptr<Node> Node::clone() const {
  MYLOGGER(trace_function, "Node::clone()", __func__, SLOG_NODE_OP);

  if(holds_alternative<monostate>(value_)) 
    return make_unique<Node>();

  return visit([&](auto&& arg) -> unique_ptr<Node> {
    using T = decay_t<decltype(arg)>;
    if constexpr(is_same_v<T, monostate>)
      return make_unique<Node>(Node());
    else if constexpr(is_same_v<T, Error>) {
      // return make_unique<Node>(Value(arg));
      return make_unique<Node>(arg);
    }
    else if constexpr(
      is_same_v<T, Integer> || is_same_v<T, Float> ||  is_same_v<T, bool>||
      is_same_v<T, string> || is_same_v<T, Lisp::Op> || is_same_v<T, ProcState> || is_same_v<T, ControlFlow>) {
      //return Node::create(Value(arg));
      auto node_ptr = create(arg);
      node_ptr->type_ = type_;
      if(type_ == Type::Identifier) node_ptr->set_identifier();
      if(type_ == Type::Atom) node_ptr->set_atom();
      if(type_ == Type::ObjectId) node_ptr->set_object_id();
      return node_ptr;
    }

    else if constexpr(is_same_v<T, List>) {
      return clone(arg);
    }
    else if constexpr(is_same_v<T, Vector>) {
      return clone(arg);
    }
    else if constexpr(is_same_v<T, DeQue>) {
      return clone(arg);
    }
    else if constexpr(is_same_v<T, Map>) {
      return clone(arg);
    }
    else if constexpr(is_same_v<T, IMap>) {
      return clone(arg);
    }
    else if constexpr(is_same_v<T, ptr_S>) {
      return arg->clone();
    }
    else if constexpr(is_same_v<T, ptr_U>) {
      return arg->clone();
    }
    else if constexpr(is_same_v<T, ptr_R>) {
      return arg->clone();
    }
    else if constexpr(is_same_v<T, Fun>) {
      return clone(arg);
    }
  }, value_);
}

// _get
bool Node::_get_bool() const { return get<bool>(value_); }
Lisp::Op Node::_get_lisp_op() const { return get<Lisp::Op>(value_); }
Node::Integer Node::_get_integer() const { return get<Integer>(value_); }
Node::Float Node::_get_float() const { return get<Float>(value_); }
string Node::_get_str() const { return _to_str(); }
Node::Map& Node::_get_map_ref() { 

  switch(type_) {
  case Type::Shared: {
    auto sptr = get<ptr_S>(value_);
    return sptr->_get_map_ref(); }
  case Type::Raw: {
    auto sptr = get<ptr_R>(value_);
    return sptr->_get_map_ref(); }
  case Type::Unique:  {
    auto &sptr = get<ptr_U>(value_);
    return sptr->_get_map_ref(); }
  default: {}
  }
  
  return get<Map>(value_); 

}

Node::Vector& Node::_get_vector_ref() { 
  switch(type_) {
  case Type::Shared: {
    auto sptr = get<ptr_S>(value_);
    return sptr->_get_vector_ref(); }
  case Type::Raw: {
    auto sptr = get<ptr_R>(value_);
    return sptr->_get_vector_ref(); }
  case Type::Unique:  {
    auto &sptr = get<ptr_U>(value_);
    return sptr->_get_vector_ref(); }
  default: {}
  }
  return get<Vector>(value_); 
}

Node::List& Node::_get_list_ref() { return get<List>(value_); }

// eval list
Node::OpStatus Node::eval(Node& env) {
  return {true, clone()};
}
//------------------------------------------------------------------------
bool Node::delete_() {
  MYLOGGER(trace_function, "Node::delete_()", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, "type: " + Node::_to_str(type_), SLOG_FUNC_INFO+30);
  switch(type_) {
  case Type::Shared: {
    cout << "delete_(): resetting shared pointer, val: " << _to_str() <<"\n";
    auto sptr = get<ptr_S>(value_);
    sptr->delete_(); 
    sptr.reset();
    value_ = monostate{};
    type_ = Type::Null;
    return true;
  }
  case Type::Raw: {
    cout  << "delete_(): resetting raw pointer, val: " << _to_str() <<"\n";
    auto rptr = get<ptr_R>(value_);
    rptr->delete_(); 
    value_ = monostate{};
    type_ = Type::Null;
    return true;
  }
  case Type::Unique:  {
    cout  << "delete_(): resetting unique pointer, val: " << _to_str() <<"\n";
    auto &uptr = get<ptr_U>(value_);
    if(uptr->type_ == Type::Shared || uptr->type_ == Type::Raw || uptr->type_ ==Type::Unique) { uptr->delete_(); }
    uptr.reset();
    value_ = monostate{};
    type_ = Type::Null;
    return true;
  }
  default: {}}
  value_ = monostate{};
  type_ = Type::Null;
  //cerr << "not a node pointing to an object!\n";
  return true;

}


//------------------------------------------------------------------------

void Node::set(Integer v)  { *this = Node(v); }
void Node::set(Float v)  { *this = Node(v); }
void Node::set(Lisp::Op v)  { *this = Node(v); }
void Node::set(ProcState v)  { *this = Node(v); }
void Node::set(ControlFlow v)  { *this = Node(v); }
void Node::set(const string& v) { *this = Node(v); }
void Node::set(List v) { *this = Node(Value(move(v))); }
void Node::set(Map v) { *this = Node(Value(move(v))); }
void Node::set(IMap v) { *this = Node(Value(move(v))); }
void Node::set(unique_ptr<Node> new_node) {
  if(!new_node) {
    set_null();
  } else {
    this->value_ = move(new_node->value_);
    this->type_ = new_node->type_;
  }
}

Node::Type Node::_get_type() const { return type_; }
Node Node::get_type() const { return type_; }

void Node::set_null() { this->value_ = monostate{}; type_=Type::Null; }
void Node::set_atom(Integer v)  { *this = Node(v); type_ = Type::Atom; }
void Node::set_atom()  { type_ = Type::Atom; }

void Node::set_object_id(Integer v)  { *this = Node(v); type_ = Type::ObjectId; }
void Node::set_object_id()  { type_ = Type::ObjectId; }


void Node::set_identifier(const string& v) { *this = Node(v); type_ = Type::Identifier; }
void Node::set_identifier() { type_ = Type::Identifier; }

Node::OpStatus Node::set(size_t index, unique_ptr<Node> child) {
  if(type_ != Type::Vector) 
    return {false, create_error(Error::Type::InvalidOperation, "Cannot set index on a non-List node.")};

  Vector &list = get<Vector>(value_);
  if(index >= list.size()) {
    ostringstream msg;
    msg << "Index " << index << " is out of bounds for list size " << list.size() << ".";
    return {false, create_error(Error::Type::IndexOutOfBounds, msg.str())};
  }
  list[index] = move(child);
  return {true, create(true)};
}

Node::OpStatus Node::set(const string&key, unique_ptr<Node> child) {
  if (type_ != Type::Map) {
    return {false, create_error(Error::Type::InvalidOperation, "Cannot set key on a non-Map node.")};
  }        
  Map& map= get<Map>(value_);
  map[key] = move(child);
  return {true, create(true)};
}

//
// set_imap for Integer, Atom IMap
//
Node::OpStatus Node::set_imap(Integer key, unique_ptr<Node> child) {
  if (type_ != Type::Map) {
    return {false, create_error(Error::Type::InvalidOperation, "Cannot set key on a non-Map node.")};
  }        
  IMap& map= get<IMap>(value_);
  map[key] = move(child);
  return {true, create(true)};
}


Node::OpStatus Node::set(const string&key, ptr_R child) {
  if (type_ != Type::Map) {
    return {false, create_error(Error::Type::InvalidOperation, "Cannot set key on a non-Map node.")};
  }        
  Map& map= get<Map>(value_);
  map[key] = Node::create(child);
  return {true, create(true)};
}



//Node::OpStatus Node::set(size_t index, Integer v) { return set(index, Node::create(Value(v))); }
Node::OpStatus Node::set(size_t index, Integer v) { return set(index, create(v)); }
Node::OpStatus Node::set(size_t index, Float v) { return set(index, create(v)); }
Node::OpStatus Node::set(size_t index, const string&v ) { return set(index, create(v)); }

Node::OpStatus Node::set(const string&key, Integer v ) { return set(key, create(v)); }
Node::OpStatus Node::set(const string&key, Float v ) { return set(key, create(v)); }
Node::OpStatus Node::set(const string&key, Lisp::Op v ) { return set(key, create(v)); }
Node::OpStatus Node::set(const string&key, ProcState v ) { return set(key, create(v)); }
Node::OpStatus Node::set(const string&key, ControlFlow v ) { return set(key, create(v)); }
Node::OpStatus Node::set(const string&key, const string&v ) { return set(key, create(v)); }
//Node::OpStatus Node::set_null(const string& key) { return set(key, create()); }


Node::Node(vector<ValueSimple> vl) : type_(Type::List) {
  //cout << "In node:: set:: vector<ValueSimple> \n";
  List list;
  //value = List{};
  //List list = get<List>(value);
  for(auto &v : vl ) { 
    auto ptr = visit([](auto&& arg) -> unique_ptr<Node> {
      using T = decay_t<decltype(arg)>;
      if constexpr (is_same_v<T, monostate>) return make_unique<Node>();
      else if constexpr (is_same_v<T, Error>) return make_unique<Node>(arg);
      else if constexpr (is_same_v<T, Integer>) { 
        //cout << "int arg: " << arg << "\n";
        return create(arg);
      }
      else if constexpr (is_same_v<T, Float>) {
        //cout << "float arg: " << arg << "\n";
        return make_unique<Node>(arg); 
      }
      else if constexpr (is_same_v<T, Lisp::Op>) {
        //cout << "LispOp:  \n";
        return make_unique<Node>(arg); 
      }
      else if constexpr (is_same_v<T, string>) {
        //cout << "string arg: " << arg << "\n";
        return make_unique<Node>(arg); 
      }
      /*
      else if constexpr (is_same_v<T, List>) { 
        //cout << "list:  \n"; //return make_unique<Node>(move(arg)); 
        return make_unique<Node>(arg); 
      }
      else if constexpr (is_same_v<T, Map>) {  
        //cout << "map:  \n"; //return make_unique<Node>(move(arg)); }
        return make_unique<Node>(arg); }
      */
      else {
        ////cout << "unknown arg: " << arg << "\n";
        return make_unique<Node>(); 
      }
    }, v);
    //cout << "node::set list size.size()" <<  list.size() << "\n";
    list.push_back(move(ptr));
  }
  value_ = move(list);
  //Node(move(list));
  //cout << "list:beg " << "\n";
  //print_value_recursive(*this, 0);
  //cout << "list:end " << "\n";
}

Node::OpStatus Node::add(unique_ptr<Node> child) {
  if(type_ != Type::List) 
    return {false, create_error(Error::Type::InvalidOperation, "Cannot add element to a non-List node.")};

  List& list = get<List>(value_);
  list.push_back(move(child));
  return {true, nullptr};
}

Node::OpStatus Node::add(const string&key, unique_ptr<Node> child) {
  if (type_ != Type::Map) {
    return {false, create_error(Error::Type::InvalidOperation, "Cannot add key-value to a non-Map node.")};
  }        
  Map& map = get<Map>(value_);

  if(!map.try_emplace(key, std::move(child)).second) {
    return {false, create_error(Error::Type::KeyAlreadyExists, "Key '" + key + "' already exists in map.")};
  }
  return {true, nullptr};
}


Node::OpStatus Node::delete_key(const string &key) {
  if(type_ != Type::Map)
    return {false, create_error(Error::Type::InvalidOperation, "Cannot delete key on a non-Map node.")};

  Map& map = get<Map>(value_);
  if(map.erase(key)==0)
    return {false, create_error(Error::Type::InvalidOperation,  "Key '" + key + "' not found in map.")};
  return {true, nullptr};
}

Node::OpStatus Node::delete_key(Integer key) {
  if(type_ != Type::IMap)
    return {false, create_error(Error::Type::InvalidOperation, "Cannot delete key on a non-Map node.")};

  IMap& map = get<IMap>(value_);
  if(map.erase(key)==0)
    return {false, create_error(Error::Type::InvalidOperation,  "Key '" + to_string( key) + "' not found in map.")};
  return {true, nullptr};
}

//------------------------------------------------------------------------
//--------------------------------
Node::OpStatus Node::pop_back() {
  MYLOGGER(trace_function, "Node::pop_back()", __func__, SLOG_NODE_OP);
  MYLOGGER_MSG(trace_function, "type: " + _to_str(type_), SLOG_NODE_OP+ 30);

  return visit([&](auto&& list) -> OpStatus {
    using T = decay_t<decltype(list)>;
    if constexpr (is_same_v<T, List>  || is_same_v<T, DeQue> || is_same_v<T, Vector>){
      if(list.empty()) { return {false, 
        create_error(Error::Type::InvalidOperation, "Cannot pop_back from an empty List or DeQue node.")};};
      auto back = move(list.back());
      list.pop_back();
      return {true, move(back)};
    } else {
      return {false, create()};
    }
  }, value_);
  return {false, create()};
}

//--------------------------------
Node::OpStatus Node::pop_front() {
  MYLOGGER(trace_function, "Node::pop_front()", __func__, SLOG_NODE_OP);
  MYLOGGER_MSG(trace_function, "type: " + _to_str(type_), SLOG_NODE_OP+30);

  return visit([&](auto&& list) -> OpStatus {
    using T = decay_t<decltype(list)>;
    if constexpr (is_same_v<T, List>  || is_same_v<T, DeQue>){
      if(list.empty()) { return {false, 
        create_error(Error::Type::InvalidOperation, "Cannot pop_front from an empty List or DeQue node.")};};
      auto front = move(list.front());
      list.pop_front();
      return {true, move(front)};

    } else if constexpr (is_same_v<T, Vector>){
      cerr << "Warning!: Node::pop_front() with vector object\n";
      if(list.empty()) { return {false, 
        create_error(Error::Type::InvalidOperation, "Cannot pop_front from an empty Vector node.")};};
      auto front = move(list.front());
      list.erase(list.begin());
      return {true, move(front)};
      
    } else {
      return {false, create()};
    }
  }, value_);
  return {false, create()};
}

//--------------------------------
Node::OpStatus Node::push_back(unique_ptr<Node> node) {
  MYLOGGER(trace_function, "Node::push_back()", __func__, SLOG_NODE_OP);
  MYLOGGER_MSG(trace_function, "type: " + _to_str(type_) + ": node value: " + node->_to_str(), SLOG_NODE_OP+30);

  return visit([&](auto&& list) -> OpStatus {
    using T = decay_t<decltype(list)>;
    if constexpr (is_same_v<T, List>  || is_same_v<T, DeQue> || is_same_v<T, Vector>){
      list.push_back(move(node));
      return {true, create()};
    } else {
      return {false, create_error(Error::Type::InvalidOperation, "push_back() current node is not list, deque or vector !")};
    }
  }, value_);
  return {false, create_error(Error::Type::InvalidOperation, "push_back() current node is not list, deque or vector !")};
}



Node::OpStatus Node::push_front(unique_ptr<Node> node) {
  MYLOGGER(trace_function, "Node::push_back()", __func__, SLOG_NODE_OP);
  MYLOGGER_MSG(trace_function, "type: " + _to_str(type_) + ": node value: " + node->_to_str(), SLOG_NODE_OP+30);

  return visit([&](auto&& list) -> OpStatus {
    using T = decay_t<decltype(list)>;
    if constexpr (is_same_v<T, List>  || is_same_v<T, DeQue> ){
      list.push_front(move(node));
      return {true, create()};
    }  else if constexpr(is_same_v<T, Vector>) {
      cerr << "Warning!: Node::push_front() with vector object\n";
      list.insert(list.begin(), move(node));
      return {true, create()};
    } else {
      return {false, create_error(Error::Type::InvalidOperation, "push_back() current node is not list, deque or vector !")};
    }
  }, value_);
  return {false, create_error(Error::Type::InvalidOperation, "push_back() current node is not list, deque or vector !")};
}


//------------------------------------------------------------------------
// Equivalent to std::vector::clear
Node::OpStatus Node::clear() {
  if (type_ != Type::List) {
    return {false, create_error(Error::Type::InvalidOperation, "Cannot clear a non-List node.")};
  }
  List& list = get<List>(value_);
  list.clear();
  return {true, nullptr}; // Success
}


// --- Overloaded Square Bracket Operators (Read-only access) ---

/**
 * @brief Accesses an element in a List node by index. Returns a clone of the Node via OpStatus.
 */

Node::OpStatusRef Node::operator[](size_t index) {
  if(type_ != Type::Vector) {
    return { false,
    Error::ref(
      Error::Type::InvalidOperation,
      "Operator[] (index) can only be used on vector nodes. Current type: " + _to_str(type_)
    )};
  }
  Vector& list = get<Vector>(value_);
  if(index >= list.size()){
    string msg = "Index " + to_string(index) + " is out of bounds for list size " + to_string(list.size()) + ".";
    return {false, Error::ref(Error::Type::IndexOutOfBounds, msg)};
  }
  return {true, *list[index]};
}




/**
 * @brief Accesses an element in a Map node by key. Returns a clone of the Node via OpStatus.
 */

Node::OpStatusRef Node::operator[](const string& key) {
  if(type_ != Type::Map){
    return {false, Error::ref(Error::Type::InvalidOperation, 
    "Operator[] (key: " + key +  ") can only be used on Map nodes. Current type: " + _to_str(type_))};
  }
  const Map& map = get<Map>(value_);
  auto it=map.find(key);

  if(it==map.end()) {
    string msg = "key '" + key + "' not found in map.";
    return {false, Error::ref(Error::Type::KeyNotFound, msg)};
  }
  return {true, *it->second};
}

//------------------------------------------------------------------------
Node::OpStatusRef Node::front() {
  MYLOGGER(trace_function, "Node::front()", __func__, SLOG_FUNC_INFO+31);

  switch(type_) {
  case Type::Vector: {
    if(empty_container()) return {false, 
      Error::ref(Error::Type::EmptyContainer,
      "Node::front() is empty: " )};
    auto &list = get<Vector>(value_);
    return {true, *list.front()}; }

  case Type::List:{
    if(empty_container()) return {false, 
      Error::ref(Error::Type::EmptyContainer,
      "Node::front() is empty: " )};
    auto &list = get<List>(value_);
    return {true, *list.front()}; }

  case Type::DeQue: {
    if(empty_container()) return {false, 
      Error::ref(Error::Type::EmptyContainer,
      "Node::front() is empty: " )};
    auto &list = get<DeQue>(value_);
    return {true, *list.front()}; }

  default:  
    return {false, Error::ref(Error::Type::IndexWrongType,
    "Node::type_ not vector, list or DeQue. Current type: " + _to_str(type_))};
  }
}

Node::OpStatusRef Node::back() {
  MYLOGGER(trace_function, "Node::back()", __func__, SLOG_FUNC_INFO+31);

  switch(type_) {
  case Type::Vector: {
    if(empty_container()) {
      return {false, Error::ref(Error::Type::EmptyContainer, "Node::back() is empty: " )};
    }

    auto &list = get<Vector>(value_);
    return {true, *list.back()}; }

  case Type::List:{
    if(empty_container()) return {false, 
      Error::ref(Error::Type::EmptyContainer,
      "Node::back() is empty: " )};
    auto &list = get<List>(value_);
    return {true, *list.back()}; }

  case Type::DeQue: {
    if(empty_container()) return {false, 
      Error::ref(Error::Type::EmptyContainer,
      "Node::back() is empty: " )};

    auto &list = get<DeQue>(value_);
    return {true, *list.back()}; }

  default:  
    return {false, Error::ref(Error::Type::EmptyContainer,
    "Node::type_ not vector, list or DeQue. Current type: " + _to_str(type_))};
  }
}



//------------------------------------------------------------------------
void Node::print(int depth) const { print_value_recursive(*this, depth); }

void Node::print_value_recursive(const Node& node, int depth) {
  if(depth==0) cout << "print recursive:\n";
  auto indent=[depth]() {
    for(int i = 0; i<depth; i++) cout << " ";
  };

  visit([&](auto&& arg) {
    using T = decay_t<decltype(arg)>;

    if constexpr (is_same_v<T, monostate>){
      cout << "Null";
    }
    else if constexpr (is_same_v<T, bool>){
      cout << "bool: " << arg;
    } else if constexpr (is_same_v<T, Error>){
      cout << "\033[31m[ERROR: " << Error::_to_str(arg.type_) << "]\033[0m: " << arg.message_;
    } else if constexpr (is_same_v<T, Integer>) {
      cout << arg; 
    } else if constexpr (is_same_v<T, Float>) {
      cout << fixed << setprecision(2) << arg; 
    } else if constexpr (is_same_v<T, Lisp::Op>) {
      cout << Lisp::_to_str(arg); 
    } else if constexpr (is_same_v<T, ProcState>) {
      cout << _to_str(arg); 
    } else if constexpr (is_same_v<T, ControlFlow>) {
      cout << _to_str(arg); 
    } else if constexpr (is_same_v<T, string>) {
      std::cout << "\"" << arg << "\""; 
    } else if constexpr (is_same_v<T, List>) {
      cout << "List["; 
      for(auto &e : arg) cout << *e <<","; 
      cout << " ]";
    } else if constexpr (is_same_v<T, DeQue>) {
      cout << "DeQue["; 
      for(auto &e : arg) cout << *e <<","; 
      cout << " ]";
    } 
    else if constexpr (is_same_v<T, Vector>) {
      cout << "Vector[(size=" << arg.size() << ") " << endl;
      for(size_t i=0; i<arg.size(); ++i) {
        indent();
        cout  << "  - [" << i << ", Type: " << Node::_to_str(arg[i]->type_) << "]: ";
        print_value_recursive(*arg[i].get(), depth+1);
        cout << "\n";
      }
      indent(); 
      cout << " ]";
    } else if constexpr (is_same_v<T, Map>) {
      cout << "{ (Map, size=" << arg.size() << ") " << endl;
      for(const auto&[key, child_ptr] : arg) {

        indent(); 
        cout << "  - " << key << " (Type: " << Node::_to_str(child_ptr->type_) << "): ";
        if(key == MODULE_PTR || key == CLASS_PTR) { cout << "==*ptr==\n"; continue; }
        if(key == CURRENT_MODULE_PTR || key == CURRENT_CLASS_PTR) { cout << "###*ptr##\n"; continue; }

        print_value_recursive(*child_ptr.get(), depth+1);
        cout << "\n";
      }
      indent();
      cout << " }";
    } else if constexpr (is_same_v<T, ptr_S>) {
      cout << "shared_ptr*:" << *arg;
    } else if constexpr (is_same_v<T, ptr_R>) {
      cout << "raw*:" << *arg;
    } else if constexpr (is_same_v<T, ptr_U>) {
      cout << "unique_ptr*:" << *arg;
    } else if constexpr (is_same_v<T, Fun>) {
      cout << "Fun*:" ;
    }


  }, node.value_);
}



ostream& operator<<(ostream& os, const Node& v) {
  //cout << "\naddr v:" <<  &v << " "; cout << v._to_str();
  //cout << "\n";
  cout << v._to_str();
  return os;
}
ostream& operator<<(ostream& os, const Node::OpStatus& s) {
  MYLOGGER(trace_function, "ostream& << (Node::OpStatus&)", __func__, SLOG_FUNC_INFO);
  if(s.first)  cout << "true: "; else cout << "false: ";

  if(s.second==nullptr) { 
    cout << "nullptr";
    return os;
  }
  cout << "value: " << s.second->_to_str() << ", type: " <<  Node::_to_str(s.second->_get_type()) ;
//  s.second->print();
  return os;
}
ostream& operator<<(ostream& os, const Node::OpStatusRef& s) {
  MYLOGGER(trace_function, "ostream& << (Node::OpStatus&)", __func__, SLOG_FUNC_INFO);
  if(s.first)  cout << "true: "; else cout << "false: ";
  cout << "value: " << s.second << ", type: " << Node::_to_str(s.second._get_type());
  return os;
}




//------------------------------------------------------------------------
Node::OpStatus Node::list_add() const {
  unique_ptr<Node> result = make_unique<Node>(0);
  return visit([&](auto&& list) -> OpStatus {
    using T = decay_t<decltype(list)>;
    if constexpr (is_same_v<T, Vector> || is_same_v<T, List> || is_same_v<T, DeQue>)  {
      for(auto& e: list ) {
        *result = *result + *e;
        if(result->type_ == Node::Type::Error) {
          cerr << "Error: " << *result << "\n";
          return {false, move(result)};
        }
      }
      return {true, move(result)};
    } else { return {false, nullptr}; }
    return {true, move(result)};
  }, value_);
}

/*
void Node::print_value(const Value& v, int depth) {
  visit([&](auto&& arg) {
    using T = decay_t<decltype(arg)>;

    if constexpr (is_same_v<T, monostate>){
      cout << "Null";
    }
    else if constexpr (is_same_v<T, bool>){
      cout << "bool: " << arg;
    }
    else if constexpr (is_same_v<T, Error>){
      cout << "\033[31m[ERROR: " << Error::_to_str(arg.type_) << "]\033[0m: " << arg.message_;
    } else if constexpr (is_same_v<T, Integer>) {
      cout << arg; 
    } else if constexpr (is_same_v<T, Float>) {
      cout << fixed << setprecision(2) << arg; 
    } else if constexpr (is_same_v<T, Lisp::Op>) {
      cout << Lisp::_to_str(arg); 
    } else if constexpr (is_same_v<T, ProcState>) {
      cout << _to_str(arg); 
    } else if constexpr (is_same_v<T, ControlFlow>) {
      cout << _to_str(arg); 
    } else if constexpr (is_same_v<T, string>) {
      std::cout << "\"" << arg << "\""; 
    } else if constexpr (is_same_v<T, List>) {
      cout << "List["; 
      for(auto &e : arg) cout << *e <<","; 
      cout << "]";
    } else if constexpr (is_same_v<T, DeQue>) {
      cout << "DeQue["; 
      for(auto &e : arg) cout << *e <<","; 
      cout << "]";
    } else if constexpr (is_same_v<T, Vector>) {
      cout << "Vector["; 
      for(auto &e : arg) cout << *e <<","; 
      cout << "]";
    } else if constexpr (is_same_v<T, Map>) {
      cout << "{ (Map, size=" << arg.size() << ") " << endl;

      for(const auto&[key, child_ptr] : arg) {
        cout << "  - " << key << " (Type: " << Node::_to_str(child_ptr->type_) << "): ";
        cout << "\n";
      }
      cout << "}";
    } else if constexpr (is_same_v<T, ptr_S>) {
      cout << "shared_ptr*:" << *arg;
    } else if constexpr (is_same_v<T, ptr_R>) {
      cout << "raw*:" << *arg;
    } else if constexpr (is_same_v<T, ptr_U>) {
      cout << "unique_ptr*:" << *arg;
    } else if constexpr (is_same_v<T, Fun>) {
      cout << "Fun*:";
    }
  }, v);
}
*/
Node::OpStatus Node::size() const {
  return visit([&](auto&& arg) -> OpStatus {
    using T = decay_t<decltype(arg)>;
    if constexpr (is_same_v<T, List> || is_same_v<T, DeQue> || 
      is_same_v<T, Vector> || is_same_v<T, Map>) {
      Integer s = arg.size();
      return {true, create(s)};
    } else {
      return {false, create(-1)};
    }
  }, value_);
  return {false, create(-1)};
}

Node::Integer Node::size_container() const {
  return visit([&](auto&& arg) -> Integer {
    using T = decay_t<decltype(arg)>;
    if constexpr (is_same_v<T, List> || is_same_v<T, DeQue> || 
      is_same_v<T, Vector> || is_same_v<T, Map>) {
      return arg.size();
    } else {
      return -1;
    }
  }, value_);
  return -1;
}

Node::OpStatus Node::empty() const {
  return visit([&](auto&& arg) -> Node::OpStatus {
    using T = decay_t<decltype(arg)>;
    if constexpr (is_same_v<T, List> || is_same_v<T, DeQue> || 
      is_same_v<T, Vector> || is_same_v<T, Map>) {
      return {true, create(arg.empty())};
    } else {
      return {false, create(false)};
    }
  }, value_);
  return {false, create(false)};
}

bool Node::empty_container() const {
  return visit([&](auto&& arg) -> bool {
    using T = decay_t<decltype(arg)>;
    if constexpr (is_same_v<T, List> || is_same_v<T, DeQue> || 
      is_same_v<T, Vector> || is_same_v<T, Map>) {
      return arg.empty();
    } else {
      return false;
    }
  }, value_);
  return false;
}

//------------------------------------------------------------------------
// convert container objects map, list, vector, deque to unqiue_ptr(shared_ptr);
unique_ptr<Node> Node::container_obj_to_US(unique_ptr<Node> node) {
  switch(node->type_) {
  case Node::Type::Map:
  case Node::Type::List:
  case Node::Type::Vector:
  case Node::Type::DeQue:
    return ptr_US(move(node));
  default: {}
  }
  //return move(node);
  return node;
}

//------------------------------------------------------------------------
 // conver to  unique pointer -> unique pointer(shared pointer)
 // it's a shared ptr being wrapped in a unqiue ptr
 // for object reference passing 
 // this is for the above container obj_to_US
unique_ptr<Node> Node::ptr_US(unique_ptr<Node> node) {
  MYLOGGER(trace_function, "Node::ptr_US(unique_ptr<Node>node)", __func__, SLOG_FUNC_INFO);
  //Node::ptr_S s_ptr_node = move(node);
  shared_ptr<Node> s_ptr_node = move(node);
  return make_unique<Node>(s_ptr_node);
}



//------------------------------------------------------------------------
// make a clone of unique shared without recursive cloning.
unique_ptr<Node> Node::ptr_USU(const unique_ptr<Node> &node) {
  MYLOGGER(trace_function, "Node::ptr_USU(const unique_ptr<Node>&node)", __func__, SLOG_FUNC_INFO);
  const auto sptr = get<ptr_S>(node->value_);
  return make_unique<Node>(sptr);
}
//------------------------------------------------------------------------
unique_ptr<Node> Node::ptr_USU(const Node &node) {
  MYLOGGER(trace_function, "Node::ptr_USU(const Node& node)", __func__, SLOG_FUNC_INFO);
  const auto sptr = get<ptr_S>(node.value_);
  return make_unique<Node>(sptr);
}

//------------------------------------------------------------------------
Node::ptr_S Node::_get_ptr_s() {
  return get<ptr_S>(value_);
}