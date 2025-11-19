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

  auto tokens_first_pass = reader.tokenize(input); // list<Token>
  auto parsed_status_first_pass = reader.parse(tokens_first_pass); 

  if(!parsed_status_first_pass.first) {
    cerr << "building_program: Reader.tokenizer() and Reader.parser(): parse error for input string: " << input  << "\n";
    return  parsed_status_first_pass;
  }

  auto parsed_status_second_pass =  parse(*parsed_status_first_pass.second);
  cout << "status parsed second pass: " << parsed_status_second_pass << "\n";

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

// tokens: double linked list of tokens
Node::OpStatus LispExpr::parse(Node& tokens) {
  MYLOGGER(trace_function, "LispExpr::parse(Node&tokens)", __func__, SLOG_FUNC_INFO);
  cout << "parse tokens: " <<  tokens << "\n\n";
  if(tokens.type_ != Node::Type::List) {
    //cerr << "parse tokens type ! list: \n";
    //return {false, nullptr};
    return {true, tokens.clone()};

  }
  auto head_status = tokens.pop_front(); 
  //cout << "head_status: " <<  head_status << "\n";

  if(!head_status.first) {
    cerr << "head_status error from front(): " <<  head_status << "\n";
    return head_status;
  }
  auto head = get<Lisp::Op>(head_status.second->value_);
  auto &list = get<Node::List>(tokens.value_);

  switch(head) {
  case Lisp::Op::print:  {
    cout << "print: " <<  tokens << "\n";
    return {true, nullptr};}
  case Lisp::Op::list:  {
    cout << "parsing list: " <<  tokens << "\n";
    return {true, nullptr};}
    return build_parsed_list(list);
  case Lisp::Op::vector:  {
    cout << "parsing vector: " <<  tokens << "\n";
    return build_parsed_vector(list);
  }
  
  default: {
    //cout << "unknown: tokens: " <<  tokens << "\n";
    return {true, nullptr}; 
  }}
  return {true, nullptr};
}

Node::OpStatus LispExpr::build_parsed_vector(Node& node) {
  MYLOGGER(trace_function, "LispExpr::build_vector(Node&)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("node: ") + node._to_str(), SLOG_FUNC_INFO+30);
  if(node.type_ != Node::Type::List) {
  }
  auto &list = get<Node::List>(node.value_);
  return build_parsed_vector(list);
}

Node::OpStatus LispExpr::build_parsed_vector(Node::List& list) {
  MYLOGGER(trace_function, "LispExpr::build_vector(Node::List&list)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("list: ") + Node::_to_str(list), SLOG_FUNC_INFO+30);

  Node::Vector vl;
  vl.reserve(list.size());
  for(auto& ele: list) {
    if(ele->type_ == Node::Type::List) { // nested parsing
      MYLOGGER_MSG(trace_function, string("build nested list: ") + ele->_to_str(), SLOG_FUNC_INFO+30);
      auto status_parsed = parse(*ele);
      if(!status_parsed.first) return { false, nullptr};
      MYLOGGER_MSG(trace_function, string("returned list type: ") + Node::_to_str(status_parsed.second->type_), SLOG_FUNC_INFO+30);
      vl.push_back(move(status_parsed.second));
    } else 
    vl.push_back(move(ele->clone()));
  }
  return {true, Node::create(move(vl))};
}




Node::OpStatus LispExpr::build_parsed_deque(Node::List& list) {
  Node::DeQue dl;
  for(auto& e : list) dl.push_back(e->clone());
  return {true, Node::create(move(dl))};
}

Node::OpStatus LispExpr::build_parsed_list(Node::List& list) {
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