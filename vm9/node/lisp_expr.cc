#include "lisp_expr.hh"
#include <iostream>

#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"

const vector<string> LispExpr::lisp_path_key = {"Lang", "Lisp"};
const vector<string> LispExpr::lisp_main_key = {"Lang", "Lisp", "Module", "Main", "main" };
const vector<string> LispExpr::lisp_lang_atoms = {"module", "fun", "mvar", "lvar", "class"};

LispExpr::LispExpr() : Lang(), reader(this)
, sym_module(str_to_atom("module"))
, sym_fun(str_to_atom("fun"))
, sym_mvar(str_to_atom("mvar"))
, sym_lvar(str_to_atom("lvar"))
, sym_class(str_to_atom("class"))
 {
  MYLOGGER(trace_function, "LispExpr::LispExpr()", __func__, SLOG_FUNC_INFO);
  Node::Vector vector;
  set_branch(lisp_main_key, Node::create(move(vector)));
  //for(auto &v : lisp_lang_atoms ) str_to_atom(v);
}
void LispExpr::set_symbols() {

}

void LispExpr::bootstrap() {
  string boot_str = "(root set_branch (list Lang Lisp))";
  // create environemtn
  // create kernel
  // create some pre modules and functions
}

Node::Integer  LispExpr::str_to_atom(const string& input) { return Lang::str_to_atom(input);}
Node::OpStatus LispExpr::atom_to_str(Node::Integer v) { return Lang::atom_to_str(v); }

void LispExpr::print() {
  cout << "Lisp Interpreter\n";
  cout << *root << "\n";
  Node::print_value_recursive(*root);
}

LispReader& LispExpr::get_reader() {
  return reader;
}


//------------------------------------------------------------------------
Node::OpStatus LispExpr::get_env() { 
  Node::Map nm={}; return {true, Node::create(move(nm))}; 
}



