#pragma once
#include "lang.hh"
#include "lisp.hh"
#include "lisp_reader.hh"
#include "defs.hh"

/*
 * Env: current_process, parent_process, 
 * frames[] = list of maps of current function vars
 *  state = run, sleep, stopped, wait_send, wait_receive, wait_process_queues ,wait_dead, defunc(waiting to be collected),
 *  inbox, outbox, urgent = messages, message types = other_process, file, network, 
 * control_flow_state = ret, loop
 * 
 */
class Interactive;

class LispExpr : public Lang, public Lisp {
  friend class Interactive;
private:
  Interactive *interface; // interface with command line, repl prompt, 
  LispReader reader;
  static const vector<string> lisp_path; 
  static const vector<string> lisp_path_module; 
  static const vector<string> lisp_path_keyword; 
  //static const vector<string> interactive_key; 
  static const vector<string> lisp_lang_atoms; 
  static const vector<string> cc_path; 
  static const vector<string> cc_path_module; 
  static bool forever ;
 // static const vector<string> lisp_process; 
  unique_ptr<Node> env_ptr;

  Node::OpStatus parse_def(const Node::List &list);

  const Node::Integer atom_module, atom_fun, atom_class, atom_get, atom_set, atom_ok, atom_error,
  atom_lambda, atom_closure;
  // internal lisp hashed symbol values  (def :symbol ... )

  void set_keywords();




  Node::OpStatus scope_params_args(const vector<string>& params, Node::Vector &&args); // create new scope with params and args

  Node::OpStatus attach_this_to_arguments(Node::Vector& list_args); // attach 'this' variable to a class method 

  Node::OpStatus attach_class_vars_to_object(Node&process, Node&object, Node::Vector& list_args); // attach 'this' variable to a class method 

  


  // (call (module function)(...))  the module function to vector  path with prefix
  //vector<string> node_mf_to_path(Node&node_,  const vector<string> prefix);
  vector<string> extract_mf(Node&process, Node&node); // extract module function
  vector<string> extract_mf(Node&process, Node::Vector &list); // extract module function

  Node::Vector list_clone_remainder(const Node::Vector &list, size_t start=0); 
  Node::Vector list_2_vector(Node::List &&list); 

  Node::OpStatus vector_to_object(const Node::Vector&list); // return an object, object_info with type = head aka Lisp::Type or Lisp::Op

  vector<string> get_params(const Node::Map&caller);

public: 
  Lisp::Op keyword_to_op(const string &kw); // convert 

  //enum class Keywords {def, call, ret, list, identifier};
  LispExpr();
  void set_interface(Interactive *);
  void bootstrap() override;

  Node::OpStatusRef process_create();
  //LispExpr(Node::Value v) : Tree() {}
  //LispExpr(vector<Node::ValueSimple> v) : Tree() {}
  
  Node::OpStatus run_program(); // create module structure 
  Node::OpStatus build_program(); // create module structure 
  Node::OpStatus build_file_str(const string& input); // create module structure 

  Node::OpStatus attach_module(unique_ptr<Node> m);// create module structure 

  void attach_cc_extern();

  Node::OpStatus attach_cc_fun(const string&name, const Node::Fun& f);// create module structure 
  Node::OpStatus attach_cc_fun(const string&name_mod, const string&name_fun, const Node::Fun& f);// create module structure 
  Node::OpStatus attach_cc_fun(const vector<string>&name, const Node::Fun& f);// 


  unique_ptr<Node> frame_create() const ; // create a frame 

  //Node::OpStatus   frame_create_params_args(const vector<string>& params, Node::Vector &&args);
  Node::OpStatus   frame_create_fun_args(Node&fun, Node::Vector &&args);
  Node::OpStatus   frame_create_fun_args_lambda(Node &process, Node&fun, Node::Vector &&args);

  Node::OpStatus frame_push(Node&process, unique_ptr<Node>frame) ; // 
  Node::OpStatus frame_pop(Node&process);
  Node::OpStatusRef frame_current(Node&process) ; // 

  unique_ptr<Node> scope_create() const ; // create a scope 
  Node::OpStatus scope_push_process(Node&process, unique_ptr<Node>scope) ; // add a scope to last scope of last frame
  Node::OpStatus scope_push_frame(Node&frame, unique_ptr<Node>scope) ; // add a scope to last scope of last frame
  Node::OpStatusRef scope_current(Node&process) ; // 

