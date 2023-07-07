#include <iostream>
#include <string>
#include <vector>
#include <readline/readline.h>
#include <readline/history.h>
#include "token.hh"

#pragma once

using namespace std;

class ReadInputLine {
private:
  bool quoted=false;
  string multiline="";
  vector<string> tokens;
  vector<Token> infix_tokens;

  bool is_pair_separator(char c);

  string read_quoted_string(const string& input, int &i, int l);
  string read_digit_string(const string& input, int &i, int l);
  string read_alno_string(const string& input, int &i, int l);
  string read_op_string(const string& input, int &i, int l);
  string read_unknown_token(const string& input, int &i, int l);

  friend class Expr;
  friend class Parser;
public:
  void tokenize(const string& input);
  void clear_token();
  string readyline(const string& input);
  void print_tokens() {
    cout << "ReadINputLine print_tokens(): \n";
    //for(string token: tokens) {
    //  cout <<  token <<  endl;
    //}
    for(Token token: infix_tokens) {
      token.print();
    }
  }
};
