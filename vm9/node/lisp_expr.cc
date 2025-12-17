#include "lisp_expr.hh"
#include <iostream>

#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"

#define UNIVERSE "universe"
const vector<string> LispExpr::lisp_path_key = {UNIVERSE, "Lang", "Lisp"};
const vector<string> LispExpr::lisp_module_key = {UNIVERSE, "Lang", "Lisp", "Module"};
const vector<string> LispExpr::lisp_lang_atoms = {UNIVERSE, "module", "fun", "mvar", "lvar", "class"};
const vector<string> LispExpr::interactive_key  = {UNIVERSE, "interactive"};
const vector<string> LispExpr::lisp_process = {UNIVERSE, "Process"};

LispExpr::LispExpr() : Lang(), reader(this)
, sym_module(str_to_atom("module"))
, sym_fun(str_to_atom("fun"))
, sym_mvar(str_to_atom("mvar"))
, sym_lvar(str_to_atom("lvar"))
, sym_class(str_to_atom("class"))
, sym_get(str_to_atom("get"))
, sym_set(str_to_atom("set"))
 {
  MYLOGGER(trace_function, "LispExpr::LispExpr()", __func__, SLOG_FUNC_INFO);
  Node::Map map_module;
  Node::Vector vector_proc;
  vector_proc.reserve(10);
  set_branch(lisp_module_key, Node::create(move(map_module)));
  set_branch(lisp_process, Node::create(move(vector_proc)));

  //set_branch(lisp_module_key, Node::create(Node::Type::Map));
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
  cout << "first pass: " <<  *parsed_status_first_pass.second << "\n";
  //cout << "first pass: " <<  "\n";
  //parsed_status_first_pass.second->print();

  //return {true, Node::create()};

  if(!parsed_status_first_pass.first) {
    cerr << "building_program: Reader.tokenize() and Reader.parser(): parse error for input string: " << input  << "\n";
    cerr << "error: " <<  *parsed_status_first_pass.second << "\n";
    return  parsed_status_first_pass;
  }


  auto parsed_status_second_pass =  parse(*parsed_status_first_pass.second);

  cout << "status parsed second pass1: " << parsed_status_second_pass << "\n";
  cout << "\n\n";


  auto attach_status = attach_module(parsed_status_second_pass.second->clone());

  //auto attach_status = attach_module(move(parsed_status_second_pass.second));
  /*
  if(parsed_status_second_pass.first) {
    auto cm  = parsed_status_second_pass.second->clone();
    cout << "cm: " << *cm << "\n";
    auto attach_status = attach_module(move(cm));
  }*/
  //cout << "status parsed second pass2: " << parsed_status_second_pass << "\n";

  // this cause it to crap
  // auto attach_status = attach_module(make_unique<Node>(Node::Type::Map));
   //auto ptr = make_unique<Node>(Node::Type::Map); attach_module(move(ptr));

  //auto attach_status = attach_module(parsed_status_second_pass.second->clone());
  //cout << "status parsed second pass.print():\n";
  //parsed_status_second_pass.second->print();



  auto env_status = get_env();
  //return parsed_status_second_pass;
  return {true, Node::create(true)};

}

Node::OpStatus LispExpr::run_program() { 
  MYLOGGER(trace_function, "LispExpr::run_program()", __func__, SLOG_FUNC_INFO);

  vector<string> main_path=  LispExpr::lisp_module_key ;
  vector<string> code_path = {"Main", "function", "main", "code"};

  main_path.insert(main_path.end(), code_path.begin(), code_path.end());

  Node::OpStatusRef node_status = get_node(main_path);
  if(!node_status.first)  {
    cerr << "main path not found!\n";
    return  {false, Node::create_error(
      Node::Error::Type::KeyNotFound, 
      "main path node not found " + _to_str_ext(main_path))};
  }

  auto env_status = get_env();
  if(!env_status.first) {
    cerr << "no env_status ! found!\n";
    return env_status;
  }

  cout << "run program node code!\n ";
  node_status.second.print();

  //eval(node_status.second,  *env_status.second);
  eval(node_status.second,  *env_status.second);
  return  {true, nullptr};

}

//------------------------------------------------------------------------
Node::OpStatus LispExpr::attach_module(unique_ptr<Node> module) {
  MYLOGGER(trace_function, "LispExpr::attach_module(unique_ptr<Node>module)", __func__, SLOG_FUNC_INFO);
  auto mod_loc = get_branch(lisp_module_key);
  return mod_loc->merge(move(module));
  //cout << "mod_loc: " << *mod_loc << "\n\n";
  //return {false, Node::create(true)};
}

//------------------------------------------------------------------------ build and parse interpreter 

