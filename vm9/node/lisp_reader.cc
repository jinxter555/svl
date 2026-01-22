#include <iostream>
#include <cstring>
#include "lisp_reader.hh"
#include "lisp_expr.hh"
#include "my_helpers.hh"

#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"

ostream& operator<<(ostream& os, const Token& v) {
  cout << v.value_;
  return os;
}
ostream& operator<<(ostream& os, list<Token>& l) {
  for(auto v: l) {
    cout << v << " ";
  }
  cout << "\n";
  return os;
}

LispReader::LispReader(LispExpr *l) : lisp(l) {
  MYLOGGER(trace_function, "LispReader::LispReader(LispExpr *) ", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("keywords init: ") , SLOG_FUNC_INFO);

}

void LispReader::reset() { col_=1; line_=1; }

void LispReader::to_newline(const string&input, size_t &i) {
  for(++i; i<input.size(); i++) {
    char c = input[i];
    if(c=='\n') break;
  }
}

string LispReader::extract_quoted_string(const string&input, size_t &i) {
  string result;
  bool in_quote = true;
  bool escaped = false;
  for(++i; i<input.size(); i++) {
    char c = input[i];
    if(escaped) {
      //result += c;
      result += escaped_char(c);
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
string LispReader::extract_single_quoted_string(const string&input, size_t &i) {
  string result;
  bool in_quote = true;
  bool escaped = false;
  for(++i; i<input.size(); i++) {
    char c = input[i];
    if(escaped) {
      result += escaped_char(c);
      escaped = false;
    } else if(isspace(c)) {
      in_quote = !in_quote;
      break;
    } else {
      result += c;
    }
    
  }
  return result;
}


//------------------------------------------------------------------------ tokenize string  a list of tokens 
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
      if(c=='\n') { line_++; col_= 1; continue;}

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
    } else if(c == ';') {
      token_begin = true;
      if(!token_str.empty()) {
        token.value_ = move(token_str);
        tokens.push_back(token);
      }
      to_newline(input, i);
      line_++; col_ = 1; 
      continue;

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
 
  //size_t i=0, s=tokens.size();
  for(auto token : tokens) {
    result = result + ","  + token.value_;
  }
  return result + "]";
}


//------------------------------------------------------------------------ parse sequences of tokens after '('
Node::OpStatus LispReader::parse_sequence(list<Token>& tokens) {
  MYLOGGER(trace_function, "LispReader::sequence(list<Token>&tokens)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("tokens: ") + _to_str(tokens), SLOG_FUNC_INFO+30);
  Node::List list;
  bool is_first_element=true;
  string token_str;
  auto endable = tokens.front().value_ ;

  while(tokens.front().value_ != ")") {

    auto token_status = parse(tokens); //if(first_loop_run && token.value_!= "(") {


    if(!token_status.first) return { false, 
      Node::create_error(Error::Type::Parse, 
      "parsed error: " + token_status.second->_to_str() + "\n") };

    if(is_first_element) {
      is_first_element = false;

      // got a list after parse
      if(token_status.second->type_== Node::Type::List) { list.push_back(move(token_status.second)); continue; }

      try {  // see if (keyword) or (scalar)

        token_str = get<string>(token_status.second->value_);
        auto op = lisp->keyword_to_op(token_str); // Lisp::Op

        if(op != Lisp::Op::scalar)  { // identifier or scalar
          MYLOGGER_MSG(trace_function, string("Lisp::Op: ") + Lisp::_to_str(op), SLOG_FUNC_INFO+30);
          list.push_back(Node::create(op));
          continue;
        }

          //MYLOGGER_MSG(trace_function, string("scalar: ") + token_str, SLOG_FUNC_INFO+30);
          //list.push_back(move(token_status.second));
      } catch(...) {}

    } 
    // for endables returns a ')', break out
    if(token_status.second->is_nil()) { 
   //   cout << "return token is nil\n";
   //   cout << "tokens: " <<  tokens << "\n\n";
      break;
    }


    list.push_back(move(token_status.second));
  }


  token_previous.value_ = ")";
  tokens.pop_front(); // remove ')' token
  return {true, Node::create(move(list))};

}

//------------------------------------------------------------------------ parse a list of tokens
Node::OpStatus LispReader::parse(list<Token>& tokens) {
  MYLOGGER(trace_function, "LispReader::parse(list<Token>&tokens)", __func__, SLOG_FUNC_INFO);
  //MYLOGGER_MSG(trace_function, string("lookup input: ") + input, SLOG_FUNC_INFO+30);

  if(tokens.empty()) 
    return {false, Node::create_error(Error::Type::Incomplete, "Unexpected EOF parsing LispExpr.")};

  //Token token = tokens.front(); tokens.erase(tokens.begin());
  Token token_next, token = tokens.front(); tokens.pop_front();

  //cout << "token: '" <<  token << "', token_previous: '" << token_previous << "' \n";

  if(token.value_ == "'") { //  parse escaped literal list
    token_next = tokens.front(); tokens.pop_front();
    if(token_next.value_ == "(") {
      tokens.push_front({token_next.col_, token_next.line_, "literal"});
      return parse_sequence(tokens);
    }
  }

  if(token.value_ == "(") {
    token_previous.value_ = "(";
    return parse_sequence(tokens);

  } else if(token.value_==")") {

    return {false, Node::create_error(Error::Type::Incomplete, "Unexpected ')'.")};

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
      string esc_str = raw_to_escaped_string(token.value_);
      auto node_ptr = Node::create(esc_str); 
      return {true, move(node_ptr)}; 
    }
    if(token.value_[0]=='\'') {
      token.value_.erase(0, 1);
      string esc_str = raw_to_escaped_string(token.value_);
      auto node_ptr = Node::create(esc_str); 
      return {true, move(node_ptr)}; 
    }
    
  }

  if(is_endable(token.value_) ) {
   // cout << "is_endable! token: '" <<  token << "' return nil\n";
    tokens.push_front(token);
    return {true, Node::create()};
  }

  // liis_closurable as in begin{}end
  if(is_closurable(token.value_) && token_previous.value_ != "(") { 
    // add (closure identifier ) -> tokens
///*
  //  cout << "is_closurable! token: '" <<  token << "', token_previous: '" << token_previous << "' \n";
    tokens.push_front(token);
  //  cout << "tokens: " <<  tokens << "\n";
    end_list.push_back(token.value_); 
    token_previous.value_ = "(";
    return parse_sequence(tokens);

//*/
  }



  // lisp identifier 
  /*
  cout << "token: '" <<  token << "', token_previous: '" << token_previous << "' \n";
  token_previous.col_= token.col_;
  token_previous.line_= token.line_;
  token_previous.value_ = token.value_;
*/
  token_previous.value_ = token.value_;

  auto node_ptr = Node::create(token.value_); 
  node_ptr->set_identifier();
  return {true, move(node_ptr)};
}


//------------------------------------------------------------------------ 

bool LispReader::is_closurable(const string&token_str) {
  MYLOGGER(trace_function, "LispReader::is_closurable(const string&token_str) ", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, "token_str: " + token_str , SLOG_FUNC_INFO);
  auto op = lisp->keyword_to_op(token_str); // Lisp::Op
  return is_closurable(op);
}


//------------------------------------------------------------------------ 
bool LispReader::is_closurable(Lisp::Op op) {
  switch(op) {
  case Lisp::Op::class_:
  case Lisp::Op::module:
  case Lisp::Op::for_:
  case Lisp::Op::do_:
  case Lisp::Op::if_:
  case Lisp::Op::defun:
    return true;
  default: {}}
  return false;
}
//------------------------------------------------------------------------ 
bool LispReader::is_endable(const string&token_str) {
  MYLOGGER(trace_function, "LispReader::is_endable(const string&token_str) ", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, "token_str: " + token_str , SLOG_FUNC_INFO);

  auto list =  split_string(token_str, ".");
  //cout << "is_endalbe() token_str: " << token_str <<  ", list.size(): " << list.size() << "\n";

  string end="", op_str="";
  if(list.size() == 1)  { 
   op_str = list[0];
   if(op_str != "end") return false;
  } else if (list.size() == 2) {
    end=list[0], 
    op_str=list[1];
   if(end != "end") return false;
  }

  //cout << "end : " << end<< "\n";
  //cout << "opstr: " << op_str << "\n";

  auto op = lisp->keyword_to_op(op_str); // Lisp::Op
  return is_closurable(op);
}