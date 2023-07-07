#include <iostream>
#include <variant>
#include <string>
#include <vector>
#include <stack>

using namespace std;

typedef variant<char, int, long long, float, double, string> token_value_t;
enum token_enum_t {
    CHAR,
    INTEGER,
    LONG,
    FLOAT,
    DOUBLE,
    OPERATOR,
    STRING,
    FUNCTION
};

class Token {
private:
  bool is_operator(char);
public:
  token_value_t value;
  token_enum_t type;

  Token(string);
  Token(token_value_t v, token_enum_t t) : value(v), type(t) {}

  void print() {
    visit([](auto&& arg) {
        cout << "token value: " << arg << endl;
    }, value);
  }
};

Token::Token(string str) {
  if(str.find_first_not_of("0123456789") == string::npos) {
    value = stoi(str), 
    type =   INTEGER;
  } else if (str.find_first_not_of("0123456789.") == string::npos) {
    value = stof(str);
    type = FLOAT;
  } else if (str.size() == 1 && is_operator(str[0])) {
    value = str[0];
    type = OPERATOR;
  } else {
    value = str, 
    type = STRING;
  }
}


bool Token::is_operator(char op) {
  switch (op) {
    case '+': case '-': case '*': case '/': case '^':
      return true;
    default:
      return false;
  }
}

int main() {
  /* 
   * vector<Token> tokens = {
    Token(10, INTEGER),
    Token('+', OPERATOR),
    Token(20, INTEGER),
    Token('+', OPERATOR),
    Token('+', OPERATOR),
    Token(20.123f, FLOAT),
  };
  */
  vector<Token> tokens = {
    Token("10"),
    Token("+"),
    Token("20"),
    Token("20.123"),
  };



  for(Token t : tokens) 
    t.print();

  cout << "\n";
  return 0;
}


