
#include <iostream>
#include <string>
#include <vector>
#include <readline/readline.h>
#include <readline/history.h>


using namespace std;

class Token {
private:
  bool quoted=false;
  string multiline="";


  vector<string> tokens;

  bool is_token_separator(char c) {
    return c == ' ' || c == '\t' || c == '\n' || c == '\r'; }
  bool is_special_token(char c) {
    return c == '=' || c == ':'; }

  string read_quoted_string(const string& input, int &i, int l);
  string read_digit_string(const string& input, int &i, int l);
  string read_alno_string(const string& input, int &i, int l);
public:
  void tokenize(const string& input);
  void clear_token() {tokens.clear();}
  string readyline(const string& input);
  void print_tokens() {
    for(string token: tokens) {
      cout <<  token <<  endl;
    }
  }
};


/*
 * checks if input "multiline" text is properly quoted 
 * if not properly quoted it asks for more line until 
 * end of quote
 */
string Token::readyline(const string& input) {
  for (int i = 0; i < input.size(); i++) {
    if (input[i] == '\"') {
      if (i > 0 && input[i - 1] == '\\') { // ignore \"
        continue;
      }
      quoted = !quoted;   // found quoted
    }
  }
  if (quoted) {
    multiline += input + "\n";
  } else {
    string result = multiline += input;
    multiline = "";
    return result;
  }
  return "";
}  


string Token::read_quoted_string(const string& input, int &i, int l) {
  string quoted_string = "";
  bool escape_char = false, well_quoted=false;
  for (i = i + 1; i < l; i++) {
    if (input[i] == '"' && !escape_char) {
      well_quoted = true;
      break;
    } else {
      if(input[i] == '\\')
        escape_char = true;
      else 
        escape_char = false;
      quoted_string += input[i];
    }
  }
  if(!well_quoted) {
    throw invalid_argument("Input is not quoted properly.");
  }
  i++;
  return quoted_string;
}

string Token::read_alno_string(const string& input, int &i, int l) {
  string alno_string = "";
  for (i = i; i < l; i++) {
    if (isalnum(input[i]) || input[i]=='.' ) {
      alno_string += input[i];
    } else {
      break;
    }
  }
  return alno_string;
}

string Token::read_digit_string(const string& input, int &i, int l) {
  string digit_string = "";
  for (i = i; i < l; i++) {
    if (isdigit(input[i]) || input[i]=='.' ) {
      digit_string += input[i];
    } else {
      break;
    }
  }
  return digit_string;
}

void Token::tokenize(const string& input) {
  string current_token = "";
  int l = input.length();

  for(int i=0; i<l; i++) {
    if(input[i] == '"') 
      tokens.push_back(read_quoted_string(input, i, l));

    if(isdigit(input[i]))
      tokens.push_back(read_digit_string(input, i, l));

    if(isalnum(input[i]))
      tokens.push_back(read_alno_string(input, i, l));

    if(!is_token_separator(input[i])) {
      if(i < l) // side effect from helper function
        tokens.push_back(string(1, input[i]));
    }
  }
}

int main() {
  char* input;
  bool quoted = false;
  Token t;


  while ((input = readline("> ")) != nullptr) {
    add_history(input);
    std::string str(input);
    free(input);          
    if (str == "exit") break;          
    string text=t.readyline(str);
    if(text!=""){        // return "" if more text is quoted and multiline 
      t.tokenize(text);
      t.print_tokens();
      t.clear_token();
    }
  }  
  return 0;
}

