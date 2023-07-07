#include <iostream>
#include <string>
#include <vector>
#include <readline/readline.h>
#include <readline/history.h>

#include "readinputline.hh"
/*
 * checks if input "multiline" text is properly quoted 
 * if not properly quoted it asks for more line until 
 * end of quote
 */
string ReadInputLine::readyline(const string& input) {
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



string ReadInputLine::read_quoted_string(const string& input, int &i, int l) {
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

string ReadInputLine::read_alno_string(const string& input, int &i, int l) {
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

string ReadInputLine::read_digit_string(const string& input, int &i, int l) {
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

string ReadInputLine::read_op_string(const string& input, int &i, int l){
  string op_string = "";
  for (i = i; i < l; i++) {
    if (ispunct(input[i])  ) {
      op_string += input[i];
    } else {
      break;
    }
  }
  i--; // take one step back because of the parent call for loop will i++
  return op_string;
}

string ReadInputLine::read_unknown_token(const string& input, int &i, int l){
  string u_string = "";
  for (i = i; i < l; i++) {
    if (!isspace(input[i])  ) {
      u_string += input[i];
    } else {
      break;
    }
  }
  return u_string;
}

void ReadInputLine::tokenize(const string& input) {
  string str;
  int l = input.length();


  for(int i=0; i<l; i++) {
    if(input[i] == '"') {   // get quoted string text
      str = read_quoted_string(input, i, l);
      infix_tokens.push_back(Token(str, STRING));
      tokens.push_back(str);
    }

    if(isdigit(input[i])) {
      str = read_digit_string(input, i, l);
      if(str.find_first_not_of("0123456789") == string::npos) {
        infix_tokens.push_back(Token(stoi(str), INTEGER));
      } else if(str.find_first_not_of("0123456789.") == string::npos) {
        infix_tokens.push_back(Token(stof(str), FLOAT));
      }
      tokens.push_back(str);
    }

    if(isalnum(input[i])) {
      str = read_alno_string(input, i, l);
      tokens.push_back(str);
      infix_tokens.push_back(Token(str, INDENTIFIER));
    }

    if(is_pair_separator(input[i])) {
      str = string(1, input[i]);
      infix_tokens.push_back(Token(str, PAIRS));
      tokens.push_back(str);
      continue;
    }

    if(!isspace(input[i])) { 
      if(i < l)  {// side effect from helper function
        str = read_op_string(input, i, l);
        infix_tokens.push_back(Token(str, OPERATOR));
        tokens.push_back(str);
      }
    }
  }
}

bool ReadInputLine::is_pair_separator(char c) { 
  switch(c) {
    case '(': case ')':
    case '[': case ']':
    case '{': case '}':
      return true;
    default:
      return false;
  }
}

void ReadInputLine::clear_token() {
  tokens.clear(); 
  infix_tokens.clear();
}

/*
int main() {
  char* input;
  ReadInputLine t;

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

*/

