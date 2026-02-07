Node::OpStatus LispExpr::eval_math(Node& process, const Lisp::Op op_head, const Node::Vector& code_list, size_t start) {
  MYLOGGER(trace_function, "LispExpr::eval_math(Node&process, Lisp::Op op_head, Node::Vector& code_list)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("Lisp::Op:: ") + Lisp::_to_str(op_head), SLOG_FUNC_INFO+30);
  MYLOGGER_MSG(trace_function, string("code_list: ") + Node::_to_str(code_list), SLOG_FUNC_INFO+30);
  MYLOGGER_MSG(trace_function, "start: " + to_string(start), SLOG_FUNC_INFO+30);

  switch(op_head){
  case Lisp::Op::add:   {
    auto list = list_clone_remainder(code_list, start);
    return builtin_add(process, list);
  }
  case Lisp::Op::sub:   {
    auto list = list_clone_remainder(code_list, start);
    return builtin_sub(process, list);
  }

  case Lisp::Op::mul:   {
    auto list = list_clone_remainder(code_list, start);
    return builtin_mul(process, list);
  }
  case Lisp::Op::div:   {
    auto list = list_clone_remainder(code_list, start);
    return builtin_div(process, list);
  }

  case Lisp::Op::eq:   {
//    cout << "eq!!!"  <<  Node::_to_str(code_list) << "size : " << code_list.size() << " start:"  << start << "\n";
    auto first_status = eval(process, *code_list[start]);
    auto second_status = eval(process, *code_list[start+1]);
    if(!first_status.first ){
      cerr << "error add first operand:" << first_status << "\n";
      return  first_status;
    }
    if(!second_status.first ){
      cerr << "error add second operand:" << second_status << "\n";
      return  second_status;
    }
    auto result = *(first_status.second) == *(second_status.second);
    return {true, result.clone()};
  }

  case Lisp::Op::lt:   {
    //cout << "lt!!!"  <<  Node::_to_str(code_list) << "size : " << code_list.size() << " start:"  << start << "\n";
    auto first_status = eval(process, *code_list[start]);
    auto second_status = eval(process, *code_list[start+1]);
    if(!first_status.first ){
      cerr << "error add first operand:" << first_status << "\n";
      return  first_status;
    }
    if(!second_status.first ){
      cerr << "error add second operand:" << second_status << "\n";
      return  second_status;
    }
    auto result = *(first_status.second) < *(second_status.second);
    return {true, result.clone()};
  }
  case Lisp::Op::gt:   {
    //cout << "gt!!!"  <<  Node::_to_str(code_list) << "size : " << code_list.size() << " start:"  << start << "\n";
    auto first_status = eval(process, *code_list[start]);
    auto second_status = eval(process, *code_list[start+1]);
    if(!first_status.first ){
      cerr << "error add first operand:" << first_status << "\n";
      return  first_status;
    }
    if(!second_status.first ){
      cerr << "error add second operand:" << second_status << "\n";
      return  second_status;
    }
    auto result = *(first_status.second) > *(second_status.second);
    return {true, result.clone()};
  }
  case Lisp::Op::gteq:   {
    auto first_status = eval(process, *code_list[start]);
    auto second_status = eval(process, *code_list[start+1]);
    if(!first_status.first ){
      cerr << "error add first operand:" << first_status << "\n";
      return  first_status;
    }
    if(!second_status.first ){
      cerr << "error add second operand:" << second_status << "\n";
      return  second_status;
    }
    auto result = *(first_status.second) >= *(second_status.second);
    return {true, result.clone()};
  }
  case Lisp::Op::lteq:   {
    auto first_status = eval(process, *code_list[start]);
    auto second_status = eval(process, *code_list[start+1]);
    if(!first_status.first ){
      cerr << "error add first operand:" << first_status << "\n";
      return  first_status;
    }
    if(!second_status.first ){
      cerr << "error add second operand:" << second_status << "\n";
      return  second_status;
    }
    auto result = *(first_status.second) <= *(second_status.second);
    return {true, result.clone()};
  }
  case Lisp::Op::and_:   {
    auto first_status = eval(process, *code_list[start]);
    auto second_status = eval(process, *code_list[start+1]);
    if(!first_status.first ){
      cerr << "error add first operand:" << first_status << "\n";
      return  first_status;
    }
    if(!second_status.first ){
      cerr << "error add second operand:" << second_status << "\n";
      return  second_status;
    }
    auto result = *(first_status.second) && *(second_status.second);
    return {true, result.clone()};
  }
  case Lisp::Op::or_:   {
    auto first_status = eval(process, *code_list[start]);
    auto second_status = eval(process, *code_list[start+1]);
    if(!first_status.first ){
      cerr << "error add first operand:" << first_status << "\n";
      return  first_status;
    }
    if(!second_status.first ){
      cerr << "error add second operand:" << second_status << "\n";
      return  second_status;
    }
    auto result = *(first_status.second) || *(second_status.second);
    return {true, result.clone()};
  }
  case Lisp::Op::not_:   {
    auto first_status = eval(process, *code_list[start]);
    if(!first_status.first ){
      cerr << "error add first operand:" << first_status << "\n";
      return  first_status;
    }
    auto result = ! (*(first_status.second) );
    return {true, result.clone()};
  }





  default:{}
  }
  cerr << "unknown op()!: " + Lisp::_to_str(op_head) + "\n"; 
  return {false, Node::create_error(Error::Type::Unknown, "Unknown Lisp::Op command")};

}

//------------------------------------------------------------------------
template <typename T>
Node::OpStatus LispExpr::builtin_add(Node& process, const T& list) {
  unique_ptr<Node> result = make_unique<Node>(0);
  if constexpr (is_same_v<T, Node::Vector> || is_same_v<T, Node::DeQue>||  is_same_v<T, Node::List>) {

    for(auto& element : list) { 
      auto ev_status = eval(process, *element);
      if(!ev_status.first) {
          cerr << "builtin_add eval() error: " << ev_status.second->_to_str() << "\n";
          return ev_status;
      }
      if(ev_status.first) *result = *result + *ev_status.second;
    }
    return {true, move(result)};
  } 
  return {false, Node::create()};
}



//------------------------------------------------------------------------
template <typename T>
Node::OpStatus LispExpr::builtin_sub(Node& process, const T& list) {
  unique_ptr<Node> result ;
  if constexpr (is_same_v<T, Node::Vector> || is_same_v<T, Node::DeQue>||  is_same_v<T, Node::List>) {
    bool first_run = true;

    for(auto& element : list) { 

      auto ev_status = eval(process, *element);

      if(!ev_status.first) {
          cerr << "builtin_sub eval() error: " << ev_status.second->_to_str() << "\n";
          return ev_status;
      }
      if(first_run) { first_run = false; result =  move(ev_status.second); continue; }

      if(ev_status.first) *result = *result -  *ev_status.second;
    }
    return {true, move(result)};
  } 
  return {false, Node::create()};
}


//------------------------------------------------------------------------
template <typename T>
Node::OpStatus LispExpr::builtin_mul(Node& process, const T& list) {
  unique_ptr<Node> result = make_unique<Node>(1);
  if constexpr (is_same_v<T, Node::Vector> || is_same_v<T, Node::DeQue>||  is_same_v<T, Node::List>) {

    for(auto& element : list) { 
      auto ev_status = eval(process, *element);
      if(!ev_status.first) {
          cerr << "builtin_mul eval() error: " << ev_status.second->_to_str() << "\n";
          return ev_status;
      }
      if(ev_status.first) *result = *result * *ev_status.second;
    }
    return {true, move(result)};
  } 
  return {false, Node::create()};
}

template <typename T>
Node::OpStatus LispExpr::builtin_div(Node& process, const T& list) {
  unique_ptr<Node> result ;
  //Node zero(0);
  Node zero(0, Node::Type::Integer);
  if constexpr (is_same_v<T, Node::Vector> || is_same_v<T, Node::DeQue>||  is_same_v<T, Node::List>) {
    bool first_run = true;

    for(auto& element : list) { 

      auto ev_status = eval(process, *element);

      if(!ev_status.first) {
          cerr << "builtin_sub eval() error: " << ev_status.second->_to_str() << "\n";
          return ev_status;
      }
      if(first_run) { first_run = false; result =  move(ev_status.second); continue; }
      auto bv = ((*ev_status.second) == zero) ;
      if(bv._get_bool() == true) return {false, Node::create_error(Error::Type::DivideByZero, "Error: Trying to divide zero!")};

      if(ev_status.first) *result = *result /  *ev_status.second;
    }
    return {true, move(result)};
  } 
}