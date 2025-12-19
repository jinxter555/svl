#include "lisp_expr.hh"
#include <iostream>

#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"

extern Node null_node;

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

Node::OpStatusRef LispExpr::proc_create() {
  MYLOGGER(trace_function, "LispExpr::proc_create()", __func__, SLOG_FUNC_INFO);
  //MYLOGGER_MSG(trace_function, string("pid: ") + to_string(pid), SLOG_FUNC_INFO+30);

  auto proc_node = get_branch(lisp_process);
  cout << "proc type: " << Node::_to_str(proc_node->type_) << "\n";

  if(proc_node->type_ != Node::Type::Vector)
    return {false, *Node::create_error(Node::Error::Type::System,
      "lisp_process not a vector: " + _to_str_ext(lisp_process)) };
  
  auto pid = proc_node->size_container();
  Node::Map map={}; 

  map["pid"] = Node::create(pid);
  proc_node->push_back( Node::create(move(map))  );
  auto r = (*proc_node)[pid];

  //return {r.first, *r.second};
  //return {r.first, null_node};
  return proc_node->get_node(pid);

//  cout << "proc_node r: " <<  r << "\n";
//  cout << r.second->get_node(pid) << "\n";

  //return  {true, r.second->get_node()};
//  return  r.second->get_node(pid);
    


}

Node::OpStatus LispExpr::proc_read(size_t pid) {
  MYLOGGER(trace_function, "LispExpr::proc_read(pid)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("pid: ") + to_string(pid), SLOG_FUNC_INFO+30);
  auto proc_node = get_branch(lisp_process);
  cout << "proc type" << Node::_to_str(proc_node->type_) << "\n";
  auto proc_status = (*proc_node)[pid];

  if(!proc_status.first) {
    cout << "proc first" << pid << " error\n";
    return  proc_status;
  }
  if(proc_status.second==nullptr) {
    cout << "proc pid " << pid << " is nullptr\n";
  }
    cout << "proc status second" << *proc_status.second<< " \n";
  
  return (*proc_node)[pid];
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
  //cout << "first pass: " <<  *parsed_status_first_pass.second << "\n";
  //cout << "first pass: " <<  "\n";
  //parsed_status_first_pass.second->print();

  //return {true, Node::create()};

  if(!parsed_status_first_pass.first) {
    cerr << "building_program: Reader.tokenize() and Reader.parser(): parse error for input string: " << input  << "\n";
    cerr << "error: " <<  *parsed_status_first_pass.second << "\n";
    return  parsed_status_first_pass;
  }


  auto parsed_status_second_pass =  parse(*parsed_status_first_pass.second);

  //cout << "status parsed second pass1: " << parsed_status_second_pass << "\n"; cout << "\n\n";


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
  auto proc_kernel = proc_create();

  if(!env_status.first) {
    cerr << "no env_status ! found!\n";
    return env_status;
  }

  if(!proc_kernel.first) {
    cerr << "no proc_kernel ! found!\n";
    return {false, Node::create(false)};
  }
  cout << "kernel: " << proc_kernel.second << "\n";

  //cout << "run program node code!\n "; node_status.second.print();

  //eval(node_status.second,  *env_status.second);
  eval(node_status.second,  *env_status.second);
  return  {true, nullptr};

}
