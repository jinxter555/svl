#include <iostream>
#include <variant>
#include <string>
#include <vector>
#include <stack>
#include <math.h>
#include "token.hh"

using namespace std;


void Token::print() {
  visit([](auto&& arg) {
    cout << "token value: " << arg << endl;
  }, value);
}

Token::Token(string str) {
  if(str.find_first_not_of("0123456789") == string::npos) {
    value = stoi(str), 
    type =   INTEGER;
  } else if (str.find_first_not_of("0123456789.") == string::npos) {
    value = stof(str);
    type = FLOAT;
  } else if (is_operator(str)) {
    value = str;
    type = OPERATOR;
  } else {
    value = str, 
    type = STRING;
  }
}


bool Token::is_operator(string op) {
  if (op == "+" || op == "-"||  op== "*" || op == "/" || op == "^" )
    return true;
  else
    return false;
}

string Token::op() const {
  if(is_operator()) {
    return get<string>(value);
  }
  return string("");
}

string Token::funcname() const {
  return get<string>(value);
}

bool Token::operator==(const string& rhs) const {
  return get<string>(value) == rhs;
}

bool Token::operator==(const char* rhs) const { 
 return operator==(string(rhs));                                                             
};   


template <typename T> 
T calc_v(string op, T a, const Token& t_b) {
  T b;
  switch(t_b.type) {
    case INTEGER:
      b = (T)get<int>(t_b.value);
      break;
    case FLOAT:
      b = (T)get<float>(t_b.value);
      break;
    default:
      break;
  }
  if(op ==  "+") return a + b ;
  if(op ==  "-") return a - b ;
  if(op ==  "*") return a * b ;
  if(op ==  "/") return a / b ;
  if(op ==  "^") return pow(a, b) ;
  return b;
}
Token Token::calc(string op, const Token& t_a, const Token& t_b){
  Token result;
  int res_i; float res_f;
  switch(t_a.type) {
    case INTEGER:
      res_i = calc_v(op, get<int>(t_a.value), t_b);
      result = Token(res_i, INTEGER);
      break;
    case FLOAT:
      res_f = calc_v(op, get<float>(t_a.value), t_b);
      result = Token(res_f, FLOAT);
      break;
    default:
      break;
  }
  return result;
}


#ifdef __MAIN__
#undef __MAIN__
int main() {
  vector<Token> tokens = {
    Token(10, INTEGER),
    Token("+", OPERATOR),
    Token(20, INTEGER),
    Token("+", OPERATOR),
    Token("+", OPERATOR),
    Token(20.123f, FLOAT),
    // Token::calc('+', Token(12.123f, FLOAT), Token(25,INTEGER)),
    Token::calc("+", Token(12, INTEGER), Token(25.123f, FLOAT)),
    //Token::calc("+", Token("12.123"), Token("25.12")),
  };
  vector<Token> tokens2 = {
    Token("10"),
    Token("+"),
    Token("20"),
    Token("20.123"),
  };


  tokens.push_back(Token("hello", STRING));
  tokens.push_back(Token("world", STRING));
  vector<Token> tokens3 = move(tokens);

  for(Token t : tokens3) 
    t.print();

  cout << "\n";
  return 0;
}

#endif
