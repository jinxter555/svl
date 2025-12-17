#pragma once
#include "lang.hh"
#include "lisp.hh"

struct Token {
  Node::Integer col_;
  Node::Integer line_;
  string value_;
};
class LispExpr;

class LispReader  : public Lisp {
private:
  Node::Integer col_=1;
  Node::Integer line_=1;
  static const Node lisp_op_map;
  LispExpr *lisp;   // lisp to atom hasher

  string extract_quoted_string(const string&input, size_t &i);
public:
  LispReader(LispExpr*);
  //void tokenize(const string& input) { }
  //vector<Token> tokenize(const string& input);  // turn everything in to a stream of tokens
  list<Token> tokenize(const string& input);  // turn everything in to a stream of tokens
  Node::OpStatus parse(list<Token>& tokens);  // turn everything in to stream of node
  Node::OpStatus parse_sequence(list<Token>& tokens);  // turn everything in to stream of node
//  Node::OpStatus token_to_node(const Token& token);  // return node
 
  Lisp::Op str_to_op(const string&input);
  string _to_str(const list<Token>& tokens);
  void reset();
};