#include "lisp_expr.hh"
#include <iostream>

#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"

extern Node null_node;

const vector<string> LispExpr::lisp_path= {UNIVERSE, "Lang", "Lisp"};
const vector<string> LispExpr::lisp_path_module= {UNIVERSE, "Lang", "Lisp", "Module"};
const vector<string> LispExpr::lisp_path_keyword= {UNIVERSE, "Lang", "Lisp", "Keyword"};
const vector<string> LispExpr::lisp_lang_atoms = {UNIVERSE, "module", "fun", "mvar", "lvar", "class"};
//const vector<string> LispExpr::interactive_key  = {UNIVERSE, "interactive"};
//const vector<string> LispExpr::lisp_process = {UNIVERSE, "Process"};

LispExpr::LispExpr() : Lang(), Lisp(), reader(this)
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
  set_branch(lisp_path_module, Node::create(move(map_module)));
  bootstrap();

  //set_branch(lisp_module_key, Node::create(Node::Type::Map));
  //for(auto &v : lisp_lang_atoms ) str_to_atom(v);
}

void LispExpr::bootstrap() {
  set_keywords();
  string boot_str = "(root set_branch (list Lang Lisp))";
  auto proc0 = process_create();

}


//Node::Integer  LispExpr::str_to_atom(const string& input) { return Lang::str_to_atom(input);}
//Node::OpStatus LispExpr::atom_to_str(Node::Integer v) { return Lang::atom_to_str(v); }

void LispExpr::print() {
  cout << "Lisp Interpreter\n";
  //cout << *root << "\n";
  Node::print_value_recursive(*root);
}

LispReader& LispExpr::get_reader() {
  return reader;
}


//------------------------------------------------------------------------
Node::OpStatus LispExpr::get_process() { 
  Node::Map nm={}; return {true, Node::create(move(nm))}; 
}



//------------------------------------------------------------------------
Node::OpStatus LispExpr::build_program(const string& input) { 
  MYLOGGER(trace_function, "LispExpr::build_program(const string&input)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("input: ") + input, SLOG_FUNC_INFO+30);

  auto tokens_raw_text = reader.tokenize(input); // list<Token> raw text tokens

  // parse tokens, to integers, floats, strings, identifiers, lisp::op_s etc..
  // and returns Node::List 
  auto tokens_interpreted  = reader.parse(tokens_raw_text);  

  if(!tokens_interpreted .first) {
    cerr << "building_program: Reader.tokenize() and Reader.parser(): parse error for input string: " << input  << "\n";
    cerr << "error: " <<  *tokens_interpreted .second << "\n";
    return  tokens_interpreted ;
  }


  // builds the interpreter tree, as in modules and function hierarchy
  auto hierarchical_code =  parse(*tokens_interpreted.second); 

  //auto attach_status = attach_module(hierarchical_code.second->clone());

  //auto attach_status = attach_module(move(hierarchical_code.second));
  return attach_module(move(hierarchical_code.second));
  //if(!attach_status.first) return attach_status;

  //auto process_status = get_process();
  //return parsed_status_second_pass;

  //return {true, Node::create(true)};

}

Node::OpStatus LispExpr::frame_create() const { 
  MYLOGGER(trace_function, "LispExpr::frame_create()", __func__, SLOG_FUNC_INFO);
  Node::Map nm={}; Node::Map lvar={};
  //return {true, Node::create(move(nm))}; 

  nm[CFS]=Node::create(Node::ControlFlow::cf_run);
  nm[LVAR]=Node::create(move(lvar));
  //nm[CURRENT_MODULE]=Node::create(CURRENT_MODULE);
  //nm[NAME_SPACE]=Node::create(NAME_SPACE);
  return {true, Node::create(move(nm))};

}

Node::OpStatus LispExpr::frame_push(Node&process, unique_ptr<Node>frame) {
  MYLOGGER(trace_function, "LispExpr::frame_push(Node&process)", __func__, SLOG_FUNC_INFO);
  auto key_status = process.has_key(FRAMES);

  if(!key_status.first) return key_status;
  if(!key_status.second->_get_bool() ) {
    return {false, Node::create_error(Node::Error::Type::KeyNotFound, 
      "LispExpr::frame_push(...) no frames vector not found in process:")};
  }
  auto frames_status = process.get_node(FRAMES);
  if(!frames_status.first)
    return {false, Node::create_error(Node::Error::Type::Unknown, "Can't get frames")};

  frames_status.second.push_back(move(frame));
  return {true, Node::create(true)};



}

Node::OpStatus LispExpr::run_program() { 
  MYLOGGER(trace_function, "LispExpr::run_program()", __func__, SLOG_FUNC_INFO);

  vector<string> kernel_path=  LispExpr::lisp_path_module;
  //vector<string> code_path = {"Main", "function", "main", "code"};
  vector<string> code_path = {"Kernel", "function", "main", "code"};

  kernel_path.insert(kernel_path.end(), code_path.begin(), code_path.end());

  Node::OpStatusRef code_list_status = get_node(kernel_path);
  if(!code_list_status.first)  {
    cerr << _to_str_ext(kernel_path) << " path not found!\n";
    return  {false, Node::create_error(
      Node::Error::Type::KeyNotFound, 
      "LispExpr::run_program() path node not found: " + _to_str_ext(kernel_path))};
  }

  auto proc_1= process_create();


  if(!proc_1.first) {
    cerr << "no proc1 aka init ! found!\n";
    return {false, Node::create(false)};
  }

  //cout << "init: " << proc_1.second << "\n";

  eval(proc_1.second, code_list_status.second);
  return  {true, nullptr};

}

Node::OpStatusRef  LispExpr::process_create() {
  MYLOGGER(trace_function, "LispExpr::process_create()", __func__, SLOG_FUNC_INFO);
  auto proc_status = Kernel::process_create();
  if(!proc_status.first) return proc_status;

//  auto frame_status = frame_create();
//  if(!frame_status.first) return proc_status;

 // frame_push(proc_status.second, move(frame_status.second));
  return proc_status;


}