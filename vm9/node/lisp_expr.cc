#include "lisp_expr.hh"
#include "my_helpers.hh"
#include <iostream>

#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"

extern Node null_node;

const vector<string> LispExpr::lisp_path= {UNIVERSE, "Lang", "Lisp"};
const vector<string> LispExpr::lisp_path_module= {UNIVERSE, "Lang", "Lisp", "Module"};
const vector<string> LispExpr::lisp_path_keyword= {UNIVERSE, "Lang", "Lisp", "Keyword"};
const vector<string> LispExpr::lisp_lang_atoms = {UNIVERSE, "module", "fun", "mvar", "lvar", "class"};
const vector<string> LispExpr::cc_path_module= {UNIVERSE, "Lang", "CC", "Module"};
//const vector<string> LispExpr::interactive_key  = {UNIVERSE, "interactive"};
//const vector<string> LispExpr::lisp_process = {UNIVERSE, "Process"};

LispExpr::LispExpr() : Lang(), Lisp(), reader(this)
, sym_module(str_to_atom("module"))
, sym_fun(str_to_atom("fun"))
, sym_class(str_to_atom("class"))
, sym_get(str_to_atom("get"))
, sym_set(str_to_atom("set"))
, sym_lambda(str_to_atom("lambda"))
 {
  MYLOGGER(trace_function, "LispExpr::LispExpr()", __func__, SLOG_FUNC_INFO);
  Node::Map map_module;
  //set_branch(lisp_path_module, Node::create(move(map_module)));
  //set_branch(lisp_path_module, Node::create(move(map_module)));
  set_branch(lisp_path_module, Node::create(Node::Type::Map));
  set_branch(cc_path_module, Node::create(Node::Type::Map));
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


extern ostream& operator<<(ostream& os, list<Token>& l) ;

//------------------------------------------------------------------------
Node::OpStatus LispExpr::build_program(const string& input) { 
  MYLOGGER(trace_function, "LispExpr::build_program(const string&input)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("input: ") + input, SLOG_FUNC_INFO+30);

  auto tokens_raw_text = reader.tokenize(input); // list<Token> raw text tokens

  // parse tokens, to integers, floats, strings, identifiers, lisp::op_s etc..
  // and returns Node::List 
  auto tokens_interpreted  = reader.parse(tokens_raw_text);  
  if(tokens_raw_text.size() != 0) cout << "error parsing left over tokens! [" << tokens_raw_text << "]\n";
  //cout << "endlist: " << _to_str_ext(reader.end_list);

  if(!tokens_interpreted.first) {
    cerr << "building_program: Reader.tokenize() and Reader.parser(): parse error for input string:\n" << input  << "\n\n";
    cerr << "error: " <<  *tokens_interpreted .second << "\n";
    return  tokens_interpreted ;
  }

  // builds the interpreter tree, as in modules and function hierarchy
  auto hierarchical_code_status =  parse(*tokens_interpreted.second); 

  if(!hierarchical_code_status.first) {
    cerr << "parse build interpreter error!" <<  hierarchical_code_status.second->_to_str() <<"\n";
    return hierarchical_code_status;
  }

  Node::Fun f;
  f = map_get_keys;
  //auto f = map_get_keys;

  //attach_cc_fun("map_get_keys", map_get_keys);
  attach_cc_fun("Map", "keys", map_get_keys);
  attach_cc_fun("Map", "get", map_get_value);
  attach_cc_fun("Map", "set", map_set_value);
  attach_cc_fun("Map", "del", map_del_key);
  attach_cc_fun("Map", "has", map_has_key);
  return attach_module(move(hierarchical_code_status.second));

}

//------------------------------------------------------------------------
//Node::OpStatus LispExpr::frame_create() const { 
unique_ptr< Node> LispExpr::frame_create() const { 
  MYLOGGER(trace_function, "LispExpr::frame_create()", __func__, SLOG_FUNC_INFO);
  Node::Map nm={}; //Node::Map lvar={};
  Node::Vector scope;
  scope.reserve(10);
  nm[SCOPES] = Node::create(move(scope));
  return Node::create(move(nm));
}

Node::OpStatus LispExpr::frame_push(Node&process, unique_ptr<Node>frame) {
  MYLOGGER(trace_function, "LispExpr::frame_push(Node&process)", __func__, SLOG_FUNC_INFO);
  auto key_status = process.has_key(FRAMES);

  if(!key_status.first) { 
    cerr << "process " << process[PID] << " has no frames!\n";
    return key_status;
  }
  if(!key_status.second->_get_bool() ) {
    return {false, Node::create_error(Error::Type::KeyNotFound, 
      "LispExpr::frame_push(...) no frames vector not found in process:")};
  }
  auto frames_status = process.get_node(FRAMES);
  if(!frames_status.first)
    return {false, Node::create_error(Error::Type::Unknown, "Can't get frames")};

  frames_status.second.push_back(move(frame));
  //cout << "process id: " << process[PID] << ": frame status " << frames_status << "\n";

  return {true, Node::create(true)};

}
Node::OpStatusRef LispExpr::frame_current(Node&process)  {
  MYLOGGER(trace_function, "LispExpr::frame_current(Node& process)", __func__, SLOG_FUNC_INFO);

  auto frames_ref_status = process[FRAMES];
  if(!frames_ref_status.first) {
    cerr << "frames[] doesn't exist!\n";
    return frames_ref_status;
  }
  auto s = frames_ref_status.second.size();

  auto frame_ref_back_status = frames_ref_status.second.back();
  if(!frame_ref_back_status.first) {
    cerr << "frames back() doesn't exist!\n";
  }
  return frame_ref_back_status;
}

//------------------------------------------------------------------------
// create a new scope with var and immute
unique_ptr<Node> LispExpr::scope_create() const {
  MYLOGGER(trace_function, "LispExpr::scope_create()", __func__, SLOG_FUNC_INFO);
  Node::Map scope={}; //Node::Map lvar={};
  scope[VAR] = Node::create(Node::Type::Map);
  scope[IMMUTE] = Node::create(Node::Type::Map);
  return Node::create(move(scope));
}

//push scope to the last scopes
Node::OpStatus LispExpr::scope_push(Node&process, unique_ptr<Node>scope) {
  MYLOGGER(trace_function, "LispExpr::scope_push(process, scope)", __func__, SLOG_FUNC_INFO);

  auto last_frame_ref_status = frame_current(process);

  if(!last_frame_ref_status.first) {
    return {false, Node::create_error(Error::Type::Unknown, "Can't get last frame aka back()")};
  }

  auto scopes_status = last_frame_ref_status.second.get_node(SCOPES);
  if(!scopes_status.first) {
    cerr << "scope_push() scope_status: " << scopes_status << "\n";
    return {false, Node::create_error(Error::Type::Unknown, "Can't get scopes")};
  }

  scopes_status.second.push_back(move(scope));
  return {true, Node::create(true)};

}

Node::OpStatusRef LispExpr::scope_current(Node&process)  {
  MYLOGGER(trace_function, "LispExpr::scope_current(Node& process)", __func__, SLOG_FUNC_INFO);


  auto frame_ref_back_status = frame_current(process);

  if(!frame_ref_back_status.first) return frame_ref_back_status;

  auto scopes_ref_status = frame_ref_back_status.second[SCOPES];
  if(!scopes_ref_status.first) {
    cerr << "scopes[] doesn't exist!\n";
    return scopes_ref_status;
  }

  auto scope_ref_back_status = scopes_ref_status.second.back();
  if(!scope_ref_back_status.first) {
    cerr << "scopes back() failed!"  << scope_ref_back_status.second._to_str() << "\n";
  }
  return  scope_ref_back_status;

  
  //auto s = r.second._to_str();
  //cout << "scopes back() " << scopes_ref_status.second << "\n";
  //cout << "scopes back() " << scopes_ref_status.second.back() << "\n";
  //return  {true, null_node};
  //return scopes_ref_status.second.back();
}



//------------------------------------------------------------------------
Node::OpStatus LispExpr::run_program() { 
  MYLOGGER(trace_function, "LispExpr::run_program()", __func__, SLOG_FUNC_INFO);


  vector<string> kernel_path=  LispExpr::lisp_path_module;
  //vector<string> code_path = {"Main", "function", "main", "code"};
  vector<string> code_path = {"Kernel", FUNCTION, "main", "code"};

  kernel_path.insert(kernel_path.end(), code_path.begin(), code_path.end());

  unique_ptr<Node> scope; Node::OpStatus scope_status;

  //  proc0
  auto frame = frame_create();
  auto proc_0  = process_get(0); 
  if(!proc_0.first) {
    return  {false, Node::create_error(
      Error::Type::InvalidOperation, 
      "LispExpr::run_program() Kernel proc 0 not found: " )};
  }

  frame->set(CURRENT_MODULE, "Kernel");
  frame->set("Pi", 3.1415);
  frame_push(proc_0.second, move(frame));
  scope = scope_create();
  scope_status =  scope_push(proc_0.second, move(scope));
  if(!scope_status.first) {
    cerr << "scope status is false: scope push failed " << *scope_status.second << "\n";
  }
    

  Node::OpStatusRef code_list_status = get_node(kernel_path);
  if(!code_list_status.first)  {
    cerr << _to_str_ext(kernel_path) << " path not found!\n";
    return  {false, Node::create_error(
      Error::Type::KeyNotFound, 
      "LispExpr::run_program() path node not found: " + _to_str_ext(kernel_path))};
  }

  // proc1
  auto frame1 = frame_create();
  frame1->set(CURRENT_MODULE, "Kernel");
  frame1->set(CURRENT_FUNCTION, "Main");
  auto proc_1= process_create();
  frame_push(proc_1.second, move(frame1));

  scope = scope_create();
  scope_status =  scope_push(proc_1.second, move(scope));
  if(!scope_status.first) {
    cerr << "scope status is false: scope push failed " << *scope_status.second << "\n";
  }

  if(!proc_1.first) {
    cerr << "no proc1 aka init ! found!\n";
    return {false, Node::create(false)};
  }

  //cout << "init: " << proc_1.second << "\n";

  return eval(proc_1.second, code_list_status.second);
  //return  {true, nullptr};

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

// create a var name list in current scope
// (var identifer1 (identifier2 value) ...)
Node::OpStatus LispExpr::var_attach(Node&process, const Node::Vector& var_list, size_t start)  {
  MYLOGGER(trace_function, "LispExpr::var_attach(process, var_list)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("var_list: ") + Node::_to_str(var_list), SLOG_FUNC_INFO+30);

  auto scope_ref_status = scope_current(process);
  if(!scope_ref_status.first) {
    cerr 
      << "something really wrong process: "  
      << Kernel::pid(process) 
      << " doesn't contain scope! "
      << scope_ref_status.second
      << "\n";

    return {false, scope_ref_status.second.clone()};
  }
  auto scope_vars_status = scope_ref_status.second.get_node(VAR);
  if(!scope_vars_status.first)  
    return {false, scope_vars_status.second.clone()};


  //cout << "current pid : " << Kernel::pid(process) << "\n";;
  size_t s = var_list.size();
  for(size_t i=start; i<s; i++) {
    auto const &ele = var_list[i];
    switch(ele->type_) {
    case Node::Type::Identifier: {
      scope_vars_status.second.set(ele->_to_str(),  make_unique<Node>());
      break; }
    case Node::Type::Vector: {
      auto v_name_ref_1 = (*ele)[0];
      auto v_var_ref_1 = (*ele)[1];
      auto v = eval(process, v_var_ref_1.second);
      if(!v.first) return v;
      scope_vars_status.second.set(v_name_ref_1.second._to_str(),  move(v.second));
      break; }
    default: return {false, Node::create_error(Error::Type::Unknown, "Unknown var error")}; }
  }
  return {true, Node::create(true)};
}


// assign to scope immute or var
Node::OpStatus LispExpr::assign_attach(Node&process, const Node::Vector& var_list, size_t start) {
  MYLOGGER(trace_function, "LispExpr::assign_attach(process, var_list)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("var_list: ") + Node::_to_str(var_list), SLOG_FUNC_INFO+30);
  auto identifier = var_list[start]->_to_str();
  auto &value_expr = var_list[start+1];
  auto value_status = eval(process, *value_expr);
  if(!value_status.first) return value_status;
  //cout << "ret value : " << value_status << "\n";

  //Node m1=make_shared<Node>(1);


  auto scope_ref_status = scope_current(process);
  if(!scope_ref_status.first) {
    cerr 
      << "something really wrong process: "  
      << Kernel::pid(process) 
      << " doesn't contain scope! "
      << scope_ref_status.second
      << "\n";

    return {false, scope_ref_status.second.clone()};
  }
  auto scope_vars_ref_status = scope_ref_status.second.get_node(VAR);
  if(!scope_vars_ref_status.first)  
    return {false, scope_vars_ref_status.second.clone()};

  auto scope_immute_ref_status = scope_ref_status.second.get_node(IMMUTE);
  if(!scope_immute_ref_status.first)  
    return {false, scope_immute_ref_status.second.clone()};


  // cout << "identifier " << identifier << "\n";

  auto nested_name = split_string(identifier, ".");

  
  if(nested_name.size() == 1) {   // assign non nested  map scalar value
    if(!scope_vars_ref_status.second.m_has_key(identifier)){
      if(!scope_immute_ref_status.second.m_has_key(identifier))  // doesn't exist and assign only once
        return scope_immute_ref_status.second.set(identifier,  Node::container_obj_to_US( move(value_status.second)));
      else  {
        cerr << "identifier " << identifier  <<" can not be reassigned\n";
        return {false, nullptr};
      }
    }
    return scope_vars_ref_status.second.set(identifier,  Node::container_obj_to_US( move(value_status.second)));

  }

  //return scope_vars_ref_status.second.set(identifier,  move(value_status.second));
  auto rv_ref_status = symbol_lookup(process, identifier );
  if(!rv_ref_status.first) {
    cerr << "assign map key error!" << rv_ref_status.second._to_str() << "\n";
    return {false, rv_ref_status.second.clone()};
  }
  //cout << "value_status : " << value_status << "\n";
  rv_ref_status.second = move(value_status.second);
  return {true, Node::create()};

}