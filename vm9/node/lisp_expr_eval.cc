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
Node::OpStatus LispExpr::builtin_print_n(Node& env, const T& list, size_t start) {
  MYLOGGER(trace_function, "LispExpr::print(Node&env, const T&list, size_t)", __func__, SLOG_FUNC_INFO);
  //cout << "builtin print!\n";
  //return {true, Node::create(true)};
  if constexpr (is_same_v<T, Node::Vector> || is_same_v<T, Node::DeQue>||  is_same_v<T, Node::List>) {
    size_t s=list.size();
    for(size_t i = start;  i<s; i++) {
      auto &element = list[i];
      cout << *element;
    }
  } else {
    cout << "builtin_print_n unknown T list\n";

  }
  return {true, Node::create()};
}

//------------------------------------------------------------------------
// eval node 
Node::OpStatus LispExpr::eval(const Node& node, Node& env) {
  MYLOGGER(trace_function, "LispExpr::eval(Node&node, Node&env)", __func__, SLOG_FUNC_INFO);

  if(node.type_ != Node::Type::Vector) {
    return {false, Node::create_error(Node::Error::Type::InvalidOperation,  
      "Can't eval unknown code vector type!\n")};
  }
  cout << "eval env: \n"; env.print();


  auto &code = get<Node::Vector>(node.value_);


  if(code[0]->type_== Node::Type::LispOp) {
    //

    Lisp::Op op_head = get<Lisp::Op>(code[0]->value_);
    switch(op_head){
    case Lisp::Op::print: {
      builtin_print_n(env, code, 1);
      break;}
    default: {
      cout << "unknown command()!\n";
      break; }};

  } else if(code[0]->type_==Node::Type::Identifier) {

    cerr << "unknown command or function call: type is : " <<  Node::_to_str(code[0]->type_) << "\n";
    cerr << "value is : " <<  code[0]->_to_str() << "\n";
    return {false, Node::create(false)};

  }
  
  //return {true, nullptr};
  return {true, Node::create()};


}