  Node::OpStatus var_attach(Node&process, const Node::Vector& var_list, size_t start=0) ; // 
  Node::OpStatus assign_attach(Node&process, const Node::Vector& var_list, size_t start=0) ; // 
  Node::OpStatus assign_attach(Node&process, const string& identifier, unique_ptr<Node>value_ptr) ; //  assign a value 
  Node::OpStatus assign_match(Node&process, const Node::Vector& var_list, const Node::Vector& value_list) ; //  assign a value 
  Node::OpStatusRef var_current(Node&scope) ; // 
  Node::OpStatusRef immute_current(Node&scope) ; // 

  // class
  Node::OpStatusRef get_class(deque<string> mfc) ; //  module class ,  1

  // var lookup should pass frame 
  Node::OpStatusRef arg_lookup(Node&scope, const string&name ) ; // 
  Node::OpStatusRef var_lookup(Node&scope, const string&name ) ; //  should use
  Node::OpStatusRef immute_lookup(Node&scope, const string&name ) ; //  should use
  Node::OpStatusRef symbol_lookup(Node&process, const string&name ) ; // 

  // parse Node::List of tokens, returns a hierarchical tree
  // of modules.function.mvar ...
  Node::OpStatus read_input(); 
  Node::OpStatus parse(Node& tokens); 

  //Node::OpStatus parse_list(Node::List& list);
  Node::OpStatus get_process();

  LispReader& get_reader(); // lisp lexer and parser

  //Node::Integer str_to_atom(const string& input);
  //Node::OpStatus atom_to_str(Node::Integer v);

  Node::OpStatus root_manifest(Node& process, const Node::Vector& code_list, size_t start);


  //vector<Token> tokenize(const string& input) ;
  //Node::OpStatus parse(vector<Token>& tokens);
  void print();

  //Node::OpStatus eval(const Node& code, Node& process);
  Node::OpStatus eval(Node& process, const Node& code_node);
  Node::OpStatus eval(Node& process, const Lisp::Op op, const Node::Vector& code_list, size_t start=0);
  inline Node::OpStatus eval_math(Node& process, const Lisp::Op op, const Node::Vector& code_list, size_t start=0);
  Node::OpStatus eval(Node& process, const Node::Vector& code_list); // this figures what to do
  Node::OpStatus eval(Node& process, const Node::Vector& code_list, size_t start); // eval each as an element node
  Node::OpStatus eval_eval(Node& process, const Node::Vector& code_list, size_t start);

  //Node::OpStatus eval_list(Node& process, const Node::List& list);

  Node::OpStatus loop_forever(Node& process, const Node::Vector& code_list, size_t start=0);
  Node::OpStatus while_(Node& process, const Node::Vector& code_list, size_t start=0);

  Node::OpStatus if_(Node& process, const Node::Vector& code_list, size_t start=0);

  Node::OpStatus call(Node& process, const Node& code_node); 
  Node::OpStatus call(Node& process, const Node::Vector& code_list, size_t start=0); // (call (module function) (arg1 arg2 arg3))
  Node::OpStatus faz(Node& process, const Node::Vector& code_list, size_t start=0); // (call (module function) (arg1 arg2 arg3))
  Node::OpStatus call(Node& process, const vector<string>& path, const Node::Vector& argv_list); // 

  Node::OpStatus call_macro(Node& process, const vector<string>&path , const Node::Vector& argv_list);

  Node::OpStatus call(Node& process, Node& fun, Node::Vector&& params);


  Node::OpStatus funcall(Node& process, const Node::Vector& code_list, size_t start=0); // creates new frame push args to args
  //Node::OpStatus call_lambda(Node& process, const Node::Map & obj_lambda, Node::Vector&& args); // call creates new scope and push args to scope immute

  Node::OpStatus call_lambda(Node& process, Node& obj_lambda, Node::Vector&& args); // call creates new scope and push args to scope immute

  Node::OpStatus call_closure(Node& process, const Node::Map & obj_closure, Node::Vector&& args); // call creates new scope and push args to scope immute
//  Node::OpStatus call_object(Node& process, const Node::Map & obj, const Node::Vector& args); // call object with Node::Map as primitive type

  Node::OpStatus call_extern(Node& process, const Node::Vector& code_list, size_t start=0);
  Node::OpStatus call_extern(Node& process, const string&mod, const string&fun ,  Node& node_this, const Node::Vector& args);
  // 
  Node::OpStatus build_parsed_list(Node& node);
  Node::OpStatus build_parsed_vector(Node& node);
  Node::OpStatus build_parsed_deque(Node& node);
  // 
  Node::OpStatus build_parsed_list(Node::List& list);
  Node::OpStatus build_parsed_vector(Node::List& list);
  Node::OpStatus build_parsed_deque(Node::List& list);
  Node::OpStatus build_parsed_map(Node::List& list); // ((k1 v1)(k2 v2)...)