// tokens: double linked list of tokens
Node::OpStatus LispExpr::parse(Node& tokens) {
  MYLOGGER(trace_function, "LispExpr::parse(Node&tokens)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("tokens: ") + tokens._to_str(), SLOG_FUNC_INFO+30);
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
    MYLOGGER_MSG(trace_function, string("LispOp: ") + Lisp::_to_str(op_head), SLOG_FUNC_INFO+30);

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
    case Lisp::Op::root: {
      MYLOGGER_MSG(trace_function, string("Lisp::Op::root: ") + tokens._to_str(), SLOG_FUNC_INFO+30);
      return build_parsed_root(list); 
    }

    default: {
      cerr << "Parser build interpreter: Lisp Op not permitted  : " <<  Lisp::_to_str(op_head) << ", " << tokens << "\n";
      return {false, Node::create()}; 
    }}

    //cout << "lisp op head: " << Lisp::_to_str(op_head) << "\n";
  } else  {  // identifiers starts as (head ...)

    MYLOGGER_MSG(trace_function, string("Node::Type: ") + Node::_to_str(head_status.second->type_), SLOG_FUNC_INFO+30);

    cout << "function call: what is up!\n";
    cerr << "Parser build unknown instruction: " << *head_status.second <<  ": " << tokens << "\n";
    Node::List nl;
    nl.push_back(move(head_status.second));
    return {true, Node::create(move(nl))};


    return {false, Node::create_error(Node::Error::Type::InvalidOperation,  
      "Parser build unknown lisp macro instruction: " + head_status.second->_to_str() +
      " and type: " + Node::_to_str(head_status.second->type_)
    )}; 

    // throw std::runtime_error("unknown keyword");

    // return a list of identifers
    //list.push_front(move(head_status.second));
    //return {true, Node::create(move(list)) };
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
  {// turn params List to params Vector for speed performance
  auto status=  build_parsed_vector(*list.front()); 
  if(!status.first) return status;
  map["params"] = move(status.second); list.pop_front();
  }

  map["description"] = move(list.front()); list.pop_front();
  
  {// turn code List to code Vector for speed performance
  auto status=  build_parsed_vector(*list.front()); 
  if(!status.first) return status;
  map["code"] = move(status.second); list.pop_front();
  //cout << "code: list after pop!" << Node::_to_str(list) << "\n";
  }

  map_n[name]  = Node::create(move(map));

  cout << "map_n: " << Node::_to_str(map_n) << "\n";

  return {true, Node::create(move(map_n))};

}
//-------------------------------- parse module
// (module Main (defun main ) (defun f1 ) (defun f2))
Node::OpStatus LispExpr::build_parsed_module(Node::List& list) {
  MYLOGGER(trace_function, "LispExpr::build_parsed_module(Node::List& list)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("list: ") + Node::_to_str(list), SLOG_FUNC_INFO+30);

  vector<string> keys={};

  auto node_functions=make_unique<Node>(Node::Type::Map);
  auto node_module=make_unique<Node>(Node::Type::Map);

  string name = get<string>(list.front()->value_); list.pop_front(); // module name

  keys.push_back(name);
  keys.push_back("function");

  for(auto& ele: list) {  
    auto status_fun = parse(*ele); // parse (defun ...)
    if(!status_fun.first) return status_fun;
    node_functions->merge(move(status_fun.second));
  }
  node_module->set(keys, move(node_functions), true);

  return {true, move(node_module)};

 }

//-------------------------------- parse root
// (root :set (path,..) value )
// (root :get () )
Node::OpStatus LispExpr::build_parsed_root(Node::List& list) {
  MYLOGGER(trace_function, "LispExpr::build_parsed_root(Node::List& list)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("list: ") + Node::_to_str(list), SLOG_FUNC_INFO+30);

  try {
    auto root_sym_op = get<Node::Integer>(list.front()->value_); list.pop_front(); // root op symbol 
    if(root_sym_op == sym_set) {
      auto path_list = move(get<Node::List>(list.front()->value_));  list.pop_front();
      auto value = move(list.front());  list.pop_front();

      auto path_vec_str = Node::list_to_vector_string(path_list);
      return set(path_vec_str, move(value), true);
      //return {true, Node::create(true)};

    } else if(root_sym_op== sym_get){
      auto path_list = move(get<Node::List>(list.front()->value_));  list.pop_front();
      auto path_vec_str = Node::list_to_vector_string(path_list);
      auto node_ref = get_node(path_vec_str);
      if(node_ref.first) return {true, node_ref.second.clone()};
    }
  } catch(...) { 
    return {false, Node::create_error(Node::Error::Type::InvalidOperation, 
        "error: parsed root get symbol") };
  }
  return {true, Node::create()};

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
  cout << "eval: \n";
  node.print();


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