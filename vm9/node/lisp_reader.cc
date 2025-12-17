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
    MYLOGGER_MSG(trace_function, "Lisp keyword: " + input + " not found , return as scalar", SLOG_FUNC_INFO+30);
    return Lisp::Op::scalar;
  }
  auto op = get<Lisp::Op>(status.second->value_);
  return op;
}

//
string LispReader::extract_quoted_string(const string&input, size_t &i) {
  string result;
  bool in_quote = true;
  bool escaped = false;
  for(++i; i<input.size(); i++) {
    char c = input[i];
    if(escaped) {
      result += c;
      escaped = false;
    }  else if(c == '\\') {
      escaped = true;
    } else if(c =='"') {
      in_quote = !in_quote;
      break;
    } else {
      result += c;
    }
    
  }
  return result;

}

list<Token> LispReader::tokenize(const string& input)  {
  MYLOGGER(trace_function, "LispReader::tokenize(string&input)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("input: ") + input, SLOG_FUNC_INFO+30);

  list<Token> tokens;
  Token token; 
  string token_str;
  bool token_begin = false;
  //for(char c : input) {
  for(size_t i=0; i<input.size(); i++) {
    char c = input[i];
    if(isspace(c)) {
      token_begin = true;
      if(!token_str.empty()) {
        //token.line_ = line_; token.col_ = col_;
        token.value_ = move(token_str);
        tokens.push_back(token);
      }
      if(c=='\n') {line_++; col_= 1;};

    } else if(c=='(' || c==')') {
      token_begin = true;

      if(!token_str.empty()) {
        //token.line_ = line_; token.col_ = col_-1;
        token.value_ = move(token_str);
        tokens.push_back(token);
      }
      //token.line_ = line_; token.col_ = col_-1;
      token.value_ = string(1,c);
      tokens.push_back(token);

    } else if(c == '"') {
      //token.value_ = move(extract_quoted_string(input, i));
      token.value_ = "\"" + move(extract_quoted_string(input, i));
      tokens.push_back(token);
      token_begin = true;
    } else {
      if(token_begin) { token.col_ = col_; token_begin=false;}
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

string LispReader::_to_str(const list<Token>& tokens) {
  string result="[";

  size_t i=0, s=tokens.size();
  for(auto token : tokens) {
    result = result + ","  + token.value_;
  }
  return result;
}


Node::OpStatus LispReader::parse_sequence(list<Token>& tokens) {
  MYLOGGER(trace_function, "LispReader::sequence(list<Token>&tokens)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("tokens: ") + _to_str(tokens), SLOG_FUNC_INFO+30);
  Node::List list;
  bool is_first_element=true;
  string token_str;

  while(tokens.front().value_ != ")") {

    auto token_status = parse(tokens); //if(first_loop_run && token.value_!= "(") {

    if(!token_status.first) return { false, 
      Node::create_error(Node::Error::Type::Parse, 
      "parsed error: " + token_status.second->_to_str() + "\n") };

    if(is_first_element) {
      is_first_element = false;

      // got a list after parse
      if(token_status.second->type_== Node::Type::List) { list.push_back(move(token_status.second)); continue; }

      try {  // see if (keyword) or (scalar)

        token_str = get<string>(token_status.second->value_);
        auto op = str_to_op(token_str); // Lisp::Op

        if(op != Lisp::Op::scalar)  { // identifier or scalar
          MYLOGGER_MSG(trace_function, string("Lisp::Op: ") + Lisp::_to_str(op), SLOG_FUNC_INFO+30);
          list.push_back(Node::create(op));
          continue;
        }

          //MYLOGGER_MSG(trace_function, string("scalar: ") + token_str, SLOG_FUNC_INFO+30);
          //list.push_back(move(token_status.second));
      } catch(...) {}

    } 
    list.push_back(move(token_status.second));
  }

  tokens.pop_front(); // remove ')' token
  return {true, Node::create(move(list))};

}

Node::OpStatus LispReader::parse(list<Token>& tokens) {
  MYLOGGER(trace_function, "LispReader::parse(list<Token>&tokens)", __func__, SLOG_FUNC_INFO);
  //MYLOGGER_MSG(trace_function, string("lookup input: ") + input, SLOG_FUNC_INFO+30);

  if(tokens.empty()) 
    return {false, Node::create_error(Node::Error::Type::Incomplete, "Unexpected EOF parsing LispExpr.")};

  //Token token = tokens.front(); tokens.erase(tokens.begin());
  Token token = tokens.front(); tokens.pop_front();

  if(token.value_ == "(") {
    return parse_sequence(tokens);

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
    // " quoted string with 
    if(token.value_[0]=='"') {
      token.value_.erase(0, 1);
      auto node_ptr = Node::create(token.value_); 
      return {true, move(node_ptr)}; 
    }
    
  }

  // lisp identifier
  auto node_ptr = Node::create(token.value_); 
  node_ptr->set_identifier();
  return {true, move(node_ptr)};
}

