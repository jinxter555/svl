#pragma once
#include "lang.hh"
#include "lisp.hh"
#include "lisp_reader.hh"

/*
 * Env: current_process, parent_process, 
 * frames[] = list of maps of current function vars
 *  state = run, sleep, stopped, wait_send, wait_receive, wait_process_queues ,wait_dead, defunc(waiting to be collected),
 *  inbox, outbox, urgent = messages, message types = other_process, file, network, 
 * control_flow_state = ret, loop
 * 
 */
#define VAR "var"
#define IMMUTE "immute"
#define LVAR "lvar"
#define MVAR "Mvar"
#define NAME_SPACE "name_space"
#define CURRENT_MODULE "current_module"
#define CURRENT_FUNCTION "current_function"
#define FUNCTION "function"
#define CODE "code"
#define _PARAMS "params"
#define ARGS "args"
#define SCOPES "scopes"
#define DESC "description"
#define OBJ_INFO "__object_info__"

class LispExpr : public Lang, public Lisp {
private:
  LispReader reader;
  static const vector<string> lisp_path; 
  static const vector<string> lisp_path_module; 
  static const vector<string> lisp_path_keyword; 
  //static const vector<string> interactive_key; 
  static const vector<string> lisp_lang_atoms; 
  static const vector<string> cc_path; 
  static const vector<string> cc_path_module; 
 // static const vector<string> lisp_process; 
  unique_ptr<Node> env_ptr;

  Node::OpStatus parse_def(const Node::List &list);

  const Node::Integer sym_module, sym_fun, sym_mvar, sym_lvar, sym_class, sym_get, sym_set; // internal lisp hashed symbol values  (def :symbol ... )

  void set_keywords();
  Node::OpStatus attach_arguments_to_frame(unique_ptr<Node>& frame, const vector<string>& params_path, unique_ptr<Node> arg_list);

  


  // (call (module function)(...))  the module function to vector  path with prefix
  vector<string> node_mf_to_path(Node&node_,  const vector<string> prefix);
  vector<string> extract_mf(Node&process, Node&node); // extract module function
  vector<string> extract_mf(Node&process, Node::Vector &list); // extract module function

public: 
  Lisp::Op keyword_to_op(const string &kw); // convert 

  //enum class Keywords {def, call, ret, list, identifier};
  LispExpr();
  void bootstrap() override;

  Node::OpStatusRef process_create();
  //LispExpr(Node::Value v) : Tree() {}
  //LispExpr(vector<Node::ValueSimple> v) : Tree() {}
  
  Node::OpStatus build_program(const string& input); // create module structure 
  Node::OpStatus run_program(); // create module structure 

  Node::OpStatus attach_module(unique_ptr<Node> m);// create module structure 
  Node::OpStatus attach_cc_fun(const string&name, const Node::Fun& f);// create module structure 


  unique_ptr<Node> frame_create() const ; // create a frame 
  Node::OpStatus frame_push(Node&process, unique_ptr<Node>frame) ; // 
  Node::OpStatusRef frame_current(Node&process) ; // 

  unique_ptr<Node> scope_create() const ; // create a scope 
  Node::OpStatus scope_push(Node&process, unique_ptr<Node>scope) ; // add a scope to last scope of last frame
  Node::OpStatusRef scope_current(Node&process) ; // 

  Node::OpStatus var_attach(Node&process, const Node::Vector& var_list, int start=0) ; // 
  Node::OpStatus assign_attach(Node&process, const Node::Vector& var_list, int start=0) ; // 
  Node::OpStatusRef var_current(Node&scope) ; // 
  Node::OpStatusRef immute_current(Node&scope) ; // 

  Node::OpStatusRef arg_lookup(Node&process, const string&name ) ; // 
  // var lookup should pass frame 
  Node::OpStatusRef var_lookup(Node&scope, const string&name ) ; //  should use
  Node::OpStatusRef immute_lookup(Node&scope, const string&name ) ; //  should use
  Node::OpStatusRef symbol_lookup(Node&process, const string&name ) ; // 

  // parse Node::List of tokens, returns a hierarchical tree
  // of modules.function.mvar ...
  Node::OpStatus parse(Node& tokens); 
  Node::OpStatus parse_list(Node::List& list);
  Node::OpStatus get_process();

  LispReader& get_reader(); // lisp lexer and parser

  //Node::Integer str_to_atom(const string& input);
  //Node::OpStatus atom_to_str(Node::Integer v);


  //vector<Token> tokenize(const string& input) ;
  //Node::OpStatus parse(vector<Token>& tokens);
  void print();

  //Node::OpStatus eval(const Node& code, Node& process);
  Node::OpStatus eval(Node& process, const Node& code_node);
  Node::OpStatus eval(Node& process, const Lisp::Op op, const Node::Vector& code_list, int start=0);
  Node::OpStatus eval(Node& process, const Node::Vector& code_list);
  //Node::OpStatus eval_list(Node& process, const Node::List& list);

  Node::OpStatus call(Node& process, Node& code_node);
  Node::OpStatus call(Node& process, const Node::Vector& code_list, int start=0);
  // 
  Node::OpStatus build_parsed_list(Node& node);
  Node::OpStatus build_parsed_vector(Node& node);
  Node::OpStatus build_parsed_deque(Node& node);
  // 
  Node::OpStatus build_parsed_list(Node::List& list);
  Node::OpStatus build_parsed_vector(Node::List& list);
  Node::OpStatus build_parsed_deque(Node::List& list);
  Node::OpStatus build_parsed_map(Node::List& list); // ((k1 v1)(k2 v2)...)

  Node::OpStatus build_parsed_fun(Node::List& list); // (fun_name (param_list)(code list))
  Node::OpStatus build_parsed_module(Node::List& list); // (fun_name (param_list)(code list))
  Node::OpStatus build_parsed_root(Node::List& list); // (fun_name (param_list)(code list))
  //Node::OpStatus build_parsed_func(Node::List& list) ;

  // 
  Node::OpStatus car(Node&process, const Node::Vector &list, int start=0);
  Node::OpStatus cdr(Node&process, const Node::Vector &list, int start=0);
  //
  // (map ( (k1 v1) (k2 v2) )) //creates a new map object
  Node::OpStatus map_create(Node&process, const Node::Vector &list_kv, int start=0);
  Node::OpStatus map_messages(Node&process, const Node::Vector &list_kv, int start=0);
  // procdess, node this, arguments..
  static Node::OpStatus map_get_keys(Node&process, Node&map, const Node::Vector& args ={});

  //
  Node::OpStatus build_parsed_def(Node::List& list);
  
  //template <typename T>
  //Node::OpStatus builtin_add_n(Node& process, const T& list, size_t start=0); 
  //Node::OpStatus builtin_mul(Node& env, const Node::List& list, size_t start=0); Node::OpStatus builtin_print(Node& env, const Node::List& list, size_t start=0); Node::OpStatus builtin_root(Node& env, const Node::List& list, size_t start=0);
  //
  template <typename T>
  Node::OpStatus builtin_add(Node& process, const T& list);
  template <typename T>
  Node::OpStatus builtin_print(Node& process, const T& list);
  template <typename T>
  Node::OpStatus builtin_print_n(Node& process, const T& list, size_t start=0);

};