//------------------------------------------------------------------------
Node::OpStatus LispExpr::build_program(const string& input) { 
  MYLOGGER(trace_function, "LispExpr::build_program(const string&input)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("input: ") + input, SLOG_FUNC_INFO+30);

  auto tokens = reader.tokenize(input);
  auto list_status = reader.parse(tokens);
  auto env_status = get_env();

  if(!list_status.first) {
    cout << "parse error for input string: " << input  << "\n";
    return  list_status;
  }
  parse_node_tokens(*list_status.second);
//  cout << "build_program parsed tokens: " <<  *list_status.second << "\n";
  
  /*
  cout << "getting value!\n";
  auto &list = get<Node::List>(list_status.second->value_);
  cout << "list size: " << list.size() << "\n";
  auto result_status2 = parse_list(list);
  //auto result_status = eval_list(*env_status.second, list);

  //cout << "result: " << *result_status.second << "\n";
 */ 
return list_status;


}
Node::OpStatus LispExpr::parse_node_tokens(Node& token_node) {
  MYLOGGER(trace_function, "LispExpr::parse_node_tokens(Node&tokens)", __func__, SLOG_FUNC_INFO);
  cout << "parse tokens: " <<  token_node << "\n";
  if(token_node.type_ != Node::Type::List) {
    cerr << "parse tokens type ! list: \n";
    return {false, nullptr};

  }
  auto &tokens = get<Node::List>(token_node.value_);
  auto &head = tokens.front();
  cout << "head " << *head << "\n";
  parse_list(tokens);
  //auto &head =  tokens.front(); tokens.pop_front();


  return {true, nullptr};

}

//------------------------------------------------------------------------
//Node::OpStatus LispExpr::build_program(const string& input) { }
//------------------------------------------------------------------------

Node::OpStatus LispExpr::parse_list(Node::List& list) {
  MYLOGGER(trace_function, "LispExpr::parse_list(List& list)", __func__, SLOG_FUNC_INFO);
  cout << "parse list!\n";
  cout << "list.size:" << list.size() <<" \n";
  cout << "list.size:" << list.size() <<" \n";
  //Node::print_value(list);
  auto head = move(list.front());
  list.pop_front();
  if(head ==nullptr) {
    cerr << "head is nullptr \n";
    return {false, nullptr};


  }
  cout << "head " << *head << "\n";
  //cout << "rest " << list << "\n";

  return {true, nullptr};

  auto op = get<Lisp::Op>(head->value_);
  //cout << list->print() << "\n";
  
  switch(op)  {
  case Lisp::Op::error: return {false, nullptr};
  //case Lisp::Op::def:  return  parse_def(list);
  case Lisp::Op::list:  return  build_list(list);
  case Lisp::Op::vector:  return  build_vector(list);
  case Lisp::Op::deque:  return  build_deque(list);
  case Lisp::Op::print:  {
    auto& rest = list.front();
    cout << "print: " <<  *rest << "\n";
    return {true, nullptr};

  }
  default:  return {true, Node::clone(list)};
  }

  return {false, nullptr};
}

/*
 * list[0] = (def
 * list[1] = :module, :func, :mvar, :lvar
Node::OpStatus LispExpr::parse_def(const Node::List& list) {
  //MYLOGGER(trace_function, "LispExpr::parse_def(List& list)", __func__, SLOG_FUNC_INFO);
  cout << "parse def:";
  auto def_type = get<Node::Integer >(list[1]->value_);
  unique_ptr<Node> node_module_ptr;

  //auto op = get<Node::LispOp>(head->value_);
  if(def_type == sym_module) {
    cout << "found def :module!\n";
    string module_name = get<string>(list[2]->value_);
  }
  return {true, Node::create("module")};
}
 */

//------------------------------------------------------------------------
Node::OpStatus LispExpr::eval(Node& env) {
  /*
  if(type_ != Type::LispOp)
    return {false, create_error(Node::Error::Type::InvalidOperation, "Not a Lisp Expression")};

  auto &list = get<Node::List>(value_);
  auto head = get<LispOp>(list[0]->value_);

  switch(head) {
  case LispOp::add: return builtin_add(env, 1);
  case LispOp::mul: return builtin_mul(env, 1);
  }
*/
  return {false, nullptr};
}

/*
Node::OpStatus LispExpr::eval_list(Node& env, const Node::List& list) {
  auto &head = list[0];
  auto op = get<Node::LispOp>(head->value_);
  
  switch(op)  {
  case Node::LispOp::root: 
    return builtin_list_root(env, list, 1);
  case Node::LispOp::error: 
  return {false, nullptr};
  case Node::LispOp::noop: 
  return {false, nullptr};
  case Node::LispOp::add: 
    return builtin_list_add(env, list, 1);
  case Node::LispOp::sub: 
  return {false, nullptr};
  case Node::LispOp::mul:
    return builtin_list_mul(env, list, 1);
  case Node::LispOp::div:
  return {false, nullptr};
  case Node::LispOp::mod:
  return {false, nullptr};
  case Node::LispOp::list: 
    return builtin_list_list(env, list, 1);
  case Node::LispOp::def: 
  return {false, nullptr};
  case Node::LispOp::call: 
  return {false, nullptr};
  case Node::LispOp::ret: 
  return {false, nullptr};
  case Node::LispOp::send: 
  return {false, nullptr};
  case Node::LispOp::cond: 
  return {false, nullptr};
  case Node::LispOp::print: return builtin_list_print(env, list, 1);
  }
  return {false, nullptr};

}

//------------------------------------------------------------------------
Node::OpStatus LispExpr::builtin_add(Node &env, const Node::List& list, size_t start) {

  cout << "builtin_add\n";
  cout << "start: " << start << "\n";
  cout << "list.size: " << list.size() << "\n";
  unique_ptr<Node> result = make_unique<Node>(0);
  for(size_t i=start; i<list.size(); i++) {
    auto e = list[i]->eval(env);
    cout << "e: " << *e.second << "\n";
    if(e.first == false) return {false, nullptr};
    *result = *result + *e.second;
    cout << "result: " << *result << "\n";

  }
  return {true, move(result)};

}

Node::OpStatus LispExpr::builtin_mul(Node &env, const Node::List& list, size_t start) {
  unique_ptr<Node> result = make_unique<Node>(1);
  for(size_t i=start; i<list.size(); i++) {
    auto e = list[i]->eval(env);
    if(e.first == false) return {false, nullptr};
    *result = *result * *e.second;
  }
  return {true, move(result)};
}

Node::OpStatus LispExpr::builtin_print(Node &env, const Node::List& list, size_t start) {
  cout << "builtin_print\n";
  cout << "start: " << start << "\n";
  cout << "list.size: " << list.size() << "\n";
  unique_ptr<Node> result = make_unique<Node>(0);
  for(size_t i=start; i<list.size(); i++) {
    auto e = list[i]->eval(env);
    cout << "e: " << *e.second << "\n";
  }
  return {true, nullptr};
}

Node::OpStatus LispExpr::builtin_list(Node &env, const Node::List& list, size_t start) {
  Node::List result_list;
  for(size_t i=start; i<list.size(); i++) {
    auto e = list[i]->eval(env);
    if(e.first == false) return e;
    result_list.push_back(move(e.second));

  }
  return {true, Node::create(move(result_list))};
}

Node::OpStatus LispExpr::builtin_root(Node& env, const Node::List& list, size_t start) {
  auto &root = list[0];
  auto &cmd = get<string>(list[1]->value_);
  if(cmd == "set_branch") {

  } 
  return {true, nullptr};

}
*/

Node::OpStatus LispExpr::build_vector(const Node::List& list) {
  Node::Vector vl;
  vl.reserve(list.size());
  for(auto& e : list) vl.push_back(e->clone());
  return {true, Node::create(move(vl))};
}

Node::OpStatus LispExpr::build_deque(const Node::List& list) {
  Node::DeQue dl;
  for(auto& e : list) dl.push_back(e->clone());
  return {true, Node::create(move(dl))};
}

Node::OpStatus LispExpr::build_list(const Node::List& list) {
  return {true, Node::clone(list)};
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
    return {false, nullptr};
  }
}

template <typename T>
Node::OpStatus LispExpr::builtin_print(Node& env, const T& list) {
  if constexpr (is_same_v<T, Node::Vector> || is_same_v<T, Node::DeQue>||  is_same_v<T, Node::List>) {
    cout << "builtin_print_list\n";
    for(auto& element : list) { 
      if(element.first) {
        auto& ev = element.second->eval(env);
        cout << *ev.second << "\n";
      }
    }
    return {true, nullptr};
  } else {
    cout << "builtin_print something\n";
    //cout << list << "\n";
  }
}