#include "lisp_expr.hh"
#include "my_helpers.hh"
#include "interactive.hh"
#include "io_file.hh"
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
, atom_module(str_to_atom("module"))
, atom_fun(str_to_atom("fun"))
, atom_class(str_to_atom("class"))
, atom_get(str_to_atom("get"))
, atom_set(str_to_atom("set"))
, atom_ok(str_to_atom("ok"))
, atom_error(str_to_atom("error"))
, atom_lambda(str_to_atom("lambda"))
, atom_closure(str_to_atom("closure"))
, atom_else(str_to_atom("else"))
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

void LispExpr::set_interface(Interactive *intf) {
  interface=intf;
  interface->load_history();
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
Node::OpStatus LispExpr::build_file_str(const string& input) { 
  MYLOGGER(trace_function, "LispExpr::build_program(const string&input)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("input: ") + input, SLOG_FUNC_INFO+30);

  auto token_list = reader.tokenize( reader.tokenize_preprocess( input)); // list<Token> raw text tokens

  Node::OpStatus op_status;


  do{
    auto tokens_interpreted  = reader.parse(token_list);  
    //if(token_list.size() != 0) cout << "error parsing left over tokens! [" << token_list<< "]\n";
  
//    cout << "reader.endlist: " << _to_str_ext(reader.end_list) << "\n";

    if(!tokens_interpreted.first) {
      cout << "missing reader.endlist: " << _to_str_ext(reader.end_list) << "\n";
      cerr << "building_program: Reader.tokenize() and Reader.parser(): parse error for input string:\n" << input  << "\n\n";
      cerr << "error: " <<  *tokens_interpreted .second << "\n";
      return  tokens_interpreted ;
    }
  
    auto mod_code_status =  parse(*tokens_interpreted.second); 
  
    if(!mod_code_status.first) {
      cerr << "parse build interpreter error!" <<  mod_code_status.second->_to_str() <<"\n";
      return mod_code_status;
    }
    op_status = attach_module(move(mod_code_status.second));

  } while(token_list.size()!=0) ;


  return op_status;
}

void LispExpr::attach_cc_extern() {
  Node::Fun f;
  f = map_get_keys;

  //attach_cc_fun("map_get_keys", map_get_keys);
  attach_cc_fun("Map", "keys", map_get_keys);
  attach_cc_fun("Map", "get", map_get_value);
  attach_cc_fun("Map", "set", map_set_value);
  attach_cc_fun("Map", "del", map_del_key);
  attach_cc_fun("Map", "has", map_has_key);
  attach_cc_fun("System.Io.File", "apply", File::apply);

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
Node::OpStatus LispExpr::frame_pop(Node&process) {
  MYLOGGER(trace_function, "LispExpr::frame_pop(Node&process)", __func__, SLOG_FUNC_INFO);
  auto key_status = process.has_key(FRAMES);
  if(!key_status.first) { 
    cerr << "process " << process[PID] << " has no frames!\n";
    return key_status;
  }
  auto frames_status_ref = process.get_node(FRAMES);
  if(!frames_status_ref.first)
    return {false, Node::create_error(Error::Type::Unknown, "Can't get frames[] ")};
  //auto frame = frames_status_ref.second.back();

  return frames_status_ref.second.pop_back();

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
  scope[ARGS] = Node::create(Node::Type::Map);
  return Node::create(move(scope));
}

//push scope to the last scopes
Node::OpStatus LispExpr::scope_push_process(Node&process, unique_ptr<Node>scope) {
  MYLOGGER(trace_function, "LispExpr::scope_push_process(process, scope)", __func__, SLOG_FUNC_INFO);

  auto frame_ref_status = frame_current(process);

  if(!frame_ref_status.first) {
    return {false, Node::create_error(Error::Type::Unknown, "Can't get last frame aka back()")};
  }
  return scope_push_frame(frame_ref_status.second, move(scope));
}

Node::OpStatus LispExpr::scope_push_frame(Node&frame, unique_ptr<Node>scope) {
  MYLOGGER(trace_function, "LispExpr::scope_push_frame(frame, scope)", __func__, SLOG_FUNC_INFO);
  auto scopes_status = frame.get_node(SCOPES);

  if(!scopes_status.first) {
    cerr << "scope_push_frame() scope_status: " << scopes_status << "\n";
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
// post process  after all lisp files all loaded
//
Node::OpStatus LispExpr::build_program() { 
  MYLOGGER(trace_function, "LispExpr::build_program()", __func__, SLOG_FUNC_INFO);
  attach_cc_extern();
  return {true, Node::create()};
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
  scope_status =  scope_push_process(proc_0.second, move(scope));
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
  frame1->set(ARGS, Node::create(Node::Type::Map)); // empty args for now
  auto proc_1= process_create();
  //frame1->set(CURRENT_PROCESS_PTR, proc_1.second->pid(PID));
  frame1->set(PID, Kernel::pid(proc_1.second));
  frame_push(proc_1.second, move(frame1));

  scope = scope_create();
  scope_status =  scope_push_process(proc_1.second, move(scope));
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
  if(!scope_vars_status.first)   {
    return {false, scope_vars_status.second.clone()};
  }


  //cout << "current pid : " << Kernel::pid(process) << "\n";;
  size_t s = var_list.size();
  for(size_t i=start; i<s; i++) {
    auto const &ele = var_list[i];
    switch(ele->type_) {
    case Node::Type::Vector: {
      auto v_name_ref_1 = (*ele)[0];
      auto v_var_ref_1 = (*ele)[1];
      auto v = eval(process, v_var_ref_1.second);
      if(!v.first) return v;
      scope_vars_status.second.set(v_name_ref_1.second._to_str(),  move(v.second));
      break; }
    case Node::Type::Identifier: {
      scope_vars_status.second.set(ele->_to_str(),  Node::create());
      break;
    }
    default: return {false, Node::create_error(Error::Type::Unknown, "Unknown var error")}; }
  }
  return {true, Node::create(true)};
}


// (assign identifier value)
// (assign (var_list) (value_list) )  // have to match
// assign to scope immute or var
//
Node::OpStatus LispExpr::assign_attach(Node&process, const Node::Vector& var_list, size_t start) {
  MYLOGGER(trace_function, "LispExpr::assign_attach(process, var_list)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("var_list: ") + Node::_to_str(var_list), SLOG_FUNC_INFO+30);

  if(var_list.size() < 3) return  {false, Node::create_error(Error::Type::Parse, "assign has less than 3 parameters!") };

  if(var_list[start]->type_ == Node::Type::Vector) {


    if(var_list[start+1]->type_ == Node::Type::Identifier) {

      auto identifier_rhs = var_list[start+1]->_to_str();
      auto rhs_value_ref_status = symbol_lookup(process, identifier_rhs);
    
      if(!rhs_value_ref_status.first) 
        return {false, rhs_value_ref_status.second.clone()};

      if( rhs_value_ref_status.second.type_ != Node::Type::Shared )  {
        return {false, Node::create_error(Error::Type::Parse, "assign match parsing error: right hand side is not a list")};
      }
      if( rhs_value_ref_status.second._get_ptr_s()->type_ != Node::Type::Vector )  {
        return {false, Node::create_error(Error::Type::Parse, "assign match parsing error: right hand side is not a list")};
      }


      return assign_match(process, var_list[start]->_get_vector_ref(), rhs_value_ref_status.second._get_ptr_s()->_get_vector_ref());

    }

    if(var_list[start+1]->type_ != Node::Type::Vector) {
      return {false, Node::create_error(Error::Type::Parse, "assign match parsing error: values should be a list")};
    }
    return assign_match(process, var_list[start]->_get_vector_ref(), var_list[start+1]->_get_vector_ref());
  }

  auto identifier = var_list[start]->_to_str();
  if(var_list[start]->type_ != Node::Type::Identifier) {
    auto errmsg = "can't assign to a non identifier variable '" + identifier + "'";
    cerr << errmsg << "\n";
    return {false, Node::create_error(Error::Type::Parse, errmsg)};
  }
  auto &value_expr = var_list[start+1];
  auto value_status = eval(process, *value_expr);
  if(!value_status.first) return value_status;
  //cout << "ret value : " << value_status << "\n";
  return assign_attach(process, identifier, move(value_status.second));

}

//
// = (a b c) (1 2 3)
// = (:ok b c) (:ok 2 3)  good assign
// = (:ok b c) (:error 2 3)  no assign
//
Node::OpStatus LispExpr::assign_match(Node&process, const Node::Vector& var_list, const Node::Vector& value_list) {
  MYLOGGER(trace_function, "LispExpr::assign_attach(process, var_list)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("var_list: ") + Node::_to_str(var_list), SLOG_FUNC_INFO+30);
  MYLOGGER_MSG(trace_function, string("value_list: ") + Node::_to_str(value_list), SLOG_FUNC_INFO+30);

  size_t var_size = var_list.size(), value_size = value_list.size(), assign_upto;
  if(var_size > value_size) return { false, Node::create_error(Error::Type::Parse, "left hand variable side is > right hand value size") };

  if(var_size < value_size) {
    assign_upto = var_size -1;
  } else assign_upto = var_size;

  //for(size_t i=0; i<var_s; i++) {
  for(size_t i=0; i<assign_upto; i++) {
    auto &lhs = var_list[i];
    auto identifier = lhs->_to_str();
    if(value_list[i] == nullptr) { 
      auto msg =  "Maybe wrong input for assign match var_list " + Node::_to_str(var_list)  + ", value_list " + Node::_to_str(value_list);
      cerr << msg << "\n";
      return {false, Node::create_error(Error::Type::Unknown,  msg)};


    }
    auto value_status = eval(process, *value_list[i]);

    if(!value_status.first) {
      cerr << "assign match() eval error:" << value_status.second->_to_str() << "\n";
      return value_status;
    }
    // if lhs == identifier, assignment
    if(lhs->type_ == Node::Type::Identifier) {
      if (identifier=="_") continue;

      auto assign_status = assign_attach(process, identifier, move(value_status.second));
      if(!assign_status.first) {
        cerr << "assign match() assign error:" << assign_status.second->_to_str() << "\n";
        return assign_status;
      }
    } else { // this is comparision 
      auto bv = *lhs != *value_status.second;
      if( bv._get_bool()) {
        //cout << *lhs << " != " << *value_status.second << "\n";
        //return {false, Node::create_error(Error::Type::NotEqual, "assign comparison not equal!")};
        return {true, Node::create(false)}; // operation is good but assign comparision false
      }
    }
  }
  // check the rest of the right hand side list
  // and assign it if the last left hand side element has an '*'
  if(var_size < value_size) {
    auto &lhs = var_list.back();
    auto identifier = lhs->_to_str();
    if(identifier.front() == '*') { // assign all 
      identifier.erase(0, 1); // remove '*'
      Node::Vector result_vec;
      for(size_t i=var_size -1; i<value_size; i++) {
        auto value_status = eval(process, *value_list[i]);
        if(!value_status.first) {
          cerr << "assign match() eval error:" << value_status.second->_to_str() << "\n";
          return value_status;
        }
        result_vec.push_back(move(value_status.second));
      }
      auto assign_status = assign_attach(process, identifier, Node::create(move(result_vec)));

      if(!assign_status.first) {
        cerr << "assign match() assign error:" << assign_status.second->_to_str() << "\n";
        return assign_status;
      }
    } else {
      return { false, Node::create_error(Error::Type::NotEqual, "left hand variable side is < right hand value size") };
    }
  }

  //return {true, Node::create(atom_ok, Node::Type::Atom)};
  return {true, Node::create(true)};
}

Node::OpStatus LispExpr::assign_attach(Node&process, const string& identifier, unique_ptr<Node> value_ptr) {

  //auto &value_ptr = value_status.second;

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


  auto scope_args_ref_status = scope_ref_status.second.get_node(ARGS);

  if(!scope_args_ref_status.first)   {
    cout << "scope ref status " <<  scope_ref_status.second << "\n";
    cout << "scope args ref not found!\n";
    return {false, scope_args_ref_status.second.clone()};
  }

  // cout << "identifier " << identifier << "\n";

  auto nested_name = split_string(identifier, ".");

  
  if(nested_name.size() == 1) {   // assign non nested  map scalar value
    if(!scope_vars_ref_status.second.m_has_key(identifier)){
      if(!scope_immute_ref_status.second.m_has_key(identifier))  // doesn't exist and assign only once
        return scope_immute_ref_status.second.set(identifier,  Node::container_obj_to_US( move(value_ptr)));
      else  {
        cerr << "identifier '" << identifier <<"' can not be reassigned\n";
        return {false, nullptr};
      }
    }
    return scope_vars_ref_status.second.set(identifier,  Node::container_obj_to_US( move(value_ptr)));

  }

  //   !scope_args_ref_status.second.m_has_key(nested_name[0])){
  // need to change to allow args
  if(!scope_vars_ref_status.second.m_has_key(nested_name[0]) &&
      !scope_args_ref_status.second.m_has_key(nested_name[0])){
    //cerr << "identifier " << identifier  <<" can not be reassigned\n";
    cerr << "Identifier: '" << nested_name[0] <<"' is not a variable. Object and Maps have to be variables to be re-assigned\n";
    return {false, nullptr};
  }

  //return scope_vars_ref_status.second.set(identifier,  move(value_status.second));
  auto rv_ref_status = symbol_lookup(process, identifier );
  if(!rv_ref_status.first) {
    cerr << "assign map key error!" << rv_ref_status.second._to_str() << "\n";
    return {false, rv_ref_status.second.clone()};
  }
  //cout << "value_status : " << value_status << "\n";
  rv_ref_status.second = move(value_ptr);
  return {true, Node::create(true)};

}