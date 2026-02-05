Node::OpStatus LispExpr::eval_math(Node& process, const Lisp::Op op_head, const Node::Vector& code_list, size_t start) {
  MYLOGGER(trace_function, "LispExpr::eval_math(Node&process, Lisp::Op op_head, Node::Vector& code_list)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("Lisp::Op:: ") + Lisp::_to_str(op_head), SLOG_FUNC_INFO+30);
  MYLOGGER_MSG(trace_function, string("code_list: ") + Node::_to_str(code_list), SLOG_FUNC_INFO+30);
  MYLOGGER_MSG(trace_function, "start: " + to_string(start), SLOG_FUNC_INFO+30);

  switch(op_head){
  case Lisp::Op::add:   {
    cout << "add!!!"  <<  Node::_to_str(code_list) << "size : " << code_list.size() << " start:"  << start << "\n";
    if(code_list.size() < 3) {
      cerr << "error add :\n";
      return  {false, Node::create_error(Error::Type::InvalidOperation, "add op needs at least 3 params") };
    }
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
    auto result = *(first_status.second) + *(second_status.second);
    return {true, result.clone()};
  }

  case Lisp::Op::mul:   {
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
    auto result = *(first_status.second) * *(second_status.second);
    return {true, result.clone()};
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