#include <iostream>
#include <variant>
#include <string>
#include <vector>
#include <stack>

#pragma once
using namespace std;


typedef variant<char, int, long long, float, double, string> token_value_t;
enum token_enum_t {
    CHAR=10,
    INTEGER=11,
    LONG=12,
    FLOAT=13,
    DOUBLE=14,
    STRING=15,
    INDENTIFIER=20,
    FUNCTION=21,
    OP_BIN=30,
    OP_UNI=31,
    PAIRS=49,
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
  void print_t();

  static token_enum_t check_operator(string op);
  static string type_str(token_enum_t t);

  bool is_operator()  const { return type==OP_BIN || type==OP_UNI;}
  bool is_op_bin()  const { return type==OP_BIN;}
  bool is_op_uni()  const { return type==OP_UNI;}

  string op() const;        // return operator
  string funcname() const;  // return function name
  string identifer() const;  // return function name

  bool operator==(const string& rhs) const;
  bool operator==(const char* rhs) const ;
  bool is_number() const  { 
    return type == INTEGER || type == FLOAT || type == LONG || type==DOUBLE; }
};
