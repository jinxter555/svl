#include <iostream>
#include <variant>
#include <string>
#include <vector>
#include <stack>

#pragma once
using namespace std;


typedef variant<char, int, long long, float, double, string> token_value_t;
enum token_enum_t {
    CHAR=0,
    INTEGER=1,
    LONG=2,
    FLOAT=3,
    DOUBLE=4,
    OPERATOR=5,
    STRING=6,
    INDENTIFIER=7,
    PAIRS=8,
    FUNCTION=9,
};

class Token {
private:
public:
  token_value_t value;
  token_enum_t type;

  Token() {}
  Token(string);
  Token(token_value_t v, token_enum_t t) : value(v), type(t) {}
  static Token calc(string op, const Token& a, const Token& b);
  void print();

  bool is_operator(string op);
  bool is_operator()  const { return type==OPERATOR;}

  string op() const;        // return operator
  string funcname() const;  // return function name

  bool operator==(const string& rhs) const;
  bool operator==(const char* rhs) const ;
  bool is_number() const  { 
    return type == INTEGER || type == FLOAT || type == LONG || type==DOUBLE; }
};
