#include "lisp_expr.hh"
#include <iostream>

#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"

const vector<string> LispExpr::lisp_path_key = {"Lang", "Lisp"};
const vector<string> LispExpr::lisp_module_key = {"Lang", "Lisp", "Module"};
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
  set_branch(lisp_module_key, Node::create(move(vector)));
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

  auto tokens_raw_text = reader.tokenize(input); // list<Token>
  auto parsed_status_first_pass = reader.parse(tokens_raw_text); 

  if(!parsed_status_first_pass.first) {
    cerr << "building_program: Reader.tokenize() and Reader.parser(): parse error for input string: " << input  << "\n";
    return  parsed_status_first_pass;
  }


  //cout << "before1 token : " << parsed_status_first_pass << "\n";
  //cout << "before1 token size: " << parsed_status_first_pass.second->size() << "\n";
  auto parsed_status_second_pass =  parse(*parsed_status_first_pass.second);
  //cout << "after1 token : " << parsed_status_first_pass << "\n";
  //cout << "after1 token size: " << parsed_status_first_pass.second->size() << "\n\n";

  cout << "status parsed second pass: " << parsed_status_second_pass << "\n";
  cout << "\n\n";

  //set_branch(lisp_lang_atoms, 123.12d);
  auto env_status = get_env();
//  cout << "build_program parsed tokens: " <<  *list_status.second << "\n";
  
  /*
  cout << "getting value!\n";
  auto &list = get<Node::List>(list_status.second->value_);
  cout << "list size: " << list.size() << "\n";
  auto result_status2 = parse_list(list);
  //auto result_status = eval_list(*env_status.second, list);

  //cout << "result: " << *result_status.second << "\n";
 */ 
return parsed_status_second_pass;

}

//------------------------------------------------------------------------ build parse

// tokens: double linked list of tokens
Node::OpStatus LispExpr::parse(Node& tokens) {
  MYLOGGER(trace_function, "LispExpr::parse(Node&tokens)", __func__, SLOG_FUNC_INFO);
  //cout << "parse tokens: " <<  tokens << "\n\n";

  if(tokens.type_ != Node::Type::List) 
    return {true, tokens.clone()};



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

    switch(op_head) {
    case Lisp::Op::print:  { //cout << "print: " <<  tokens << "\n";
      return {true, Node::create()};}
    case Lisp::Op::deque:  { 
      return build_parsed_deque(list); }
    case Lisp::Op::list:  { //cout << "parsing list: " <<  tokens << "\n";
      return build_parsed_list(list); }
    case Lisp::Op::vector:  { //cout << "parsing vector: " <<  tokens << "\n";
      return build_parsed_vector(list);}
    case Lisp::Op::def: {// cout << "case parse def\n";
      return build_parsed_def(list); }
    case Lisp::Op::defun: {
      return build_parsed_fun(list); }
    case Lisp::Op::module: {

      return build_parsed_module(list); 
    }

    default: {
      cerr << "unknown: tokens: " <<  tokens << "\n";
      return {true, Node::create()}; 
    }}

    //cout << "lisp op head: " << Lisp::_to_str(op_head) << "\n";
  } else  {  // identifiers starts as (head ...)
    // return a list of identifers
    list.push_front(move(head_status.second));
    return {true, Node::create(move(list)) };
  }

  return {true, Node::create()};
}

//------------------------------------------------------------------------ build parse
// asssumes Node.value_ contains a Node::List of nodes

//-------------------------------- vector

Node::OpStatus LispExpr::build_parsed_vector(Node& node) {
  MYLOGGER(trace_function, "LispExpr::build_parsed_vector(Node&)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("node: ") + node._to_str(), SLOG_FUNC_INFO+30);
  if(node.type_ != Node::Type::List) {
  }
  auto &list = get<Node::List>(node.value_);
  return build_parsed_vector(list);
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
    } else 
    //dl.push_back(move(ele->clone()));
    dl.push_back(move(ele));
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
  for(auto& e : list) {

  }
  return {true, Node::create(move(map))};
}
//Node::OpStatus LispExpr::build_parsed_map(Node& node) { }


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


//-------------------------------- parse fun
// (fun_name (param_list) (description) (code list))
// return map as function
//
Node::OpStatus LispExpr::build_parsed_fun(Node::List& list) {
  MYLOGGER(trace_function, "LispExpr::build_parsed_fun(Node::List& list)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("list: ") + Node::_to_str(list), SLOG_FUNC_INFO+30);

  Node::Map map_n={}, map={}; 
  string name = get<string>(list.front()->value_); list.pop_front(); // function name

  // set func
  map["params"] = move(list.front()); list.pop_front();
  map["description"] = move(list.front()); list.pop_front();
  map["code"] = move(list.front()); list.pop_front();

  map_n[name]  = Node::create(move(map));

  return {true, Node::create(move(map_n))};

}
//-------------------------------- parse module
// (module Main (defun main ) (defun f1 ) (defun f2))
Node::OpStatus LispExpr::build_parsed_module(Node::List& list) {
  MYLOGGER(trace_function, "LispExpr::build_parsed_module(Node::List& list)", __func__, SLOG_FUNC_INFO);
  //MYLOGGER_MSG(trace_function, string("list: ") + Node::_to_str(list), SLOG_FUNC_INFO+30);

  unique_ptr<Node> node_f;
  Node::Map map_n={}, map_f={}, map={}; 
  cout << "parse module1\n";
  string name = get<string>(list.front()->value_); list.pop_front(); // module name
 // auto &name_l = get<Node::List>(list.front()->value_); list.pop_front(); // module name
  //auto  &name_s = name_l.front();
  //cout << "name_s " <<  *name_s << "\n";
  cout << "name " <<  name << "\n";
  cout << "parse module2\n";

  //map["name"] = move(list.front()); list.pop_front();

  for(auto& ele: list) {  
    cout << "ele: " << *ele << "\n";
    auto status_fun = parse(*ele); // parse (defun ...)
    if(!status_fun.first) return status_fun;
    //for(auto& p : *status_fun.second) {}
    //map_f.merge(  move(status_fun.second));
    node_f->merge(move(status_fun.second));
  }
  map_n["function"] = move(node_f);
  //map[name] = Node::create(move(map_n));
  //return {true, Node::create(move(map))};

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
    return {true, Node::create()};
  } else {
    cout << "builtin_print something\n";
    //cout << list << "\n";
  }
}