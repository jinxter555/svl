#include <iostream>
#include "lisp_reader.hh"
#include "lisp_expr.hh"

#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"

/*
unique_ptr<Node> tokenize(const string& input) {
  Node::List tokens;
  string token;
  for (char c : input) {
    if (isspace(c)) {
      if (!token.empty()) tokens.push_back(Node::create(token)), token.clear();
    } else if (c == '(' || c == ')') {
      if (!token.empty()) tokens.push_back(Node::create(token)), token.clear();
        tokens.push_back(Node::create(string(1, c)) );
    } else {
       token += c;
    }
  }
  if (!token.empty()) tokens.push_back(Node::create(token));
  return Node::create( move(tokens));
}
*/

//LispReader::lisp_op_map.set("kernel", Node::LispOp::kernel);

LispReader::LispReader(LispExpr *l) : lisp(l) {
  MYLOGGER(trace_function, "LispReader::LispReader(LispExpr *) ", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("keywords init: ") , SLOG_FUNC_INFO);

  Lisp::init();
}

void LispReader::reset() { col_=1; line_=1; }

Lisp::Op LispReader::str_to_op(const string &input) {
  MYLOGGER(trace_function, "LispReader::str_to_op()", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("lookup input: ") + input, SLOG_FUNC_INFO+30);

  //auto &map_ = Lisp::map_;

  if(Lisp::map_->type_ != Node::Type::Map) {
    cout << "lisp keyworld type != map\n";
    return Lisp::Op::error;
  }
  auto status = (*Lisp::map_)[input];
  if(!status.first) {
    MYLOGGER_MSG(trace_function, "keyword: " + input + " not found , return as identifier", SLOG_FUNC_INFO+30);
    return Lisp::Op::identifier;
  }
  auto op = get<Lisp::Op>(status.second->value_);
  return op;
}

list<Token> LispReader::tokenize(const string& input)  {
  MYLOGGER(trace_function, "LispReader::tokenize(string&input)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("input: ") + input, SLOG_FUNC_INFO+30);

  list<Token> tokens;
  Token token; 
  string token_str;
  for(char c : input) {
    if(isspace(c)) {
      if(!token_str.empty()) {
        //token.line_ = line_; token.col_ = col_;
        token.value_ = move(token_str);
        tokens.push_back(token);
      }
      if(c=='\n') line_++;
    } else if(c=='(' || c==')') {
      if(!token_str.empty()) {
        //token.line_ = line_; token.col_ = col_-1;
        token.value_ = move(token_str);
        tokens.push_back(token);
      }
      //token.line_ = line_; token.col_ = col_-1;
      token.value_ = string(1,c);
      tokens.push_back(token);

    } else {
      token_str += c;

    }
    col_++;
  }
  if(!token_str.empty()) {
    //token.line_ = line_; token.col_ = col_-1;
    token.value_ = move(token_str);
    tokens.push_back(token);
  }
  return tokens;

}

Node::OpStatus LispReader::parse(list<Token>& tokens) {
  if(tokens.empty()) 
    return {false, Node::create_error(Node::Error::Type::Incomplete, "Unexpected EOF parsing LispExpr.")};

  //Token token = tokens.front(); tokens.erase(tokens.begin());
  Token token = tokens.front(); tokens.pop_front();

  if(token.value_ == "(") {
    Node::List list;
    bool first_loop_run=true;
    while(tokens.front().value_ != ")") {

      auto status = parse(tokens); //if(first_loop_run && token.value_!= "(") {
      if(!status.first ) return {false, Node::create()};

      if(first_loop_run ) {       //cout << "first loop run: " << *status.second << "\n";
        string token_str;
        first_loop_run = false; 

        try {
           token_str = get<string>(status.second->value_);
        } catch(...) { 
          cout << "(keyword ): get<string>() keyword not string: " << *status.second << "\n";
          return {false, nullptr};
        }
        auto op = str_to_op(token_str); // Lisp::Op
        
        if(op == Lisp::Op::identifier)  { // identifier
          auto node_ptr = Node::create(token_str);
          node_ptr->set_identifier();
          list.push_back(move(node_ptr));

        } else 
        list.push_back(Node::create(op));
        continue;
      }

      if(status.first) list.push_back(move(status.second));
    }
    //tokens.erase(tokens.begin());
    tokens.pop_front();
    return {true, Node::create(move(list))};

  } else if(token.value_==")") {
    return {false, Node::create_error(Node::Error::Type::Incomplete, "Unexpected ')'.")};

  } else {
    // Float
    if(token.value_.find(".")  != std::string::npos) {
      try { 
        auto v = stod(token.value_);  //cout << "d v:" << v << "\n";
        return {true, Node::create(v)};
      } catch(...) {}
    }

    // Integer
    try { 
      auto v = stol(token.value_);  // cout << "l v:" << v << "\n";
      return {true, Node::create(v)}; 
    } catch(...) {}

    // atom
    if(token.value_[0]==':') {
      token.value_.erase(0, 1);
      auto v = lisp->str_to_atom(token.value_); //auto node_ptr = Node::create(atom);
      auto node_ptr = Node::create(v); node_ptr->set_atom();

      return {true, move(node_ptr)}; 
    }
  }

  // lisp identifier
  auto node_ptr = Node::create(token.value_); 
  node_ptr->set_identifier();
  return {true, move(node_ptr)};
}