  Node::OpStatus build_parsed_fun(Node::List& cc_list); // (fun_name (param_list)(code list))
  Node::OpStatus build_parsed_macro(Node::List& cc_list); // (fun_name (param_list)(code list))
  Node::OpStatus build_parsed_module(Node::List& cclist); // (fun_name (param_list)(code list))
  Node::OpStatus build_parsed_class(Node::List& cclist); // (fun_name (param_list)(code list))
  Node::OpStatus build_parsed_root(Node::List& cclist); // (fun_name (param_list)(code list))
  //Node::OpStatus build_parsed_func(Node::List& list) ;


  // 
  Node::OpStatus car(Node&process, const Node::Vector &list, size_t start=0);
  Node::OpStatus cdr(Node&process, const Node::Vector &list, size_t start=0);
  //
  // (map ( (k1 v1) (k2 v2) )) //creates a new map object
  Node::OpStatus hash_create(Node&process, const Node::Vector &list_kv, size_t start=0);
  Node::OpStatus ihash_create(Node&process, const Node::Vector &list_kv, size_t start=0);
  Node::OpStatus object_create(Node&process, const Node::Vector &list, size_t start=0);
  Node::OpStatus send_object_message(Node&process, const Node::Vector &list, size_t start=0);
  Node::OpStatus call_object(Node&Process, Node& object, const string method_fun, const Node::Vector&argv_list);

  // procdess, node this, arguments..
  static Node::OpStatus map_del_key(Node&process, Node&map, const Node::Vector& args ={});
  static Node::OpStatus map_has_key(Node&process, Node&map, const Node::Vector& args ={});
  static Node::OpStatus map_get_keys(Node&process, Node&map, const Node::Vector& args ={});
  static Node::OpStatus map_get_value(Node&process, Node&map, const Node::Vector& args ={}); // get value index by key
  static Node::OpStatus map_set_value(Node&process, Node&map, const Node::Vector& args ={}); // get value index by key
  //
  Node::OpStatus lambda_create(Node&process, const Node::Vector &list, size_t start=0);
  Node::OpStatus lambda_bind_early(Node&process, const Node::Vector &list, size_t start=0); // binding outter scope vars when created
  //
  Node::OpStatus closure_create(Node&process, const Node::Vector &list, size_t start=0);
  
  Node::OpStatus literal(const Node::Vector &list, size_t start=0);
  Node::OpStatus quote(Node&process, const Node::Vector &list, size_t start=0);
  Node::OpStatus unquote(Node&process, const Node::Vector &list, size_t start=0);

  // handle control flow object
  Node::ControlFlow handle_cf_object(Node&process, Node::Vector &result_list, const Node::Map& object); // handles (return ... :ok )
  Node::ControlFlow handle_cf_object(Node&process, const Node::Map& object); // just returns
  Node::ControlFlow handle_cf_object_return(Node&process, Node::Vector &result_list, const Node::Map& object);

  Node::OpStatus cf_object_to_OpStatus(Node&process, unique_ptr<Node> object_ptr); // if returns object  or just regular optstauts
  
  //
  Node::OpStatus lisp_object_return(Node&process, const Node::Vector &code_list, size_t start=0);
  

  //
  Node::OpStatus build_parsed_def(Node::List& list);
  
  //template <typename T>
  //Node::OpStatus builtin_add_n(Node& process, const T& list, size_t start=0); 
  //Node::OpStatus builtin_mul(Node& env, const Node::List& list, size_t start=0); Node::OpStatus builtin_print(Node& env, const Node::List& list, size_t start=0); Node::OpStatus builtin_root(Node& env, const Node::List& list, size_t start=0);
  //
  template <typename T>
  Node::OpStatus builtin_add(Node& process, const T& list);
  template <typename T>
  Node::OpStatus builtin_sub(Node& process, const T& list);
  template <typename T>
  Node::OpStatus builtin_mul(Node& process, const T& list);
  template <typename T>
  Node::OpStatus builtin_div(Node& process, const T& list);


  template <typename T>
  Node::OpStatus builtin_print_n(Node& process, const T& list, size_t start=0);
  Node::OpStatus builtin_print_r(Node& process, const Node::Vector& cc_vec, size_t start=0);

};