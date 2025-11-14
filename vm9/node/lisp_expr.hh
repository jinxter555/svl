#pragma once
#include "lang.hh"
#include "lisp.hh"
#include "lisp_reader.hh"

/*
 * Env: current_process, parent_process, 
 * frames[] = list of maps of current function vars
 * inbox, outbox, urgent = messages, message types = other_process, file, network, 
 * state = run, sleep, stopped, wait_send, wait_receive, wait_process_queues ,wait_dead, defunc(waiting to be collected),
 * control_flow_state = ret, loop
 * 
 */

class LispExpr : public Lang {
private:
  LispReader reader;
  static const vector<string> lisp_main_key ; 
  static const vector<string> lisp_path_key ; 
  static const vector<string> lisp_lang_atoms; 
  unique_ptr<Node> env_ptr;

  Node::OpStatus parse_def(const Node::List &list);
  void set_symbols();
  const Node::Integer sym_module, sym_fun, sym_mvar, sym_lvar, sym_class; // internal lisp hashed symbol values  (def :symbol ... )
public: 

  //enum class Keywords {def, call, ret, list, identifier};
  LispExpr();
  void bootstrap();
  //LispExpr(Node::Value v) : Tree() {}
  //LispExpr(vector<Node::ValueSimple> v) : Tree() {}
  
  Node::OpStatus build_program(const string& input); // create module structure 
  Node::OpStatus parse_node_tokens(Node& token_node); // create module structure 

//  Node::OpStatus parse(const string& input); // build lists
  Node::OpStatus parse_list(Node::List& list);
  Node::OpStatus get_env();

  LispReader& get_reader(); // lisp lexer and parser

  Node::Integer str_to_atom(const string& input);
  Node::OpStatus atom_to_str(Node::Integer v);


  //vector<Token> tokenize(const string& input) ;
  //Node::OpStatus parse(vector<Token>& tokens);
  void print();

  Node::OpStatus eval(Node& env);
  Node::OpStatus eval_list(Node& env, const Node::List& list);
  // 
  Node::OpStatus build_list(const Node::List& list);
  Node::OpStatus build_vector(const Node::List& list);
  Node::OpStatus build_deque(const Node::List& list);
  
  // Node::OpStatus builtin_add(Node& env, const Node::List& list, size_t start=0); Node::OpStatus builtin_mul(Node& env, const Node::List& list, size_t start=0); Node::OpStatus builtin_print(Node& env, const Node::List& list, size_t start=0); Node::OpStatus builtin_root(Node& env, const Node::List& list, size_t start=0);
  //
  template <typename T>
  Node::OpStatus builtin_add(Node& env, const T& list);
  template <typename T>
  Node::OpStatus builtin_print(Node& env, const T& list);
};